#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sigHandler(int sigNumber){
	printf("\nYou cannot interrupt/stop this program.\n");
	printf("Press CTRL + D to quit\n");
}

void main(){
	signal(SIGINT, sigHandler);
	signal(SIGTSTP, sigHandler);

	pid_t pid, start;

	int i; 
	char *token, *test[5], input[10], *x = "cd", *dan = "&";
	char *substr;
	char ch;

	start = fork();
	if (start == 0){
		execlp("pwd", "pwd", NULL);
	}
	wait();
	printf("Input: ");
	while(scanf("%[^\n]", input)!= EOF){
		//memset(input, '\0', sizeof(input));
		//printf("Masukkan perintah: ");
		getchar();


		i = 0;

		memset(test, '\0', sizeof(test));
		token = strtok(input, " ");
		substr = strstr(input, " ");

		while(token != NULL){
			test[i] = token;
			i++;
			token = strtok(NULL, " ");
		}

		if(strcmp(test[0], x) == 0){
			chdir(test[i-1]);
			start = fork();
			if(start == 0){
				execlp("pwd", "pwd", NULL);
			}
			wait();
		}
		else{
			if(strcmp(test[i-1], dan) == 0){
				test[i-1] = NULL;
				pid = fork();
				if(pid == 0){
					execvp(test[0], test);
				}
				start = fork();
				if(start == 0){
					execlp("pwd", "pwd", NULL);
				}
				wait();
			}
			else{
				pid = fork();
				if(pid == 0){
					execvp(test[0], test);
				}
				wait();
				start = fork();
				if(start == 0){
					execlp("pwd", "pwd", NULL);
				}
				wait();
			}
		}
		memset(input, '\0', sizeof(input));
		printf("Input: ");
	}
}