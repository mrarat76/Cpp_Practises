#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "flowessalse.hpp"
#include "flowersales_imp.cpp"

int main() {
    // Initialize the flower database
    initializeFlowerDatabase();
    loadFlowerDataFromFile();
    std::vector<UserBase> users(100); // Maximum assumption of 100 users
    int userCount = 0;

    // Read users from a file
    if (!readUsersFromFile(users, userCount)) {
        std::cout << "User's data cannot be detected.." << std::endl;
        return 1;
    }

    // Default admin user check
    if (userCount == 0) {
        // If user data is empty, add a default admin user
        users[0].setUsername("admin") ;
        users[0].setPassword("admin123");
        users[0].isAdminUser(); // Mark this user as admin
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
                            adduser(users, userCount, newUsername, newPassword, newUserIsAdmin);
                            break;
                        }
                        case 2: {
                            std::string deleteUser;
                            std::cout << "Enter the username to delete: ";
                            std::cin >> deleteUser;
                            deleteUser(users, userCount, deleteUser);
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
                                if (flowerDatabase[i].flowerID == id) {
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

                            addFlower(id, flowerName, flowerPrice, flowerType, flowerStock);
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
                                if (flowerDatabase[i].flowerID == editFlowerID) {
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
                            std::cin >> newFlowerType;
                            std::cout << "Enter the new flower stock quantity: ";
                            std::cin >> newFlowerStock;

                            updateFlower(editFlowerID, newFlowerName, newFlowerPrice, newFlowerType, newFlowerStock);
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
                            listUsers(users, userCount);
                            break;
                        }
                        case 11:{
                            std::string userName;
                            std::cout << "To find, enter the username: ";
                            std::cin >> userName;
                            findUser(users, userCount, userName);
                            break;
                        }
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
