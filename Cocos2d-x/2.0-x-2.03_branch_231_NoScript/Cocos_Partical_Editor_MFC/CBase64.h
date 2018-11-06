/** 
* (C) Copyright 2009, asiainfo 
* @version  v1.0 
* @author   chenli 
* @brief    base64±àÂëºÍ½âÂë 
* 
* history: 
* <p>chenli 2009-02-17 1.0 build this moudle</p> 
*/  
  
#ifndef ___BASE64_H___   
#define ___BASE64_H___   
  
  
#include <string>   
  
using namespace std;  
  
class CBase64  
{  
public:  
    CBase64();  
    ~CBase64();  
  
    bool static Encode(const unsigned char *pIn, unsigned long uInLen, string& strOut);  
  
    bool static Encode(const unsigned char *pIn, unsigned long uInLen, unsigned char *pOut, unsigned long *uOutLen);  
      
    bool static Decode(const string& strIn, unsigned char *pOut, unsigned long *uOutLen) ;  
 
    bool static Decode(const unsigned char *pIn, unsigned long uInLen, unsigned char *pOut, unsigned long *uOutLen) ;  
};  
  
#endif // ___BASE64_H___ 

