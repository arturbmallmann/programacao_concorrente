/*
* from https://fabiojrcosta.wordpress.com/2014/08/11/variavel-condicional/
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define TAM_BUFFER 5
#define N 3

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int count = 0;

typedef struct {
	int idx, length;
}thread_arg, *ptr_thread_arg;

void *consume(void *arg){
//		ptr_thread_arg ptarg = (ptr_thread_arg) arg;
//		int id = ptarg->idx;
		int id = *(int *) arg;
		printf("Id: %d\n",id);
		while(1)
		{
		pthread_mutex_lock(&mutex);

		if( count % N != id )pthread_cond_wait(&cond,&mutex);

		count++;
		printf("Count: %d Thread: %d\n",count,id);

		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);

		}
//*/
//return(0);
}

int main(){
	printf("inicionou\n");
	pthread_t threads[N];
	thread_arg targs[N];
	int id_arg[N];
	int aa = 11;
	for (int i=0;i<N;i++) printf("_%d_\n",i);
	for(int i=0;i<N;i++) {
		int *u = malloc(sizeof(int));
		*u = i;
		id_arg[i] = i;
		targs[i].idx=i;
		targs[i].length=i*1000;
		pthread_create(&threads[i],NULL,&consume,&id_arg[i]);//targs[i]);
	}
	for (int o=0;o<N;o++) pthread_join(threads[o],NULL);
}

