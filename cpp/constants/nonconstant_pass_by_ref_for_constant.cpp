#include <iostream>

using namespace std;

// constant as reference
void func(const int &a) {
    cout << endl <<"Address after: " << &a;
    
}

int main() {
    int a = 10;
    cout << endl << "Address before:" << &a;
    // passing non constant allowed, compiler can cast to const only within sub function
    func(a);
    
    return 0;
}
