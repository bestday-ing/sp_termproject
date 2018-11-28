#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg)  {perror(msg); exit(1);}

int main(int ac, char *av[])
{
	struct sockaddr_in saddr,cli;
	struct hostent *hp;
	char hostname[HOSTLEN];
	int sock_id,sock_fd,clen = sizeof(cli);
	FILE *sock_fp;
	time_t thetime;
	char buf[256];
	

	sock_id = socket(PF_INET,SOCK_STREAM,0);
	if(sock_id == -1)
		oops("socket");

	bzero( (void*)&saddr, sizeof(saddr) );
	gethostname(hostname, HOSTLEN);
	hp = gethostbyname(hostname);

	bcopy( (void*)hp->h_addr, (void*)&saddr.sin_addr, hp->h_length);
	saddr.sin_port = htons(PORTNUM);
	saddr.sin_family = AF_INET;

	if(bind(sock_id , (struct sockaddr*)&saddr,sizeof(saddr)) != 0)
		oops("bind");

	if(listen(sock_id, 4) !=0)
		oops("listen");

	// main loop : accept(), write, close
	
	while(1) {
		sock_fd = accept(sock_id, (struct sockaddr *)&cli,&clen );
		if(sock_fd == -1)
		oops("accept");
		
		sprintf(buf,"%s",inet_ntoa(cli.sin_addr)); // client enters the server 
		
		strcpy(buf, "Welcome to my room");

		if(send(sock_fd,buf,strlen(buf)+1,0) == -1){
			perror("send");
			exit(1);
		}
		
		if(recv(sock_fd,buf,strlen(buf)+1,0) == -1){
			perror("recv");
			exit(1);
		}

		printf(" **From Client : %s\n",buf);
		close(sock_fd);
	}
}
