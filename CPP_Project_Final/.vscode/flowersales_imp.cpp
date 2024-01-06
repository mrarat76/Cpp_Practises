#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "flowessalse.hpp"
#include <sstream> 

enum FlowerType { ROSE, TULIP, LILY, DAISY, SUNFLOWER };



// Global variables
Flower flowerDatabase[100];
int flowerCount = 0;

Flower* flowerorderdb = nullptr;
int flowercount = 0;

// Function implementations
void initializeFlowerDatabase() {
    flowerCount = 0;
}
std::ostream& operator<<(std::ostream& os, const FlowerType& flowerType) {
    switch (flowerType) {
        case FlowerType::ROSE:
            os << "Rose";
            break;
        case FlowerType::TULIP:
            os << "Tulip";
            break;
        case FlowerType::LILY:
            os << "Lily";
            break;
        case FlowerType::DAISY:
            os << "Daisy";
            break;
        case FlowerType::SUNFLOWER:
            os << "Sunflower";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

void loadFlowerDataFromFile() {
    std::ifstream file("flowers.txt");
    if (!file.is_open()) {
        std::cout << "Çiçek verileri okunamadı." << std::endl;
        return;
    }

    int flowerID;
    std::string name;
    double price;
    int typeAsInt;
    int stock;

    while (file >> flowerID >> name >> price >> typeAsInt >> stock) {
        FlowerType type = static_cast<FlowerType>(typeAsInt);
        flowerDatabase[flowerCount] = Flower(flowerID, name, price, type, stock);
        flowerCount++;
    }

    file.close();
}


const char* getFlowerTypeName(FlowerType type) {
    switch (type) {
        case FlowerType::ROSE:
            return "ROSE";
        case FlowerType::TULIP:
            return "TULIP";
        case FlowerType::LILY:
            return "LILY";
        case FlowerType::DAISY:
            return "DAISY";
        case FlowerType::SUNFLOWER:
            return "SUNFLOWER";
        default:
            return "UNKNOWN";
    }
}

void addFlower(int flowerID, const char* name, float price, FlowerType type, int stock) {
    if (flowerCount < 100) {
        flowerDatabase[flowerCount].setFlowerID(flowerID); // Assuming there is a setter function for flowerID
        flowerDatabase[flowerCount].setName(name);
        flowerDatabase[flowerCount].setPrice(price);
        flowerDatabase[flowerCount].setType(type);
        flowerDatabase[flowerCount].setStock(stock);
        flowerCount++;
    }
}

void findFlower(int flowerID) {
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].getFlowerID() == flowerID) {
            std::cout << "Flower ID: " << flowerDatabase[i].getFlowerID() << std::endl;
            std::cout << "Flower Name: " << flowerDatabase[i].getName() << std::endl;
            std::cout << "Flower Price: " << flowerDatabase[i].getPrice() << std::endl;
            std::cout << "Flower Type: " << flowerDatabase[i].getType() << std::endl;
            std::cout << "Flower Type Name: " << getFlowerTypeName(flowerDatabase[i].getType()) << std::endl;
            std::cout << "Flower stock quantity: " << flowerDatabase[i].getStock() << std::endl;
            return;
        }
    }
    std::cout << "The ID of " << flowerID << " could not be found." << std::endl;
}

void updateFlower(int flowerID, const char* newName, float newPrice, FlowerType newType) {
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].getFlowerID() == flowerID) {
            flowerDatabase[i].setName(newName);
            flowerDatabase[i].setPrice(newPrice);
            flowerDatabase[i].setType(newType);
            std::cout << "ID'si " << flowerID << " olan çiçek güncellendi." << std::endl;
            return;
        }
    }
    std::cout << "ID'si " << flowerID << " olan çiçek bulunamadı." << std::endl;
}

void deleteFlower(int flowerID) {
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].getFlowerID() == flowerID) {
            for (int j = i; j < flowerCount - 1; j++) {
                flowerDatabase[j] = flowerDatabase[j + 1];
            }
            flowerCount--;
            std::cout << "ID'si " << flowerID << " olan çiçek silindi." << std::endl;
            return;
        }
    }
    std::cout << "ID'si " << flowerID << " olan çiçek bulunamadı." << std::endl;
}

