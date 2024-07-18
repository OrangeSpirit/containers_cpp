#ifndef __S21_QUEUE__
#define __S21_QUEUE__

class queue {
  private:

  public:
    //  Queue Member functions
    queue() //default constructor, creates empty queue
    queue(std::initializer_list<value_type> const &items) //initializer list constructor, creates queue initizialized using std::initializer_list
    queue(const queue &q) //copy constructor
    queue(queue &&q)  //move constructor
    ~queue()  //destructor
    operator=(queue &&q)  //assignment operator overload for moving object

    //  Queue Element access
    const_reference front() //  access the first element
    const_reference back()  //  access the last element

    //  Queue Capacity
    bool empty()  //  checks whether the container is empty
    size_type size()  //  returns the number of elements

    //  Queue Modifiers
    void push(const_reference value)  //  inserts element at the end
    void pop()  //  removes the first element
    void swap(queue& other) //  swaps the contents
};

#endif