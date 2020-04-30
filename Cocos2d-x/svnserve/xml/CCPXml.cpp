#include<stdio.h>
#include<string.h>
#include<locale.h>
#include"tinyxml.h"

//g++ -o CCPXml CCPXml.cpp -ltinyxml
int main()
{
 ::setlocale(LC_ALL,"chs");
 //从XML文件中读出数据
 TiXmlDocument* m_xmlDoc;
 char name[100],legend[100];
 m_xmlDoc = new TiXmlDocument("ccp.xml");

 if (m_xmlDoc->LoadFile())
 {

  TiXmlElement *xheros = 0;
  xheros = m_xmlDoc->FirstChildElement("Socialisms");

  if (xheros)
  {
	  TiXmlElement *xhero = 0;
	  xhero=xheros->FirstChildElement("Socialism");
	  int i=0;
	  while(xhero)
	  {
		  printf("第%d位英雄--------\n",i+1);
	      TiXmlElement *xname = 0;
          if((xname=xhero->FirstChildElement("Name"))!=NULL)
		  {
			  printf("%s\n",xname->FirstChild()->Value());
		  }
	      TiXmlElement *xNumber = 0;
          if(xname!=NULL && (xNumber=xname->NextSiblingElement("Number"))!=NULL)
		  {
			  printf("%s\n",xNumber->FirstChild()->Value());
		  }
	      TiXmlElement *xCountry = 0;
          if(xNumber!=NULL && (xCountry=xNumber->NextSiblingElement("Country"))!=NULL)
		  {
			  printf("%s\n",xCountry->FirstChild()->Value());
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