#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ============================================================
// ORDER STATUS
// ============================================================

enum class OrderStatus
{
  Pending,
  Confirmed,
  Processing,
  Shipped,
  Delivered,
  Cancelled
};

// ============================================================
// ORDER ITEM
// ============================================================

class OrderItem
{
private:
  int productId;
  string productName;
  double price;
  int quantity;

public:
  OrderItem()
      : productId(0),
        productName(""),
        price(0.0),
        quantity(0)
  {
  }

  OrderItem(
      int id,
      const string &name,
      double productPrice,
      int qty)
      : productId(id),
        productName(name),
        price(productPrice),
        quantity(qty)
  {
  }

  int getProductId() const
  {
    return productId;
  }

  string getProductName() const
  {
    return productName;
  }

  double getPrice() const
  {
    return price;
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
    cout << "\nSubtotal   : Rs. "
         << getSubtotal();

    cout << "\n------------------------------------\n";
  }
};

// ============================================================
// ORDER
// ============================================================

class Order
{
private:
  int orderId;
  int customerId;

  vector<OrderItem> items;

  double totalAmount;

  OrderStatus status;

  string paymentMethod;

public:
  Order()
      : orderId(0),
        customerId(0),
        totalAmount(0.0),
        status(OrderStatus::Pending),
        paymentMethod("")
  {
  }

  Order(
      int id,
      int customer,
      const vector<OrderItem> &orderItems,
      double total,
      const string &payment,
      OrderStatus orderStatus = OrderStatus::Confirmed)
      : orderId(id),
        customerId(customer),
        items(orderItems),
        totalAmount(total),
        status(orderStatus),
        paymentMethod(payment)
  {
  }

  int getOrderId() const
  {
    return orderId;
  }

  int getCustomerId() const
  {
    return customerId;
  }

  const vector<OrderItem> &getItems() const
  {
    return items;
  }

  double getTotalAmount() const
  {
    return totalAmount;
  }

  OrderStatus getStatus() const
  {
    return status;
  }

  string getPaymentMethod() const
  {
    return paymentMethod;
  }

  void setStatus(OrderStatus newStatus)
  {
    status = newStatus;
  }

  string getStatusString() const
  {
    switch (status)
    {
    case OrderStatus::Pending:
      return "Pending";

    case OrderStatus::Confirmed:
      return "Confirmed";

    case OrderStatus::Processing:
      return "Processing";

    case OrderStatus::Shipped:
      return "Shipped";

    case OrderStatus::Delivered:
      return "Delivered";

    case OrderStatus::Cancelled:
      return "Cancelled";
    }

    return "Unknown";
  }

  void displayOrder() const
  {
    cout << "\n====================================";
    cout << "\n              ORDER";
    cout << "\n====================================";

    cout << "\nOrder ID       : " << orderId;
    cout << "\nCustomer ID    : " << customerId;
    cout << "\nPayment Method : " << paymentMethod;
    cout << "\nStatus         : "
         << getStatusString();

    cout << "\n====================================\n";

    for (const OrderItem &item : items)
    {
      item.displayOrderItem();
    }

    cout << "\nTotal Amount : Rs. "
         << totalAmount;

    cout << "\n====================================\n";
  }
};

#endif