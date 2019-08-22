#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <assert.h>

#import "c:\\program files\\common files\\system\\ado\\msado15.dll" no_namespace rename("EOF","adoEOF")//避免与文件的结束符号混淆，将EOF改为adoEOF

int main(int argc, char* argv[])
{
	::CoInitialize(NULL);///初始化COM库
	_ConnectionPtr m_pConnection;
	HRESULT hr=m_pConnection.CreateInstance("ADODB.Connection");
	assert(hr==S_OK);
    
	try
	{
		hr=m_pConnection->Open("Driver={SQL Server};Server=127.0.0.1,1433;Database=luckmedb;UID=sa;PWD=123456","","",adModeUnknown);
		assert(hr==S_OK);

		_variant_t _vRes;
		char sz[200]="EXEC b_get_UserDetail 'test2233'";
  
		_RecordsetPtr rs=m_pConnection->Execute((_bstr_t)sz,&_vRes,adCmdText);
		_variant_t vt=rs->GetCollect((_variant_t)((long)0));
		printf("%s\n",(char *)(_bstr_t)rs->GetCollect((_variant_t)((long)0)));
	}
	catch(_com_error e)
	{
		//处理错误
	}
	

	m_pConnection->Close();
	CoUninitialize();

	getchar();
	return 0;
}
