#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>

class FileReader
{
public:
	FileReader(std::string file);
	~FileReader();
	void readFile(std::string file); 
	std::map<std::string, std::vector<std::string>> getInput(); 
	void printMap();


private:
	std::map<std::string, std::vector<std::string>> params; 
	std::vector<std::string> keys; 
};

#endif
