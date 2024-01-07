#include "out.h"


// FD_CPY(fd_set*, fd_set*, int)

void FD_CPY(fd_set *param_1,fd_set *param_2,int param_3)

{
  int local_18;
  uint local_14;
  
  for (local_14 = 0; local_14 < 0x10; local_14 = local_14 + 1) {
    param_2->fds_bits[local_14] = 0;
  }
  for (local_18 = 0; local_18 <= param_3; local_18 = local_18 + 1) {
    if ((param_1->fds_bits[(ulong)(long)local_18 >> 6] >> ((byte)local_18 & 0x3f) & 1U) != 0) {
      param_2->fds_bits[(ulong)(long)local_18 >> 6] =
           param_2->fds_bits[(ulong)(long)local_18 >> 6] | 1L << ((byte)local_18 & 0x3f);
    }
  }
  return;
}



void main(int param_1,undefined8 *param_2)

{
  uint16_t uVar1;
  int iVar2;
  fd_set local_188;
  fd_set local_108;
  socklen_t local_7c;
  sockaddr local_78;
  socklen_t local_5c;
  sockaddr local_58;
  int local_44;
  int local_40;
  uint local_3c;
  fd_set *local_38;
  int local_2c;
  hostent *local_28;
  char *local_20;
  int local_18;
  int local_14;
  hostent *local_10;
  
  if (param_1 != 1) {
    fprintf(stderr,"usage : %s\n",*param_2);
                    // WARNING: Subroutine does not return
    exit(1);
  }
  local_44 = startserver();
  if (local_44 == -1) {
                    // WARNING: Subroutine does not return
    exit(1);
  }
  local_38 = &local_108;
  for (local_3c = 0; local_3c < 0x10; local_3c = local_3c + 1) {
    local_108.fds_bits[local_3c] = 0;
  }
  local_108.fds_bits[(ulong)(long)local_44 >> 6] =
       1L << ((byte)local_44 & 0x3f) | local_108.fds_bits[(ulong)(long)local_44 >> 6];
  local_40 = local_44;
  while( true ) {
    do {
      FD_CPY(&local_108,&local_188,local_40);
      iVar2 = select(local_40 + 1,&local_188,(fd_set *)0x0,(fd_set *)0x0,(timeval *)0x0);
      if (iVar2 == -1) {
        perror("select");
                    // WARNING: Subroutine does not return
        exit(1);
      }
      for (local_2c = 3; local_2c <= local_40; local_2c = local_2c + 1) {
        if ((local_2c != local_44) &&
           ((local_188.fds_bits[(ulong)(long)local_2c >> 6] >> ((byte)local_2c & 0x3f) & 1U) != 0))
        {
          local_5c = 0x10;
          iVar2 = getpeername(local_2c,&local_58,&local_5c);
          if (iVar2 == -1) {
            perror("getpeername");
          }
          local_28 = gethostbyaddr(local_58.sa_data + 2,4,2);
          local_20 = (char *)recvtext(local_2c);
          if (local_20 == (char *)0x0) {
            uVar1 = ntohs(local_58.sa_data._0_2_);
            printf("admin: disconnect from \'%s(%hu)\'\n",local_28->h_name,(ulong)uVar1);
            close(local_2c);
            local_108.fds_bits[(ulong)(long)local_2c >> 6] =
                 ~(1L << ((byte)local_2c & 0x3f)) & local_108.fds_bits[(ulong)(long)local_2c >> 6];
          }
          else {
            for (local_18 = 3; local_18 <= local_40; local_18 = local_18 + 1) {
              if (((local_18 != local_44) && (local_18 != local_2c)) &&
                 (((byte)(local_108.fds_bits[(ulong)(long)local_18 >> 6] >> ((byte)local_18 & 0x3f))
                  & 1) == 1)) {
                sendtext(local_18,local_20);
              }
            }
            uVar1 = ntohs(local_58.sa_data._0_2_);
            printf("%s(%hu): %s",local_28->h_name,(ulong)uVar1,local_20);
            free(local_20);
          }
        }
      }
    } while ((local_188.fds_bits[(ulong)(long)local_44 >> 6] >> ((byte)local_44 & 0x3f) & 1U) == 0);
    local_7c = 0x10;
    local_14 = accept(local_44,&local_78,&local_7c);
    if (local_14 == -1) break;
    local_108.fds_bits[(ulong)(long)local_14 >> 6] =
         1L << ((byte)local_14 & 0x3f) | local_108.fds_bits[(ulong)(long)local_14 >> 6];
    if (local_40 < local_14) {
      local_40 = local_14;
    }
    local_10 = gethostbyaddr(local_78.sa_data + 2,4,2);
    uVar1 = ntohs(local_78.sa_data._0_2_);
    printf("admin: connect from \'%s\' at \'%hu\'\n",local_10->h_name,(ulong)uVar1);
  }
  perror("accept");
                    // WARNING: Subroutine does not return
  exit(0);
}



// sendtext(int, char*)

undefined8 sendtext(int param_1,char *param_2)

{
  uint32_t uVar1;
  size_t sVar2;
  ulong local_30;
  ulong local_10;
  
  if (param_2 == (char *)0x0) {
    local_30 = 0;
  }
  else {
    sVar2 = strlen(param_2);
    local_30 = sVar2 + 1;
  }
  local_10 = local_30;
  uVar1 = htonl((uint32_t)local_30);
  local_10 = (ulong)uVar1;
  write(param_1,&local_10,8);
  uVar1 = ntohl((uint32_t)local_10);
  local_10 = (ulong)uVar1;
  if (local_10 != 0) {
    write(param_1,param_2,local_10);
  }
  return 1;
}



