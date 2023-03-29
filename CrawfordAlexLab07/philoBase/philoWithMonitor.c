#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

//random amount of time (cycle of pickup/eat/put down chopstick)
#define SLEEP_TIME ( (rand() % 5 + 1) * 1000)

//enumerate states
enum STATE {THINKING, HUNGRY, EATING}; 
enum STATE* state;

//pointer to a function that is executed by every thread (philosopher)
void *philosopher(void *id);

//pick up chopsticks #howYOUdoin'
void pickup(void* id);

//put down chopstick
void putdown(void* id);

//check if a chopstick in use
void test(void* id);

//array holding IDs of chopsticks and wait signals for each chopstic
pthread_mutex_t *chopstick;
pthread_cond_t *cond;

int numOfSeats, numOfTurns;

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: philosophers <number of seats> <number of turns>");
        return 1;
    }
    
    numOfSeats = strtod(argv[1], NULL);
    numOfTurns = strtod(argv[2], NULL);

    chopstick = calloc(numOfSeats, sizeof(pthread_mutex_t));
    cond = calloc(numOfSeats, sizeof(pthread_cond_t));

    state = malloc(sizeof(enum STATE) * numOfSeats);


    // set the seed for random number generator
    srand(time(NULL));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("Start a dinner for %d diners\n", numOfSeats);

    pthread_t philosopher_tid[numOfSeats];

    long i;
    //initialize chopsticks
    for (i = 0; i < numOfSeats; i++){
        pthread_mutex_init(chopstick + i, NULL);
        pthread_cond_init(cond + i, NULL);
    }

    //create philosophers
    for (i = 0; i < numOfSeats; i++){
        pthread_create(&philosopher_tid[i], NULL, philosopher, (void *) i);
        state[i] = THINKING;
    }

    //wait for philosophers to finish
    for (i = 0; i < numOfSeats; i++)
        pthread_join(philosopher_tid[i], NULL);

    //destroy chopsticks
    for (i = 0; i < numOfSeats; i++)
        pthread_mutex_destroy(chopstick + i);

    printf("Dinner is no more.\n");

    return 0;
}

void *philosopher(void *num)
{
    int id = (long) num;

    printf("Philsopher no. %d sits at the table.\n", id);
    // philosophers arrive at the table at various times
    usleep(SLEEP_TIME);

    int i;
    for (i = 0; i < numOfTurns; i++)
    {
        pickup(num);
        printf("Phlisopher %d is eating for time #%d.\n", id,i);
        putdown(num);
    }

    printf(">>>>>> Philsopher no. %d finished meal. <<<<<<\n", id);

    pthread_exit(NULL);
}

void pickup(void* id){
    state[(int) id] = HUNGRY;
    test(id);
    if(state[(int) id] != EATING){
        pthread_cond_wait(&cond[(int)id], &chopstick[ (int) id]);
    }

}

void putdown(void* id){
    state[(int) id] = THINKING;
    test(id);
}

void test(void* id){
    int leftHand = (numOfSeats + (int) id + 1) % numOfSeats;
    int rightHand = (numOfSeats + (int) id - 1) % numOfSeats;
    if(state[(int) id] == HUNGRY){
        if(state[leftHand] != EATING){
            if(state[rightHand] != EATING){
                state[(int) id] = EATING;
                pthread_cond_signal(&cond[(int) id]);
            }
        }
    }else if(state[(int) id] == THINKING){
        if(state[leftHand] == HUNGRY){
            pthread_cond_signal(&cond[leftHand]);
        }
        if(state[rightHand] == HUNGRY){
            pthread_cond_signal(&cond[rightHand]);
        }
    }
}
