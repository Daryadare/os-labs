#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

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

int print(int arr[]){
	for(int i=0; i<2; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(){
        int sock=socket(AF_INET,SOCK_STREAM,0);
        if(sock==-1){
                printf("error opening stream socket");
                exit(1);
        }

        struct sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=htonl(INADDR_ANY);
        addr.sin_port=htons(1234);

	int res=connect(sock,(struct sockaddr*)&addr,sizeof(addr));
	if(res!=0){
		printf("error connecting to the server");
		exit(1);
	}

        int part1[]={-1,-1};
        int part2[]={-1,-1};
        int part3[]={-1,-1};
        int part4[]={-1,-1};
        int array[] = {12, 2, 3, 19, 9, 7, 14, 18};

        int n;
	int temp[2];
	printf("Input number of array's part [1,4]: ");
        scanf("%d",&n);
	if(n==1){
		interval(array,part1,0,5);
		insertionSort(part1,2);
		memcpy(temp,part1,sizeof(int)*2);
	}
	else if(n==2){
		interval(array,part2,5,10);
		insertionSort(part2,2);
		memcpy(temp,part2,sizeof(int)*2);
	}
	else if(n==3){
		interval(array,part3,10,15);
		insertionSort(part3,2);
		memcpy(temp,part3,sizeof(int)*2);
	}
	else if(n==4){
		interval(array,part4,15,20);
		insertionSort(part4,2);
		memcpy(temp,part4,sizeof(int)*2);
	}
	else{
		printf("unrecognizable symbol");
		exit(1);
	}

	res=send(sock,temp,sizeof(int)*2,0);
	if(res<=0){
		printf("error sending");
		exit(1);
	}

	if(shutdown(sock,1)<0){
		printf("error trying to shutdown");
		exit(1);
	}
	return 0;
}
