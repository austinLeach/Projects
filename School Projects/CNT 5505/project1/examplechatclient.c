

//----- (0000000000400E5C) ----------------------------------------------------
int __fastcall __noreturn main(int argc, const char **argv, const char **envp)
{
  char s[1024]; // [rsp+10h] [rbp-490h] BYREF
  fd_set readfds; // [rsp+410h] [rbp-90h] BYREF
  int v5; // [rsp+494h] [rbp-Ch]
  void *ptr; // [rsp+498h] [rbp-8h]

  if ( argc != 3 )
  {
    fprintf(stderr, "usage : %s <servhost> <servport>\n", *argv);
    exit(1);
  }
  v5 = hooktoserver((char *)argv[1], (char *)argv[2]);
  if ( v5 == -1 )
    exit(1);
  while ( 1 )
  {
    readfds.fds_bits[0] |= 1uLL;
    readfds.fds_bits[(unsigned __int64)v5 >> 6] |= 1LL << (v5 & 0x3F);
    if ( select(v5 + 1, &readfds, 0LL, 0LL, 0LL) == -1 )
      break;
    if ( ((readfds.fds_bits[(unsigned __int64)v5 >> 6] >> (v5 & 0x3F)) & 1) != 0 )
    {
      ptr = recvtext(v5);
      if ( !ptr )
      {
        fwrite("error: server died\n", 1uLL, 0x13uLL, stderr);
        exit(1);
      }
      printf(">>> %s", (const char *)ptr);
      free(ptr);
    }
    if ( (readfds.fds_bits[0] & 1) != 0 )
    {
      if ( !fgets(s, 1024, stdin) )
        exit(0);
      sendtext(v5, s);
    }
  }
  perror("select");
  exit(1);
}

//----- (0000000000401028) ----------------------------------------------------
__int64 __fastcall sendtext(int a1, char *a2)
{
  uint32_t v2; // eax
  size_t v4; // [rsp+8h] [rbp-28h]
  uint32_t hostlong[2]; // [rsp+28h] [rbp-8h] BYREF

  if ( a2 )
    v4 = strlen(a2) + 1;
  else
    LODWORD(v4) = 0;
  *(_QWORD *)hostlong = htonl(v4);
  write(a1, hostlong, 8uLL);
  v2 = ntohl(hostlong[0]);
  *(_QWORD *)hostlong = v2;
  if ( v2 )
    write(a1, a2, *(size_t *)hostlong);
  return 1LL;
}

//----- (00000000004010B7) ----------------------------------------------------
__int64 __fastcall readn(int a1, char *a2, int a3)
{
  int v7; // [rsp+3Ch] [rbp-4h]

  while ( 1 )
  {
    if ( a3 <= 0 )
      return 1;
    v7 = read(a1, a2, a3);
    if ( v7 <= 0 )
      break;
    a3 -= v7;
    a2 += v7;
  }
  if ( v7 == -1 )
    perror("read");
  return 0;
}

//----- (000000000040112E) ----------------------------------------------------
void *__fastcall recvtext(int a1)
{
  uint32_t v1; // eax
  uint32_t netlong[2]; // [rsp+10h] [rbp-10h] BYREF
  void *ptr; // [rsp+18h] [rbp-8h]

  if ( (unsigned int)readn(a1, (char *)netlong, 8) )
  {
    v1 = ntohl(netlong[0]);
    *(_QWORD *)netlong = v1;
    ptr = 0LL;
    if ( v1 )
    {
      ptr = malloc(*(size_t *)netlong);
      if ( !ptr )
      {
        fwrite("error : unable to malloc\n", 1uLL, 0x19uLL, stderr);
        return 0LL;
      }
      if ( !(unsigned int)readn(a1, (char *)ptr, netlong[0]) )
      {
        free(ptr);
        return 0LL;
      }
    }
    return ptr;
  }
  return 0LL;
}

