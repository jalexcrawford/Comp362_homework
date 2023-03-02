#include "matrixMult.h"

int main(int argc, char *argv[])
{
   //Overwrite stdin to read from the input file
   if (freopen(argv[1], "r", stdin) == 0){
      oops("Cannot open the input file.\n", -1);
   }

   int **a1, **b1, **c1, **a2, **b2, **c2; // matrices
   int m1, k1, n1, m2, k2, n2; // dimensions of the matices m x k and k x n

   allocateAndLoadMatrices(&a1, &b1, &c1, &m1, &k1, &n1);
   allocateAndLoadMatrices(&a2, &b2, &c2, &m2, &k2, &n2);

   // the real magic happens in there

   // TODO: implement

   // dispaly results of matrix multiplication

   printf("\nMATRIX A1\n");
   displayMatrix(a1, m1, k1);
   freeMatrix(a1, m1);
   printf("\nMATRIX B1\n");
   displayMatrix(b1, k1, n1);
   freeMatrix(b1, k1);
   printf("\nMATRIX A1 x B1\n");
   displayMatrix(c1, m1, n1);
   freeMatrix(c1, m1);

   printf("\nMATRIX A2\n");
   displayMatrix(a2, m2, k2);
   freeMatrix(a2, m2);
   printf("\nMATRIX B2\n");
   displayMatrix(b2, k2, n2);
   freeMatrix(b2, k2);
   printf("\nMATRIX A2 x B2\n");
   displayMatrix(c2, m2, n2);
   freeMatrix(c2, m2);

   return 0;
}

void allocateAndLoadMatrices(int ***a, int ***b, int ***c, int *m, int *k, int *n)
// takes pointers to two-dimensional matrices, so they can be allocated in here
// and used by the caller
{
   //Use scanf because stdin has been overwritten and will read from the input file.
   if (scanf("%d %d %d", m, k, n) == 0)
      oops("Cannot read matrix sizes.\n", -2);
   //Allocate m * k array
   int* ptrA = malloc(((*m) * (*k)) * sizeof(int*));
   *a = ptrA;
   for(int i = 0; i< (*m); i++){
      for(int j = 0; j < (*k); j++){
         (*a)[i][j] = malloc(sizeof(int));
      }
   }
   //Load matrix A into m * k array
   loadMatrix(a, *m, *k); //m is rows for A and k is columns

   //Allocate n * k array
   int* ptrB = malloc(((*n) * (*k)) * sizeof(int*));
   *b = ptrB;
   for(int i = 0; i< (*m); i++){
      for(int j = 0; j < (*k); j++){
         (*b)[i][j] = malloc(sizeof(int));
      }
   }
   //Load matrix B into n * k array
   loadMatrix(b, *k, *n); //k is rows for B and n is columns

   //Allocate m * n array for result matirx
   int* ptrC = malloc(((*m) * (*n)) * sizeof(int*));
   *c = ptrC;
   for(int i = 0; i< (*m); i++){
      for(int j = 0; j < (*n); j++){
         (*c)[i][j] = malloc(sizeof(int));
      }
   }   
   //Do not need to load C because that's the result and will be loaded in multiplication

}

//Take in a reference to a matrix, number of rows and colums. It then opens in.txt with read persmissions.
//Then it loops over row and columns and reads in an int to the location in the matrix.
void loadMatrix(int ***matrix, int r, int c)
{
   //loop over the rows then the columns of the matrix to load.
   for(int i = 0; i<r; i++){
      for(int j = 0; i < c; j++){
            (*matrix)[i][j] = scanf("%d");      
      }
   } 
}

pthread_t **multiply(int **a, int **b, int **c, int m, int k, int n)
{
   pthread_t **tids = alloc_tids(m, n);

   // TODO: implement WITH ALL THE MAGIC BECAUSE THIS TASK IS SO WELL DEFINED...
   //also it doesn't follow the official pthreads examples. #staySalty
   
   return tids;
}

pthread_t **alloc_tids(int m, int n)
{
   pthread_t **tids;

   // TODO: implement

   return tids;
}

void *matrixThread(void *param)
{
   // map the parameter onto the structure
   MATRIX_CELL *cell = (MATRIX_CELL *)param;

   // TODO: implement

   free(cell);

   return NULL;
}

void free_tids(pthread_t **tids, int m)
{
   // TODO: implement 
}

void join(pthread_t **tids, int m, int n)
{
   // TODO: implement
}
void displayMatrix(int **matrix, int r, int c)
{
   for(int i = 0; i < r; i++){
      for(int j = 0; j < c; j++){
         printf("%d\t", matrix[i][j]);
      }
   }
}

//Loop over each row of the matrix and free stuff, but it doesn't go over all of the cells because 
//only the number of rows is called for some reson.
void freeMatrix(int **matrix, int r)
{
   for(int i = 0; i < r; i++){
      free(matrix[i][0]);
   }
   free(matrix);
}
