#include "SIX_SystemInfo.h"
#ifdef WIN32
#include "Iphlpapi.h"
#endif

char g_s3Levels[1024];

#define HWD_MT_BIT         0x10000000     // EDX[28]  Bit 28 is set if HT or multi-core is supported
#define NUM_LOGICAL_BITS   0x00FF0000     // EBX[23:16] Bit 16-23 in ebx contains the number of logical
                                          // processors per physical processor when execute cpuid with 
                                          // eax set to 1
#define NUM_CORE_BITS      0xFC000000     // EAX[31:26] Bit 26-31 in eax contains the number of cores minus one
                                          // per physical processor when execute cpuid with 
                                          // eax set to 4. 


#define INITIAL_APIC_ID_BITS  0xFF000000  // EBX[31:24] Bits 24-31 (8 bits) return the 8-bit unique 
                                          // initial APIC ID for the processor this code is running on.

// Status Flag
#define SINGLE_CORE_AND_HT_ENABLED					1
#define SINGLE_CORE_AND_HT_DISABLED					2
#define SINGLE_CORE_AND_HT_NOT_CAPABLE				4
#define MULTI_CORE_AND_HT_NOT_CAPABLE				5
#define MULTI_CORE_AND_HT_ENABLED					6
#define MULTI_CORE_AND_HT_DISABLED					7
#define USER_CONFIG_ISSUE							8

int SIX_SystemInfo::getCPUInfo(char *CPUName, char *Hypotaxis, int *PhysicalCount,int *CoreCount,int *LogicalCount,int *HT,long *Frequency)
{
	int result=1;
	*Frequency = GetCPUSpeed();

	//Log->WriteToFile("*Frequency = %d",*Frequency);

	unsigned int  TotAvailLogical   = 0,  // Number of available logical CPU per CORE
				 TotAvailCore  = 0,      // Number of available cores per physical processor
                 PhysicalNum   = 0;      // Total number of physical processors

	unsigned char StatusFlag = 0; 
	//int MaxLPPerCore;
	if (CpuIDSupported() < 4)
	{ // CPUID does not report leaf 4 information
	   //printf("\nUser Warning:\n CPUID Leaf 4 is not supported or disabled. Please check  \
			 //\n BIOS and correct system configuration error if leaf 4 is disabled. \n");
		result = 2;
	}
	StatusFlag = CPUCount(&TotAvailLogical, &TotAvailCore, &PhysicalNum);
	*PhysicalCount = PhysicalNum;
	*CoreCount = TotAvailCore;
	*LogicalCount = TotAvailLogical;
	
	if( USER_CONFIG_ISSUE == StatusFlag)
	{
	//printf("User Configuration Error: Not all logical processors in the system are enabled \
	//while running this process. Please rerun this application after make corrections. \n");
	//exit(1);
		return 0;
	}

	//printf("\n----Counting Hardware MultiThreading Capabilities and Availability ---------- \n\n");
	//printf("This application displays information on three forms of hardware multithreading\n");
	//printf("capability and their availability to apps. The three forms of capabilities are:\n");
	//printf("multi-processor (MP), Multi-core (core), and HyperThreading Technology (HT).\n");
	//printf("\nHardware capability results represents the maximum number provided in hardware.\n");	
	//printf("Note, Bios/OS or experienced user can make configuration changes resulting in \n");
	//printf("less-than-full HW capabilities are available to applications.\n");
	//printf("For best result, the operator is responsible to configure the BIOS/OS such that\n");
	//printf("full hardware multi-threading capabilities are enabled.\n");
	//printf("\n---------------------------------------------------------------------------- \n\n\n");

	//printf("\nCapabilities:\n\n");

   switch(StatusFlag)
   {

   //case MULTI_CORE_AND_HT_NOT_CAPABLE:
	  // printf("\tHyper-Threading Technology: not capable  \n\tMulti-core: Yes \n\tMulti-processor: ");
	  // if (PhysicalNum > 1) printf("yes\n"); else printf("No\n");
	  // break;

   //case SINGLE_CORE_AND_HT_NOT_CAPABLE:
	  // printf("\tHyper-Threading Technology: Not capable  \n\tMulti-core: No \n\tMulti-processor: ");
	  // if (PhysicalNum > 1) printf("yes\n"); else printf("No\n");
	  // break;

   case SINGLE_CORE_AND_HT_DISABLED:
	   //printf("\tHyper-Threading Technology: Disabled  \n\tMulti-core: No \n\tMulti-processor: ");
	   //if (PhysicalNum > 1) printf("yes\n"); else printf("No\n");
	   *HT = 2;
	   break;

   case SINGLE_CORE_AND_HT_ENABLED:
	   //printf("\tHyper-Threading Technology: Enabled  \n\tMulti-core: No \n\tMulti-processor: ");
	   //if (PhysicalNum > 1) printf("yes\n"); else printf("No\n");
	   *HT = 1;
	   break;

   case MULTI_CORE_AND_HT_DISABLED:
	   //printf("\tHyper-Threading Technology: Disabled  \n\tMulti-core: Yes \n\tMulti-processor: ");
	   //if (PhysicalNum > 1) printf("yes\n"); else printf("No\n");
	   *HT = 2;
	   break;

   case MULTI_CORE_AND_HT_ENABLED:
	   //printf("\tHyper-Threading Technology: Enabled  \n\tMulti-core: Yes \n\tMulti-processor: ");
	   //if (PhysicalNum > 1) printf("yes\n"); else printf("No\n");
	   *HT = 1;
	   break;
   }

   //printf("\n\nHardware capability and its availability to applications: \n");
   //printf("\n  System wide availability: %d physical processors, %d cores, %d logical processors\n", \
	  //     PhysicalNum, TotAvailCore, TotAvailLogical);

	//MaxLPPerCore = MaxLogicalProcPerPhysicalProc() / MaxCorePerPhysicalProc() ;
	//printf("  Multi-core capabililty : %d cores per package \n", MaxCorePerPhysicalProc());
	//printf("  HT capability: %d logical processors per core \n",  MaxLPPerCore);
	//assert (PhysicalNum * MaxCorePerPhysicalProc() >= TotAvailCore);
	//assert (PhysicalNum * MaxLogicalProcPerPhysicalProc() >= TotAvailLogical);
	//if( PhysicalNum * MaxCorePerPhysicalProc() > TotAvailCore) printf("\n  Not all cores in the system are enabled for this application.\n");
	//else printf("\n  All cores in the system are enabled for this application.\n");
   
   //printf("\n\nRelationships between OS affinity mask, Initial APIC ID, and 3-level sub-IDs: \n");
   //printf("\n%s", g_s3Levels);
   sprintf(Hypotaxis,"%s",g_s3Levels);
   //printf("\n\nPress Enter To Continue\n");
  //getchar();

	GetCPUName(CPUName);

	return result;
}

