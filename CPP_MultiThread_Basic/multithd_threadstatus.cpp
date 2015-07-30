#include <iostream>
#include <pthread.h>

using namespace std;

const int NUM_THREADS = 5;

void *say_hello(void *args){
        int res = *((int *)args);
        cout<<"Hello in "<<res<<endl;
        int status = 10 + *((int *)args);
	pthread_exit((void *)status);
}

int main(){
        pthread_t tids[NUM_THREADS];
        int index[NUM_THREADS];

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        for(int i = 0; i < NUM_THREADS; ++ i){
                index[i] = i;
                int ret = pthread_create(&tids[i], &attr, say_hello, (void *)&(index[i]));
                if(ret != 0){
                        cout<<"pthread_create error: error_code="<<ret<<endl;
                }
        }

	pthread_attr_destroy(&attr);	

	void *status;
        for(int i = 0; i < NUM_THREADS; ++ i){
		int ret = pthread_join(tids[i], &status);

		if(ret != 0){
			cout<<"pthread_create error: error_code="<<ret<<endl;
		}else{
			cout<<"pthread_join get status: "<<(long)status<<endl;
		}
        }

        pthread_exit(NULL);
        return 0;
}

