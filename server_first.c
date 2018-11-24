#include "header.h"

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

}