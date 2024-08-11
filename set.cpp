#include <iostream>
#include <initializer_list>
#include <set>
#include "s21_tree.h"

namespace s21 {
  template <typename Key>
  class set {
    public:
    using key_type = Key; // the first template parameter (Key)
    using value_type = Key; // value type (the value itself is a key)
    using reference = value_type &; // defines the type of the reference to an element
    using const_reference = const value_type &; //  defines the type of the constant reference
    //using iterator = internal class SetIterator<T> or BinaryTree::iterator as the internal iterator of tree subclass; defines the type for iterating through the container
    //using const_iterator = internal class SetConstIterator<T> or BinaryTree::const_iterator as the internal const iterator of tree subclass; defines the constant type for iterating through the container
    using size_type = size_t; // defines the type of the container size (standard type is size_t)

    set(){};
    set(std::initializer_list<Key> &items) {
      for (value_type value : items) Tree<Key, Key>::insert(value);
    };
    set(const set &s);
    set(set &&s);
    ~set();
    set &operator=(set &&s);

    // iterator begin(); //  returns an iterator to the beginning
    // iterator end(); //  returns an iterator to the end

    // bool empty(); //  checks whether the container is empty
    // size_type size(); //  returns the number of elements
    // size_type max_size(); //  returns the maximum possible number of elements

    // void clear(); //  clears the contents
    // std::pair<iterator, bool> insert(const value_type& value);  //  inserts node and returns iterator to where the element is in the container and bool denoting whether the insertion took place
    // void erase(iterator pos); //  erases element at pos
    // void swap(set& other);  //  swaps the contents
    // void merge(set& other); //  splices nodes from another container

    // iterator find(const Key& key);  //  finds element with specific key
    // bool contains(const Key& key);  //  checks if the container contains element with specific key
  };
} // namespace s21

int main() {
  s21::set<int> test_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};



  return 0;
}
