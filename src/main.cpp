// Interal Imports
#include "common.hpp"

#include "main.h"

using namespace std;

int main(int input_arg_number, char* input_args[])
{
	try {
		po::variables_map ConfigVariables;
		map<string, vector<string> > Structure_Date;

		ConfigVariables = ParseCommandLineArgs(input_arg_number, input_args);
		cout << ConfigVariables["structure_file"].as<string>() << endl;
		Structure_Date = ParseConfigData(ConfigVariables["structure_file"].as<string>());
		PrintConfigData(Structure_Date);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}