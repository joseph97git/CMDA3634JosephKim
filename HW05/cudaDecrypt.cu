
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"


//device functions

//compute a*b mod p safely
__device__ unsigned int kernelModProd(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int za = a;
  unsigned int ab = 0;

  while (b > 0) {
    if (b%2 == 1) ab = (ab +  za) % p;
    za = (2 * za) % p;
    b /= 2;
  }
  return ab;
}

//compute a^b mod p safely
__device__ unsigned int kernelModExp(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int z = a;
  unsigned int aExpb = 1;

  while (b > 0) {
    if (b%2 == 1) aExpb = kernelModProd(aExpb, z, p);
    z = kernelModProd(z, z, p);
    b /= 2;
  }
  return aExpb;
}


__global__ void kernelFindKey(unsigned int n, unsigned int p,
							  unsigned int g, unsigned int h,
							  unsigned int* x) {
	
	int threadid = threadIdx.x; //thread number
	int blockid = blockIdx.x; //block number
	int Nblock = blockDim.x; //number of threads in a block
	
	int id = threadid + blockid*Nblock;
	
	
	// find the secret key 
      if (kernelModExp(g,id+1,p)==h) {
        printf("Secret key found! x = %u \n", id+1);
        *x=id+1;
      } 

 
}



int main (int argc, char **argv) {

  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */
     
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

  
  /* Q4 Make the search for the secret key parallel on the GPU using CUDA. */

  //allocate storage on host
  unsigned int *h_result = (unsigned int *) malloc(sizeof(unsigned int));
 
  h_result[0] = x; //define h_result as the 
  
  //allocate storage on device
  unsigned int *d_result;
  cudaMalloc(&d_result, sizeof(unsigned int));
  
  //define thread and block size
  int Nthreads = 64;
  int Nblocks = (p+Nthreads-1)/Nthreads;
  
   if (x==0 || modExp(g,x,p)!=h) {
	   
	
    double startTime = clock();  
    printf("Finding the secret key...\n");
    kernelFindKey <<<Nblocks,Nthreads>>>(n,p,g,h,d_result);
  
    cudaDeviceSynchronize(); 
    double endTime = clock();
    
    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;
    
    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }  
  //copy answer from device back to the host
  cudaMemcpy(h_result,d_result,sizeof(double),cudaMemcpyDeviceToHost);
  x = h_result[0]; //redefine x 
  
  
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
  unsigned char *message = (unsigned char *) calloc(bufferSize,sizeof(unsigned char));
  
  convertZToString(Zmessage, Nints, message, Nchars);

  printf("Decrypted Message = \"%s\"\n", message);
  printf("\n");
  
  cudaFree(d_result);
  free(h_result);
  
  return 0;
}
