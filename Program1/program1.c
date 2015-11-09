#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sigHandler(int sigNumber){
	printf("\nYou cannot interrupt/stop this program.\n");
	printf("input 0 to quit\n");
}

void main(){
	signal(SIGINT, sigHandler);
	signal(SIGTSTP, sigHandler);

	pid_t pid;

	int i; 
	char *token, *test[5], input[10], *x = "cd", *dan = "&";

	while(1){
		memset(input, '\0', sizeof(input));
		printf("Masukkan perintah: ");
		scanf("%[^\n]", input);
		if(EOF) return;
		getchar();
		
		//if(input[0] == '\04') break;

		i = 0;

		memset(test, '\0', sizeof(test));
		token = strtok(input, " ");

		while(token != NULL){
			test[i] = token;
			i++;
			token = strtok(NULL, " ");
		}

		if(strcmp(test[0], x) == 0){
			chdir(test[i-1]);
		}
		else{
			if(strcmp(test[i-1], dan) == 0){
				test[i-1] = NULL;
				pid = fork();
				if(pid == 0){
					execvp(test[0], test);
				}
			}
			else{
				pid = fork();
				if(pid == 0){
					execvp(test[0], test);
				}
				wait();
			}
		}
	}
}