/**
reintepret_cast in unsafe it will only be,
useful when you know what your doing 100%
when, passing data across some callbacks
and getting back data could be one example
>>>>>>>>>>>>>>>>
2. derive1 object after dynamic cast:0xa00000590
called Base::func
called Derived1::func1
>>>>>>>>>>>>>>>>
As you can see above vtable was same size,
probably it helped to still get write function
from Base since it was originally object of Derived
In second case no vtable so compile time mapping,
goes to derived1 class function

**/
#include <iostream>
using namespace std;

class Base {
public:
  virtual void func(void);
};
void Base::func() {
	cout << "called Base::" << __func__ << endl;
}

class Base1 {
public:
  virtual void func(void);
};
void Base1::func() {
	cout << "called Base1::" << __func__ << endl;
}

class Derived : public Base {};

class Derived1 : public Base1 {
	public:
  void func();
  void func1();
};

void Derived1::func() {
	cout << "called Derived1::" << __func__ << endl;
}

void Derived1::func1() {
	cout << "called Derived1::" << __func__ << endl;
}

int main() {
  Base *base_obj = new Derived();
  Base1 *base1_obj = new Derived1();
  Derived *derived_obj;
  Derived1 *derived1_obj;

  derived1_obj = reinterpret_cast<Derived1 *>(base_obj);

  /* This will be NULL since derived1 class doesn't derive from base */
  if (derived1_obj == NULL)
    cout << "2. derive1 obj after dynamic cast NULL" << endl;
  else
    cout << "2. derive1 object after dynamic cast:" << derived1_obj << endl;
  derived1_obj->func();
  derived1_obj->func1();
}
