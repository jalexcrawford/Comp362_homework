#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

//random amount of time (cycle of pickup/eat/put down chopstick)
#define SLEEP_TIME ( (rand() % 5 + 1) * 1000)

//enumerate states
enum STATE {THINKING, HUNGRY, EATING}; 

//pointer to a function that is executed by every thread (philosopher)
void *philosopher(int *id);

//pick up chopsticks #howYOUdoin'
void* pickup(___int_size_t_h* id);

//put down chopstick
void* putdown(int* id);

//check if a chopstick in use
void* test(int* id);

//array holding IDs of chopsticks
pthread_mutex_t *chopstick;

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

    enum STATE state[numOfSeats];


    // set the seed for random number generator
    srand(time(NULL));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("Start a dinner for %d diners\n", numOfSeats);

    pthread_t philosopher_tid[numOfSeats];

    long i;
    //initialize chopsticks
    for (i = 0; i < numOfSeats; i++)
        pthread_mutex_init(chopstick + i, NULL);

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

void *philosopher(int *num)
{
    int id = (long) num;

    printf("Philsopher no. %d sits at the table.\n", id);
    // philosophers arrive at the table at various times
    usleep(SLEEP_TIME);

    int i;
    for (i = 0; i < numOfTurns; i++)
    {
        pickup(id);
        printf("Eating");
        putdown(id);
    }

    printf(">>>>>> Philsopher no. %d finished meal. <<<<<<\n", id);

    pthread_exit(NULL);
}

void *pickup(void* id){
    state[id] = HUNGRY;
    test(id);
    if(state[id] != EATING){
        pthread_cond_wait();
    }

}

void* test(void* id){
    void* leftHand = (numOfSeats + (int) id + 1) % numOfSeats;
    void* rightHand = (numOfSeats + (int) id - 1) % numOfSeats;
    if(state[*id] == HUNGRY){
        if(state[*leftHand] != EATING){
            if(state[*rightHand] != EATING){
                state[id] = EATING;
                pthread_cond_signal();
            }
        }
    }
}
