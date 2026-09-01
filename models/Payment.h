#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// ============================================================
// ABSTRACT PAYMENT CLASS
// ============================================================

class Payment
{
protected:
  double amount;

public:
  Payment(double paymentAmount)
      : amount(paymentAmount)
  {
  }

  virtual bool processPayment() = 0;

  virtual string getPaymentMethod() const = 0;

  virtual ~Payment() = default;
};

// ============================================================
// UPI PAYMENT
// ============================================================

class UPIPayment : public Payment
{
private:
  string upiId;

public:
  UPIPayment(
      double paymentAmount,
      const string &upi)
      : Payment(paymentAmount),
        upiId(upi)
  {
  }

  bool processPayment() override
  {
    if (upiId.empty() ||
        upiId.find('@') == string::npos)
    {
      cout << "\nInvalid UPI ID.\n";
      return false;
    }

    cout << "\nUPI payment of Rs. "
         << amount
         << " processed successfully.\n";

    return true;
  }

  string getPaymentMethod() const override
  {
    return "UPI";
  }
};

// ============================================================
// CARD PAYMENT
// ============================================================

class CardPayment : public Payment
{
private:
  string cardNumber;
  string cvv;

public:
  CardPayment(
      double paymentAmount,
      const string &card,
      const string &cardCvv)
      : Payment(paymentAmount),
        cardNumber(card),
        cvv(cardCvv)
  {
  }

  bool processPayment() override
  {
    if (cardNumber.length() != 16)
    {
      cout << "\nCard number must contain 16 digits.\n";
      return false;
    }

    for (char character : cardNumber)
    {
      if (!isdigit(
              static_cast<unsigned char>(character)))
      {
        cout << "\nInvalid card number.\n";
        return false;
      }
    }

    if (cvv.length() != 3)
    {
      cout << "\nCVV must contain 3 digits.\n";
      return false;
    }

    for (char character : cvv)
    {
      if (!isdigit(
              static_cast<unsigned char>(character)))
      {
        cout << "\nInvalid CVV.\n";
        return false;
      }
    }

    cout << "\nCard payment of Rs. "
         << amount
         << " processed successfully.\n";

    return true;
  }

  string getPaymentMethod() const override
  {
    return "Card";
  }
};

// ============================================================
// CASH ON DELIVERY
// ============================================================

class CashOnDelivery : public Payment
{
public:
  CashOnDelivery(double paymentAmount)
      : Payment(paymentAmount)
  {
  }

  bool processPayment() override
  {
    cout << "\nCash on Delivery selected.\n";

    cout << "Amount payable on delivery: Rs. "
         << amount
         << "\n";

    return true;
  }

  string getPaymentMethod() const override
  {
    return "Cash on Delivery";
  }
};

#endif