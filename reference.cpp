#include <iostream>
#include <string>

struct channel {
  std::string name;
  int subs;
};

void print_Y(channel& ch) {
  std::cout << ch.name << std::endl;
  std::cout << ch.subs << std::endl;
}


int main() {
  int a = 100;
  int& r_a = a;
  std::cout << &a << std::endl;
  std::cout << &r_a << std::endl;
  std::cout << r_a << std::endl;
  
  channel Y = {"asdf", 899};
  channel& r_Y = Y;
  std::cout << r_Y.name << "  " << r_Y.subs << std::endl;
  
  print_Y(Y);


  int 
  return 0;
}