#include "nauty.hpp"

using namespace std;

nauty_env::nauty_env() {
	orbits_sz = 0;
	map_sz = 0;
	n = 0;
	m = 0;

	options = \
		{0, FALSE, FALSE, FALSE, TRUE, FALSE, CONSOLWIDTH, \
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, 100, 0, 1, 0, &dispatch_graph, FALSE, NULL};

	options.digraph = TRUE;
	options.getcanon = TRUE;
	//options.writeautoms = true;
}

nauty_env::~nauty_env() {}

void nauty_env::SetSize(int Size) {
	n = Size;
	m = SETWORDSNEEDED(n);
	nauty_check(WORDSIZE, m, n, NAUTYVERSIONID);
	DYNALLOC1(int, orbits, orbits_sz, Size, "malloc");
	DYNALLOC1(int, map, map_sz, n, "malloc");
}

void nauty_env::GetCanonical(nauty_graph& cg, nauty_graph & can_g) {
	densenauty(cg.cg, cg.lab, cg.ptn, orbits, &options, &stats, m, n, can_g.cg);
}

void nauty_env::Reset() {
	*orbits = 0;
	n = 0;
	m = 0;
}

nauty_graph::nauty_graph()
{
	lab_sz = 0;
	ptn_sz = 0;
	cg_sz  = 0;
	n = 0;
	m = 0;
}

nauty_graph::~nauty_graph() {}

void nauty_graph::SetSize(int Size)
{
	n = Size;
	m = SETWORDSNEEDED(n);
	DYNALLOC1(int, lab, lab_sz, Size, "malloc");
	DYNALLOC1(int, ptn, ptn_sz, Size, "malloc");
	DYNALLOC2(graph, cg, cg_sz, m, n, "malloc");
	EMPTYGRAPH(cg, m, n);
}

void nauty_graph::SetTest(int Size)
{
	SetSize(Size);
	DYNALLOC2(graph, cg, cg_sz, n, m, "malloc");
	EMPTYGRAPH(cg, m, n);
	for (int i = 0; i < n; i += 2) /* Spokes */
		ADDONEEDGE(cg, i, i + 1, m);
	for (int i = 0; i < n - 2; ++i) /* Cycle */
		ADDONEEDGE(cg, i, i + 2, m);
	ADDONEEDGE(cg, 1, n - 2, m);
	ADDONEEDGE(cg, 0, n - 1, m);
}

void nauty_graph::SetType1()
{
	int Size = 6;
	SetSize(Size);
	EMPTYGRAPH(cg, m, n);
	for (int v = 0; v < n; ++v) ADDONEEDGE(cg, v, (v + 1) % n, m);
}

