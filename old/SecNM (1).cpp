#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define PI 3.14159265
bool vanhiba=false;
double* Csoleszky(int n, int m, double matrix[], double vektor[]){
    double y[n];
    double *x=(double*) malloc(n*sizeof(double));
    bool hiba=false;
    for (int k=0;k<n;k++){
      if (matrix[k*(k+1)/2+k] < 1e-15){	
	hiba=true;
	vanhiba=true;
	printf("szingularis\n");
	break;
      }else	{
	 hiba=false;
	 vanhiba=false;
	 matrix[k*(k+1)/2+k]=sqrt(matrix[k*(k+1)/2+k]);
      }	 
      for (int i=k+1;i<n;i++){ 
	matrix[i*(i+1)/2+k]=matrix[i*(i+1)/2+k]/matrix[k*(k+1)/2+k];
	for (int j=k+1;j<=i;j++){
	  matrix[i*(i+1)/2+j]=  matrix[i*(i+1)/2+j]-matrix[i*(i+1)/2+k]*matrix[j*(j+1)/2+k]; 
	}
      }
    }
    
    if (hiba == false){    
    y[0]=vektor[0]/matrix[0];
    for (int i=1;i<n;i++){ 
      double sum=0;
      for (int j=0;j<i;j++){
	sum+=(matrix[i*(i+1)/2+j]*y[j]);
      }
      y[i]=(vektor[i]-sum)/matrix[i*(i+1)/2+i];
      }  
    for (int i=n-1;i>=0;i--){
      double sum=0;
      for (int j=i+1;j<n;j++){
	sum+=matrix[j*(j+1)/2+i]*x[j];
      }
	x[i]=(y[i]-sum)/matrix[i*(i+1)/2+i];
    }
}  
 return x;  
}
//<--->
//<Csoli megvan>
//<--->
int main(){
  int db;
  scanf("%d", &db);
  for (int cik=0;cik<db;cik++){
    int model;
    double *x;
    int n; 
    scanf("%d", &model);
    if (model == 1){ 
      scanf("%d",&n);
    }
    int meresszam;
    scanf("%d",&meresszam);
    double t[meresszam];
    for (int i=0;i<meresszam;i++)
      scanf("%lf",&t[i]);
    double f[meresszam];
    for (int i=0;i<meresszam;i++)
      scanf("%lf",&f[i]);
    
// <------------------>   
// Beolvastunk mindent!
// <------------------>   
    
if (model == 1){
      
      
      double A[meresszam][n];
      double ATfi[n];
      for (int j=0;j<meresszam;j++){
	for (int i=0;i < n;i++){
	  A[j][i]=pow(t[j],i);
	}
      }
      
      int m=(n*n-n)/2+n;
      double ATA[m];
      for(int i=0;i<n;i++)
	for(int j=0;j<=i;j++){
	  double szum=0;
	  for(int k=0;k<meresszam;k++)
	    szum+=A[k][i]*A[k][j];	
	  ATA[i*(i+1)/2+j]=szum;
	}
      
      for(int j=0;j<n;j++){
       ATfi[j]=0;
	for(int i=0;i<meresszam;i++){
	 ATfi[j]+=A[i][j]*f[i];
	
       } 	      
      }    
      x=Csoleszky(n,m,ATA,ATfi);
      if (vanhiba==false){
      for(int j=0;j<n;j++){
          printf("%.8lf ",x[j]);}
       printf("\n");}
}   
if (model == 2){
      n = 2;
      
      double A[n][meresszam];
      double ATfi[n];
      for (int i=0;i < meresszam;i++){
	A[0][i]=1;
	A[1][i]=1/t[i];
      }
      int m=(n*n-n)/2+n;
      double ATA[m];
      ATA[0]=0;
      ATA[1]=0;
      ATA[2]=0;
      for(int i=0;i<meresszam;i++){
	  ATA[0]+=A[0][i]*A[0][i];
	  ATA[2]+=A[1][i]*A[1][i];
	  ATA[1]+=A[0][i]*A[1][i];	  
      }
      ATfi[0]=0;
      ATfi[1]=0;
       for(int i=0;i<meresszam;i++){
	 ATfi[0]+=A[0][i]*f[i];
	 ATfi[1]+=A[1][i]*f[i];
       } 	      
      x=Csoleszky(n,m,ATA,ATfi);
      if (vanhiba==false){
      printf("%.8lf",x[0]);
      printf(" %.8lf\n",x[1]);}
}        
if (model == 3){
      n = 3;
      double A[meresszam][n];
      double ATfi[n];
      
      for (int i=0;i < meresszam;i++){
	A[i][0]=1;
	A[i][1]=cos(M_PI*t[i]);
	A[i][2]=sin(M_PI*t[i]);
//	printf("%.8lf ",A[i][0]);
//	printf("%.8lf ",A[i][1]);
//	printf("%.8lf \n",A[i][2]);
      }
      
      
      
      
      int m=(n*n-n)/2+n;
      double ATA[m];
      for (int i=0;i<m;i++)
	ATA[m]=0;
      for(int i=0;i<meresszam;i++){
	  ATA[0]+=A[i][0]*A[i][0];
	  ATA[1]+=A[i][0]*A[i][1];
	  ATA[2]+=A[i][1]*A[i][1];
	  ATA[3]+=A[i][0]*A[i][2];
	  ATA[4]+=A[i][1]*A[i][2];
	  ATA[5]+=A[i][2]*A[i][2];
      }
 //     for (int i=0;i<m;i++)
//	printf("%.8lf ",ATA[i]);
    //  printf("\n");
      
      
      ATfi[0]=0;
      ATfi[1]=0;
      ATfi[2]=0;
       for(int i=0;i<meresszam;i++){
	 ATfi[0]+=A[i][0]*f[i];
	 ATfi[1]+=A[i][1]*f[i];
	 ATfi[2]+=A[i][2]*f[i];
//	 printf("%.8lf ",ATfi[i]);
//	 printf("%.8lf ",ATfi[i]);
//	 printf("%.8lf \n",ATfi[i]);
       } 	
            
      x=Csoleszky(n,m,ATA,ATfi);
      if (vanhiba==false){
      printf("%.8lf",x[0]);
      printf(" %.8lf",x[1]);
      printf(" %.8lf\n",x[2]);}
}    

  free(x);
  }
  
  return 0;
}