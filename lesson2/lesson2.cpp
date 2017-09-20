#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h> 



void rowNormal(){
    int n,m;
  double number;
  
  std::cin >> n;
  std::cin >> m;
  
  std::vector<std::vector<double> > matrix;
  
  
  
  for (int i = 0;i<n;i++){
    std::vector<double> vector;
    for (int j = 0;j < m;j++){
      std::cin >> number;
      vector.push_back(number);
    }
    matrix.push_back(vector);
     
  }
  double max = 0;
  for (int i = 0;i<n;i++){
    std::vector<double> vector;
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
  
  std::cout << max;
}

void colNormal(){
    int n,m;
  double number;
  
  std::cin >> n;
  std::cin >> m;
  
  std::vector<std::vector<double> > matrix;
  
  
  
  for (int i = 0;i<n;i++){
    std::vector<double> vector;
    for (int j = 0;j < m;j++){
      std::cin >> number;
      vector.push_back(number);
    }
    matrix.push_back(vector);
     
  }
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
  
  std::cout << max;
}

void matrixmatrix(){
  
      int n,m,k;
  double number;
  
  std::cin >> n;
  std::cin >> m;
  std::cin >> k;
  
  std::vector<std::vector<double> > matrix;
  std::vector<std::vector<double> > matrix2;
  
  for (int i = 0;i<n;i++){
    std::vector<double> vector;
    for (int j = 0;j < m;j++){
      std::cin >> number;
      vector.push_back(number);
    }
    matrix.push_back(vector);
     
  }
  
  for (int i = 0;i<m;i++){
    std::vector<double> vector;
    for (int j = 0;j < k;j++){
      std::cin >> number;
      vector.push_back(number);
    }
    matrix2.push_back(vector);
    
  }
    
    std::vector<std::vector<double> > y;
    for (int i = 0;i<n;i++){
      std::vector<double> vector;
      for (int j = 0; j<k ; j++){
	double sum = 0;
	for (int l = 0;l<m;l++){
	  sum += matrix[i][l] * matrix2[l][j];
	}
	vector.push_back(sum);
      }
      y.push_back(vector);
      vector.erase(vector.begin(), vector.begin() + n);

      
    }
    std::cout << y[0][0];
  
}


void matrixVector(){
    int n,m;
  double number;
  
  std::cin >> n;
  std::cin >> m;
  
  std::vector<std::vector<double> > matrix;
  std::vector<double> tmpVector;
  
  for (int i = 0;i<n;i++){
    std::vector<double> vector;
    for (int j = 0;j < m;j++){
      std::cin >> number;
      vector.push_back(number);
    }
    matrix.push_back(vector);
    
  }
  
  std::vector<double> vector;
    for (int j = 0;j < m;j++){
      std::cin >> number;
      vector.push_back(number);
    }
    
    std::vector<double > y;
    for (int i = 0;i<n;i++){
      double sum = 0;
      for (int j=0;j<m;j++){
	sum += (matrix[i][j] * vector[j]);
      }
      y.push_back(sum);
      
    }
    std::cout << y[1];
  
}

int main(){

  rowNormal();
  return 0;

}