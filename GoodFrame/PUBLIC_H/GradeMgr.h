/*
等级管理
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

	// 添加等级
	void AddGrade(CMD_GradeInfo *pGradeList, int iDataLen);
	
	// 查找等级信息
	CMD_GradeInfo* FindGradeInfoFromGradeId(int iGradeId);

	// 经验值查等级ID
	CMD_GradeInfo* FindGradeInfoFromExp(int iExp);

	// 排序
	void SortGrade();

private:
	std::vector<CMD_GradeInfo> m_vecGradeList;

};

#endif