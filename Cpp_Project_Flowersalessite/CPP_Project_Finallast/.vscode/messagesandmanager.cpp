#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Include for calloc and malloc
#include <fstream> // Include for ifstream
#include <sstream> // Include the necessary header file for std::istringstream


// Define macros for memory allocation and deallocation
#define ALLOC(type, count) static_cast<type*>(std::calloc(count, sizeof(type)))
#define ALLOC_ARRAY(type, count) static_cast<type**>(std::calloc(count, sizeof(type*)))
#define FREE(ptr) std::free(ptr)

// Message base struct
struct Message {
    std::string messageText;

    // Virtual function for polymorphism
    virtual std::string getType() const { return "Message"; }

    // Virtual destructor for proper cleanup
    virtual ~Message() {}
};

// Manager struct
struct Manager {
    std::string username;
    std::string password;
    Message*** messages; // Triple pointer to an array of pointers to pointers to messages
    int messageCount;    // Number of messages

    Manager(const std::string& uname) : username(uname), messages(nullptr), messageCount(0) {}
    Manager() : username(""), messages(nullptr), messageCount(0) {}


    // Method to write and store a message
    void writeMessage(const std::string& text) {
        Message* newMessage = ALLOC(Message, 1); // Dynamic allocation using the ALLOC macro
        newMessage->messageText = text;

        // Allocate memory for the array of pointers to pointers to messages
        if (messages == nullptr) {
            messages = ALLOC_ARRAY(Message*, 1); // Dynamic allocation using the ALLOC_ARRAY macro
        } else {
            // Resize the array of pointers to pointers to messages
            Message*** newMessages = ALLOC_ARRAY(Message*, messageCount + 1);
            for (int i = 0; i < messageCount; ++i) {
                newMessages[i] = messages[i];
            }
            FREE(messages); // Deallocate the old array using the FREE macro
            messages = newMessages;
        }

        // Allocate memory for the pointer to the new message
        messages[messageCount] = ALLOC(Message*, 1);
        *(messages[messageCount]) = newMessage;
        ++messageCount;
        
    }

    // Method to list all messages
    void listMessages() const {
        std::cout << "Messages by " << username << ":" << std::endl;
        for (int i = 0; i < messageCount; ++i) {
            std::cout << "Message " << i + 1 << ": " << (*(messages[i]))->getType() << ": " << (*(messages[i]))->messageText << std::endl;
        }
    }
    void readmessages() {
    for (int i = 0; i < messageCount; ++i) {
        Message* message = *(messages[i]);
        std::string messageText = message->messageText;
        // Now, you can use 'messageText' to access the text of the message.
        std::cout << "Message " << i + 1 << ": " << messageText << std::endl;
    }
   
}
   friend void showtotalarr(const Manager& manager) {
        std::cout << "Total message count: " << manager.messageCount << std::endl;
    }

    // Destructor to free memory
    ~Manager() {
        for (int i = 0; i < messageCount; ++i) {
            FREE(*(messages[i])); // Free individual message objects using the FREE macro
            FREE(messages[i]); // Free pointers to message objects using the FREE macro
        }
        FREE(messages); // Free the array of pointers to pointers using the FREE macro
    }
};

// Customized message type struct
struct RegisterMessage : Message {
    std::string type;

    RegisterMessage(const std::string& t) : type(t) {}
    RegisterMessage() : type("") {}

    std::string getType() const override {
        return "RegisterMessage (" + type + ")";
    }
};


