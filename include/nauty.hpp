#pragma once

#include "nauty.h"

class nauty_graph
{
public:
	// Member Variables
	// Constructor(s)
	nauty_graph();
	// Destructor(s)
	virtual ~nauty_graph();
	// Member functions
	void SetSize(int Size);
	void SetTest(int Size);
	void SetType1();
	void SetTypeStackedRing(int RingSize, int Height); // Size of a single ring, Height
	int GetSize();
	void PrintGraph();
	TLS_ATTR int *lab; TLS_ATTR size_t lab_sz;
	TLS_ATTR int *ptn; TLS_ATTR size_t ptn_sz;
	TLS_ATTR graph *cg; TLS_ATTR size_t cg_sz;
	int n;
	int m;
private:
};

class nauty_env
{
public:
	// Member Variables
	// Constructor(s)
	nauty_env();
	// Destructor(s)
	virtual ~nauty_env();
	// Member functions
	void SetSize(int);
	void SetSizeFromGraph(nauty_graph);

	void GetCanonical(nauty_graph & cg, nauty_graph & can_g);

	void Reset();

	TLS_ATTR int *orbits; TLS_ATTR size_t orbits_sz;
	TLS_ATTR int *map; TLS_ATTR size_t map_sz;
	optionblk options;
	statsblk stats;
	int n;
	int m;

private:
};
