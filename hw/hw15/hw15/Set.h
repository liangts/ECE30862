#include <limits>
#include <iostream>
#include <exception>
#include <stdexcept>

class Set {
private:
    bool* set_memory;
    int max;
    int count;
public:
    explicit Set(int);
    Set(const Set&);
    ~Set();
    Set& operator+(const unsigned int);
    Set& operator-(const unsigned int);
    Set  operator&(Set&);
    Set  operator~();
    Set  operator/(Set&);
    Set& operator=(const Set&);
    
    int getSetMax();
    bool contains(const unsigned int operand);
    int getCopyCount();
};


std::ostream& operator<<(std::ostream&, Set);

int Set::getSetMax(){
    return this->max;
}

bool Set::contains(const unsigned int operand){
    if (operand > this->max)
        return false;
    return this->set_memory[operand];
}

int Set::getCopyCount(){
    return count;
}

Set::Set(int max) : max(max){
    this->set_memory = new bool[max + 1];
    count = 0L;
    for (int i = 0; i <= max; i++) {
        this->set_memory[i] = false;
    }
}
Set::Set(const Set& copy) : Set(copy.max) {
    this->count = copy.count + 1;

    memcpy(set_memory, copy.set_memory, sizeof(bool) * (copy.max + 1));
}

Set::~Set() {
    delete this->set_memory;
}

Set& Set::operator+(const unsigned int operand) {
    if ((int) operand > this->max) {
        return *this;
    }
    this->set_memory[(int) operand] = true;
    return *this;
}
Set& Set::operator-(const unsigned int operand) {
    if ((int) operand > this->max) {
        return *this;
    }
    this->set_memory[(int) operand] = false;
    return *this;
}
Set  Set::operator&(Set& operand) {
    Set retSet = Set(this->max);
    for (int i = 0; i <= this->max; i++) {
        if (this->set_memory[i] && operand.set_memory[i]) {
            retSet = retSet + i;
        }
    }
    return retSet;
}
Set  Set::operator~() {
    Set retSet = Set(this->max);
    for (int i = 0; i <= this->max; i++) {
        if (!this->set_memory[i]) {
            retSet = retSet + i;
        }
    }
    return retSet;
}
Set Set::operator/(Set& operand) {
    Set retSet = Set(this->max);
    for (int i = 0; i <= this->max; i++) {
        if (this->set_memory[i] && !operand.set_memory[i]) {
            retSet = retSet + i;
        }
    }
    return retSet;
}
Set& Set::operator=(const Set& copy) {
    this->count = copy.count + 1;

    delete this->set_memory;
    this->set_memory = new bool[this->max + 1];
    memcpy(set_memory, copy.set_memory, sizeof(bool) * (copy.max + 1));
    return *this;
}

std::ostream& operator<<(std::ostream& stream, Set set) {
    for (int i = 0; i <= set.getSetMax(); i++) {
        if (!set.contains((unsigned int) i)) continue;
        stream << i;
        bool flag = false;
        for (int j = i + 1; j <= set.getSetMax(); j++) {
            if (set.contains((unsigned int) j)) {
                flag = true;
                break;
            }
        }
        if (flag) stream << ',' << ' ';
    }
    return stream;
}
