#include <stdio.h>
#include <signal.h>

void sigHandler(int sigNumber){
	printf("\nYou cannot interrupt/stop this program.\n");
	printf("press 0 to quit\n");
}

void main(){
	signal(SIGINT, sigHandler);
	signal(SIGTSTP, sigHandler);
	int a;
	scanf("%d", &a);
	if(a==0) return;
}
