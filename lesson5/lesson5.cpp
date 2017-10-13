#include "mathhelpers.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>

double sumVector(Vector vector){
  double sum = 0.0;
  for (int i = 0;i< vector.size();i++){
    sum += vector[i];
  }
  return sum;
}

double sum2Vector(Vector vector){
  double sum = 0.0;
  for (int i = 0;i< vector.size();i++){
    sum += pow(vector[i],2);
  }
  return sum;
}

double sum2Vectors(Vector vector1, Vector vector2){
  double sum = 0.0;
  for (int i = 0;i< vector1.size();i++){
    sum += vector1[i] * vector2[i];
  }
  return sum;
}

double det2(Matrix matrix){
  double det = 1.0;
  double tmp = 1.0;
  for (int i = 0; i< matrix.size();i++){
    det *= matrix[i][i];
  }
  tmp = matrix[0][1] * matrix[1][0];
  det -= tmp;
  return det;
}

Matrix helpInvers2(Matrix matrix){
  Matrix inversMatrix = matrix;
  inversMatrix[0][0] = matrix[1][1];
  inversMatrix[1][1] = matrix[0][0];
  inversMatrix[0][1] *= -1;
  inversMatrix[1][0] *= -1;
  return inversMatrix;
}

Vector calculateATF(Vector t, Vector f){
  Vector vector;
  vector.push_back(sumVector(f));
  vector.push_back(sum2Vectors(t, f));
  return vector;
}

int main(){
  
  int m;
  std::cin >> m;
  
  Vector t = readVector(m);
  Vector f = readVector(m);
  Matrix a;
  for (int i = 0; i< m;i++){
    Vector tmpVector;
    tmpVector.push_back(1);
    tmpVector.push_back(t[i]);
    a.push_back(tmpVector);
  }
  Matrix ata;
  for (int i= 0; i< 2;i++){
    Vector tmpVector;
    for (int j= 0; j< 2;j++){
      tmpVector.push_back(0);
    }
    ata.push_back(tmpVector);
  }
  ata[0][0] = m;
  ata[0][1] = sumVector(t);
  ata[1][0] = ata[0][1];
  ata[1][1] = sum2Vector(t);
  double det = 1.0/det2(ata);
  Matrix inversHelp = helpInvers2(ata);
  
  Vector atf = calculateATF(t, f);
  Vector result = multiply(inversHelp, atf);
  result[0] *= det;
  result[1] *= det;
  print(result);
  
  return 0;
}

