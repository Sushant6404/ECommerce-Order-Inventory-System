#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

class Product
{
private:
  int productId;
  string name;
  string category;
  double price;
  int stock;

public:
  Product()
      : productId(0),
        name(""),
        category(""),
        price(0.0),
        stock(0)
  {
  }

  Product(
      int id,
      const string &productName,
      const string &productCategory,
      double productPrice,
      int productStock)
      : productId(id),
        name(productName),
        category(productCategory),
        price(productPrice),
        stock(productStock)
  {
  }

  int getProductId() const
  {
    return productId;
  }

  string getName() const
  {
    return name;
  }

  string getCategory() const
  {
    return category;
  }

  double getPrice() const
  {
    return price;
  }

  int getStock() const
  {
    return stock;
  }

  void setPrice(double newPrice)
  {
    if (newPrice >= 0)
    {
      price = newPrice;
    }
  }

  void setStock(int newStock)
  {
    if (newStock >= 0)
    {
      stock = newStock;
    }
  }

  void displayProduct() const
  {
    cout << "\nProduct ID : " << productId;
    cout << "\nName       : " << name;
    cout << "\nCategory   : " << category;
    cout << "\nPrice      : Rs. " << price;
    cout << "\nStock      : " << stock;
    cout << "\n------------------------------------\n";
  }
};

#endif