//----- (00000000004011FA) ----------------------------------------------------
__int64 __fastcall hooktoserver(char *a1, char *a2)
{
  const char *v2; // rax
  uint16_t v3; // ax
  struct addrinfo s; // [rsp+20h] [rbp-80h] BYREF
  struct addrinfo *pai; // [rsp+50h] [rbp-50h] BYREF
  socklen_t len; // [rsp+5Ch] [rbp-44h] BYREF
  struct sockaddr addr; // [rsp+60h] [rbp-40h] BYREF
  int fd; // [rsp+88h] [rbp-18h]
  int ecode; // [rsp+8Ch] [rbp-14h]
  struct addrinfo *ai; // [rsp+98h] [rbp-8h]

  bzero(&s, 0x30uLL);
  s.ai_family = 0;
  s.ai_socktype = 1;
  ecode = getaddrinfo(a1, a2, &s, &pai);
  if ( ecode )
  {
    v2 = gai_strerror(ecode);
    printf("getaddrinfo wrong: %s\n", v2);
    return (unsigned int)-1;
  }
  else
  {
    ai = pai;
    do
    {
      fd = socket(pai->ai_family, pai->ai_socktype, pai->ai_protocol);
      if ( fd >= 0 )
      {
        if ( !connect(fd, pai->ai_addr, pai->ai_addrlen) )
          break;
        close(fd);
      }
      pai = pai->ai_next;
    }
    while ( pai );
    freeaddrinfo(ai);
    if ( fd >= 0 )
    {
      len = 16;
      if ( getsockname(fd, &addr, &len) == -1 )
      {
        perror("getsockname");
        return (unsigned int)-1;
      }
      else
      {
        v3 = ntohs(*(uint16_t *)addr.sa_data);
        printf("admin: connected to server on '%s' at '%s' thru '%hu'\n", a1, a2, v3);
        return (unsigned int)fd;
      }
    }
    else
    {
      puts("socket error");
      return (unsigned int)-1;
    }
  }
}

//----- (0000000000401387) ----------------------------------------------------
__int64 startserver(void)
{
  const char *v0; // rax
  uint16_t v1; // ax
  char name[256]; // [rsp+10h] [rbp-160h] BYREF
  struct addrinfo req; // [rsp+110h] [rbp-60h] BYREF
  struct addrinfo *pai; // [rsp+140h] [rbp-30h] BYREF
  socklen_t len; // [rsp+14Ch] [rbp-24h] BYREF
  struct sockaddr s; // [rsp+150h] [rbp-20h] BYREF
  int fd; // [rsp+160h] [rbp-10h]
  int ecode; // [rsp+164h] [rbp-Ch]

  fd = socket(2, 1, 6);
  if ( fd == -1 )
  {
    perror("socket");
    return (unsigned int)-1;
  }
  else
  {
    bzero(&s, 0x10uLL);
    s.sa_family = 2;
    *(_DWORD *)&s.sa_data[2] = htonl(0);
    *(_WORD *)s.sa_data = htons(0);
    if ( bind(fd, &s, 0x10u) == -1 )
    {
      perror("bind");
      return (unsigned int)-1;
    }
    else
    {
      listen(fd, 5);
      len = 16;
      if ( getsockname(fd, &s, &len) == -1 )
      {
        perror("getsockname");
        return (unsigned int)-1;
      }
      else
      {
        gethostname(name, 0x100uLL);
        bzero(&req, 0x30uLL);
        req.ai_family = 0;
        req.ai_socktype = 1;
        req.ai_flags = 2;
        ecode = getaddrinfo(name, 0LL, &req, &pai);
        if ( ecode )
        {
          v0 = gai_strerror(ecode);
          printf("getaddrinfo wrong: %s\n", v0);
          return (unsigned int)-1;
        }
        else
        {
          v1 = ntohs(*(uint16_t *)s.sa_data);
          printf("admin: started server on '%s' at '%hu'\n", pai->ai_canonname, v1);
          freeaddrinfo(pai);
          return (unsigned int)fd;
        }
      }
    }
  }
}
