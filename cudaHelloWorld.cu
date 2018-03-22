#include <std.io>
#include <stdlib.h>

#include "cuda.h"

// This is my DEVICE function 
// __global__ mean this function is visible to the host
__global__ void kernelHelloWorld() {
  
  print("Hello World!\n");

}

int main(int argc, char** argv) {

  int Nblocks = 10; //number of blocks
  int Nthreads = 3; //number of threads per block

  // run the function 'kernelHellowWorld' on the DEVICE
  kernelHelloWorld <<< Nblocks, Nthreads >>> ();


}
