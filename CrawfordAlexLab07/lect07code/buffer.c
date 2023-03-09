#include "buffer.h"

// a buffer to hold items
BUFFER_ITEM *buffer;
int bufferSize;

// a lock to protect the the buffer
pthread_mutex_t mutex;

// counting semaphores
sem_t empty;
sem_t full;

int insertPointer = 0, removePointer = 0;

int main(int argc, char *argv[])
{
   if (argc < 7)
   {
      fprintf(stderr, "Usage: buffer simulationLength producerThreads consumerThreads bufferSize producerSleepCeiling consumerSleepCeiling");
      exit(EXIT_FAILURE);
   }

   // length of the simulation in seconds
   int simulationLength = strtol(argv[1], NULL, 10);

   // number of threads
   int producerThreads = strtol(argv[2], NULL, 10);
   int consumerThreads = strtol(argv[3], NULL, 10);

   // size of the buffer
   bufferSize = strtol(argv[4], NULL, 10);
   buffer = malloc(bufferSize * sizeof(BUFFER_ITEM));

   long producerSleepCeiling = strtol(argv[5], NULL, 10);
   long consumerSleepCeiling = strtol(argv[6], NULL, 10);

   // initialize the the critical section lock
   pthread_mutex_init(&mutex, NULL);

   // initialize the counting semphors
   sem_init(&empty, 0, bufferSize);
   sem_init(&full, 0, 0);

   srandom(time(0));

   // create the producer and consumer threads

   pthread_t tid;

   while (producerThreads-- > 0)
      pthread_create(&tid, NULL, producer, (void*) producerSleepCeiling);

   while (consumerThreads-- > 0)
      pthread_create(&tid, NULL, consumer, (void*) consumerSleepCeiling);

   // sleep for user specified time
   sleep(simulationLength);

   exit(EXIT_SUCCESS);
}

void *producer(void *param)
{
   BUFFER_ITEM rand;

   while (true)
   {
      sleep(random() % (long)param);

      produce((rand = random()));
   }
}

void *consumer(void *param)
{
   BUFFER_ITEM rand;

   while (true)
   {
      sleep(random() % (long)param);

      consume(&rand);
   }
}

void produce(BUFFER_ITEM item)
{
   // wait if the buffer is empty
   sem_wait(&empty);

   // enter critical section
   pthread_mutex_lock(&mutex);

   buffer[insertPointer++] = item;
   insertPointer = insertPointer % bufferSize;

   printf("Producer %lx produced %d to slot %d \n", pthread_self(), item, insertPointer);
   fflush(stdout);

   // exit critical section
   pthread_mutex_unlock(&mutex);

   // signal the removal of an item from the buffer
   sem_post(&full);
}

void consume(BUFFER_ITEM *item)
{
   // wait if the buffer is full
   sem_wait(&full);

   // exter critical section
   pthread_mutex_lock(&mutex);

   *item = buffer[removePointer];
   buffer[removePointer++] = EMPTY_SLOT;
   removePointer = removePointer % bufferSize;

   printf("Consumer %lx consumed %d from slot %d \n", pthread_self(), *item, removePointer);
   fflush(stdout);

   // exit critical section
   pthread_mutex_unlock(&mutex);

   // signal the addition to the buffer
   sem_post(&empty);
}

