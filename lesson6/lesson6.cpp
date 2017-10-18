#include "mathhelpers.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>

Matrix initMatrix ( int n ) {
    Matrix result;
    for ( int i = 0; i< n; i++ ) {
        Vector vector;
        for ( int i = 0; i< n; i++ ) {
            vector.push_back ( 0.0 );
        }
        result.push_back ( vector );
    }
    return result;
}

int main(){
  //Langrans
  int n;
  double y;
  std::cin >> n;
  
  Vector X = readVector(n);
  Vector FVector = readVector(n);
//    print(X);
  std::cin >> y;
  
   Matrix F = initMatrix(n);
  
   for(int i = 0; i < n; i++){
    F[i][0] = FVector[i];
   }
//    print(F);
  
    for(int k = 1; k < n; k++){
       for(int i = k; i < n; i++){
 	F[i][k] = (F[i][k-1] - F[i-1][k-1]) / (X[i] - X[i-k]);
       }
   }
   
   for(int i = 0; i < n; i++){
    FVector[i] = F[i][i];
   }
   
   print(FVector);
   double sum = 0;
   for(int i = 0; i<n;i++){
     double multiply = 1.0;
     for(int j = 0; j < i; j++){
       multiply *= y-X[j]; 
    }
    multiply *= FVector[i];
    sum += multiply;
  }
//    double c = FVector[0];
//    for(int k = 1;k < n; k++){
//      c = c * (y - X[n-k]) + FVector[n-k];
//   }
  std::cout <<std::endl;
  std::cout << sum <<std::endl;
  
  return 0;
}