// readn(int, char*, int)

undefined4 readn(int param_1,char *param_2,int param_3)

{
  int iVar1;
  ssize_t sVar2;
  int local_1c;
  char *local_18;
  
  local_1c = param_3;
  local_18 = param_2;
  while( true ) {
    if (local_1c < 1) {
      return 1;
    }
    sVar2 = read(param_1,local_18,(long)local_1c);
    iVar1 = (int)sVar2;
    if (iVar1 < 1) break;
    local_1c = local_1c - iVar1;
    local_18 = local_18 + iVar1;
  }
  if (iVar1 == -1) {
    perror("read");
  }
  return 0;
}



// recvtext(int)

char * recvtext(int param_1)

{
  int iVar1;
  uint32_t uVar2;
  ulong local_18;
  char *local_10;
  
  iVar1 = readn(param_1,(char *)&local_18,8);
  if (iVar1 == 0) {
    return (char *)0x0;
  }
  uVar2 = ntohl((uint32_t)local_18);
  local_18 = (ulong)uVar2;
  local_10 = (char *)0x0;
  if (local_18 != 0) {
    local_10 = (char *)malloc(local_18);
    if (local_10 == (char *)0x0) {
      fwrite("error : unable to malloc\n",1,0x19,stderr);
      return (char *)0x0;
    }
    iVar1 = readn(param_1,local_10,(int)local_18);
    if (iVar1 == 0) {
      free(local_10);
      return (char *)0x0;
    }
  }
  return local_10;
}



// hooktoserver(char*, char*)

int hooktoserver(char *param_1,char *param_2)

{
  uint16_t uVar1;
  int iVar2;
  char *pcVar3;
  int local_9c;
  addrinfo local_88;
  addrinfo *local_58;
  socklen_t local_4c;
  sockaddr local_48 [2];
  int local_20;
  int local_1c;
  addrinfo *local_10;
  
  bzero(&local_88,0x30);
  local_88.ai_family = 0;
  local_88.ai_socktype = 1;
  local_1c = getaddrinfo(param_1,param_2,&local_88,&local_58);
  if (local_1c == 0) {
    local_10 = local_58;
    local_1c = 0;
    do {
      local_20 = socket(local_58->ai_family,local_58->ai_socktype,local_58->ai_protocol);
      if (-1 < local_20) {
        iVar2 = connect(local_20,local_58->ai_addr,local_58->ai_addrlen);
        if (iVar2 == 0) break;
        close(local_20);
      }
      local_58 = local_58->ai_next;
    } while (local_58 != (addrinfo *)0x0);
    freeaddrinfo(local_10);
    if (local_20 < 0) {
      puts("socket error");
      local_9c = -1;
    }
    else {
      local_4c = 0x10;
      iVar2 = getsockname(local_20,local_48,&local_4c);
      if (iVar2 == -1) {
        perror("getsockname");
        local_9c = -1;
      }
      else {
        uVar1 = ntohs(local_48[0].sa_data._0_2_);
        printf("admin: connected to server on \'%s\' at \'%s\' thru \'%hu\'\n",param_1,param_2,
               (ulong)uVar1);
        local_9c = local_20;
      }
    }
  }
  else {
    pcVar3 = gai_strerror(local_1c);
    printf("getaddrinfo wrong: %s\n",pcVar3);
    local_9c = -1;
  }
  return local_9c;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked
// startserver()

int startserver(void)

{
  uint16_t uVar1;
  int iVar2;
  char *pcVar3;
  int local_16c;
  char local_168 [256];
  addrinfo local_68;
  addrinfo *local_38;
  socklen_t local_2c;
  sockaddr local_28;
  int local_18;
  int local_14;
  
  local_18 = socket(2,1,6);
  if (local_18 == -1) {
    perror("socket");
    local_16c = -1;
  }
  else {
    bzero(&local_28,0x10);
    local_28.sa_family = 2;
    local_28.sa_data._2_4_ = htonl(0);
    local_28.sa_data._0_2_ = htons(0);
    iVar2 = bind(local_18,&local_28,0x10);
    if (iVar2 == -1) {
      perror("bind");
      local_16c = -1;
    }
    else {
      listen(local_18,5);
      local_2c = 0x10;
      iVar2 = getsockname(local_18,&local_28,&local_2c);
      if (iVar2 == -1) {
        perror("getsockname");
        local_16c = -1;
      }
      else {
        gethostname(local_168,0x100);
        bzero(&local_68,0x30);
        local_68.ai_family = 0;
        local_68.ai_socktype = 1;
        local_68.ai_flags = 2;
        local_14 = getaddrinfo(local_168,(char *)0x0,&local_68,&local_38);
        if (local_14 == 0) {
          uVar1 = ntohs(local_28.sa_data._0_2_);
          printf("admin: started server on \'%s\' at \'%hu\'\n",local_38->ai_canonname,(ulong)uVar1)
          ;
          freeaddrinfo(local_38);
          local_16c = local_18;
        }
        else {
          pcVar3 = gai_strerror(local_14);
          printf("getaddrinfo wrong: %s\n",pcVar3);
          local_16c = -1;
        }
      }
    }
  }
  return local_16c;
}


