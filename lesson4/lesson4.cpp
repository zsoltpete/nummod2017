#include "mathhelpers.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>

void csolesz(){
    int n;
  std::cin >> n;
  Matrix matrix;
  matrix = readMatrix(n, n);
  
  for(int k = 0; k<n;k++){
    if (matrix[k][k] < pow(10,-15)){
      std::cout << "Nem lehet gyököt vonni" << std::endl;
    }else{
      matrix[k][k] = sqrt(matrix[k][k]);
      for(int i = k + 1;i<n;i++){
	matrix[i][k] = matrix[i][k] / matrix[k][k];
	for(int j = k + 1; j < i + 1; j++){
	  matrix[i][j] = matrix[i][j] - (matrix[i][k] * matrix[j][k]);
	}
      }
    }
  }
  print(matrix);
}

void version1(){
       int n;
  std::cin >> n;
  Matrix matrix;
  matrix = readMatrix(n, n);
  Matrix copyMatrix;
  copyMatrix = matrix;
  Matrix egysegMatrix;
  egysegMatrix = readMatrix(n, n);
  Matrix result;
  result = readMatrix(n, n);
  for (int k = 0; k < n;k++){
    double divide = matrix[k][k];
    for(int i = k; i < n;i++){
      //std::cout << matrix[k][i] << matrix[k][k] << std::endl;
      matrix[k][i] = matrix[k][i] / divide;
      egysegMatrix[k][i] = egysegMatrix[k][i] / divide;
      //std::cout << matrix[k][i] << std::endl;
    }
    for(int j = 0; j < n;j++){
      if (j != k ) {
	for(int i = 0;i<n;i++){
	  matrix[j][i] = matrix[j][i] - matrix[k][i] * matrix[j][k];
	  egysegMatrix[j][i] = egysegMatrix[j][i] - matrix[k][i] * matrix[j][k];
	} 
      }
    }
  }
  print(matrix);
  print(egysegMatrix);
  print(multiply(egysegMatrix, copyMatrix));
}

int main(){
  
      int n;
  std::cin >> n;
  Matrix matrix;
  matrix = readMatrix(n, n);
  Matrix copyMatrix;
  copyMatrix = matrix;
  for (int k = 0; k < n;k++){
    double divide = matrix[k][k];
    for(int i = k; i < n;i++){
      //std::cout << matrix[k][i] << matrix[k][k] << std::endl;
      matrix[k][i] = matrix[k][i] / divide;
      egysegMatrix[k][i] = egysegMatrix[k][i] / divide;
      //std::cout << matrix[k][i] << std::endl;
    }
    for(int j = 0; j < n;j++){
      if (j != k ) {
	for(int i = 0;i<n;i++){
	  matrix[j][i] = matrix[j][i] - matrix[k][i] * matrix[j][k];
	  egysegMatrix[j][i] = egysegMatrix[j][i] - matrix[k][i] * matrix[j][k];
	} 
      }
    }
  }
  print(matrix);
  print(egysegMatrix);
  print(multiply(egysegMatrix, copyMatrix));
  return 0;
}

