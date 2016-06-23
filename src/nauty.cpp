#include "nauty.hpp"

using namespace std;

nauty_env::nauty_env() {
	lab_sz    = 0;
	ptn_sz    = 0;
	orbits_sz = 0;
	map_sz    = 0;

	options = \
	{0, FALSE, FALSE, FALSE, TRUE, FALSE, CONSOLWIDTH, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 100, 0, 1, 0, &dispatch_sparse, FALSE, NULL};

	options.digraph = true;
	options.getcanon = true;
	//options.writeautoms = true;
}

nauty_env::~nauty_env() {}

void nauty_env::SetSize(int Size) {
	DYNALLOC1(int, lab, lab_sz, Size, "malloc");
	DYNALLOC1(int, ptn, ptn_sz, Size, "malloc");
	DYNALLOC1(int, orbits, orbits_sz, Size, "malloc");
	DYNALLOC1(int, map, map_sz, Size, "malloc");
}

void nauty_env::GetCanonical(sparsegraph & graph, sparsegraph & cg) {
	sparsenauty(&graph, lab, ptn, orbits, &options, &stats, &cg);
}

void nauty_env::Reset() {
	*lab = 0;
	*ptn = 0;
	*orbits = 0;
	*map = 0;
}

nauty_graph::nauty_graph()
{
	graph = { 0,NULL,0,NULL,NULL,NULL,0,0,0,0 };
}

nauty_graph::~nauty_graph() {}

void nauty_graph::SetSize(int Size, int MaxDegree)
{
	SG_ALLOC(graph, Size, MaxDegree * Size, "malloc");
}

void nauty_graph::SetTest(int Size)
{
	SetSize(Size, 3);
	int i;
	graph.nv = Size; /* Number of vertices */
	graph.nde = 3 * Size; /* Number of directed edges */
	for (i = 0; i < Size; ++i)
	{
		graph.v[i] = 3 * i; /* Position of vertex i in v array */
		graph.d[i] = 3; /* Degree of vertex i */
	}
	for (i = 0; i < Size; i += 2) /* Spokes */
	{
		graph.e[graph.v[i]] = i + 1;
		graph.e[graph.v[i + 1]] = i;
	}
	for (i = 0; i < Size - 2; ++i) /* Clockwise edges */
		graph.e[graph.v[i] + 1] = i + 2;
	graph.e[graph.v[Size - 2] + 1] = 1;
	graph.e[graph.v[Size - 1] + 1] = 0;
	for (i = 2; i < Size; ++i) /* Anticlockwise edges */
		graph.e[graph.v[i] + 2] = i - 2;
	graph.e[graph.v[1] + 2] = Size - 2;
	graph.e[graph.v[0] + 2] = Size - 1;
}

void nauty_graph::SetType1()
{
	int Size = 6;
	SetSize(Size, 3);
	int i;
	graph.nv = Size; /* Number of vertices */
	graph.nde = 3 * Size; /* Number of directed edges */
	for (i = 0; i < Size; ++i)
	{
		graph.v[i] = 3 * i; /* Position of vertex i in v array */
		graph.d[i] = 3; /* Degree of vertex i */
	}
	graph.e[graph.v[0]] = 1;
	graph.e[graph.v[1]] = 2;
	graph.e[graph.v[2]] = 0;
	graph.e[graph.v[3]] = 4;
	graph.e[graph.v[4]] = 5;
	graph.e[graph.v[5]] = 3;
	graph.e[graph.v[0]] = 3;
	graph.e[graph.v[1]] = 4;
	graph.e[graph.v[2]] = 5;
}

void nauty_graph::SetType2()
{
	int Size = 10;
	SetSize(Size, 3);
	int i;
	graph.nv = Size; /* Number of vertices */
	graph.nde = 3 * Size; /* Number of directed edges */
	for (i = 0; i < Size; ++i)
	{
		graph.v[i] = 3 * i; /* Position of vertex i in v array */
		graph.d[i] = 3; /* Degree of vertex i */
	}
	for (i = 0; i < Size; i += 2) /* Spokes */
	{
		graph.e[graph.v[i]] = i + 1;
		graph.e[graph.v[i + 1]] = i;
	}
	for (i = 0; i < Size - 2; ++i) /* Clockwise edges */
		graph.e[graph.v[i] + 1] = i + 2;
	graph.e[graph.v[Size - 2] + 1] = 1;
	graph.e[graph.v[Size - 1] + 1] = 0;
	for (i = 2; i < Size; ++i) /* Anticlockwise edges */
		graph.e[graph.v[i] + 2] = i - 2;
	graph.e[graph.v[1] + 2] = Size - 2;
	graph.e[graph.v[0] + 2] = Size - 1;
}

void nauty_test(int n) {
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

	int m, i;
	m = SETWORDSNEEDED(n);
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

