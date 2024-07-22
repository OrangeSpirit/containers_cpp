#include <iostream>
#include <list>

template <typename T>
class queue {
 public:

  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  queue() { inner_list = std::list<value_type>(); }
  queue(std::initializer_list<value_type> const &items) {
    inner_list = std::list<value_type>(items);
  }
  queue(const queue &temp_queue) : inner_list(temp_queue.inner_list) {}
  queue(queue &&temp_queue) noexcept
      : inner_list(std::move(temp_queue.inner_list)) {}
  ~queue() { this->inner_list.clear(); }
  queue &operator=(queue &&temp_queue) {
    this->inner_list = std::move(temp_queue.inner_list);
    return *this;
  }
  bool empty() { return inner_list.empty(); }
  size_type size() { return inner_list.size(); }
  void push(value_type value) { this->inner_list.push_back(value); }
  void pop() { this->inner_list.pop_front(); }
  void swap(queue &other) { this->inner_list.swap(other.inner_list); }

  const_reference front() { return this->inner_list.front(); }
  const_reference back() { return this->inner_list.back(); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    return this->inner_list.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  std::list<value_type> inner_list;
};

template <typename T>
class queue {
 public:
  using value_type = T; // Определение типа значений очереди через шаблонный параметр T
  using reference = value_type &; // Тип ссылки на значение очереди
  using const_reference = const value_type &; // Тип константной ссылки на значение очереди
  using size_type = size_t; // Используется для определения типа размера очереди

  queue() { inner_list = std::list<value_type>(); } // Конструктор по умолчанию инициализирует внутренний список пустым
  queue(std::initializer_list<value_type> const &items) { inner_list = std::list<value_type>(items); } // Конструктор с инициализатором списком
  queue(const queue &temp_queue) : inner_list(temp_queue.inner_list) {} // Конструктор копирования
  queue(queue &&temp_queue) noexcept : inner_list(std::move(temp_queue.inner_list)) {} // Конструктор перемещения
  ~queue() { this->inner_list.clear(); } // Деструктор очищает внутренний список
  queue &operator=(queue &&temp_queue) { this->inner_list = std::move(temp_queue.inner_list); return *this; } // Оператор присваивания

  bool empty() { return inner_list.empty(); } // Проверяет, пуста ли очередь
  size_type size() { return inner_list.size(); } // Возвращает количество элементов в очереди
  void push(value_type value) { this->inner_list.push_back(value); } // Добавляет элемент в конец очереди
  void pop() { this->inner_list.pop_front(); } // Удаляет первый элемент очереди
  void swap(queue &other) { this->inner_list.swap(other.inner_list); } // Меняет местами внутренние списки двух очередей

  const_reference front() { return this->inner_list.front(); } // Возвращает первый элемент очереди
  const_reference back() { return this->inner_list.back(); } // Возвращает последний элемент очереди

  template <typename... Args>
  void insert_many_back(Args &&...args) { return this->inner_list.insert_many_back(std::forward<Args>(args)...); } // Добавляет несколько элементов в конец очереди

 private:
  std::list<value_type> inner_list; // Внутренний список, используемый для хранения элементов очереди
};
