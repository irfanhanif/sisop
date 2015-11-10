#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

FILE *file1, *file2, *file3;

void *function1(void*);
void *function2(void*);

int main(){
	//membuka semua file dengan dan menunjuknya dengan pointer
	file1 = fopen("firstfile.txt", "r");
	file2 = fopen("secondfile.txt", "wb"); //Menulis dan Membaca
	file3 = fopen("thirdfile.txt", "w");

	pthread_t thread1, thread2;

	//menjalan dua thread
	pthread_create(&thread1, NULL, function1, NULL);
	pthread_create(&thread2, NULL, function2, NULL);

	//main menunggu kedua thread untuk selesai
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("\nCOMPLETED\n");
	return 0;
}

//fungsi untuk membaca file1 dan menuliskannya di file2
void *function1(void *arg){
	//seek the end of the file
	fseek(file1, 0L, SEEK_END);
	//returns the current file position of the given stream.
	long fsize = ftell(file1);
	//seek back to the beginning of the file
	fseek(file1, 0, SEEK_SET);
	//printf("%ld", fsize);

	//alokasi string sebesar fsize
	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, file1);

	fputs(string, file2);
	//fclose(file2);
}

void *function2(void *arg){
	long fsize = 0;

	//menunggu file2 telah ditulis
	while(1){
		//printf("1");
		//fseek(file2, 0, SEEK_END);

		fsize = ftell(file2);
		//fseek(file2, 0, SEEK_SET);
		if(fsize > 0){
			//printf("%ld", fsize);
			break;
		}
	}

	//fopen("secondfile.txt", "r");

	//menutup pointer file agar dapat dibuka kembali
	fclose(file2);
	file2 = fopen("secondfile.txt", "r");

	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, file2);

	fprintf(file3, "%s", string);
}