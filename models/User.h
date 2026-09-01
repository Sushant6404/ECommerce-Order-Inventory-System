#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User
{
protected:
  int userId;
  string name;
  string email;
  string password;

public:
  User()
      : userId(0),
        name(""),
        email(""),
        password("")
  {
  }

  User(
      int id,
      const string &userName,
      const string &userEmail,
      const string &userPassword)
      : userId(id),
        name(userName),
        email(userEmail),
        password(userPassword)
  {
  }

  int getUserId() const
  {
    return userId;
  }

  string getName() const
  {
    return name;
  }

  string getEmail() const
  {
    return email;
  }

  string getPassword() const
  {
    return password;
  }

  bool checkPassword(const string &enteredPassword) const
  {
    return password == enteredPassword;
  }

  virtual void displayRole() const = 0;

  virtual ~User() = default;
};

#endif