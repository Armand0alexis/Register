
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Checkout.h"
using namespace std;

int main()
{
    
    ifstream infile;        //file containing items to be put in queue
    ofstream outfile;       //file containing output
    string infilename;      //input file name
    string outfilename;     //output file name
    string itemname;
    double price =0;
    double originalprice =0;
    
    Item item;
    Checkout queue;
    int itemCount = 0;
    double totalgroc = 0;
    double taxes = .0725;
    
    
    cout << "What is the name of the file (GroceryList.txt): ";
    cin >> infilename;
    infile.open(infilename.c_str());
    while(infile.fail())
    {
        cout << "Try another file to open (GroceryList.txt): ";
        cin >> infilename;
        infile.open(infilename.c_str());
    }
    
    
    //Enqueue Grocery List
    while(itemname != "endlist")
    {

        infile >> itemname;
        if(itemname == "endlist")
        {
            break;
        }
        infile >> price;
        item.setName(itemname);
        item.setPrice(price);
        queue.addItem(item);
        
        itemCount++;
        originalprice += price;
    }

     cout << "\nEnter name of the output file: ";
     cin >> outfilename;
     outfile.open(outfilename.c_str());
    
    outfile << "Check Out Queue Receipt:\n\n";
    outfile << left << setw(15) << "Items:";
    outfile << right << setw(10) << "Price:\n\n";
    
    //Dequeue Grocery list
  while(!queue.isEmpty())
    {
        item = queue.scanItem(outfile);
        itemname = item.getName();
        price = item.getPrice();
        cout << left << setw(15) << itemname << price << endl;
        outfile.precision(2);
        outfile.setf(ios::fixed);
        outfile << left << setw(15) <<  itemname;
        outfile << right << setw(10);
        outfile << price << endl;
        
        totalgroc += price;
        
    }
    
    taxes = totalgroc*taxes;
    outfile.precision(2);
    outfile.setf(ios::fixed);
    outfile << "\nTotal Items: " << itemCount << endl;
    outfile << "Total: $" << totalgroc << endl;
    outfile << "Taxes: $" << taxes << endl;
    outfile << "Total Due: $" << totalgroc+taxes << endl;
    outfile << "Total Savings: $" << originalprice-totalgroc << endl;
    
    
    infile.close();
    outfile.close();
    

    
    return 0;
}
