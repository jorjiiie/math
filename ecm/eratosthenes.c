#include <stdio.h>
#include <string.h>

/*
 * Ryan Zhu
 * I'm not sure actually how it works but this is suppposed to be a wheel sieve of eratosthenes but I haven't figured it out yet
 */
int isPrime[100000001];
int STEP[510511];
#define GO 510510
int main() {

	int cnt = 0;
	memset(isPrime,1,sizeof isPrime);
	int STEP_COUNT=0;
	int primes[7] = {2,3,5,7,11,13,17};
	int j;
	for (int i=1;i<=510510;i++) {
		for (j=0;j<7;j++) {
			if (i%primes[j]==0) goto end; // LMAO WHEN I START UNIRONICALLY OVERUSING GOTO
			
		}
		STEP[STEP_COUNT++]=i;
		end:
			continue;

	}
	int k = 0;
	// for (int i = STEP[k]; k < STEP_COUNT; i = STEP[++k]) {
		// printf("%d ",i);
	// }
	printf("%d\n",STEP_COUNT);
	// printf("%d\n",cnt);

	// FILE *IN = fopen("PRIMES.txt","r");
	// for (int i=0;i<50;i++) {
	// 	int a;
	// 	fscanf(IN,"%d",&a);
	// 	printf("%d\n",a);
	// }
}