//
// CpuIDSupported will return 0 if CPUID instruction is unavailable. Otherwise, it will return 
// the maximum supported standard function.
//
unsigned int SIX_SystemInfo::CpuIDSupported()
{
#ifdef WIN32
	unsigned int MaxInputValue;
// If CPUID instruction is supported

	try
	{
		MaxInputValue = 0;
		// call cpuid with eax = 0
		__asm
		{
			xor eax, eax
			cpuid
			mov MaxInputValue, eax
		}
	}
	catch (...)
	{
		return(0);                   // cpuid instruction is unavailable
	}
	return MaxInputValue;
#else
	return 0;
#endif
}


// GenuineIntel will return 0 if the processor is not a Genuine Intel Processor 
unsigned int SIX_SystemInfo::GenuineIntel()
{
#ifdef WIN32
	unsigned int VendorID[3] = {0, 0, 0};
	try    // If CPUID instruction is supported
	{
		__asm		
		{
			xor eax, eax			// call cpuid with eax = 0
        	cpuid					// Get vendor id string
			mov VendorID, ebx
			mov VendorID + 4, edx
			mov VendorID + 8, ecx
		}
	}		
	catch (...)
	{
		return(0);      		unsigned int MaxInputValue =0;
		             // cpuid instruction is unavailable
	}
	return ( (VendorID[0] == 'uneG') &&
			 (VendorID[1] == 'Ieni') &&
			 (VendorID[2] == 'letn')); 
#else
	return 0;
#endif
}

// Function returns the maximum cores per physical package. Note that the number of 
// AVAILABLE cores per physical to be used by an application might be less than this
// maximum value.
//
unsigned int SIX_SystemInfo::MaxCorePerPhysicalProc()
{
	unsigned int Regeax = 0;
#ifdef WIN32	
	if (!HWD_MTSupported()) 
		return 1;  // Single core
	__asm
	{
		xor eax, eax
		cpuid
		cmp eax, 4			// check if cpuid supports leaf 4
		jl single_core		// Single core
		mov eax, 4			
		mov ecx, 0			// start with index = 0; Leaf 4 reports
		cpuid				// at least one valid cache level
		mov Regeax, eax
		jmp multi_core

		single_core:
			xor eax, eax

		multi_core:
			
	}
#endif
	return (unsigned int)((Regeax & NUM_CORE_BITS) >> 26)+1;
}

//
// The function returns 0 when the hardware multi-threaded bit is not set.
//
unsigned int SIX_SystemInfo::HWD_MTSupported()
{
	unsigned int Regedx = 0;
#ifdef WIN32
	if ((CpuIDSupported() >= 1) && GenuineIntel())
	{
		__asm
		{
			mov eax, 1
			cpuid
			mov Regedx, edx
		}		
	}
#endif
	return (Regedx & HWD_MT_BIT);
}

// Function returns the maximum logical processors per physical package. Note that the number of 
// AVAILABLE logical processors per physical to be used by an application might be less than this
// maximum value.
unsigned int SIX_SystemInfo::MaxLogicalProcPerPhysicalProc()
{
	unsigned int Regebx = 0;
#ifdef WIN32
	if (!HWD_MTSupported()) 
		return 1;
	__asm
	{
		mov eax, 1
		cpuid
		mov Regebx, ebx
	}
#endif
	return (unsigned int) ((Regebx & NUM_LOGICAL_BITS) >> 16);
}

