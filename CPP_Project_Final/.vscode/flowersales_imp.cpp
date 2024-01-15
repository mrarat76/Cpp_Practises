#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "flowessalse.hpp"
#include <sstream> 
 #include <algorithm> // Add the missing include directive



//enum FlowerType { ROSE, TULIP, LILY, DAISY, SUNFLOWER };
// add,delete ve update için admin ve user classlarını dahil et.
// manager için add,delete ve update yap.


// Global variables
Flower flowerDatabase[100];
int flowerCount = 0;

Flower* flowerorderdb = new Flower[MAX_FLOWERS]; // Assuming MAX_FLOWERS is the maximum number of flowers you want to store

int flowercount = 0;

// Function implementations
void initializeFlowerDatabase() {
    flowerCount = 0;
}
void initializeFlowerOrderDatabase() {
    flowercount = 0;
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
    int price;
    int typeAsInt;
    int stock;

    while (file >> flowerID >> name >> price >> typeAsInt >> stock) {
        FlowerType type = static_cast<FlowerType>(typeAsInt);
        flowerDatabase[flowerCount] = Flower(flowerID, name, price, type, stock);
        flowerCount++;
    }

     if (file.fail() && !file.eof()) {
        std::cout << "Dosya okuma hatası." << std::endl;
    }

    file.close();



    

    
}


