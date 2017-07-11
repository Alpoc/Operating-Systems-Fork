#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;
int main(int argc, char** argv){

    int pid, ppid;
    int i = 0;
    int wstatus;
    
    pid = fork();
    
    if ( pid < 0 ) {
        
        cout << "pid error \n";
        exit(1);
    }
    
    if ( pid == 0 ) {
   	cout << "Child PID: " << getpid() << "\n";
	int status;
        status = execl("./count", "count", "5", NULL);
	cout << "Process " << getpid() << " exited with status: " << status << "\n";
        
    }

    else {
	cout << "Parent PID: " << getpid() << "\n";
	do { 
		int status = waitpid(pid, &wstatus, 0);
		if (status == -1) {
			perror("wait pid failed");
			
		}
	
	} while( !WIFEXITED(wstatus));

	cout << "Process " << pid << " exited with status: " << WEXITSTATUS(wstatus) << endl;
	}

}
