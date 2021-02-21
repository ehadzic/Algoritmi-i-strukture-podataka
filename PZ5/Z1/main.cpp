#include <iostream>

int fib2_0(int n){
    if(n==0) return 0;
    if(n==1) return 1;
    return fib2_0(n-1)+fib2_0(n-2);
}


int nzd(int x, int y){
    if(y==0) return x;
    return(y,x%y);
    
}

void TestFib2_0(){
    std::cout<<fib2_0(20);
}

void TestNzd(){
    std::cout<<nzd(6,561);
    
}


int main() {
    std::cout << "Pripremna Zadaca Za Vjezbu 5, Zadatak 1";
    return 0;
}
