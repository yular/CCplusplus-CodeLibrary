#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

const int LEN = 256;
const int ERRORNO = 1;

char command[LEN];

int main(){
	int rtn_val = 3;
	while(1){
		cout<<">";
		fgets(command, LEN, stdin);
		command[strlen(command) - 1] = 0;
		if(fork() == 0){
			execlp(command, command);
			perror(command);
			exit(ERRORNO);
		}else{
			rtn_val = 3;
			wait(&rtn_val);
			printf("Child Process return %d\n",(int)rtn_val);
		}
	}
	return 0;
}

