/**
 * Project Ticketing Machine Apliccation
 */

#include "Ticketing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

// Ticket Implementation
Ticket::Ticket(const std::string& des, const std::string& ori, int pri) 
    : price(pri), destination(des), origin(ori) {}

Ticket::Ticket() : price(0), destination(""), origin("") {}

std::string Ticket::getDestination() const { return destination; }
std::string Ticket::getOrigin() const { return origin; }
int Ticket::getPrice() const { return price; }

void Ticket::setTicket(const std::string& ori, const std::string& des, int pri) {
    origin = ori;
    destination = des;
    price = pri;
}
void Ticket::resetPrice(int newPrice) { price = newPrice; }

// Person Implementation
Person::Person() : username(""), password(0), name(""), birth(0), address(""), city(""), province(""), street(""), postalcode(0) {}

Person::Person(const std::string& user, int pass) 
    : username(user), password(pass), name(""), birth(0), postalcode(0) {}

bool Person::login(const std::string& user, int pass) const {
    return (user == username && pass == password);
}

void Person::resetPassword(int newpass) { password = newpass; }

// Getters
std::string Person::getUsername() const { return username; }
int Person::getPassword() const { return password; }
std::string Person::getName() const { return name; }
int Person::getBirth() const { return birth; }
std::string Person::getAddress() const { return address; }
std::string Person::getCity() const { return city; }
std::string Person::getProvince() const { return province; }
std::string Person::getStreet() const { return street; }
int Person::getPostalCode() const { return postalcode; }

void Person::setBasicInfo(const std::string& n, int b, const std::string& a, const std::string& c,
                          const std::string& p, const std::string& s, int pc) {
    name = n; 
    birth = b; 
    address = a; 
    city = c; 
    province = p; 
    street = s; 
    postalcode = pc;
}

//Person
void Person::displayProfile() const {
    std::cout << "Username : " << username 
              << "\nName : " << name 
              << "\nBirth Year : " << birth 
              << "\nAddress : " << address
              << "\nStreet : " << street 
              << "\nCity : " << city 
              << "\nProvince : " << province 
              << "\nPostal Code : " << postalcode << "\n";
}

// Customer Implementation
Customer::Customer() : Person(), balance(0) {}
Customer::Customer(const std::string& user, int pass) : Person(user, pass), balance(0) {}

void Customer::setBalance(int amount) { balance = amount; }

//3. Top Up Balance
void Customer::addBalance(int amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Added $" << amount << ". New Balance: $" << balance;
    }
}

//2. Check Balance
int Customer::getBalance() const { return balance; }

bool Customer::buyTicket(const Ticket& t) {
    if (balance >= t.getPrice()) {
        balance -= t.getPrice();
        addHistory(t);
        std::cout << "Purchase successful!";
        WaitEnter();
        return true;
    } else {
        std::cout << "Insufficient funds.";
        WaitEnter();
        return false;
    }
}

void Customer::addHistory(const Ticket& t) {
    std::string entry = t.getOrigin() + "->" + t.getDestination() + "|$" + std::to_string(t.getPrice());
    history.push_back(entry);
}

void Customer::viewHistory() const {
    size_t i = 0;
    std::cout << "--- Purchase History ---\n" << "Origin->Destination|Price\n";
    if(history.empty()) std::cout << "(Empty)\n";
    for(const auto& h : history) {
        std::cout << h << "\n";
        i++;
    }
    WaitEnter();
    clearLine();
    clearLine();
    clearLine();
    for(size_t j = 0 ; j < i ; j++) clearLine();
}

std::string Customer::getHistoryString() const {
    std::string result;
    for (size_t i = 0; i < history.size(); i++) {
        result += history[i];
        if (i + 1 < history.size()) result += ";";
    }
    return result;
}

void Customer::loadHistoryFromString(const std::string& s) {
    history.clear();
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ';')) {
        if (!item.empty()) history.push_back(item);
    }
}

// Display for Customer
void Customer::displayProfile() const {
    Person::displayProfile(); // Call parent
    std::cout << "Balance: $" << balance << std::endl;
    WaitEnter();    
    clearLine();
    clearLine();
    clearLine();
    clearLine();
    clearLine();
    clearLine();
    clearLine();
    clearLine();
    clearLine();
    clearLine();
}

// Admin Implementation
Admin::Admin(const std::string& user, int pass) : Person(user, pass) {}

void Admin::createNewTicket(std::vector<Ticket>& tickets) {
    std::string org, des;
    std::cout << "Origin: "; std::cin >> org;
    std::cout << "Destination: "; std::cin >> des;
    int price = getIntInput("Price: ");
    tickets.push_back(Ticket(des, org, price));
    saveTickets(tickets);
    std::cout << "Ticket Created.";
    WaitEnter();
    clearLine();
    clearLine();
    clearLine();
    clearLine();
}

