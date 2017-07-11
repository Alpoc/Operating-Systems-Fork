//Dalton Wiebold
//This program forks then from the child process kills 5 signals to the parent.
//Collaborated with Saad, Roach, Eli, Ethan.
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <iostream>
#include <cassert>
#include <sys/wait.h>

using namespace std;

void handler(int);

int main(void) {

	int send_signal (int pid);
	int pid, ppid;
	int wstatus;
	int signum;

	struct sigaction *action = new (struct sigaction);
	action -> sa_handler = handler;
	sigemptyset (&(action -> sa_mask));
	assert (sigaction (SIGSEGV, action, NULL) == 0);	

	struct sigaction *action_hup = new (struct sigaction);
	action_hup -> sa_handler = handler;
	sigemptyset (&(action_hup -> sa_mask));
	assert (sigaction (SIGHUP, action_hup, NULL) == 0);

	struct sigaction *action_usr1 = new (struct sigaction);
	action_usr1 -> sa_handler = handler;
	sigemptyset (&(action_usr1 -> sa_mask));
	assert (sigaction (SIGUSR1, action_usr1, NULL) == 0);


	if(sigaction(SIGSEGV, action, NULL) < 0) {
		perror("SIGHUP ERRO");
		delete[] action;
		exit(EXIT_FAILURE);
	}

	if(sigaction(SIGHUP, action_hup, NULL) < 0) {
		perror("SIGHUP ERRO");
		delete[] action_hup;
		exit(1);
	}

	if(sigaction(SIGUSR1, action_usr1, NULL) < 0) {
		perror("SIGHUP ERRO");
		delete[] action_usr1;
		exit(1);
	}	

	pid = fork();

	if ( pid < 0 ) {
        	perror("fork failed \n");
        	exit(1);
	}

	else if ( pid == 0 ) {
		kill(getpid(), SIGHUP);
		kill(getpid(), SIGUSR1); //signal 10
		kill(getpid(), SIGUSR1);
		kill(getpid(), SIGUSR1);
		kill(getpid(), SIGSEGV); //signal 11
    	}
	
	else {
		do {
                	int status = waitpid(pid, &wstatus, 0);
                	if (status == -1) {
	                        perror("wait pid failed");
			}
		} while( !WIFEXITED(wstatus) );

		
		delete[] action;
		delete[] action_hup;
		delete[] action_usr1;
		exit(EXIT_SUCCESS);
        }
}

void handler(int signl) {

	switch (signl) {
        	case SIGHUP:
			signal(SIGHUP, handler);
			cout << "Recieved: SIGHUP" << "\n";
            		break;
        	case SIGUSR1:
			signal(SIGUSR1, handler);
			cout << "Recieved: SIGUSR1" << "\n";
            		break;
        	case SIGINT:
			signal(SIGINT, handler);
			cout << "Recieved: SIGINT" << "\n";
            		exit(0);
		case SIGSEGV:
			signal(SIGSEGV, handler);	
			cout << "Recieved: SIGSEGV" << "\n";
	}
}
