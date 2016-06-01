// Interal Imports
#include "common.hpp"

int main(int input_arg_number, char* input_args[])
{
	try {
		po::variables_map ConfigVariables;
		ConfigVariables = ParseCommandLineArgs(input_arg_number, input_args);
		//cout << ConfigVariables << endl;
		//cout << SF << endl;
		//ParseConfigData(ConfigVariables["struct_file"]);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}