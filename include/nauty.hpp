#pragma once

#include "nausparse.h"

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
	sparsegraph GetCanonical(sparsegraph & graph);
private:
	TLS_ATTR int *lab; TLS_ATTR size_t lab_sz;
	TLS_ATTR int *ptn; TLS_ATTR size_t ptn_sz;
	TLS_ATTR int *orbits; TLS_ATTR size_t orbits_sz;
	TLS_ATTR int *map; TLS_ATTR size_t map_sz;
	optionblk options;
	statsblk stats;
	/* Declare and initialize sparse graph structures */
};

class nauty_graph
{
public:
	// Member Variables
	// Constructor(s)
	nauty_graph();
	// Destructor(s)
	virtual ~nauty_graph();
	// Member functions
	void SetSize(int Size, int MaxDegree);
	void SetTest(int Size);
	sparsegraph graph;
private:
};

void nauty_test(int);