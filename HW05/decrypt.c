#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"


int main (int argc, char **argv) {
  
  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */
    
  FILE * f;
  f = fopen("public_key.txt","r");
  
  // read in n,p,g,h
  fscanf(f,"%d",&n);
  fscanf(f,"%d",&p);
  fscanf(f,"%d",&g);
  fscanf(f,"%d",&h);
  fclose(f);
  
  FILE * of;
  of = fopen("message.txt","r");
  
  // read in Nints;
  fscanf(of,"%d",&Nints);

  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }

  /* Q3 After finding the secret key, decrypt the message */
  
    //storage for message as elements of Z_p
  unsigned int *Zmessage = 
      (unsigned int *) malloc(Nints*sizeof(unsigned int)); 
  
  //storage for extra encryption coefficient 
  unsigned int *a = 
      (unsigned int *) malloc(Nints*sizeof(unsigned int)); 
      
  for (int i=0;i<Nints;i++) {
	  fscanf(of,"%d %d", &Zmessage[i], &a[i]);
  }
  fclose(of);
  
  ElGamalDecrypt(Zmessage,a,Nints,p,x);
  
  unsigned int charsPerInt = (n-1)/8;
  unsigned int Nchars = Nints * charsPerInt;
  
  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
  
  convertZToString(Zmessage, Nints, message, Nchars);

  printf("Decrypted Message = \"%s\"\n", message);
  printf("\n");
  
  return 0;
}
