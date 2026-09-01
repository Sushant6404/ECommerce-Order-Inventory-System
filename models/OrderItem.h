#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include "Product.h"

class OrderItem
{
private:
  int productId;
  string productName;
  double price;
  int quantity;

public:
  OrderItem(
      int id,
      string name,
      double productPrice,
      int qty)
  {
    productId = id;
    productName = name;
    price = productPrice;
    quantity = qty;
  }

  int getProductId() const
  {
    return productId;
  }

  int getQuantity() const
  {
    return quantity;
  }

  double getSubtotal() const
  {
    return price * quantity;
  }

  void displayOrderItem() const
  {
    cout << "\nProduct ID : " << productId;
    cout << "\nName       : " << productName;
    cout << "\nPrice      : Rs. " << price;
    cout << "\nQuantity   : " << quantity;
    cout << "\nSubtotal   : Rs. " << getSubtotal();
    cout << "\n-----------------------------\n";
  }
};

#endif