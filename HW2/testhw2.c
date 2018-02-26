#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int modprod(unsigned int a, unsigned int b, unsigned int p);

int main(void) {

	unsigned int a = 12;
	unsigned int b = 12;
	unsigned int p = 1;

	printf("The modprod for %d * %d mod %d is: %d\n",a,b,p,modprod(a,b,p));



	return 0;

}

//compute a*b mod p safely
unsigned int modprod(unsigned int a, unsigned int b, unsigned int p) {
  /* Q1.2: Complete this function */
    unsigned int za = a;
    unsigned int ab = 0;
    
	// find index for length binary
    int num = 0;
    int n = 0;
    while (num < b) { 
        num = (unsigned int)pow((double)2,(double)n);
        n++;
    } // end length binary

    for (int i=0;i<n-1;i++) { // length is index binary - 1
        int bi=b;
		
		// computing binary of position i 
        for (int j=n-2;j>=i+1;j--) {
            bi = bi % (unsigned int)pow((double)2,(double)j);
        }

		if ((unsigned int)pow((double)2,(double)i) > bi) {
			bi = 0;
		}
		else {
			bi = 1;
		} // end binary i 

		// applying safe computation with binary position i
        if (bi == 1) {
            ab = (ab + za*bi) % p;
        } 
        za = 2*za % p;  
		// end computation
    }

    return ab; 
}

