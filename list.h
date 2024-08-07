#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class list {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    
    // Конструкторы и деструкторы
    list() noexcept : head_(nullptr), tail_(nullptr), size_(0) {};
    list(size_type n);
    list(std::initializer_list<value_type> const &items);
    list(const list &l) noexcept;
    list(list &&l) noexcept;
    ~list();
    
    void push_front(const_reference value);
    void push_back(const_reference value);
    void pop_front();
    void pop_back();
    const_reference front() const;
    const_reference back() const;
    void swap(list& other);
    void sort();
    void merge(list& other);
    void reverse();
    void unique();
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    bool empty() const noexcept;
    void clear();
    
    list& operator=(const list &l);
    list& operator=(list &&l) noexcept;

private:
    typedef struct Node {
        value_type value_;
        Node* next_;
        Node* prev_;
        explicit Node(value_type value) noexcept:
            value_(value), next_(nullptr), prev_(nullptr) {}
    } Node;
    
    Node* head_;
    Node* tail_;
    size_type size_;
    
    // Вспомогательные методы
    void init_from_initializer_list(std::initializer_list<value_type> const &items);
    
    class Iterator {
        friend class list<T>;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        Iterator() noexcept : current(nullptr), list_tail(nullptr) {}
        explicit Iterator(Node* node) noexcept : current(node), list_tail(nullptr) {}
        explicit Iterator(Node* node, Node* last_node) noexcept : current(node), list_tail(last_node) {}
        Iterator(const Iterator& other) noexcept : current(other.current), list_tail(nullptr) {}
        ~Iterator() = default;
        
        bool operator!=(const Iterator& other) const noexcept {
            return current != other.current;
        }
        
        bool operator==(const Iterator& other) const noexcept {
            return current == other.current;
        }
        
        Iterator& operator=(const Iterator& other) noexcept {
            if (this != &other) {
                current = other.current;
            }
            return *this;
        }
        
        reference operator*() const noexcept {
            if (current == nullptr) {
                return list_tail->value_;
            } else {
                return current->value_;
            }
        }
        
        pointer operator->() const noexcept {
            return &current->value_;
        }
        
        Iterator operator+(size_type n) noexcept {
            auto iter = *this;
            while (n-- > 0) {
                if (iter.current != nullptr) {
                    ++iter;
                }
            }
            return iter;
        }
        
        Iterator operator-(size_type n) noexcept {
            auto iter = *this;
            while (n-- > 0) {
                if (iter.current != nullptr) {
                    --iter;
                } else {
                    iter.current = iter.list_tail;
                }
            }
            return iter;
        }
        
        Iterator operator++(int) noexcept {
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        Iterator operator++() noexcept {
            if (current) current = current->next_;
            return *this;
        }
        
        Iterator operator--(int) noexcept {
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }
        
        Iterator operator--() noexcept {
            if (current == nullptr) {
                if (list_tail) {
                    current = list_tail->prev_;
                }
            } else {
                current = current->prev_;
            }
            return *this;
        }
        
        Iterator& operator+=(size_type n) noexcept {
            auto iter = *this;
            while (n-- > 0) {
                if (current) current = current->next_;
            }
            return *this;
        }

        Iterator& operator-=(size_type n) noexcept {
            auto iter = *this;
            while (n-- > 0) {
                if (current)
                    current = current->prev_;
                else
                    current = list_tail;
            }
            return *this;
        }
        
        Node* GetNode_() const noexcept { return current; }
        
    protected:
        Node* current;
        Node* list_tail;
    };
    
    class ConstIterator : public Iterator {
    public:
        using pointer = const T*;
        using reference = const T&;
        
        ConstIterator() noexcept : Iterator() {}
        explicit ConstIterator(Node* node) noexcept : Iterator(node) {}
        explicit ConstIterator(Node* node, Node* list_tail) : Iterator(node, list_tail) {}
        ConstIterator(const ConstIterator& other) noexcept : Iterator(other.current, other.list_tail) {}
        ConstIterator(const Iterator& other) noexcept : Iterator(other) {}
        ~ConstIterator() = default;
        
        ConstIterator& operator=(const ConstIterator& other) noexcept {
            if (this != &other) {
                Iterator::operator=(other);
            }
            return *this;
        }
        
        reference operator*() const noexcept {
            return (reference)this->current->value_;
        }
        
        pointer operator->() const noexcept {
            return (pointer)&this->current->value_;
        }
    };

public:
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    
    iterator insert(iterator pos, const_reference value);
    void print_list(const s21::list<T>& lst);
    
    template <typename... Args>
    iterator insert_many(const_iterator pos, Args&&... args) {
        Node* pos_node = GetIteratorNode_(pos);
        Iterator it(pos_node);
        Iterator first_inserted;
        bool first_insertion_done = false;
        
        for (auto elem : {std::forward<Args>(args)...}) {
            if (!first_insertion_done) {
                first_inserted = insert(it, elem);
                first_insertion_done = true;
            } else {
                insert(it, elem);
            }
        }
        return first_insertion_done ? first_inserted : it;
    }
    
    template <typename... Args>
    void insert_many_back(Args&&... args) {
        const_iterator it = end();
        insert_many(it, std::forward<Args>(args)...);
    }
    
    template <typename... Args>
    void insert_many_front(Args&&... args) {
        for (auto elem : {std::forward<Args>(args)...}) {
            push_front(elem);
        }
    }
    
    void splice(const_iterator pos, list& other);
    void erase(iterator pos);
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    Node* GetIteratorNode_(const_iterator iter) const noexcept {
        return iter.GetNode_();
    }
};

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    if (n <= 0) {
        throw std::out_of_range("Index out of range");
    }
    for (size_type i = 0; i < n; i++) {
        push_back(value_type());
    }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : head_(nullptr), tail_(nullptr), size_(0) {
    init_from_initializer_list(items);
}

