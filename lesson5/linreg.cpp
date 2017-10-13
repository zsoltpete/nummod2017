#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <iomanip>

using namespace std;

int n;
vector < vector <double> > A;
vector<double> t,f,F,X;

int input_size(){
    int size;
    cin >> size;
    return size;
}

vector<double> input_vector(int n){
  vector<double> M;
    for(int j = 0 ; j<n;j++){
      double temp;
      cin>>temp;
      M.push_back(temp);
  }
  return M;
}

vector<vector<double>> null_2x2_matrix(){
    int n=2;
    vector<vector<double>> M;
    for(int i = 0 ; i<n;i++){
      vector<double> tmp;
      for(int j = 0 ; j<n;j++){
        tmp.push_back(0);
      }
      M.push_back(tmp);
    }
    return M;
}

vector<vector<double>> A_matrix(vector<double> & t,int m){
  vector<vector<double>> A=null_2x2_matrix();

  A[0][0]=m;
  A[0][1]=0;
  A[1][0]=0;
  for(int i = 0 ; i<m;i++){
    A[0][1]+=t[i];
    A[1][0]+=t[i];
  }
  A[1][1]=0;
  for(int i = 0 ; i<m;i++){
    A[1][1]+= (t[i]*t[i]);
  }
  return A;
}

vector<double> F_vector(vector<double> & t,vector<double> & f,int m){

  F.push_back(0);
  for(int i = 0 ; i<m;i++){
    F[0]+=f[i];
  }
  F.push_back(0);
  for(int i = 0 ; i<m;i++){
    F[1]+=(t[i]*f[i]);
  }
  return F;
}

double det(vector<vector<double>> A){
  //csak 2x2es mátrix:
  double det=1;
  det=A[0][0]*A[1][1]-A[0][1]*A[1][0];
  return det;

}

vector<double> X_solver(vector<vector<double>> A,vector<double> F){
  vector<double> X;
  X.push_back(0);X.push_back(0);

  double det = A[0][0]*A[1][1]-A[0][1]*A[1][0];

  X[0]=(1/det)*((A[1][1]*F[0])+(-1*A[0][1]*F[1]));

  X[1]=(1/det)*((-1*A[1][0]*F[0])+(A[0][0]*F[1]));

  return X;
}

int main(int argc, char** argv) {
  n=input_size();
  t=input_vector(n);
  f=input_vector(n);
  cout<<"A: "<<endl;
  A=A_matrix(t,n);
  for(int i = 0 ; i < 2 ; i++){
    for(int j = 0 ; j < 2 ; j++)
      cout<<A[i][j]<<" ";
    cout<<endl;
    }
    cout<<"F: "<<endl;
  F=F_vector(t,f,n);
  for(int j = 0 ; j < 2 ; j++)
    cout<<F[j]<<" ";
  cout<<endl;

  X=X_solver(A,F);
  cout<<X[0]<<" , "<<X[1]<<endl;

  return 0;
}
