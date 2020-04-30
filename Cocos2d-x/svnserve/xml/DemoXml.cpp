#include"tinyxml.h"
#include<stdio.h>
#include<locale.h>
#include<string>
using namespace std;

//g++ -o DemoXml DemoXml.cpp -ltinyxml

typedef std::string   SexyString;
// These structs just represent the values from our properties/demo.xml
// file. In a real game, you'd have your own made up config file format.
// The names correspond to the attributes/sections from the XML file.
struct s_Section1
{
 SexyString mItem1Text;
 SexyString  mBoolParamText;
 bool  mBoolParamElement;
};
 
s_Section1  mSection1;

struct s_Section2
{
 SexyString mSectionAttribText;
 SexyString mIntParamText;
 int   mIntParamElement;
 SexyString mMultiAttrib1;
 SexyString mMultiAttrib2;
 SexyString mMultiAttrib3;
 SexyString  mSubsectionItem2;
};
s_Section2  mSection2;
enum
{
 TYPE_NONE,
 TYPE_START,//1
 TYPE_END,
 TYPE_ELEMENT,//3
 TYPE_INSTRUCTION,
 TYPE_COMMENT
};
/** The types of XML nodes supported by TinyXml. (All the
unsupported types are picked up by UNKNOWN.)
*/
enum NodeType
{
 DOCUMENT,
 ELEMENT,
 COMMENT,
 UNKNOWN,
 TEXT,
 DECLARATION,
 TYPECOUNT
};
std::string StringToLower(const std::string& theString)
{
 std::string aString;
 for (unsigned i = 0; i < theString.length(); i++)
  aString += tolower(theString[i]);
 return aString;
}
bool StringToInt(const std::string theString, int* theIntVal)
{
 *theIntVal = 0;
 if (theString.length() == 0)
  return false;
 int theRadix = 10;
 bool isNeg = false;
 unsigned i = 0;
 if (theString[i] == '-')
 {
  isNeg = true;
  i++;
 }
 for (; i < theString.length(); i++)
 {
  char aChar = theString[i];
  if ((theRadix == 10) && (aChar >= '0') && (aChar <= '9'))
   *theIntVal = (*theIntVal * 10) + (aChar - '0');
  else if ((theRadix == 0x10) && 
   (((aChar >= '0') && (aChar <= '9')) || 
   ((aChar >= 'A') && (aChar <= 'F')) || 
   ((aChar >= 'a') && (aChar <= 'f'))))
  {   
   if (aChar <= '9')
    *theIntVal = (*theIntVal * 0x10) + (aChar - '0');
   else if (aChar <= 'F')
    *theIntVal = (*theIntVal * 0x10) + (aChar - 'A') + 0x0A;
   else
    *theIntVal = (*theIntVal * 0x10) + (aChar - 'a') + 0x0A;
  }
  else if (((aChar == 'x') || (aChar == 'X')) && (i == 1) && (*theIntVal == 0))
  {
   theRadix = 0x10;
  }
  else
  {
   *theIntVal = 0;
   return false;
  }
 }
 if (isNeg)
  *theIntVal = -*theIntVal;
 return true;
}

int main()
{
 ::setlocale(LC_ALL,"chs");
 //从XML文件中读出数据
 TiXmlDocument* m_xmlDoc;
 char name[100],legend[100];
 m_xmlDoc = new TiXmlDocument("demo.xml");
 if (m_xmlDoc->LoadFile())
 {
  TiXmlElement *xheros = 0;
  xheros = m_xmlDoc->FirstChildElement("Section1");
        int mType=xheros->Type();
  //_ASSERTE(mType==ELEMENT/*TYPE_START*/ && "tip");
  string str=xheros->Value();
  //_ASSERTE(str=="Section1" && "tip");
  int a=0;
  if(xheros)
  {
    TiXmlElement *xhero = 0;
    xhero=xheros->FirstChildElement("Item1");
    int mType1=xhero->Type();
    //_ASSERTE(mType1==ELEMENT/*TYPE_ELEMENT*/ && "Item1");
    string str1=xhero->Value();
    //_ASSERTE(str1=="Item1" && "tip");
    //mSection1.mItem1Text = e.mAttributes[_S("text")];
    mSection1.mItem1Text=xhero->Attribute("text");
    TiXmlElement *xn1 = 0;
    if(xhero!=NULL && (xn1=xhero->NextSiblingElement("BoolParam"))!=NULL)
    {
     mSection1.mBoolParamText=xn1->Attribute("text");
     string str=xn1->FirstChild()->Value();
     mSection1.mBoolParamElement = StringToLower(str) == "false" ? false : true;
    }
  }
  xheros=xheros->NextSiblingElement();
  if (xheros->Value() =="IntParam")
   mSection2.mSectionAttribText = xheros->Attribute("s2attrib");
  TiXmlElement *xhero = 0;
  xhero=xheros->FirstChildElement("IntParam");
  if (xhero!=NULL)
  {
   mSection2.mIntParamText = xhero->Attribute("text");
            (void)StringToInt(xhero->Value(), &mSection2.mIntParamElement);
  }
  xhero=xheros->FirstChildElement("MultiAttrib");
  if (xhero!=NULL)
  {
   mSection2.mMultiAttrib1 = xhero->Attribute("attrib1");
   mSection2.mMultiAttrib2 = xhero->Attribute("attrib2");
   mSection2.mMultiAttrib3 = xhero->Attribute("attrib3");
  }
  xhero=xheros->FirstChildElement("Subsection");
  xhero=xhero->FirstChildElement("Item2");
  if (xhero!=NULL)
  {
   mSection2.mSubsectionItem2 = xhero->Value();
  }
 }
 delete m_xmlDoc;
 //getchar();
 return 0;
}