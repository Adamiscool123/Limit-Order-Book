#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream> // For I/O streams objects
#include <mutex> // To ensure that only one thread can access a shared resource at a time
#include <netinet/in.h>
#include <queue> // For push , pop , empty , and front
#include <string>
#include <sys/socket.h> // For sockets
#include <thread>       // For multitasking/multithreading
#include <unistd.h>     // Sleep function
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>

struct account{
    std::string firstname;
    std::string lastname;
    std::string username;
    std::string password;
};

class account_set_up{
    public:
        int check(void){
            int choice;
            
            std::cout << "1. Create Account" << std::endl << "2. Login" << std::endl << "3. Exit" << std::endl << "Enter choice: ";
            std::cin >> choice;

            return choice;
        }
        void create_account(account a){
            std::cout << "First Name: ";

            std::cin >> a.firstname;

            std::cout << std::endl << "Last Name: ";

            std::cin >> a.lastname;

            std::cout << std::endl << "Username: ";

            std::cin >> a.username;

            std::cout << std::endl << "Password: ";

            std::cin >> a.password;
        }
        void login(void){

        }
};

int main(void) {
  int port = 8080; 

  account_set_up start;

  account a;

  while(true){
    int choice = start.check();

    if(choice == 1){
        start.create_account(a);
    }
    else if(choice == 2){
        start.login();
    }
    else{
        break;
    }
  }

  return 0;
}