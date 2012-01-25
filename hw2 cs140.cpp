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

  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
      tempMatrix[(i*size)+j] = 0;
    for(int k = 0; k <= i; k++)
      tempMatrix[(i*size)+k] = i+1;
  }

  int offset = ((size*size)/nprocs)*rank;
  for(int i = 0; i < (size*size)/nprocs; i++)
    mat[i] = tempMatrix[i+offset];
}

// Subroutine to generate a random vector
void generatevec(double * x,int size)
{
  for(int i = 0; i < size; i++)
    x[i] = 1;
}

double norm2(double *vector, int size)
{
  double total = 0;
  for(int i = 0; i < size; i++)
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



  double temp[mSize*mSize];

  for(int i = 0; i < nprocs;i++)
    MPI_Gather(matrix, (mSize*mSize)/nprocs, MPI_DOUBLE, temp ,(mSize*mSize)/nprocs, MPI_DOUBLE,i, MPI_COMM_WORLD);


 double *newVec = (double*)malloc(sizeof(double)*mSize);
  for(int i = 0; i < mSize; i++)
    newVec[i] = 0;
  for(int i = 0; i < mSize; i++)
    {
      for(int j = 0; j < vSize; j++)
        {
          newVec[i] += temp[(i*mSize)+j] * vector[j];
        }
    }
  for(int i = 0; i < mSize; i++)
    result[i] = newVec[i];
  free(newVec);
}


double powerMethod(double * mat, double * x, int size, int iter)
{
  double newX[size];
  for(int i = 0; i < iter; i++)
    {
      for(int j = 0; j < size; j++)
        {
          x[j] = x[j] / norm2(x, size);

        }
      matVec(mat, x, size, size, x);
    }
