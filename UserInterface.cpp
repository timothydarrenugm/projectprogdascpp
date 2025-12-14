/**
 * Project Ticketing Machine Apliccation
 */

#include "Ticketing.h"
#include <iostream>
#include <vector>
#include <limits>

// Helper function for the User Menu Loop
void userMenu(Customer& currentCustomer, std::vector<Ticket>& tickets, std::vector<Customer>& allCustomers) {
    std::cout << "=== USER MENU: " << currentCustomer.getUsername() << " ===\n\n" ;
    while (true) {
        std::cout << "1. View Profile\n"
                  << "2. Check Balance\n"
                  << "3. Top Up Balance\n"
                  << "4. Buy Ticket\n"
                  << "5. Transaction History\n"
                  << "6. Logout\n"
                  << "Choice: ";
        
        int choice = getIntInput("");
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();

        if (choice == 1) {
            currentCustomer.displayProfile();
        } 
        else if (choice == 2) {
            std::cout << "Current Balance: $" << currentCustomer.getBalance() ;
            WaitEnter();
            clearLine();
        } 
        else if (choice == 3) {
            std::cout << "Current Balance: $" << currentCustomer.getBalance() ;
            int amount = getIntInput("\nEnter amount to top up: ");
            currentCustomer.addBalance(amount);
            saveUsers(allCustomers);
            WaitEnter();
            clearLine();
            clearLine();
            clearLine();
        } 
        else if (choice == 4) {
            if (tickets.empty()) {
                std::cout << "(No tickets available)\n";
                WaitEnter();
                clearLine();
                continue;
            }
            std::cout << "=== Ticket Store ===\n" << "--- Available Tickets ---\n";
            std::cout << "Current Balance: $" << currentCustomer.getBalance() << "\n";
            for (size_t i = 0; i < tickets.size(); i++) {
                std::cout << i + 1 << ". " << tickets[i].getOrigin() << " -> " 
                          << tickets[i].getDestination() << " | Price: $" 
                          << tickets[i].getPrice() << "\n";
            }

            int tIndex = getIntInput("Select ticket number (0 to cancel): ");
            if (tIndex > 0 && tIndex <= (int)tickets.size()) {
                if(currentCustomer.buyTicket(tickets[tIndex - 1])) {
                    saveUsers(allCustomers); 
                }
            }
            for (size_t i = 0; i < tickets.size(); i++) {
                clearLine();
            }
            clearLine();
            clearLine();
            clearLine();
            clearLine();
            clearLine();
        } 
        else if (choice == 5) {
            currentCustomer.viewHistory();
        } 
        else if (choice == 6) {
            std::cout << "Logging out...\n";
            WaitEnter();
            clearLine();
            clearLine();
            clearLine();
            clearLine();
            break;
        } 
        else {
            std::cout << "Invalid choice.";
            WaitEnter();
            clearLine();
        }
    }
}

void adminMenu(std::vector<Customer>& customers, std::vector<Ticket>& tickets) {
    Admin admin("admin", 1234); 

    std::cout << "===== ADMIN PANEL =====\n" << std::endl;
    while (true) {
        std::cout << "1. View All Users\n"
                  << "2. Create New Ticket\n"
                  << "3. Change Ticket Price\n"
                  << "4. View All Tickets\n"
                  << "5. Delete Ticket\n"
                  << "6. Delete User\n"
                  << "7. Reset User Password\n"
                  << "8. Exit\n"
                  << "Choice: ";
        
        int choice = getIntInput("");
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();

        if (choice == 1) {
            admin.viewAllUsers(customers);
        }
        else if (choice == 2) {
            admin.createNewTicket(tickets);
        }
        else if (choice == 3) {
            std::string org, des;
            std::cout << "Origin: "; std::cin >> org;
            std::cout << "Destination: "; std::cin >> des;
            
            bool found = false;
            for(auto& t : tickets) {
                if(t.getOrigin() == org && t.getDestination() == des) {
                    int newPrice = getIntInput("New Price: ");
                    t.resetPrice(newPrice); 
                    saveTickets(tickets);
                    std::cout << "Price updated.";
                    found = true;
                    WaitEnter();
                    clearLine();
                    clearLine();
                    clearLine();
                    clearLine();
                    break;
                }
            }
            if(!found) std::cout << "Ticket not found.\n";
        }
        else if (choice == 4) {
            size_t i = 0 ;
            std::cout << "--- Active Tickets ---\n";
            for(const auto& t : tickets) {
                std::cout << t.getOrigin() << " -> " << t.getDestination() 
                          << " [$" << t.getPrice() << "]\n";
                i++;
            }
            WaitEnter();
            for (size_t j = 0; j < i;j++ ) {
                clearLine();
            }
            clearLine();
            clearLine();
        }
        else if (choice == 5) { // Delete Tickets
           std::string org, des;
           std::cout << "Origin: "; std::cin >> org;
           std::cout << "Destination: "; std::cin >> des;
           
           auto it = tickets.begin();
           bool removed = false;
           while(it != tickets.end()) {
               if(it->getOrigin() == org && it->getDestination() == des) {
                   it = tickets.erase(it);
                   saveTickets(tickets);
                   removed = true;
                   std::cout << "Ticket deleted.";
               } else {
                   ++it;
               }
           }
           if(!removed) std::cout << "Ticket not found.";
           WaitEnter();
            clearLine();
            clearLine();
            clearLine();
        }
        else if (choice == 6) {
            std::string user;
            std::cout << "Username to delete: "; std::cin >> user;
            
            bool removed = false;
            for(size_t i=0; i<customers.size(); i++) {
                if(customers[i].getUsername() == user) {
                    customers.erase(customers.begin() + i);
                    saveUsers(customers);
                    std::cout << "User deleted.";
                    removed = true;
                    WaitEnter();
                    clearLine();
                    clearLine();
                    break;
                }
            }
            if(!removed) {
                std::cout << "User not found.\n";
                WaitEnter();
                clearLine();
                clearLine();
                clearLine();
            }
        }
        else if (choice == 7) {
            std::string user;
            std::cout << "Username: "; std::cin >> user;
            bool found = false;
            for(auto& c : customers) {
                if(c.getUsername() == user) {
                    int newPass = getIntInput("New Password: ");
                    c.resetPassword(newPass);
                    saveUsers(customers);
                    std::cout << "Password reset.";
                    found = true;
                    WaitEnter();
                    clearLine();
                    clearLine();
                    clearLine();
                    break;
                }
            }
            if(!found) { 
                std::cout << "User not found.";
                WaitEnter();
                clearLine();
                clearLine();
            }
        }
        else if (choice == 8) {
            clearLine();
            clearLine();
            clearLine();
            break;
        }
    }
}

