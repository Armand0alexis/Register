<h1 align="center">Grocery Store Checkout</h1>

## Overview 

<p>
	Oftentimes grocery stores have a conveyor belt at the checkout which brings the products to the person at the register so that they can be scanned. Our project attempts to model this using an Item class to represent the grocery store products, a Checkout class (essentially a queue) to represent the conveyor belt, and a driver program that shows an example scenario where a customer loads the Checkout with items and they are scanned to produce a receipt.
</p>

#### Contents of Item.h 

``` C++
#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using namespace std;

class Item
{
private:
    string name;
    double price;
public:
    Item();
    Item(string, double);
    void setName(string);
    string getName();
    void setPrice(double);
    double getPrice();
};

#endif /* ITEM_H_ */
```

#### Contents of Item.cpp 

```C++

#include "Item.h"

//default constructor
Item::Item()
{
    name = "default";
    price = 0;
}
//parameterized constructor
Item::Item(string nm, double pr)
{
    name = nm;
    price = pr;
}
//sets name of item
void Item::setName(string nm)
{
    name = nm;
}
//returns name of item
string Item::getName()
{
    return name;
}
//sets price of item
void Item::setPrice(double pr)
{
    price = pr;
}
//returns price of item
double Item::getPrice()
{
    return price;
}

```

#### Analysis of Item 
<p>
		An item is an object with a name and a price that represents a product at a grocery store.
</p>

<h4 align="center">Time Complexity of Item::Item():O(1) </h4>
<p>
		This is the default constructor for an Item. It sets the name and price to default values. The function contains a constant number of expressions which gives it a constant efficiency.
</p>

<h4 align="center">Time Complexity for Item::Item(string nm, double pr):O(1) </h4>
<p>
	This is a parameterized constructor for an Item. It sets the name and price to match the provided arguments. The function contains a constant number of expressions which gives it a constant efficiency.
</p>

<h4 align="center">Time Complexity for void Item::setName(string nm): O(1)</h4>
<p>
	setName will assign the value of the provided argument to the Item’s name member. The function contains a constant number of expressions which gives it a constant efficiency.
</p>

<h4 align="center"> Time Complexity for string Item::getName(): O(1)</h4>
<p>
	getName will return the value of the Item’s name member. The function contains a constant number of expressions which gives it a constant efficiency.
</p>

<h4 align="center">Time Complexity for void Item::setPrice(double pr): O(1)</h4>
<p>
	setPrice will assign the value of the provided argument to the Item’s price member. The function contains a constant number of expressions which gives it a constant efficiency.
</p>

<h4 align="center">Time Complexity for double Item::getPrice(): O(1)</h4>
<p>
	getPrice will return the value of the Item’s price member. The function contains a constant number of expressions which gives it a constant efficiency.
</p>

#### Contents of Checkout.h 

```C++ 

#ifndef CHECKOUT_H_
#define CHECKOUT_H_
#include "Item.h"
#include <iostream>
using namespace std;


struct Node
{
    Item info;
    Node* next = NULL;
};

class Checkout
{
private:
    Node* front;
    Node* rear;
    std::string itemsOnSale[5];
    
public:
    Checkout();
    Checkout(const Checkout&);
    ~Checkout();
    bool isEmpty();
    bool isFull();
    void addItem(Item);
    Item scanItem(std::ofstream & outfile);
    void checkDiscount(Item&, std::ofstream & outfile);
    
    /*
     void insertItem(Item);
     void removeItem(Item);
     */
};

class EmptyCheckout
{
};

class FullCheckout
{
};

#endif /* CHECKOUT_H_ */
```

#### Contents of Checkout.cpp 

