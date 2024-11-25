#include "Product.h"
#include <iostream>
#include <string>
using namespace std;

class International : public Product {
    private:
        int leadTime; // days
    public:
        International(string pname, double pprice, int pleadTime): Product(pname, pprice) {
            leadTime=pleadTime;
        }

        int getMinStock(int lastMonth) const override {
            return lastMonth*leadTime/30;
        }
};