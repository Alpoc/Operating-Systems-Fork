//Dalton Wiebold
//This program forks then from the child process kills 5 signals to the parent.
//Collaborated with Saad, Roach, Ethan.
//write() should be used instead of cout becuase its async safe, for this class
//  it does not matter.
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <iostream>
#include <cassert>
#include <sys/wait.h>
#include <string.h>

using namespace std;

void handler(int);

int main(void) {

	int send_signal (int pid);
	int pid;
	int wstatus;

	struct sigaction *action = new (struct sigaction);
	//Next line and similar is to handle uninitialized bits.
	//Sets those bits to 0 before using in the struct.
	action -> sa_flags = SA_RESTART;
	action -> sa_handler = handler;
	sigemptyset (&(action -> sa_mask)); //I will not ignore any signals
	assert (sigaction (SIGSEGV, action, NULL) == 0);


	struct sigaction *action_hup = new (struct sigaction);
	action_hup -> sa_flags = SA_RESTART;
	action_hup -> sa_handler = handler;
	sigemptyset (&(action_hup -> sa_mask));
	assert (sigaction (SIGHUP, action_hup, NULL) == 0);


	struct sigaction *action_usr1 = new (struct sigaction);
	action_usr1 -> sa_flags = SA_RESTART;
	action_usr1 -> sa_handler = handler;
	sigemptyset (&(action_usr1 -> sa_mask));
	assert (sigaction (SIGUSR1, action_usr1, NULL) == 0);



	if(sigaction(SIGSEGV, action, NULL) < 0) {
		perror("SIGHUP ERROR \n");
		delete action;
		exit(EXIT_FAILURE);
	}

	if(sigaction(SIGHUP, action_hup, NULL) < 0) {
		perror("SIGHUP ERROR \n");
		delete action_hup;
		exit(1);
	}

	if(sigaction(SIGUSR1, action_usr1, NULL) < 0) {
		perror("SIGHUP ERROR \n");
		delete action_usr1;
		exit(1);
	}

	pid = fork();

	if ( pid < 0 ) {
        	perror("fork failed \n");
        	exit(1);
	}

	else if ( pid == 0 ) {
		kill(getppid(), SIGHUP);
		kill(getppid(), SIGUSR1); //signal 10
		kill(getppid(), SIGUSR1);
		kill(getppid(), SIGUSR1);
		kill(getppid(), SIGSEGV); //signal 11


		delete action;
		delete action_hup;
		delete action_usr1;
    	}

	else {
		do {
                	int status = waitpid(pid, &wstatus, 0);
                	if (status == -1) {
	                        perror("wait pid failed \n");
			}
		} while( !WIFEXITED(wstatus) );


		delete action;
		delete action_hup;
		delete action_usr1;
		exit(EXIT_SUCCESS);
        }
}

void handler(int signl) {
		//char const *variable is the current way to store the strng and use in write
    char const *c;

	switch (signl) {
        	case SIGHUP:
			c = "Signal received from child: SIGHUP\n";
                	write (1, c, strlen(c));
            		break;

        	case SIGUSR1:
        		c = "Signal received from child: SIGUSR1\n";
                	write (1, c, strlen(c));
            		break;

        	case SIGINT:
			c = "Signal received from child: SIGINT\n";
                	write (1, c, strlen(c));
            		//exit(0);

		    case SIGSEGV:
			c = "Signal received from child: SIGSEGV\n";
                	write (1, c, strlen(c));
	}

}
