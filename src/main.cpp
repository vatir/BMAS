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

		adjMatrix graph(CompleteGraph); 
		graph.printMatrix(); 
		//CompleteGraph.PrintRepresentation();
		//CompleteGraph.PrintSubunitLocations();
		//CompleteGraph.PrintBondTypes();
		//CompleteGraph.PrintBonds();

		//nauty_test(10);
		nauty_graph cg1;
		nauty_graph cg2;
		nauty_graph tg1;
		nauty_graph tg2;
		nauty_env workspace;
		nauty_env workspace2; 
		nauty_graph test(graph); 
		nauty_graph test2(graph);
		workspace2.SetSize(graph.getSize());
		workspace.SetSize(10);
		tg2.SetTest(10);
		tg1.SetTest(10);
		cg1.SetSize(graph.getSize());
		cg2.SetSize(graph.getSize());
		

		workspace2.GetCanonical(test2, cg2);
		//workspace.Reset();
		workspace2.GetCanonical(test, cg1);

		
		int k;
		for (k = 0; k < workspace2.m*(size_t)workspace2.n; ++k)
			if (cg1.cg[k] != cg2.cg[k]) break;
		if (k == workspace2.m*(size_t)workspace2.n)
		{
			printf("Isomorphic.\n");
			if (workspace2.n <= 1000)
			{
				/* Write the isomorphism. For each i, vertex lab1[i]
				of sg1 maps onto vertex lab2[i] of sg2. We compute
				the map in order of labeling because it looks better. */ 
				for (int i = 0; i < workspace2.n; ++i) workspace2.map[test.lab[i]] = test2.lab[i];
				for (int i = 0; i < workspace2.n; ++i) printf(" %d-%d", i, workspace2.map[i]);
				printf("\n"); 
			}
		}
		else {
			printf("Not isomorphic.\n");
		}
		
		
	} 
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	 
	return 0;
}

