#include <iostream>
#include <string>

class Person {
  std::string Name;
  int Type;
  std::string Property;
  
  public:
    Person() : Name("Yona"), Type(11), Property("light") {}
    Person(std::string name, int type, std::string property) {
      this->Name = name;
      this->Type = type;
      this->Property = property;
    }
    Person(const Person &other) {
      std::cout << "call copy construct" << std::endl;
      this->Name = other.Name;
      this->Type = other.Type;
      this->Property = other.Property;
    }
    Person(const Person&& other) {
      
    }

    ~Person() {}

  void print_person() {
    std::cout << "Name = " << Name << "   " << "Type = " << Type <<  "   " << "Property = " << Property << std::endl;
  }

  

};

int main() {
  Person P1;
  P1.print_person();
  Person P2("Pups_high", 55, "very_high");
  P2.print_person();

  Person P3(P2);
  P3.print_person();



  return 0;
}