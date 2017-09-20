#include "mathhelpers.h"

int main(){
  
      int n,m,k;
  
  
  std::cin >> n;
  std::cin >> m;
  
  Matrix matrix;
  Matrix matrix2;
  Vector vector;
  matrix = readMatrix(n, m);
  print(matrix);
  
  return 0;
}