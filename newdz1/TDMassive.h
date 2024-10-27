// TDMassive.h
#ifndef TDMASSIVE_H
#define TDMASSIVE_H

#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <iostream>

#define STEP_CAPACITY 15
#define MAX_CAPACITY 100000

// Состояния элементов массива
enum State { empty, busy, deleted };

// Шаблонный класс TDMassive
// Реализация динамического массива с возможностью добавления, удаления и замены элементов
// Класс поддерживает состояния элементов: пустой, занятый и удаленный

template <typename T>
class TDMassive {
    T* _data; // Указатель на массив данных
    State* _states; // Указатель на массив состояний
    size_t _capacity; // Текущая вместимость массива
    size_t _size; // Текущий размер (количество элементов)
    size_t _deleted; // Количество удаленных элементов

public:
    TDMassive(); // Конструктор по умолчанию
    explicit TDMassive(size_t n); // Конструктор с заданной вместимостью
    ~TDMassive(); // Деструктор

    bool empty() const noexcept; // Проверка, пуст ли массив
    bool full() const noexcept; // Проверка, полон ли массив
    size_t size() const noexcept; // Получение текущего размера
    size_t capacity() const noexcept; // Получение текущей вместимости
    void clear(); // Очистка массива
    void push_back(T value); // Добавление элемента в конец массива
    void remove_by_index(size_t pos); // Удаление элемента по индексу
    void replace(size_t pos, T new_value); // Замена элемента по индексу
    void repacking(); // Перепаковка массива для удаления "пустых" мест
    size_t find_first(T value) const noexcept; // Поиск первого элемента с заданным значением
    size_t find_last(T value) const noexcept; // Поиск последнего элемента с заданным значением
    T& operator[](size_t index); // Оператор доступа к элементу по индексу
};

// Конструктор по умолчанию
// Инициализирует массив с вместимостью равной STEP_CAPACITY
template <typename T>
TDMassive<T>::TDMassive() : _size(0), _capacity(STEP_CAPACITY), _deleted(0) {
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

// Конструктор с заданной вместимостью
// Инициализирует массив с заданной вместимостью n
template <typename T>
TDMassive<T>::TDMassive(size_t n) : _capacity(n), _size(0), _deleted(0) {
    if (_capacity == 0) {
        _capacity = STEP_CAPACITY;
    }
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

// Деструктор
// Освобождает выделенную память
template <typename T>
TDMassive<T>::~TDMassive() {
    delete[] _data;
    delete[] _states;
}

// Проверка на пустоту
// Возвращает true, если массив пуст
template <typename T>
bool TDMassive<T>::empty() const noexcept {
    return _size == 0;
}

// Проверка на заполненность
// Возвращает true, если массив полон
template <typename T>
bool TDMassive<T>::full() const noexcept {
    return _size >= _capacity;
}

// Получение текущего размера
// Возвращает количество элементов в массиве
template <typename T>
size_t TDMassive<T>::size() const noexcept {
    return _size;
}

// Получение текущей вместимости
// Возвращает текущую вместимость массива
template <typename T>
size_t TDMassive<T>::capacity() const noexcept {
    return _capacity;
}

// Очистка массива
// Устанавливает все элементы массива как пустые
template <typename T>
void TDMassive<T>::clear() {
    _size = 0;
    _deleted = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

// Добавление элемента в конец массива
// Добавляет элемент в конец массива, если есть свободное место, иначе увеличивает вместимость
template <typename T>
void TDMassive<T>::push_back(T value) {
    if (full()) {
        // Увеличиваем вместимость массива
        size_t new_capacity = _capacity * 2;
        if (new_capacity > MAX_CAPACITY) {
            throw std::logic_error("Превышена максимальная вместимость");
        }

        T* new_data = new T[new_capacity];
        State* new_states = new State[new_capacity];

        // Копируем старые данные в новый массив
        for (size_t i = 0; i < _capacity; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }

        // Освобождаем старую память
        delete[] _data;
        delete[] _states;

        // Переносим указатели на новые массивы
        _data = new_data;
        _states = new_states;
        _capacity = new_capacity;

        // Инициализируем новые ячейки как пустые
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = State::empty;
        }
    }

    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;
}

// Удаление элемента по индексу
// Устанавливает состояние элемента как "удаленный"
template <typename T>
void TDMassive<T>::remove_by_index(size_t pos) {
    if (pos >= _size || _states[pos] == State::deleted) {
        throw std::out_of_range("Неверный индекс");
    }
    _states[pos] = State::deleted;
    _deleted++;
}

// Замена элемента по индексу
// Заменяет элемент на новый по заданному индексу
template <typename T>
void TDMassive<T>::replace(size_t pos, T new_value) {
    if (pos >= _size || _states[pos] == State::deleted) {
        throw std::out_of_range("Неверный индекс");
    }
    _data[pos] = new_value;
}

// Перепаковка массива
// Удаляет все "пустые" места, оставленные удаленными элементами
template <typename T>
void TDMassive<T>::repacking() {
    size_t new_size = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == State::busy) {
            _data[new_size] = _data[i];
            _states[new_size] = State::busy;
            new_size++;
        }
    }
    _size = new_size;
    _deleted = 0;
    for (size_t i = new_size; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

// Поиск первого элемента с заданным значением
// Возвращает индекс первого элемента с заданным значением или SIZE_MAX, если не найдено
template <typename T>
size_t TDMassive<T>::find_first(T value) const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == State::busy && _data[i] == value) {
            return i;
        }
    }
    return SIZE_MAX;
}

// Поиск последнего элемента с заданным значением
// Возвращает индекс последнего элемента с заданным значением или SIZE_MAX, если не найдено
template <typename T>
size_t TDMassive<T>::find_last(T value) const noexcept {
    for (size_t i = _size; i > 0; i--) {
        if (_states[i - 1] == State::busy && _data[i - 1] == value) {
            return i - 1;
        }
    }
    return SIZE_MAX;
}

// Оператор доступа к элементу по индексу
// Возвращает ссылку на элемент по заданному индексу
template <typename T>
T& TDMassive<T>::operator[](size_t index) {
    if (index >= _size || _states[index] == State::deleted) {
        throw std::out_of_range("Неверный индекс");
    }
    return _data[index];
}

#endif // TDMASSIVE_H
