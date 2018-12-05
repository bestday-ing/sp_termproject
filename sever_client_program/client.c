#include "header.h"

#define MAXLINE 100
#define CH 1024
#define WAITING "Waiting user"
#define PORTNUM 30000

char quit[] = "/quit\n";
char list[] = "/list\n";
char smsg[] = "/smsg";

/************************************************************************/
void chatting(int, int, fd_set , char* );
void exec_chat();
/************************************************************************/
void loading(char* );
int set_ticker(int );

int main(){
	exec_chat();
}

void chatting(int sockfd, int maxfdp1, fd_set rset, char *nickname)
{
	char chatData[CH];
	char buf[CH];
	int n;

	while (1) {
		FD_ZERO(&rset);
		FD_SET(0, &rset);
		FD_SET(sockfd, &rset);	
		if (select(maxfdp1, &rset, (fd_set *)0, (fd_set *)0, (struct timeval *)0) <0) {
			printf("\n\n>> select error\n");
			sleep(2);
			return;
		} // FD_SET으로 설정된 fd만을 확인

		if (FD_ISSET(sockfd, &rset)) { // sockfd에 대한 소켓을 int로 return한다
			memset(chatData, 0, sizeof(chatData));
			if ((n = read(sockfd, chatData, sizeof(chatData))) >0) { //서버에게 받은 메세지를 읽고
				write(1, chatData, n); // 화면에 출력
			}
		}
		
		if (FD_ISSET(0, &rset)) {
			memset(buf, 0, sizeof(buf)); 
			if ((n = read(0, buf, sizeof(buf)))>0) { 
				if (!strcmp(buf, quit)) {
					write(sockfd, buf, strlen(buf));
					break;
				}
				if (!strcmp(buf, list)) {
					write(sockfd, buf, strlen(buf));
					continue;
				}
				if (strstr(buf, smsg) != NULL) {
					write(sockfd, buf, strlen(buf));
					continue;
				}
				sprintf(chatData, "[%s] %s", nickname, buf);
				write(sockfd, chatData, strlen(chatData));
			}
		}
	}
}

void exec_chat()
{
	int port;
	char nick[MAXLINE], ip[MAXLINE];

	int sockfd;
	struct linger ling; 
	struct sockaddr_in servaddr;
	int maxfdp1;
	fd_set rset;

	int len;
	char chatData[CH];
	char buf[CH];
	int n;
	char* token = NULL;
	
	port=PORTNUM;
	 
	printf("\n\n>> TYPE YOUR NICKNAME \n");
	scanf("%s", nick);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	ling.l_onoff = 1;
	ling.l_linger = 0;
	setsockopt(sockfd, SOL_SOCKET,SO_LINGER, &ling,sizeof(ling));

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);


	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
		printf("\n\n>> Can not connect\n");
		sleep(2);
		return;
	}

	write(sockfd, nick, strlen(nick)); //send client's nickname
	maxfdp1 = sockfd + 1;

	chatting(sockfd, maxfdp1, rset, nick);

	close(sockfd);
}

