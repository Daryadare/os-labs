#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_barrier_t barrier;

void* func1(void *args){
 int i;
  for(i=0; i<49; i+=3){
   printf("thread 1 printing value %d\n", i);
   if(i==24){
    printf("Thread 1 has reached the barrier\n");
    pthread_barrier_wait(&barrier);
   }
  }
}

void* func2(void *args){
 int i;
  for(i=0; i<49; i+=4){
   printf("thread 2 printing value %d\n", i);
   if(i==24){
    printf("Thread 2 has reached the barrier\n");
    pthread_barrier_wait(&barrier);
   }
 }
}

void* func3(void *args){
 int i;
  for(i=0; i<49; i+=6){
   printf("thread 3 printing value %d\n", i);
   if(i==24){
    printf("Thread 3 has reached the barrier\n");
    pthread_barrier_wait(&barrier);
   }
 }
}

void* func4(void *args){
 int i;
  for(i=0; i<30; i+=5)
   printf("thread 4 printing value %d\n", i);
}

int main(){
 pthread_t thread1;
 pthread_t thread2;
 pthread_t thread3;
 pthread_t thread4;
 pthread_barrier_init(&barrier, NULL, 3);//инициализация барьера для 3 потоков
 printf("Barrier value is 24\n");

 pthread_create(&thread1, NULL, func1, NULL);
 pthread_create(&thread2, NULL, func2, NULL);
 pthread_create(&thread3, NULL, func3, NULL);
 pthread_create(&thread4, NULL, func4, NULL);

 pthread_join(thread1, NULL);
 pthread_join(thread2, NULL);
 pthread_join(thread3, NULL);
 pthread_join(thread4, NULL);

 pthread_barrier_destroy(&barrier);//уничтожение барьера
 pthread_exit(NULL);
}
