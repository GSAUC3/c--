#include<iostream>







int main(){

  int a[]  ={1,2,3,4,5,6};

  int* p = a; 

  for (int i =0;i<6;i++){
    std::cout<< *(p+i)<<std::endl;
  }
  return 0;
  }