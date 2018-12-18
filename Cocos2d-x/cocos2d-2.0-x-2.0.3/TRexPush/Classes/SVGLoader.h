

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "pugixml.hpp"
#include "Box2D/Box2D.h"


class SVGLoader: public pugi::xml_tree_walker
{

	std::ifstream inFile;

	pugi::xml_document doc;

	std::map<string, vector<b2Vec2> > paths;

	void parseVertices(string init, vector<b2Vec2> &vec);

public:

	virtual bool for_each(pugi::xml_node &node);

	b2PolygonShape *createEdge(string obj_id);

	inline vector<b2Vec2> &operator[](string pathName){
		return paths[pathName];
	}

	SVGLoader(string filename);
	~SVGLoader(void);
};

