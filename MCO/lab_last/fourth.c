/*Write a multithreaded program to multiply every element in the 
array by a constant. The even numbered threads should multiply 
the elements in the even indices of the array and the odd 
numbered threads should multiply the elements present in the 
odd indices of the array. (Assume 0 to be the starting even 
index) give openMP program*/


#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 10
#define CONSTANT 2

int main() {
    int array[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10};

    #pragma omp parallel num_threads(2)
    {
        int thread_id =omp_get_thread_num();

        if(thread_id % 2 == 0) {
            #pragma omp for
            for(int i=0;i<ARRAY_SIZE ; i+=2){
                array[i] *= CONSTANT;
                printf("Thread %d : Element at indexd %d multiplied by %d = %d \n",thread_id,i,CONSTANT,array[i]);
            }
        }

        else {
            #pragma omp for
            for(int i=1;i<ARRAY_SIZE ;i+=2){
                array[i] *=CONSTANT;
                printf("Thread %d : Element at indexd %d multiplied by %d = %d \n",thread_id,i,CONSTANT,array[i]);

            }
        }
    }
    return 0;
}
