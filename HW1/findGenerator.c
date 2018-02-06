#include<stdio.h>
#include<math.h>

// The program will not function properly if you 
// enter a number greater than the largest int
// possible, 2147483647. Other than that, it 
// will function properly without any sort of 
// lag or 'hang' due to computational load.

int findGen(int num);

int p;

int main(void) {
	printf("Enter a prime number: "); 
	scanf("%d", &p);
	printf("%d is a generator of Z_%d.\n", findGen(p), p);
}

int findGen(int num) {
	for (int j=1;j<=p-1;j++) {
		for (int i=1;i<p-1;i++) {
			if (pow((double)j,(double)i) != 1) {
				return j;
			}
		}
	}
}
