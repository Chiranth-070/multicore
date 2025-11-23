#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define B 5
#define N 10

int buf[B], in=0, out=0, cnt=0;
pthread_mutex_t m;
pthread_cond_t nf, ne;

void* prod(){
    for(int i=1;i<=N;i++){
        pthread_mutex_lock(&m);
        while(cnt==B) pthread_cond_wait(&nf,&m);

        buf[in]=i;
        printf("Produced Task: %d\n", i);
        in=(in+1)%B; cnt++;

        pthread_cond_signal(&ne);
        pthread_mutex_unlock(&m);
        sleep(1);
    }
    return NULL;
}

void* cons(){
    for(int i=1;i<=N;i++){
        pthread_mutex_lock(&m);
        while(cnt==0) pthread_cond_wait(&ne,&m);

        printf("Consumed Task: %d\n", buf[out]);
        out=(out+1)%B; cnt--;

        pthread_cond_signal(&nf);
        pthread_mutex_unlock(&m);
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t p, c;
    pthread_mutex_init(&m,NULL);
    pthread_cond_init(&nf,NULL);
    pthread_cond_init(&ne,NULL);

    pthread_create(&p,NULL,prod,NULL);
    pthread_create(&c,NULL,cons,NULL);
    pthread_join(p,NULL);
    pthread_join(c,NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&nf);
    pthread_cond_destroy(&ne);
}

// mpicc -o p6 p6.c
// mpirun -np 1 ./p6
