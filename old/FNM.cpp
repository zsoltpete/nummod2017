#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

int main(){
  int counter;
  scanf("%d", &counter);
  for (int loopCounter = 0;loopCounter<counter;loopCounter++){
    int n,m;
    scanf("%d", &n);
    m = ((n*n-n)/2)+n;
    double x[n],y[n],b[n], underD[m];
    for (int i = 0;i < m;i++){
        scanf("%lf", &underD[i]);
    }
    for(int i = 0;i < n;i++){
        scanf("%lf", &b[i]);
    }
    int error = 0;
    for (int k = 0;k < n;k++){
        if (underD[k * (k + 1) / 2 + k] < 1e - 15){
            error = 1;
            cout << "error \n";
            break;
        }else	{
        error = 0;
        underD[k * (k + 1) / 2 + k] = sqrt(underD[k * (k + 1) / 2 + k]);
        }
        for (int i = k + 1;i < n;i++){
            underD[i * (i + 1) / 2 + k] = underD[i * (i + 1) / 2 + k] / underD[k * (k + 1) / 2 + k];
            for (int j = k + 1;j <= i;j++){
                underD[i * (i + 1) / 2 + j] =  underD[i * (i + 1) / 2 + j] - underD[i * (i + 1) / 2 + k] * underD[j * (j + 1) / 2 + k];
            }
        }
    }
    if (!error){
        y[0] = b[0] / underD[0];
        for (int i = 1;i < n;i++){
            double sum = 0;
            for (int j = 0;j < i;j++){
                sum += (underD[i * (i + 1) / 2 + j] * y[j]);
            }
            y[i] = (b[i] - sum) / underD[i * (i + 1) / 2 + i];
        }
        for (int i = n - 1;i >= 0;i--){
            double sum = 0;
            for (int j = i + 1;j < n;j++){
                sum += underD[j * (j + 1) / 2 + i] * x[j];
            }
            x[i] = (y[i] - sum) / underD[i * (i + 1) / 2 + i];
        }
        for (int i = 0;i < n;i++){
            for (int j = 0;j < i + 1;j++){
                cout << underD[i * (i + 1) / 2 + j];
            }
            cout << endl;
        }
        for (int i = 0;i < n;i++){
            cout << x[i];
        }
        cout << endl;
    }
  }
return 0;
}
