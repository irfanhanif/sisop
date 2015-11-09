#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *findPrime(void*);

int counter;

int main(){
	int number, i, j, *temp;
	int x[i];

	counter = 0;

	printf("Masukkan angka: ");
	scanf("%d", &number);

	pthread_t *thread = (pthread_t*)malloc(number * sizeof(pthread_t));
	for(i=1; i <= number;i++){
		x[i] = i;
		pthread_create(&thread[i], NULL, findPrime, &x[i]);
	}

	for(i=1; i<=number; i++)
		pthread_join(thread[i], NULL);

	//pthread_exit(NULL);

	printf("Jumlah prime number: %d\n", counter);

	return 0;
}

void *findPrime(void *args){
	int i, flag=0;

	int number = *((int*) args);

	if(number == 1) return;
	for(i=1; i<= number; i++){
		if(number % i == 0)
			flag++;
	}
	if(flag > 2){
		//printf("%d: not prime\n", number);
	}
	else{
		//printf("%d: prime\n", number);
		counter++;
	}
	return;
}