#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TTL 64
#define BUF_SIZE 30
#define address "127.0.0.1"
int main(int argc, char **argv)
{
	int send_sock;
	struct sockaddr_in mul_adr;
	int time_live = TTL;
	FILE *fp;
	char buf[BUF_SIZE];
	int port = 9190;
	

	send_sock=socket(PF_INET,SOCK_DGRAM,0);
	memset(&mul_adr,0,sizeof(mul_adr));
	mul_adr.sin_family=AF_INET;
	mul_adr.sin_addr.s_addr=inet_addr(address);
	mul_adr.sin_port=htons(port);

	setsockopt(send_sock, IPPROTO_IP,IP_MULTICAST_TTL,(void*)&time_live,sizeof(time_live));
	if((fp=fopen("data.txt","r")) == NULL)
	{
		perror("fopen");
		exit(1);
	}

	while(!feof(fp))
	{
		fgets(buf,BUF_SIZE,fp);
		sendto(send_sock, buf, strlen(buf),0,(struct sockaddr*)&mul_adr,sizeof(mul_adr));
		sleep(2);
	}
	close(fp);
	close(send_sock);
	return 0;

}

