#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include "Product.h"

using namespace std;

// ============================================================
// CART ITEM
// ============================================================

class CartItem
{
private:
  Product product;
  int quantity;

public:
  CartItem(
      const Product &product,
      int quantity)
      : product(product),
        quantity(quantity)
  {
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
    if (newQuantity > 0)
    {
      quantity = newQuantity;
    }
  }

  double getSubtotal() const
  {
    return product.getPrice() * quantity;
  }

  void displayCartItem() const
  {
    cout << "\nProduct ID : "
         << product.getProductId();

    cout << "\nName       : "
         << product.getName();

    cout << "\nPrice      : Rs. "
         << product.getPrice();

    cout << "\nQuantity   : "
         << quantity;

    cout << "\nSubtotal   : Rs. "
         << getSubtotal();

    cout << "\n------------------------------------\n";
  }
};

// ============================================================
// CART
// ============================================================

class Cart
{
private:
  vector<CartItem> items;

public:
  void addProduct(
      const Product &product,
      int quantity)
  {
    if (quantity <= 0)
    {
      cout << "\nQuantity must be greater than 0.\n";
      return;
    }

    if (quantity > product.getStock())
    {
      cout << "\nInsufficient stock.\n";
      return;
    }

    for (CartItem &item : items)
    {
      if (item.getProduct().getProductId() ==
          product.getProductId())
      {
        int newQuantity =
            item.getQuantity() + quantity;

        if (newQuantity > product.getStock())
        {
          cout << "\nRequested quantity exceeds available stock.\n";
          return;
        }

        item.setQuantity(newQuantity);

        cout << "\nCart quantity updated successfully.\n";
        return;
      }
    }

    items.push_back(
        CartItem(product, quantity));

    cout << "\nProduct added to cart successfully.\n";
  }

  void removeProduct(int productId)
  {
    for (auto it = items.begin();
         it != items.end();
         ++it)
    {
      if (it->getProduct().getProductId() ==
          productId)
      {
        items.erase(it);

        cout << "\nProduct removed from cart successfully.\n";
        return;
      }
    }

    cout << "\nProduct not found in cart.\n";
  }

  void updateQuantity(
      int productId,
      int newQuantity)
  {
    if (newQuantity <= 0)
    {
      cout << "\nQuantity must be greater than 0.\n";
      return;
    }

    for (CartItem &item : items)
    {
      if (item.getProduct().getProductId() ==
          productId)
      {
        if (newQuantity >
            item.getProduct().getStock())
        {
          cout << "\nInsufficient stock.\n";
          return;
        }

        item.setQuantity(newQuantity);

        cout << "\nQuantity updated successfully.\n";
        return;
      }
    }

    cout << "\nProduct not found in cart.\n";
  }

  double calculateTotal() const
  {
    double total = 0.0;

    for (const CartItem &item : items)
    {
      total += item.getSubtotal();
    }

    return total;
  }

  void displayCart() const
  {
    if (items.empty())
    {
      cout << "\nYour cart is empty.\n";
      return;
    }

    cout << "\n====================================";
    cout << "\n            SHOPPING CART";
    cout << "\n====================================\n";

    for (const CartItem &item : items)
    {
      item.displayCartItem();
    }

    cout << "\nTotal Amount : Rs. "
         << calculateTotal();

    cout << "\n====================================\n";
  }

  bool isEmpty() const
  {
    return items.empty();
  }

  const vector<CartItem> &getItems() const
  {
    return items;
  }

  void clearCart()
  {
    items.clear();
  }
};

#endif