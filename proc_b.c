/* A C program that does not terminate when Ctrl+C is pressed */
/*#include <stdio.h> 
#include <signal.h>*/
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>  

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num) 
{ 
	signal(SIGINT, sigintHandler); 
	printf("\n SIGINT is handled and the process will not be terminated \n"); 
} 

/* Signal Handler for SIGTERM */
void sigtermHandler(int sig_num) 
{ 
	signal(SIGTERM, sigintHandler); 
	printf("\n SIGTERM is handled and the process will not be terminated \n"); 
} 

int main () 
{ 
	int i=0;
	signal(SIGINT, sigintHandler); //sets a function to handle SIGINT signal
	signal(SIGTERM, sigtermHandler); //sets a function to handle SIGTERM signal
	/* Infinite loop */
	while(1) {
		sleep(2);
		printf("%d\n", ++i);
	} 
	return 0; 
} 
