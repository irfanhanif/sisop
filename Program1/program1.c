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

	pid_t pid, temp;

	char input[10];
	while(1){
		memset(input, '\0', sizeof(input));
		printf("Masukkan perintah: ");
		scanf("%[^\n]", input);
		getchar();
		if(input[0] == 'q') break;
		//printf("%s\n", input);

		char test[5][100];
		int i = 0;

		memset(test, '\0', sizeof(test));

		char *token = strtok(input, " ");

		while(token != NULL){
			strcpy(test[i], token);
			i++;
			token = strtok(NULL, " ");
		}

		pid = fork();
		if(pid == 0){
			if(i>1)
				execlp(test[0], test[0], test[1], (char*) NULL);
			else{
				execlp(test[0], test[0], (char*) NULL);
			}
			//temp = getpid();
		}
		//waitpid(temp);
		wait();
	}
}