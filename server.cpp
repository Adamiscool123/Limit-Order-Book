#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream> // For I/O streams objects
#include <map>
#include <mutex> // To ensure that only one thread can access a shared resource at a time
#include <netinet/in.h>
#include <queue> // For push , pop , empty , and front
#include <sstream>
#include <string>
#include <sys/socket.h> // For sockets
#include <thread>       // For multitasking/multithreading
#include <unistd.h>     // Sleep function

void handle_client(){
    
}

void server(int port){

  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  // Specify the address
  sockaddr_in serverAddress;

  // Assign protocol to IPv4
  serverAddress.sin_family = AF_INET;

  // htons = Host to Network Short: Takes in port number and converts it to
  // standardized network format so router can understand
  serverAddress.sin_port = htons(port);

  // Final step for configuring serverAddress: Tells OS which IP address the
  // server should listen to

  // INADDR_ANY: Uses port 0.0.0.0 or in other words "Listen on all available
  // network interfaces" so no need to specify actual IP address Basically can
  // take in connections from any IP address
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // System call that assigns server address with server socket
  // bind(serverSocket, serverAddress, serverAddress length)
  int value = bind(serverSocket, (struct sockaddr *)&serverAddress,
                   sizeof(serverAddress));

  if (value < 0) {
    std::cout << "Binding failed" << std::endl;
    return;
  }

  // Listen to the socket: 5 is the queue for amount of connections waiting to
  // be accepted
  listen(serverSocket, 5);

  std::cout << "Server Listening on port " << port << std::endl;

  while (true) {
    // Accept connection request:

    // accept(serverSocket, clientAddressPointer, clientAddressLengthPointer)
    // The nullptr are placeholders
    int newSocket = accept(serverSocket, nullptr, nullptr);

    if (newSocket < 0) {
      // Handle error
      continue;
    }

    std::thread(handle_client, newSocket).detach();
  
  }

  // Close socket
  close(serverSocket);
}

int main(void){
    std::cout << "Starting Server" << std::endl;

    int PORT = 8080;

    server(PORT);

    return 0;
}