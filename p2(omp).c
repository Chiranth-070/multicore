#include <omp.h>
#include <stdio.h>

int main(){
    #pragma omp parallel
    {
        int t_id = omp_get_thread_num();
        printf("Hello from thread %d\n", t_id);
    }
    return 0;
}

//gcc -fopenmp -o p2 p2.c
// ./p2
