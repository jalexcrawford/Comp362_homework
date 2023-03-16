// AJ Bieszczad - 10/21/2018

#include "deadlock.h"

bool deadlockDetected = false; // support for recursive detection of multiple cycles

int main(int argc, char **argv)
{
    freopen(argv[1], "r", stdin);

    char inputBuffer[MAX_LINE_LENGTH];

    WAIT_FOR_GRAPH waitForGraph;

    waitForGraph.numberOfProcesses = 0;

    scanf(" %[^\n]\n", inputBuffer);
    fprintf(stderr, "VERTICES: %s\n", inputBuffer);
    loadProcesses(inputBuffer, &waitForGraph);

    scanf(" %[^\n]\n", inputBuffer);
    fprintf(stderr, "EDGES: %s\n", inputBuffer);
    loadDependencies(inputBuffer, &waitForGraph);

    printTable(&waitForGraph);

    for (int i = 0; i < waitForGraph.numberOfProcesses; i++)
        if (waitForGraph.dependencies[i][waitForGraph.numberOfProcesses + 1] == '0')
            detectDeadlocks(&waitForGraph, i, NULL);

    if (!deadlockDetected)
        printf("\nNO DEADLOCK!\n");
}

//
// Read vertices from the input, construct and array of their names, and count them
//
// Expecting: V={<node 1>, <node 2>, ..., <node n>}
// For example: V={Aa, Bbb, Cccc, Ddddd}
//
void loadProcesses(char *inputBuffer, WAIT_FOR_GRAPH *graph)
{
    if (*inputBuffer != 'V')
    {
        printf("INCORRECT INPUT!\n");
        exit(EXIT_FAILURE);
    }

    graph->numberOfProcesses = 0;

    char *delim = " ={},";
    char *rest = strdup(inputBuffer);
    char *next = NULL;
    strsep(&rest, delim);
    while (rest != NULL)
    {
        next = strsep(&rest, delim);
        if (*next != '\0')
        {
            graph->processes[graph->numberOfProcesses] = next;
            graph->numberOfProcesses++;
        }
    }
}

//
// Read dependencies and construct an adjacency table for the graph
//
// Expecting: E={{<node k1>, <node k2>}, {<node k3>, <node k4>}, ..., {<node k5>, <node k6>}}
// For example: E={{Aa, Cccc}, {Aa, Ddddd}, {Bbb, Cccc}, {Cccc, Bbb}, {Cccc, Ddddd}, {Ddddd, Aa}, {Ddddd, Cccc}}
//
// This input will yield the following packed (char**) adjacency table:
//    0011
//    0010
//    0101
//    1010
//
void loadDependencies(char *inputBuffer, WAIT_FOR_GRAPH *graph)
{
    if (*inputBuffer != 'E')
    {
        printf("INCORRECT INPUT!\n");
        exit(EXIT_FAILURE);
    }

    graph->dependencies = malloc(graph->numberOfProcesses * sizeof(char *));
    for (int i = 0; i < graph->numberOfProcesses; i++)
        graph->dependencies[i] = malloc((graph->numberOfProcesses + 2) * sizeof(char));

    for (int i = 0; i < graph->numberOfProcesses; i++)
        for (int j = 0; j < (graph->numberOfProcesses + 2); j++)
            graph->dependencies[i][j] = '0';

    char *delim = " ={},";
    char *rest = strdup(inputBuffer);
    char *next = NULL;
    strsep(&rest, delim);
    bool found;
    while (rest != NULL)
    {
        next = strsep(&rest, delim);
        if (*next != '\0')
        {
            found = false;
            for (int i = 0; i < graph->numberOfProcesses && !found; i++)
            {
                if (strcmp(next, graph->processes[i]) == 0)
                {
                    next = strsep(&rest, delim);
                    while (*next == '\0')
                    {
                        next = strsep(&rest, delim);
                    }
                    for (int j = 0; j < graph->numberOfProcesses && !found; j++)
                    {
                        if (strcmp(next, graph->processes[j]) == 0)
                        {
                            graph->dependencies[i][j] = '1';
                            found = true;
                        }
                    }
                }
            }
        }
    }
}

void detectDeadlocks(WAIT_FOR_GRAPH *graph, int currentNode, PROCESS *currentWaitForList) {
   // TODO: Search for cycles
}

void printTable(WAIT_FOR_GRAPH *graph) {
   // TODO: Print the adjacency matrix
}

void printCycle(PROCESS *list) {
   // TODO: Print the cycle found
}