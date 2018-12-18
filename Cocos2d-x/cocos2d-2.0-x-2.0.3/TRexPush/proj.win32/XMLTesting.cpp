#include "XMLTesting.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "pugixml.hpp"
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "SVGLoader.h"
#include "cocos2d.h"
#include "CCDictionary.h"
#include "GB2ShapeCache.h"

using namespace std;
using namespace pugi;
USING_NS_CC;

class tri_test_walker: public xml_tree_walker
{



public:
	vector<b2Vec2> vertices;

	void parseVertices(string init){
		auto str = stringstream(init);

		string s;
		while(str.good()){
			str >> s;
			int idx = s.find(',');

			if (idx == -1){
				continue;
			}
			else{
				string s1 = s.substr(0,idx);
				string s2 = s.substr(idx+1, -1);

				double x;  stringstream(s1) >> x;
				double y;  stringstream(s2) >> y;

				vertices.push_back(b2Vec2(x, y));
			}
		}
	}

	virtual bool for_each(xml_node &node){

		cout<<node.name()<<endl;

		string s = node.attribute("id").as_string();
		if(s == "TRI_OBJ"){

			// The vertex path attribute
			s = node.attribute("d").as_string();

			parseVertices(s);
			
			// End the traversal
			return false;
		}

		// Continue the traversal
		return true;
	}
};

void xmlTests(std::string filename){


	//SVGLoader walker(filename);


	/*for (auto itr = walker["TRI_OBJ"].begin();
		itr != walker["TRI_OBJ"].end();
		itr++){

			cout<<"("<<itr->x<<", "<<itr->y<<"), ";
	}*/
	//cout<<endl;

	
	auto *dict = CCDictionary::createWithContentsOfFile("LevelData.plist");
	/*CCDictElement *el;

	CCDICT_FOREACH(dict, el){
		cout<<el->getStrKey()<<endl;
		
		auto *next = dynamic_cast<CCDictionary *>(el->getObject());
		if (next){
			CCDictElement *eel;
			CCDICT_FOREACH(next, eel){
				cout<<"\t"<<eel->getStrKey()<<endl;
			}
		}
	}*/

	//doc.save(std::cout);

	auto *stagesDict = dynamic_cast<CCDictionary*>(dict->objectForKey("STAGES"));
	
	CCDictElement *obj;
	CCDICT_FOREACH(stagesDict, obj){
		//cout<<obj-<<endl;
		//cout<<obj->getObject()->
		//CCInteger
	}
	

	//gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("starshape.plist");


}