void summarizeFlowerSales() {
    float totalSales = 0;
    for (int i = 0; i < flowerCount; i++) {
        totalSales += flowerDatabase[i].getPrice();
    }
    std::cout << "Toplam Satış: " << totalSales << std::endl;
}

/*void initializeFlowerOrderDatabase(int initialSize) {
    flowerorderdb = new Flower[initialSize];
    if (flowerorderdb == nullptr) {
        std::cerr << "Hata: Çiçek siparişi veritabanı oluşturulamadı." << std::endl;
        exit(1);
    }
    flowercount = 0;
}*/

void cleanUpFlowerOrderDatabase() {
    delete[] flowerorderdb;
    flowerorderdb = nullptr;
    flowercount = 0;
}

void deleteFlowerFromFile(int flowerID) {
    std::ifstream inputFile("flowers.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Çiçek verileri okunamadı." << std::endl;
        return;
    }

    std::ofstream tempFile("temp_flower.txt");
    if (!tempFile.is_open()) {
        std::cerr << "Geçici dosya oluşturulamadı." << std::endl;
        return;
    }

    int currentID;
    std::string currentName;
    float currentPrice;
    int currentType;
    int currentStock;

    while (inputFile >> currentID >> currentName >> currentPrice >> currentType >> currentStock) {
        if (currentID != flowerID) {
            tempFile << currentID << " " << currentName << " " << currentPrice << " " << currentType << " " << currentStock << std::endl;
        }
    }

    inputFile.close();
    tempFile.close();

    remove("flowers.txt");
    rename("temp_flower.txt", "flowers.txt");

    std::cout << "ID'si " << flowerID << " olan çiçek başarıyla silindi." << std::endl;

    loadFlowerDataFromFile();
}


int userLogin(UserBase users[], int userCount, std::string& username, std::string& password) {
    int isLoggedIn = 0;

    std::string inputUsername;
    std::string inputPassword;

    std::cout << "Giriş" << std::endl;
    std::cout << "Kullanıcı Adı: ";
    std::cin >> inputUsername;
    std::cout << "Şifre: ";
    std::cin >> inputPassword;

    for (int i = 0; i < userCount; i++) {
        if (inputUsername == users[i].getUsername() && inputPassword == users[i].getPassword()) {
            isLoggedIn = 1;
            username = inputUsername;
            password = inputPassword;
            break;
        }
    }

    return isLoggedIn;
}


/*int userLogin(User users[], int userCount, char* username, char* password) {
    int isLoggedIn = 0;

    char inputUsername[50];
    char inputPassword[50];

    std::cout << "Giriş" << std::endl;
    std::cout << "Kullanıcı Adı: ";
    std::cin >> inputUsername;
    std::cout << "Şifre: ";
    std::cin >> inputPassword;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(inputUsername, users[i].username) == 0 && strcmp(inputPassword, users[i].password) == 0) {
            isLoggedIn = 1;
            strcpy(username, inputUsername);
            strcpy(password, inputPassword);
            break;
        }
    }

    return isLoggedIn;
}*/

int writeFlowerOrdersToFile(Flower* orders, int count) {
    std::ofstream file("flowerorder.txt", std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Dosya açma hatası" << std::endl;
        return 0;
    }

    for (int i = 0; i < count; i++) {
        file << orders[i].getFlowerID() << " " << orders[i].getName() << " " << orders[i].getPrice() << " " << orders[i].getType() << " " << orders[i].getStock() << std::endl;
    }

    file.close();
    return 1;
}

#include <iostream> // Include the necessary header file for the output stream

int writeFlowerDataToFile() {
    std::ofstream file("flowers.txt");
    if (!file.is_open()) {
        return 0;
    }

    for (int i = 0; i < flowerCount; i++) {
        file << flowerDatabase[i].getFlowerID() << " " << flowerDatabase[i].getName() << " " << flowerDatabase[i].getPrice() << " " << flowerDatabase[i].getType() << " " << flowerDatabase[i].getStock() << std::endl;
    }

    file.close();
    std::cout << "Flower data has been written to the file." << std::endl; // Add the missing std::cout statement

    return 1;
}

