#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
int main (){
 pid_t pid; // process identifier
 if (pid=fork()){
  if (pid=fork()){}}
 struct tm *u;
 char t[20] = {0};
 const timer_t timer = time(NULL);
 u = localtime(&timer);
 strftime(t,20,"%H:%M:%S",u);
 printf("Current time = %s\n",t);
 if(pid==0){
  printf ("Это Дочерний процесс его pid=%d\n", getpid());
  printf ("А pid его Родительского процесса=%d\n", getppid());
 }
 else if(pid>0){
  printf("Это Родительский процесс pid=%d\n", getpid());
  system("ps -x");
 }
 else
  printf("Ошибка вызова fork, потомок не создан\n");
}
