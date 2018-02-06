#include<stdio.h>
#include<stdlib.h>

// The program will not function properly if you 
// enter a number greater than the largest integer
// possible, 2147483647. It will also not 
// function properly if the product of the two
// numbers you entered is greater than the 
// largest possible integer. Other than that, it 
// will function properly without any sort of 
// lag or 'hang' due to computational load.


int gcd(int a, int b);
int lcm(int a, int b);

int main(void) {
	int a,b;

	printf("Enter the first number: ");
	scanf("%d", &a);
	printf("Enter the second number: ");
	scanf("%d", &b);
	printf("The least common multiple of %d and %d is %d.\n", a, b, lcm(a,b));
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

int lcm(int a, int b) {
	return (a * b) / gcd(a,b);
}
