#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
void thread(void *pointer){
 struct tm *u;
 char t[20] = {0};
 const timer_t timer = time(NULL);
 u = localtime(&timer);
 strftime(t,20,"%H:%M:%S",u);
 printf("Current time = %s\n",t);
 long id;
 id = (long)pointer;
 printf("Executing thread %ld with id %lu pid = %d\n",id,pthread_self(),getpid());
 pthread_exit(NULL);
}
void main(int argc,char const *argv[]){
 int num = 3;
 pthread_t pthr[num];
 int output;
 for(int i=0; i<3; i++){
  output = pthread_create(&pthr[i],NULL,thread,(void *)i);
  if(output){
   printf("Error! Return from pthread_create() = %d\n",output);
   exit(0);
  }
 }
 pthread_exit(NULL);
}
