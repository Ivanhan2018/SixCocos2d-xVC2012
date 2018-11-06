#include "./PublicHead.h"
#include "TerminateResult.h"

CTerminateResult::CTerminateResult(void)
{
	set_class_name_flag("CTerminateResult");
}

CTerminateResult::~CTerminateResult(void)
{
}

int CTerminateResult::OnIoComplete(DWORD dwBytesTransfered)
{
	return CCompleteResult::COMPLETE_RESULT_EXIT;
}