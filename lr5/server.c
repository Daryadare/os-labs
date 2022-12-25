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

	if(bind(sock,(struct sockaddr *)&addr,sizeof(addr))<0){
		printf("error calling bind");
		exit(1);
	}

	if(listen(sock,5)){
		printf("error listening");
		exit(1);
	}

	int array[]={12, 2, 3, 19, 9, 7, 14, 18};
	int transfer[2];
	int finalarray[8];

	for(int i=0; i<4; i++){
		int msg=accept(sock,NULL,NULL);
		if(msg<0){
			printf("error accepting");
			exit(1);
		}
		int temp[2];
		recv(msg,temp,sizeof(int)*2,0);
		if(i==0){
			finalarray[0]=temp[0];
			finalarray[1]=temp[1];
		}
		else if(i==1){
			finalarray[2]=temp[0];
			finalarray[3]=temp[1];
		}
		else if(i==2){
			finalarray[4]=temp[0];
			finalarray[5]=temp[1];
		}
		else{
			finalarray[6]=temp[0];
			finalarray[7]=temp[1];
		}
	}
	insertionSort(finalarray,8);
	for(int i=0; i<8; i++){
		printf("%d ",finalarray[i]);
	}
	printf("\n");
	close(sock);
	return 0;
}
