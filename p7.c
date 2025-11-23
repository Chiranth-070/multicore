#include <stdio.h>
#include <pthread.h>

#define T 5

int balance = 1000;
pthread_mutex_t m;

void* transact(void* x){
    int amt = *(int*)x;
    pthread_mutex_lock(&m);

    if(balance + amt >= 0){
        balance += amt;
        printf("Transaction successful. New balance: %d\n", balance);
    } else
        printf("Transaction denied. Insufficient funds.\n");

    pthread_mutex_unlock(&m);
    return NULL;
}

int main(){
    pthread_t th[T];
    int a[T] = {-200, 100, -300, 150, -400};

    pthread_mutex_init(&m, NULL);

    for(int i=0;i<T;i++)
        pthread_create(&th[i], NULL, transact, &a[i]);

    for(int i=0;i<T;i++)
        pthread_join(th[i], NULL);

    printf("Final account balance: %d\n", balance);
    pthread_mutex_destroy(&m);
}


// mpicc -o p7 p7.c
// mpirun -np 1 ./p7
