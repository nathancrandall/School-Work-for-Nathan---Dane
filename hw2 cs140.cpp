#include <iostream>
#include <cmath>

using namespace std;

void generatematrix(double * mat, int size)
{  
  for(int i = 0; i < size; i++)
  {
          for(int j = 0; j < size; j++)
          {
                  mat[(i*size)+j] = 0;
          }
          for(int k = 0; k <= i; k++)
          {
                  mat[(i*size)+k] = i+1;  
          }
  }
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
  if(mSize != vSize)
  {
    printf("cannot multiply together.\n");
    return;
  }
  double *newVec = new double[mSize];
  for(int i = 0; i < mSize; i++)
          newVec[i] = 0;
  for(int i = 0; i < mSize; i++)
  {
    for(int j = 0; j < vSize; j++)
    {
      newVec[i] += matrix[(i*mSize)+j] * vector[j];
    }
  }
  for(int i = 0; i < mSize; i++)
          result[i] = newVec[i];
  delete [] newVec;
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

  return norm2(x, size);
}


int main()
{
    double matrix[36] = {1,0,0,0,0,0,2,2,0,0,0,0,3,3,3,0,0,0,4,4,4,4,0,0,5,5,5,5,5,0,6,6,6,6,6,6};
    double vec[6];
    double spectral_radius;
    int size = 6;
    int iter = 1000;
    
    //generatematrix(matrix, 4);
    generatevec(vec, 6);
    
    
    spectral_radius = powerMethod(matrix,vec,size,iter);
    
    cout << "spectral radius = " << spectral_radius << endl;
    
    
    
    system("PAUSE");
    return 0;
}
