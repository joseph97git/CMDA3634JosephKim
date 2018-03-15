#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <omp.h>

int main(int argc, char **argv) {

	//number of parallel threads that OpenMp should use
	int NumThreads = 100;

	//tell OpenMP to use NumThreads threads
	omp_set_num_threads(NumThreads);

	float *val = (float*) malloc(NumThreads*sizeof(float));	
	
	int winner = 0; 
	float sum = 0;

	//fork into a parallel region, declare shared variables;
	#pragma omp parallel shared(val,winner) reduction(+:sum)
	{
		//varaiables declared inside a parallel region are PRIVATE 
		int rank = omp_get_thread_num(); //thread's rank
		int size = omp_get_num_threads(); //total number of threads

		printf("Hello World from thread %d of %d \n", rank, size);
		
		val[rank] = (float) rank;
		
		#pragma omp for	
		for (int n=1;n<10000;n++) {
			sum += 1/(float) n;
		}

		//this is bad. We've made a 'data race'
		//we can find it using the master region
		#pragma omp master
		{
			winner = rank;
		}
		//we can safely do this with a critical region
		//#pragma omp critical
		//{
		//	sum += rank;
		//}

		//a better way is to tell OpenMP that we want that variable reduced
		sum += (float)rank;
	}
	//merge back to serial

	for (int n=0;n<NumThreads;n++) 
		printf("val[%d] = %f \n", n, val[n]);

	printf("The winner was %d\n", winner);
	printf("The sum was %f\n", sum);

	return 0;

}
