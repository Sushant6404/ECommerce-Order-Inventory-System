#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User
{
public:
  Admin()
      : User()
  {
  }

  Admin(
      int id,
      const string &adminName,
      const string &adminEmail,
      const string &adminPassword)
      : User(
            id,
            adminName,
            adminEmail,
            adminPassword)
  {
  }

  void displayRole() const override
  {
    cout << "Admin";
  }

  void displayAdmin() const
  {
    cout << "\n====================================";
    cout << "\n            ADMIN PROFILE";
    cout << "\n====================================";

    cout << "\nAdmin ID : " << userId;
    cout << "\nName     : " << name;
    cout << "\nEmail    : " << email;
    cout << "\nRole     : ";

    displayRole();

    cout << "\n====================================\n";
  }
};

#endif