unsigned char SIX_SystemInfo::GetAPIC_ID()
{
	unsigned int Regebx = 0;
#ifdef WIN32
	__asm
	{
		mov eax, 1
		cpuid
		mov Regebx, ebx
	}
#endif
	return (unsigned char) ((Regebx & INITIAL_APIC_ID_BITS) >> 24);
}

// Determine the width of the bit field that can represent the value count_item. 
unsigned int SIX_SystemInfo::find_maskwidth(unsigned int CountItem)
{
	unsigned int MaskWidth,count = CountItem;
#ifdef WIN32
	__asm
	{
		mov eax, count
		mov ecx, 0
		mov MaskWidth, ecx
		dec eax
		bsr cx, ax
		jz Next
		inc cx
		mov MaskWidth, ecx
		Next:		
	}
#endif
	return MaskWidth;
}

// Extract the subset of bit field from the 8-bit value FullID.  It returns the 8-bit sub ID value
unsigned char SIX_SystemInfo::GetNzbSubID(unsigned char FullID,unsigned char MaxSubIDValue,unsigned char ShiftCount)
{
	unsigned int MaskWidth;
	unsigned char MaskBits;

	MaskWidth = find_maskwidth((unsigned int) MaxSubIDValue);
	MaskBits  = (0xff << ShiftCount) ^ 
				((unsigned char) (0xff << (ShiftCount + MaskWidth)));

	return (FullID & MaskBits);
}

unsigned char SIX_SystemInfo::CPUCount(unsigned int *TotAvailLogical,unsigned int *TotAvailCore,unsigned int *PhysicalNum)
{
	unsigned char StatusFlag = 0;
#ifdef WIN32
	unsigned int numLPEnabled = 0;
	DWORD dwAffinityMask;
	int j = 0, MaxLPPerCore;
	unsigned char apicID, PackageIDMask;
	unsigned char tblPkgID[512], tblCoreID[512], tblSMTID[512];
	char tmp[1024]={0};
	memset(tmp,0,sizeof(tmp));
	g_s3Levels[0] = 0;
	*TotAvailCore = 1;
	*PhysicalNum  = 1;

	DWORD dwProcessAffinity, dwSystemAffinity;
	GetProcessAffinityMask(GetCurrentProcess(), 
						   &dwProcessAffinity,
						   &dwSystemAffinity);
	if (dwProcessAffinity != dwSystemAffinity)  // not all CPUs are enabled
	{
		StatusFlag = USER_CONFIG_ISSUE;
		return StatusFlag;
	}
	
	// Assumwe that cores within a package have the SAME number of 
	// logical processors.  Also, values returned by
	// MaxLogicalProcPerPhysicalProc and MaxCorePerPhysicalProc do not have
	// to be power of 2.

	MaxLPPerCore = MaxLogicalProcPerPhysicalProc() / MaxCorePerPhysicalProc();
	dwAffinityMask = 1;

	while (dwAffinityMask && dwAffinityMask <= dwSystemAffinity)
	{
		if (SetThreadAffinityMask(GetCurrentThread(), dwAffinityMask))
		{
			Sleep(0);  // Ensure system to switch to the right CPU
			apicID = GetAPIC_ID();

			// Store SMT ID and core ID of each logical processor
			// Shift vlaue for SMT ID is 0
			// Shift value for core ID is the mask width for maximum logical
			// processors per core

			tblSMTID[j]  = GetNzbSubID(apicID, MaxLPPerCore, 0);
			tblCoreID[j] = GetNzbSubID(apicID, 
						   MaxCorePerPhysicalProc(),
						   (unsigned char) find_maskwidth(MaxLPPerCore));

			// Extract package ID, assume single cluster.
			// Shift value is the mask width for max Logical per package

			PackageIDMask = (unsigned char) (0xff << 
							find_maskwidth(MaxLogicalProcPerPhysicalProc()));

			tblPkgID[j] = apicID & PackageIDMask;
			//sprintf(tmp,"  AffinityMask = %d; Initial APIC = %d; Physical ID = %d, Core ID = %d,  SMT ID = %d\n",
			//	    dwAffinityMask, apicID, tblPkgID[j], tblCoreID[j], tblSMTID[j]);
			sprintf_s(tmp,1023,"%X%X ",tblPkgID[j], tblCoreID[j]);
			strcat_s(g_s3Levels, tmp);

			numLPEnabled ++;   // Number of available logical processors in the system.

		} // if

		j++;
		dwAffinityMask = 1 << j;
	} // while

    // restore the affinity setting to its original state
    SetThreadAffinityMask(GetCurrentThread(), dwProcessAffinity);
	Sleep(0);
	*TotAvailLogical = numLPEnabled;
	
	//
	// Count available cores (TotAvailCore) in the system
	//
	unsigned char CoreIDBucket[512];
	DWORD ProcessorMask, pCoreMask[512];
	unsigned int i, ProcessorNum;

	CoreIDBucket[0] = tblPkgID[0] | tblCoreID[0];
	ProcessorMask = 1;
	pCoreMask[0] = ProcessorMask;

	for (ProcessorNum = 1; ProcessorNum < numLPEnabled; ProcessorNum++)
	{
		ProcessorMask <<= 1;
		for (i = 0; i < *TotAvailCore; i++)
		{
			// Comparing bit-fields of logical processors residing in different packages
			// Assuming the bit-masks are the same on all processors in the system.
			if ((tblPkgID[ProcessorNum] | tblCoreID[ProcessorNum]) == CoreIDBucket[i])
			{
				pCoreMask[i] |= ProcessorMask;
				break;
			}

		}  // for i

		if (i == *TotAvailCore)   // did not match any bucket.  Start a new one.
		{
			CoreIDBucket[i] = tblPkgID[ProcessorNum] | tblCoreID[ProcessorNum];
			pCoreMask[i] = ProcessorMask;

			(*TotAvailCore)++;	// Number of available cores in the system

		}

	}  // for ProcessorNum


	//
	// Count physical processor (PhysicalNum) in the system
	//
	unsigned char PackageIDBucket[512];
	DWORD pPackageMask[512];

	PackageIDBucket[0] = tblPkgID[0];
	ProcessorMask = 1;
	pPackageMask[0] = ProcessorMask;

	for (ProcessorNum = 1; ProcessorNum < numLPEnabled; ProcessorNum++)
	{
		ProcessorMask <<= 1;
		for (i = 0; i < *PhysicalNum; i++)
		{
			// Comparing bit-fields of logical processors residing in different packages
			// Assuming the bit-masks are the same on all processors in the system.
			if (tblPkgID[ProcessorNum]== PackageIDBucket[i])
			{
				pPackageMask[i] |= ProcessorMask;
				break;
			}
		}  // for i

		if (i == *PhysicalNum)   // did not match any bucket.  Start a new one.
		{
			PackageIDBucket[i] = tblPkgID[ProcessorNum];
			pPackageMask[i] = ProcessorMask;

			(*PhysicalNum)++;	// Total number of physical processors in the system

		}

	}  // for ProcessorNum

//
// Check to see if the system is multi-core 
// Check if the system is hyper-threading
//
	if (*TotAvailCore > *PhysicalNum) 
	{
		// Multi-core
		if (MaxLPPerCore == 1)
			StatusFlag = MULTI_CORE_AND_HT_NOT_CAPABLE;
		else if (numLPEnabled > *TotAvailCore)
			StatusFlag = MULTI_CORE_AND_HT_ENABLED;
			else StatusFlag = MULTI_CORE_AND_HT_DISABLED;

	}
	else
	{
		// Single-core
		if (MaxLPPerCore == 1)
			StatusFlag = SINGLE_CORE_AND_HT_NOT_CAPABLE;
		else if (numLPEnabled > *TotAvailCore)
			StatusFlag = SINGLE_CORE_AND_HT_ENABLED;
			else StatusFlag = SINGLE_CORE_AND_HT_DISABLED;
	}
#endif
	return StatusFlag;
}

