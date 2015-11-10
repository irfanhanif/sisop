#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sigHandler(int sigNumber){
	printf("\nYou cannot interrupt/stop this program.\n");
	printf("Press CTRL + D to quit\n");
}

void main(){
	//Signal handler untuk mengambil CTRL+C dan CTRL+Z
	signal(SIGINT, sigHandler);
	signal(SIGTSTP, sigHandler);

	pid_t pid, start;

	int i; 
	char *token, *test[5], input[10], *x = "cd", *dan = "&";

	//menampilkan posisi direktoru sekarang dengan forking
	start = fork();
	if (start == 0){
		execlp("pwd", "pwd", NULL);
	}
	wait();
	printf("Input: ");

	//kondisi pada while. jika diinput CTRL+D maka akan terminate
	while(scanf("%[^\n]", input)!= EOF){
		//mengambil enter
		getchar();

		i = 0;

		//membuat seluruh pointer to char test isinya NULL
		memset(test, '\0', sizeof(test));

		//memilah substring sebelum spasi
		token = strtok(input, " ");

		//mengambil semua substring yang dipisah spasi
		while(token != NULL){
			test[i] = token;
			i++;
			token = strtok(NULL, " ");
		}

		//jika yang diinput adalah cd
		if(strcmp(test[0], x) == 0){
			//melakukan change directory
			chdir(test[i-1]);
			//menampilkan posisi direktori aktif
			start = fork();
			if(start == 0){
				execlp("pwd", "pwd", NULL);
			}
			wait();
		}
		//jika bukan perintah cd
		else{
			//jika meminta background proses
			//yang diakhiri dengan &
			if(strcmp(test[i-1], dan) == 0){
				test[i-1] = NULL;

				//melakukan background proses yang diminta
				pid = fork();
				if(pid == 0){
					execvp(test[0], test);
				}

				//menampilkan posisi direktori sekarang
				start = fork();
				if(start == 0){
					execlp("pwd", "pwd", NULL);
				}
				wait();
			}

			//bukan proses yang background
			else{

				//melakukan proses yang diminta
				pid = fork();
				if(pid == 0){
					execvp(test[0], test);
				}
				wait();

				//menampilkan direktori aktif
				start = fork();
				if(start == 0){
					execlp("pwd", "pwd", NULL);
				}
				wait();
			}
		}

		//membuat semua isi variabel input menjadi NULL
		memset(input, '\0', sizeof(input));
		printf("Input: ");
	}
}