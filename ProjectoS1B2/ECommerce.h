#include "Warehouse.h"
#include "Product.h"
#include "National.h"
#include "International.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm> 
#include <cctype> 
using namespace std;

class ECommerce {
    private:
        vector<Warehouse> warehouses;
        vector<unique_ptr<Product>> products;
        map<string,int> lastMonth;
    public:
        ECommerce(int pwarehouses) {
            cout << "Welcome to ECommerce!" << endl;
            for (int i = 1; i <= pwarehouses; ++i) {
                    string name;
                    cout << "Enter the name of warehouse number " << i << ": ";
                    cin >> name;
                    Warehouse warehouse = Warehouse(name);
                    warehouses.emplace_back(warehouse);
                }
        }   

    void addNational(string pname, double pprice, int pother){
        products.push_back(make_unique<National>(pname, pprice, pother));
        cout<< "Product added successfully."<< pname << endl;
    }

    void addInternational(string pname, double pprice, int pother){
        products.push_back(make_unique<International>(pname, pprice, pother));
        cout<< "Product added successfully."<< pname << endl;
    }
    
    void displayProducts(){
        for (auto& product : products) {
            cout << product->getName() << " " << product->getPrice() << endl;
        }
    }

    // gets stock of a product in every warehouse
    int getStock(string name){
        int totalStock = 0;
        for (auto& warehouse : warehouses) {
            int stock = warehouse.getStock(name);
            if (stock != -1) {
                totalStock += stock;
            }    
        }    
        if (totalStock != 0) {
            return totalStock;
        } 
        else{
            return 0;
        }
    }

    // gets stock of a product in a specific warehouse
    void getStock(string name, string warehouseName){
        for (auto& warehouse : warehouses) {
            if (warehouseName == warehouse.getName()) {
                int stock = warehouse.getStock(name);
                if (stock != -1) {
                    cout << "Stock of " << name << " in " << warehouseName << " is " << stock << endl;
                }
                else{
                    cout << "No stock of " << name << " found in " << warehouseName << endl;
                }
            }
        }
    }

    // gets stock of every product in every warehouse
    void getStock(){
        for (auto& warehouse : warehouses) {
            cout << "Warehouse: " << warehouse.getName() << endl;
            warehouse.getStock();
        }
        int totalMoney=0;
        for (auto& product : products) {
            int stock = getStock(product->getName());
            totalMoney+=stock*product->getPrice();
        }
        cout << "Total money: " << totalMoney << endl;
    }

    // gets stock of every product in a specific warehouse
    void getStockWarehouse(string name){
        for (auto& warehouse : warehouses) {
            if (name == warehouse.getName()) {
                cout << "Warehouse: " << name << endl;
                warehouse.getStock();
            }
        }
    }

    void move(string in, string out, int quantity, string productName){
        if(in == out){
            cout << "You can't move stock from the same warehouse." << endl;
        }
        else if(in == "in" && out == "out"){
            cout << "You need to move a product into a warehouse or out of a warehouse." << endl;
        }
        // if the product comes from the outside and goes into the warehouse
        // just update the stock of the warehouse
        else if(in == "in"){
            bool found = false;
            for (auto& warehouse : warehouses) {
                if (out == warehouse.getName()) {
                    found = true;
                    warehouse.updateStock(productName,quantity);
                }
            }
            if(found==false){
                cout<< "The destination warehouse does not exist"<<endl;
                cout<< "No changes made"<<endl;
            }
        }
        else{
            bool found = false;
            for (auto& warehouse : warehouses) {
                if (in == warehouse.getName()) {
                    found = true; // found the warehouse where is comming from
                    int stock = warehouse.getStock(productName);
                    if (stock != -1) {
                        if (stock >= quantity) {
                            // if the product is going to the outside of the warehouses
                            // Thats when we need to update lastMonth
                            // thats when we validate if we need to re-order more stock
                            if (out == "out") {
                                for( int i = 0; i < products.size(); i++){
                                    // update lastmonth
                                    if( lastMonth.find(productName) != lastMonth.end()){
                                        lastMonth[productName] += quantity;
                                    }
                                    else{
                                        lastMonth[productName] = quantity;
                                    }
                                    // check minStock
                                    if (productName == products[i]->getName()){
                                        int lastMonthOfProduct = lastMonth[productName];
                                        int minStock = products[i]->getMinStock(lastMonthOfProduct);
                                        // get stock in all warehouses
                                        int stockInAllWarehouses = getStock(productName);
                                        if (stockInAllWarehouses - quantity < minStock){
                                            cout << endl;
                                            cout << "!!!!" << endl;
                                            cout << "You need to re-order more stock of " << productName << endl;
                                            cout << "!!!!" << endl;
                                            cout << "your current stock is: " << stock-quantity << endl;
                                            cout << "your min stock is: " << minStock << endl;
                                            cout << "!!!!" << endl;
                                        }
                                    }
                                }
                            }
                            else{
                                // modify the stock of the warehouse where is going to
                                for (auto& warehouse : warehouses) {
                                    if (out == warehouse.getName()) {
                                        warehouse.updateStock(productName,quantity);
                                    }
                                }    
                            }
                            warehouse.updateStock(productName, (quantity*-1));
                            cout << "Moved " << quantity << " " << productName << " from " << in <<endl;
                        }
                        // if there is not enogh stock in the warehouse to move the product
                        else{
                        cout << "There is not enough stock in " << in << " to move " << productName << endl;
                        cout << "Current stock of " << productName << " is: " << stock << endl;
                        }
                    }
                    // if there is no stock of the product in the warehouse
                    else{
                        cout << "There is no stock of " << productName << " in " << in << endl;
                    }
                }
            }
            // display if the product comes from an unvalid place
            if(found==false){
                cout << "Enter a valid name of where does the product comes from" << endl;
            }
        }    
    }
};