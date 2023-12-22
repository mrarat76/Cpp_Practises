#include <iostream>
#include <string>
#include <vector>



class Employee{

public: 
std::string name;
std::string lastName;
double salary;


Employee(std::string fName, std:: string lName, double sal):
firstName(fName), lastName(lName), salary(sal) {}


virtual ~Employee() = {}







}

class Manager : public Employee{

    public:
    Manager(std::string fName, std:: string lName, double sal):
    firstName(fName), lastName(lName), salary(sal) {}

    salary=15000;

}

class Factory{
private:
std::vector<Employee*> employees;

public:
void addEmployee(Employee* employee){
    employees.push_back(employee);
}

void printEmployeeType(){


    for(auto& emp : employees){
        if(dynamic_cast<Manager*>(emp)!= nullptr){
            std::cout << "is a Manager" << std::endl;
        }
        else{
            std::cout << "Employee" << std::endl;
        }
    }
}

double calculateTotalSalary(){
    double totalSalary=0;
    for(auto& emp : employees){
        totalSalary += emp->salary;
    }
    return totalSalary;
}
void deleteManagers(){
    for(auto& emp : employees){
        if(dynamic_cast<Manager*>(emp)!= nullptr){
            delete emp;
        }
    }

};

~ Factory(){
    for(auto& emp : employees){
        delete emp;
    }
}

};

int main(){
    
        Factory factory;
        factory.addEmployee(new Employee("John", "Doe", 10000));
        factory.addEmployee(new Employee("Jane", "Doe", 10000));
        factory.addEmployee(new Manager("John", "Doe", 10000));
        factory.addEmployee(new Manager("Jane", "Doe", 10000));
    
        factory.printEmployeeType();
        std::cout << "Total Salary: " << factory.calculateTotalSalary() << std::endl;
        factory.deleteManagers();
        std::cout << "Total Salary: " << factory.calculateTotalSalary() << std::endl;
        factory.printEmployeeType();
    
        return 0;
}

