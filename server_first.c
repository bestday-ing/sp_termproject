#include "header.h"

struct List_c {
	int socket_num;
	char nick[CH]; 
	char ip[40];
	int port;
}list_c[100]; // �������� ������ ����ü�� ����, ��������, ip, port ���


/*************************************/
int pushClient(int, char*, char*, int);
int popClient(int);
void constr_func(int, int); // ���ο� Ŭ���̾�Ʈ ����� ���� �Ѹ�
void quit_func(int);
void list_func(int);
int smsg_func(char*, int);  // �ӼӸ�
void make_client(char*, int, char*); // ���Ͽ���
/*************************************/
int creating_room(int, int); // �ٽ� �Լ�
void chatting(int , int , fd_set , char *);  // ä�� ���� ���� �ְ�޴�
/*************************************/
char *replaceValue(char *strInput, const char *strTarget, const char *strChange);

int main(){

}