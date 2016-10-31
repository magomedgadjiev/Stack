#ifndef stack_cpp
#define stack_cpp
#pragma once

#include <iostream>
#include <new>
#include <stdexcept>
#include <vector>
#include <memory>

size_t max(size_t a, size_t b) {
    return a > b ? a : b;
}

class bitset {
public:
    explicit bitset(size_t size) /*strong*/;

    bitset(bitset const &other) = delete;

    auto operator=(bitset const &other) -> bitset & = delete;

    bitset(bitset &&other) = delete;

    auto operator=(bitset &&other) -> bitset & = delete;

    auto set(size_t index) /*strong*/ -> void;

    auto reset(size_t index) /*strong*/ -> void;

    auto test(size_t index) /*strong*/ -> bool;

    auto size() /*noexcept*/ -> size_t;

    auto counter() /*noexcept*/ -> size_t;

private:
    std::unique_ptr<bool[]> ptr_;
    size_t size_;
    size_t counter_;
};

bitset::bitset(size_t size)
    :
{
    ;
}

auto bitset::size() -> size_t {
    return size_;
}

auto bitset::counter() -> size_t {
    return counter_;
}

auto bitset::set(size_t index) -> void {
    if(index <= size_ || index < 0){
        std::out_of_range("Error");
    }
    ptr_[index] = true;
}

auto bitset::reset(size_t index) -> void {
    if(index >= size_ || index < 0){
        std::out_of_range("Error");
    }
    ptr_[index] = false;
}

auto bitset::test(size_t index) -> bool {
    if(index >= size_ || index < 0){
        std::out_of_range("Error");
    }
    return ptr_[index];
}


template<typename T>
class Allocator {
protected:
public:
    explicit
    Allocator( std::size_t size = 0 ) /*strong*/;
    Allocator( Allocator const & other ) /*strong*/;
    auto operator =( Allocator const & other ) -> Allocator & = delete;
    ~Allocator();

    auto resize() /*strong*/ -> void;

    auto construct(T * ptr, T const & value ) /*strong*/ -> void;
    auto destroy( T * ptr ) /*noexcept*/ -> void;

    auto get() /*noexcept*/ -> T *;
    auto get() const /*noexcept*/ -> T const *;

    auto count() const /*noexcept*/ -> size_t;
    auto full() const /*noexcept*/ -> bool;
    auto empty() const /*noexcept*/ -> bool;
private:
    auto destroy( T * first, T * last ) /*noexcept*/ -> void;
    auto swap( Allocator &other ) /*noexcept*/ -> void;


    T * ptr_;
    size_t size_;
    std::unique_ptr<bitset> map_;
};

template<typename T>
Allocator<T>::Allocator(size_t size)
        : ptr_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))),
          size_(size),
          map_(new bitset(size))
{ }

template <typename T>
Allocator<T>::Allocator(Allocator const &other)
        :   size_(other.size_),
            map_(new bitset(other.size_))

{
    if (this != &other){
        if (empty()){
            ptr_(static_cast<T *>(size_ == 0 ? nullptr : operator new(size_ * sizeof(T))))
        }
    }
    for (int i = 0; i < size_; ++i) {
        construct(ptr_ + i, other.ptr_[i]);
    }
}

template<typename T>
Allocator<T>::~Allocator() {
    operator delete(ptr_);
}

template<typename T>
auto Allocator<T>::swap(Allocator<T> &other) -> void {
    std::unique_ptr<bitset[]> tmp(&map_);
    map_ = &other.map_;
    other.map_ = &map_;
    std::swap(ptr_, other.ptr_);
    std::swap(size_, other.size_);
}

template<typename T>
void Allocator<T>::construct(T *ptr, T const &value) {
    new(ptr) T(value);
}

template<typename T>
void Allocator<T>::destroy(T *ptr) noexcept {
    ptr->~T();
}

template<typename T>
auto Allocator<T>::resize() -> void {
    size_t new_size = max(size_ * 2, 1);
    map_ = new bool[new_size];
    for (int i = 0; i < ; ++i) {
        
    }
}

template<typename T>
auto Allocator<T>::get() -> T * {
    return ptr_;
}

template<typename T>
auto Allocator<T>::get() const -> T * {
    return ptr_;
}

template<typename T>
auto Allocator<T>::count() const -> size_t {
    return map_->counter();
}

template<typename T>
auto Allocator<T>::full() const -> bool {
    return map_->counter() == size_;
}

auto Allocator::empty() const -> bool {
    return map_->counter() == 0;
}

template<typename T>
auto Allocator<T>::destroy(T *first, T *last) -> void {
    for (; first != last; ++first) {
        destroy(&*first);
    }
}



template<typename T>
class Stack{
public:
    explicit
    Stack( size_t size = 0 );
    auto operator =( Stack const & other ) /*strong*/ -> Stack &;

    auto empty() const /*noexcept*/ -> bool;
    auto count() const /*noexcept*/ -> size_t;

    auto push( T const & value ) /*strong*/ -> void;
    auto pop() /*strong*/ -> void;
    auto top() /*strong*/ -> T &;
    auto top() const /*strong*/ -> T const &;
private:
    Allocator<T> allocator_;

    auto throw_is_empty() const -> void;
};

template<typename T>
Stack<T>::Stack(size_t size)
        : Allocator<T>(size) {
    ;
}

template<typename T>
Stack<T>::Stack(const Stack &tmp)
        : allocator_(tmp.allocator_) { }

template<typename T>
auto Stack<T>::count() const -> size_t {
    return allocator_.count();
}

template<typename T>
auto Stack<T>::push(const T &value) -> void {
    if (allocator_.full()) {
        size_t array_size = max(allocator_.count() * 2, 1);

        Stack temp{array_size};
        while (temp.count() < allocator_.count()) {
            temp.push(allocator_.get()[temp.count()]);
        }
        allocator_.;
    }
    allocator_.construct(allocator_.get() + allocator_.count(), value);
}

template<typename T>
auto Stack<T>::pop() -> void {
    throw_is_empty();
    --allocator_.get();
}

template<typename T>
auto Stack<T>::operator=(const Stack<T> &tmp) -> Stack & {
    if (this != &tmp) {
        Stack(tmp).swap(*this);
    }
    return *this;
}

template<typename T>
auto Stack<T>::top() const -> T const & {
    throw_is_empty();
    return this->ptr_[this->count_ - 1];
}

template<typename T>
auto Stack<T>::top() -> const T & {
    throw_is_empty();
    return this->ptr_[this->count_ - 1];
}

template<typename T>
auto Stack<T>::empty() const -> bool {
    return this->count_ == 0;
}

auto Stack::throw_is_empty() const -> void {
    if (empty()) {
        std::logic_error("stack is empty");
    }
}




#endif
