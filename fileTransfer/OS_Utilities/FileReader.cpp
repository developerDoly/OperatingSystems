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
#include "../OS_Blowfish/blowfish.h"

long GetFileSize(std::string filename);
int processChunk(std::vector<char> buffer, int bufferSize);
std::string convertToString(char* a, int size);
int processFile();
int send(char* message);
//FileReader(char* inputFileName, char* outputFileName);
//~FileReader();

class FileProcessor {
    long sizeOfFile;
    int bufferSize = 2048;
    char inputFile[];
    char outputFile[];
    
    
    int numBuffers;
    int remainingBytesInFile;
    
    
    FileReader(char* inputFileName, char* outputFileName){
		strcpy(inputFile, inputFileName);
		strcpy(outputFile, outputFileName);
		
        sizeOfFile = GetFileSize(inputFile);
        std::cout << "file size in bytes: " << sizeOfFile << "\n";
        
        numBuffers = (int) sizeOfFile/bufferSize;//numBuffer will always be an integer
        remainingBytesInFile = (int) sizeOfFile%bufferSize;
        std::cout << "numBuffers: " << numBuffers << "\n";
        std::cout << "remainingBytesInFile: " << remainingBytesInFile << "\n";
        
        
    }
    
  
    long GetFileSize(std::string filename){
        struct stat stat_buf;
        int rc = stat(filename.c_str(), &stat_buf);
        return rc == 0 ? stat_buf.st_size : -1;
    }
    
    //change processChunk to change what to do with the pieces of the file
    std::string processFile(){
		std::string text;
        
        std::ifstream fin(inputFile, std::ios::in | std::ios::binary);
        std::vector<char> buffer (bufferSize, 0);
        //std::ofstream output(outputFile, std::ios::out | std::ios::binary);//used for writing out to a file
        
        for(int i = 0; (i < numBuffers) && (fin.good()); i++){
            fin.read(buffer.data(), buffer.size());
            //if (output.is_open() && fin.good()){
               // send(processChunk(buffer, bufferSize));
			   text = text + processChunk(buffer, bufferSize);
                
                // output << buffer.data();
                // std::cout << i << "\n";
                // output.write(buffer.data(), sizeof(char) * bufferSize);//used for writing out to a file
           // }
        }
        if(fin.good()){
            std::vector<char> lastBuffer (remainingBytesInFile, 0);
            fin.read(lastBuffer.data(), remainingBytesInFile);
           // send(processChunk(lastBuffer, remainingBytesInFile));
		   text = text + processChunk(buffer, bufferSize);
		   
            //output << lastBuffer.data();
            //std::cout << "in if of for loop: " << "\n";
            //output.write(lastBuffer.data(), sizeof(char) * remainingBytesInFile);//used for writing out to a file
        }
        fin.close();
        //output.close();//used for writing out to a file
		
		return text;
    }
    
    char* processChunk(std::vector<char> buffer, int bufferSize){
        
        //creating key
        int someMultipleOfEight = 24;
        std::vector<char> key;
        for (int i = 0; i < someMultipleOfEight; i++) {
            key.push_back(i);
        }
        
        //makeing the blowfish with the made key
        Blowfish blowfish(key);//key is vector<char> whose length is a multple of 8
        
        
        return blowfish.Encrypt(buffer).data();//blowfish.Encrypt(buffer) returns a vector<char>
    }
    
    //HERE:
    int send (char* message){
        
    }
    
    
    std::string convertToString(char* a, int size) {
        int i;
        std::string s = "";
        for (i = 0; i < size; i++) {
            s = s + a[i];
        }
        return s;
    }
    
};

