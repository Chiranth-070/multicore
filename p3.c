#include <stdio.h>
#include <pthread.h>
#define SIZE 3

int A[SIZE][SIZE]={{1,2,3},{4,5,6},{7,8,9}};
int B[SIZE][SIZE]={{9,8,7},{6,5,4},{3,2,1}};
int C[SIZE][SIZE];

void* add_row(void* r){
    int i = *(int*)r;
    printf("Thread %lu processing row %d\n",(unsigned long)pthread_self(), i);
    for(int j=0;j<SIZE;j++)
        C[i][j]=A[i][j]+B[i][j];
    return NULL;
}

int main(){
    pthread_t t[SIZE];
    int row[SIZE];

    for(int i=0;i<SIZE;i++){
        row[i]=i;
        pthread_create(&t[i], NULL, add_row, &row[i]);
    }
    for(int i=0;i<SIZE;i++)
        pthread_join(t[i], NULL);

    printf("\nResultant Matrix:\n");
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
}

// mpicc -0 p3 p3.c
// mpirun -np 1 ./p3
