#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 16
#define MAX_NUM_OF_PROCESSES 16

typedef struct waitForGraph {
    int numberOfProcesses;
    char *processes[MAX_NUM_OF_PROCESSES];
    char **dependencies; // encoded with '0' and '1'; two extra columns for "visited' and 'processed'
} WAIT_FOR_GRAPH;

typedef struct process
{
    char *processName;
    struct process *next;
} PROCESS;

void loadProcesses(char *inputBuffer, WAIT_FOR_GRAPH *graph);
void loadDependencies(char *inputBuffer, WAIT_FOR_GRAPH *graph);
void detectDeadlocks(WAIT_FOR_GRAPH *graph, int currentNode, PROCESS *currentWaitForList);
void printTable(WAIT_FOR_GRAPH *graph);
void printCycle(PROCESS *list);