#include <iostream>
#include <pthread.h>

using namespace std;

const int BOUNDARY = 5;

int tasks = 10;
pthread_mutex_t tasks_mutex;
pthread_cond_t tasks_cond;

void *say_hello2(void *args){
	pthread_t pid = pthread_self();
	cout<<"["<<pid<<"] Hello in thread "<<*((int *)args)<<endl;

	bool is_signaled = false;
	while(1){
		pthread_mutex_lock(&tasks_mutex);
		if(tasks > BOUNDARY){
			cout<<"["<<pid<<"] take task: "<<tasks<<" in thread "<< *((int*)args) << endl;  
			-- tasks;
		}else if(! is_signaled){
			cout << "["<< pid << "] pthread_cond_signal in thread " << *((int*)args) << endl;
			pthread_cond_signal(&tasks_cond);
			is_signaled = true;
		}
		pthread_mutex_unlock(&tasks_mutex);

		if(tasks == 0)
			break;
	}
}

void *say_hello1(void *args){
        pthread_t pid = pthread_self();
        cout<<"["<<pid<<"] Hello in thread "<<*((int *)args)<<endl;

	while(1){
		pthread_mutex_lock(&tasks_mutex);
		if(tasks > BOUNDARY){
			cout<<"["<<pid<<"] pthread_cond_wait in thread " << *((int*)args) << endl;
			pthread_cond_wait(&tasks_cond, &tasks_mutex);
		}else{
			cout << "["<< pid << "] take task:  "<< tasks << " in thread "<< *((int*)args) << endl;  
			-- tasks;
		}
		pthread_mutex_unlock(&tasks_mutex);

		if(tasks == 0)
			break;
	}
}

int main(){
        pthread_t tid1, tid2;

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        pthread_mutex_init(&tasks_mutex, NULL);
	pthread_cond_init(&tasks_cond, NULL);

	int idx1 = 1;
	int ret = pthread_create(&tid1, &attr, say_hello1, (void *)&idx1);
	if(ret){
		cout << "pthread_create error: error_code=" << ret << endl;  
	}
	
	int idx2 = 2;
	ret = pthread_create(&tid2, &attr, say_hello2, (void *)&idx2);
        if(ret){
                cout << "pthread_create error: error_code=" << ret << endl; 
        }

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

        pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&tasks_mutex);
	pthread_cond_destroy(&tasks_cond);

        pthread_exit(NULL);
	return 0;
}

