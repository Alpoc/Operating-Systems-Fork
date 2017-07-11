#include <iostream>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main(int argc, char** argv){


    int pid, ppid;
    int i = 0;
       
    cout << "Child PID: " << getpid() << "\n";
    cout << "Parent PID: " << getppid() << "\n";
    
    pid = fork();
    
    if ( pid < 0 ) {
        
        cout << "pid error \n";
        exit(1);
    }
    
    if ( pid == 0 ) {
   
        system("./count 5");
        
    }

}
