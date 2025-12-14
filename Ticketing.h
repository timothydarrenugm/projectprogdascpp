/**
 * Project Ticketing Machine Apliccation
 */

#ifndef _Ticketing_H
#define _Ticketing_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Class: Ticket
class Ticket {
private:
    int price;
    std::string destination;
    std::string origin;

public:
    Ticket();
    Ticket(const std::string& destination, const std::string& origin, int price);

    std::string getDestination() const;
    std::string getOrigin() const;
    int getPrice() const;

    void setTicket(const std::string& origin, const std::string& destination, int price);
    void resetPrice(int newPrice);
};

// Base Class: Person
class Person {
protected: 

    std::string username;
    int password;
    std::string name;
    int birth;
    std::string address;
    std::string city;
    std::string province;
    std::string street;
    int postalcode;

public:
    Person();
    Person(const std::string& username, int password);
    virtual ~Person() {} 

    bool login(const std::string& user, int pass) const;
    void resetPassword(int newpass);
    
    virtual void displayProfile() const;

    // Getters and Setters Basic Info
    void setBasicInfo(const std::string& name, int birth,
                      const std::string& address, 
                      const std::string& city,
                      const std::string& province, 
                      const std::string& street, 
                      int postalcode);
    
    std::string getUsername() const;
    int getPassword() const;
    std::string getName() const;
    int getBirth() const;
    std::string getAddress() const;
    std::string getCity() const;
    std::string getProvince() const;
    std::string getStreet() const;
    int getPostalCode() const;
};

// Derived Class Customer
class Customer : public Person {
private:
    int balance;
    std::vector<std::string> history;

public:
    Customer();
    Customer(const std::string& username, int password);

    void setBalance(int amount);
    void addBalance(int amount);
    int getBalance() const;
    
    bool buyTicket(const Ticket& t);
    
    // History Management
    void addHistory(const Ticket& t);
    void viewHistory() const;
    std::string getHistoryString() const; 
    void loadHistoryFromString(const std::string& s);

    // Override the base displayProfile
    void displayProfile() const override;
};

// Derived Class Admin
class Admin : public Person {
public:
    Admin(const std::string& username, int password);

    void createNewTicket(std::vector<Ticket>& tickets);
    void viewAllUsers(const std::vector<Customer>& customers) const;
    
};

// utility functions

// login function
void logins();

//Load and Save Data
void saveUsers(const std::vector<Customer>& customers);
void loadUsers(std::vector<Customer>& customers);

void saveTickets(const std::vector<Ticket>& tickets);
void loadTickets(std::vector<Ticket>& tickets);

std::string encode(const std::string& s);
std::string decode(const std::string& s);
int getIntInput(const std::string& prompt);

//Ascii basic clearline
void clearLine();
// Halt program
void WaitEnter();

#endif // _Ticketing_H