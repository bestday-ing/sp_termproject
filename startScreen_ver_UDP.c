#include <stdio.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>

int row, col;
int count = 0;

void tty_mode(int);
void main_screen();
void chat_menu(int clickEvent);
void tcp_ip_mode_screen();
void udp_mode_screen();
void multicast();
void broadcast();

int main()	
{
	int c;
 
	tty_mode(0);
	initscr();

//	crmode();
//	noecho();

	main_screen();	

	while(1)
	{
		c = getchar();
		if(c == 'Q'){
			clear();
			break;
		}
		if(c=='1'){ // TCP/IP mode 
			clear();
			tcp_ip_mode_screen();
			c= getchar();
			if(c=='1'){
				clear();
				chat_menu(1);
				tty_mode(1);
				// exec server program
			}
			else if(c=='2'){ 
				clear();
				chat_menu(2);
				tty_mode(1);
				//exec client program
			}
		}
		else if(c=='2'){ // UDP mode
			clear();
			udp_mode_screen();
			c=getchar();
			if(c == '1')
			{
				clear();
				multicast();

				int d;
				d=getchar();
				if(d == '1')
				{
					printf("test");
					//tty_mode(1);
					//char buf[100];
					//strcpy(buf,"./sender");

					execl("./sender","./sender" ,NULL);

				}
				else if(d == '2')
				{
					tty_mode(1);
					//char buf[100];
					//strcpy(buf,"./receiver");
					execl("./receiver","./receiver",NULL);

				}
			}
			else if (c == '2')
			{
				clear();
				broadcast();
			}
		}
		else if(c==27){ //esc key --> back to the main screen
			clear();
			main_screen();
		}
	}

	tty_mode(1);
	return 0;
}

void chat_menu(int clickEvent)
{
	clear();
	if(clickEvent == 1){
		move(1, 2);
		addstr("Copyright.2018.Center Of Computer");
		move(2, 2);	
	}
	if(clickEvent == 2){
		move(1, 2);
		addstr("Copyright.2018.Center Of Computer");
		move(2, 2);
	}
	
	refresh();
}

void main_screen() 
{
	clear();
	
	move(1, 2);
	addstr("*** * W E L C O M E * ***");
	move(2, 2);
	addstr("select your mode");	
	move(3, 2);
	addstr("Note) press key 'Q' : Quit this program");	

	move(5, 2);
	addstr("         1. TCP/IP mode");

	move(7, 2);
	addstr("         2. UDP mode");

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

	move(20,2);
	
	refresh();
}

void tcp_ip_mode_screen()
{
	clear();
	move(1, 2);
	addstr("Copyright.2018.Center Of Computer");	
	//move(3, 2);
	//addstr("Note) press key '' : Quit this program");	

	move(5, 2);
	addstr("         1. create chat room (server)");

	move(7, 2);
	addstr("         2. enter chat room (client)");

	move(20,2);
	
	refresh();
}

void udp_mode_screen()
{
	clear();
	move(1, 2);
	addstr("Copyright.2018.Center Of Computer");	
	//move(3, 2);
	//addstr("Note) press key '' : Quit this program");	

	move(5, 2);
	addstr("         1. multicast");

	move(7, 2);
	addstr("         2. broadcast");

	move(20,2);
	
	refresh();
}

void multicast()
{
	clear();
	move(1, 2);
	addstr("Copyright.2018.Center Of Computer");	
	//move(3, 2);
	//addstr("Note) press key '' : Quit this program");	

	move(5, 2);
	addstr("         1. Server");

	move(7, 2);
	addstr("         2. Client");

	move(20,2);
	
	refresh();


}

void broadcast()
{
	clear();
	move(1, 2);
	addstr("Copyright.2018.Center Of Computer");	
	//move(3, 2);
	//addstr("Note) press key '' : Quit this program");	

	move(5, 2);
	addstr("         1. Server");

	move(7, 2);
	addstr("         2. Client");

	move(20,2);
	
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
