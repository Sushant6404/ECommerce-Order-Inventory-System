#ifndef CART_ITEM_H
#define CART_ITEM_H

#include "Product.h"

class CartItem
{
private:
  Product product;
  int quantity;

public:
  CartItem(Product product, int quantity)
  {
    this->product = product;
    this->quantity = quantity;
  }

  Product getProduct() const
  {
    return product;
  }

  int getQuantity() const
  {
    return quantity;
  }

  void setQuantity(int newQuantity)
  {
    quantity = newQuantity;
  }

  double getSubtotal() const
  {
    return product.getPrice() * quantity;
  }

  void displayCartItem() const
  {
    cout << "\nProduct ID : " << product.getProductId();
    cout << "\nName       : " << product.getName();
    cout << "\nPrice      : Rs. " << product.getPrice();
    cout << "\nQuantity   : " << quantity;
    cout << "\nSubtotal   : Rs. " << getSubtotal();
    cout << "\n-----------------------------\n";
  }
};

#endif