```C++ 

#include "Checkout.h"
#include <fstream>
//default constructor
Checkout::Checkout() : itemsOnSale{"banana", "lunchable", "wheatbread", "soap", "coffee"}
{
    front = NULL;
    rear = NULL;
}
//copy constructor
Checkout::Checkout(const Checkout& copy) : itemsOnSale{"banana", "lunchable", "wheatbread", "soap", "coffee"}
{
    front = NULL;
    rear = NULL;
    Node* temp = copy.front;
    while(temp != NULL)
    {
        addItem(temp->info);
        temp = temp->next;
    }
}
//destructor
Checkout::~Checkout()
{
    Node* temp;
    while(front != NULL)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}
//returns true if the checkout is empty
bool Checkout::isEmpty()
{
    if(front == NULL && rear == NULL)
        return true;
    else
        return false;
}
//returns false if a new node cannot be made
bool Checkout::isFull()
{
    try
    {
        Node* temp;
        temp = new Node;
        delete temp;
        return false;
    }
    catch(std::bad_alloc)
    {
        return true;
    }
}
//adds an item to the rear of the line of checkout items. Throws exception if Checkout is full.
void Checkout::addItem(Item item)
{
    if(isFull())
        throw FullCheckout();
    else
    {
        Node* newNode;
        newNode = new Node;
        newNode->info = item;
        newNode->next = NULL;
        if(rear == NULL)
            front = newNode;
        else
            rear->next = newNode;
        rear = newNode;
    }
}

void Checkout::checkDiscount(Item& item, std::ofstream &outfile)
{
    double discounted;
    double price;
    for(string n : itemsOnSale)
    {
        if (item.getName() == n)
        {
            price = item.getPrice();
            discounted = price - (price * .25);
            item.setPrice(discounted);
            outfile << "Discount applied for " << item.getName() << "! ";
            outfile << " Original Price: " << price;
            outfile << " Discounted price: " << item.getPrice() << endl;
            
            break;
        }
    }
    
}

//remove an item from the front and returns it. Throws exception if Checkout is empty.
Item Checkout::scanItem(std::ofstream & outfile)
{
    Item item;
    if(isEmpty())
        throw EmptyCheckout();
    else
    {
        Node* temp;
        temp = front;
        item = temp->info;
        front = front->next;
        if(front == NULL)
            rear = NULL;
        delete temp;
    }
    checkDiscount(item, outfile);
    return item;
}

```

#### Analysis of Checkout 
<p>
		Checkout is a slightly modified linked list based queue data structure that represents the conveyor belt at the store checkout. Those modifications include name changes for members, a private member array of strings that serve as the store’s list of items on sale, the checkDiscount function that modifies items if their name matches an item on the sale list, and the inclusion of checkDiscount in the dequeue method.
</p>

<h4 align="center">Time Complexity for Checkout::Checkout(): O(1)</h4>
<p>
	The class constructor is called when a new object of the class is created and it initially sets the classes private Node pointers, Front and Rear to NULL. The class constructor also initializes the array of strings that is part of its private members, with certain items that are considered to be on sale at a discounted price. This array will serve as a way to check and compare against items that we have in our queue once we scan each item. Since the class constructor only sets the Front and Rear Pointers to NULL, and initializes the array of strings, giving this algorithm a constant runtime and  time complexity of O(1).
</p>

<h4 align="center">Time Complexity of Checkout::Checkout(const Checkout& copy): O(n)</h4>
<p>
	The copy constructor is called whenever there is a Checkout instance that is being assigned the same values as an already existing Checkout instance. The array member is explicitly initialized before the actual body of the copy constructor is executed. Then, like the default constructor, front and rear are set to NULL. On line 15, a temporary Node pointer is created and assigned to the front of the queue we are copying from. Then, a while loop is initiated and runs as long as the temporary pointer is not NULL. This causes the temp pointer to traverse through the queue as addItem() is called, which takes the items from the original queue and adds them to the new queue being created. This must happen for every item in the queue we are copying from, giving this algorithm a linear runtime and time complexity O(n).
</p>

