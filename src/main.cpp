const char * VERSION = "0.0.1";

// --------------------------------------------------
// Quick import of all standard packages
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
// --------------------------------------------------

// Import Eveything Else
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/random.hpp>
#include <boost/dynamic_bitset.hpp>

// Interal Imports
// #include "BMAS/Common.hpp"

// Setup namespaces for easier usage
using namespace std;
namespace po = boost::program_options;

// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	copy(v.begin(), v.end(), ostream_iterator<T>(os, endl));
	return os;
}

// Check for Param Filetype section headers
bool FindHeaderName(string& line, string& HeaderName)
{
	boost::regex e("^\\s*\\[(.*)\\]\\s*$");
	boost::match_results<std::string::const_iterator> match_results;
	if (boost::regex_match(line, match_results, e, boost::match_default | boost::match_partial)) {
		HeaderName = match_results[1]; // Value in the first set of parenthesis
		return true;
	}
	return false;
}

void StripComments(string& line)
{
	boost::regex e("^([^#]*).*$");
	boost::match_results<std::string::const_iterator> match_results;
	if (boost::regex_match(line, match_results, e, boost::match_default | boost::match_partial)) {
		line = match_results[1]; // Value in the first set of parenthesis
	}
}

map<string, vector<string> > ParseBMASConfigFile(vector<string>& ConfigData) {
	// Parse the incoming Struct File here
	string line;
	string HeaderName = "";
	map<string, vector<string> > ConfigSettings;
	//while (getline(struct_file_handle, line))
	for (string line : ConfigData)
	{
		// Prepare the line for processing
		StripComments(line);	// Remove anything "behind" a # symbol
		boost::trim(line);	// Remove whitespace from both ends of the line
		if (line.length() == 0) { continue; }	// Skip Blank Lines

		if (FindHeaderName(line, HeaderName)) { continue; } // Look for a header entry
		if (HeaderName == "") { continue; } // A header has not yet been seen

		ConfigSettings[HeaderName].push_back(line); // Build Config Structure
	}
	return ConfigSettings;
}

int main(int input_arg_number, char* input_args[])
{
	try {
		// ----------------------------------------------------------------
		// Setup command line and config file option system

		// Variables that will be filled by the command line input parser
		string config_file;
		string struct_file;

		// Set Command Line Only Options
		po::options_description generic("Generic options");
		generic.add_options()
			("version,v", "print version string")
			("help,h", "produce help message")
			("config_file,c", po::value<string>(&config_file)->default_value("C:\\Users\\koanb\\Documents\\Visual Studio 2015\\Projects\\BoostTest\\multiple_sources.cfg"),
				"File Containing Default Configuration Options.")
			;

		// Set Options that can come from either the Command Line or the Config File
		po::options_description config("Configuration");
		config.add_options()
			("struct_file,S", po::value<string>(&struct_file)->default_value("C:\\Users\\koanb\\Documents\\Visual Studio 2015\\Projects\\BoostTest\\StackedTrimer.txt"),
				"File Containing Description of the Structure.")
			;

		po::options_description cmdline_options;
		cmdline_options.add(generic).add(config);

		po::options_description config_file_options;
		config_file_options.add(config);

		po::options_description visible("Allowed options");
		visible.add(generic).add(config);

		po::positional_options_description p;
		p.add("struct_file", -1);

		po::variables_map vm;
		store(po::command_line_parser(input_arg_number, input_args).
			options(cmdline_options).positional(p).run(), vm);
		notify(vm);
		// ----------------------------------------------------------------
		// Respond to Command line options

		// Read the config file and add any options from there
		ifstream config_file_handle(config_file);
		if (!config_file_handle)
		{
			cout << "can not open config file: " << config_file << endl;
			return 0;
		}
		else
		{
			store(parse_config_file(config_file_handle, config_file_options), vm);
			notify(vm);
			config_file_handle.close();
		}

		if (vm.count("help")) {
			cout << visible << endl;
			return 0;
		}

		if (vm.count("version")) {
			cout << "BMAS C++ based frontend version: " << VERSION << endl;
			return 0;
		}
		// ----------------------------------------------------------------
		// Import the Configuration Settings from the Structure File
		map<string, vector<string> > ConfigSettings;
		ifstream struct_file_handle(struct_file);
		if (!struct_file_handle)
		{
			cout << "can not open structure file: " << struct_file << endl;
			return 0;
		}
		else
		{
			string line;
			vector<string> ConfigFileData;
			while (getline(struct_file_handle, line)) { ConfigFileData.push_back(line); }
			struct_file_handle.close();

			ConfigSettings = ParseBMASConfigFile(ConfigFileData);
			// Notes for later, it will be used to subdevide the data on each line
			//boost::split(SplitVec, line, boost::is_any_of(":"), boost::token_compress_on);
			//cout << SplitVec;
		}

		// Print the data to confirm it looks reasonable.
		for (pair<string, vector<string> > SettingGroup : ConfigSettings)
		{
			cout << "Header Section: " << SettingGroup.first << endl;
			for (auto Setting : SettingGroup.second) {
				cout << Setting << endl;
			}
		}

	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}