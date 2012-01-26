/* CS 140
 * Assignment 1 : Matrix Vector Multiplication and the Power Method
 * Group members : Nathan Crandall , Dane Pitkin
 * */

/* This file provides the placeholder function definitions, where you will be
 * implementing the assignment algorithms. You will be required to turn in
 * only this file during the submission, where it will be compiled together
 * with our main function and tested. It is therefore required that you keep the
 * function declaration formats unchanged.
 */


#include "powermethod.h"

void generatematrix(double * mat, int size)
{
  int nprocs, rank;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  int tempMatrix[size*size];

  int i, j, k;

  for(i = 0; i < size; i++)
  {
    for(j = 0; j < size; j++)
      tempMatrix[(i*size)+j] = 0;
    for(k = 0; k <= i; k++)
      tempMatrix[(i*size)+k] = i+1;
  }

  int offset = ((size*size)/nprocs)*rank;
  for(i = 0; i < (size*size)/nprocs; i++)
    mat[i] = tempMatrix[i+offset];
}

// Subroutine to generate a random vector
void generatevec(double * x,int size)
{
  int i;
  for(i = 0; i < size; i++)
    x[i] = 1;
}
double norm2(double *vector, int size)
{
  double total = 0;
  int i;
  for(i = 0; i < size; i++)
    {
      total += (vector[i] * vector[i]);
    }
  return sqrt(total);
}
void matVec(double *matrix, double *vector, int mSize, int vSize, double *result)
{
  int nprocs, rank;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);


  if(mSize != vSize)
  {
    printf("cannot multiply together.\n");
    return;
  }
  int i, j;
 double *newVec = (double*)malloc(sizeof(double)*mSize/nprocs);
  for(i = 0; i < mSize/nprocs; i++)
    newVec[i] = 0;
  for(i = 0; i < mSize/nprocs; i++)
    {
      for(j = 0; j < vSize; j++)
        {
          newVec[i] += matrix[(i*mSize)+j] * vector[j];
        }
    }

  for(i = 0; i < nprocs; i++)
  MPI_Gather(newVec, mSize/nprocs, MPI_DOUBLE, result ,mSize/nprocs, MPI_DOUBLE,i, MPI_COMM_WORLD);


  free(newVec);
}
double powerMethod(double * mat, double * x, int size, int iter)
{
  double newX[size];
  int i, j;
  for(i = 0; i < iter; i++)
    {
      for(j = 0; j < size; j++)
        {
          x[j] = x[j] / norm2(x, size);

        }
      matVec(mat, x, size, size, x);
    }
  return norm2(x, size);
}
