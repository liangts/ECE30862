#include <limits>
#include <iostream>
#include <exception>
#include <stdexcept>
#include "Set.h"

std::ostream& operator<<(std::ostream&, Set);

Set::Set(size_t set_max) : set_max(set_max){
    this->set_memory = new bool[set_max + 1];
    counter = 0L;
    for (size_t i = 0; i <= set_max; i++) {
        this->set_memory[i] = false;
    }
}
Set::Set(const Set& copy) : Set(copy.set_max) {
    this->counter = copy.counter + 1;

    memcpy(set_memory, copy.set_memory, sizeof(bool) * (copy.set_max + 1));
}

Set::~Set() {
    delete this->set_memory;
}

Set& Set::operator+(const unsigned int operand) {
    if ((size_t) operand > this->set_max) {
        throw new std::runtime_error("exceed set maximum");
    }
    this->set_memory[(size_t) operand] = true;
    return *this;
}
Set& Set::operator-(const unsigned int operand) {
    if ((size_t) operand > this->set_max) {
        throw new std::runtime_error("exceed set maximum");
    }
    this->set_memory[(size_t) operand] = false;
    return *this;
}
Set Set::operator&(Set& operand) {
    Set retSet = Set(this->set_max);
    for (size_t i = 0; i <= this->set_max; i++) {
        if (this->set_memory[i] && operand.set_memory[i]) {
            retSet = retSet + i;
        }
    }
    return retSet;
}
Set Set::operator~() {
    Set retSet = Set(this->set_max);
    for (size_t i = 0; i <= this->set_max; i++) {
        if (!this->set_memory[i]) {
            retSet = retSet + i;
        }
    }
    return retSet;
}
Set Set::operator/(Set& operand) {
    Set retSet = Set(this->set_max);
    for (size_t i = 0; i <= this->set_max; i++) {
        if (this->set_memory[i] && !operand.set_memory[i]) {
            retSet = retSet + i;
        }
    }
    return retSet;
}

Set& Set::operator=(const Set& copy) {
    this->counter = copy.counter + 1;

    delete this->set_memory;
    this->set_memory = new bool[this->set_max + 1];
    memcpy(set_memory, copy.set_memory, sizeof(bool) * (copy.set_max + 1));
    return *this;
}

std::ostream& operator<<(std::ostream& stream, Set set) {
    for (size_t i = 0; i <= set.getSetMax(); i++) {
        if (!set.contains((unsigned int) i)) continue;
        stream << i;
        bool flag = false;
        for (size_t j = i + 1; j <= set.getSetMax(); j++) {
            if (set.contains((unsigned int) j)) {
                flag = true;
                break;
            }
        }
        if (flag) stream << ',' << ' ';
    }
    return stream;
}
