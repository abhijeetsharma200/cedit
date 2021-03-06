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
	tcgetattr(STDIN_FILENO, &orig_termios); // gets terminal attributes and puts in orig_termios
	
	struct termios raw = orig_termios;

	raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
	
	raw.c_oflag &= ~(OPOST);	
	
	raw.c_cflag |= 	~(CS8);
	
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	
	raw.c_cc[VMIN] = 0;

	raw.c_cc[VTIME] = 1;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	
	atexit(disableRawMode); // at exit returns the terminal to the original state
}

int main(){
	enableRawMode();
	
	//char c;
	
	//while (read(STDIN_FILENO, &c, 1) ==1 && c != 'q'){
	//	// reads 1 byte from standard input into c till q is entered
	//	if(iscntrl(c)){
	//		printf("%d\r\n", c);

	//	}else {
	//	printf("%d ('%c')\r\n", c, c);
	//	} 
	//}
	while (1){
		char c = '\0';
		read(STDIN_FILENO, &c, 1);
		if (iscntrl(c)){
			printf("%d\r\n", c);
		} else {
		printf("%d ('%c')\r\n", c, c);
		}
	if (c=='q') break;
	}
	
	return 0;
}
