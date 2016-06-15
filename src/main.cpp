#include "main.hpp"

#include "nausparse.h"

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

		// ----------------  nauty Testing Section  ----------------
		DYNALLSTAT(int, lab1, lab1_sz);
		DYNALLSTAT(int, lab2, lab2_sz);
		DYNALLSTAT(int, ptn, ptn_sz);
		DYNALLSTAT(int, orbits, orbits_sz);
		DYNALLSTAT(int, map, map_sz);
		static DEFAULTOPTIONS_SPARSEGRAPH(options);
		statsblk stats;
		/* Declare and initialize sparse graph structures */
		SG_DECL(sg1); SG_DECL(sg2);
		SG_DECL(cg1); SG_DECL(cg2);

		options.getcanon = true;
		//options.defaultptn = false;
		options.writeautoms = true;

		int n, m, i;
		n = 60;

		m = SETWORDSNEEDED(n);
		nauty_check(WORDSIZE, m, n, NAUTYVERSIONID);
		DYNALLOC1(int, lab1, lab1_sz, n, "malloc");
		DYNALLOC1(int, lab2, lab2_sz, n, "malloc");
		DYNALLOC1(int, ptn, ptn_sz, n, "malloc");
		DYNALLOC1(int, orbits, orbits_sz, n, "malloc");
		DYNALLOC1(int, map, map_sz, n, "malloc");

		/* Now make the first graph */
		SG_ALLOC(sg1, n, 3 * n, "malloc");
		sg1.nv = n; /* Number of vertices */
		sg1.nde = 3 * n; /* Number of directed edges */
		for (i = 0; i < n; ++i)
		{
			sg1.v[i] = 3 * i; /* Position of vertex i in v array */
			sg1.d[i] = 3; /* Degree of vertex i */
		}
		for (i = 0; i < n; i += 2) /* Spokes */
		{
			sg1.e[sg1.v[i]] = i + 1;
			sg1.e[sg1.v[i + 1]] = i;
		}
		for (i = 0; i < n - 2; ++i) /* Clockwise edges */
			sg1.e[sg1.v[i] + 1] = i + 2;
		sg1.e[sg1.v[n - 2] + 1] = 1;
		sg1.e[sg1.v[n - 1] + 1] = 0;
		for (i = 2; i < n; ++i) /* Anticlockwise edges */
			sg1.e[sg1.v[i] + 2] = i - 2;
		sg1.e[sg1.v[1] + 2] = n - 2;
		sg1.e[sg1.v[0] + 2] = n - 1;
		/* Now make the second graph */
		SG_ALLOC(sg2, n, 3 * n, "malloc");
		sg2.nv = n; /* Number of vertices */
		sg2.nde = 3 * n; /* Number of directed edges */
		for (i = 0; i < n; ++i)
		{
			sg2.v[i] = 3 * i;
			sg2.d[i] = 3;
		}
		for (i = 0; i < n; ++i)
		{
			sg2.v[i] = 3 * i;
			sg2.d[i] = 3;
			sg2.e[sg2.v[i]] = (i + 1) % n; /* Clockwise */
			sg2.e[sg2.v[i] + 1] = (i + n - 1) % n; /* Anti-clockwise */
			sg2.e[sg2.v[i] + 2] = (i + n / 2) % n; /* Diagonals */
		}

	   /* Label sg1, result in cg1 and labeling in lab1; similarly sg2.
		It is not necessary to preallocate space in cg1 and cg2, but
		they have to be initialized as we did above. */
		sparsenauty(&sg1, lab1, ptn, orbits, &options, &stats, &cg1);
		sparsenauty(&sg2, lab2, ptn, orbits, &options, &stats, &cg2);
		/* Compare canonically labeling graphs */
		if (aresame_sg(&cg1, &cg2))
		{
			printf("Isomorphic.\n");
			if (n <= 1000)
			{
				/* Write the isomorphism. For each i, vertex lab1[i]
				of sg1 maps onto vertex lab2[i] of sg2. We compute
				the map in order of labeling because it looks better. */
				for (i = 0; i < n; ++i) map[lab1[i]] = lab2[i];
				for (i = 0; i < n; ++i) printf(" %d-%d", i, map[i]);
				printf("\n");
			}
		}
		else
			printf("Not isomorphic.\n");


	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}