long SIX_SystemInfo::GetCPUTicks()
{
	volatile long time_temp = 0;
	//Log->WriteToFile("A.time_temp = %u",time_temp);
#ifdef WIN32
	__asm
	{
		rdtsc
		//_emit 0x0F
		//_emit 0x31
		mov	dword ptr [time_temp], eax
		mov	dword ptr [time_temp+4], edx
	}
#endif
	//Log->WriteToFile("B.time_temp = %u",time_temp);
	return time_temp;
}

int SIX_SystemInfo::GetCPUSpeed()
{
	//计算CPU速度(MHz)
	double speed_mhz=0.0;
#ifdef WIN32
	DWORD timeStop, timeStart;
	long t1,t2;

	timeStart=GetTickCount();

	for (;;)
	{
		timeStop = GetTickCount();
		if (timeStop - timeStart > 0)
		{
			//Log->WriteToFile("A.GetCPUSpeed");
			t1 = GetCPUTicks();
			//Log->WriteToFile("B.GetCPUSpeed");
			break;
		}
	}

	//Log->WriteToFile("C.GetCPUSpeed");

	for (;;)
	{
		timeStop = GetTickCount();
		if (timeStop - timeStart > 500)
		{
			//Log->WriteToFile("D.GetCPUSpeed");
			t2 = GetCPUTicks();
			//Log->WriteToFile("E.GetCPUSpeed");
			break;
		}
	}
	
	//Log->WriteToFile("t2 - t1 = %d - %d = %d",t2,t1,t2-t1);

	speed_mhz = speed_mhz + (t2-t1) / (1000.0 * 500.0);
#endif
	return (int)speed_mhz;
}

void SIX_SystemInfo::GetCPUName(char *str)
{
#ifdef WIN32
	char brand_string[1024]={0};
	memset(brand_string,0,sizeof(brand_string));

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx

		mov eax, 0x80000002
		cpuid
		mov dword ptr [brand_string], eax
		mov dword ptr [brand_string+4], ebx
		mov dword ptr [brand_string+8], ecx
		mov dword ptr [brand_string+12], edx

		mov eax, 0x80000003
		cpuid
		mov dword ptr [brand_string+16], eax
		mov dword ptr [brand_string+20], ebx
		mov dword ptr [brand_string+24], ecx
		mov dword ptr [brand_string+28], edx

		mov eax, 0x80000004
		cpuid
		mov dword ptr [brand_string+32], eax
		mov dword ptr [brand_string+36], ebx
		mov dword ptr [brand_string+40], ecx
		mov dword ptr [brand_string+44], edx

		pop edx
		pop ecx
		pop ebx
		pop eax
	}

	sprintf_s(str,1023,"%s",brand_string);
