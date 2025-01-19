/**
Output of program will be as below.

illustrating dynamic_cast operates runtime,
if casting can be done or it cannot be done:
>>>>>>>>>>>>>>>>>>
1. derive object after dynamic cast:0xa00000590
2. derive1 obj after dynamic cast NULL
3. derive1 object after dynamic cast:0xa00000460
>>>>>>>>>>>>>>>>>>
 *
 **/
#include <iostream>
using namespace std;

class Base {
public:
  virtual void func(void);
};
void Base::func() {}

class Base1 {
public:
  virtual void func(void);
};
void Base1::func() {}

class Derived : public Base {};

class Derived1 : public Base1 {
  void func();
};
void Derived1::func() {}

int main() {
  Base *base_obj = new Derived();
  Base1 *base1_obj = new Derived1();
  Derived *derived_obj;
  Derived1 *derived1_obj;

  derived_obj = dynamic_cast<Derived *>(base_obj);
  derived1_obj = dynamic_cast<Derived1 *>(base_obj);
  if (derived_obj == NULL)
    cout << "1. derive obj after dynamic cast NULL" << endl;
  else
    cout << "1. derive object after dynamic cast:" << derived_obj << endl;

  /* This will be NULL since derived1 class doesn't derive from base */
  if (derived1_obj == NULL)
    cout << "2. derive1 obj after dynamic cast NULL" << endl;
  else
    cout << "2. derive1 object after dynamic cast:" << derived1_obj << endl;

  derived1_obj = dynamic_cast<Derived1 *>(base1_obj);
  if (derived1_obj == NULL)
    cout << "3. derive1 obj after dynamic cast NULL" << endl;
  else
    cout << "3. derive1 object after dynamic cast:" << derived1_obj << endl;
}
