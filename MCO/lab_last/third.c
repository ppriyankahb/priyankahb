/*Create two functions, one to add two arrays and one to multiply 
two arrays. 
Write a program that will call these two functions in two separate 
threads. Also display their thread ids.*/

#include<stdio.h>
#include<omp.h>

#define ARRAY_SIZE 5

void add_arrays(int array1[],int array2[]) {
    printf("thread %d : Adding arrays\n",omp_get_thread_num());
    int result[ARRAY_SIZE];

    for(int i=0;i<ARRAY_SIZE ;i++){
        result[i] = array1[i]+array2[i];

    }

    printf("Thread %d result after addition: ",omp_get_thread_num());
    for(int i=0;i<ARRAY_SIZE;i++){
        printf("%d ",result[i]);
    }
    printf("\n");
}

void multiply_arrays(int array1[],int array2[]) {
    printf("thread %d : multiply arrays\n",omp_get_thread_num());
    int result[ARRAY_SIZE];

    for(int i=0;i<ARRAY_SIZE ;i++){
        result[i] = array1[i]*array2[i];

    }

    printf("Thread %d result after multiplication: \n",omp_get_thread_num());
    for(int i=0;i<ARRAY_SIZE;i++){
        printf("%d ",result[i]);
    }
    printf("\n");
}
int main()
{
    int array1[ARRAY_SIZE] = {1,2,3,4,5};
    int array2[ARRAY_SIZE] = {6,7,8,9,0};

    #pragma omp parallel num_threads(2)
    {
        #pragma omp sections
        {
            #pragma omp section 
            {
                add_arrays(array1,array2);

            }
            #pragma omp section
            {
                multiply_arrays(array1,array2);
            }
        }
    }

    return 0;
}