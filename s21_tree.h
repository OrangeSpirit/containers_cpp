#ifndef CPP2_S21_CONTAINERS_SRC_TREE_S21_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_TREE_S21_TREE_H_

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>
#include <vector>

namespace s21 {
template <typename K, typename V>
class Tree {
public:
    using key_type = K;
    using mapped_type = V;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    
    // Конструктор по умолчанию
    Tree() noexcept;
    // Конструктор, создающий дерево с одним элементом
    explicit Tree(const value_type &elem) noexcept;
    // Конструктор, инициализирующий дерево списком элементов
    Tree(std::initializer_list<value_type> const &items);
    // Копирующий конструктор
    Tree(const Tree &other) noexcept;
    // Перемещающий конструктор
    Tree(Tree &&other) noexcept;
    
    // Деструктор
    virtual ~Tree();
    
    // Проверяет, пустое ли дерево
    bool empty() const noexcept;
    // Возвращает количество элементов в дереве
    size_type size() const noexcept;
    // Возвращает максимальное возможное количество элементов
    size_type max_size() const noexcept;
    // Очищает дерево
    void clear() noexcept;
    // Объединяет текущее дерево с другим деревом
    void merge(Tree<K, V> &other);
    // Меняет местами два дерева
    void swap(Tree &other);
    // Проверяет, содержит ли дерево элемент с заданным ключом
    bool contains(const K &key) const noexcept;
    
    // Копирующее присваивание
    Tree &operator=(const Tree &other) noexcept;
    // Присваивание с перемещением
    Tree &operator=(Tree &&other) noexcept;
    
protected:
    typedef struct Node {
        value_type element_;
        unsigned char height_;
        explicit Node(const value_type &elem) : element_(elem), height_(1){};
    } Node;
    
    // Указатель на корень дерева
    Node *root_;
    // Указатель на родительское дерево
    Tree *parent_;
    // Указатель на левое поддерево
    Tree *left_;
    // Указатель на правое поддерево
    Tree *right_;
    
    class Iterator {
    public:
        Iterator() noexcept : tree_(nullptr) {}
        Iterator(const Iterator &other) noexcept : tree_(other.tree_) {}
        explicit Iterator(Tree<K, V> *tree) noexcept : tree_(tree) {}
        ~Iterator() = default;
        
        bool operator==(const Iterator &other) {
            return this->tree_ == other.tree_;
        }
        
        bool operator!=(const Iterator &other) {
            return this->tree_ != other.tree_;
        }
        
        const value_type *operator->() { return &(tree_->root_->element_); }
        
        Iterator operator++() {
            Plus_();
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator tmp(*this);
            Plus_();
            return tmp;
        }
        
        Iterator operator+=(size_type n) {
            while (n-- > 0) operator++();
            return *this;
        }
        
        Iterator operator--() {
            Minus_();
            return *this;
        }
        
        Iterator operator--(int) {
            Iterator tmp(*this);
            Minus_();
            return tmp;
        }
        
        Iterator operator-=(size_type n) {
            while (n-- > 0) operator--();
            return *this;
        }
        
        void SetTree(Tree<K, V> *t) noexcept { tree_ = t; }
        Tree<K, V> *GetTree() { return tree_; }
        Node *GetNode() { return tree_->root_; }
    
    protected:
        Tree<K, V> *tree_;
        // Переход к предыдущему элементу
        void Minus_() {
            if (tree_->left_) {
                tree_ = tree_->FindMax(tree_->left_);
            } else if (!tree_->left_ && !tree_->right_) {
                if (tree_->parent_) {
                    if (tree_->parent_->right_ == tree_) {
                        tree_ = tree_->parent_;
                    } else if (tree_->parent_->left_ == tree_) {
                        if (tree_->parent_ && tree_->parent_->parent_) {
                            tree_ = tree_->parent_->parent_;
                        }
                    }
                }
            } else if (tree_->parent_) {
                tree_ = tree_->parent_;
            }
        }
        // Переход к следующему элементу
        void Plus_() {
            if (tree_->right_) {
                tree_ = tree_->FindMin(tree_->right_);
            } else if (!tree_->left_ && !tree_->right_) {
                if (tree_->parent_) {
                    if (tree_->parent_->left_ == tree_) {
                        tree_ = tree_->parent_;
                    } else if (tree_->parent_->right_ == tree_) {
                        if (tree_->parent_ && tree_->parent_->parent_) {
                            tree_ = tree_->parent_->parent_;
                        }
                    }
                }
            } else if (tree_->parent_) {
                tree_ = tree_->parent_;
            }
        }
    };
    
