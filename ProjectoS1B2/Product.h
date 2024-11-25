#include <iostream>
#include <string>
#ifndef PRODUCT_H
#define PRODUCT_H
using namespace std;

class Product{
    protected:
        string name;
        double price;
    public:
        Product(string pname, double pprice){
            name = pname;
            price = pprice;
        }
        virtual ~Product() {
            cout << "Product deleted"<< name << endl;
        };

        string getName(){
            return name;
        }
        double getPrice(){
            return price;
        }
        virtual int getMinStock(int lastMonth) const =0;

        void setPrice(int pprice){
            price = pprice;
        }

};

#endif // PRODUCT_H