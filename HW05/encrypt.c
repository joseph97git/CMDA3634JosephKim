#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */
  FILE * f;
  f = fopen("public_key.txt","r");
  
  // read in n,p,g,h
  fscanf(f,"%d",&n);
  fscanf(f,"%d",&p);
  fscanf(f,"%d",&g);
  fscanf(f,"%d",&h);
  fclose(f);
  
  unsigned int charsPerInt = (n-1)/8;

  padString(message, charsPerInt);
  
  unsigned int Nchars = strlen(message);
  unsigned int Nints  = strlen(message)/charsPerInt;

  //storage for message as elements of Z_p
  unsigned int *Zmessage = 
      (unsigned int *) malloc(Nints*sizeof(unsigned int)); 
  
  //storage for extra encryption coefficient 
  unsigned int *a = 
      (unsigned int *) malloc(Nints*sizeof(unsigned int)); 

  // cast the string into an unsigned int array
  convertStringToZ(message, Nchars, Zmessage, Nints);
  
  //Encrypt the Zmessage with the ElGamal cyrptographic system
  ElGamalEncrypt(Zmessage,a,Nints,p,g,h);
  
  FILE * of;
  of = fopen("message.txt", "w");
  fprintf(of,"%d\n", Nints);
  for (int i=0;i<Nints;i++) {
	  fprintf(of,"%d %d\n", Zmessage[i], a[i]);
  }
  fclose(of);
  
  return 0;
}