    class ConstIterator : public Iterator {
    public:
        ConstIterator() noexcept : Iterator() {}
        ConstIterator(const ConstIterator &other) noexcept : Iterator(other.tree_) {}
        explicit ConstIterator(Tree<K, V> *tree) noexcept : Iterator(tree) {}
        ConstIterator(const Iterator& other) noexcept : Iterator(other) {}
        ~ConstIterator() = default;
    };
    
    Tree *FindMin(const Tree *node) const;
    Tree *FindMax(const Tree *node) const;
    
    void Insert_(const value_type &elem, Iterator &iter, bool &is_inserted);
    
    void InsertMultiSet_(const value_type &elem, Iterator &iter, bool &is_inserted) {
        if (!root_) {
            root_ = new Node(elem);
            iter.SetTree(this);
            is_inserted = true;
            return;
        }
        if (elem.first <= root_->element_.first) {
            if (!left_) {
                left_ = new Tree<K, V>();
                left_->parent_ = this;
            }
            left_->InsertMultiSet_(elem, iter, is_inserted);
        } else if (elem.first >= root_->element_.first) {
            if (!right_) {
                right_ = new Tree<K, V>();
                right_->parent_ = this;
            }
            right_->InsertMultiSet_(elem, iter, is_inserted);
        }
        Balance_();
    }
    
private:
    // Возвращает высоту поддерева, корнем которого является узел tr
    unsigned char Height_(Tree *tr);
    // Возвращает балансировочный фактор текущего узла, который равен разнице высот правого и левого поддеревьев
    int BalanceFactor_();
    // Обновляет высоту текущего узла на основе высот его дочерних узлов
    void FixHeight_();
    // Выполняет левый поворот вокруг текущего узла
    void RotateLeft_();
    // Выполняет правый поворот вокруг текущего узла
    void RotateRight_();
    // Балансирует текущий узел
    void Balance_();
    // Рекурсивно вычисляет размер дерева, начиная с текущего узла
    void Size_(int &size) const noexcept;
    // Меняет содержимое текущего узла с другим узлом
    void Swap_(Tree &other);
    // Рекурсивно проверяет, содержится ли ключ key в дереве, начиная с текущего узла
    void Contains_(const K &key, bool &contains) const noexcept;
    // Удаляет указанный узел current из дерева
    void RemoveThis_(Tree *current);
    // Удаляет крайний узел и корректирует указатели родительского узла
    void RemoveEdge_(Tree *current);
    // Удаляет узел current и выполняет необходимую балансировку
    void RemoveNode_(Tree *current);
    // Поиск по ключу
    Tree<K, V>* FindNode(Tree* node, const K& key);
    // Очистка всего дерева
    void ClearTree_(Node *node);
    
public:
    using const_iterator = ConstIterator;
    using iterator = Iterator;
    
    iterator begin() const {
        if (!left_ && !right_ && !root_)
            throw std::out_of_range("Tree does not exist");
        
        const Tree<K, V> *tmp_this = this;
        Tree<K, V> *min_tr = FindMin(left_ ? left_ : tmp_this);
        return Iterator(min_tr);
    }
    
    iterator end() const {
        if (!left_ && !right_ && !root_)
            throw std::out_of_range("Tree does not exist");
        
        const Tree<K, V> *tmp_this = this;
        Tree<K, V> *max_tr = FindMax(right_ ? right_ : tmp_this);
        return Iterator(max_tr);
    }
    
