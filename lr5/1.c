#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){
	FILE *f;
	char s;
	char *p;
	char buf[100];
	char fileName[20];
	int pid;
	long conv=strtol(argv[2], &p, 10);
	pid=conv;

	if(argc<3){
		printf("Введите имя файла и pid процесса: ");
		exit(0);
	}

	f=fopen(argv[1],"rw");
	if(!f){
		printf("Ошибка обнаружения файла\nСоздание файла с указанным именем...\n");
		if(!(f=fopen(argv[1],"w"))){
			printf("Ошибка открытия файла\n");
			exit(0);}

		sprintf(buf,"%s %d %s %s","pmap",pid,">>",argv[1]);
		system(buf);
		printf("Файл успешно создан\n");}

		else{
		printf("Файл уже существует\n"
"Вы можете заменить файл на новый (1) или переименовать результирующий файл (2)\n"
"Введите 1 или 2: ");

		s=getchar();
		if(s=='1'){
			fclose(f);
			remove(argv[1]);
			f=fopen(argv[1], "w");
			sprintf(buf,"%s %d %s %s","pmap",pid,">>",argv[1]);
			system(buf);
			fclose(f);
			printf("Файл успешно заменен\n");
			exit(0);}

		else if (s=='2'){
			fclose(f);
			while(1){
				printf("Введите новое имя файла: \n");
				scanf("%s",&fileName);
				f=fopen(fileName,"rw");

				if(!f){
					if(!(f=fopen(fileName, "w"))){
						printf("Ошибка открытия файла\n");
						exit(0);
					}
					sprintf(buf,"%s %d %s %s","pmap",pid,">>",fileName);
					system(buf);
					fclose(f);
					printf("Файл успешно переименован\n");
                    			exit(0);
				}
				else printf("Файл с таким именем уже существует\n");
			}
		}
		else{
			printf("Ошибка некорректного ввода\n");
			exit(0);
		}
	}
}
