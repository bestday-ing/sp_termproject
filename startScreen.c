#include <stdio.h>
#include <curses.h>
#include <termios.h>

//host.c
typedef struct {
	char roomName[100];
	char ip[50];
	int portNum;
	int availNum; //client가 접속시 확인하는 사항:: 현재 인원 접속 수
	int maxNum; 
}Host;

Host hostList[50];

int row, col;
int count = 0;

void tty_mode(int);
void main_screen();
void enter_chat_menu_setting();
void create_chat_menu_setting();

int main()	
{
	int c;
 
	tty_mode(0);
	initscr(); // 초기화

//	crmode();
//	noecho();

	main_screen();	// 메인 화면

/*
<<<<<<< HEAD
	Q 입력 시 종료
	1 입력 시 채팅방 생성
	2 입력 시 채팅방 접속
	B 입력 시 메인 화면으로 되돌아가기
=======
	Q �엯�젰 �떆 醫낅즺
	1 �엯�젰 �떆 梨꾪똿諛� �깮�꽦
	2 �엯�젰 �떆 梨꾪똿諛� �젒�냽
	B �엯�젰 �떆 硫붿씤 �솕硫댁쑝濡� �릺�룎�븘媛�湲�
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65
*/
	while(1)
	{
		c = getchar();
		if(c == 'Q'){
			clear();
			break;
		}
		if(c=='1'){ // 채팅방 생성 
			clear();
			create_chat_menu_setting();
                        }
		if(c=='2'){ // 채팅방 접속
			clear();
			enter_chat_menu_setting();
		}
<<<<<<< HEAD
		if(c=='B'){// 메인 메뉴로 되돌아가기
=======
		if(c=='B'){// 硫붿씤 硫붾돱濡� �릺�룎�븘媛�湲�
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65
			clear();
			main_screen();
		}
	}
	
<<<<<<< HEAD
	//original로 복구 ! 코드 수정 시 이를 유념하고 어디서든 종료해도 original restore 염두 !! 
=======
	//original濡� 蹂듦뎄 ! 肄붾뱶 �닔�젙 �떆 �씠瑜� �쑀�뀗�븯怨� �뼱�뵒�꽌�뱺 醫낅즺�빐�룄 original restore �뿼�몢 !! 
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65
	tty_mode(1);
	return 0;
}

void main_screen() // 메인메뉴
{
	clear();
	
	move(1, 2);
	addstr("*** * W E L C O M E * ***");
	move(2, 2);
	addstr("press key '1' : Create Chat, '2' : Enter Chat");	
	move(3, 2);
	addstr("Note) press key 'Q' : Quit this program");	

	move(5, 2);
	addstr("         1. Create Chat");

	move(7, 2);
	addstr("         2. Enter Chat");

	move(13, 25);
	addstr("          PM: CENTER OF COMPUTER          ");
	
	move(14, 25);
	addstr("- Leader, Scheduler: SongGi-Hong");
	move(15, 25);
	addstr("- Git Maintainer, Developer: YuBin-Jung");
	move(16, 25);
	addstr("- Project Designer and Analysist : TaeWon-Nam");
	move(17, 25);
	addstr("- Development Leader : AYeong-Yun");
	move(18, 25);
	addstr("");

	move(20,2); // 메세지 전송받을 공간
	
	refresh();
}

void enter_chat_menu_setting() // 채팅 입장 메뉴
{
	clear();
	//list 보여주고 방 번호 입력할 수 있는 공간을 만들어야 함.
	move(1, 2);
        addstr("--- Create Chatting Room ---");
	move(3, 2);
	addstr("Note) press key 'Q' : Quit this program, 'B' : back to the main menu");	

        move(20,2);// 메세지 전송받을 공간

	refresh();
}

void create_chat_menu_setting() // 채팅 생성 메뉴
{
	clear();
<<<<<<< HEAD
	//채팅방 이름, max 인원수 입력  받아오기
=======
	//梨꾪똿諛� �씠由�, max �씤�썝�닔 �엯�젰  諛쏆븘�삤湲�
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65
	move(1, 2);
	addstr("--- Create Chatting Room ---");
	move(3, 2);
	addstr("Note) press key 'Q' : Quit this program, 'B' : back to the main menu");	

<<<<<<< HEAD
	move(20,2);// 메세지 전송받을 공간
=======
	move(20,2);// 硫붿꽭吏� �쟾�넚諛쏆쓣 怨듦컙
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65

	refresh();
}
void tty_mode(int how)
{
	static struct termios original_mode;
	if(how == 0)
		tcgetattr(0, &original_mode);
	else
		tcsetattr(0, TCSANOW, &original_mode);
}
