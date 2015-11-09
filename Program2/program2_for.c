#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *findPrime(void*);

int counter;

int main(){
	int number, i, j, *temp;

	counter = 0;

	printf("Masukkan angka: ");
	scanf("%d", &number);

	pthread_t *thread = (pthread_t*)malloc(number * sizeof(pthread_t));
	for(i=0; i < number;i++)
		pthread_create(&thread[i], NULL, findPrime, NULL);
	
	for(j=0; j < number; j++)
		pthread_join(thread[i], NULL);

	printf("Jumlah prime number: %d\n", counter);

	return 0;
}

void *findPrime(void *args){
	int i, flag=0;
	static int check = 0;
	++check;
	//printf("%d", *args);

	//int number = *(int*) args;
	//printf("%dA", *number);

	for(i=1; i<= check; i++){
		if(check % i == 0)
			flag++;
	}
	if(flag > 2){
		//printf("%d: not prime\n", check);
	}
	else{
		//printf("%d: prime\n", check);
		counter++;
	}
	return;
}