#include <string>
#include "FileReader.h"

int main(int argc, char** argv) {
	std::string input = argv[1];
	//Hard coded just for testing purposes
	//std::string input = "trimer.txt";
	FileReader reader(input); 
	//reader.printMap(); 

	return 0; 
}