<h4 align="center">Time Complexity for Checkout::~Checkout(): O(n)</h4>
<p>
	The destructor creates a temporary Node* on line 25, which is a constant time operation. Then, a while loop is initiated in which the temp pointer is assigned to the front of the queue. Then, the private member front is assigned to its successor. Temp is then deleted, which deallocates the memory previously occupied by front. This continues until front is equal to NULL, indicating that the queue is empty. Since all the nodes in the queue must be visited and deleted, this is a linear algorithm with a time complexity of O(n).
</p>

<h4 align="center">Time Complexity of bool Checkout::isEmpty(): O(1)</h4>
<p>
		isEmpty is a member function of the Checkout class used to check if the Checkout contains no items. On line 36 is the beginning of an if statement. The condition is that the front and rear are both equal to NULL. If the condition is true line 37 is executed. When this happens the function returns true. If the condition is false, then line 39 will be executed, returning false. There are no loops in this function and the number of expressions to evaluate are constant giving the function worst cast complexity O(1).
</p>

<h4 align="center">Time Complexity of bool Checkout::isFull(): O(1)</h4>
<p>
	isFull is a member function of the Checkout class that is used to check if the checkout is full. Lines 46 to 49 are within a try block. Line 46 and 47 create a node pointer and set it to point to a dynamically allocated node. Line 48 deletes this new node. If execution of the function makes it to line 49 without throwing an exception, then the function returns false. This means the Checkout is not full because there is enough memory for another item to be added to the Checkout. The catch at line 51 will execute line 53 if a bad memory allocation exception is thrown during the try block. When line 53 is executed the function returns true meaning that there is not enough available memory for a new node and the Checkout is full. This function has no loops and a constant number of expressions to evaluate giving it a time complexity of O(1).
</p>

<h4 align="center">Time Complexity of void Checkout::addItem(Item item): O(1)</h4>
<p>
		AddItem function is a member of the Checkout class it simulates an adding of an item to a conveyor belt so that it later can be scanned. So the function takes an Item type object to be added to the Queue. First the function checks if the Queue isFull via a member function, line 59, which determines if the queue has reached its maximum length, if the condition is true it will throw a FullCheckout() exception. If the condition is false it will proceed to adding a new item to the queue. In line 63-66 we create a new Node and assign the item to the nodes info, and set its next to NULL. In line 67  it checks to see if the rear is equal to NULL, if it is we assign the newNode to the front because we have an empty queue. If that is not the case since we keep track of the rear pointer we then assign the newNode to the last position in the Queue. This simulates adding things to the conveyor belt as you unloaded from your shopping cart. In this case our Data file that acts like our shopping cart.. Therefore this algorithm for adding Items to the Queue will be constant runtime and time complexity of O(1), because we are only adding items to the end of the list and not in any specific order.
</p>

<h4 align="center">Time Complexity of Checkout::checkDiscount: O(1) or O(j)</h4>
<p>
	( j is the number of items on sale in the store)
After being called by the scanItem function, checkDiscount creates two doubles, discounted and price, in case there is a discount to be applied. Then, on line 79, a for loop is initiated to go through all elements in the itemsOnSale private variable. In the for loop, there is a comparison between the name of the item being scanned and the current element of the array. If there is a match, the price of the item is fetched, the discount is calculated and applied to the original price, and is then recorded on the filestream. Then the loop breaks. Within the for loop, all assignments and operations are O(1), but since the worst case scenario is that the name of the item being scanned is not in the array, we must search through potentially the entire array, which has a time complexity of O(n).
</p>

