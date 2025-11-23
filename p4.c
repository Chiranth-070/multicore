#include <stdio.h>
#include <pthread.h>

#define SIZE 16
#define NUM_THREADS 4

int arr[SIZE] = {38,27,43,3,9,82,10,29,42,2,1,8,5,6,7,4};
int temp[SIZE];

typedef struct {
    int l, r;
} data;

void merge(int l, int m, int r){
    int i=l, j=m+1, k=l;
    while(i<=m && j<=r)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while(i<=m) temp[k++] = arr[i++];
    while(j<=r) temp[k++] = arr[j++];
    for(i=l;i<=r;i++) arr[i]=temp[i];
}

void sort(int l, int r){
    if(l>=r) return;
    int m=(l+r)/2;
    sort(l,m); sort(m+1,r);
    merge(l,m,r);
}

void* thread_sort(void* x){
    data* d = (data*)x;
    sort(d->l, d->r);
    return NULL;
}

int main(){
    pthread_t t[NUM_THREADS];
    data d[NUM_THREADS];
    int part = SIZE / NUM_THREADS;

    for(int i=0;i<NUM_THREADS;i++){
        d[i].l = i*part;
        d[i].r = (i == NUM_THREADS-1) ? SIZE-1 : (i+1)*part-1;
        pthread_create(&t[i], NULL, thread_sort, &d[i]);
    }
    for(int i=0;i<NUM_THREADS;i++)
        pthread_join(t[i], NULL);

    for(int i=1;i<NUM_THREADS;i++){
        int mid = i*part - 1;
        int right = (i == NUM_THREADS-1) ? SIZE-1 : (i+1)*part-1;
        merge(0, mid, right);
    }

    printf("\nSorted Array:\n");
    for(int i=0;i<SIZE;i++) printf("%d ", arr[i]);
    printf("\n");
}

// mpicc -o p4 p4.c
// mpirun -np 1 ./p4