    virtual std::pair<iterator, bool> insert(const value_type &value);
    void erase(iterator pos);
    
    Tree<K, V> *GetTree_(iterator pos) { return pos.GetTree(); }
    Node *GetNode_(iterator pos) { return pos.GetNode(); }
    
    template <typename... Args>
    std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
        std::vector<std::pair<iterator, bool>> res_vec;
        for (auto elem : {std::forward<Args>(args)...}) {
            res_vec.push_back(insert(elem));
        }
        return res_vec;
    }
};

template <typename K, typename V>
Tree<K, V>::Tree() noexcept : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {}

template <typename K, typename V>
Tree<K, V>::Tree(const value_type &elem) noexcept : parent_(nullptr), left_(nullptr), right_(nullptr) {
    root_ = new Node(elem);
}

template <typename K, typename V>
Tree<K, V>::Tree(const std::initializer_list<value_type> &items) : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {
    for (value_type i : items) insert(i);
}

template <typename K, typename V>
Tree<K, V>::Tree(const Tree &other) noexcept : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {
    *this = other;
}

template <typename K, typename V>
Tree<K, V>::Tree(Tree&& other) noexcept
    : root_(other.root_), parent_(other.parent_), left_(other.left_), right_(other.right_) {
    other.root_ = nullptr;
    other.parent_ = nullptr;
    other.left_ = nullptr;
    other.right_ = nullptr;
}

template <typename K, typename V>
Tree<K, V>::~Tree() {
    clear();
}

