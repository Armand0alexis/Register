
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



