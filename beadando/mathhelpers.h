#ifndef H___MATHHELPER
#define H___MATHHELPER

#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h> 
#include <iomanip>

typedef std::vector<std::vector<double> > Matrix;
typedef std::vector<double> Vector;

inline void print(Vector vector){
  for (int i = 0; i < vector.size(); i++){
    std::cout << std::fixed << std::setprecision(8) << vector[i] << " ";
  }
}

inline void print(Matrix matrix){
  for (int i = 0; i < matrix.size(); i++){
    Vector vector = matrix[i];
    for(int j = 0;j < vector.size();j++){
      std::cout << std::fixed << std::setprecision(8) << vector[j] << " "; }
    std::cout << std::endl;
  }
}

inline double rownormal(Matrix matrix, int n, int m){

  double max = 0;
  for (int i = 0;i<n;i++){
    Vector vector;
    double sum = 0;
    for (int j = 0;j < m;j++){
      sum += fabs(matrix[i][j]);
    }
    if (i == 0){
      max = sum;
    }else{
      if (max < sum){
	max = sum;
      }
    }
     
  }
  return max;
}

inline double colNormal(Matrix matrix, int n, int m){
    double max = 0;
    for (int i = 0;i<m;i++){
      std::vector<double> vector;
      double sum = 0;
      for (int j = 0;j < n;j++){
	sum += fabs(matrix[j][i]);
      }
      if (i == 0){
	max = sum;
      }else{
	if (max < sum){
	  max = sum;
	}
    }
  }
  return max;
}

inline Vector multiply(Matrix matrix, Vector vector){
  int n = matrix.size();
  int m = vector.size();
    Vector y;
    for (int i = 0;i<n;i++){
      double sum = 0;
      for (int j=0;j<m;j++){
	sum += (matrix[i][j] * vector[j]);
      }
      y.push_back(sum);
      
    }
    return y;
}

inline Matrix multiply(Matrix matrix1, Matrix matrix2){
    int n = matrix1.size();
    int m = matrix2.size();
    Vector tmp = matrix2[0];
    int k = tmp.size();
    Matrix y;
    for (int i = 0;i < n; i++){
      Vector vector;
      for (int j = 0; j < k; j++){
	double sum = 0;
	for (int l = 0;l < m; l++){
	  sum += matrix1[i][l] * matrix2[l][j];
	}
	vector.push_back(sum);
      }
      y.push_back(vector);
      vector.erase(vector.begin(), vector.begin() + k);
    }
    return y;
}

inline Vector readVector(int n){
    Vector vector;
    double number;
    for (int j = 0;j < n; j++){
      std::cin >> number >> std::setprecision(8);
      vector.push_back(number);
    }
    return vector;
}

inline Matrix readMatrix(int n, int m){
    double number;
    Matrix matrix;
    for (int i = 0;i<n;i++){
    Vector vector;
    for (int j = 0;j < m;j++){
      std::cin >> number;
      vector.push_back(number);
    }
    matrix.push_back(vector);
    
  }
  return matrix;
}

#endif 