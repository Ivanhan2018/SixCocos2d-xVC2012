//
//  Login.h
//  Game
//
//  Created by zhouwei on 13-6-17.
//
//

#ifndef __Game__Login__
#define __Game__Login__

#include "ans/BaseObject.h"
#include "event/GBEvent.h"
#include "event/GBEventIDs.h"
#include "common/GlobalDef.h"
#include "cocos2d.h"
#include <iostream>
#include <string>
using namespace std;
using namespace cocos2d;

class Login : public BaseObject,CCObject
{
public:
    Login();
    ~Login();
    
    void onSocketLogin(GBEventConstArg& arg);
    
    //�û���½
    void setUserLogin(string account,string password);

    //�û�ע��
    void setUserRegister(const char* szAccount,const char* szPassword,int nfaceId,int nGender, int visiter);
    
    bool onEventLoginRead(CMD_Command* pCommand,void* pBuffer,WORD wDataSize);
    
    string getAccout() { return m_szAccount; }
private:
    string m_szAccount;
    string m_szPassword;
    
};
#endif /* defined(__Game__Login__) */
