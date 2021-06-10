#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios; 

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(){

	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	struct termios raw = orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN  | ISIG);
	raw.c_cc[VMIN] = 3;
	raw.c_cc[VTIME] = 100;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
int main(){
	enableRawMode();

	while(1){
	char *c = "";
	read(STDIN_FILENO, &c, 3); 
		if(iscntrl(c[0])){
			printf("%d\r\n", c[0]);
		}else{
			printf("%d ('%s')\r\n", c[0], c);
		}
	if (c[0] == 'q') break;
	}
	return 0;
}
