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

	raw.c_iflag &= ~(IXON | ICRNL);
	
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	
	atexit(disableRawMode); // at exit returns the terminal to the original state
}

int main(){
	enableRawMode();
	
	char c;
	while (read(STDIN_FILENO, &c, 1) ==1 && c != 'q'){
		// reads 1 byte from standard input into c till q is entered
		if(iscntrl(c)){
			printf("%d\n", c);

		}else {
		printf("%d ('%c')\n", c, c);
		} 
	}
	return 0;
}
