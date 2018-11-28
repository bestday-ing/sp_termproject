#include "header.h"

#define WAITING "Waiting user"
#define MAXLINE 100
#define CH 1024
#define INVALID_SOCK -1
#define PORTNUM 30000


int MAX_CLIENT =  100;
int usr_max_client = 0;
char greeting[] = "\n>> Welcome to chatting room ( /quit : exit, /list : user list, /smsg : whisper)\n";
char ERROR[] = "\n>> Sorry, the room is full! ( /quit : exit )\n";
char SERVER_QUIT[] = "\n>> There is no server owner. Please input \"/quit\"\n";

char quit[] = "/quit\n";
char list[] = "/list\n";
char smsg[] = "/smsg";

char fuck[]="fuck";
char ssibal[]="ssibal";


struct List_c {
	int socket_num;
	char nick[CH]; 
	char ip[40];
	int port;
}list_c[100]; // 소켓으로 보내는 구조체로 별명, 소켓정보, ip, port 기록

/*************************************/
int pushClient(int, char*, char*, int);
int popClient(int);
void constr_func(int, int); // 새로운 클라이언트 입장시 정보 뿌림
void quit_func(int);
void list_func(int);
int smsg_func(char*, int);  // 귓속말
void make_client(char*, int, char*); // 소켓연결
/*************************************/
int creating_room(int, int); // 핵심 함수
void chatting(int , int , fd_set , char *);  // 채팅 내용 전달 주고받는
/*************************************/
char *replaceValue(char *strInput, const char *strTarget, const char *strChange);


int main(){

	int port,ppl;

	port=PORTNUM;
 	printf("\n\n>> TYPE MAX PEOPLE ALLOWED IN YOUR ROOM : \n");

	if(scanf("%d", &ppl) != 1){
		printf("\n\n>> Wrong input\n");
		sleep(2);
		return;
	}

	creating_room(port, ppl);
 return 0;
}

int pushClient(int connfd, char* c_nick, char* c_ip, int c_port) {
	int i;

	for (i = 0; i<usr_max_client; i++) {
		if (list_c[i].socket_num == INVALID_SOCK) {
			list_c[i].socket_num = connfd;
			strcpy(list_c[i].nick, c_nick);
			strcpy(list_c[i].ip, c_ip);
			list_c[i].port = c_port;
			return i;
		}
	}

	if (i == MAX_CLIENT)
		return -1;
	/* 새로운 클라이언트 등장시, 리스트내에 클라이언트 정보기록할 필요 있음
	정해놓은 최대 클라이언트 number에 맞춰 for 문을 돌려 만약 비어있을시 거기에 클라이언트 정보 넣음
  	*/
}

int popClient(int s)
{
	int i;

	for (i = 0; i<usr_max_client; i++) {
		if (s == list_c[i].socket_num) {
			list_c[i].socket_num = INVALID_SOCK;
			memset(list_c[i].nick, 0, sizeof(list_c[i].nick));
			memset(list_c[i].ip, 0, sizeof(list_c[i].ip));
			break;
		}
	}
	close(s);
	return 0;
}

void constr_func(int i, int index) {
	char buf1[MAXLINE];

	memset(buf1, 0, sizeof(buf1));
	sprintf(buf1, "     [%s is connected]\r\n", list_c[index].nick);
	write(list_c[i].socket_num, buf1, strlen(buf1));
	// index 클라이언트가 입장햇다는 정보를 다른 클라이언트들에게 모두 뿌리고 있음

	sprintf(buf1, "     [%s is connected]\r\n", list_c[i].nick);
	write(list_c[index].socket_num, buf1, strlen(buf1));
	/* 새로 입장한 index 클라이언트 에게 지금 접속 되어있는 
		클라이언트에 대한 모든 정보를 전달해주고 있다. */ 
}

void quit_func(int i) {
	int j;
	char* token = NULL;
	char buf1[MAXLINE];

	memset(buf1, 0, sizeof(buf1));
	for (j = 0; j<MAX_CLIENT; j++)
		if (j != i && list_c[j].socket_num != INVALID_SOCK) {
			sprintf(buf1, "    >> %s has left the %s\r\n", list_c[i].nick, list_c[i].ip);
			write(list_c[j].socket_num, buf1, strlen(buf1));
		}

	popClient(list_c[i].socket_num);
}

