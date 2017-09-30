#include "mathhelpers.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>


Vector randomizeVector(int n){
  Vector vector;
  double number;
  for (int i = 0; i < n;i++){
    number = rand() % 9999 + 1;
    number /= 10000;
    vector.push_back(number);
  }
  return vector;
  
}


double infiniteVectorNorm(Vector vector, int n){

  double max = 0;
  for (int i = 0;i< n;i++){
    if (i == 0) {
      max == fabs(vector[i]);
    }else {
      if (max < fabs(vector[i])){
	max = fabs(vector[i]);
      }
    }
  }
  
  return max;
}

int main(){
  
  int n,m;
  std::cin >> n;
  std::cin >> m;
  Matrix vectorContainer, multipliedVectors;
  
  Matrix matrix;
  matrix = readMatrix(n,m);
  srand(time(NULL));
  int max = 0;
  for(int i = 0; i< 100000; i++){
    Vector vector;
    vector = randomizeVector(n);
    vectorContainer.push_back(vector);
    multipliedVectors.push_back(multiply(matrix, vector));
    if (max < (infiniteVectorNorm(multipliedVectors[i], n) / infiniteVectorNorm(vector, n))){
      max = (infiniteVectorNorm(multipliedVectors[i], n) / infiniteVectorNorm(vector, n));
    }
    
  }
  
  std::cout << max << std::endl;
  std::cout << rownormal(matrix, n,m);
  
  return 0;
}

