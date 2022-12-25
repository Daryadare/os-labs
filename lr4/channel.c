#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

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
	int p[2];
	int part1[]={-1,-1};
	int part2[]={-1,-1};
	int part3[]={-1,-1};
	int part4[]={-1,-1};
	int finalarray[8];
	int array[] = {12, 2, 3, 19, 9, 7, 14, 18};
	printf("Initial array: ");
	print(array, 8);
	printf("\n");

	if(pipe(p)==-1){
		perror("error");
		exit(1);}
	else{printf("Received array:\n");}

	pid=fork();
	if(pid==0){
		interval(array, part1,0,5);
		insertionSort(part1,2);
		write(p[1],part1,sizeof(int)*2);

		interval(array, part2,5,10);
		insertionSort(part2,2);
               	write(p[1],part2,sizeof(int)*2);

		interval(array, part3,10,15);
               	insertionSort(part3,2);
               	write(p[1],part3,sizeof(int)*2);

		interval(array, part4,15,20);
               	insertionSort(part4,2);
               	write(p[1],part4,sizeof(int)*2);

		close(p[1]);
		exit(0);
	}

	if(pid>0){
		read(p[0],&finalarray,sizeof(int)*8);
		for(int i=0; i<8; i++){
			printf("%d ",finalarray[i]);
		}
		close(p[0]);
	}
	printf("\n");
	return 0;
}