void loadFlowerorderDataFromFile() {
    std::ifstream file("flowerorder.txt");

    if (!file.is_open()) {
        std::cerr << "Dosya açma hatası" << std::endl;
        return; // Exit the function without storing data if there's an error
    }

    int flowerID;
    std::string name;
    int price;
    int typeAsInt;
    int stock;

    while (file >> flowerID >> name >> price >> typeAsInt >> stock) {
        FlowerType type = static_cast<FlowerType>(typeAsInt);
        Flower flower(flowerID, name, price, type, stock);
        flowerorderdb[flowercount] = flower;
        flowercount++;
    }

    if (file.fail() && !file.eof()) {
        std::cerr << "Dosya okuma hatası." << std::endl;
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
        file << orders[i].getFlowerID() << " " << orders[i].getName() << " " << orders[i].getPrice() << " " <<static_cast<int> (orders[i].getType()) << " " << orders[i].getStock() << std::endl;
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
        file << flowerDatabase[i].getFlowerID() << " " << flowerDatabase[i].getName() << " " << flowerDatabase[i].getPrice() << " " << static_cast<int>(flowerDatabase[i].getType()) << " " << flowerDatabase[i].getStock() << std::endl;
    }
    /*for (int i = 0; i < flowerCount; i++) {
        file << flowerDatabase[i].getFlowerID() << " " << flowerDatabase[i].getName() << " " << flowerDatabase[i].getPrice() << " " << flowerDatabase[i].getType() << " " << flowerDatabase[i].getStock() << std::endl;
    }*/

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

bool initializeUsers(std::vector<UserBase>& users) {
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
        // Use the constructor to create a UserBase object and add it to the vector
        users.emplace_back(username, password, isAdmin);
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

void listUsers(const std::vector<UserBase>& users) {
    std::cout << "All users:" << std::endl;
    for (const UserBase& user : users) {
        std::cout << "Username: " << user.getUsername() << std::endl;
        std::cout << "Password: " << user.getPassword() << std::endl;
        std::cout << "Is Admin: " << user.isAdminUser() << std::endl;
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

void findUser(const std::vector<UserBase>& users, const std::string& username) {
    int found = 0;
    for (const UserBase& user : users) {
        if (user.getUsername() == username) {
            std::cout << "Username: " << user.getUsername() << std::endl;
            std::cout << "Password: " << user.getPassword() << std::endl;
            std::cout << "Is Admin: " << user.isAdminUser() << std::endl;
            std::cout << "Admins are 1, Users are 0" << std::endl;
            std::cout << std::endl;
            found = 1;
        }
    }
    if (!found) {
        std::cout << "The username " << username << " could not be found." << std::endl;
    }
}




void writeUserToTxtFile(const User& user) {
    std::ofstream file("user.txt");
    if (file.is_open()) {
        file << user.getUsername() << std::endl;
        file << user.getPassword() << std::endl;
        file.close();
        std::cout << "User information written to file: " << "user.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file: " << "user.txt" << std::endl;
    }
}

void readUserFromTxtFile(User& user) {
    std::ifstream file("user.txt");
    if (file.is_open()) {
        std::string username, password, isAdminStr;
        std::getline(file, username);
        std::getline(file, password);
        std::getline(file, isAdminStr);
        file.close();

        user.setUsername(username);
        user.setPassword(password);
        std::cout << "User information read from file: " << "user.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file: " << "user.txt" << std::endl;
    }
}
/*
void writeAdminToTxtFile(const admin& admin) {
    std::ofstream file("admin.txt");
    if (file.is_open()) {
        file << admin.getUsername() << std::endl;
        file << admin.getPassword() << std::endl;
        file.close();
        std::cout << "Admin information written to file: " << "admin.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file: " << "admin.txt" << std::endl;
    }
} */

/*void liststandartuser(const std::vector<User>& user) {
    std::cout << "All users:" << std::endl;
    for (const User& user : user) {
        
            std::cout << "Username: " << user.getUsername() << std::endl;
            std::cout << "Password: " << user.getPassword() << std::endl;
            std::cout << std::endl;
        
    }
}*/

void listadminuser(const std::vector<admin>& admins){
std::cout << "All admins:" << std::endl;
    for (const admin& admine : admins) {
        
            std::cout << "Username: " << admine.getUsername() << std::endl;
            std::cout << "Password: " << admine.getPassword() << std::endl;
            std::cout << std::endl;
        
    }
}

void readAdminFromTxtFile(admin& admin) {
    std::ifstream file("admin.txt");
    if (file.is_open()) {
        std::string username, password, isAdminStr;
        std::getline(file, username);
        std::getline(file, password);
        std::getline(file, isAdminStr);
        file.close();

        admin.setUsername(username);
        admin.setPassword(password);
        std::cout << "Admin information read from file: " << "admin.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file: " << "admin.txt" << std::endl;
    }
}
bool WriteAdminToTxtFile(const admin& adminc) {
    std::ofstream file("admin.txt");
    if (file.is_open()) {
        file << adminc.getUsername() << adminc.getPassword()<< std::endl;
        
        file.close();
        std::cout << "Admin information written to file: " << "admin.txt" << std::endl;
        return true;  // Başarılı oldu, true döndürüyoruz.
    } else {
        std::cerr << "Unable to open file: " << "admin.txt" << std::endl;
        return false; // Başarısız oldu, false döndürüyoruz.
    }
}

void addadmin (std::vector<admin>& admins, int* adminCount, const char* newUsername, const char* newPassword, int newUserIsAdmin) {
    if (*adminCount >= 100) {
        std::cout << "User limit exceeded. Cannot add more users." << std::endl;
        return;
    }

    // Add the new user directly to the vector and set its properties individually
    admins.emplace_back();
    admins.back().setUsername(newUsername);
    admins.back().setPassword(newPassword);
    admins.back().setAdminUser(newUserIsAdmin);
   

    (*adminCount)++;

    if (WriteAdminToTxtFile(admins.back())) {
        std::cout << "User has been successfully added." << std::endl;
    } else {
        std::cout << "User could not be added." << std::endl;
    }
}




void deleteadmin(std::vector<admin>& admins, int* adminCount, const char* deleteadUsername) {
    int found = 0;
    for (int i = 0; i < *adminCount; i++) {
        if (std::string(deleteadUsername) == admins[i].getUsername()) { // Kullanıcı adı karşılaştırması
            found = 1;
            for (int j = i; j < *adminCount - 1; j++) {
                // Kullanıcıları kaydır
                admins[j].setUsername(admins[j + 1].getUsername());
                admins[j].setPassword(admins[j + 1].getPassword());
                admins[j].setAdminUser(admins[j + 1].isAdminUser());
                
            }
            (*adminCount)--;

            if (WriteAdminToTxtFile(admins[i])) {
                std::cout << "User '" << deleteadUsername << "' has been successfully deleted." << std::endl;
            } else {
                std::cout << "User '" << deleteadUsername << "' could not be deleted." << std::endl;
            }
            break;
        }
    }

    if (!found) {
        std::cout << "User '" << deleteadUsername << "' not found." << std::endl;
    }
}

void updateAdmin(std::vector<admin>& admins, int adminCount, const char* usernameToUpdate, const char* newUsername, const char* newPassword, int newUserIsAdmin) {
    for (int i = 0; i < adminCount; i++) {
        if (std::string(usernameToUpdate) == admins[i].getUsername()) {
            // Kullanıcı adı eşleşti, bu kullanıcıyı güncelleyebiliriz.
            admins[i].setUsername(newUsername);
            admins[i].setPassword(newPassword);
            admins[i].setAdminUser(newUserIsAdmin);
           

            if (WriteAdminToTxtFile(admins[i])) {
                std::cout << "Admin '" << usernameToUpdate << "' has been successfully updated." << std::endl;
            } else {
                std::cout << "Admin '" << usernameToUpdate << "' could not be updated." << std::endl;
            }
            return; // Güncelleme işlemi tamamlandı, işlevi sonlandır
        }
    }

    // Eğer buraya kadar geldiysek, kullanıcı adı bulunamadı.
    std::cout << "Admin '" << usernameToUpdate << "' not found." << std::endl;
}



void addstandartuser(std::vector<User>& userse, int* userCount, const char* newUsername, const char* newPassword, int newUserIsAdmin) {
    if (*userCount >= 100) {
        std::cout << "User limit exceeded. Cannot add more users." << std::endl;
        return;
    }
    bool WriteUserToTxtFile(const User& user);

    // Add the new user directly to the vector and set its properties individually
    userse.emplace_back();
    userse.back().setUsername(newUsername);
    userse.back().setPassword(newPassword);
    userse.back().setAdminUser(newUserIsAdmin);
   

    (*userCount)++;

    if (WriteUserToTxtFile(userse.back())) {
        std::cout << "User has been successfully added." << std::endl;
    } else {
        std::cout << "User could not be added." << std::endl;
    }
}


bool WriteUserToTxtFile(const User& user) {
    std::ofstream file("user.txt");
    if (file.is_open()) {
        file << user.getUsername()  << std::endl;
        file  << std::endl;
        file.close();
        std::cout << "User information written to file: " << "user.txt" << std::endl;
        return true;  // Başarılı oldu, true döndürüyoruz.
    } else {
        std::cerr << "Unable to open file: " << "user.txt" << std::endl;
        return false; // Başarısız oldu, false döndürüyoruz.
    }
}


void deletestandartuser(std::vector<User>& users, int* userCount, const char* deleteUsername) {
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

            if (WriteUserToTxtFile(users[i])) {
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



void updatestandartuser(std::vector<User>& users, int userCount, const char* usernameToUpdate, const char* newUsername, const char* newPassword, int newUserIsAdmin) {
    for (int i = 0; i < userCount; i++) {
        if (std::string(usernameToUpdate) == users[i].getUsername()) {
            // Kullanıcı adı eşleşti, bu kullanıcıyı güncelleyebiliriz.
            users[i].setUsername(newUsername);
            users[i].setPassword(newPassword);
            users[i].setAdminUser(newUserIsAdmin);
           

            if (WriteUserToTxtFile(users[i])) {
                std::cout << "User '" << usernameToUpdate << "' has been successfully updated." << std::endl;
            } else {
                std::cout << "User '" << usernameToUpdate << "' could not be updated." << std::endl;
            }
            return; // Güncelleme işlemi tamamlandı, işlevi sonlandır
        }
    }

    // Eğer buraya kadar geldiysek, kullanıcı adı bulunamadı.
    std::cout << "User '" << usernameToUpdate << "' not found." << std::endl;
}



void liststandartuser(const std::vector<User>& users) {
    std::cout << "All users:" << std::endl;
    for (const User& user : users) {
        
            std::cout << "Username: " << user.getUsername() << std::endl;
            std::cout << "Password: " << user.getPassword() << std::endl;
            std::cout << std::endl;
        
    }
}





void deleteuser(std::vector<UserBase>& users, int* userCount, const char* deleteUsername,std::vector<admin>& admins, int adminCount, std::vector<User>& userss, int usercount) {
    int found = 0;
    int isAdminUser ;
    for (int i = 0; i < *userCount; i++) {
        if (std::string(deleteUsername) == users[i].getUsername()) { // Kullanıcı adı karşılaştırması
            found = 1;
            isAdminUser = users[i].isAdminUser(); // Kullanıcının admin durumunu al
            for (int j = i; j < *userCount - 1; j++) {
                // Kullanıcıları kaydır
                users[j].setUsername(users[j + 1].getUsername());
                users[j].setPassword(users[j + 1].getPassword());
                users[j].setAdminUser(users[j + 1].isAdminUser());
            }
            (*userCount)--;

              if (isAdminUser == 0) {
                deletestandartuser(userss, userCount, deleteUsername); // Standart kullanıcıyı sil
            } else if (isAdminUser == 1) {
                deleteadmin(admins, &adminCount, deleteUsername); // Admin kullanıcısını sil  /// ana metoda parametre eklenecek.
            }
           

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


void deleteUser(std::vector<UserBase>& users, int* userCount, const char* deleteUsername,std::vector<admin>& admins, int adminCount, std::vector<User>& userss, int usercount){
    int found = 0;
    int isadminUser ;
    
    
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getUsername() == deleteUsername) {
            found = 1;
           isadminUser= it->isAdminUser();
            users.erase(it);
            break;
            (*userCount)--;
        }
    }

    
              if (isadminUser == 0) {
                deletestandartuser(userss, userCount, deleteUsername); // Standart kullanıcıyı sil
            } else if (isadminUser == 1) {
                deleteadmin(admins, &adminCount, deleteUsername); // Admin kullanıcısını sil  /// ana metoda parametre eklenecek.
            }
           
             writeUsersToFile(users);
           
            if (writeUsersToFile(users)) {
                std::cout << "User '" << deleteUsername << "' has been successfully deleted." << std::endl;
            } else {
                std::cout << "User '" << deleteUsername << "' could not be deleted." << std::endl;
            }
            
    
    if (found==0) {
        std::cout << "User '" << deleteUsername << "' not found." << std::endl;
    }
    
    
    
    
    }


/*
void deleteuSer(std::vector<UserBase>& users, int* userCount, const char* deleteUsername, std::vector<admin>& admins, int adminCount, std::vector<User>& userss, int usercount) {
    int found = 0;
    int isAdminUser;

    for (int i = 0; i < *userCount; i++) {
        if (deleteUsername == users[i].getUsername()) { // Kullanıcı adı karşılaştırması
            found = 1;
            isAdminUser = users[i].isAdminUser(); // Kullanıcının admin durumunu al

            users.erase(users.begin() + i); // Kullanıcıyı vektörden sil

            (*userCount)--;

            if (isAdminUser == 0) {
                deletestandartuser(userss, userCount, deleteUsername); // Standart kullanıcıyı sil
            } else if (isAdminUser == 1) {
                deleteadmin(admins, &adminCount, deleteUsername); // Admin kullanıcısını sil
            }
            writeUsersToFile(users);
            if (writeUsersToFile(users)) {
                std::cout << "User '" << deleteUsername << "' has been successfully deleted." << std::endl;
            } else {
                std::cout << "User '" << deleteUsername << "' could not be deleted." << std::endl;
            }
            break;
        }
    }
}*/ 






void adduser(std::vector<UserBase>& users, int* userCount, const char* newUsername, const char* newPassword, int newUserIsAdmin,std::vector<admin>& admins, int adminCount, std::vector<User>& userss, int usercount ) {
    if (*userCount >= 100) {
        std::cout << "User limit exceeded. Cannot add more users." << std::endl;
        return;
    }

    // Add the new user directly to the vector and set its properties individually
    users.emplace_back();
    users.back().setUsername(newUsername);
    users.back().setPassword(newPassword);
    users.back().setAdminUser(newUserIsAdmin);

    

if (newUserIsAdmin == 0){
   addstandartuser(userss, &usercount, newUsername, newPassword, newUserIsAdmin);
} else if (newUserIsAdmin == 1) {
    
     addadmin(admins, &adminCount, newUsername, newPassword, newUserIsAdmin); //ana metoda parametre eklenecek.
}


    if (writeUsersToFile(users)) {
        std::cout << "User has been successfully added." << std::endl;
    } else {
        std::cout << "User could not be added." << std::endl;
    }
}


void updateuser(std::vector<UserBase>& users, int userCount, const char* usernameToUpdate, const char* newUsername, const char* newPassword, int newUserIsAdmin, std::vector<admin>& admins, int adminCount, std::vector<User>& userss, int usercount) {
    int found = 0;
    int isAdminUser = -1; // -1: Bulunamadı, 0: Standart kullanıcı, 1: Admin kullanıcı

    for (int i = 0; i < userCount; i++) {
        if (std::string(usernameToUpdate) == users[i].getUsername()) { // Kullanıcı adı karşılaştırması
            found = 1;
            isAdminUser = users[i].isAdminUser(); // Kullanıcının admin durumunu al

            // Kullanıcının bilgilerini güncelle
            users[i].setUsername(newUsername);
            users[i].setPassword(newPassword);
            users[i].setAdminUser(newUserIsAdmin);

            if (isAdminUser == 0) {
                // Eğer kullanıcı bir standart kullanıcıysa, standart kullanıcı işlemini çağır
                updatestandartuser(userss, usercount, usernameToUpdate, newUsername, newPassword, newUserIsAdmin);
            } else if (isAdminUser == 1) {
                // Eğer kullanıcı bir admin kullanıcısıysa, admin işlemini çağır
                updateAdmin(admins, adminCount, usernameToUpdate, newUsername, newPassword, newUserIsAdmin);
            }

            if (writeUsersToFile(users)) {
                std::cout << "User '" << usernameToUpdate << "' has been successfully updated." << std::endl;
            } else {
                std::cout << "User '" << usernameToUpdate << "' could not be updated." << std::endl;
            }
            break;
        }
    }

    if (!found) {
        std::cout << "User '" << usernameToUpdate << "' not found." << std::endl;
    }
}