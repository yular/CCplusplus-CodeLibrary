#include <iostream>
#include <pthread.h>

using namespace std;

const int NUM_THREADS = 5;

void *say_hello(void *args){
	cout<<"hello ... "<<endl;
}

int main(){
	pthread_t tids[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; ++ i){
		int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
		if(ret != 0){
			cout<<"pthread_create error: error_code="<<ret<<endl;
		}
	}
	pthread_exit(NULL);
	return 0;
}
