#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv){
	FILE *f;
	char s;
	char *p;
	int n,i;
	long viv = strtol(argv[2], &p, 10);
	n = viv;

	if(argc<3){
		printf("Введите имя файла и количество строк в группе\n");
		exit(0);
	}

	if(f=fopen(argv[1], "r")){
		if (strcmp(argv[2],"0")==0){
			s = fgetc(f);
			while(s!=EOF){
				printf("%c",s);
				s=fgetc(f);
			}
		}
		else{
			while(1){
				for(i=0; i<n; i++){
					s=fgetc(f);
					if(s!=EOF){
						while(s!='\n'){
							printf("%c",s);
							s=fgetc(f);
						}
						printf("\n");
					}
					else if(feof(f)!=0){
						printf("\nЧтение файла завершено\n");
						exit(0);
					}
					else{
						printf("\nОшибка чтения файла\n");
						exit(0);
					}
				}
				printf("\nДля продолжения нажмите любую клавишу...\n"
"(Для выхода из программы нажмите q)\n");
					if(getchar()=='q') {break;}
					else if(getchar()=='\n') {printf("n");}
			}
		}
		fclose(f);
	}
	else{
		printf("Ошибка открытия файла\n");
	}
}
