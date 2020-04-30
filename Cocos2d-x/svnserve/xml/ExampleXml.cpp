#include<stdio.h>
#include<string.h>
#include"tinyxml.h"

//g++ -o ExampleXml ExampleXml.cpp -ltinyxml
int main()
{
 //从XML文件中读出数据
 TiXmlDocument* m_xmlDoc;
 char name[100],legend[100]; 
 m_xmlDoc = new TiXmlDocument("Example.xml");

 if (m_xmlDoc->LoadFile())
 {

  TiXmlElement *xheros = 0;
  xheros = m_xmlDoc->FirstChildElement("Example");

  if (xheros)
  {
	  TiXmlElement *xhero = 0;
	  xhero=xheros->FirstChildElement("SecondNode");
	  int i=0;
	  while(xhero)
	  {
		  printf("第%d个SecondNode--------\n",i+1);
		  printf("%s\n",xhero->Value());//SecondNode,SecondNode
          printf("%s\n",xhero->Attribute("type"));//thirdie,fourdie
          printf("%s\n",xhero->FirstChild()->Value());//ThirdNode,ForthNode
		  //if(strcmp(xhero->Attribute("type"),"thirdie")==0)
		  //{
		  //}
		  //if(strcmp(xhero->Attribute("type"),"fourdie")==0)
		  //{
            //printf("%s\n",xhero->FirstChildElement("ForthNode")->Attribute("id"));//1
            //printf("%s\n",xhero->FirstChildElement("ForthNode")->Value());//ForthNode
            //printf("%s\n",xhero->FirstChildElement("ForthNode")->FirstChild()->Value());//Since it has text, it's not safe..lol
		  //}
            //或TiXmlElement *eNode =xhero->FirstChildElement("ThirdNode");
            TiXmlElement *eNode =xhero->FirstChildElement();
			while(eNode)
			{
				printf("%s  ",eNode->Attribute("id"));//1
				//printf("%s\n",eNode->Value());//ThirdNode
				printf("%s  ",eNode->Attribute("order"));//(null)或2
				printf("%s  ",eNode->Attribute("safe"));//(null)或2
				if(eNode->FirstChild())//add
				printf("%s\n",eNode->FirstChild()->Value());//The ID of me is 1
				else
					printf("\n");//add
				eNode=eNode->NextSiblingElement();
			}
          //printf("%s\n",xhero->LastChild()->Value());//ThirdNode,ForthNode
		  printf("\n");
		  i++;
          xhero=xhero->NextSiblingElement();
	  }

   printf("总共有%d个SecondNode\n",i);
  }

 }
 delete m_xmlDoc;
 //getchar();
 return 0;
}