void updateflower(int flowerID, const char* newName, float newPrice, FlowerType newType, int newStock) {
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].getFlowerID() == flowerID) {
            flowerDatabase[i].setName(newName);
            flowerDatabase[i].setPrice(newPrice);
            flowerDatabase[i].setType(newType);
            flowerDatabase[i].setStock(newStock);

            if (writeFlowerDataToFile()) {
                std::cout << "The flower with ID " << flowerID << " has been successfully updated." << std::endl;
            } else {
                std::cout << "The flower with ID " << flowerID << " could not be updated." << std::endl;
            }
            return;
        }
    }
    std::cout << "The flower with ID " << flowerID << " was not found." << std::endl;
}





int writeUsersToFile(const std::vector<UserBase>& users) {
    std::ofstream file("users.txt");
    if (!file.is_open()) {
        return 0;
    }

    for (const UserBase& user : users) {
        file << user.getUsername() << " " << user.getPassword() << " " << user.isAdminUser() << std::endl;
    }

    file.close();
    return 1;
}



/*
int writeUsersToFile(UserBase users[], int userCount) {
    std::ofstream file("users.txt");
    if (!file.is_open()) {
        return 0;
    }

    for (int i = 0; i < userCount; i++) {
        file << users[i].getUsername() << " " << users[i].getPassword() << " " << users[i].isAdminUser() << std::endl;
    }

    file.close();
    return 1;
}*/


void deleteuser(std::vector<UserBase>& users, int* userCount, const char* deleteUsername) {
    int found = 0;
    for (int i = 0; i < *userCount; i++) {
        if (std::string(deleteUsername) == users[i].getUsername()) { // Kullanıcı adı karşılaştırması
            found = 1;
            for (int j = i; j < *userCount - 1; j++) {
                // Kullanıcıları kaydır
                users[j].setUsername(users[j + 1].getUsername());
                users[j].setPassword(users[j + 1].getPassword());
                users[j].setAdminUser(users[j + 1].isAdminUser());
            }
            (*userCount)--;

            if (writeUsersToFile(users)) {
                std::cout << "User '" << deleteUsername << "' has been successfully deleted." << std::endl;
            } else {
                std::cout << "User '" << deleteUsername << "' could not be deleted." << std::endl;
            }
            break;
        }
    }

    if (!found) {
        std::cout << "User '" << deleteUsername << "' not found." << std::endl;
    }
}

/*void deleteuser(UserBase users[], int* userCount, const char* deleteUsername) {
    int found = 0;
    for (int i = 0; i < *userCount; i++) {
        if (std::string(deleteUsername) == users[i].getUsername()) { // Kullanıcı adı karşılaştırması
            found = 1;
            for (int j = i; j < *userCount - 1; j++) {
                // Kullanıcıları kaydır
                users[j].setUsername(users[j + 1].getUsername());
                users[j].setPassword(users[j + 1].getPassword());
                users[j].setAdminUser(users[j + 1].isAdminUser());
            }
            (*userCount)--;

            if (writeUsersToFile(users, *userCount)) {
                std::cout << "User '" << deleteUsername << "' has been successfully deleted." << std::endl;
            } else {
                std::cout << "User '" << deleteUsername << "' could not be deleted." << std::endl;
            }
            break;
        }
    }

    if (!found) {
        std::cout << "User '" << deleteUsername << "' not found." << std::endl;
    }
}*/




/*void deleteuser(UserBase users[], int* userCount, const char* deleteUsername) {
    int found = 0;
    for (int i = 0; i < *userCount; i++) {
            if (strcmp(deleteUsername, users[i].getUsername()) == 0) {
        // SOLUTION: Convert deleteUsername to std::string before comparison
            if (std::string(deleteUsername) == users[i].username) {
            found = 1;
            for (int j = i; j < *userCount - 1; j++) {
                strcpy(users[j].username, users[j + 1].username);
                strcpy(users[j].password, users[j + 1].password);
                users[j].isAdmin = users[j + 1].isAdmin;
            }
            (*userCount)--;

            if (writeUsersToFile(users, *userCount)) {
                std::cout << "User '" << deleteUsername << "' has been successfully deleted." << std::endl;
            } else {
                std::cout << "User '" << deleteUsername << "' could not be deleted." << std::endl;
            }
            break;
        }
    }

    if (!found) {
        std::cout << "User '" << deleteUsername << "' not found." << std::endl;
    }
}*/

/*int readUsersFromFile(User users[], int* userCount) {
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        return 0;
    }

    *userCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string username, password;
        int isAdmin;
        if (iss >> username >> password >> isAdmin) {
            users[*userCount] = User(username, password, static_cast<bool>(isAdmin));
            (*userCount)++;
        }
    }

    file.close();
    return 1;
}*/

