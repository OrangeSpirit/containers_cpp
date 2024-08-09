#include <iostream>
#include <string>
#include "s21_tree.h"

int main() {
  s21::Tree<int, int> dubik(std::pair(3,9));
  s21::Tree<int, char> baobab(std::pair(11, 'A'));
  s21::Tree<int, std::string> iva(std::pair(333, "veter"));
  s21::Tree<int, int> elj;
  std::pair<int, char> pair_1(76, 'B');
  std::cout << "dubik, baobab" << std::endl;
  std::cout << "check empty dubik   " << dubik.empty() << std::endl;
  std::cout << "check empty elj     " << elj.empty() << std::endl;
  std::cout << "check size               " << baobab.size() << std::endl;
  // std::cout << "begin   " << iva.begin() << std::endl;


  return 0;
}