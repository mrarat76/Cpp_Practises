#include <string>
#ifndef FLOWER_SALES_H
#define FLOWER_SALES_H
#define MAX_FLOWERS 100

// Define an enum
enum class FlowerType {
    ROSE,
    TULIP,
    LILY,
    DAISY,
    SUNFLOWER
};

class UserBase {
public:
    UserBase(const std::string& username, const std::string& password, bool isAdmin)
        : username(username), password(password), isAdmin(isAdmin) {}

    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    bool isAdminUser() const { return isAdmin; }
     // Getter metotları
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    bool isAdminUser() const { return isAdmin; }

    // Setter metotları
    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setPassword(const std::string& newPassword) { password = newPassword; }
    void setAdminUser(bool newAdminStatus) { isAdmin = newAdminStatus; }


private:
    std::string username;
    std::string password;
    bool isAdmin;
};

class User : public UserBase {
public:
    User(const std::string& username, const std::string& password, bool isAdmin)
        : UserBase(username, password, isAdmin) {}
};

class admin : public UserBase {
public:
    admin(const std::string& username, const std::string& password, bool isAdmin)
        : UserBase(username, password, isAdmin) {}
};

// Define classes
class Flower {
public:
    Flower() : flowerID(0), name(""), price(0.0f), type(FlowerType::ROSE), stock(0) {}
    Flower(int flowerID, const std::string& name, float price, FlowerType type, int stock)
        : flowerID(flowerID), name(name), price(price), type(type), stock(stock) {}

    int getFlowerID() const { return flowerID; }
    std::string getName() const { return name; }
    float getPrice() const { return price; }
    FlowerType getType() const { return type; }
    int getStock() const { return stock; }

    void setFlowerID(int newFlowerID) { flowerID = newFlowerID; }
    void setName(const std::string& newName) { name = newName; }
    void setPrice(float newPrice) { price = newPrice; }
    void setType(FlowerType newType) { type = newType; }
    void setStock(int newStock) { stock = newStock; }

private:
    int flowerID;
    std::string name;
    float price;
    FlowerType type;
    int stock;
};

Flower* flowerorderdb = nullptr;
int flowerCount = 0;
int flowercount = 0;

#endif
