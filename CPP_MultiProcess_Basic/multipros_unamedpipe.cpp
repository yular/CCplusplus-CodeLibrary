#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define INPUT 0
#define OUTPUT 1

int main(){
	int file_descriptors[2];
	pid_t pid;
	char buf[256];
	int returned_cnt;

	memset(buf, 0, sizeof(buf));

	pipe(file_descriptors); // Unnamed pipe

	if((pid = fork()) == -1){
		cout<<"Error in fork"<<endl;
		exit(1);
	}

	if(pid == 0){
		cout<<"in the spawned (child) process..."<<endl;
		close(file_descriptors[INPUT]);
		write(file_descriptors[OUTPUT], "test data", strlen("test data"));
		exit(0);
	}else{
		cout<<"in the spawning (parent) process..."<<endl;
                returned_cnt = read(file_descriptors[INPUT], buf, sizeof(buf));
		cout<<returned_cnt<<" bytes of data received from spawned process: "<<buf<<endl;
	}

        return 0;
}

