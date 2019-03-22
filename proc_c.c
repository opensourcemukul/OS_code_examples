// C program to implement sighup(), sigint() 
// and sigquit() signal functions 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 

// function declaration 
void sighup(); 
void sigint(); 
void sigquit(); 

// driver code 
void main() 
{ 
	int pid; 
	printf("\n(%d)PARENT: Sleeping now, will create the child process after i wake up.\n\n",getpid()); 
	sleep(10);
	printf("\nPARENT: woke up!\n"); 
	printf("\nPARENT: creating child process\n"); 
	/* get child process */
	if ((pid = fork()) < 0) { 
		perror("fork"); 
		exit(1); 
	} 

	if (pid == 0) { /* child */
		printf("\n(%d)CHILD: Hello.\n",getpid()); 
		signal(SIGHUP, sighup); 
		signal(SIGINT, sigint); 
		signal(SIGQUIT, sigquit); 
		for (;;) 
			; /* loop for ever */
	} 

	else /* parent */
	{ /* pid hold id of child */
		printf("\n(%d)PARENT: going to sleep..\n",getpid()); 
		sleep(10); /* pause for 10 secs */
		printf("\n(%d)PARENT: woke up!\n",getpid()); 
		printf("\n(%d)PARENT: sending SIGHUP\n\n",getpid()); 
		kill(pid, SIGHUP); 

		printf("\n(%d)PARENT: going to sleep..\n",getpid()); 
		sleep(10); /* pause for 10 secs */
		printf("\n(%d)PARENT: woke up!\n",getpid());
		printf("\n(%d)PARENT: sending SIGINT\n\n",getpid()); 
		kill(pid, SIGINT); 

		printf("\n(%d)PARENT: going to sleep..\n",getpid()); 
		sleep(10); /* pause for 10 secs */
		printf("\n(%d)PARENT: woke up!\n",getpid());
		printf("\n(%d)PARENT: sending SIGQUIT\n\n",getpid()); 
		kill(pid, SIGQUIT); 
		sleep(10); 
	} 
} 

// sighup() function definition 
void sighup() 
{ 
	signal(SIGHUP, sighup); /* reset signal */
	printf("(%d)CHILD: I have received a SIGHUP\n",getpid()); 
} 

// sigint() function definition 
void sigint() 
{ 
	signal(SIGINT, sigint); /* reset signal */
	printf("(%d)CHILD: I have received a SIGINT\n",getpid()); 
} 

// sigquit() function definition 
void sigquit() 
{ 
	printf("(%d)CHILD: My DADDY has Killed me!!! I will be a Zombie unless my parent is terminated.\n",getpid()); 
	exit(0); 
} 
