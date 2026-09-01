#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "models/Product.h"
#include "models/User.h"
#include "models/Customer.h"
#include "models/Admin.h"
#include "models/Cart.h"
#include "models/Order.h"
#include "models/Payment.h"

#include "services/InventoryManager.h"
#include "services/OrderManager.h"
#include "services/FileManager.h"

using namespace std;

// ============================================================
// INPUT UTILITY
// ============================================================

void clearInput()
{
  cin.clear();

  cin.ignore(
      numeric_limits<streamsize>::max(),
      '\n');
}

// ============================================================
// ADMIN MENU
// ============================================================

void adminMenu(
    InventoryManager &inventory,
    OrderManager &orderManager,
    FileManager &fileManager,
    vector<Customer> &customers)
{
  int choice = 0;

  do
  {
    cout << "\n====================================";
    cout << "\n            ADMIN PANEL";
    cout << "\n====================================";

    cout << "\n1. Add Product";
    cout << "\n2. View Products";
    cout << "\n3. Search Product";
    cout << "\n4. Update Stock";
    cout << "\n5. View All Orders";
    cout << "\n6. Update Order Status";
    cout << "\n7. Logout";

    cout << "\n====================================";
    cout << "\nEnter your choice: ";

    if (!(cin >> choice))
    {
      clearInput();

      cout << "\nInvalid input.\n";
      continue;
    }

    switch (choice)
    {
    case 1:
    {
      int id;
      string name;
      string category;
      double price;
      int stock;

      cout << "\nEnter Product ID: ";

      if (!(cin >> id))
      {
        clearInput();

        cout << "\nInvalid Product ID.\n";
        break;
      }

      clearInput();

      cout << "Enter Product Name: ";
      getline(cin, name);

      cout << "Enter Category: ";
      getline(cin, category);

      cout << "Enter Price: ";

      if (!(cin >> price))
      {
        clearInput();

        cout << "\nInvalid price.\n";
        break;
      }

      cout << "Enter Stock: ";

      if (!(cin >> stock))
      {
        clearInput();

        cout << "\nInvalid stock.\n";
        break;
      }

      if (name.empty() ||
          category.empty() ||
          price < 0 ||
          stock < 0)
      {
        cout << "\nInvalid product information.\n";
        break;
      }

      Product product(
          id,
          name,
          category,
          price,
          stock);

      if (inventory.addProduct(product))
      {
        fileManager.saveProducts(inventory);
      }

      break;
    }

    case 2:
    {
      inventory.displayAllProducts();

      break;
    }

    case 3:
    {
      int productId;

      cout << "\nEnter Product ID: ";

      if (!(cin >> productId))
      {
        clearInput();

        cout << "\nInvalid Product ID.\n";
        break;
      }

      Product *product =
          inventory.searchProduct(productId);

      if (product != nullptr)
      {
        product->displayProduct();
      }
      else
      {
        cout << "\nProduct not found.\n";
      }

      break;
    }

    case 4:
    {
      int productId;
      int stock;

      cout << "\nEnter Product ID: ";

      if (!(cin >> productId))
      {
        clearInput();

        cout << "\nInvalid Product ID.\n";
        break;
      }

      cout << "Enter New Stock: ";

      if (!(cin >> stock))
      {
        clearInput();

        cout << "\nInvalid stock.\n";
        break;
      }

      if (inventory.updateStock(
              productId,
              stock))
      {
        fileManager.saveProducts(inventory);
      }

      break;
    }

    case 5:
    {
      orderManager.displayAllOrders();

      break;
    }

    case 6:
    {
      int orderId;
      int statusChoice;

      cout << "\nEnter Order ID: ";

      if (!(cin >> orderId))
      {
        clearInput();

        cout << "\nInvalid Order ID.\n";
        break;
      }

      cout << "\n1. Confirmed";
      cout << "\n2. Processing";
      cout << "\n3. Shipped";
      cout << "\n4. Delivered";
      cout << "\n5. Cancelled";

      cout << "\n\nEnter Status: ";

      if (!(cin >> statusChoice))
      {
        clearInput();

        cout << "\nInvalid status.\n";
        break;
      }

      bool updated = false;

      switch (statusChoice)
      {
      case 1:
        updated =
            orderManager.updateOrderStatus(
                orderId,
                OrderStatus::Confirmed);
        break;

      case 2:
        updated =
            orderManager.updateOrderStatus(
                orderId,
                OrderStatus::Processing);
        break;

      case 3:
        updated =
            orderManager.updateOrderStatus(
                orderId,
                OrderStatus::Shipped);
        break;

      case 4:
        updated =
            orderManager.updateOrderStatus(
                orderId,
                OrderStatus::Delivered);
        break;

      case 5:
        updated =
            orderManager.updateOrderStatus(
                orderId,
                OrderStatus::Cancelled);
        break;

      default:
        cout << "\nInvalid status choice.\n";
      }

      if (updated)
      {
        fileManager.saveOrders(orderManager);
      }

      break;
    }

    case 7:
    {
      cout << "\nAdmin logged out successfully.\n";

      break;
    }

    default:
    {
      cout << "\nInvalid choice. Please try again.\n";
    }
    }

  } while (choice != 7);
}

