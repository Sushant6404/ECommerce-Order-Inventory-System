#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <iostream>
#include <vector>

#include "../models/Product.h"

using namespace std;

class InventoryManager
{
private:
  vector<Product> products;

public:
  bool addProduct(
      const Product &product,
      bool showMessage = true)
  {
    if (product.getProductId() <= 0)
    {
      if (showMessage)
      {
        cout << "\nInvalid Product ID.\n";
      }

      return false;
    }

    if (product.getPrice() < 0)
    {
      if (showMessage)
      {
        cout << "\nInvalid product price.\n";
      }

      return false;
    }

    if (product.getStock() < 0)
    {
      if (showMessage)
      {
        cout << "\nInvalid stock value.\n";
      }

      return false;
    }

    for (const Product &existingProduct : products)
    {
      if (existingProduct.getProductId() ==
          product.getProductId())
      {
        if (showMessage)
        {
          cout << "\nProduct ID already exists.\n";
        }

        return false;
      }
    }

    products.push_back(product);

    if (showMessage)
    {
      cout << "\nProduct added successfully.\n";
    }

    return true;
  }

  Product *searchProduct(int productId)
  {
    for (Product &product : products)
    {
      if (product.getProductId() ==
          productId)
      {
        return &product;
      }
    }

    return nullptr;
  }

  const Product *searchProduct(int productId) const
  {
    for (const Product &product : products)
    {
      if (product.getProductId() ==
          productId)
      {
        return &product;
      }
    }

    return nullptr;
  }

  void displayAllProducts() const
  {
    if (products.empty())
    {
      cout << "\nNo products available.\n";
      return;
    }

    cout << "\n====================================";
    cout << "\n           PRODUCT LIST";
    cout << "\n====================================\n";

    for (const Product &product : products)
    {
      product.displayProduct();
    }
  }

  bool updateStock(
      int productId,
      int quantity)
  {
    Product *product =
        searchProduct(productId);

    if (product == nullptr)
    {
      cout << "\nProduct not found.\n";
      return false;
    }

    if (quantity < 0)
    {
      cout << "\nInvalid stock quantity.\n";
      return false;
    }

    product->setStock(quantity);

    cout << "\nStock updated successfully.\n";

    return true;
  }

  bool reduceStock(
      int productId,
      int quantity)
  {
    Product *product =
        searchProduct(productId);

    if (product == nullptr)
    {
      return false;
    }

    if (quantity <= 0)
    {
      return false;
    }

    if (product->getStock() < quantity)
    {
      return false;
    }

    product->setStock(
        product->getStock() - quantity);

    return true;
  }

  const vector<Product> &getProducts() const
  {
    return products;
  }

  void clearProducts()
  {
    products.clear();
  }
};

#endif