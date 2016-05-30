#include "FileReader.h"


FileReader::FileReader(std::string file)
{ 
	readFile(file); 
}


FileReader::~FileReader()
{
}

void FileReader::readFile(std::string file) {
	int size; 
	char current; 
	std::ifstream in(file, std::ifstream::in);
	std::string str; 
	std::string key; 
	std::vector<std::string> content; 
	
	//check if the stream can be opened. v. necessary bc for some reason it didn't like your file
	if (in.good()) {
		//run while the end of the file has not been reached
		while (!in.eof()) {
			std::getline(in, str); //read in the current line
			size = str.length();
			int i = 0;

			//run if the string isn't empty, so we're able to ignore blank lines
			if (!str.empty()) {
				//the current char of the string we're viewing
				current = str[i];
				//determine how much blank space (in the form of spaces and tabs) is at the beginning of lines
				while (current == ' ' || current == '	') {
					i++;
					current = str[i];
				}
				//determine if the current line is a header, denoted by [...]
				if (str[i] == '[' && str[size - 1] == ']') {
					//erase any spaces and tabs
					str.erase(0, i);
					//make the header a key in the map
					key = str;
					//i thought it could be useful to store the keys in another vector?
					keys.push_back(key);
					//clear the contents of the vector
					content.clear();
					//insert the key and the vector as a new entry into our map
					params.insert(std::pair <std::string, std::vector<std::string> >(key, content));
				}
				//check if the line is a comment. if not, add it to the vector and update the vector in the map
				else if (str[i] != '#') {
					str.erase(0, i);
					content.push_back(str);
					params[key] = content;
				}

			}
		}
	}
	else {
		std::cout << "Unable to open input stream. Use a different input file" << std::endl; 
	}
	in.close(); 

}

std::map<std::string, std::vector<std::string>> FileReader::getInput() {
	return params; 
}

/* we don't have to keep the print method, I wrote it more for testing/ debugging than anything
 * but I figure that they could be useful. */


void FileReader::printMap() {

	for (int i = 0; i < keys.size(); i++) {
		std::vector<std::string> temp = params[keys[i]];
		int size = temp.size();

		for (int i = 0; i < size; i++) {
			std::cout << temp[i] << std::endl;
		}
	}
}