// ============================================================
// CHECKOUT
// ============================================================

void checkoutCustomer(
    Customer &customer,
    InventoryManager &inventory,
    OrderManager &orderManager,
    FileManager &fileManager,
    vector<Customer> &customers)
{
  Cart &cart =
      customer.getCart();

  if (cart.isEmpty())
  {
    cout << "\nCannot checkout. Cart is empty.\n";
    return;
  }

  cart.displayCart();

  double amount =
      cart.calculateTotal();

  int paymentChoice;

  cout << "\n====================================";
  cout << "\n          PAYMENT METHOD";
  cout << "\n====================================";

  cout << "\n1. UPI";
  cout << "\n2. Card";
  cout << "\n3. Cash on Delivery";
  cout << "\n4. Cancel Checkout";

  cout << "\n====================================";
  cout << "\nSelect Payment Method: ";

  if (!(cin >> paymentChoice))
  {
    clearInput();

    cout << "\nInvalid payment choice.\n";
    return;
  }

  unique_ptr<Payment> payment;

  switch (paymentChoice)
  {
  case 1:
  {
    string upiId;

    cout << "\nEnter UPI ID: ";
    cin >> upiId;

    payment =
        make_unique<UPIPayment>(
            amount,
            upiId);

    break;
  }

  case 2:
  {
    string cardNumber;
    string cvv;

    cout << "\nEnter 16-digit Card Number: ";
    cin >> cardNumber;

    cout << "Enter 3-digit CVV: ";
    cin >> cvv;

    payment =
        make_unique<CardPayment>(
            amount,
            cardNumber,
            cvv);

    break;
  }

  case 3:
  {
    payment =
        make_unique<CashOnDelivery>(
            amount);

    break;
  }

  case 4:
  {
    cout << "\nCheckout cancelled.\n";
    return;
  }

  default:
  {
    cout << "\nInvalid payment method.\n";
    return;
  }
  }

  bool success =
      orderManager.checkout(
          customer.getUserId(),
          cart,
          inventory,
          *payment);

  if (success)
  {
    fileManager.saveAll(
        inventory,
        customers,
        orderManager);
  }
}

// ============================================================
// CUSTOMER MENU
// ============================================================

void customerMenu(
    Customer &customer,
    InventoryManager &inventory,
    OrderManager &orderManager,
    FileManager &fileManager,
    vector<Customer> &customers)
{
  int choice = 0;

  do
  {
    cout << "\n====================================";
    cout << "\n          CUSTOMER PANEL";
    cout << "\n====================================";

    cout << "\nWelcome, "
         << customer.getName();

    cout << "\n\n1. View Products";
    cout << "\n2. Search Product";
    cout << "\n3. Add Product to Cart";
    cout << "\n4. View Cart";
    cout << "\n5. Remove Product from Cart";
    cout << "\n6. Update Cart Quantity";
    cout << "\n7. Checkout";
    cout << "\n8. View My Orders";
    cout << "\n9. View Profile";
    cout << "\n10. Logout";

    cout << "\n====================================";
    cout << "\nEnter your choice: ";

    if (!(cin >> choice))
    {
      clearInput();

      cout << "\nInvalid input.\n";
      continue;
    }

    switch (choice)
    {
    case 1:
    {
      inventory.displayAllProducts();
      break;
    }

    case 2:
    {
      int productId;

      cout << "\nEnter Product ID: ";

      if (!(cin >> productId))
      {
        clearInput();

        cout << "\nInvalid Product ID.\n";
        break;
      }

      Product *product =
          inventory.searchProduct(productId);

      if (product != nullptr)
      {
        product->displayProduct();
      }
      else
      {
        cout << "\nProduct not found.\n";
      }

      break;
    }

    case 3:
    {
      int productId;
      int quantity;

      cout << "\nEnter Product ID: ";

      if (!(cin >> productId))
      {
        clearInput();

        cout << "\nInvalid Product ID.\n";
        break;
      }

      Product *product =
          inventory.searchProduct(productId);

      if (product == nullptr)
      {
        cout << "\nProduct not found.\n";
        break;
      }

      cout << "Enter Quantity: ";

      if (!(cin >> quantity))
      {
        clearInput();

        cout << "\nInvalid quantity.\n";
        break;
      }

      customer
          .getCart()
          .addProduct(
              *product,
              quantity);

      break;
    }

    case 4:
    {
      customer
          .getCart()
          .displayCart();

      break;
    }

    case 5:
    {
      int productId;

      cout << "\nEnter Product ID to remove: ";

      if (!(cin >> productId))
      {
        clearInput();

        cout << "\nInvalid Product ID.\n";
        break;
      }

      customer
          .getCart()
          .removeProduct(productId);

      break;
    }

    case 6:
    {
      int productId;
      int quantity;

      cout << "\nEnter Product ID: ";

      if (!(cin >> productId))
      {
        clearInput();

        cout << "\nInvalid Product ID.\n";
        break;
      }

      cout << "Enter New Quantity: ";

      if (!(cin >> quantity))
      {
        clearInput();

        cout << "\nInvalid quantity.\n";
        break;
      }

      customer
          .getCart()
          .updateQuantity(
              productId,
              quantity);

      break;
    }

    case 7:
    {
      checkoutCustomer(
          customer,
          inventory,
          orderManager,
          fileManager,
          customers);

      break;
    }

    case 8:
    {
      orderManager.displayCustomerOrders(
          customer.getUserId());

      break;
    }

    case 9:
    {
      customer.displayCustomer();

      break;
    }

    case 10:
    {
      cout << "\nCustomer logged out successfully.\n";

      break;
    }

    default:
    {
      cout << "\nInvalid choice. Please try again.\n";
    }
    }

  } while (choice != 10);
}

