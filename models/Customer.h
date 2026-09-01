#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Cart.h"

class Customer : public User
{
private:
  string address;
  Cart cart;

public:
  Customer()
      : User(),
        address("")
  {
  }

  Customer(
      int id,
      const string &customerName,
      const string &customerEmail,
      const string &customerPassword,
      const string &customerAddress)
      : User(
            id,
            customerName,
            customerEmail,
            customerPassword),
        address(customerAddress)
  {
  }

  string getAddress() const
  {
    return address;
  }

  void setAddress(const string &newAddress)
  {
    address = newAddress;
  }

  Cart &getCart()
  {
    return cart;
  }

  void displayRole() const override
  {
    cout << "Customer";
  }

  void displayCustomer() const
  {
    cout << "\n====================================";
    cout << "\n          CUSTOMER PROFILE";
    cout << "\n====================================";

    cout << "\nCustomer ID : " << userId;
    cout << "\nName        : " << name;
    cout << "\nEmail       : " << email;
    cout << "\nAddress     : " << address;
    cout << "\nRole        : ";

    displayRole();

    cout << "\n====================================\n";
  }
};

#endif