#include <iostream>

class MyClass {
  public:
    int *data;

    MyClass(int size) {
      this->Size = size;
      this->data = new int[size];

      for (int i = 0; i < size; i++) {
        data[i] = i;
      }
      std::cout << "Call Constructor Creator     " << this << std::endl;
    };

    MyClass(const MyClass &other) {
      this->Size = other.Size;
      this->data = new int[other.Size];

      for (int i = 0; i < other.Size; i++) {
        this->data[i] = other.data[i];
      }
      std::cout << "Call Constructor Copy        " << this << std::endl;

    }

    MyClass& operator = (const MyClass &other) {
      std::cout << "Call operator                " << this << std::endl;
      std::cout << "other =                      " << &other << std::endl;
      this->Size = other.Size;
      if (this->data != nullptr) {
        delete[] this->data;
      }
      this->data = new int[other.Size];
      for (int i = 0; i < other.Size; i++) {
        this->data[i] = other.data[i];
      }
      return *this;
     }

    ~MyClass() {
      delete[] data;
      std::cout << "Call DESTRUCTOR              " << this << std::endl;
    };

  private:
    int Size;
};


int main() {
  MyClass A(11);
  MyClass B(3);
  MyClass C = A;
  MyClass D(B);

  MyClass F(7);

  F = A = B;


  // int r;
  // std::cout << "r = " << r << "   &r = " << &r << std::endl;
  // int &l = r;
  // std::cout << "l = " << l << "   &l = " << &l << std::endl;
  // r = 88;
  // std::cout << "avter" << std::endl << "l = " << l << "   &l = " << &l << std::endl;
  // r = 999;
  // std::cout << "avter r = 999" << std::endl << "l = " << l << "   &l = " << &l << std::endl;



  return 0;
}