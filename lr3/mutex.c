#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t mutex;

void* func1(void *args){
 int i;
 pthread_mutex_lock(&mutex);
  for(i=0; i<5; i++)
   printf("thread 1 printing value 14 for the %d time\n", i+1);
 pthread_mutex_unlock(&mutex);
}

void* func2(void *args){
 int i;
  pthread_mutex_lock(&mutex);
  for(i=0; i<2; i++)
   printf("thread 2 printing value 0 for the %d time\n", i+1);
  pthread_mutex_unlock(&mutex);
}

void* func3(void *args){
 int i;
  pthread_mutex_lock(&mutex);
  for(i=0; i<8; i++)
   printf("thread 3 printing value 77 for the %d time\n", i+1);
  pthread_mutex_unlock(&mutex);
}

int main(){
 pthread_t thread1;
 pthread_t thread2;
 pthread_t thread3;
 pthread_mutex_init(&mutex, NULL);//инициализация мьютекса

 pthread_create(&thread1, NULL, func1, NULL);
 pthread_create(&thread2, NULL, func2, NULL);
 pthread_create(&thread3, NULL, func3, NULL);

 pthread_join(thread1, NULL);
 pthread_join(thread2, NULL);
 pthread_join(thread3, NULL);

 pthread_mutex_destroy(&mutex);//уничтожение мьютекса
 pthread_exit(NULL);
}
