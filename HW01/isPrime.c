#include<stdio.h>
#include<stdlib.h>

// The program will not function properly if you 
// enter a number greater than the largest int
// possible, 2147483647. It will experience some
// lag or 'hang' time if you enter very large 
// numbers.

int checkPrime(int num);
char* isPrime(int check);

int main(void) {
	
	int num;	

	printf("Enter a number: ");
	scanf("%d", &num);
	printf("%d %s.\n", num, isPrime(checkPrime(num)));

	return 0;
}

	int checkPrime(int num) {
		if (num <= 1) {
			return 0;
		}
		for (int i=2;i<num/2;i++) {
			if (num % i == 0) {
				return 0;
			}
		}
		return 1;	
	}

	char* isPrime(int check) {
		if (check == 1) {
			return "is prime";
		}
		else {
			return "is not prime";
		}
	}


