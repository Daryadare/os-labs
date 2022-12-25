#define _POSIX_SOURCE
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h> 
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char ** argv){
 char hostname[128];
 char login[128];

 gethostname(hostname, sizeof(hostname));
 getlogin_r(login, sizeof(login));
 printf("task 1\n My hostname: %s. My login: %s\n", hostname,login);
 printf("\n");

 struct utsname uts;
 if (uname(&uts)>=0)
  printf("task 2\n sysname: %s\n nodename: %s\n release: %s\n version: %s"
"\n machine: %s\n ", uts.sysname,uts.nodename,uts.release,uts.version,uts.machine);
 else{
 printf("Fix your function\n");
 }
 printf("\n");

 long clock_ticks = sysconf(_SC_CLK_TCK);
 long pagesize = sysconf(_SC_PAGESIZE);
 long stream = sysconf(_SC_STREAM_MAX);
 printf("task 3\n System  metrics:\n Clock ticks per second = %ld\n Size of a page"
" in bytes = %ld\n Maximum number of streams = %ld\n",clock_ticks,pagesize,stream);
 printf("\n");

 printf("task 4\n");
 time_t temp;
 temp = time(NULL);
 printf("1 method\n Seconds since 1970-01-01 00:00:00 : %ld\n", time(&temp)); 
 printf("2 method\n %s", asctime(localtime(&temp)));
 printf("\n");

 printf("task5.1 Reading files in directory\n");
 DIR *dir;
 struct dirent *entry;

 dir = opendir(".");
 while (entry = readdir(dir)){
  printf("%10s:\t i-number = %ld\t type of fyle: [%d]\t length of record: %d\t\n",
entry->d_name,entry->d_ino,entry->d_type,entry->d_reclen);
 }
 closedir(dir);
 printf("\n");

 printf("task5.2 Output the files in reverse alphabetical order\n");
 struct dirent **namelist;
 int n;
 n = scandir(".", &namelist, 0, alphasort);
 if (n < 0)
  perror("scandir");
 else {
  while(n--){
   printf("%s\n", namelist[n]->d_name);
   free(namelist[n]);
  }
 free(namelist);
 }
 printf("\n");

 printf("task5.3 Current path\n");
 if(argc!=2)
  printf("Using: %s path\n", argv[0]);
 printf("\n");

 struct stat statv;
 if(!stat(argv[0], &statv))
  printf("task5.4 Info about file %s\n Size: %d\n Reference count: %d\n",
argv[0],(int)statv.st_size,(int)statv.st_nlink);
 return 0;
}

