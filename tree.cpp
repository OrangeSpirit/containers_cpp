#include <iostream>
#include <string>
#include "s21_tree.h"

int main() {
  s21::Tree<int, int> dubik(std::pair(3,9));
  s21::Tree<int, char> baobab(std::pair(11, 'A'));
  s21::Tree<int, std::string> iva(std::pair(333, "veter"));
  s21::Tree<int, int> elj;
  std::pair<int, char> pair_1(76, 'B');

  std::pair<int, int> p1(1, 1);
  std::pair<int, int> p2(3, 3);
  std::pair<int, int> p3(11, 11);
  std::pair<int, int> p4(22, 22);
  std::pair<int, int> p5(77, 77);

  s21::Tree<int, int> big_tree{p1, p2, p5, p4, p3};
  std::cout << "big_tree size =   " << big_tree.size() << std::endl;
  std::cout << "dubik, baobab" << std::endl;
  std::cout << "check empty dubik   " << dubik.empty() << std::endl;
  std::cout << "check empty elj     " << elj.empty() << std::endl;
  std::cout << "check size               " << baobab.size() << std::endl;

  std::cout << "big_tree person" << big_tree.GetNode_() << std::endl;
  // std::cout << "begin   " << iva.begin() << std::endl;


  return 0;
}