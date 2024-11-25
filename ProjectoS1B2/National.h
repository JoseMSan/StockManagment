#include "Product.h"
#include <iostream>
#include <string>
using namespace std;

class National : public Product {
    private:
        int minStock;
    public:
        National(string pname, double pprice, int pminStock): Product(pname, pprice) {
            minStock=pminStock;
        }

        int getMinStock(int lastMonth) const override {
            return minStock;
        }
};
