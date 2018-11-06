/*
 *  platform.h
 *  test
 *
 *  Created by Aden on 14-11-20.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#pragma pack(1)

#define	BUILD_VER	0	// ��Ȩ�汾
#define PRODUCT_VER 6	// ��Ʒ�汾

// ��ڰ汾
#define INTERFACE_VERSION(cbMainVer,cbSubVer)			\
		(((BYTE)(PRODUCT_VER))<<24)+					\
		(((BYTE)(cbMainVer))<<16)+						\
		((BYTE)(cbSubVer)<<8)+							\
		(BYTE)(BUILD_VER))			

// ģ��汾
#define PROCESS_VERSION(cbMainVer,cbSubVer,cbBuildVer)  \
		(DWORD)(										\
		(((BYTE)(PRODUCT_VER))<<24)+					\
		(((BYTE)(cbMainVer))<<16)+						\
		 ((BYTE)(cbSubVer)<<8)+							\
		  (BYTE)(cbBuildVer))
		 
// ����汾
#define VERSION_FRAME			PROCESS_VERSION(7,0,3)				// ��ܰ汾
#define VERSION_PLAZA			PROCESS_VERSION(10,0,3)				// �����汾

#define VERSION_MOBILE			PROCESS_VERSION(1,0,3)				// �ֻ��汾

#define VERSION_ROOM			PROCESS_VERSION(6,0,3)				// �ֻ��汾

// �汾����
#define VERSION_EFFICACY		0									// Ч��汾
#define VERSION_FRAME_SDK		INTERFACE_VERSION(6,3)				// ��ܰ汾



#pragma pack()