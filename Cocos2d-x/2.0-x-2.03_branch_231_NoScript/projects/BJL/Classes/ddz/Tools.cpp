#include "Tools.h"

const char* loadText(const char* key)
{
	string path = "xml/text.xml";
	TinyXmlReader m_TinyXmlReader;
	TinyXMLDocument* doc = m_TinyXmlReader.open(path);
	return doc->readString(key);
	return NULL;
}