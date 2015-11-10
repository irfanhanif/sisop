#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *findPrime(void*);

//variabel untuk menghitung banyaknya bilangan prima
int counter;

int main(){
	int number, i, *temp;
	int x[i];

	counter = 0;

	printf("Masukkan angka: ");
	scanf("%d", &number);

	//deklarasi pointer thread sebanyak input yang diinginkan
	pthread_t *thread = (pthread_t*)malloc(number * sizeof(pthread_t));

	//melakukan looping, membuat thread sebanyak bilangan prima
	for(i=1; i <= number;i++){
		//bilangan prima dipassing dalam bentuk array
		x[i] = i;
		pthread_create(&thread[i], NULL, findPrime, &x[i]);
	}

	//menunggu semua thread selesai
	for(i=1; i<=number; i++)
		pthread_join(thread[i], NULL);

	
	//mencetak jumlah bilangan prima
	printf("Jumlah prime number: %d\n", counter);

	return 0;
}

//fungsi untuk mencari bilangan prima
void *findPrime(void *args){
	int i, flag=0;

	int number = *((int*) args);

	if(number == 1) return;
	for(i=1; i<= number; i++){
		if(number % i == 0)
			flag++;
	}
	if(flag <= 2)
		counter++;
	return;
}