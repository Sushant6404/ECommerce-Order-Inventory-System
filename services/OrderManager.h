#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <iostream>
#include <vector>

#include "../models/Order.h"
#include "../models/Cart.h"
#include "../models/Payment.h"

#include "InventoryManager.h"

using namespace std;

class OrderManager
{
private:
  vector<Order> orders;
  int nextOrderId;

public:
  OrderManager()
      : nextOrderId(1001)
  {
  }

  bool checkout(
      int customerId,
      Cart &cart,
      InventoryManager &inventory,
      Payment &payment)
  {
    if (cart.isEmpty())
    {
      cout << "\nCannot checkout. Cart is empty.\n";
      return false;
    }

    const vector<CartItem> &cartItems =
        cart.getItems();

    // ====================================================
    // STEP 1: VALIDATE INVENTORY
    // ====================================================

    for (const CartItem &cartItem : cartItems)
    {
      int productId =
          cartItem.getProduct().getProductId();

      int quantity =
          cartItem.getQuantity();

      Product *product =
          inventory.searchProduct(productId);

      if (product == nullptr)
      {
        cout << "\nProduct no longer exists.\n";
        return false;
      }

      if (product->getStock() < quantity)
      {
        cout << "\nInsufficient stock for "
             << product->getName()
             << ".\n";

        return false;
      }
    }

    // ====================================================
    // STEP 2: PROCESS PAYMENT
    // ====================================================

    if (!payment.processPayment())
    {
      cout << "\nPayment failed. Order was not created.\n";
      return false;
    }

    // ====================================================
    // STEP 3: CREATE ORDER ITEMS
    // ====================================================

    vector<OrderItem> orderItems;

    double totalAmount = 0.0;

    for (const CartItem &cartItem : cartItems)
    {
      int productId =
          cartItem.getProduct().getProductId();

      Product *currentProduct =
          inventory.searchProduct(productId);

      if (currentProduct == nullptr)
      {
        cout << "\nUnexpected product error.\n";
        return false;
      }

      int quantity =
          cartItem.getQuantity();

      OrderItem item(
          currentProduct->getProductId(),
          currentProduct->getName(),
          currentProduct->getPrice(),
          quantity);

      orderItems.push_back(item);

      totalAmount +=
          item.getSubtotal();
    }

    // ====================================================
    // STEP 4: REDUCE INVENTORY
    // ====================================================

    for (const CartItem &cartItem : cartItems)
    {
      inventory.reduceStock(
          cartItem.getProduct().getProductId(),
          cartItem.getQuantity());
    }

    // ====================================================
    // STEP 5: CREATE ORDER
    // ====================================================

    Order order(
        nextOrderId,
        customerId,
        orderItems,
        totalAmount,
        payment.getPaymentMethod(),
        OrderStatus::Confirmed);

    orders.push_back(order);

    cout << "\n====================================";
    cout << "\n     ORDER PLACED SUCCESSFULLY";
    cout << "\n====================================";

    cout << "\nOrder ID       : "
         << nextOrderId;

    cout << "\nTotal Amount   : Rs. "
         << totalAmount;

    cout << "\nPayment Method : "
         << payment.getPaymentMethod();

    cout << "\nStatus         : Confirmed";

    cout << "\n====================================\n";

    nextOrderId++;

    cart.clearCart();

    return true;
  }

  void displayCustomerOrders(
      int customerId) const
  {
    bool found = false;

    cout << "\n====================================";
    cout << "\n             MY ORDERS";
    cout << "\n====================================\n";

    for (const Order &order : orders)
    {
      if (order.getCustomerId() ==
          customerId)
      {
        order.displayOrder();

        found = true;
      }
    }

    if (!found)
    {
      cout << "\nNo orders found.\n";
    }
  }

  void displayAllOrders() const
  {
    if (orders.empty())
    {
      cout << "\nNo orders available.\n";
      return;
    }

    cout << "\n====================================";
    cout << "\n            ALL ORDERS";
    cout << "\n====================================\n";

    for (const Order &order : orders)
    {
      order.displayOrder();
    }
  }

  bool updateOrderStatus(
      int orderId,
      OrderStatus newStatus)
  {
    for (Order &order : orders)
    {
      if (order.getOrderId() ==
          orderId)
      {
        order.setStatus(newStatus);

        cout << "\nOrder status updated successfully.\n";

        return true;
      }
    }

    cout << "\nOrder not found.\n";

    return false;
  }

  const vector<Order> &getOrders() const
  {
    return orders;
  }

  void addLoadedOrder(
      const Order &order)
  {
    orders.push_back(order);

    if (order.getOrderId() >=
        nextOrderId)
    {
      nextOrderId =
          order.getOrderId() + 1;
    }
  }

  void clearOrders()
  {
    orders.clear();

    nextOrderId = 1001;
  }
};

#endif