#include<iostream>

using namespace std;

void simpol_swap(int x, int y){
  int temp = x;
  x=y;
  y=temp;
}

void call_by_reference_pointers(int* x, int* y){
  int temp = *x;
  *x = *y;
  *y = temp;
}

void call_by_reference(int& x, int& y){
  int temp = x;
  x=y;
  y=temp;

}

int main(){

  int a=3, b = -1;
  cout<< "Before\na: "<<a<<"\tb: "<<b<<endl;
  simpol_swap(a,b);
  cout<< "a: "<<a<<"\tb: "<<b<<endl;
  
  call_by_reference_pointers(&a,&b);
  cout<< "a: "<<a<<"\tb: "<<b<<endl;

  call_by_reference(a,b);
  cout<< "a: "<<a<<"\tb: "<<b<<endl;


return 0;
}