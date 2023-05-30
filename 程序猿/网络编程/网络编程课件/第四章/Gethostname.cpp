////////////////////////////////////////////////////////////////
// VCKBASE Online Journal
//
// getip1.cpp
//
// �����򱨸汾����ÿһ��������IP��ַ:
//
// ��ʾ��Ҫ�ڻ�����������ȷָ��wsock32.lib���·��;
//
// Make sure your INCLUDE and LIB environment variables are set up properly;
// you can run vcvars32.bat
//
#include <winsock.h>
#include <wsipx.h>
#include <wsnwlink.h>
#include <stdio.h>

int main()
{
	// ��ʼ�� Windows sockets API. Ҫ��汾Ϊ version 1.1
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData)) {
		printf("WSAStartup failed %s\n", WSAGetLastError());
		return -1;
	}

	// ���������.
	char hostname[256];
	int res = gethostname(hostname, sizeof(hostname));
	if (res != 0) {
		printf("Error: %u\n", WSAGetLastError());
		return -1;
	}
	printf("hostname=%s\n", hostname);

	// ������������ȡ������Ϣ. 
	hostent* pHostent = gethostbyname(hostname);
	if (pHostent==NULL) {
		printf("Error: %u\n", WSAGetLastError());
		return -1;
	}

	// �������ص�hostent��Ϣ
	hostent& he = *pHostent;
	printf("name=%s\naliases=%s\naddrtype=%d\nlength=%d\n",	he.h_name, he.h_aliases, he.h_addrtype, he.h_length);

	sockaddr_in sa;
	for (int nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) {
		memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
		printf("Address: %s\n", inet_ntoa(sa.sin_addr));		//�������ص�hostent��Ϣdisplay as string
	}
	
	//����gethostbyaddr()����
	struct sockaddr_in LocalHostAddr;//����������ַ 
	HOSTENT* pResult;

	LocalHostAddr.sin_family=AF_INET; 
	LocalHostAddr.sin_port=htons(u_short(21)); 
	//�Ȼ��IP����ͨ��IP���hostname
	for (nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) {
		memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
		LocalHostAddr.sin_addr.s_addr=inet_addr(inet_ntoa(sa.sin_addr)); 
		pResult=gethostbyaddr((const char *) & (LocalHostAddr.sin_addr.s_addr),4,AF_INET); 

		printf("Host Name: %s\n", pResult->h_name);		//�������ص�hostent��Ϣdisplay as string
	}
	struct servent * sptr;
	sptr=getservbyname("domain", "udp");
	printf("Test getservbyname: %s\n",sptr->s_aliases);

	sptr=getservbyport(htons(53), "udp");
	printf("Test getservbyport: %s\n",sptr->s_aliases);

	
	// ��ֹ Windows sockets API
	WSACleanup();

	return 0;
}