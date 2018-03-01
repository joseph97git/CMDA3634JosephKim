#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed;
  
  seed = clock(); //this will make your program run differently everytime
  //seed = 0; //uncomment this and you program will behave the same everytime it's run
  
  srand48(seed);


  //begin by getting user's input
	unsigned int n;

  printf("Enter a number of bits: ");
  scanf("%u",&n);

  //make sure the input makes sense
  if ((n<2)||(n>30)) {
  	printf("Unsupported bit size.\n");
		return 0;  	
  }
  // *** 2 bit input *** //
  /* 
   * If there is a 2 bit input, then the only possible binary representations
   * are 00, 01, 10, and 11, that is 0, 1, 2, and 3. Thus, it is impossible to
   * find a p and q to satisfy the conditions in Q3.2 (i.e. p=3, q=1 doesn't
   * work as 1 is not prime, 2 doesn't work either). 
   * 
   * My code with enter an infinite loop when evaluating isProbablyPrime(q)
   * when q is 1, after entering 2 for the number of bits. Nowhere was it
   * specified how to handle this, and the if statement above that checks
   * to make sure the input makes sense allows for n = 2, so I'm just 
   * assuming allowing n = 2 is intentional, or I'm just wrong (which is
   * a definite possibility).   
   * */
  int p = randXbitInt(n);

  /* Q2.2: Use isProbablyPrime and randomXbitInt to find a random n-bit prime number */

	while (isProbablyPrime(p)==0) {
		p = randXbitInt(n);
	}	

  printf("p = %u is probably prime.\n", p);

  /* Q3.2: Use isProbablyPrime and randomXbitInt to find a new random n-bit prime number 
     which satisfies p=2*q+1 where q is also prime */
	int q;
	p = randXbitInt(n);
    q = (p-1)/2;
	while (isProbablyPrime(p)==0 || isProbablyPrime(q)==0) {
		p = randXbitInt(n);
		q = (p-1)/2;
	}
	

	printf("p = %u is probably prime and equals 2*q + 1. q= %u and is also probably prime.\n", p, q);  

	/* Q3.3: use the fact that p=2*q+1 to quickly find a generator */
	unsigned int g = findGenerator(p);

	printf("g = %u is a generator of Z_%u \n", g, p);  
	
	/* BONUS */
	unsigned int x = rand() % p;
	unsigned int h = 1; 
	
	while (x < 0 || x > (p-1)) { //find random x
		x = rand() % p;
	}
	for (int j=0;j<x;j++) { //compute h = g^x
		h = h*g;
	}
	
	printf("Given g = %u and x = %u, h = g^x = %u \n", g, x, h); 
	
	int xguess;
	int gpow = 1;
	for (int i=1;i<=(p-1);i++) { //compute g = g^s 
		gpow = 1;
		for (int s=0;s<i;s++) {
			gpow = g*gpow;
		}
		if (gpow == h) { 
			xguess = i;	
			break; 
		}
	}
	
	printf("Given g = %u and h = %u, x = %u \n", g, h, xguess);

  return 0;
}