void Admin::viewAllUsers(const std::vector<Customer>& customers) const {
    size_t i = 0;
    
    std::cout << "--- All Customers ---\n";
    for(const auto& c : customers) {
        std::cout  << "Username : " << c.getUsername() << " | Password : " << c.getPassword() << "\n";
        i++;
    }
    std::cout << "" << "\n1. View Customer Profile" 
              << "\n2. Exit" << std::endl;
    int choice = getIntInput("Choice : ");
    clearLine();
    clearLine();
    clearLine();

    if (choice == 1) {
        std::string user;
        std::cout << "--- Customer Profile ---" << "\nUsername: "; std::cin >> user;
        int pass = getIntInput("Password: ");
        clearLine();
        clearLine();
        for (const auto& c : customers) {
            if (c.login(user, pass)) {
                clearLine();
                clearLine();
                clearLine();
                for (size_t j = 0; j < i;j++ ) {
                    clearLine();
                }
                std::cout << "--- Customer Profile ---\n";
                c.displayProfile();
                clearLine();
                break;
            }
            else {
                std::cout << "Invalid Credentials" << std::endl;
                WaitEnter();
                for (size_t j = 0; j < i;j++ ) {
                    clearLine();
                }
                clearLine();
                clearLine();
                clearLine();
                clearLine();
                clearLine();
                break;
            }
    }
    }   
    else if (choice == 2) {
        std::cout << "Exiting..." << std::endl;
        WaitEnter();
        for (size_t j = 0; j < i;j++ ) {
            clearLine();
        }
        clearLine();
        clearLine();
        clearLine();
        clearLine();
    }
    else {
        std::cout << "Input Invalid" <<  std::endl;
        WaitEnter();
        for (size_t j = 0; j < i;j++ ) {
            clearLine();
        }
        clearLine();
        clearLine();
        clearLine();
        clearLine();
    }

    
}

// Utility Implementation
void saveUsers(const std::vector<Customer>& customers) {
    std::ofstream file("users.txt");
    if (!file) return;

    for (const auto &p : customers) {
        file << encode(p.getUsername()) << " " << p.getPassword() << " "
             << encode(p.getName()) << " " << p.getBirth() << " " << encode(p.getAddress()) << " "
             << encode(p.getCity()) << " " << encode(p.getProvince()) << " "
             << encode(p.getStreet()) << " " << p.getPostalCode() << " "
             << p.getBalance() << " " << encode(p.getHistoryString()) << "\n";
    }
}

void loadUsers(std::vector<Customer>& customers) {
    std::ifstream file("users.txt");
    if (!file) return;

    std::string username, name, address, city, province, street, historyStr;
    int password, birth, postal, balance;

    while (file >> username >> password >> name >> birth >> address >> city
                >> province >> street >> postal >> balance >> historyStr) {
        
        Customer c(decode(username), password);
        c.setBasicInfo(decode(name), birth, decode(address), decode(city), decode(province), decode(street), postal);
        c.setBalance(balance);
        c.loadHistoryFromString(decode(historyStr));
        customers.push_back(c);
    }
}

void saveTickets(const std::vector<Ticket>& tickets) {
    std::ofstream file("tickets.txt");
    if (!file) return;
    for (const auto &p : tickets) {
        file << encode(p.getOrigin()) << " " << p.getDestination() << " " << p.getPrice() << "\n";
    }
}

void loadTickets(std::vector<Ticket>& tickets) {
    std::ifstream file("tickets.txt");
    if (!file) return;
    std::string origin, destination;
    int price;
    while (file >> origin >> destination >> price) {
        tickets.push_back(Ticket(decode(destination), decode(origin), price));
    }
}

std::string encode(const std::string& s) {
    std::string r = s;
    std::replace(r.begin(), r.end(), ' ', '_');
    return r.empty() ? "NULL" : r;
}

std::string decode(const std::string& s) {
    std::string r = s;
    if(r == "NULL") return "";
    std::replace(r.begin(), r.end(), '_', ' ');
    return r;
}

// Basic ANSI clear
void clearLine() {
    std::cout << "\033[A\033[2K";
}

int getIntInput(const std::string& prompt) {
    int x;
    std::cout << prompt;
    while(!(std::cin >> x)){
        clearLine();
        std::cout << "Invalid input. Numbers only: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    return x;
}

void WaitEnter() {
    std::cout << "\nPress Enter to continue...";
    while (std::cin.get()!='\n');
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    clearLine(); 
}