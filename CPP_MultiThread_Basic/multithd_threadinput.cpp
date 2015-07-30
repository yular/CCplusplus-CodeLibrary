#include <iostream>
#include <pthread.h>

using namespace std;

const int NUM_THREADS = 5;

void *say_hello(void *args){
	int res = *((int *)args);
        cout<<"Hello in "<<res<<endl;
}

int main(){
        pthread_t tids[NUM_THREADS];
	int index[NUM_THREADS];

        for(int i = 0; i < NUM_THREADS; ++ i){
		index[i] = i;
                int ret = pthread_create(&tids[i], NULL, say_hello, (void *)&(index[i]));
                if(ret != 0){
                        cout<<"pthread_create error: error_code="<<ret<<endl;
                }
        }
	for(int i = 0; i < NUM_THREADS; ++ i){
		pthread_join(tids[i], NULL);
	}
//	pthread_exit(NULL);
        return 0;
}