#endif
}

int SIX_SystemInfo::getMemInfo(double *ullTotalPhys,double *ullAvailPhys,double *ullTotalVirtual,double *ullAvailVirtual,int *dwMemoryLoad)
{
#ifdef WIN32
	// 内存信息
	MEMORYSTATUSEX memStatus;

	memset(&memStatus,0,sizeof(memStatus));
	memStatus.dwLength=sizeof(MEMORYSTATUSEX);

	if (!GlobalMemoryStatusEx(&memStatus))
		return 0;

	// 物理内存总数(Gbyte)
	*ullTotalPhys		= (double)(memStatus.ullTotalPhys)/1024.0/1024.0;
	// 可用物理内存(Gbyte)
	*ullAvailPhys		= (double)(memStatus.ullAvailPhys)/1024.0/1024.0;
	// 虚拟内存总数(Gbyte)
	*ullTotalVirtual	= (double)(memStatus.ullTotalVirtual)/1024.0/1024.0;
	// 可用虚拟内存(Gbyte)
	*ullAvailVirtual	= (double)(memStatus.ullAvailVirtual)/1024.0/1024.0;
	// 物理内存使用率(1～100)
	*dwMemoryLoad		= memStatus.dwMemoryLoad;

	return 1;
#else
	return 0;
#endif
}

int SIX_SystemInfo::getHDInfoEachVolume(MP *mp)
{
#ifdef WIN32
	TCHAR format[1024] = {0};
	_ULARGE_INTEGER result_freespace,result_totalspace,result_g;
	int space_total,space_free,space_count=0;

	// A～Z
	for(int i=0x41;i<=0x5A;i++)
	{
#ifdef UNICODE
		swprintf(format,L"%c:",i);
#else
		sprintf_s(format,MAX_PATH-1,/*%c:*/XorStr<0x9B,4,0x3F1347C6>("\xBE\xFF\xA7"+0x3F1347C6).s,i);
#endif

		if(GetDriveType((LPCTSTR)format)==DRIVE_FIXED)
		{
			if (!GetDiskFreeSpaceEx(format,&result_freespace,&result_totalspace,&result_g))
				return -1;
			
			space_total = (int)(result_totalspace.QuadPart/1024.0f/1024.0f);
			space_free = (int)(result_freespace.QuadPart/1024.0f/1024.0f);

			TCHAR Volumelabel[MAX_PATH] = {0};
			DWORD SerialNumber = 0;
			DWORD MaxCLength = 0;
			DWORD FileSysFlag = 0;
			TCHAR FileSysName[MAX_PATH] = {0};

			if (GetVolumeInformation(format,Volumelabel,MAX_PATH-1,&SerialNumber,&MaxCLength,&FileSysFlag,FileSysName,MAX_PATH-1))
			{
				//SIXLog("--------------------------------");
				//SIXLog("Volumelabel=%s",SIX_Utility::GetInstance()->UnicodeToUtf8(Volumelabel).c_str());
				//SIXLog("SerialNumber=%08X",SerialNumber);
				//SIXLog("MaxCLength=%d",MaxCLength);
				//SIXLog("FileSysFlag=%08X",FileSysFlag);
				//SIXLog("FileSysName=%s",SIX_Utility::GetInstance()->UnicodeToUtf8(FileSysName).c_str());
			}

#ifdef UNICODE
			swprintf_s(format,1023,L"%s%.2f/%.2f/%08X",format,(float)(space_total/1024.0f),(float)(space_free/1024.0f),SerialNumber);
			mp->push_back(SIX_Utility::GetInstance()->UnicodeToUtf8(format));
#else
			sprintf_s(format,1023,/*%s%.2f/%.2f/%08X*/XorStr<0x5C,17,0x9D5E3E25>("\x79\x2E\x7B\x71\x52\x07\x4D\x46\x4A\x57\x00\x48\x4D\x59\x52\x33"+0x9D5E3E25).s,format,(float)(space_total/1024.0f),(float)(space_free/1024.0),SerialNumber);
			mp->push_back(format);
#endif
			space_count++;
		}
	}

	if (!space_count)
		return 0;

	return 1;
#else
	return 0;
#endif
}

int SIX_SystemInfo::getHDInfo(char *SerialNumber)
{
#ifdef WIN32
	IDSECTOR IdSector;
	if (!ReadDriveInfoNT(&IdSector))
		return 0;
	memcpy(SerialNumber,IdSector.sSerialNumber,sizeof(IdSector.sSerialNumber));
	return 1;
#else
	return 0;
#endif
}

#ifdef WIN32
// 高低位置换且移除左右任意一边的空格
// Cool.Cat
void SIX_SystemInfo::ReverseByte(char *pBuffer,int len)
{
	char ch;
	int i;

	// 高低位交换
	for(i=0;i<len;i+=2)
	{
		ch = pBuffer[i];
		pBuffer[i] = pBuffer[i+1];
		pBuffer[i+1] = ch;
	}

	// 如果是右对齐，计算左边空格位数
	i=0;
	while(i<len && pBuffer[i]==' ') 
		i++;
	// 移动到左边
	memmove(pBuffer,&pBuffer[i],len-i);
	if (i>0)
	{
		// 右边剩余部分移除掉
		pBuffer[len-i] = '\0';
	}
	else
	{
		// 去掉右边的空格
		i = len - 1;
		while(i>=0 && pBuffer[i]==' ')
		{
			pBuffer[i] = '\0';
			i--;
		}
	}
}

