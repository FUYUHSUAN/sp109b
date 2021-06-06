#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

void die(const char *s) {
	  write(STDOUT_FILENO, "\x1b[2J", 4);
	    write(STDOUT_FILENO, "\x1b[H", 3);
	      perror(s);
	        exit(1);
}
void editorOpen(char *filename) {
	  FILE *fp = fopen(filename, "r");
	    if (!fp) die("fopen");
	      char *line = NULL;
	        size_t linecap = 0;
		  ssize_t linelen;
		    linelen = getline(&line, &linecap, fp);
		      if (linelen != -1) 
		      {
			          while (linelen > 0 && (line[linelen - 1] == '\n' ||
							                             line[linelen - 1] == '\r'))
					        linelen--;
    printf("%s",line);						       
		      }
		        free(line);
			  fclose(fp);
}
int main(int argc, char *argv[]) {
	      if (argc >= 2) {
		          editorOpen(argv[1]);
			    }
	    
		  return 0;
}
