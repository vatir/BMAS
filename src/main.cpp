#include "main.hpp"

using namespace std;

int main(int input_arg_number, char* input_args[])
{
	try {
		po::variables_map ConfigVariables;
		map<string, vector<string> > Structure_Date;

		ConfigVariables = ParseCommandLineArgs(input_arg_number, input_args);

		//cout << ConfigVariables["structure_file"].as<string>() << endl;

		Structure_Date = ParseConfigData(ConfigVariables["structure_file"].as<string>());
		//PrintConfigData(Structure_Date);

		Structure CompleteGraph(Structure_Date);

		//CompleteGraph.PrintRepresentation();
		//CompleteGraph.PrintSubunitLocations();
		//CompleteGraph.PrintBondTypes();
		//CompleteGraph.PrintBonds();

		//nauty_test(10);
		sparsegraph cg;
		nauty_graph tg;
		nauty_env workspace;
		
		workspace.SetSize(10);
		tg.SetTest(10);

		cg = workspace.GetCanonical(tg.graph);

		if (aresame_sg(&tg.graph, &cg)) {
			cout << "Worked!";
		}

	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}

