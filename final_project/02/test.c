#include <unistd.h>
#include<stdio.h>
int main() {
	  char c;
	    while (read(STDIN_FILENO, &c, 1) == 1 ){
		    if(c=='q')break;
		    if(c=='w')printf("success write");
	    }
	      return 0;
	
}
