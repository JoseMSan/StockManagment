#include "ECommerce.h"
#include "Product.h"
#include "Warehouse.h"
#include <iostream>
using namespace std;

int main(){
    int wharehouse;
    cout << "Enter the number of Warehouses you want to create: ";
    cin >> wharehouse;

    ECommerce ecommerce = ECommerce(wharehouse);
    while (true){
        int choice1;
        cout << "Enter the number of the option you want to select"<<endl;
        cout << "1. Add Product"<< endl;
        cout << "2. Move Products"<< endl;
        cout << "3. Get Stock"<< endl;
        cout << "4. Exit"<<endl;
        cin>> choice1;
        if(choice1==1){
            string type;
            string name;
            int price;
            int minStock;
            cout << "Enter 'i' if the product is international or enter 'n' if the product is national: "<<endl;
            cin >> type;
            cout << "Enter the name of the product: "<<endl;
            cin >> name;
            cout << "Enter the price of the product: "<<endl;
            cin >> price;
            if (type == "i"){
                cout << "Enter the lead time of the product in days: "<<endl;
                cin >> minStock;
                ecommerce.addInternational(name, price, minStock);
            }
            else if(type == "n"){
                cout << "Enter the minimum stock of the product: "<<endl;
                cin >> minStock;
                ecommerce.addNational(name,price,minStock);
            }
            else{
                cout << "Invalid input"<<endl;
            }

        }
        else if(choice1==2){
            string in;
            string out;
            int quantity;
            string name;
            cout << "Enter the name of the product: "<<endl;
            cin >> name;
            cout << "Where is "<< name << " coming from? "<<endl;
            cin >> in;
            cout << "Where is "<< name << " going to? "<<endl;
            cin >> out;
            cout << "Enter the quantity of the product: "<<endl;
            cin >> quantity;
            ecommerce.move(in, out, quantity,name);
        }
        else if(choice1==3){
            int choice2;
            string name;
            cout << "Enter the number of the option you want to select"<<endl;
            cout << "1. Get the stock of warehouse"<< endl;
            cout << "2. Get the stock of all products"<< endl;
            cin>> choice2;
            if(choice2==1){
                cout << "Enter the name of the warehouse: "<<endl;
                cin >> name;
                ecommerce.getStockWarehouse(name);
            }
            else if(choice2==2){
                ecommerce.getStock();
            }
            else{
                cout << "Invalid input"<<endl;
            }
        }
        else if(choice1==4){
            break;
        }
        else{
            cout << "Invalid choice"<<endl;
        }

    }
    cout << "Thank you for using our ecommerce system"<<endl;
    return 0;
}