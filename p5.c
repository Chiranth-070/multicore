#include <stdio.h>
#include <pthread.h>

#define SIZE 100
#define T 4

int arr[SIZE];
int found = -1;
pthread_mutex_t lock;

void* search(void* x){
    int s = *(int*)x, e = s + SIZE/T;
    for(int i=s;i<e;i++)
        if(arr[i] == 50){
            pthread_mutex_lock(&lock);
            found = i;
            pthread_mutex_unlock(&lock);
            return NULL;
        }
    return NULL;
}

int main(){
    pthread_t th[T];
    int start[T];

    for(int i=0;i<SIZE;i++) arr[i]=i+1;

    pthread_mutex_init(&lock, NULL);

    for(int i=0;i<T;i++){
        start[i] = i*(SIZE/T);
        pthread_create(&th[i], NULL, search, &start[i]);
    }
    for(int i=0;i<T;i++)
        pthread_join(th[i], NULL);

    (found!=-1) ? printf("Number 50 found at index: %d\n",found)
                : printf("Number 50 not found.\n");

    pthread_mutex_destroy(&lock);
}

// mpicc -o p5 p5.c
// mpirun -np 1 ./p5
