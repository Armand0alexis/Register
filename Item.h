
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