HANDLE SIX_SystemInfo::OpenDevice(LPCTSTR deviceName)
{
	return CreateFile(deviceName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);
}

// 发送查询命令到设备
BOOL SIX_SystemInfo::QueryDevice(HANDLE hPhysicalDriveIOCTL,PSENDCMDINPARAMS pSCIP,PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,PDWORD lpcbBytesReturned)
{
	// Set up data structures for IDENTIFY command.
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
	pSCIP->irDriveRegs.bFeaturesReg = 0;
	pSCIP->irDriveRegs.bSectorCountReg = 1;
	pSCIP->irDriveRegs.bSectorNumberReg = 1;
	pSCIP->irDriveRegs.bCylLowReg = 0;
	pSCIP->irDriveRegs.bCylHighReg = 0;

	// Compute the drive number.
	pSCIP->irDriveRegs.bDriveHeadReg = 0xA0|((bDriveNum&1)<<4);

	// The command can either be IDE identify or ATAPI identify.
	pSCIP->irDriveRegs.bCommandReg = bIDCmd;
	pSCIP->bDriveNumber = bDriveNum;
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;

	return (DeviceIoControl(hPhysicalDriveIOCTL,DFP_RECEIVE_DRIVE_DATA,(void*)pSCIP,sizeof(SENDCMDINPARAMS)-1,(void*)pSCOP,sizeof(SENDCMDOUTPARAMS)+IDENTIFY_BUFFER_SIZE-1,lpcbBytesReturned,0));
}

