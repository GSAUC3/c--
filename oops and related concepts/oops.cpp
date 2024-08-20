#include <iostream>

#define print(x) std::cout<< x <<std::endl;

// is a preprocessor macro definition in C++. 
// # define is a preprocessor directive used to define macros. 
// A macro is a fragment of code which has been given a name. 
// Whenever the name is used, it is replaced by the code that the macro represents.










int main(){

    int a = 5; 
    int& ref = a;

    // ref = 2; 

    print(ref);
    


}