void list_func(int i) {
	int j, cnt = 0;
	char buf1[MAXLINE];

	memset(buf1, 0, sizeof(buf1));
	for (j = 0; j<MAX_CLIENT; j++)
		if (list_c[j].socket_num != INVALID_SOCK) cnt++;
	sprintf(buf1, "    >>the number of current user is %d\r\n", cnt);
	write(list_c[i].socket_num, buf1, strlen(buf1));
	for (j = 0; j<MAX_CLIENT; j++)
		if (list_c[j].socket_num != INVALID_SOCK) {
			sprintf(buf1, "     [%s from %s:%d]\r\n", list_c[j].nick, list_c[j].ip, list_c[j].port);
			write(list_c[i].socket_num, buf1, strlen(buf1));
		}
}

int smsg_func(char* chatData, int i) { //  "/smsg"+"nickname"+"말할내용" 으로 입력형식 갖춤
	int j, smsg_sock;
	char* token = NULL;
	char buf1[MAXLINE];

	memset(buf1, 0, sizeof(buf1));
	token = strtok(chatData, " ");
	char * end;

	if(strcmp(token, smsg)==0){ //smsg="/smsg"라고 넣어둠
		token = strtok(NULL, " ");
		for (j = 0; j<MAX_CLIENT; j++)
			if (!strcmp(list_c[j].nick, token))
				smsg_sock = list_c[j].socket_num;
		token = strtok(NULL, "\n");
		memset(buf1, 0, sizeof(buf1));
		sprintf(buf1, "[smsg from %s] %s\r\n", list_c[i].nick, token);
		write(smsg_sock, buf1, strlen(buf1));
		return 0;
	}

	else{
		if ((end = strtok(NULL, "\n")) == NULL) 
			sprintf(buf1, "%s", token);
		else sprintf(buf1, "%s %s", token, end);
		sprintf(chatData, "[%s] %s\n", list_c[i].nick, buf1);
		return 1;

		/* 예로 지금 hello my name is yun이라고 입력되어 있다
		" "으로 token을 잘라 hello가 token에 들어가 있음.
		end에는 이제 문장 끝까지 들어가 있는 상태
		만약 end가 null이라면 토큰만 보내면 되겟지만 계속 연결된 내용이 있음으로
		token과 end 모두를 버퍼에 입력해준다.
		*/
	}	
}