bool readUsersFromFile(std::vector<UserBase>& users, int& userCount) {
    // Open the user file for reading
    std::ifstream userFile("users.txt");
    if (!userFile) {
        return false; // Unable to open the file
    }

    // Read user data from the file and populate the users vector
    std::string username;
    std::string password;
    bool isAdmin;
    
    while (userFile >> username >> password >> isAdmin) {
        if (userCount < users.size()) {
            // Use the constructor to create a UserBase object and add it to the vector
            users[userCount] = UserBase(username, password, isAdmin);
            userCount++;
        } else {
            // Resize the vector if needed (you may adjust the size increment)
            users.resize(users.size() + 100);
        }
    }

    // Close the file
    userFile.close();

    return true; // Data successfully read from the file
}







/*
int readUsersFromFile(User users[], int* userCount) {
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        return 0;
    }

    *userCount = 0;
    while (file >> users[*userCount].getUsername() >> users[*userCount].password >> users[*userCount].isAdmin) {
        (*userCount)++;
    }

    file.close();
    return 1;
}

void adduser(UserBase users[], int* userCount, const char* newUsername, const char* newPassword, int newUserIsAdmin) {
    if (*userCount >= 100) {
        std::cout << "User limit exceeded. Cannot add more users." << std::endl;
        return;
    }

    // newUsername ve newPassword değerlerini doğrudan c_str() ile kullanabilirsiniz.
    users[*userCount].setUsername(newUsername);
    users[*userCount].setPassword(newPassword);
    users[*userCount].setAdminUser(newUserIsAdmin);
    (*userCount)++;

    if (writeUsersToFile(users, *userCount)) {
        std::cout << "User has been successfully added." << std::endl;
    } else {
        std::cout << "User could not be added." << std::endl;
    }
}*/


void adduser(std::vector<UserBase>& users, int* userCount, const char* newUsername, const char* newPassword, int newUserIsAdmin) {
    if (*userCount >= 100) {
        std::cout << "User limit exceeded. Cannot add more users." << std::endl;
        return;
    }

    // Add the new user directly to the vector and set its properties individually
    users.emplace_back();
    users.back().setUsername(newUsername);
    users.back().setPassword(newPassword);
    users.back().setAdminUser(newUserIsAdmin);

    (*userCount)++;

    if (writeUsersToFile(users)) {
        std::cout << "User has been successfully added." << std::endl;
    } else {
        std::cout << "User could not be added." << std::endl;
    }
}








/*
void adduser(UserBase users[], int* userCount, const char* newUsername, const char* newPassword, int newUserIsAdmin) {
    if (*userCount >= 100) {
        std::cout << "User limit exceeded. Cannot add more users." << std::endl;
        return;
    }

    strcpy(users[*userCount].username, newUsername);
    strcpy(users[*userCount].password, newPassword);
    users[*userCount].isAdmin = newUserIsAdmin;
    (*userCount)++;

    if (writeUsersToFile(users, *userCount)) {
        std::cout << "User has been successfully added." << std::endl;
    } else {
        std::cout << "User could not be added." << std::endl;
    }
}*/

void listFlowers(Flower flowerDatabase[], int flowerCount) {
    std::cout << "All Flowers have been listed below:" << std::endl;
    for (int i = 0; i < flowerCount; i++) {
        std::cout << "Flower ID: " << flowerDatabase[i].getFlowerID() << std::endl;
        std::cout << "Flower Name: " << flowerDatabase[i].getName() << std::endl;
        std::cout << "Flower Price: " << flowerDatabase[i].getPrice() << std::endl;
        std::cout << "Flower Type: " << flowerDatabase[i].getType() << std::endl;
        std::cout << "Flower Stock Quantity: " << flowerDatabase[i].getStock() << std::endl;
        std::cout << "Flower Type Name: " << getFlowerTypeName(flowerDatabase[i].getType()) << std::endl;
        std::cout << std::endl;
    }
}

