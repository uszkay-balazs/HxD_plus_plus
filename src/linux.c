#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>


#define	ERROR 	"[\x1b[31mERROR\x1b[m]   "			/* 'ERROR' in red */
#define	WARNING "[\x1b[38;5;208mWARNING\x1b[m] "	/* 'WARNING' in orange */
#define	INFO 	"[\x1b[34mINFO\x1b[m]    "			/* 'INFO' in blue */
#define	SUCCESS	"[\x1b[32mSUCCESS\x1b[m] "			/* 'SUCCESS' in green */


struct termios saved_attr;
void reset_terminal_mode(void){
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_attr);
	return;
}

void set_terminal_mode(void) {
	if (!isatty(STDIN_FILENO)) {
		printf(ERROR"Not terminal");
		exit(1);
	}
	tcgetattr(STDIN_FILENO, &saved_attr);
	atexit(reset_terminal_mode);	

	struct termios attr;
	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~(ICANON|ECHO); // clear canonical mode and echo
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
	return;
}

size_t get_file_size(FILE* fp) {
	size_t loc = ftell(fp);
	fseek(fp, SEEK_END, 0);
	size_t res = ftell(fp);
	fseek(fp, SEEK_SET, loc);
	return res;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf( ERROR"Not enough arguments provided.\n" );
		return 1;
	} else if (argc > 2) {
		printf( WARNING"Only the first argument is processed\n" );
	}
	set_terminal_mode();
	FILE* fp;
	fp = fopen(argv[1], "r+b");
	size_t fsize = get_file_size(fp);

	char* buffer = (char*) malloc(fsize + 1);
	if (fread(buffer, sizeof(char), fsize, fp) != fsize) {
		printf(ERROR"Could not read file '%s'\n", argv[1]);
		return 1;
	}
	
	fclose(fp);
	return 0;
}