template <typename K, typename V>
void Tree<K, V>::ClearTree_(Node *node) {
    if (node) {
        ClearTree_(left_ ? left_->root_ : nullptr);
        ClearTree_(right_ ? right_->root_ : nullptr);
        delete left_;
        delete right_;
        delete node;
    }
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(Tree &&other) noexcept {
    if (this != &other) {
        ClearTree_(root_);
        root_ = other.root_;
        parent_ = other.parent_;
        right_ = other.right_;
        left_ = other.left_;
        other.root_ = nullptr;
        other.parent_ = nullptr;
        other.right_ = nullptr;
        other.left_ = nullptr;
    }
    return *this;
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(const Tree &other) noexcept {
    if (this != &other) {
        auto it = other.begin();
        clear();
        root_ = nullptr;
        parent_ = nullptr;
        left_ = nullptr;
        right_ = nullptr;
        std::pair<K, V> el;
        el.first = it->first;
        el.second = it->second;
        insert(el);
        while (true) {
            if (it == other.end()) break;
            ++it;
            el.first = it->first;
            el.second = it->second;
            insert(el);
        }
    }
    return *this;
}

template <typename K, typename V>
typename Tree<K, V>::size_type Tree<K, V>::size() const noexcept {
    int size = 0;
    Size_(size);
    return size;
}

template <typename K, typename V>
inline unsigned char Tree<K, V>::Height_(Tree *t) {
    if (t && t->root_) {
        return t->root_->height_;
    } else {
        return 0;
    }
}

template <typename K, typename V>
inline int Tree<K, V>::BalanceFactor_() {
    return (Height_(right_) - Height_(left_));
}

template <typename K, typename V>
void Tree<K, V>::FixHeight_() {
    if (!root_) return;
    
    int left_height = Height_(left_);
    int right_height = Height_(right_);
    
    root_->height_ = std::max(left_height, right_height) + 1;
}

template <typename K, typename V>
void Tree<K, V>::RotateLeft_() {
    Tree* newRoot = right_;
    if (!newRoot) return;
    
    Tree* newNode = new Tree();
    newNode->parent_ = this;
    newNode->left_ = left_;
    if (left_)
        left_->parent_ = newNode;
    newNode->root_ = root_;
    left_ = newNode;
    
    Tree* oldLeft = newRoot->left_;
    
    newNode->right_ = oldLeft;
    if (oldLeft) oldLeft->parent_ = newNode;
    
    root_ = newRoot->root_;
    right_ = newRoot->right_;
    if (right_) right_->parent_ = this;
    
    FixHeight_();
    newNode->FixHeight_();
    
    newRoot->left_ = nullptr;
    newRoot->right_ = nullptr;
    newRoot->root_ = nullptr;
    delete newRoot;
}

template <typename K, typename V>
void Tree<K, V>::RotateRight_() {
    Tree* newRoot = left_;
    if (!newRoot) return;
    
    Tree* newNode = new Tree();
    newNode->parent_ = this;
    newNode->right_ = right_;
    if (right_)
        right_->parent_ = newNode;
    newNode->root_ = root_;
    right_ = newNode;
    
    Tree* oldRight = newRoot->right_;
    
    newNode->left_ = oldRight;
    if (oldRight) oldRight->parent_ = newNode;
    
    root_ = newRoot->root_;
    left_ = newRoot->left_;
    if (left_) left_->parent_ = this;
    
    FixHeight_();
    newNode->FixHeight_();
    
    newRoot->left_ = nullptr;
    newRoot->right_ = nullptr;
    newRoot->root_ = nullptr;
    delete newRoot;
}

template <typename K, typename V>
void Tree<K, V>::Balance_() {
    FixHeight_();
    int balance = BalanceFactor_();
    if (balance == 2) {
        if (right_->BalanceFactor_() < 0) {
            right_->RotateRight_();
        }
        RotateLeft_();
    } else if (balance == -2) {
        if (left_->BalanceFactor_() > 0) {
            left_->RotateLeft_();
        }
        RotateRight_();
    }
}

template <typename K, typename V>
void Tree<K, V>::Insert_(const value_type &elem, Iterator &iter, bool &is_inserted) {
    if (!root_) {
        root_ = new Node(elem);
        iter.SetTree(this);
        is_inserted = true;
        return;
    }
    if (elem.first < root_->element_.first) {
        if (!left_) {
            left_ = new Tree();
            left_->parent_ = this;
        }
        left_->Insert_(elem, iter, is_inserted);
    } else if (elem.first > root_->element_.first) {
        if (!right_) {
            right_ = new Tree();
            right_->parent_ = this;
        }
        right_->Insert_(elem, iter, is_inserted);
    }
    Balance_();
}

template <typename K, typename V>
Tree<K, V> *Tree<K, V>::FindMin(const Tree *node) const {
    if (node->left_ && node->left_->root_) {
        return FindMin(node->left_);
    } else {
        return (Tree<K, V> *)node;
    }
}

template <typename K, typename V>
Tree<K, V> *Tree<K, V>::FindMax(const Tree *node) const {
    if (node->right_ && node->right_->root_) {
        return FindMax(node->right_);
    } else {
        return (Tree<K, V> *)node;
    }
}

template <typename K, typename V>
Tree<K, V>* Tree<K, V>::FindNode(Tree* node, const K& key) {
    if (node == nullptr || node->root_->element_.first == key) {
        return node;
    }
    
    if (key < node->root_->element_.first) {
        return FindNode(node->left_, key);
    } else {
        return FindNode(node->right_, key);
    }
}

template <typename K, typename V>
void Tree<K, V>::erase(Tree<K, V>::Iterator pos) {
    Tree *current = GetTree_(pos);
    if (current == this) {
        RemoveThis_(current);
    } else {
        if (!current->left_ && !current->right_) {
            RemoveEdge_(current);
        } else {
            RemoveNode_(current);
        }
    }
    if (root_) Balance_();
}

template <typename K, typename V>
void Tree<K, V>::Size_(int &size) const noexcept {
    if (root_) ++size;
    if (right_) right_->Size_(size);
    if (left_) left_->Size_(size);
}

template <typename K, typename V>
void Tree<K, V>::clear() noexcept {
    delete left_;
    delete right_;
    delete root_;
}

template <typename K, typename V>
void Tree<K, V>::Swap_(Tree &other) {
    std::swap(root_, other.root_);
    std::swap(parent_, other.parent_);
    std::swap(left_, other.left_);
    std::swap(right_, other.right_);
}

template <typename K, typename V>
void Tree<K, V>::RemoveThis_(Tree *current) {
    if (current->right_ || current->left_) {
        RemoveNode_(current);
    } else {
        delete root_;
        root_ = nullptr;
    }
}

template <typename K, typename V>
void Tree<K, V>::RemoveEdge_(Tree *current) {
    Tree *parent = current->parent_;
    if (parent->left_ == current)
        parent->left_ = nullptr;
    else
        parent->right_ = nullptr;
    current->left_ = nullptr;
    current->right_ = nullptr;
    delete current;
}

template <typename K, typename V>
void Tree<K, V>::RemoveNode_(Tree *current) {
    Tree* parent = nullptr;
    if (current->parent_) {
        parent = FindNode(this, current->parent_->root_->element_.first);
    }
    if (!current->left_ && !current->right_) {
        current->root_ = nullptr;
        RemoveEdge_(current);
    } else if (current->left_ && !current->right_) {
        if (parent) {
            if (parent->left_ == current)
                parent->left_ = current->left_;
            else
                parent->right_ = current->left_;
        } else {
            left_ = current->left_;
        }
        current->left_->parent_ = parent;
        current->left_ = nullptr;
        current->right_ = nullptr;
        delete current;
    } else if (!current->left_ && current->right_) {
        if (parent) {
            if (parent->left_ == current)
                parent->left_ = current->right_;
            else
                parent->right_ = current->right_;
        } else {
            right_ = current->right_;
        }
        current->right_->parent_ = parent;
        current->left_ = nullptr;
        current->right_ = nullptr;
        delete current;
    } else {
        Tree *min = FindMin(current->right_);
        
        current->root_ = min->root_;
        
        RemoveNode_(min);
    }
}

template <typename K, typename V>
bool Tree<K, V>::empty() const noexcept {
    return !root_;
}

template <typename K, typename V>
typename Tree<K, V>::size_type Tree<K, V>::max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Tree<V, V>) / 2;
}