int creating_room(int port,  int ppl)
{
	struct linger ling; // TIME_WAIT
	int connfd, listenfd;
	struct sockaddr_in servaddr, cliaddr;
	int clilen;
	int maxfd = 0;  
	int i, j, n;
	fd_set rset;

	int pid;
	int index;

	char* token = NULL;
	char buf1[MAXLINE];
	char buf2[MAXLINE];
	char chatData[CH];
	char nick[MAXLINE];
  char *temp;

	int quit_check = -1;

	MAX_CLIENT = ppl;
	usr_max_client = MAX_CLIENT;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	ling.l_onoff = 1;
	ling.l_linger = 0;
	setsockopt(listenfd, SOL_SOCKET,SO_LINGER, &ling,sizeof(ling));

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);

	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
		printf("\n\n>> Error : that port is already being used\n");
		sleep(2);
		return -1;
	}
	if (listen(listenfd, MAX_CLIENT) == -1) {
		printf("\n\n>> Room is full\n");
		sleep(2);
		return -1;
	}

	for (i = 0; i<MAX_CLIENT; i++)
		list_c[i].socket_num = INVALID_SOCK;

	memset(buf1, 0, sizeof(buf1));
	inet_ntop(AF_INET, &servaddr.sin_addr, buf1, sizeof(buf1));
	
	printf("\n\n>> Server Domain\n");
	printf("     - Room max = %d\n", usr_max_client);
	printf("     - [server address is %s : %d]\n", buf1, ntohs(servaddr.sin_port));

	pid = fork();
	if( pid == -1)
	        perror("fork");
	else if(pid == 0){
        	//exec_client(buf1,port,nick);
	//	exit(0);
	}
	else{
        	printf("   - Warning : if you close the room, other users can't chat anymore\n");

		for (; ; )
		{
		
			maxfd = listenfd;

			FD_ZERO(&rset);
			FD_SET(listenfd, &rset);
			for (i = 0; i<MAX_CLIENT; i++) {
				if (list_c[i].socket_num != INVALID_SOCK) {	
					FD_SET(list_c[i].socket_num, &rset);
					if (list_c[i].socket_num > maxfd) maxfd = list_c[i].socket_num;
				}
			}
			maxfd++;

			// close(listenfd)
			if (select(maxfd, &rset, (fd_set *)0, (fd_set *)0, (struct timeval *)0) < 0) {
				printf("\n\n>> The server shuts down.\n");
				sleep(2);
				return 1;
			}

			if (FD_ISSET(listenfd, &rset)) { 
				clilen = sizeof(cliaddr);
				if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) > 0) {
					memset(buf1, 0, sizeof(buf1));
					memset(buf2, 0, sizeof(buf2));
					read(connfd, buf1, sizeof(buf1));//read client's nickname
					inet_ntop(AF_INET, &cliaddr.sin_addr, buf2, sizeof(buf2));
					index = pushClient(connfd, buf1, buf2, ntohs(cliaddr.sin_port));//push socknum,nick,ip,port_num of client
		        if(index!=-1)
		            printf("  (server) %s is connected from %s\r\n", list_c[index].nick, list_c[index].ip);
		        else
		            printf("  (server) due to the room full, connection rejected\n");

					if (index<0) {
						write(connfd, ERROR, strlen(ERROR));
						close(connfd);
					}
					else {
						write(connfd, greeting, strlen(greeting));
						for (i = 0; i<MAX_CLIENT; i++)
							if (i != index && list_c[i].socket_num != INVALID_SOCK) {
								constr_func(i, index);
						}
					}
				}
			}

			for (i = 0; i<MAX_CLIENT; i++) {
				if ((list_c[i].socket_num != INVALID_SOCK) && FD_ISSET(list_c[i].socket_num, &rset)) {
					memset(chatData, 0, sizeof(chatData));
					if ((n = read(list_c[i].socket_num, chatData, sizeof(chatData)))>0) {
						if (!strcmp(chatData, quit)) {//disconnect from the client "i"
							quit_func(i);
							continue;
						}
						if (!strcmp(chatData, list)) {//print the list of clients
							list_func(i);
							continue;
						}
						if (strstr(chatData, smsg) != NULL) {
							if (smsg_func(chatData, i) == 0) continue;
							else;
						}
              
            if (strstr(chatData,fuck)){
             strcpy(chatData,replaceValue(chatData,fuck,"xxxx") ); 
            }
            
            if (strstr(chatData, ssibal)){
            strcpy(chatData,replaceValue(chatData,ssibal,"xxxxxx") );  
            }
              
						for (j = 0; j<MAX_CLIENT; j++) {//send chatting letters
							if (list_c[i].socket_num != INVALID_SOCK)
								if (j != i)
									write(list_c[j].socket_num, chatData, sizeof(chatData));
						}
					}
				}
			}

	quit_check = -1;
	for (i = 0; i < MAX_CLIENT; i++)
	{
		if (list_c[i].socket_num != INVALID_SOCK)
			quit_check = 1;
	}

	if (quit_check == -1) {
		//	if(list_c[0].socket_num == INVALID_SOCK){ // server가 종료 될때
				for (i = 0; i<MAX_CLIENT; i++) {// 
					if (list_c[i].socket_num != INVALID_SOCK)
							write(list_c[i].socket_num, SERVER_QUIT, sizeof(SERVER_QUIT));
				}
				close(listenfd);
			}
		}
	}
}

char *replaceValue(char *strInput, const char *strTarget, const char *strChange)
{
    char* strResult;
    char* strTemp;
    int i = 0;
    int nCount = 0;
    int nTargetLength = strlen(strTarget);
 
    if (nTargetLength < 1)
        return strInput;
 
    int nChangeLength = strlen(strChange);
 
    if (nChangeLength != nTargetLength)
    {
        for (i = 0; strInput[i] != '\0';)
        {
            if (memcmp(&strInput[i], strTarget, nTargetLength) == 0)
            {
                nCount++;
                i += nTargetLength;
            }
            else i++;
        }
    }
    else
    {
        i = strlen(strInput);
    }
 
    strResult = (char *) malloc(i + 1 + nCount * (nChangeLength - nTargetLength));
    if (strResult == NULL) return NULL;
 
 
    strTemp = strResult;
    while (*strInput)
    {
        if (memcmp(strInput, strTarget, nTargetLength) == 0)
        {
            memcpy(strTemp, strChange, nChangeLength);
            strTemp += nChangeLength;
            strInput  += nTargetLength;
        }
        else
        {
            *strTemp++ = *strInput++;
        }
    }
 
    *strTemp = '\0';
 
    return strResult;
}
