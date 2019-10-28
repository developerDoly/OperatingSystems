#include <sys/stat.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
//#include <io.h>
//#include "./Blowfish-master/blowfish.h"



long GetFileSize(std::string filename);
int processChunk(std::vector<char> buffer, int bufferSize);
std::string convertToString(char* a, int size);

long GetFileSize(std::string filename){
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int main(){
    char inputFile[] = "./200MB.zip";
    char outputFile[] = "./new.txt";
    
	long sizeOfFile = GetFileSize(inputFile);
    std::cout << "file size in bytes: " << sizeOfFile << "\n";
	int bufferSize = 4096;
	
	int numBuffers = (int) sizeOfFile/bufferSize;//numBuffer will always be an integer
	int remainingBytesInFile = (int) sizeOfFile%bufferSize;
	
	std::cout << "numBuffers: " << numBuffers << "\n";
	std::cout << "remainingBytesInFile: " << remainingBytesInFile << "\n";
	
    std::ifstream fin(inputFile, std::ios::in | std::ios::binary);
	std::vector<char> buffer (bufferSize, 0);
    std::ofstream output(outputFile, std::ios::out | std::ios::binary);
	
	for(int i = 0; (i < numBuffers) && (fin.good()); i++){
		fin.read(buffer.data(), buffer.size());
		if (output.is_open() && fin.good()){
			processChunk(buffer, bufferSize);
           // output << buffer.data();
           // std::cout << i << "\n";
            output.write(buffer.data(), sizeof(char) * bufferSize);
		}
	}
    if(fin.good()){
        std::vector<char> lastBuffer (remainingBytesInFile, 0);
        fin.read(lastBuffer.data(), remainingBytesInFile);
        processChunk(lastBuffer, remainingBytesInFile);
        //output << lastBuffer.data();
        //std::cout << "in if of for loop: " << "\n";
        output.write(lastBuffer.data(), sizeof(char) * remainingBytesInFile);
    }
	fin.close();
	output.close();
}

int processChunk(std::vector<char> buffer, int bufferSize){
    
	int someMultipleOfEight = 24;
    std::vector<char> key;
	for (int i = 0; i < someMultipleOfEight; i++) {
		key.push_back(i);
	}

	//makeing the blowfish with the made key
	//Blowfish blowfish(key);//pass in vector<char> whose length is a multple of 8
	
	//send(blowfish.Encrypt(buffer).data());//blowfish.Encrypt(buffer) returns a vector<char>
}

std::string convertToString(char* a, int size) {
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 
