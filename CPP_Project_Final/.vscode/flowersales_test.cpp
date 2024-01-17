#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "flowessalse.hpp"
#include "flowersales_imp.cpp"
#include "messagesandmanager.cpp"

int main() {
    // Initialize the flower database
    initializeFlowerDatabase();
    initializeFlowerOrderDatabase();
    loadFlowerDataFromFile();
    loadFlowerorderDataFromFile();
    
    std::vector<UserBase> users; // Dinamik olarak büyüyebilir
    std::vector<Manager> managers; // Dinamik olarak büyüyebilir
    std::vector<User> userss; // Dinamik olarak büyüyebilir
    std::vector<admin> admins; // Dinamik olarak büyüyebilir
    std::vector<RegisterMessage> regs; // Dinamik olarak büyüyebilir
    initializeregistremessagesfromtxt(regs);
    /*std::vector<UserBase> users(100); // Maximum assumption of 100 users
    std::vector<Manager> managers(100); // Maximum assumption of 100 managers*/
    readmanagersfromfile(managers, "managers.txt");
   /*
    std::vector<User> userss (100);
    std::vector<admin> admins (100);
    std::vector<RegisterMessage> regs(100);*/


    
    if (initializeUsers(users)) {
        std::cout << "Users initialized successfully." << std::endl;
    } else {
        std::cout << "Unable to initialize users from file." << std::endl;
    }
    
    int userCount = 0;
    int adminCount=0;
    int uscount=0; 

    // Read users from a file
    if (!readUsersFromFile(users, userCount)) {
        std::cout << "User's data cannot be detected.." << std::endl;
        return 1;
    }

    // Default admin user check
    if (userCount == 0) {
        // If user data is empty, add a default admin user
        if (users.empty()) {
        users.emplace_back(); // Add a new User object to the vector
    }
        users[0].setUsername("admin") ;
        users[0].setPassword("admin123");
        users[0].setAdminUser(true); // Mark this user as admin
        userCount = 1;
        if (writeUsersToFile(users)) {
            std::cout << "Default admin has been generated." << std::endl;
        } else {
            std::cout << "Attention! Default admin has not been generated." << std::endl;
            return 1;
        }
    }

    bool isLoggedIn = false;
    std::string username;

    while (true) {
       
       int loginChoice;
        std::cout << "\033[37;1mProvided by AraTech Autonomous Systems\033[0m" << std::endl;
        std::cout << "=== FLOWER SALES SYSTEM ===" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Manager Login / Register" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> loginChoice;

        switch (loginChoice){
         case 1: {
                // Normal username and password login
                std::string password;

                std::cout << "===     LOGIN PAGE    ===" << std::endl;
                std::cout << "Username: ";
                std::cin >> username;
                std::cout << "Password: ";
                std::cin >> password;

                // Check username and password, allow them to log in
                int userIndex = -1;
                for (int i = 0; i < userCount; i++) {
                    if (username == users[i].getUsername() && password == users[i].getPassword()) {
                        isLoggedIn = true; // User has logged in
                        break;
                    }
                }

                if (!isLoggedIn) {
                    std::cout << "Invalid username or password." << std::endl;
                    continue; // If user can't log in, return to the main menu
                }
                break;
            }

           case 2:
                 int managerChoice;
                std::cout << "=== MANAGER LOGIN / REGISTER ===" << std::endl;
                std::cout << "1. Manager Login" << std::endl;
                std::cout << "2. Register as User" << std::endl;
                std::cout << "3. Exit" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> managerChoice;
              

              switch (managerChoice) {
                case 1: {
                    // Manager login
                    std::string managerusername;
                    std::string managerpassword;

                    std::cout << "===     LOGIN PAGE    ===" << std::endl;
                    std::cout << "Username: ";
                    std::cin >> managerusername;
                    std::cout << "Password: ";
                    std::cin >> managerpassword;

                    

                    // Check username and password, allow them to log in
                    int userIndex = -1;
bool exitMenu = false;

while (!exitMenu) {
    for (int i = 0; i < userCount; i++) {
        if (managerusername == managers[i].username && managerpassword == managers[i].password) {
            std::cout << "Welcome " << managers[i].username << std::endl;
            std::cout << "1. Check Flower Sales" << std::endl;
            std::cout << "2. Check Flower Stock" << std::endl;
            std::cout << "3. List Users" << std::endl;
            std::cout << "4. Send Message to Admin" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::cout << "6. List Messages" << std::endl;
            std::cout << "7. Add Manager" << std::endl;
            std::cout << "8. Delete Manager" << std::endl;
            std::cout << "9. Update Manager" << std::endl;
            std::cout << "10. Find Manager" << std::endl;
            std::cout << "11. List Managers" << std::endl;
            std::cout << "12. Update User" << std::endl;
            std::cout << "13. Find User" << std::endl;
            std::cout << "14.Read register messages" << std::endl;
            std::cout << "Enter your choice:";

            int swchoice;
            std::cin >> swchoice;

            switch (swchoice) {
                case 1: {
                    listOrders();
                    break;
                }
                case 2: {
                    listFlowers(flowerDatabase, flowerCount);
                    break;
                }
                case 3: {
                    listUsers(users);
                    break;
                }
                case 4: {
                    std::string message;
                    std::cout << "Enter your message: ";
                    std::cin >> message;
                    managers[i].writeMessage(message);
                    break;
                }
                case 5: {
                    std::cout << "Exiting..." << std::endl;
                    exitMenu = true; // Set the flag to exit the loop
                    break;
                }
                case 6: {
                    managers[i].readmessages();
                    break;
                }
                case 7: {
                    std::string newUsername;
                    std::string newPassword;

                    std::cout << "Enter new username: ";
                    std::cin >> newUsername;
                    std::cout << "Enter new password: ";
                    std::cin >> newPassword;

                    addmanager(managers, newUsername.c_str(), newPassword.c_str());

                    break;
                }
                case 8: {
                    std::string deleteManager;
                    std::cout << "Enter the username to delete: ";
                    std::cin >> deleteManager;
                    deletemanager(managers, deleteManager.c_str());

                    break;
                }
                case 9: {
                    std::string userName;
                    std::cout << "To update, enter the username: ";
                    std::cin >> userName;

                    std::string newUsername;
                    std::string newPassword;

                    std::cout << "Enter the new password: ";
                    std::cin >> newPassword;

                    updatemanager(managers, userName.c_str(),  newPassword.c_str());

                    break;
                }
                case 10: {
                    std::string userName;
                    std::cout << "To find, enter the username: ";
                    std::cin >> userName;
                    findmanager(managers, userName.c_str());
                    break;
                }
                case 11: {
                    listmanagers(managers);
                    break;
                }
                case 12: {
                    
                    std::string userName;
                    std::cout << "To update, enter the username: ";
                    std::cin >> userName;
       
                    std::string newUsername;
                    std::string newPassword;
                    int newUserIsAdmin;

                    std::cout << "Enter the new username: ";
                    std::cin >> newUsername;
                    std::cout << "Enter the new password: ";
                    std::cin >> newPassword;
                    std::cout << "Specify if the user is an admin (1 for admin, 0 for regular user): ";
                    std::cin >> newUserIsAdmin;

                    updateuser(users, userCount, userName.c_str(), newUsername.c_str(), newPassword.c_str(), newUserIsAdmin, admins, adminCount, userss, uscount);

                    break;
                }
                case 13: {
                    std::string userName;
                    std::cout << "To find, enter the username: ";
                    std::cin >> userName;
                    findUser(users, userName.c_str());
                    break;
                }

                case 14: {
                    readregistermessages(regs);
                    break;
                }
                
                default: {
                    std::cout << "Invalid choice." << std::endl;
                    break;
                }
            }

            if (exitMenu) {
                  fflush(stdout); // Flush the buffer
                system("cls");
                return main();
            }
                break; // Exit the for loop
               
        }
    }
}

                
                
                }
                

                case 2: {
                    std::string messageType;
                    std::cout << "===     REGISTER PAGE    ===" << std::endl;
                    std::cout << "Enter your message: ";
                    std::cout << "Enter your message as concatanated for insance: adduser,username,password,1 or 0 ";
                    std::cin >> messageType;
                    addToMessageArray(messageType, regs);
                    writemessagestotxt(regs);
                    // register array
                }
                case 3: {
                   std::cout << "Exiting..." << std::endl;
                            fflush(stdout); // Flush the buffer
                            system("cls");  // Clear the console (for Windows)
                            return main();
            }
            
            default:
                std::cout << "Invalid choice." << std::endl;
                break;
        }
                



        }
        
       
       
       
       
       
       
       
       
       
        if (!isLoggedIn) {
            // If the user is not logged in, request username and password
            std::string password;

            std::cout << "\033[37;1mProvided by AraTech Autonomous Systems\033[0m" << std::endl;
            std::cout << "=== FLOWER SALES SYSTEM ===" << std::endl;
            std::cout << "Welcome" << std::endl;
            std::cout << "===     LOGIN PAGE    ===" << std::endl;
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;

            // Check username and password, allow them to login
            int userIndex = -1;
            for (int i = 0; i < userCount; i++) {
                if (username == users[i].getUsername() && password == users[i].getPassword()) {
                    isLoggedIn = true; // User has logged in
                    break;
                }
            }

            if (!isLoggedIn) {
                std::cout << "Invalid username or password." << std::endl;
                continue; // If user can't login, request username and password again
            }
        }

        if (isLoggedIn) {
            // If the user is logged in, perform actions in this block
            bool isAdmin = false;

            for (int i = 0; i < userCount; i++) {
                if (username == users[i].getUsername()) {
                    isAdmin = users[i].isAdminUser();
                    break;
                }
            }

            if (isAdmin) {
                int choice;
                while (true) {
                    std::cout << "Administrator Panel" << std::endl;
                    std::cout << "1. Add User" << std::endl;
                    std::cout << "2. Delete User" << std::endl;
                    std::cout << "3. Order a flower" << std::endl;
                    std::cout << "4. List all flowers" << std::endl;
                    std::cout << "5. Exit" << std::endl;
                    std::cout << "6. Add flower" << std::endl;
                    std::cout << "7. Edit flower" << std::endl;
                    std::cout << "8. Find flower by ID" << std::endl;
                    std::cout << "9. List orders" << std::endl;
                    std::cout << "10. List all users" << std::endl;
                    std::cout << "11. Find user by Username" << std::endl;
                    std::cout << "12. Update User" << std::endl;
                    std::cout<<"13. List Messages"<<std::endl;
                    std::cout << "14.See massages from managers." << std::endl; 
                    std::cout << "Enter your choice: ";
                    std::cin >> choice;

                    switch (choice) {
                        case 1: {
                            std::string newUsername;
                            std::string newPassword;
                            bool newUserIsAdmin;

                            std::cout << "Enter new username: ";
                            std::cin >> newUsername;
                            std::cout << "Enter new password: ";
                            std::cin >> newPassword;
                            std::cout << "Specify whether the new user is an administrator (1) or a regular user (0): ";
                            std::cin >> newUserIsAdmin;
                            
                            adduser(users, &userCount, newUsername.c_str(), newPassword.c_str(), newUserIsAdmin, admins, adminCount, userss, uscount);

                            break;
                        }
                        case 2: {
                            std::string deleteUSer;
                            std::cout << "Enter the username to delete: ";
                            std::cin >> deleteUSer;
                            deleteUser(users, &userCount, deleteUSer.c_str(), admins, adminCount, userss, userCount); // Pass deleteUser.c_str()

                            break;
                        }
                        case 3: {
                            placeOrder(flowerDatabase, flowerCount);
                            break;
                        }
                        case 4: {
                            listFlowers(flowerDatabase, flowerCount);
                            break;
                        }
                        case 5: {
                            std::cout << "Exiting..." << std::endl;
                            fflush(stdout); // Flush the buffer
                            system("cls");  // Clear the console (for Windows)
                            return main();
                        }
                        case 6: {
                            int id;
                            std::string flowerName;
                            float flowerPrice;
                            int flowerType;
                            int flowerStock;

                            std::cout << "To add, enter the flower ID: ";
                            std::cin >> id;
                            // Check if a flower with the given ID already exists
                            bool isAlreadyExist = false;
                            for (int i = 0; i < flowerCount; i++) {
                                if (flowerDatabase[i].getFlowerID() == id) { // Assuming getFlowerID() is a public member function of the Flower class
                                    isAlreadyExist = true;
                                    break;
                                }
                            }

                            if (isAlreadyExist) {
                                std::cout << "A flower with this ID already exists. The addition couldn't be completed." << std::endl;
                                break;
                            }

                            std::cout << "The names are as follows: ROSE, TULIP, LILY, DAISY, SUNFLOWER." << std::endl;
                            std::cout << "Enter the flower name to add: ";
                            std::cin >> flowerName;
                            std::cout << "Enter the flower price: ";
                            std::cin >> flowerPrice;
                            std::cout << "Specify the flower type: {ROSE -> 0, TULIP->1, LILY->2, DAISY->3, SUNFLOWER->4} ";
                            std::cin >> flowerType;
                            std::cout << "Enter the flower stock quantity:";
                            std::cin >> flowerStock;

                            FlowerType flowerTypeEnum;
                            switch (flowerType) {
                                case 0:
                                    flowerTypeEnum = static_cast<FlowerType>(0);
                                    break;
                                case 1:
                                    flowerTypeEnum = static_cast<FlowerType>(1);
                                    break;
                                case 2:
                                    flowerTypeEnum = static_cast<FlowerType>(2);
                                    break;
                                case 3:
                                    flowerTypeEnum =static_cast<FlowerType>(3);
                                    break;
                                case 4:
                                    flowerTypeEnum =static_cast<FlowerType>(4);
                                    break;
                                default:
                                  std::cout << "Invalid selection. Please choose a valid option." << std::endl;

                            }

                            addFlower(id, flowerName.c_str(), flowerPrice, flowerTypeEnum, flowerStock);
                            if (writeFlowerDataToFile()) {
                                std::cout << "The flower has been successfully added." << std::endl;
                            } else {
                                std::cout << "The flower could not be added." << std::endl;
                            }
                            break;
                        }
                        case 7: {
                            int editFlowerID;

                            std::cout << "Enter the flower ID to edit:";
                            std::cin >> editFlowerID;

                            bool found = false;
                            for (int i = 0; i < flowerCount; i++) {
                                if (flowerDatabase[i].getFlowerID() == editFlowerID) { // Assuming getFlowerID() is a public member function of the Flower class
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                std::cout << "The flower with this ID could not be found." << std::endl;
                                break;
                            }

                            std::string newFlowerName;
                            float newFlowerPrice;
                            int newFlowerType;
                            int newFlowerStock;

                            std::cout << "Enter the new flower name:";
                            std::cin >> newFlowerName;
                            std::cout << "Enter the new flower price: ";
                            std::cin >> newFlowerPrice;
                            std::cout << "Specify the new flower type: ";
                            std::cout << "Specify the flower type: {ROSE -> 0, TULIP->1, LILY->2, DAISY->3, SUNFLOWER->4} ";
                            std::cin >> newFlowerType;
                            std::cout << "Enter the new flower stock quantity: ";
                            std::cin >> newFlowerStock;

                            updateFlower(editFlowerID, newFlowerName.c_str(), newFlowerPrice, static_cast<FlowerType>(newFlowerType));
                            writeFlowerDataToFile();

                            break;
                        }
                        case 8: {
                            int flowerID;
                            std::cout << "To find, enter the flower ID: ";
                            std::cin >> flowerID;
                            findFlower(flowerID);
                            break;
                        }
                        case 9:{
                            listOrders();
                            break;
                        }
                        case 10:{
                            listUsers(users);
                            break;
                        }
                        case 11:{
                            std::string userName;
                            std::cout << "To find, enter the username: ";
                            std::cin >> userName;
                            findUser(users, userName.c_str());
                            break;
                        }
                        case 12:{
                            std::string userName;   
                            std::cout << "To update, enter the username: ";
                            std::cin >> userName;
                            
                            std::string newUsername;
                            std::string newPassword;
                            bool newUserIsAdmin;

                            std::cout << "Enter the new username: ";
                            std::cin >> newUsername;
                            std::cout << "Enter the new password: ";
                            std::cin >> newPassword;
                            std::cout << "Specify if the user is an admin (1 for admin, 0 for regular user): ";
                            std::cin >> newUserIsAdmin;

                            updateuser(users, userCount, userName.c_str(), newUsername.c_str(), newPassword.c_str(), newUserIsAdmin, admins, adminCount, userss, uscount);

                            break;
                        }
                        case 13:{
                            readregistermessages(regs);
                            break;
                        }
                        case 14:{
                             Manager manager;

                            manager.readmessages();}
                            break;
                        
                        default:
                            std::cout << "Invalid selection. Please choose a valid option." << std::endl;
                    }
                }
            } else {
                int choice;
                while (true) {
                    std::cout << "User Panel" << std::endl;
                    std::cout << "1. Order a flower" << std::endl;
                    std::cout << "2. List all flowers" << std::endl;
                    std::cout << "3. Show order" << std::endl;
                    std::cout << "4. Exit" << std::endl;
                    std::cout << "5. Find flower by ID" << std::endl;
                    std::cout << "Enter your precious choice: ";
                    std::cin >> choice;

                    switch (choice) {
                        case 1: {
                            placeOrder(flowerDatabase, flowerCount);
                            break;
                        }
                        case 2: {
                            listFlowers(flowerDatabase, flowerCount);
                            break;
                        }
                        case 3: {
                            listOrders();
                            break;
                        }
                        case 4: {
                            std::cout << "Exiting..." << std::endl;
                            fflush(stdout); // Flush the buffer
                            system("cls");  // Clear the console (for Windows)
                            return main();
                        }
                        case 5: {
                            int flowerID;
                            std::cout << "To find, enter the flower ID:";
                            std::cin >> flowerID;
                            findFlower(flowerID);
                            break;
                        }
                        default:
                            std::cout << "Invalid selection. Please choose a valid option." << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}