template <typename T>
void list<T>::init_from_initializer_list(std::initializer_list<value_type> const &items) {
    for (const auto& item : items) {
        push_back(item);
    }
}

template <typename T>
list<T>::list(const list &l) noexcept : head_(nullptr), tail_(nullptr), size_(0) {
    Node* current = l.head_;
    while (current) {
        push_back(current->value_);
        current = current->next_;
    }
}

template <typename T>
list<T>::list(list &&l) noexcept : head_(l.head_), tail_(l.tail_), size_(l.size_) {
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
}

template <typename T>
list<T>::~list(){
    clear();
}

template <typename T>
list<T>& list<T>::operator=(const list &l) {
    if (this != &l) {
        clear();
        // Node* current = l.head_;
        // while (current) {
        //     push_back(current->value_);
        //     current = current->next_;
        // }
        *this = l;
    }
    return *this;
}

template <typename T>
list<T>& list<T>::operator=(list &&l) noexcept {
    if (this != &l) {
        clear();
        head_ = l.head_;
        tail_ = l.tail_;
        size_ = l.size_;
        l.head_ = nullptr;
        l.tail_ = nullptr;
        l.size_ = 0;
    }
    return *this;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
    return Iterator(head_, tail_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
    return Iterator(nullptr, tail_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
    return ConstIterator(head_, tail_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
    return ConstIterator(nullptr, tail_);
}

template <typename T>
void list<T>::clear() {
    while (head_) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    tail_ = nullptr;
    size_ = 0;
}

template <typename T>
void print_list(const s21::list<T>& lst) {
    for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
typename list<T>::iterator list<T>::insert(list::iterator pos, const_reference value) {
    Node* node = pos.GetNode_();
    Node* newNode = new Node(value);
    if (node) {
        newNode->next_ = node;
        newNode->prev_ = node->prev_;
        if (node->prev_) {
            node->prev_->next_ = newNode;
        } else {
            head_ = newNode;
        }
    } else {
        if (tail_) {
            tail_->next_ = newNode;
            newNode->prev_ = tail_;
            tail_ = newNode;
        } else {
            head_ = tail_ = newNode;
        }
    }
    ++size_;
    return Iterator(newNode, tail_);
}

template <typename T>
void list<T>::erase(list::iterator pos) {
    Node* node = pos.current;
    if (node) {
        if (node->prev_) {
            node->prev_->next_ = node->next_;
        } else {
            head_ = node->next_;
        }
        if (node->next_) {
            node->next_->prev_ = node->prev_;
        } else {
            tail_ = node->prev_;
        }
        delete node;
        --size_;
    }
}

template <typename T>
void list<T>::push_back(const_reference value) {
    Node* newNode = new Node(value);
    if (tail_) {
        tail_->next_ = newNode;
        newNode->prev_ = tail_;
        tail_ = newNode;
    } else {
        head_ = tail_ = newNode;
    }
    ++size_;
}

template <typename T>
void list<T>::pop_back() {
    if (tail_) {
        Node* temp = tail_;
        tail_ = tail_->prev_;
        if (tail_) {
            tail_->next_ = nullptr;
        } else {
            head_ = nullptr;
        }
        delete temp;
        --size_;
    }
}

template <typename T>
void list<T>::push_front(const_reference value) {
    Node* newNode = new Node(value);
    if (head_) {
        head_->prev_ = newNode;
        newNode->next_ = head_;
        head_ = newNode;
    } else {
        head_ = tail_ = newNode;
    }
    ++size_;
}

template <typename T>
void list<T>::pop_front() {
    if (head_) {
        Node* temp = head_;
        head_ = head_->next_;
        if (head_) {
            head_->prev_ = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete temp;
        --size_;
    }
}

template <typename T>
void list<T>::swap(list& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list& other) {
    if (this != &other) {
        Node* thisCurrent = head_;
        Node* otherCurrent = other.head_;
        if (thisCurrent) {
            while (thisCurrent && otherCurrent) {
                if (thisCurrent->value_ <= otherCurrent->value_) {
                    thisCurrent = thisCurrent->next_;
                } else {
                    Node* nextOther = otherCurrent->next_;
                    if (thisCurrent->prev_) {
                        thisCurrent->prev_->next_ = otherCurrent;
                    } else {
                        head_ = otherCurrent;
                    }
                    otherCurrent->prev_ = thisCurrent->prev_;
                    otherCurrent->next_ = thisCurrent;
                    thisCurrent->prev_ = otherCurrent;
                    otherCurrent = nextOther;
                }
            }
            
            if (otherCurrent) {
                tail_->next_ = otherCurrent;
                otherCurrent->prev_ = tail_;
                tail_ = other.tail_;
            }
        } else {
            head_ = other.head_;
            tail_ = other.tail_;
        }
        
        size_ += other.size_;
        
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
}

template <typename T>
void list<T>::splice(list::const_iterator pos, list& other) {
    Node* node = pos.GetNode_();
    
    if (!other.head_) {
        return;
    }
    
    if (head_ == nullptr) {
        head_ = other.head_;
        tail_ = other.tail_;
    } else {
        if (node && this != &other) {
            if (node->prev_) {
                node->prev_->next_ = other.head_;
                other.head_->prev_ = node->prev_;
            } else {
                head_ = other.head_;
            }
            other.tail_->next_ = node;
            node->prev_ = other.tail_;
        }
    }
    
    size_ += other.size_;
    
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
void list<T>::reverse() {
    Node* current = head_;
    Node* temp = nullptr;
    while (current) {
        temp = current->prev_;
        current->prev_ = current->next_;
        current->next_ = temp;
        current = current->prev_;
    }
    if (temp) {
        head_ = temp->prev_;
    }
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
    return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
    return (std::numeric_limits<std::size_t>::max() / sizeof(Node));
}

template <typename T>
bool list<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return head_->value_;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail_->value_;
}

template <typename T>
void list<T>::unique() {
    Node* current = head_;
    while (current && current->next_) {
        if (current->value_ == current->next_->value_) {
            Node* temp = current->next_;
            current->next_ = temp->next_;
            if (temp->next_) {
                temp->next_->prev_ = current;
            } else {
                tail_ = current;
            }
            delete temp;
            --size_;
        } else {
            current = current->next_;
        }
    }
}

template <typename T>
void list<T>::sort() {
    if (head_ == tail_) return;
    
    list<T> carry;
    list<T> counter[64];
    int fill = 0;
    
    while (!empty()) {
        carry.push_back(front());
        pop_front();
        int i = 0;
        while (i < fill && !counter[i].empty()) {
            counter[i].merge(carry);
            carry.swap(counter[i++]);
        }
        carry.swap(counter[i]);
        if (i == fill) ++fill;
    }
    
    for (int i = 1; i < fill; ++i) {
        counter[i].merge(counter[i - 1]);
    }
    
    swap(counter[fill - 1]);
}

}

#endif
