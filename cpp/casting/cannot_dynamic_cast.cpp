/**
 * This program will fail to compile because there is no reason to dynamic cast
 around since no virtual functions
 *
 * dynamic_cast_fail_compile.cpp:34:25: error: cannot ‘dynamic_cast’ ‘base1_obj’
 (of type ‘class Base1*’) to type ‘class Derived1*’ (source type is not
 polymorphic) 34 |          derived1_obj = dynamic_cast<Derived1 *> (base1_obj);
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
  void func(void);
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
  derived1_obj = dynamic_cast<Derived1 *>(base1_obj);
  if (derived_obj == NULL)
    cout << "derive obj after dynamic cast NULL";
  else
    cout << "derive object after dynamic cast" << derived_obj;

  if (derived1_obj == NULL)
    cout << "derive1 obj after dynamic cast NULL";
  else
    cout << "derive1 object after dynamic cast" << derived1_obj;
}
