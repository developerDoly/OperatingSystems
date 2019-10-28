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
#include<bits/stdc++.h> 

long GetFileSize(std::string filename);

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int main(){
	long sizeOfFile = GetFileSize("input.txt");
	int bufferSize = 4096;
	
	int numBuffers = (int) sizeOfFile/bufferSize;//numBuffer will always be an integer
	int remainingBytesInFile = (int) sizeOfFile%bufferSize;
	
	std::cout << "numBuffers: " << numBuffers << "\n";
	std::cout << "remainingBytesInFile: " << remainingBytesInFile << "\n";
	
	std::ifstream fin("./input.txt", std::ifstream::binary);
	std::vector<char> buffer (bufferSize, 0);
	std::ofstream output("./b.txt");
	
	for(int i = 0; i < numBuffers; i++){
		fin.read(buffer.data(), buffer.size());
		if (output.is_open()){
			output << buffer.data();
		}	
	}
	std::vector<char> lastBuffer (remainingBytesInFile, 0);
	fin.read(lastBuffer.data(), remainingBytesInFile);
	output << lastBuffer.data();
	fin.close();
	output.close();
}