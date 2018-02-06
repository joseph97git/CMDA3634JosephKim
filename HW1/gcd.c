#include<stdio.h>
#include<stdlib.h>

// The program will not function properly if you 
// enter a number greater than the largest int
// possible, 2147483647. Other than that, it 
// will function properly without any sort of 
// lag or 'hang' due to computational load.

int gcd(int a, int b);

int main(void) {
	int a,b;

	printf("Enter the first number: ");
	scanf("%d", &a);
	printf("Enter the second number: ");
	scanf("%d", &b);
	printf("The greatest common divisor of %d and %d is %d.\n", a, b, gcd(a,b));
	return 0;
}

int gcd(int a, int b) {
	if (b % a == 0) {
		return abs(a);
	}
	else {
		return gcd(b % a, a);
	}
}	
