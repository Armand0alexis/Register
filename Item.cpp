
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

