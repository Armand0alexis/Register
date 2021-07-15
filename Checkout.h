
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

