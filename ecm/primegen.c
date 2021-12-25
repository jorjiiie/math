#include <stdio.h>
#include <string.h>

int isPrime[100000001];


int main() {

	FILE *OUT = fopen("PRIMES.txt","w");
	int cnt = 0;
	memset(isPrime,1,sizeof isPrime);
	fprintf(OUT,"2\n");
	for (long long i=3;i<=1e8;i+=2) {
		if (isPrime[i]) {
			cnt++;
			// fprintf(OUT,"%lld ",i);
			for (long long j=i*i;j<=1e8;j+=i*2) {
				isPrime[j]=0;
			}
			fprintf(OUT, "%lld\n", i);
		}

	}
	// printf("%d\n",cnt);

	// FILE *IN = fopen("PRIMES.txt","r");
	// for (int i=0;i<50;i++) {
	// 	int a;
	// 	fscanf(IN,"%d",&a);
	// 	printf("%d\n",a);
	// }
}