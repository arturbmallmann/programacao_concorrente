/*
* from https://fabiojrcosta.wordpress.com/2014/08/11/variavel-condicional/
*/
#include <stdio.h>
#include <pthread.h>
#define TAM_BUFFER 5

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int condition = 0;
int count = 0;

void *consume(void *arg)
{
while(1)
{
pthread_mutex_lock(&mutex);

while(condition == 0 )pthread_cond_wait(&cond,&mutex);
/*bloqueia a variavel condicional
indicando que o produtor precisa encher o buffer*/

count--;condition--;
printf("Consumed %d condition %d\n",count,condition);

if(condition == 0)
pthread_cond_signal(&cond);
pthread_mutex_unlock(&mutex);

}
//return(0);
}

void *produce(void *arg){

while(1)
{
pthread_mutex_lock(&mutex);

while(condition == TAM_BUFFER)    pthread_cond_wait(&cond,&mutex);
/*bloqueia a variavel condicional
indicando que o buffer está cheio
e o consumidor precisa esvaziar o buffer*/

count++;condition++;
printf("Produced %d condition %d\n",count,condition);

if(condition == TAM_BUFFER)
pthread_cond_signal(&cond);
pthread_mutex_unlock(&mutex);

}
//return(0);
}

int main(){
pthread_t th1,th2;

pthread_create(&th1,NULL,&consume,NULL);
pthread_create(&th2,NULL,&produce,NULL);
pthread_join(th1,NULL);
pthread_join(th2,NULL);

}
