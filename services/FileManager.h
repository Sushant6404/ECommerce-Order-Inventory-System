#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../models/Customer.h"
#include "InventoryManager.h"
#include "OrderManager.h"

using namespace std;

class FileManager
{
private:
  string productFile;
  string customerFile;
  string orderFile;

  vector<string> split(
      const string &text,
      char delimiter) const
  {
    vector<string> parts;

    stringstream ss(text);

    string part;

    while (getline(ss, part, delimiter))
    {
      parts.push_back(part);
    }

    return parts;
  }

public:
  FileManager(
      const string &products = "data/products.txt",
      const string &customers = "data/customers.txt",
      const string &orders = "data/orders.txt")
      : productFile(products),
        customerFile(customers),
        orderFile(orders)
  {
  }

  // ========================================================
  // PRODUCTS
  // ========================================================

  void saveProducts(
      const InventoryManager &inventory) const
  {
    ofstream file(productFile);

    if (!file)
    {
      cout << "\nUnable to save products file.\n";
      return;
    }

    for (const Product &product :
         inventory.getProducts())
    {
      file
          << product.getProductId() << "|"
          << product.getName() << "|"
          << product.getCategory() << "|"
          << product.getPrice() << "|"
          << product.getStock()
          << "\n";
    }
  }

  void loadProducts(
      InventoryManager &inventory) const
  {
    ifstream file(productFile);

    if (!file)
    {
      return;
    }

    inventory.clearProducts();

    string line;

    while (getline(file, line))
    {
      if (line.empty())
      {
        continue;
      }

      vector<string> values =
          split(line, '|');

      if (values.size() != 5)
      {
        continue;
      }

      try
      {
        int id =
            stoi(values[0]);

        string name =
            values[1];

        string category =
            values[2];

        double price =
            stod(values[3]);

        int stock =
            stoi(values[4]);

        inventory.addProduct(
            Product(
                id,
                name,
                category,
                price,
                stock),
            false);
      }
      catch (...)
      {
        // Ignore malformed records.
      }
    }
  }

  // ========================================================
  // CUSTOMERS
  // ========================================================

  void saveCustomers(
      const vector<Customer> &customers) const
  {
    ofstream file(customerFile);

    if (!file)
    {
      cout << "\nUnable to save customers file.\n";
      return;
    }

    for (const Customer &customer : customers)
    {
      file
          << customer.getUserId() << "|"
          << customer.getName() << "|"
          << customer.getEmail() << "|"
          << customer.getPassword() << "|"
          << customer.getAddress()
          << "\n";
    }
  }

  void loadCustomers(
      vector<Customer> &customers) const
  {
    ifstream file(customerFile);

    if (!file)
    {
      return;
    }

    customers.clear();

    string line;

    while (getline(file, line))
    {
      if (line.empty())
      {
        continue;
      }

      vector<string> values =
          split(line, '|');

      if (values.size() != 5)
      {
        continue;
      }

      try
      {
        int id =
            stoi(values[0]);

        customers.push_back(
            Customer(
                id,
                values[1],
                values[2],
                values[3],
                values[4]));
      }
      catch (...)
      {
        // Ignore malformed records.
      }
    }
  }

  // ========================================================
  // ORDERS
  // ========================================================

  void saveOrders(
      const OrderManager &orderManager) const
  {
    ofstream file(orderFile);

    if (!file)
    {
      cout << "\nUnable to save orders file.\n";
      return;
    }

    for (const Order &order :
         orderManager.getOrders())
    {
      file
          << order.getOrderId() << "|"
          << order.getCustomerId() << "|"
          << order.getTotalAmount() << "|"
          << static_cast<int>(
                 order.getStatus())
          << "|"
          << order.getPaymentMethod()
          << "|";

      const vector<OrderItem> &items =
          order.getItems();

      for (size_t i = 0;
           i < items.size();
           i++)
      {
        const OrderItem &item =
            items[i];

        file
            << item.getProductId()
            << ","
            << item.getProductName()
            << ","
            << item.getPrice()
            << ","
            << item.getQuantity();

        if (i + 1 < items.size())
        {
          file << ";";
        }
      }

      file << "\n";
    }
  }

  void loadOrders(
      OrderManager &orderManager) const
  {
    ifstream file(orderFile);

    if (!file)
    {
      return;
    }

    orderManager.clearOrders();

    string line;

    while (getline(file, line))
    {
      if (line.empty())
      {
        continue;
      }

      vector<string> values =
          split(line, '|');

      if (values.size() != 6)
      {
        continue;
      }

      try
      {
        int orderId =
            stoi(values[0]);

        int customerId =
            stoi(values[1]);

        double total =
            stod(values[2]);

        int statusValue =
            stoi(values[3]);

        string paymentMethod =
            values[4];

        vector<OrderItem> items;

        vector<string> itemRecords =
            split(values[5], ';');

        for (const string &record :
             itemRecords)
        {
          if (record.empty())
          {
            continue;
          }

          vector<string> itemValues =
              split(record, ',');

          if (itemValues.size() != 4)
          {
            continue;
          }

          int productId =
              stoi(itemValues[0]);

          string productName =
              itemValues[1];

          double price =
              stod(itemValues[2]);

          int quantity =
              stoi(itemValues[3]);

          items.push_back(
              OrderItem(
                  productId,
                  productName,
                  price,
                  quantity));
        }

        OrderStatus status =
            OrderStatus::Confirmed;

        if (statusValue >= 0 &&
            statusValue <= 5)
        {
          status =
              static_cast<OrderStatus>(
                  statusValue);
        }

        Order order(
            orderId,
            customerId,
            items,
            total,
            paymentMethod,
            status);

        orderManager.addLoadedOrder(order);
      }
      catch (...)
      {
        // Ignore malformed records.
      }
    }
  }

  // ========================================================
  // SAVE EVERYTHING
  // ========================================================

  void saveAll(
      const InventoryManager &inventory,
      const vector<Customer> &customers,
      const OrderManager &orderManager) const
  {
    saveProducts(inventory);
    saveCustomers(customers);
    saveOrders(orderManager);
  }

  void loadAll(
      InventoryManager &inventory,
      vector<Customer> &customers,
      OrderManager &orderManager) const
  {
    loadProducts(inventory);
    loadCustomers(customers);
    loadOrders(orderManager);
  }
};

#endif