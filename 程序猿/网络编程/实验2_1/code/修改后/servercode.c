/****************************************************/
/************* datetime Example Server **************/
/****************************************************/
#include "datetime.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int
main( int argc , char * * argv )
{
	int listenfd , connfd;
	struct sockaddr_in servaddr;
	char buff[ MAXLINE ];
	pid_t pid;

	listenfd = socket( AF_INET , SOCK_STREAM , 0 );

	memset( &servaddr , 0 , sizeof( servaddr ) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
	servaddr.sin_port = htons( 13 );

	bind( listenfd , (struct sockaddr *)&servaddr , sizeof( servaddr ) );
	listen( listenfd , 1024 );
	/*
	time_t timep;
	time(&timep);
	printf("%s", asctime(gmtime(&timep)));
	*/

	for( ; ; )
	{
		connfd = accept( listenfd , (struct sockaddr *)NULL , NULL );
		if((pid = fork()) == 0){
			close(listenfd);
			time_t ticks;
			time(&ticks );
			snprintf( buff , sizeof( buff ) , "%.24s\r\n" , ctime(&ticks) );
			printf("%s\n", buff);
			write( connfd , buff , strlen( buff ) );
			close( connfd );
			printf("%s\n", "Into sleep!!");
			sleep(2);
			printf("%s\n", "Out sleep and exit!!");
			exit(0);
		}
		close(connfd);
	} 
}