/*std::vector<Manager> readManagersFromFile(const std::string& filename = "managers.txt") {
    std::vector<Manager> managers; // Vector to store the managers read from the file
    #include <fstream> // Include the necessary header file for ifstream

    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            // Assuming each line in the file contains a username
            Manager manager(line);
            managers.push_back(manager);
        }

        file.close();
    } else {
        std::cerr << "Unable to open the file: " << filename << std::endl;
    }

    return managers;
}*/
void readmanagersfromfile(std::vector<Manager>& managers, const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;


        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string username, password;

            // Assuming each line contains a username and a password separated by a space
            if (iss >> username >> password) {
                Manager manager(username);
                manager.password = password;
                managers.push_back(manager);
            } else {
                std::cerr << "Invalid line format in file: " << filename << std::endl;
            }
        }

        file.close();
    } else {
        std::cerr << "Unable to open the file: " << filename << std::endl;
    }
}
/*
void readmanagersfromfile(std::vector<Manager>& managers, const std::string& filename ) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            // Assuming each line in the file contains a username
            Manager manager(line);
            managers.push_back(manager);
        }

        file.close();
    } else {
        std::cerr << "Unable to open the file: " << filename << std::endl;
    }
}*/






/*void addToMessageArray(const std::string& messageType, std::vector<RegisterMessage>& messageArray) {
   RegisterMessage newMessage(messageType);
    messageArray.emplace_back(newMessage);
    messageArray.back().messageText = "This is a message of type " + messageType;
   
}*/
void addToMessageArray(const std::string& messageType, std::vector<RegisterMessage>& messageArray) {
    RegisterMessage newMessage(messageType);
    newMessage.messageText = "This is a message of type " + messageType;
    messageArray.push_back(newMessage);
}


void writemessagestotxt(std::vector<RegisterMessage>& messahearray){
    std::ofstream file("messages.txt");

    if (file.is_open()) {
        for (const RegisterMessage& message : messahearray) {
            file << message.getType() << std::endl;
        }

        file.close();
    } else {
        std::cerr << "Unable to open the file: " << "messages.txt" << std::endl;
    }
}
void readmessagesfromtxt(std::vector<RegisterMessage>& messahearray){
    std::ifstream file("messages.txt");

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            // Assuming each line in the file contains a username
            RegisterMessage message(line);
            messahearray.push_back(message);
        }

        file.close();
    } else {
        std::cerr << "Unable to open the file: " << "messages.txt" << std::endl;
    }
}
void readregistermessages(std::vector<RegisterMessage>& messageArray) {
    for(const RegisterMessage& message : messageArray) {
        std::cout << message.getType() << std::endl;
    }

}
void initializeregistremessagesfromtxt (std::vector<RegisterMessage>& messageArray){
    readmessagesfromtxt(messageArray);
}


void writemanagerstofile(const std::vector<Manager>& managers, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const Manager& manager : managers) {
            file << manager.username << " " << manager.password << std::endl;
        }

        file.close();
    } else {
        std::cerr << "Unable to open the file: " << filename << std::endl;
    }
}

void addmanager(std::vector<Manager>& managers, const std::string& username, const std::string& password) {
    Manager manager(username);
    manager.password = password;
    managers.push_back(manager);
    writemanagerstofile(managers, "managers.txt");
}

void deletemanager(std::vector<Manager>& managers, const std::string& username) {
    for (int i = 0; i < managers.size(); ++i) {
        if (managers[i].username == username) {
            managers.erase(managers.begin() + i);
            break;
        }
    }
    writemanagerstofile(managers, "managers.txt");
}

void listmanagers(const std::vector<Manager>& managers) {
    std::cout << "Managers:" << std::endl;
    for (const Manager& manager : managers) {
        std::cout << manager.username << std::endl;
    }
}

void updatemanager(std::vector<Manager>& managers, const std::string& username, const std::string& password) {
    for (Manager& manager : managers) {
        if (manager.username == username) {
            manager.password = password;
            break;
        }
    }
    writemanagerstofile(managers, "managers.txt");
}



void findmanager(const std::vector<Manager>& managers, const std::string& username) {
    for (const Manager& manager : managers) {
        if (manager.username == username) {
            std::cout << "Manager found: " << manager.username << " " << manager.password << std::endl;
            return;
        }
    }

    std::cout << "Manager not found." << std::endl;
}

