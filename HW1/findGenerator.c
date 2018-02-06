#include<stdio.h>
#include<math.h>

// The program will not function properly if you 
// enter a very large number. It will lag or 'hang' 
// for a very long time depending on the number you
// enter.

int findGen(int prime);
int checkGen(int num, int prime);

int p;

int main(void) {
	printf("Enter a prime number: "); 
	scanf("%d", &p);
	printf("%d is a generator of Z_%d.\n", findGen(p), p);
}

int findGen(int prime) {
	for (int j=1;j<=prime-1;j++) {
		if (checkGen(j,prime) == 1) {
			return j;
		}
	}
	return -1; //indicates there is an error
    		   //by definition there should exist
			   //at least one generator.
}

int checkGen(int num, int prime) {
	for (int i=1;i<prime-1;i++) {
			if ((int)pow((double)num,(double)i) % prime == 1) {
				return 0;
			}
		}
	return 1;
}

