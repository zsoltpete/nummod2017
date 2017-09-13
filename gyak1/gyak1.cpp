#include <iostream>
#include <math.h> 

int main(){


}

void feladatP1(){
  
  std::cout << "P1 feladat";
  std::cout << (0.4-0.5+0.1 == 0) << (0.1-0.5+0.4 == 0) << std::endl;
  std::cout << std::endl;
  
}

void feladatP3(){
    double number = (pow(2, 66) + 1 == pow(2, 66));
  int counter = 1;
   while (number == 1) {
     number = (pow(2, 66) + counter == pow(2, 66));
     counter++;
     
  }
  std::cout << counter-1 << std::endl;
  
  
}

void feladatP4(){
  
    double x = 1.0/3;
  for (int i = 0;i<40;i++){
    x = 4*x - 1;
  }
  std::cout << x <<std::endl;
  
}

void feladatP2(){
  
  
  
    double epsilon = 1;
  while (1 + epsilon > 1) {
    epsilon/=2;
  }
  
  std::cout << epsilon * 2 << std::endl;
  
}

void feladatP2_part2(){
  
  double tmpEps = 1;
  double epsilon = 1;
  while (0 + epsilon > 0) {
    tmpEps = epsilon;
    epsilon/=2;
  }
  
  std::cout << tmpEps << std::endl;
}

void feladatP5(){
    double x = 2.0;
  for (int i = 0;i<60;i++){
    x = sqrt(x);
     std::cout << x << std::endl;
  }
    for (int i = 0;i<60;i++){
    x = pow(x, 2);
    
  }
  std::cout << x << std::endl;
  
}

void feladatP6(){
  int counter = 0;
  for (int x = 1; x<100;x++){
    std::cout << (  (((1.0/pow(x,2))/10.0)+1.0)*pow(x,2) - pow(x, 2) == 0.1) << std::endl;
    if  (  1/pow(x,2)/10*pow(x,2) - pow(x, 2) == 0.1) {
      counter++;
      
    }
  }
  std::cout << std::endl;
  std::cout << counter << std::endl;
  
}