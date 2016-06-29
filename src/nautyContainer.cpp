#include "nautyContainer.h"



nautyContainer::nautyContainer(adjMatrix matrix)
{
	buildGraph(matrix); 
}


nautyContainer::~nautyContainer()
{
}

void nautyContainer::buildGraph(adjMatrix matrix) {
	int** adjacencies = matrix.getMatrix();

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

	int m, n, i, de; 

	n = matrix.getSize(); 
	de = matrix.getNumEdges(); 

	m = SETWORDSNEEDED(n);
	nauty_check(WORDSIZE, m, n, NAUTYVERSIONID);
	DYNALLOC1(int, lab1, lab1_sz, n, "malloc");
	DYNALLOC1(int, lab2, lab2_sz, n, "malloc");
	DYNALLOC1(int, ptn, ptn_sz, n, "malloc");
	DYNALLOC1(int, orbits, orbits_sz, n, "malloc");
	DYNALLOC1(int, map, map_sz, n, "malloc");

	SG_ALLOC(sg1, n, de, "malloc");
	sg1.nv = n; /* Number of vertices */
	sg1.nde = de;
	
	for (i = 0; i < n; ++i)
	{
		sg1.v[i] = (de/n) * i; /* Position of vertex i in v array */
		sg1.d[i] = de/n; /* Degree of vertex i */
		
	}
	
	for (i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			
			if (adjacencies[i][j] == 1) {
				
				sg1.e[sg1.v[i]] = j; 
			}
			else {
				continue; 
			}
		}
	}
	sparsenauty(&sg1, lab1, ptn, orbits, &options, &stats, &cg1);
}