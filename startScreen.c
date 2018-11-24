#include <stdio.h>
#include <curses.h>
#include <termios.h>

//host.c
typedef struct {
	char roomName[100];
	char ip[50];
	int portNum;
	int availNum; //client°¡ Á¢¼Ó½Ã È®ÀÎÇÏ´Â »çÇ×:: ÇöÀç ÀÎ¿ø Á¢¼Ó ¼ö
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
	initscr(); // ÃÊ±âÈ­

//	crmode();
//	noecho();

	main_screen();	// ¸ÞÀÎ È­¸é

/*
<<<<<<< HEAD
	Q ÀÔ·Â ½Ã Á¾·á
	1 ÀÔ·Â ½Ã Ã¤ÆÃ¹æ »ý¼º
	2 ÀÔ·Â ½Ã Ã¤ÆÃ¹æ Á¢¼Ó
	B ÀÔ·Â ½Ã ¸ÞÀÎ È­¸éÀ¸·Î µÇµ¹¾Æ°¡±â
=======
	Q ìž…ë ¥ ì‹œ ì¢…ë£Œ
	1 ìž…ë ¥ ì‹œ ì±„íŒ…ë°© ìƒì„±
	2 ìž…ë ¥ ì‹œ ì±„íŒ…ë°© ì ‘ì†
	B ìž…ë ¥ ì‹œ ë©”ì¸ í™”ë©´ìœ¼ë¡œ ë˜ëŒì•„ê°€ê¸°
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65
*/
	while(1)
	{
		c = getchar();
		if(c == 'Q'){
			clear();
			break;
		}
		if(c=='1'){ // Ã¤ÆÃ¹æ »ý¼º 
			clear();
			create_chat_menu_setting();
                        }
		if(c=='2'){ // Ã¤ÆÃ¹æ Á¢¼Ó
			clear();
			enter_chat_menu_setting();
		}
<<<<<<< HEAD
		if(c=='B'){// ¸ÞÀÎ ¸Þ´º·Î µÇµ¹¾Æ°¡±â
=======
		if(c=='B'){// ë©”ì¸ ë©”ë‰´ë¡œ ë˜ëŒì•„ê°€ê¸°
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65
			clear();
			main_screen();
		}
	}
	
<<<<<<< HEAD
	//original·Î º¹±¸ ! ÄÚµå ¼öÁ¤ ½Ã ÀÌ¸¦ À¯³äÇÏ°í ¾îµð¼­µç Á¾·áÇØµµ original restore ¿°µÎ !! 
=======
	//originalë¡œ ë³µêµ¬ ! ì½”ë“œ ìˆ˜ì • ì‹œ ì´ë¥¼ ìœ ë…í•˜ê³  ì–´ë””ì„œë“  ì¢…ë£Œí•´ë„ original restore ì—¼ë‘ !! 
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65
	tty_mode(1);
	return 0;
}

void main_screen() // ¸ÞÀÎ¸Þ´º
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

	move(20,2); // ¸Þ¼¼Áö Àü¼Û¹ÞÀ» °ø°£
	
	refresh();
}

void enter_chat_menu_setting() // Ã¤ÆÃ ÀÔÀå ¸Þ´º
{
	clear();
	//list º¸¿©ÁÖ°í ¹æ ¹øÈ£ ÀÔ·ÂÇÒ ¼ö ÀÖ´Â °ø°£À» ¸¸µé¾î¾ß ÇÔ.
	move(1, 2);
        addstr("--- Create Chatting Room ---");
	move(3, 2);
	addstr("Note) press key 'Q' : Quit this program, 'B' : back to the main menu");	

        move(20,2);// ¸Þ¼¼Áö Àü¼Û¹ÞÀ» °ø°£

	refresh();
}

void create_chat_menu_setting() // Ã¤ÆÃ »ý¼º ¸Þ´º
{
	clear();
<<<<<<< HEAD
	//Ã¤ÆÃ¹æ ÀÌ¸§, max ÀÎ¿ø¼ö ÀÔ·Â  ¹Þ¾Æ¿À±â
=======
	//ì±„íŒ…ë°© ì´ë¦„, max ì¸ì›ìˆ˜ ìž…ë ¥  ë°›ì•„ì˜¤ê¸°
>>>>>>> 54c292493da7df1cb530bc301f1d60826448dd65
	move(1, 2);
	addstr("--- Create Chatting Room ---");
	move(3, 2);
	addstr("Note) press key 'Q' : Quit this program, 'B' : back to the main menu");	

<<<<<<< HEAD
	move(20,2);// ¸Þ¼¼Áö Àü¼Û¹ÞÀ» °ø°£
=======
	move(20,2);// ë©”ì„¸ì§€ ì „ì†¡ë°›ì„ ê³µê°„
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
