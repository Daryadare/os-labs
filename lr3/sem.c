#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;
static int counter = 1;

void* func1(void* args){
 int i;
 int local;
 for(i=0; i<3; i++){
  sem_wait(&semaphore); //ожидание доступа
  local = counter;
  printf("thread 1 income value: %d\n", local);
  local++;
  counter = local;
  sleep(1);
  sem_post(&semaphore);//разблокировка ожидающих потоков + увеличение значения семафора
 }
}

void* func2(void* args){
 int i;
 int local;
 for(i=0; i<3; i++){
  sem_wait(&semaphore); //ожидание доступа
  local = counter;
  printf("thread 2 income value: %d\n", local);
  local--;
  counter = local;
  sleep(1);
  sem_post(&semaphore);
 }
}

void main() {
 pthread_t thread1;
 pthread_t thread2;
 printf("initial counter value: %d\n", counter);
 sem_init(&semaphore, 1, 1);//инициализация семафора
//счeтчик=1, значит, после того, как один из потоков уменьшит значение семафора,
//второй вынужден будет ждать доступа к ресурсу

 pthread_create(&thread1, NULL, func1, NULL);
 pthread_create(&thread2, NULL, func2, NULL);

//перевод потоков в состояние ожидания
 pthread_join(thread1, NULL);
 pthread_join(thread2, NULL);

 sem_destroy(&semaphore);//уничтожение семафора
 printf("final counter value: %d\n", counter);
 pthread_exit(NULL);
}
