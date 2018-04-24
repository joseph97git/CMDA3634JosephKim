#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void padString(unsigned char* string, unsigned int charsPerInt);
void convertStringToZ(unsigned char *string, unsigned int Nchars,
                      unsigned int  *Z, unsigned int Nints);
void convertZToString(unsigned int  *Z, unsigned int Nints,
                      unsigned char *string, unsigned int Nchars);

int main(void) {

  unsigned int n;
  printf("Enter a number of bits: "); fflush(stdout);
  char status = scanf("%u",&n);

  //make sure the input makes sense
  if ((n<8)||(n>31)) {//Updated bounds. 8 is no good (need to encode chars)
  	printf("Unsupported bit size.\n");
		return 0;  	
  }
  printf("\n");

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  //populate the string with a message
  strcpy(message, "ABCDE");
  printf("Message = \"%s\"\n", message);
  int len = strlen(message);
  printf("The length of the messsage is: %d\n", len);

  /* Q1.1 Finish this line   */
  unsigned int charsPerInt = (n-1)/8;

  padString(message, charsPerInt);
  printf("The charsPerInt is: %u\n", charsPerInt);
  printf("Padded Message = \"%s\"\n", message);
  int new = strlen(message);
  printf("The new length of the message is: %d\n", new);

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
  
  printf("The encoded msg is: ");
  for (int i=0;i<Nints;i++) {
	  printf("%u ", Zmessage[i]);
  }
  printf("\n");
  
  convertZToString(Zmessage, Nints, message, Nchars);

 
  printf("\"%s\"", message);
  
  printf("\n");
  
  return 0;

} 

//Pad the end of string so its length is divisible by charsPerInt
// Assume there is enough allocated storage for the padded string 
void padString(unsigned char* string, unsigned int charsPerInt) {

  /* Q1.2 Complete this function   */
  unsigned char* str = string;
  while(strlen(string) % charsPerInt != 0) {
	  unsigned int len = strlen(string);
	  str[len]=' ';
	  str[len + 1] = '\0';
  }
}

void convertStringToZ(unsigned char *string, unsigned int Nchars,
                      unsigned int  *Z,      unsigned int Nints) {

  /* Q1.3 Complete this function   */
  /* Q2.2 Parallelize this function with OpenMP   */
  unsigned char *str = string;
  unsigned int *num = Z;
  unsigned int charsPerInt = Nchars / Nints;
  for (int i=0;i<Nints;i++) {
	 unsigned int shift = Nchars / Nints;
	 char tmp_a = *str;
	 unsigned int a = (unsigned int) tmp_a;
	 unsigned int s_a = a << (8 * (shift-1));
	 for (int j=0;j<charsPerInt-1;j++) {
		 shift--;
		 str += 1;
		 char tmp_b = *str;
		 unsigned int b = (unsigned int) tmp_b;
		 unsigned int s_b = b << (8 * (shift-1));
		 s_a = s_a | s_b;
	 }
     *num = s_a;
     num += 1;
     str += 1;
  }
}

void convertZToString(unsigned int  *Z,      unsigned int Nints,
                      unsigned char *string, unsigned int Nchars) {

  /* Q1.4 Complete this function   */
  /* Q2.2 Parallelize this function with OpenMP   */
  unsigned int *num = Z;
  unsigned char *str = string;
  unsigned int charsPerInt = Nchars / Nints;
  printf("The number of charsPerInt is: %u\n", charsPerInt);
  printf("The number of ints are: %u\n", Nints);
  for (int i=0;i<Nints; i++) {
	  unsigned int shiftFactor = Nchars / Nints;
	  unsigned int p = *num;
	  for (int j=0;j<charsPerInt;j++) {
		  unsigned int mask = 0x000000FF << (8 * (shiftFactor-1));
		  unsigned char tmp_p = (p & mask) >> (8 * (shiftFactor-1));
		  printf("%c",tmp_p);
		  *str = tmp_p;
		  str += 1;
		  shiftFactor--;
	  }
	  num += 1;
  }
}

