#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

//
// Created by Doly Rakotomaheninna on 10/22/19.
//

//This is acting as a server.

//has master key for UserA and another master key for UserB



//gets request from UserA

//sends back a message to UserA that is encrypted using UserA's master key
//The message also contains the same request that UserA sent to the KDC as well as the session key and the N1
//Also an encrypted ticket that is secured using UserB's master key. This ticket contains the session key and the id of UserA
//E(K_A, K_S | Request | N_1 | E(K_B, K_s | "UserA"))

//go to UserA

char* ipAddressOfThing0 = "10.35.195.46";



//int main(){
 //   Server kdc = new Server();
//}



////////////////////////////////////////////////////////////////////////////////
//below is just for testing

int main(){
	std::string ipAddress0 = "10.35.195.46";
	std::string ipAddress1 = "10.35.195.47";
	std::string ipAddress2 = "10.35.195.22";
	
	int port = 9800;
	
	FileReader fileReader = new FileReader("test.txt", "output.txt");
	
	std::string textToBeSent = fileReader.processFile();
	
	Connection connection = new Connection("Thing1", "10.35.195.47", port);
	
	connection.createSocket("10.35.195.46", port);
	
	connection.sendStuff(textToBeSent);
	
	
}