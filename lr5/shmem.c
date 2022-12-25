#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>

void insertionSort(int mass[],int n){
        int newEl,loc;
        for(int i=1; i<n; i++){
                newEl=mass[i];
                loc=i-1;
                while(loc>=0 && mass[loc]>newEl){
                        mass[loc+1]=mass[loc];
                        loc=loc-1;
                }
        mass[loc+1]=newEl;
        }
}

int interval(int arr[], int part[], int a, int b){
        int n=-1;
        for(int i=0; i<8; i++){
                if(arr[i]>=a && arr[i]<b){
                        n=arr[i];
                        if(n!=-1 && part[0]==-1){
                                part[0]=n;
                        }
                        else if(n!=-1 && part[1]==-1){
                                part[1]=n;
                        }
                }
        }
}

void print(int array[],int k){
         for (int i=0; i<k; i++){
                 printf("%d ", array[i]);
         }
         printf("\n");
}

int main(){
	pid_t pid;
	int shm;
	if((shm=shm_open("shmemory",O_RDWR|O_CREAT,0777))<0){
		perror("error create shm");
		return(1);
	}
	if(ftruncate(shm, sizeof(int)*8)==-1){
		perror("ftruncate");
		return(1);
	}
	int part1[]={-1,-1};
        int part2[]={-1,-1};
        int part3[]={-1,-1};
        int part4[]={-1,-1};

	int array[] = {12, 2, 3, 19, 9, 7, 14, 18};
        printf("Initial array: ");
        print(array, 8);
        printf("\n");

	int* address = (int*) mmap(0,sizeof(int)*8,PROT_READ|PROT_WRITE,MAP_SHARED,shm,0);
	if(address==(int*)-1){
		perror("error address");
		return(1);
	}
	else{
		printf("Received array:\n");}

	pid=fork();
	if(pid==0){
		interval(array, part1,0,5);
		insertionSort(part1,2);
		address[0]=part1[0];
		address[1]=part1[1];

		interval(array, part2,5,10);
		insertionSort(part2,2);
		address[2]=part2[0];
		address[3]=part2[1];

		interval(array, part3,10,15);
		insertionSort(part3,2);
		address[4]=part3[0];
		address[5]=part3[1];

		interval(array, part4,15,20);
		insertionSort(part4,2);
		address[6]=part4[0];
		address[7]=part4[1];

		exit(0);
	}
	else{sleep(1);}

	if(pid>0){
                for(int i=0; i<8; i++){
                        printf("%d ",address[i]);
                }
        }
	printf("\n");
	shm_unlink("shmemory");
	return 0;
}
