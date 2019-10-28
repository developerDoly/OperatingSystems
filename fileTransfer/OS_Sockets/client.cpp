#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <std::string.h>
#include <std::string>

class Client{

    //default constructor
    Client(char[] name, char[] ipAddress, int port) {
        std::string c_name = name;



        std::cout << "Client " << c_name << " has been created.\n";
    }
    
	
    ~Client(){
        std::cout << "Client " << c_name << " has been destroyed.\n";
    }

    int createSocket(char[] ipAddress, int port) {
        // Create a socket
        int listening = socket(AF_INET, SOCK_STREAM, 0);
        if (listening == -1) {
            cerr << "Can't create a socket! Quitting" << endl;
            return -1;
        }

        //	Create a hint structure for the server we're connecting with
        int port = 9800;
        std::string ipAddress = "10.35.195.46";

        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

        //	Connect to the server on the socket
        int connectRes = connect(sock, (sockaddr * ) & hint, sizeof(hint));
        if (connectRes == -1) {
            return 1;
        }
    }
    
    int sendStuff(){
        char buf[4096];
        std::string userInput;

        //		Enter lines of text
        std::cout << "> ";
        getline(std::cin, userInput);

        //		Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
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
        int bytesReceived = recv(sock, buf, 4096, 0);
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
    
    int closeSocket(){
        close(sock);
        
        return 0;
    }

};

void readInFile(){
	ifstream is("./../../../../../../../../../../../../tmp/1G");
	
	char buf[4096];
	do {
		is.read(buf, sizeof(buf));
		process_chunk(buf, is.gcount());
	}while(is);
	
}
