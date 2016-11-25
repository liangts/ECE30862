#include <string>
#include <iostream>
class L {
public:
    int data;
    L() : data(0) { }
    L(int i) : data(i) { }
    virtual ~L() { }
    static void swap(L lO1, L lO2, L& lR1, L& lR2, L* lP1, L* lP2) {
        L tmpO = lO1;
        L& tmpR = lR1;
        tmpO = lO1; lO1 = lO2; lO2 = tmpO;
        tmpR = lR1; lR1 = lR2; lR2 = tmpR;
        tmpO.data = lP1->data; lP1->data = lP2->data; lP2->data = tmpO.data;
        lP1 = lP2;
    }
    friend std::ostream& operator<< (std::ostream& os, const L& m);
};
int main(int argc, char * argv[ ]) {
    L lO1(1); L lO2(2);
    L* t = new L(1); L lR1 = *t; t = new L(2); L lR2 = *t;
    L* lP1 = new L(1); L* lP2 = new L(2);
    std::cout << "lO1: " << lO1.data << ", lO2: " << lO2.data << std::endl; // lOa
    std::cout << "lR1: " << lR1.data << ", lR2: " << lR2.data << std::endl; // lRa
    std::cout << "lP1->data: " << lP1->data << ", lP2->data2: " << lP2->data << std::endl; // lXa
    std::cout << "lP1: " << lP1 << ", lP2: " << lP2 << std::endl; // lPa
    L::swap(lO1, lO2, lR1, lR2, lP1, lP2);
    std::cout << "lO1: " << lO1.data << ", lO2: " << lO2.data << std::endl; // lOb
    std::cout << "lR1: " << lR1.data << ", lR2: " << lR2.data << std::endl; // lRb
    std::cout << "lP1->data: " << lP1->data << ", lP2->data2: " << lP2->data << std::endl; // lXb
    std::cout << "lP1: " << lP1 << ", lP2: " << lP2 << std::endl; // lPb
}