template <typename K, typename V>
void Tree<K, V>::merge(Tree<K, V>&other) {
    if (!other.root_) return;
    auto itr1 = other.begin();
    std::pair<K, V> sr;
    for (; itr1 != other.end(); itr1++) {
        sr.first = itr1->first;
        sr.second = itr1->second;
        insert(sr);
    }
    sr.first = itr1->first;
    sr.second = itr1->second;
    insert(sr);
    other.clear();
    other.root_ = nullptr;
    other.right_ = nullptr;
    other.left_ = nullptr;
    other.parent_ = nullptr;
}

template <typename K, typename V>
void Tree<K, V>::swap(Tree &other) {
    Swap_(other);
}

template <typename K, typename V>
std::pair<typename Tree<K, V>::iterator, bool> Tree<K, V>::insert(const Tree::value_type &value) {
    iterator it;
    bool is_inserted = false;
    Insert_(value, it, is_inserted);
    std::pair<iterator, bool> res = {it, is_inserted};
    return res;
}

template <typename K, typename V>
bool Tree<K, V>::contains(const K &key) const noexcept {
    bool contains = true;
    Contains_(key, contains);
    return contains;
}

template <typename K, typename V>
void Tree<K, V>::Contains_(const K &key, bool &contains) const noexcept {
    if (!root_ || (!left_ && !right_ && root_->element_.first != key)) {
        contains = false;
    } else if (key < root_->element_.first) {
        if (left_) {
            left_->Contains_(key, contains);
        } else {
            contains = false;
        }
    } else if (key > root_->element_.first) {
        if (right_) {
            right_->Contains_(key, contains);
        } else {
            contains = false;
        }
    }
}
 
} // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_TREE_S21_TREE_H_
