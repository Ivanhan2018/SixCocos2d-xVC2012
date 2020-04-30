#include<stdio.h>
#include<string.h>
#include<locale.h>
#include"tinyxml.h"

//g++ -o UIXml UIXml.cpp -ltinyxml
int main()
{
 ::setlocale(LC_ALL,"chs");
 //从XML文件中读出数据
 TiXmlDocument* m_xmlDoc;
 char name[100],legend[100];
 m_xmlDoc = new TiXmlDocument("UI.xml");

 if (m_xmlDoc->LoadFile())
 {

  TiXmlElement *xheros = 0;
  xheros = m_xmlDoc->FirstChildElement("RootWindow");

  if (xheros)
  {
	  TiXmlElement *xhero = 0;
	  xhero=xheros->FirstChildElement("Dialog");
	  int i=0;
	  while(xhero)
	  {
		  printf("第%d个Dialog--------\n",i+1);
	      TiXmlElement *xID = 0;
          if((xID=xhero->FirstChildElement("ID"))!=NULL)
		  {
			  printf("%s\n",xID->FirstChild()->Value());
		  }
	      TiXmlElement *xn1 = 0;
          if(xID!=NULL && (xn1=xID->NextSiblingElement("TextID"))!=NULL)
		  {
			  printf("%s\n",xn1->FirstChild()->Value());
		  }
	      TiXmlElement *xn2 = 0;
          if(xn1!=NULL && (xn2=xn1->NextSiblingElement("LocationX"))!=NULL)
		  {
			  printf("%s\n",xn2->FirstChild()->Value());
		  }
	      TiXmlElement *xn3 = 0;
          if(xn2!=NULL && (xn3=xn2->NextSiblingElement("LocationY"))!=NULL)
		  {
			  printf("%s\n",xn3->FirstChild()->Value());
		  }
	      TiXmlElement *xn4 = 0;
          if(xn3!=NULL && (xn4=xn3->NextSiblingElement("Width"))!=NULL)
		  {
			  printf("%s\n",xn4->FirstChild()->Value());
		  }
	      TiXmlElement *xn5 = 0;
          if(xn4!=NULL && (xn5=xn4->NextSiblingElement("Height"))!=NULL)
		  {
			  printf("%s\n",xn5->FirstChild()->Value());
		  }
	      TiXmlElement *xn6 = 0;
          if(xn5!=NULL && (xn6=xn5->NextSiblingElement("Transparency"))!=NULL)
		  {
			  printf("%s\n",xn6->FirstChild()->Value());
		  }
	      TiXmlElement *xn7 = 0;
          if(xn6!=NULL && (xn7=xn6->NextSiblingElement("Visible"))!=NULL)
		  {
			  printf("%s\n",xn7->FirstChild()->Value());
		  }
	      TiXmlElement *xn8 = 0;
          if(xn7!=NULL && (xn8=xn7->NextSiblingElement("TipString"))!=NULL)
		  {
			  if(xn8->FirstChild())
			  printf("%s\n",xn8->FirstChild()->Value());
			  else
				  printf("<TipString />\n");
		  }
	      TiXmlElement *xn9 = 0;
          if(xn8!=NULL && (xn9=xn8->NextSiblingElement("BackgroundTexture"))!=NULL)
		  {
			  printf("%s\n",xn9->FirstChild()->Value());
		  }
		  TiXmlElement *xctls = 0;
		  //不要xctls=xheros->FirstChildElement("Controls");
          if(xn9!=NULL && (xctls=xn9->NextSiblingElement("Controls"))!=NULL)
		  {
			  printf("%s\n",xctls->Value());//Controls
			  TiXmlElement *xctl = 0;
			  xctl=xctls->FirstChildElement();
			  int ii=0;
			  while(xctl)
			  {
				  printf("第%d个Dialog第%d个ctl--------\n",i+1,ii+1);
                  printf("%s\n",xctl->Value());
				  TiXmlElement *xctlID = 0;
				  if((xctlID=xctl->FirstChildElement("ID"))!=NULL)
				  {
					  printf("%s\n",xctlID->FirstChild()->Value());
				  }
				  TiXmlElement *xctln1 = 0;
				  if(xctlID!=NULL && (xctln1=xctlID->NextSiblingElement("TextID"))!=NULL)
				  {
					  printf("%s\n",xctln1->FirstChild()->Value());
				  }
				  ii++;
				  xctl=xctl->NextSiblingElement();
			  }

		  }
		  printf("\n");
		  i++;
          xhero=xhero->NextSiblingElement();
		  //if(i>=5)break;
	  }

   printf("总共有%d个Dialog\n",i);//83
  }

 }
 delete m_xmlDoc;
 //getchar();
 return 0;
}