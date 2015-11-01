#include <stdio.h>
#include <pthread.h>

void *numberOfPrime(void*);
void primeChecker(int);

int counter = 0;

void main(){
	int number;
	printf("Masukkan jumlah N: ");
	scanf("%d", &number);

	int *pointer = &number;

	pthread_t thread;
	pthread_create(&thread, NULL, numberOfPrime, (void*) pointer);
	pthread_join(thread, NULL);

	printf("Total of Prime Number: %d\n", counter);
}

void *numberOfPrime(void* arg){
	int *number = (int*) arg;
	pthread_t thread;

	int check = *number;

	//printf("number: %d\n", *number);
	//printf("number: %d\n", *number);
	
	if(*number>=1){
		*number = *number-1;
		pthread_create(&thread, NULL, numberOfPrime, (void*)number);
		primeChecker(check);
		pthread_join(thread, NULL);
	}
}

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
