#include <iostream>
#include <string>
#include <map>
#ifndef WAREHOUSE_H
#define WAREHOUSE_H
using namespace std;

class Warehouse{
    private:
        string name;
        map<string,int> products;
    
    public:
        Warehouse(string pname){ 
            name = pname ;
        }


        int getStock(string name){
            if (products.find(name) != products.end()){
                return products[name];
            }
            else{
                return -1;
            }
        }

        void getStock(){
            for (auto i = products.begin(); i != products.end(); i++){
                cout << i->first << " : " << i->second << endl;
            }
        }


        void updateStock(string name, int quantity){
            if (products.find(name) != products.end()){
                int currentQuantity = products[name];
                products[name] = currentQuantity + quantity;
            }
            else{
                products[name] = quantity;
                cout << name << " added to the warehouse." << endl;
            }
        }

        string getName() {
            return name;
        }

};

#endif // WAREHOUSE_H