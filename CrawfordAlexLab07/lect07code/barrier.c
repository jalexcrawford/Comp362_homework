#define _XOPEN_SOURCE 600

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int numberOfIterations;
int sleepCeiling;

// barrier variable
pthread_barrier_t barr;

void *buzzer(void *param)
{
	int thread_number = (int) (long) param;
	int sleep_time;
	int rc;
	for (int i = 0; i < numberOfIterations; i++)
	{
		// synchronization point for group initiation of buzzing
		rc = pthread_barrier_wait(&barr);

		if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
		{
			printf("Could not wait on barrier\n");
			exit(-1);
		}

		printf("%sThis %d (tid: %ld) buzzer STARTED buzziing for %d seconds :-)\n",
		       (rc != 0 ? "ALL BUZZERS READY TO START BUZZING!\n" : ""),
		       thread_number,
		       (long) pthread_self(),
		       sleep_time);
		fflush(stdout);

		// simuate some work to do with random time need
		sleep_time = random() % sleepCeiling;
		sleep(sleep_time);

		// synchronization point for group termination of buzzing
		rc = pthread_barrier_wait(&barr);

		if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
		{
			printf("Could not wait on barrier\n");
			exit(-1);
		}

		printf("%sThis %d (tid: %ld) buzzer STOPPED buzziing :-)\n",
		       (rc != 0 ? "ALL BUZZERS DONE BUZZING FOR NOW!\n" : ""),
		       thread_number,
		       (long) pthread_self());
		fflush(stdout);
	}

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		fprintf(stderr, "Usage: barrier numberOfBuzzers numberOfIterations sleepCeiling\n");
		exit(EXIT_FAILURE);
	}

	// length of the simulation in seconds
	int numberOfBuzzers = strtol(argv[1], NULL, 10);

	// max iterations in bees
	numberOfIterations = strtol(argv[2], NULL, 10);

	// max sleep length for bees
	sleepCeiling = strtol(argv[3], NULL, 10);

	// initialize the semaphore
	srandom(time(NULL));

	pthread_t buzzers[numberOfBuzzers];

	// barrier initialization
	if (pthread_barrier_init(&barr, NULL, numberOfBuzzers))
	{
		printf("Could not create a barrier\n");
		return -1;
	}

	for (int i = 0; i < numberOfBuzzers; ++i)
	{
		if (pthread_create(&buzzers[i], NULL, &buzzer, (void *) (long) i))
		{
			printf("Could not create thread %d\n", i);
			return -1;
		}
	}

	printf("MAIN WAITING FOR ALL BUZZERS TO JOIN IT\n");
	fflush(stdout);

	for (int i = 0; i < numberOfBuzzers; ++i)
	{
		if (pthread_join(buzzers[i], NULL))
		{
			printf("Could not join thread %d\n", i);
			return -1;
		}
	}
	printf("JOINING DONE\n");
	fflush(stdout);

	exit(EXIT_SUCCESS);
}
