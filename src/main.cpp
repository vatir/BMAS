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
		SG_DECL(cg1);
		SG_DECL(cg2);
		nauty_graph tg1;
		nauty_graph tg2;
		nauty_env workspace;
		
		workspace.SetSize(100);
		workspace.SetSize(100);
		tg2.SetType2();
		tg1.SetType1();

		workspace.GetCanonical(tg2.graph, cg2);
		//workspace.Reset();
		workspace.GetCanonical(tg1.graph, cg1);

		if (aresame_sg(&cg1, &cg2)) {
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

