#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

 Connection(char* name, char* ipAddress, int port);
  int setReceiver(std::string ipAddress);
  int createSocket(char* ipAddress, int port);
  int closeSocket();
  int listenToMessage();
  int sendStuff(std::string message);
  int waitForResponse();
  
//
class Connection {
	sockaddr_in hint;
	int listening;
	int clientSocket;
	
    char[] c_name;
    int c_port;
    char[] c_ipAddress;
    
    char[] r_ipAddress;
    
    //default constructor for Server or Client
    //type is "Server" or "Client"
    Connection(char* name, char* ipAddress, int port){
        c_name = name;
        c_port = port;
        c_ipAddress = ipAddress;
        
        std::cout c_name << " has been created.\n";
    }
    

    //ipAddress belongs to the server you are trying to connect to
    int setReceiver(std::string ipAddress){
        r_ipAddress = ipAddress;
    }
    
    int createSocket(char* ipAddress, int port) {
        // Create a socket
        listening = socket(AF_INET, SOCK_STREAM, 0);
        if (listening == -1) {
            std::cout << "Can't create a socket! Quitting\n";
            return -1;
        }
        
        // Bind the ip address and port to a socket
        hint.sin_family = AF_INET;
        hint.sin_port = htons(c_port);
        inet_pton(AF_INET, ipAddress, &hint.sin_addr);
        
        bind(listening, (sockaddr * ) & hint, sizeof(hint));
        
        // Tell Winsock the socket is for listening
        listen(listening, SOMAXCONN);
        // Wait for a connection
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);
        
        clientSocket = accept(listening, (sockaddr * ) & client, &clientSize);
        
        char host[NI_MAXHOST];      // Client's remote name
        char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
        
        memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
        memset(service, 0, NI_MAXSERV);
        
        if (getnameinfo((sockaddr * ) & client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
            cout << host << " connected on port " << service << endl;
        } else {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            cout << host << " connected on port " << ntohs(client.sin_port) << endl;
        }
		
        return 0;
    }
	
	int closeSocket(){
		close(listening);
	}
    
    int listenToMessage(){
        char buf[4096];
        
        memset(buf, 0, 4096);
        
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1) {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
        
        if (bytesReceived == 0) {
            cout << "Client disconnected " << endl;
            break;
        }
        
        cout << string(buf, 0, bytesReceived) << endl;
        
        // Echo message back to client
        send(clientSocket, buf, bytesReceived + 1, 0);
        
        // Close the socket
        close(clientSocket);
        
        return 0;
    }
	
	 int sendStuff(std::string message){

        //		Send to server
        int sendRes = send(clientSocket, message.c_str(), message.size() + 1, 0);
        if (sendRes == -1)
        {
            std::cout << "Could not send to server! Whoops!\r\n";
            continue;
        }
        
        return 0;
    }
    
    
    int waitForResponse(){
        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
        }
        return 0;
    }
};