// ============================================================
// MAIN
// ============================================================

int main()
{
  InventoryManager inventory;

  OrderManager orderManager;

  vector<Customer> customers;

  FileManager fileManager;

  // --------------------------------------------------------
  // LOAD PREVIOUS DATA
  // --------------------------------------------------------

  fileManager.loadAll(
      inventory,
      customers,
      orderManager);

  // --------------------------------------------------------
  // DEFAULT ADMIN
  // --------------------------------------------------------

  Admin admin(
      1,
      "System Admin",
      "admin@shop.com",
      "admin123");

  int mainChoice = 0;

  do
  {
    cout << "\n====================================";
    cout << "\n       E-COMMERCE SYSTEM";
    cout << "\n====================================";

    cout << "\n1. Admin Login";
    cout << "\n2. Customer Registration";
    cout << "\n3. Customer Login";
    cout << "\n4. Exit";

    cout << "\n====================================";
    cout << "\nEnter your choice: ";

    if (!(cin >> mainChoice))
    {
      clearInput();

      cout << "\nInvalid input.\n";
      continue;
    }

    switch (mainChoice)
    {
      // ----------------------------------------------------
      // ADMIN LOGIN
      // ----------------------------------------------------

    case 1:
    {
      string email;
      string password;

      cout << "\nEnter Admin Email: ";
      cin >> email;

      cout << "Enter Admin Password: ";
      cin >> password;

      if (
          admin.getEmail() == email &&
          admin.checkPassword(password))
      {
        cout << "\nAdmin login successful.\n";

        adminMenu(
            inventory,
            orderManager,
            fileManager,
            customers);
      }
      else
      {
        cout << "\nInvalid admin credentials.\n";
      }

      break;
    }

      // ----------------------------------------------------
      // CUSTOMER REGISTRATION
      // ----------------------------------------------------

    case 2:
    {
      int id;

      string name;
      string email;
      string password;
      string address;

      cout << "\nEnter Customer ID: ";

      if (!(cin >> id))
      {
        clearInput();

        cout << "\nInvalid Customer ID.\n";
        break;
      }

      clearInput();

      cout << "Enter Name: ";
      getline(cin, name);

      cout << "Enter Email: ";
      getline(cin, email);

      cout << "Enter Password: ";
      getline(cin, password);

      cout << "Enter Address: ";
      getline(cin, address);

      if (
          id <= 0 ||
          name.empty() ||
          email.empty() ||
          password.empty() ||
          address.empty())
      {
        cout << "\nInvalid registration details.\n";
        break;
      }

      bool duplicate = false;

      for (const Customer &customer :
           customers)
      {
        if (
            customer.getUserId() == id ||
            customer.getEmail() == email)
        {
          duplicate = true;
          break;
        }
      }

      if (duplicate)
      {
        cout << "\nCustomer ID or email already exists.\n";

        break;
      }

      Customer customer(
          id,
          name,
          email,
          password,
          address);

      customers.push_back(customer);

      fileManager.saveCustomers(customers);

      cout << "\nCustomer registered successfully.\n";

      break;
    }

      // ----------------------------------------------------
      // CUSTOMER LOGIN
      // ----------------------------------------------------

    case 3:
    {
      string email;
      string password;

      clearInput();

      cout << "\nEnter Email: ";
      getline(cin, email);

      cout << "Enter Password: ";
      getline(cin, password);

      bool found = false;

      for (Customer &customer :
           customers)
      {
        if (
            customer.getEmail() == email &&
            customer.checkPassword(password))
        {
          cout << "\nLogin successful.\n";

          customerMenu(
              customer,
              inventory,
              orderManager,
              fileManager,
              customers);

          found = true;

          break;
        }
      }

      if (!found)
      {
        cout << "\nInvalid email or password.\n";
      }

      break;
    }

      // ----------------------------------------------------
      // EXIT
      // ----------------------------------------------------

    case 4:
    {
      fileManager.saveAll(
          inventory,
          customers,
          orderManager);

      cout << "\n====================================";
      cout << "\nData saved successfully.";
      cout << "\nThank you for using the system.";
      cout << "\n====================================\n";

      break;
    }

    default:
    {
      cout << "\nInvalid choice. Please try again.\n";
    }
    }

  } while (mainChoice != 4);

  return 0;
}