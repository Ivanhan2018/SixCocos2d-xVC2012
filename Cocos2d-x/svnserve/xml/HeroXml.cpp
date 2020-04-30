#include<stdio.h>
#include<string.h>
#include"tinyxml.h"

//g++ -o HeroXml HeroXml.cpp -ltinyxml
int main()
{
 //从XML文件中读出数据
 TiXmlDocument* m_xmlDoc;
 char name[100],legend[100]; 
 m_xmlDoc = new TiXmlDocument("hero.xml");

 if (m_xmlDoc->LoadFile())
 {

  TiXmlElement *xheros = 0;
  xheros = m_xmlDoc->FirstChildElement("heros");//不是"hero"

  if (xheros)
  {
	  TiXmlElement *xhero = 0;
	  xhero=xheros->FirstChildElement("hero");
	  int i=0;
	  while(xhero)
	  {
		  printf("第%d位英雄--------\n",i+1);
		  //printf("%s\n",xhero->Value());//hero
          //printf("%s\n",xhero->FirstChild()->Value());//name
          //printf("%s\n",xhero->LastChild()->Value());//legend
	      TiXmlElement *xname = 0;
          if((xname=xhero->FirstChildElement("name"))!=NULL)
		  {
			  //printf("%s\n",xname->Value());//name
			  printf("%s\n",xname->FirstChild()->Value());//屈原
		  }
	      TiXmlElement *xlegend = 0;
          if(xname!=NULL && (xlegend=xname->NextSiblingElement("legend"))!=NULL)
		  //不要if((xlegend=xname->FirstChildElement("legend"))!=NULL)
		  {
			  //printf("%s\n",xlegend->Value());//xlegend
			  printf("%s\n",xlegend->FirstChild()->Value());//为国而亡
		  }
		  printf("\n");
		  i++;
          xhero=xhero->NextSiblingElement();
	  }

   printf("总共有%d位英雄\n",i);
  }

 }
 delete m_xmlDoc;
 //getchar();
 return 0;
}