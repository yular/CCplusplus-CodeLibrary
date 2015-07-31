#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h> 
#include <sys/ipc.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
	key_t unique_key;
	int id;
	struct sembuf lock_it;
	union semun options;
	int i;

	//Generate new key
	unique_key = ftok(".",'a');
	
	//Generate a new semaphore set
	id = semget(unique_key, 1, IPC_CREAT | IPC_EXCL | 0666);
	printf("semaphore id=%d\n",id);
	options.val = 1;
	semctl(id, 0, SETVAL, options);

	//Print the value of semaphore
	i = semctl(id, 0, GETVAL, 0);
	printf("Value of semaphore at index 0 is %d\n",i);

	//Reconfigure semaphore
	lock_it.sem_num = 0;
	lock_it.sem_op = -1;
	lock_it.sem_flg = IPC_NOWAIT;
	if(semop(id, &lock_it, 1) == -1){
		printf("can not lock semaphore.\n");
		exit(1);
	}

	i = semctl(id, 0, GETVAL, 0);
	printf("Value of semaphore at index 0 is %d\n",i);

	semctl(id, 0, IPC_RMID, 0);
	return 0;
}

