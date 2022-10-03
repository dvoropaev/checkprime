#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
	unsigned long long int number;
	struct timespec start, finish;
	double elapsed;
	int N;
	while(1){
		scanf("%i", &N);
		scanf("%llu", &number);
		clock_gettime(CLOCK_MONOTONIC, &start);
		if(isPrime(number, N) == 1)
			printf("YES ");
		else
			printf("NO  ");
		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; //-------------?
		printf("(%f sec)\n\n", elapsed);
	}

	return 0;
}
