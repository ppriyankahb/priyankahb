#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 4

int matrix[SIZE][SIZE];
int sumDiagonal1 = 0;
int sumDiagonal2 = 0;
int sumAll = 0;
char sentence[100];

void* computeSumDiagonal1(void* arg) {
  for (int i = 0; i < SIZE; i++) {
    sumDiagonal1 += matrix[i][i];
  }
  return NULL;
}

void* computeSumDiagonal2(void* arg) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (i + j == SIZE - 1) {
        sumDiagonal2 += matrix[i][j];
      }
    }
  }
  return NULL;
}

void* computeSumAll(void* arg) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      sumAll += matrix[i][j];
    }
  }
  return NULL;
}

//void writeToFile(void* arg) {
    //char *sentence=(char*)arg;
  
  //}

  
  //fclose(fp);

  

/*void *threadFunction(void *arg) {
    char *sentence = (char *)arg;
    writeToFile(sentence);
    return NULL;
}*/

int main() {
  pthread_t thread1, thread2, thread3, thread4;

  // Read the matrix from the user
  printf("Enter the matrix elements:\n");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }

  // Read the sentence from the user
  printf("Enter the sentence to write to file:\n");
  scanf("%[^\n]s",sentence);

  // Create threads to compute the sums
  pthread_create(&thread1, NULL, computeSumDiagonal1, NULL);
  pthread_create(&thread2, NULL, computeSumDiagonal2, NULL);
  pthread_create(&thread3, NULL, computeSumAll, NULL);

  // Create a thread to write the sentence to file
  //pthread_create(&thread4, NULL, threadFunction, (void*)sentence);

  // Wait for all threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  //pthread_join(thread4, NULL);

  FILE *fp = fopen("txt.txt", "w");
  if (fp == NULL) {
    printf("Error opening file\n");
    exit(1);
  }
    fprintf(fp,"%s",sentence);
   fclose(fp);


  // Print the results
  printf("Sum of principal diagonal 1: %d\n", sumDiagonal1);
  printf("Sum of principal diagonal 2: %d\n", sumDiagonal2);
  printf("Sum of all elements: %d\n", sumAll);

  return 0;
}