<h4 align="center">Time Complexity of Item Checkout::scanItem(std::ofstream & outfile): O(1) or O(j) (j is the number of items on sale at the grocery store)</h4>
<p>
		scanItem is a member function of the Checkout class that simulates an item being taken off of the conveyor belt and scanned. It takes an ofstream by reference as a parameter and uses it for a call of the checkDiscount member function. On line 98 is an if statement that checks if the Checkout is empty via the isEmpty member function. If this condition is true scanItem will throw an EmptyCheckout() exception. If the Checkout is not empty lines 102-108 will be executed. During this block a temporary pointer is set to the front of the Checkout, the value of that item is saved in an Item object that was created on line 97, the front pointer of the Checkout is moved to the next position, and the memory is deallocated for the node that the temporary pointer is pointing at. On line 106 is another if statement which checks if the front has passed the end of the Checkout. If this is true then the rear pointer is also set to NULL meaning that the Checkout is now empty. On line 110 the checkDiscount member function is called to possibly update the price of the item based upon what items are on sale. The Item containing the values of what used to be the front item in the Checkout is returned on line 111. scanItem does not contain any loops  and a constant number of expressions up to line 110 when checkDiscount is called which has an efficiency of O(j) where j is the number of items on sale at the grocery store. This gives scanItem an efficiency of O(1) or O(j).
</p>

#### Contents of CheckoutDriver.cpp 

```C++
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

```

#### Analysis of CheckoutDriver 
<p>
		The CheckoutDriver is designed to implement our interpretation of a check out at a grocery store with loading things to the conveyor belt. At that time the cashier scans them one by one as they are placed in the cover belt in a first in first out method. As they are being scanned we check to see if that certain item is on sale, if it is we apply a discount to that item. We implement this by using a linked list Queue. In our CheckoutDriver we are using ifstream and ofstream, we use ifstream to read off the items that we have in the data file we named “GroceryList.txt”  this file contains all of the items names and prices that we purchasing. In our CheckoutDriver we are also using local variables that will keep track of the items, original total price, taxes, and number of items.
</p>
<p>
		 The first thing that happens in our driver in lines 24-32, we ask the user to open up the text file that contains all of the items we are purchasing. We can think of this like our shopping cart that holds all our groceries. In this block we are using a string that holds what the user entered, we are also using a while loop because if the user entered a file name that is not in the project directory it will ask the user to re-entered a correct file name. In lines 34-48 after the user has entered a valid file name we implement the process of inserting all of the items into the queue. We do this by using a while loop, having the ifstream infile reading all of the “itemname” and “price” of the text file. Inside the loop we have an if statement which will end the while loop if we have reached the end of our text file. Every time the infile reads a name and price we use an item type object so set its name and price using member functions setPrice(), setName(), and then pass that item type to the addItem function and store it the queue. Inside that same block we keep track of the original price of each item and a count of each item being stored in the queue. A time complexity of reading items in the text file and inserting them into the queue would be constant time O(1). In lines 50-52 the user then enters a file name that will be written to using ofstream and it will serve as a customers receipt that will show everything that they have purchased. In lines 54-56 we are writing to our outfile and formatting how the Checkout Receipt will look like. In lines 58-70 we implement the process of scanning each item that is in the queue(“conveyor belt”).  We implement this process by using a while loop with a condition to keep looping as long as queue is not empty using the member function isEmpty to check if it is empty. In this block we scanItem (“Dequeue”) from our conveyor belt. As this is happening scanItem returns an item type and we assign that item type to our item object. Using the item we can retrieve the items name and price using the member functions getName() and getPrice(); after we have scanItem and got the items name and price we use outfile which writes the name and price to our receipt file. In that same block we use setw() and .precision() to format the customers receipt. Using a local variable totalgroc we are keeping track of the new price of each item after it has been scanned. In lines 72-79, we calculate the the taxes and total prices of all of the items we purchased. We use our local variables and outfile  to write to the text file the number of items, total, taxes, total due, and total savings. In lines 81-82, we use infile.close() to close out “GroceryList.txt” file and oufile.close() to close the file that we created that served as the customer receipt.
</p>

#### Example of GroceryList.txt file 

```text
apple
4.0
pears 
3.0
milk
2.0
celery
3.4
sprouts
2.0
ketchup
4.0
mustard
2.0
```
