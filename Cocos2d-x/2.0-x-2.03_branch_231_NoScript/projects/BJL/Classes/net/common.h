/*
 *  common.h
 *  stream
 *
 *  Created by WJ on 14-11-25.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#ifndef COMMON_LIB_H
#define COMMON_LIB_H

#include"common/Define.h"
//��������
bool Common_MappedBuffer(void* data, int nDataSize);

//��������
bool Common_unMappedBuffer(void* data, int nDataSize);

//������֤
bool Common_Compilation(TCHART *data);


#endif