void placeOrder(struct Flower flowerDatabase[], int flowerCount) {
    int flowerID;
    int value;

    std::cout << "Enter the flower ID to place an order: ";
    std::cin >> flowerID;
    std::cout << "Enter the flower stock quantity: ";
    std::cin >> value;

    int foundIndex = -1;
    for (int i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].getFlowerID() == flowerID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex >= 0) {
        if (flowerDatabase[foundIndex].getStock() > 0) {
            // Sipariş işlemini burada yapabilirsiniz
            std::cout << "Flower has ordered successfully" << std::endl;
            flowerDatabase[foundIndex].setStock(flowerDatabase[foundIndex].getStock() - value);

            // Dinamik olarak flowerorderdb'yi genişlet
            if (flowerorderdb == nullptr) {
                // flowerorderdb henüz boşsa, ilk defa bellek ayırın
                flowerorderdb = new Flower[1]();
            } else {
                // flowerorderdb doluysa, realloc kullanarak belleği genişletin
                Flower* temp = new Flower[flowercount + 1];
                for (int i = 0; i < flowercount; i++) {
                    temp[i] = flowerorderdb[i];
                }
                delete[] flowerorderdb;
                flowerorderdb = temp;
            }

            if (flowerorderdb == nullptr) {
                std::cout << "Error: Couldn't allocate or expand memory." << std::endl;
                exit(1);
            }

            // Yeni çiçeği flowerorderdb'ye ekleyin
            flowerorderdb[flowercount].setFlowerID(flowerDatabase[foundIndex].getFlowerID());
            flowerorderdb[flowercount].setName(flowerDatabase[foundIndex].getName()) ;
            flowerorderdb[flowercount].setPrice (flowerDatabase[foundIndex].getPrice());
            flowerorderdb[flowercount].setType(flowerDatabase[foundIndex].getType());
            flowerorderdb[flowercount].setStock(value);
            flowercount++;

            if (flowerDatabase[foundIndex].getStock() == 0) {
                deleteFlowerFromFile(flowerID);
            }

            // Sipariş verilen çiçeği silmek için deleteFlower fonksiyonunu çağırın

            writeFlowerOrdersToFile(flowerorderdb, flowercount);
        } else {
            std::cout << "Flower out of stock." << std::endl;
        }
    } else {
        std::cout << "Invalid Flower ID." << std::endl;
    }
}

void listOrders() {
    std::cout << "All orders:" << std::endl;
    for (int i = 0; i < flowercount; i++) {
        std::cout << "Flower ID: " << flowerorderdb[i].getFlowerID() << std::endl;
        std::cout << "Flower Name: " << flowerorderdb[i].getName() << std::endl;
        std::cout << "Flower Price: " << flowerorderdb[i].getPrice() << std::endl;
        std::cout << "Flower Type: " << flowerorderdb[i].getType() << std::endl;
        std::cout << "The stock quantity of the ordered flower: " << flowerorderdb[i].getStock() << std::endl;
        std::cout << "Flower Type Name: " << getFlowerTypeName(flowerorderdb[i].getType()) << std::endl;
        std::cout << std::endl;
    }
}

void listUsers(struct UserBase users[], int userCount) {
    std::cout << "All users:" << std::endl;
    for (int i = 0; i < userCount; i++) {
        std::cout << "Username: " << users[i].getUsername() << std::endl;
        std::cout << "Password: " << users[i].getPassword() << std::endl;
        std::cout << "Is Admin: " << users[i].isAdminUser() << std::endl;
        std::cout << "Admins are 0, Users are 1" << std::endl;
        std::cout << std::endl;
    }
}

void addUserAdmin(User** userPtr, admin* newAdmin) {
    if (userPtr == nullptr || *userPtr == nullptr) {
        // Hata işleme burada eklenebilir
        return;
    }

    // User yapısının admin işaretçisine yeni admin ekleniyor
   // (*userPtr)->admin = newAdmin;
}

void finduser(struct UserBase users[], int userCount, char* username) {
    int i;
    int found = 0;
    for (i = 0; i < userCount; i++) {
        if (users[i].getUsername()== username) {
            std::cout << "Username: " << users[i].getUsername() << std::endl;
            std::cout << "Password: " << users[i].getPassword() << std::endl;
            std::cout << "Is Admin: " << users[i].isAdminUser() << std::endl;
            std::cout << "Admins are 0, Users are 1" << std::endl;
            std::cout << std::endl;
            found = 1;
        }
    }
    if (!found) {
        std::cout << "The username " << username << " could not be found." << std::endl;
    }
}