// copyright:no copyright,use it if you like
// license boilerplate:maybe BSD
// filename:Vector.h
// author:Tempest(https://gitee.com/Tempest56890)
// date:2021-10-15
// brief:implement the function of STL Vector

#ifndef __TEMPEST_VECTOR__
#define __TEMPEST_VECTOR__

#include <iostream>
#include <new>
#include <vector>
#include <exception>
#include <cmath>
#include <limits>

// the total number of tests cases that we run through in this test.
// used to provide extra space for new elements to be pushed.
// it's predefined as 16, and can be changed outside.
static int spare_capacity(16);

template <typename obj>

// implement the funciton of STL Vector.
// example:
//    Vector<int> vec(100);
//    for (int i = 0; i < 100; i++) {
//      vec[i] = i;
//    }
//    Vector<int>::iterator iter;
//    for(iter = vec.begin();iter != vec.end();++iter) {
//        cout<<*iter<<" ";
//    }
class Vector {
 public:
    // define a iterator ,it's essence is a pointer.
    typedef obj* iterator;
    typedef const obj* const_iterator;
    // one-parameter Vector constructor.
    explicit Vector(int init_size = 0)
        : obj_size(init_size),
          obj_capacity(init_size + spare_capacity) {
        objects = new obj [obj_capacity];
    }
    // deep copy to construct a vector
    explicit Vector(const Vector& rhs) : objects(nullptr) {
        operator = (rhs);
    }
    const Vector& operator=(const Vector& rhs);
    // Vector destructor.
    ~Vector() {
        releasemem();
    }
    int size() const;
    int capacity() const;
    bool is_empty();
    obj& operator[](int obj_index);
    const obj& operator[](int obj_index) const;
    void printVector();
    void resize(int new_size);
    void reserve(int new_capacity);
    const obj& back() const;
    void push_back(const obj& new_element);
    void pop_back();
    // return the address of the first and latest pushed elements.
    iterator begin() {
        return& objects[0];
    };
    const_iterator begin() const {
        return& objects[0];
    };
    iterator end() {
        return& objects[size()];
    };
    const_iterator end() const {
        return& objects[size()];
    };
    
 private:
    // used to describe how many elements have be pushed.
    int obj_size;
    // used to describe the actual memory of a vector.
    int obj_capacity;
    // predefine an one-dimensional pointer.
    obj* objects = nullptr;
    void releasemem();
    void warning(int error) const;
};

template <typename obj>
// frees the memory by deleting the pointer.
// i/o param:(none)
void Vector<obj>::releasemem() {
    if (objects != nullptr) delete [] objects;
    objects = nullptr;
};

template <typename obj>
// provides other class functions  way to throw out problems.
// i/o param:error
void Vector<obj>::warning(int error) const {
    switch (error) {
        case 1: {
            std::cerr<<"Sorry but it's out of range."<<std::endl;
            break;
        }
        case 2: {
            std::cerr<<"It's empty."<<std::endl;
            break;
        }
    }
};

template <typename obj>
// overloads operator = for class object to deep copy.
// return:a const pointer to the current object
// the reference parameter rhs has to be maintained and
// released when function ends.
// the parameter can be a null pointer.
const Vector<obj>& Vector<obj>::operator=(const Vector<obj>& rhs) {
    if (this != &rhs) {
        delete [] objects;
        obj_size = rhs.obj_size;
        obj_capacity = rhs.obj_capacity;
        objects = new obj [capacity()];
        for (int i = 0;i < size();i++) {
            objects[i] = rhs.objects[i];
        }
    }
    return* this;
};

template <typename obj>
int Vector<obj>::size() const {
    return obj_size;
};

template <typename obj>
int Vector<obj>::capacity() const {
    return obj_capacity;
};

template <typename obj>
bool Vector<obj>::is_empty() {
    return size() == 0;
};

template <typename obj>
// function reference operator.
// i/o param:obj_index
// throws error when the given param is greater than size.
obj& Vector<obj>::operator[](int obj_index) {
    if (obj_index >= obj_size) warning(1);
    return objects[obj_index];
};

template <typename obj>
// function reference operator.
// i/o param:obj_index
// throw error when the given param is greater than size.
const obj& Vector<obj>::operator[](int obj_index) const {
    if (obj_index >= obj_size) warning(1);
    return objects[obj_index];
};

template <typename obj>
// throw error when objects is empty.
void Vector<obj>::printVector() {
    if (size() == 0) {
        warning(2);
    } else {
        for (int i = 0;i < size() - 1;++i) {
            std::cout<<objects[i]<<",";
        }
        std::cout<<objects[size() - 1]<<std::endl;
    }
};

template <typename obj>
// expands the array with proportionality coefficient 2.
// i/o param:new_size
// funciton call reserve().
// do nothing when new_size is less than the former one.
void Vector<obj>::resize(int new_size) {
    if (new_size > obj_capacity) reserve(2 * new_size + 1);
    if (new_size > obj_size) obj_size = new_size;
};

template <typename obj>
// update the capacity of objects.
// i/o param:new_capacity
// new a object to temporatily store elements.
void Vector<obj>::reserve(int new_capacity) {
    if (new_capacity >= obj_size) {
        obj_capacity = new_capacity;
        obj* temporary = objects;
        objects = new obj [new_capacity];
        for (int i = 0;i < obj_size;++i) {
            objects[i] = temporary[i];
        }
        delete [] temporary;
    }
    return;
};

template <typename obj>
const obj& Vector<obj>::back() const {
    return objects[obj_size - 1];
};

template <typename obj>
// enter a new element into the vector.
// i/o param:new_element
// function call reserve().
// when not call reserve(),the time complexity is O(n).
void Vector<obj>::push_back(const obj& new_element) {
    if (obj_size == obj_capacity) reserve(2 * obj_capacity + 1);
    objects[obj_size] = new_element;
    obj_size = obj_size + 1;
};

template <typename obj>
// shift out the last element.
void Vector<obj>::pop_back() {
    obj_size = obj_size - 1;
};

#else
#endif