void logins() {

    std::vector<Customer> customers;
    std::vector<Ticket> tickets;

    loadUsers(customers);
    loadTickets(tickets);

    const std::string ADMIN_USER = "admin";
    const int ADMIN_PASS = 1234;

    std::cout << "===  TICKET SYSTEM ===\n\n" ;
    while (true) {
        std::cout << "1. Login as User\n"
                  << "2. Register New User\n"
                  << "3. Login as Admin\n"
                  << "4. Exit\n"
                  << "Choice: ";
        
        int choice = getIntInput("");
        clearLine();
        clearLine();
        clearLine();
        clearLine();
        clearLine();

        if (choice == 1) {
            std::string user;
            std::cout << "# Login Page #\n\n" << "Username: "; std::cin >> user;
            int pass = getIntInput("Password: ");

            bool found = false;
            for (auto& c : customers) {
                if (c.login(user, pass)) {
                    std::cout << "Login successful!\n";
                    clearLine();
                    clearLine();
                    clearLine();
                    clearLine();
                    clearLine();
                    found = true;
                    userMenu(c, tickets, customers);
                    break;
                }
            }
            if (!found) {
                std::cout << "Invalid credentials.";
                WaitEnter();
                clearLine();
                clearLine();
                clearLine();
                clearLine();
                clearLine();
            }
        }
        else if (choice == 2) {
            std::string user;
            std::cout << "# Register Page #\n" <<  "Choose Username: "; std::cin >> user;

            bool exists = false;
            for (const auto& c : customers) {
                if (c.getUsername() == user) exists = true;
            }

            if (exists) {
                std::cout << "Username taken.\n";
                WaitEnter();
                clearLine();
                clearLine();
                clearLine();
            } else {
                int pass = getIntInput("Choose Password (numbers): ");
                
                // Create a CUSTOMER object
                Customer newC(user, pass);
                
                // Set details
                std::string name, address, city, prov, street;
                int birth, postal;
                std::cin.ignore(); // clear buffer
                std::cout << "Name : "; std::getline(std::cin, name);
                birth = getIntInput("Birth Year : ");
                std::cin.ignore();
                std::cout << "Address : "; std::getline(std::cin, address); 
                std::cout << "Street : "; std::getline(std::cin, street);
                std::cout << "City : "; std::getline(std::cin, city);
                std::cout << "Province : "; std::getline(std::cin, prov);
                postal = getIntInput("Postal Code : ");

                newC.setBasicInfo(name, birth, address, city, prov, street, postal);
                
                customers.push_back(newC);
                saveUsers(customers);
                std::cout << "Registered successfully!\n";
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
                clearLine();
                clearLine();
            }
        }
        else if (choice == 3) {
            std::string user;
            std::cout << "Admin Username : "; std::cin >> user;
            int pass = getIntInput("Admin Password : ");

            if (user == ADMIN_USER && pass == ADMIN_PASS) {
                std::cout << "Admin Access Granted.\n";
                WaitEnter();
                clearLine();
                clearLine();
                clearLine();
                clearLine();
                adminMenu(customers, tickets);
            } else {
                std::cout << "Access Denied.\n";
                WaitEnter();
                clearLine();
                clearLine();
                clearLine();
                clearLine();
            }
        }
        else if (choice == 4) {
            clearLine();
            clearLine();
            std::cout << "Goodbye.\n";
            break;
        }
    }
}
