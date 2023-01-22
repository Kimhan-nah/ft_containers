#include <iostream>
using namespace std;

template <typename T>
class Base {
 protected:
  T asset;
  int test;

 public:
  Base(T a) {
    asset = a;
    test = 42;
  }
  void showBase() { cout << asset << endl; }
};

template <typename T>
class Derived : public Base<T> {
  // int asset;
  int test;

 public:
  // Derived(int a, int b) : Base<T>::Base(a) { test = b; }
  Derived(int a, int b) : Base<T>(a) { test = b; }
  // Derived(int a, int b) : Base::Base(a) { test = b; }

  void showDerived() {
    cout << "Base::asset : " << Base<T>::asset << endl;
    cout << "test : " << test << endl;
    cout << "Base::test : " << Base<T>::test << endl;
  }
};

int main() {
  Derived<int> D(10, 50);

  D.showBase();
  D.showDerived();
  // cout << D.asset << endl;
  return 0;
}