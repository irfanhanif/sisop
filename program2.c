#include <stdio.h>
#include <pthread.h>

void *numberOfPrime(void*);
void primeChecker(int);

int counter = 0;

void main(){
	int number;
	printf("Masukkan jumlah N: ");
	scanf("%d", &number);

	int *pointer = &number; //melakukan passing argumen

	pthread_t thread;
	pthread_create(&thread, NULL, numberOfPrime, (void*) pointer);
	pthread_join(thread, NULL);

	printf("Total of Prime Number: %d\n", counter);
}

void *numberOfPrime(void* arg){
//passing argumen menggunakan typecasting dari int* -> void* -> int*
	int *number = (int*) arg;
	pthread_t thread;

//sintaks ini untuk mengakali pengecekan bilangan prima sebelum berkurang duluan
	int check = *number;
	
//melakukan rekursif untuk setiap cek bilangan prima
//agar pengecekan setiap angka berjalan bersamaan
	if(*number>=1){
		*number = *number-1;
		pthread_create(&thread, NULL, numberOfPrime, (void*)number);
		primeChecker(check);
		pthread_join(thread, NULL);
	}
}

//Fungsi untuk mengetahui sebuah bilangan prima atau bukan
//print setiap bilangan opsional untuk cek apakah multithreading berhasil
void primeChecker(int number){
	int i, flag=0;

	if(number == 1){
		printf("%d: prime\n", number);
		counter++;
		return;	
	}	
	
	for(i=1; i<=number; i++)
		if(number%i == 0)
			flag++;
	if(flag>2){
		printf("%d: not prime\n", number);	
	}
	else{
		printf("%d: prime\n", number);
		counter++;	
	}
}