bool SIX_SystemInfo::ReadDriveInfoNT(PIDSECTOR pIdSector,int drive)
{
	bool done = false;
	TCHAR driveName[MAX_PATH] = {0};
	#ifdef UNICODE
	swprintf_s(driveName,MAX_PATH-1,L"\\\\.\\PhysicalDrive%d",drive);
	#else
	sprintf_s(driveName,MAX_PATH-1,/*\\\\.\\PhysicalDrive%d*/XorStr<0x1C,20,0xB6B93175>("\x40\x41\x30\x43\x70\x49\x5B\x50\x4D\x46\x47\x4B\x6C\x5B\x43\x5D\x49\x08\x4A"+0xB6B93175).s,drive);
	#endif

	// 尝试以共享读写的方式打开已存在的设备
	HANDLE hDevice = OpenDevice(driveName);

	if (hDevice==INVALID_HANDLE_VALUE)
		return done;

	// 查询设备版本
	GETVERSIONOUTPARAMS Version;
	memset(&Version,0,sizeof(Version));
	unsigned long cbBytes = 0;

	if (DeviceIoControl(hDevice,DFP_GET_VERSION,0,0,&Version,sizeof(Version),&cbBytes,0))
	{
		//SIXLog("DeviceIoControl.Version[%02X-%02X-%02X-%X-%X]",
		//	Version.bIDEDeviceMap,
		//	Version.bVersion,
		//	Version.bRevision,
		//	Version.fCapabilities,
		//	Version.dwReserved);
	}

	if (Version.bIDEDeviceMap==0)
	{
		SIXLog("IDE/ATAPI.Nil");
		CloseHandle(hDevice);
		return done;
	}

	// IDE/ATAPI

	// 输入数据结构指针
	SENDCMDINPARAMS scip;
	memset(&scip,0,sizeof(scip));

	// 输出数据结构指针
	unsigned char IdOutCmd [sizeof(SENDCMDOUTPARAMS)+IDENTIFY_BUFFER_SIZE-1];
	memset(&IdOutCmd,0,sizeof(IdOutCmd));

	unsigned char bIDCmd = (Version.bIDEDeviceMap>>drive&0x10)?IDE_ATAPI_IDENTIFY:IDE_ATA_IDENTIFY;

	if (QueryDevice(hDevice,&scip,(PSENDCMDOUTPARAMS)&IdOutCmd,(unsigned char)bIDCmd,(unsigned char)drive,&cbBytes))
	{
		unsigned short *pFakeSector = (unsigned short *)((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer;
		memcpy(pIdSector,(PIDSECTOR)pFakeSector,sizeof(IDSECTOR));

		// Win下还要再翻转下字节顺序才行
		// Cool.Cat
		ReverseByte(pIdSector->sSerialNumber,20);

		done = true;
	}

	CloseHandle(hDevice);

	return done;
}
#endif

int SIX_SystemInfo::getOSInfo(char *OSinfo,char *Verinfo,char *Buildinfo,char *Packinfo)
{
#ifdef WIN32
	OSVERSIONINFO versionInfo;

	versionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);

	if (!::GetVersionEx (&versionInfo)) 
		return 0;
	
	if (versionInfo.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
	{
		if (versionInfo.dwMajorVersion == 4) 
		{
			if (versionInfo.dwMinorVersion==0)
				sprintf_s(OSinfo,64,/*Windows 95*/XorStr<0xA0,11,0x1AF96A1F>("\xF7\xC8\xCC\xC7\xCB\xD2\xD5\x87\x91\x9C"+0x1AF96A1F).s);
			else if (versionInfo.dwMinorVersion==10)
				sprintf_s(OSinfo,64,/*Windows 98*/XorStr<0x7A,11,0x24373A2C>("\x2D\x12\x12\x19\x11\x08\xF3\xA1\xBB\xBB"+0x24373A2C).s);
			else if (versionInfo.dwMinorVersion==90)
				sprintf_s(OSinfo,64,/*Windows Me*/XorStr<0xF9,11,0xEEC58DF8>("\xAE\x93\x95\x98\x92\x89\x8C\x20\x4C\x67"+0xEEC58DF8).s);
		}
	}
	else if (versionInfo.dwPlatformId==VER_PLATFORM_WIN32_NT)
	{
		if (versionInfo.dwMajorVersion==3)
			sprintf_s(OSinfo,64,/*Windows NT 3.51*/XorStr<0xC8,16,0x5A25F5E1>("\x9F\xA0\xA4\xAF\xA3\xBA\xBD\xEF\x9E\x85\xF2\xE0\xFA\xE0\xE7"+0x5A25F5E1).s);
		else if (versionInfo.dwMajorVersion==4)
			sprintf_s(OSinfo,64,/*Windows NT 4.0*/XorStr<0x6E,15,0xAED07559>("\x39\x06\x1E\x15\x1D\x04\x07\x55\x38\x23\x58\x4D\x54\x4B"+0xAED07559).s);
		else if (versionInfo.dwMajorVersion==5 && versionInfo.dwMinorVersion==0)
			sprintf_s(OSinfo,64,/*Windows 2000*/XorStr<0xB2,13,0xBD2CA1A7>("\xE5\xDA\xDA\xD1\xD9\xC0\xCB\x99\x88\x8B\x8C\x8D"+0xBD2CA1A7).s);
		else
		{
			LONG result=0;

			HKEY hKey;

#ifdef UNICODE
			result = ::RegOpenKeyEx (HKEY_LOCAL_MACHINE,
				L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
				0, KEY_QUERY_VALUE, &hKey);
#else
			result = ::RegOpenKeyEx (HKEY_LOCAL_MACHINE,
				/*SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion*/XorStr<0xE6,45,0xF141F12C>("\xB5\xA8\xAE\xBD\xBD\xAA\xBE\xA8\xB2\xA2\x99\x92\x80\x9C\x87\x9A\x90\x83\xA4\xAE\x93\x95\x98\x92\x89\x8C\x20\x4F\x56\x5F\x47\x70\x74\x75\x6D\x67\x7E\x5D\x69\x7F\x7D\x66\x7F\x7F"+0xF141F12C).s,
				0, KEY_QUERY_VALUE, &hKey);
#endif

			if (result != ERROR_SUCCESS) 
				return 0;

			TCHAR data [64];
			DWORD dataSize;

			memset(&data,0,sizeof(data));

			dataSize = sizeof (data);

#ifdef UNICODE
			result = ::RegQueryValueEx (hKey, 
				L"ProductName", 
				0, 0,(LPBYTE) data, &dataSize);
#else
			result = ::RegQueryValueEx (hKey, 
				/*ProductName*/XorStr<0xFC,12,0xD43BE633>("\xAC\x8F\x91\x9B\x75\x62\x76\x4D\x65\x68\x63"+0xD43BE633).s, 
				0, 0,(LPBYTE) data, &dataSize);
#endif

			if (result != ERROR_SUCCESS) 
			{
				RegCloseKey(hKey);
				SetLastError(result);
				return 0;
			}

			sprintf_s(OSinfo,64,"%s",data);

			memset(&data,0,sizeof(data));

			dataSize = sizeof (data);

#ifdef UNICODE
			result = ::RegQueryValueEx (hKey, 
				L"CurrentVersion",
				0, 0,(LPBYTE) data, &dataSize);
#else
			result = ::RegQueryValueEx (hKey, 
				/*CurrentVersion*/XorStr<0xD4,15,0xFC826218>("\x97\xA0\xA4\xA5\xBD\xB7\xAE\x8D\xB9\xAF\xAD\xB6\x8F\x8F"+0xFC826218).s,
				0, 0,(LPBYTE) data, &dataSize);
#endif

			sprintf_s(Verinfo,32,"%s",data);

			memset(&data,0,sizeof(data));

			dataSize = sizeof (data);

#ifdef UNICODE
			result = ::RegQueryValueEx (hKey,
				L"CurrentBuildNumber", 
				0, 0,(LPBYTE) data, &dataSize);
#else
			result = ::RegQueryValueEx (hKey,
				/*CurrentBuildNumber*/XorStr<0x37,19,0x6599F85D>("\x74\x4D\x4B\x48\x5E\x52\x49\x7C\x4A\x29\x2D\x26\x0D\x31\x28\x24\x22\x3A"+0x6599F85D).s, 
				0, 0,(LPBYTE) data, &dataSize);
#endif

			sprintf_s(Buildinfo,32,"%s",data);

			memset(&data,0,sizeof(data));

			dataSize = sizeof (data);

#ifdef UNICODE
			result = ::RegQueryValueEx (hKey, 
				L"CSDVersion",
				0, 0,(LPBYTE) data, &dataSize);
#else
			result = ::RegQueryValueEx (hKey, 
				/*CSDVersion*/XorStr<0x00,11,0xE637AEBC>("\x43\x52\x46\x55\x61\x77\x75\x6E\x67\x67"+0xE637AEBC).s,
				0, 0,(LPBYTE) data, &dataSize);
#endif

			sprintf_s(Packinfo,32,"%s",data);

			RegCloseKey(hKey);
		}
	}
	else if (versionInfo.dwPlatformId==VER_PLATFORM_WIN32s)
	{
		sprintf_s(OSinfo,64,/*Windows 3.1*/XorStr<0x2C,12,0x7B8E467A>("\x7B\x44\x40\x4B\x5F\x46\x41\x13\x07\x1B\x07"+0x7B8E467A).s);
	}

	return 1;
#else
	return 0;
#endif
}

int SIX_SystemInfo::getAdapter(MP *mp,bool strmode)
{
#ifdef WIN32
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;

	pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
	}
	
	if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
	{
		pAdapter = pAdapterInfo;

		int pos=0;

		char rdata[256] = {0};

		while (pAdapter)
		{
			if (strmode)
			{
				sprintf_s(rdata,255,/*%s,%s*/XorStr<0xF5,6,0x03481BF0>("\xD0\x85\xDB\xDD\x8A"+0x03481BF0).s,
					pAdapter->Description,
					pAdapter->IpAddressList.IpAddress.String);
			}
			else
			{
				sprintf_s(rdata,255,/*%s,%02X%02X%02X%02X%02X%02X*/XorStr<0xE6,28,0x7F78ED5D>("\xC3\x94\xC4\xCC\xDA\xD9\xB4\xC8\xDE\xDD\xA8\xD4\xC2\xC1\xAC\xD0\xC6\xC5\xA0\xDC\xCA\xC9\xA4\xD8\xCE\xCD\x58"+0x7F78ED5D).s,
				pAdapter->Description,
				pAdapter->Address[0],pAdapter->Address[1],pAdapter->Address[2],
				pAdapter->Address[3],pAdapter->Address[4],pAdapter->Address[5]);
			}

			mp->push_back(rdata);

			//tt.Format("\tAdapter Name: \t%s\n\tAdapter Desc: \t%s\n\tAdapter Addr: \t%ld\n\tPhysical Address:%02X-%02X-%02X-%02X-%02X-%02X\n\tIP Address: \t%s\n\tIP Mask: \t%s\n\tGateway: \t%s\n\t***\n",
			//	pAdapter->AdapterName,
			//	pAdapter->Description,
			//	pAdapter->Address,
			//	pAdapter->Address[0],
			//	pAdapter->Address[1],
			//	pAdapter->Address[2],
			//	pAdapter->Address[3],
			//	pAdapter->Address[4],
			//	pAdapter->Address[5],
			//	pAdapter->IpAddressList.IpAddress.String,
			//	pAdapter->IpAddressList.IpMask.String,
			//	pAdapter->GatewayList.IpAddress.String
			//	);

			//AfxMessageBox(tt);
			//WriteDesc(tt);

			//if (pAdapter->DhcpEnabled) 
			//{
			//	tt.Format("\tDHCP Enabled: Yes\n\t\tDHCP Server: \t%s\n\tLease Obtained: %ld\n",
			//		pAdapter->DhcpServer.IpAddress.String,
			//		pAdapter->LeaseObtained
			//		);
			//	WriteDesc(tt);
			//}
			//else
			//	WriteDesc("\tDHCP Enabled: No\n");

			//if (pAdapter->HaveWins)
			//{
			//	tt.Format("\tHave Wins: Yes\n\t\tPrimary Wins Server: \t%s\n\t\tSecondary Wins Server: \t%s\n",
			//		pAdapter->PrimaryWinsServer.IpAddress.String,
			//		pAdapter->SecondaryWinsServer.IpAddress.String
			//		);
			//	WriteDesc(tt);
			//}
			//else
			//	WriteDesc("\tHave Wins: No\n");

			pAdapter = pAdapter->Next;

			pos++;
		}

		free(pAdapterInfo);
	}
	else 
		return 0;

	return 1;
#else
	return 0;
#endif
}

void SIX_SystemInfo::getDeviceInfo(char *info)
{
#ifdef WIN32
	char SerialNumber[32] = {0};
	memset(&SerialNumber,0,sizeof(SerialNumber));
	SIX_SystemInfo pSysInfo;
	if (pSysInfo.getHDInfo(SerialNumber))
	{
		memcpy(info,SerialNumber,strlen(SerialNumber));
	}
#else
	CCString *pIEMI = CCString::createWithFormat("%s",SIX_CCJNIHelper::GetInstance()->getIMEIJNI());
	memcpy(info,pIEMI->getCString(),pIEMI->length());
#endif
	SIXLog("getDeviceInfo[%s]",info);
}