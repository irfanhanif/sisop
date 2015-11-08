#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

FILE *file1, *file2, *file3;

void *function1(void*);
void *function2(void*);

int main(){
	file1 = fopen("firstfile.txt", "r");
	file2 = fopen("secondfile.txt", "r+");
	file3 = fopen("thirdfile.txt", "w");

	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, function1, NULL);
	pthread_create(&thread2, NULL, function2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}

void *function1(void *arg){
	fseek(file1, 0, SEEK_END);
	long fsize = ftell(file1);
	fseek(file1, 0, SEEK_SET);

	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, file1);

	fputs(string, file2);
	fclose(file2);
}

void *function2(void *arg){
	long fsize = 0;
	/*do{
		file2 = fopen("secondfile.txt", "r+");
		fseek(file2, 0, SEEK_END);
		fsize = ftell(file1);
		fseek(file2, 0, SEEK_SET);
	} while(fsize == 0);*/

	while(1){
		fseek(file2, 0, SEEK_END);
		fsize = ftell(file1);
		fseek(file2, 0, SEEK_SET);
		if(fsize != 0){
			file2 = fopen("secondfile.txt", "r+");
			break;
		}
	}

	//printf("%ld", fsize);

	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, file2);

	puts(string);

	fprintf(file3, "%s", string);
}