
#include <defs.h>



//----- (0000000000400ECC) ----------------------------------------------------
__int64 __fastcall FD_CPY(fd_set *a1, fd_set *a2, int a3)
{
  __int64 result; // rax
  unsigned int j; // [rsp+14h] [rbp-10h]
  unsigned int i; // [rsp+18h] [rbp-Ch]

  for ( i = 0; i <= 0xF; ++i )
    a2->fds_bits[i] = 0LL;
  for ( j = 0; ; ++j )
  {
    result = j;
    if ( (int)j > a3 )
      break;
    if ( ((a1->fds_bits[(unsigned __int64)(int)j >> 6] >> (j & 0x3F)) & 1) != 0 )
      a2->fds_bits[(unsigned __int64)(int)j >> 6] |= 1LL << (j & 0x3F);
  }
  return result;
}

//----- (0000000000400F79) ----------------------------------------------------
int __fastcall __noreturn main(int argc, const char **argv, const char **envp)
{
  uint16_t v3; // ax
  uint16_t v4; // ax
  uint16_t v5; // ax
  fd_set readfds; // [rsp+10h] [rbp-180h] BYREF
  fd_set v7; // [rsp+90h] [rbp-100h] BYREF
  socklen_t addr_len; // [rsp+11Ch] [rbp-74h] BYREF
  struct sockaddr v9; // [rsp+120h] [rbp-70h] BYREF
  socklen_t len; // [rsp+13Ch] [rbp-54h] BYREF
  struct sockaddr addr; // [rsp+140h] [rbp-50h] BYREF
  int v12; // [rsp+154h] [rbp-3Ch]
  int v13; // [rsp+158h] [rbp-38h]
  unsigned int i; // [rsp+15Ch] [rbp-34h]
  fd_set *v15; // [rsp+160h] [rbp-30h]
  int fd; // [rsp+16Ch] [rbp-24h]
  struct hostent *v17; // [rsp+170h] [rbp-20h]
  void *ptr; // [rsp+178h] [rbp-18h]
  int j; // [rsp+180h] [rbp-10h]
  int v20; // [rsp+184h] [rbp-Ch]
  struct hostent *v21; // [rsp+188h] [rbp-8h]

  if ( argc != 1 )
  {
    fprintf(stderr, "usage : %s\n", *argv);
    exit(1);
  }
  v12 = startserver();
  if ( v12 == -1 )
    exit(1);
  v15 = &v7;
  for ( i = 0; i <= 0xF; ++i )
    v15->fds_bits[i] = 0LL;
  v7.fds_bits[(unsigned __int64)v12 >> 6] |= 1LL << (v12 & 0x3F);
  v13 = v12;
  while ( 1 )
  {
    FD_CPY(&v7, &readfds, v13);
    if ( select(v13 + 1, &readfds, 0LL, 0LL, 0LL) == -1 )
      break;
    for ( fd = 3; fd <= v13; ++fd )
    {
      if ( fd != v12 && ((readfds.fds_bits[(unsigned __int64)fd >> 6] >> (fd & 0x3F)) & 1) != 0 )
      {
        len = 16;
        if ( getpeername(fd, &addr, &len) == -1 )
          perror("getpeername");
        v17 = gethostbyaddr(&addr.sa_data[2], 4u, 2);
        ptr = recvtext(fd);
        if ( ptr )
        {
          for ( j = 3; j <= v13; ++j )
          {
            if ( j != v12 && j != fd && ((v7.fds_bits[(unsigned __int64)j >> 6] >> (j & 0x3F)) & 1) != 0 )
              sendtext(j, (char *)ptr);
          }
          v4 = ntohs(*(uint16_t *)addr.sa_data);
          printf("%s(%hu): %s", v17->h_name, v4, (const char *)ptr);
          free(ptr);
        }
        else
        {
          v3 = ntohs(*(uint16_t *)addr.sa_data);
          printf("admin: disconnect from '%s(%hu)'\n", v17->h_name, v3);
          close(fd);
          v7.fds_bits[(unsigned __int64)fd >> 6] &= ~(1LL << (fd & 0x3F));
        }
      }
    }
    if ( ((readfds.fds_bits[(unsigned __int64)v12 >> 6] >> (v12 & 0x3F)) & 1) != 0 )
    {
      addr_len = 16;
      v20 = accept(v12, &v9, &addr_len);
      if ( v20 == -1 )
      {
        perror("accept");
        exit(0);
      }
      v7.fds_bits[(unsigned __int64)v20 >> 6] |= 1LL << (v20 & 0x3F);
      if ( v20 > v13 )
        v13 = v20;
      v21 = gethostbyaddr(&v9.sa_data[2], 4u, 2);
      v5 = ntohs(*(uint16_t *)v9.sa_data);
      printf("admin: connect from '%s' at '%hu'\n", v21->h_name, v5);
    }
  }
  perror("select");
  exit(1);
}

//----- (0000000000401318) ----------------------------------------------------
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

//----- (00000000004013A7) ----------------------------------------------------
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

//----- (000000000040141E) ----------------------------------------------------
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

//----- (00000000004014EA) ----------------------------------------------------
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

//----- (0000000000401677) ----------------------------------------------------
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

