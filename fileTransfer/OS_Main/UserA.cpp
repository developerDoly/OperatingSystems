//
// Created by Doly Rakotomaheninna on 10/23/19.
//

//This is acting as a client.

//has master key for UserA

//step one, UserA sends a request to KDC  for a session key to communicate with UserB along with a Nonce N1
//RequestN1

//go to KDC

//UserA gets this reponse from the KDC: E(K_A, K_S | Request | N_1 | E(K_B, K_s | "UserA"))

//UserA decrypts it using UserA's master key to get session key

//compare the Request and N_1 to make sure they are the same, so that you know the session key is fresh

//Sends to UserB: E(K_B, K_s | "UserA")

//Go to UserB

//receives message from UserB
//E(K_S, N_2 | "UserB")

//UserA decrypts message and applies function on N_2, such as adding a random string, and this function is previously agreed upon
//UserA then sends this message to UserB
//E(K_S, f(N_2)), this proves to UserB that UserA is UserA




////////////////////////////////////////////////////////////////////////////////
//below is just for testing
#include <iostream>
#include <string.h>
#include "../OS_Blowfish/blowfish.h"
#include "../OS_Utilities/FileReader.cpp"
#include "../OS_Sockets/connection.cpp"

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


















