#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Include for calloc and malloc
#include <fstream> // Include for ifstream

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

    std::string getType() const override {
        return "RegisterMessage (" + type + ")";
    }
};


std::vector<Manager> readManagersFromFile(const std::string& filename = "managers.txt") {
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
}


int main() {
    Manager manager("JohnDoe");

    manager.writeMessage("Hello, everyone!");
    manager.writeMessage("I have an important announcement.");
    manager.writeMessage("Have a great day!");

    RegisterMessage registerMsg("New User Registration");
    manager.writeMessage("Welcome to our platform!");
    *(manager.messages[3]) = &registerMsg; // Add a custom message type using a double pointer

    manager.listMessages();

    return 0;
}




