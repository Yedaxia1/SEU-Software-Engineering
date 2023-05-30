/*
    71118415 叶宏庭
    2021-05-31 22:09:16
*/

#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <stdlib.h>

#define MCASTADDR "234.5.6.7"
#define MCASTPORT 12345
#define BUFSIZE 1024
#define DEFAULT_COUNT 500

BOOL bSender = TRUE,
     bLoopBack = TRUE;

DWORD dwInterface,
      dwMulticastGroup,
      dwCount;

short iPort;

void usage(char *progname)
{
    
}

void ValidateArgs()
{
    // 定义网络参数
    dwInterface = INADDR_ANY;
    dwMulticastGroup = inet_addr(MCASTADDR);
    iPort = MCASTPORT;
    dwCount = DEFAULT_COUNT;
}

int main(int argc, char **argv)
{
    WSADATA wsd;
    struct sockaddr_in local,
                       remote,
                       from;
    SOCKET sock, sockM;
    TCHAR recvbuf[BUFSIZE],
          sendbuf[BUFSIZE];
    int len = sizeof(struct sockaddr_in),
        optval,
        ret;
    DWORD i=0;

    ValidateArgs();

    if(WSAStartup(MAKEWORD(2, 2), &wsd) != 0){
        printf("WSAStartup() failed\n");
        return -1;
    }

    if((sock = WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,
                            WSA_FLAG_MULTIPOINT_C_LEAF|WSA_FLAG_MULTIPOINT_D_LEAF|
		                    WSA_FLAG_OVERLAPPED))==INVALID_SOCKET)
    {
        printf("socket failed with:%d\n",WSAGetLastError());
	    WSACleanup();
	    return -1;
    }

    bool  reuseport = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuseport, sizeof(bool));

    /* local.sin_family=AF_INET;
    local.sin_port = htons(iPort+1);
    local.sin_addr.s_addr = dwInterface;

    if(bind(sock,(struct sockaddr *)&local ,sizeof(local))==SOCKET_ERROR){
        printf("bind failed with :%d \n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return -1;
    } */

    remote.sin_family =AF_INET;
	remote.sin_port = htons(iPort);
	remote.sin_addr.s_addr = dwMulticastGroup;

    /* optval = 8;
    if(setsockopt(sock,IPPROTO_IP,IP_MULTICAST_TTL,(char *)&optval,sizeof(int))==SOCKET_ERROR){
		printf("setsockopt(IP_MULTICAST_TTL) failed: %d\n",WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return -1;
	} */

    /* if(bLoopBack)
    {
        optval = 0;
        if(setsockopt(sock,IPPROTO_IP,IP_MULTICAST_LOOP,(char *)&optval,sizeof(optval))==SOCKET_ERROR){
            printf("setsockopt(IP_MULTICAST_LOOP) failed: %d\n",WSAGetLastError());
            closesocket(sock);
            WSACleanup();
            return -1;
	    }
    } */

    if((sockM = WSAJoinLeaf(sock,(SOCKADDR *)&remote,sizeof(remote),NULL,NULL,NULL,NULL,JL_BOTH))==INVALID_SOCKET){
		printf("WSAJoinLeaf() failed : %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
//		WSACLeanup();
		return -1;
	}


    if(!bSender)
    {   // 接收端
        printf("Start rece...\n");
        for(i = 0;i < dwCount;i++)
        {
            //printf("hhh");
            if((ret = recvfrom(sock ,recvbuf,BUFSIZE,0, (struct sockaddr *)&from , &len))==SOCKET_ERROR){
                printf("recvfrom failed with: %d\n" , WSAGetLastError());
                closesocket(sockM);
                closesocket(sock);
                WSACleanup();
                return -1;
		    }
            recvbuf[ret] = 0;
            printf("RECV: '%s' from <%s>\n", recvbuf, inet_ntoa(from.sin_addr));
        }
    }
    else
    {   // 发送端
        printf("Start send...\n");
        for ( i = 0; i < dwCount; i++)
        {
            sprintf(sendbuf, "server 1: This is a test: %d", i);
            printf("%s\n", sendbuf);
            if (sendto(sock,(char *)sendbuf,strlen(sendbuf),0,(struct sockaddr *) &remote,sizeof(remote))==SOCKET_ERROR){
                printf("sendto failed with: %d\n", WSAGetLastError());
                closesocket(sockM);
                closesocket(sock);
                WSACleanup();
                return -1;
	    	}
            Sleep(500);
        }
        
    }
    closesocket(sock);

    WSACleanup();
    return -1;
}

