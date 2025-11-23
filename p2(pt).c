#include <pthread.h>
#include <stdio.h>

void* print_msg(void *x){
    printf("Hello from thread %d\n", *(int*)x);
    return NULL;
}

int main(){
    pthread_t t[5];
    int id[5];

    for(int i=0; i<5; i++){
        id[i] = i;
        pthread_create(&t[i], NULL, print_msg, &id[i]);
    }
    for(int i=0;i<5;i++)
        pthread_join(t[i], NULL);
}

//gcc -pthread -o p2 p2.c
// ./p2
