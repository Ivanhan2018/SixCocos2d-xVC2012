/*
�ȼ�����
*/
#ifndef GRADE_MGR_H
#define GRADE_MGR_H

#include <vector>
#include "GameSkeletonID.h"
#include <math.h>

class GradeMgr
{
public:
	GradeMgr();
	~GradeMgr();

	// ��ӵȼ�
	void AddGrade(CMD_GradeInfo *pGradeList, int iDataLen);
	
	// ���ҵȼ���Ϣ
	CMD_GradeInfo* FindGradeInfoFromGradeId(int iGradeId);

	// ����ֵ��ȼ�ID
	CMD_GradeInfo* FindGradeInfoFromExp(int iExp);

	// ����
	void SortGrade();

private:
	std::vector<CMD_GradeInfo> m_vecGradeList;

};

#endif