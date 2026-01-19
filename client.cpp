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
#include <memory>  // For std::shared_ptr
#include <string>  // For std::string
#include <vector>  // For std::vector
#include "ftxui/component/component.hpp"       // For components
#include "ftxui/component/component_options.hpp" // For InputOption
#include "ftxui/component/screen_interactive.hpp" // For screen
#include "ftxui/dom/elements.hpp"  // For styling (border, color)

using namespace ftxui;

struct account{
    uint8_t msg_type = 1;    // ID 1 = Create Account
    
    char firstname[32];      // Fixed buffer (not std::string)
    char lastname[32];
    char username[32];
    char password[32];
    
    int32_t trade_size;      // 32-bit int
    int64_t funding;         // 64-bit int (Money needs big numbers)
    int32_t account_type;    // 1=Retail, 2=Hedge Fund
};

class account_set_up{
    public:
        int check(void){
            system("clear");

            int choice;
            
            std::cout << "1. Create Account" << std::endl << "2. Login" << std::endl << "3. Exit" << std::endl << "Enter choice: ";
            std::cin >> choice;

            return choice;
        }
        void create_account(account a){
            system("clear");

            // 1. STATE VARIABLES (Where user data is stored)
            std::string username;
            std::string password;
            std::string full_name;
            std::string deposit;
            
            // Options for Account Type
            std::vector<std::string> tier_options = {
                "Retail (Standard)", 
                "Institutional (Hedge Fund - Low Latency)"
            };
            int tier_selected = 0;

            // Options for Leverage
            std::vector<std::string> leverage_options = {
                "1:1 (Cash Account)", 
                "1:4 (Margin Account)",
                "1:10 (High Risk)"
            };
            int leverage_selected = 0;

            // 2. DEFINE COMPONENTS
            
            // Input Fields
            Component input_name = Input(&full_name, "Enter Full Name");

            Component input_username = Input(&username, "Enter Username");
            
            // Password Field (Masked with *)
            InputOption password_option;
            password_option.password = true;
            Component input_password = Input(&password, "Enter Password", password_option);
            
            Component input_deposit = Input(&deposit, "$10,000 min");

            // Radio Buttons
            Component radio_tier = Radiobox(&tier_options, &tier_selected);
            Component radio_leverage = Radiobox(&leverage_options, &leverage_selected);

            auto screen = ScreenInteractive::TerminalOutput();

            // Submit Button
            Component button_submit = Button("SUBMIT APPLICATION", [&] {
                // This runs when clicked/pressed
                // TODO: Send Struct to Server here
                screen.Exit();
            });

            // 3. LAYOUT CONTAINER (Holds all logic components)
            auto form_container = Container::Vertical({
                input_name,
                input_username,
                input_password,
                input_deposit,
                radio_tier,
                radio_leverage,
                button_submit,
            });

            // 4. THE RENDERER (How it LOOKS)
            auto renderer = Renderer(form_container, [&] {
                return vbox({
                    // TITLE HEADER
                    vbox({
                        text("Application Form") | bold | center,
                        separator(),
                    }) | border,

                    text(""), // Spacer

                    // FORM SECTION
                    window(text(" 1. NEW PORTFOLIO "), vbox({
                        hbox(text(" Full Name:  ") | size(WIDTH, EQUAL, 15), input_name->Render()),
                        hbox(text(" Username:   ") | size(WIDTH, EQUAL, 15), input_username->Render()),
                        hbox(text(" Password:   ") | size(WIDTH, EQUAL, 15), input_password->Render()),
                    })),

                    text(""), // Spacer

                    // FINANCIALS SECTION
                    window(text(" 2. FINANCIAL CONFIGURATION "), vbox({
                        hbox(text(" Deposit:    ") | size(WIDTH, EQUAL, 15), input_deposit->Render()),
                        separator(),
                        text(" Account Tier:") | bold,
                        radio_tier->Render() | flex,
                        text(""),
                        text(" Leverage:") | bold,
                        radio_leverage->Render() | flex,
                    })),

                    text(""), // Spacer

                    // SUBMIT BUTTON
                    button_submit->Render() | center | borderDouble | color(Color::Green),

                }) | border | center; // Center everything on screen
            });

            screen.Loop(renderer);
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