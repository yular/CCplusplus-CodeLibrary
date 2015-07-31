#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
	int i;
	//pid_t child_pid;
	//child_pid = fork();
	if(fork() == 0){
		for(i = 1; i < 1000; ++ i)
			cout<<"This is child process"<<endl;
	}else{
		for(i = 1; i < 1000; ++ i)
			cout<<"This is main process"<<endl;
	}
	return 0;
}
