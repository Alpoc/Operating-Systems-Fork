#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
using namespace std;
int main(int argc, char** argv){

    int timer;
    timer = strtol(argv[1], NULL, 10);
    
    int pid, ppid;
    int i = 0;
    

    while (i < timer) {
        
        i++;
        cout << "Process: " << getpid() << " " << i <<"\n";
    }
    
    return i;

}
