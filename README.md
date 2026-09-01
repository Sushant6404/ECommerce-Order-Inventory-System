# E-Commerce Order & Inventory Management System

A console-based E-Commerce Order and Inventory Management System developed using C++ and Object-Oriented Programming principles.

## Features

### Admin

- Admin login
- Add products
- View products
- Search products
- Update inventory
- View customer orders
- Update order status

### Customer

- Customer registration
- Customer login
- Browse products
- Search products
- Add products to cart
- Remove cart items
- Update cart quantity
- Checkout
- UPI payment
- Card payment
- Cash on Delivery
- View order history
- View profile

## Inventory Management

The system validates available stock before checkout.

After an order is successfully placed, inventory is automatically reduced.

Example:

```text
Initial Laptop Stock = 10
Customer Purchase = 2
Remaining Stock = 8
```

## Payment System

The application supports:

- UPI
- Card
- Cash on Delivery

Payment is implemented using abstraction and runtime polymorphism.

```text
                Payment
               /   |   \
              /    |    \
           UPI    Card   COD
```

## OOP Concepts Used

- Classes and Objects
- Encapsulation
- Abstraction
- Inheritance
- Polymorphism
- Function Overriding
- Pure Virtual Functions
- Composition
- Constructors
- Virtual Destructor

## C++ Concepts Used

- STL vector
- Smart pointers
- unique_ptr
- References
- Pointers
- enum class
- File handling
- Exception-safe parsing
- Input validation

## Project Architecture

```text
User
├── Admin
└── Customer
      └── Cart
           └── CartItem
                └── Product

Customer
   ↓
Checkout
   ↓
Payment
├── UPIPayment
├── CardPayment
└── CashOnDelivery

Checkout
   ↓
OrderManager
├── InventoryManager
└── Order
     └── OrderItem
```

## File Persistence

The application stores data in:

```text
data/products.txt
data/customers.txt
data/orders.txt
```

Therefore data can be restored after restarting the application.

## Default Admin Login

```text
Email: admin@shop.com
Password: admin123
```

## Compilation

Compile using:

```bash
g++ -std=c++17 main.cpp -o ecommerce.exe
```

Run on Windows PowerShell:

```powershell
.\ecommerce.exe
```

## Example Product

```text
Product ID: 101
Name: Laptop
Category: Electronics
Price: 55000
Stock: 10
```

## Technologies

- C++
- C++17
- STL
- File Handling
- Git
- GitHub

## Testing

Test scenarios are documented inside:

```text
tests/test_cases.txt
```

The tests cover:

- Authentication validation
- Product validation
- Duplicate records
- Inventory validation
- Cart validation
- Payment validation
- Checkout
- Stock deduction
- Order management
- File persistence

## Future Improvements

- MySQL database integration
- Password hashing
- Automated unit testing
- Product deletion
- Product categories and filters
- Order cancellation with stock restoration
- Discounts and coupons
- Sales analytics
- GUI or web frontend
