#pragma once
#include "graphStructs.h"
#include "nausparse.h"
class nautyContainer
{
public:
	nautyContainer(adjMatrix matrix);
	~nautyContainer();
	void buildGraph(adjMatrix matrix); 
};

