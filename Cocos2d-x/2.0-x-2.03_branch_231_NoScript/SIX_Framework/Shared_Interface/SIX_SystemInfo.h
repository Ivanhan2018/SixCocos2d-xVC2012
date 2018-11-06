/*********************************************************
Name：SIX_SystemInfo
Desc：硬件信息类
Auth：Cool.Cat@2013-09-30
**********************************************************/
#pragma once
#include <xorstr.h>
#include <SIX_Typedef.h>
#include <SIX_CCJNIHelper.h>
#include <vector>
using namespace std;

#ifdef WIN32
#define	DFP_GET_VERSION				0x74080
#define	DFP_RECEIVE_DRIVE_DATA		0x7c088
#define	IDE_ATAPI_IDENTIFY			0xA1
#define	IDE_ATA_IDENTIFY			0xEC

#pragma pack(push)
#pragma pack(1)
typedef struct _GETVERSIONOUTPARAMS
{
	// Binary driver version.
	unsigned char bVersion;
	// Binary driver revision.
	unsigned char bRevision;
	// Not used.
	unsigned char bReserved;
	// Bit map of IDE devices.
	unsigned char bIDEDeviceMap;
	// Bit mask of driver capabilities.
	unsigned long fCapabilities;
	// For future use.
	unsigned long dwReserved[4];
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;

// 返回的数据结构，总共512字节(256个unsigned short int)
typedef struct _IDSECTOR
{
	// 0=基本信息字
	unsigned short wGenConfig;
	// 1=柱面数
	unsigned short wNumCyls;
	// 2=保留
	unsigned short wReserved;
	// 3=磁头数
	unsigned short wNumHeads;
	// 4=每磁道字节数
	unsigned short wBytesPerTrack;
	// 5=每扇区字节数
	unsigned short wBytesPerSector;
	// 6=每磁道扇区数
	unsigned short wSectorsPerTrack;
	// 7～9=厂家预留
	unsigned short wVendorUnique[3];
	// 10～19=序列号
	char sSerialNumber[20];
	// 20=缓冲类型
	unsigned short wBufferType;
	// 21=缓冲大小
	unsigned short wBufferSize;
	// 22=ECC校验大小
	unsigned short wECCSize;
	// 23～26=固件版本
	char sFirmwareRev[8];
	// 27～46=内部型号
	char sModelNumber[40];
	// 47=厂家预留
	unsigned short wMoreVendorUnique;
	// 48=???
	unsigned short wDoubleWordIO;
	// 49=一般能力
	struct {
		unsigned short reserved1:8;
		unsigned short DMA:1;				// 1=支持DMA
		unsigned short LBA:1;				// 1=支持LBA
		unsigned short DisIORDY:1;			// 1=可不使用IORDY
		unsigned short IORDY:1;				// 1=支持IORDY
		unsigned short SoftReset:1;			// 1=需要ATA软启动
		unsigned short Overlap:1;			// 1=支持重叠操作
		unsigned short Queue:1;				// 1=支持命令队列
		unsigned short InlDMA:1;			// 1=支持交叉存取DMA
	} wCapabilities;
	// 50=保留
	unsigned short wReserved1;
	// 51=PIO时序
	unsigned short wPIOTiming;
	// 52=DMA时序
	unsigned short wDMATiming;
	// 53=后续字段有效性标志
	struct {
		unsigned short CHSNumber:1;			// 1=WORD 54-58有效
		unsigned short CycleNumber:1;		// 1=WORD 64-70有效
		unsigned short UnltraDMA:1;			// 1=WORD 88有效
		unsigned short reserved:13;
	} wFieldValidity;
	// 54=CHS可寻址的柱面数
	unsigned short wNumCurrentCyls;
	// 55=CHS可寻址的磁头数
	unsigned short wNumCurrentHeads;
	// 56=CHS可寻址每磁道扇区数
	unsigned short wNumCurrentSectorsPerTrack;
	// 57=CHS可寻址的扇区数(低位)
	unsigned short wCurrentSectorsLow;
	// 58=CHS可寻址的扇区数(高位)
	unsigned short wCurrentSectorsHigh;
	// 59=多扇区读写设定
	struct {
		unsigned short CurNumber:8;			// 当前一次性可读写扇区数
		unsigned short Multi:1;				// 1=已选择多扇区读写
		unsigned short reserved1:7;
	} wMultSectorStuff;
	// 60～61=LBA可寻址的扇区数
	unsigned long ulTotalAddressableSectors;
	// 62=单字节DMA支持能力
	unsigned short wSingleWordDMA;
	// 63=多字节DMA支持能力
	struct {
		unsigned short Mode0:1;				// 1=支持模式0 (4.17Mb/s)
		unsigned short Mode1:1;				// 1=支持模式1 (13.3Mb/s)
		unsigned short Mode2:1;				// 1=支持模式2 (16.7Mb/s)
		unsigned short Reserved1:5;
		unsigned short Mode0Sel:1;			// 1=已选择模式0
		unsigned short Mode1Sel:1;			// 1=已选择模式1
		unsigned short Mode2Sel:1;			// 1=已选择模式2
		unsigned short Reserved2:5;
	} wMultiWordDMA;
	// 64=高级PIO支持能力
	struct {
		// 支持高级POI模式数
		unsigned short AdvPOIModes:8;
		unsigned short reserved:8;
	} wPIOCapacity;
	// 65=多字节DMA传输周期的最小值
	unsigned short wMinMultiWordDMACycle;
	// 66=多字节DMA传输周期的建议值
	unsigned short wRecMultiWordDMACycle;
	// 67=无流控制时PIO传输周期的最小值
	unsigned short wMinPIONoFlowCycle;
	// 68=有流控制时PIO传输周期的最小值
	unsigned short wMinPOIFlowCycle;
	// 69～79=保留
	unsigned short wReserved69[11];
	// 80=主板本
	struct {
		unsigned short Reserved1:1;
		unsigned short ATA1:1;						// 1=支持ATA-1
		unsigned short ATA2:1;						// 1=支持ATA-2
		unsigned short ATA3:1;						// 1=支持ATA-3
		unsigned short ATA4:1;						// 1=支持ATA/ATAPI-4
		unsigned short ATA5:1;						// 1=支持ATA/ATAPI-5
		unsigned short ATA6:1;						// 1=支持ATA/ATAPI-6
		unsigned short ATA7:1;						// 1=支持ATA/ATAPI-7
		unsigned short ATA8:1;						// 1=支持ATA/ATAPI-8
		unsigned short ATA9:1;						// 1=支持ATA/ATAPI-9
		unsigned short ATA10:1;						// 1=支持ATA/ATAPI-10
		unsigned short ATA11:1;						// 1=支持ATA/ATAPI-11
		unsigned short ATA12:1;						// 1=支持ATA/ATAPI-12
		unsigned short ATA13:1;						// 1=支持ATA/ATAPI-13
		unsigned short ATA14:1;						// 1=支持ATA/ATAPI-14
		unsigned short Reserved2:1;
	} wMajorVersion;
	// 81=副版本
	unsigned short wMinorVersion;
	// 82～87=保留
	unsigned short wReserved82[6];
	// 88=Ultra DMA支持能力
	struct {
		unsigned short Mode0:1;						// 1=支持模式0 (16.7Mb/s)
		unsigned short Mode1:1;						// 1=支持模式1 (25Mb/s)
		unsigned short Mode2:1;						// 1=支持模式2 (33Mb/s)
		unsigned short Mode3:1;						// 1=支持模式3 (44Mb/s)
		unsigned short Mode4:1;						// 1=支持模式4 (66Mb/s)
		unsigned short Mode5:1;						// 1=支持模式5 (100Mb/s)
		unsigned short Mode6:1;						// 1=支持模式6 (133Mb/s)
		unsigned short Mode7:1;						// 1=支持模式7 (166Mb/s) ???
		unsigned short Mode0Sel:1;					// 1=已选择模式0
		unsigned short Mode1Sel:1;					// 1=已选择模式1
		unsigned short Mode2Sel:1;					// 1=已选择模式2
		unsigned short Mode3Sel:1;					// 1=已选择模式3
		unsigned short Mode4Sel:1;					// 1=已选择模式4
		unsigned short Mode5Sel:1;					// 1=已选择模式5
		unsigned short Mode6Sel:1;					// 1=已选择模式6
		unsigned short Mode7Sel:1;					// 1=已选择模式7
	} wUltraDMA;
	// 89～255=保留
	unsigned short wReserved89[167];
} IDSECTOR, *PIDSECTOR;
#pragma pack(pop)
#endif

class SIX_SystemInfo:public TSingleton<SIX_SystemInfo>{
public:
	static unsigned int CpuIDSupported();
	static unsigned int GenuineIntel();
	static unsigned int MaxCorePerPhysicalProc();
	static unsigned int HWD_MTSupported();
	static unsigned int MaxLogicalProcPerPhysicalProc();
	static unsigned char GetAPIC_ID();
	static unsigned int find_maskwidth(unsigned int CountItem);
	static unsigned char GetNzbSubID(unsigned char FullID,unsigned char MaxSubIDValue,unsigned char ShiftCount);
	static unsigned char CPUCount(unsigned int *TotAvailLogical,unsigned int *TotAvailCore,unsigned int *PhysicalNum);
	static long GetCPUTicks();
	static int GetCPUSpeed();
	static void GetCPUName(char *str);

	static int getCPUInfo(char *CPUName, char *Hypotaxis, int *PhysicalCount,int *CoreCount,int *LogicalCount,int *HT,long *Frequency);
	static int getMemInfo(double *ullTotalPhys,double *ullAvailPhys,double *ullTotalVirtual,double *ullAvailVirtual,int *dwMemoryLoad);
	static int getHDInfoEachVolume(MP *mp);
	static int getHDInfo(char *SerialNumber);
	static int getOSInfo(char *OSinfo,char *Verinfo,char *Buildinfo,char *Packinfo);
	static int getAdapter(MP *mp,bool strmode=false);

	static void getDeviceInfo(char *info);
private:
#ifdef WIN32
	static void ReverseByte(char *pBuffer,int);
	static HANDLE OpenDevice(LPCTSTR);
	static BOOL QueryDevice(HANDLE hPhysicalDriveIOCTL,PSENDCMDINPARAMS pSCIP,PSENDCMDOUTPARAMS pSCOP,BYTE bIDCmd,BYTE bDriveNum,PDWORD lpcbBytesReturned);
	static bool ReadDriveInfoNT(PIDSECTOR pIdSector,int drive=0);
#endif
};

// HD Tune专业版：ATA     KINGSTON SV300S3 信息
//----------------------------------------------------
//固件版本 :         505ABBF0
//序列号 :           50026B722B01F5E0
//容量 :             120.0 gB (111.8 GB)
//缓存大小 :         无
//扇区大小 :         512 bytes
//标准 :             ATA8-ACS - SATA III
//支持模式 :         UDMA Mode 6
//当前模式 :         UDMA Mode 5
//平均速度 :         953 MB/秒
//磁盘转速 :         0 RPM

//S.M.A.R.T :                    是
//48位寻址 :                     是
//预先读取 :                     是
//写入缓存 :                     是
//主保护区域 :                   是
//设备配置覆盖 :                 否
//固件升级 :                     是
//自动噪音管理 :                 否
//电源管理 :                     是
//高级电源管理 :                 是
//接口电源管理 :                 是
//待机时通电 :                   是
//安全模式 :                     是
//SCT Tables :                   是
//原生指令序列 (NCQ) :           是
//Trim指令 (禁用删除通知) :      是

//卷标          : 系统保留 (Z:)
//容量          : 99 MB
//剩余          : 71 MB
//使用          : 28%
//文件系统      : NTFS
//序列号        : FA48-3F16
//对齐          : 1 MB

//卷标          : (C:)
//容量          : 51099 MB
//剩余          : 10448 MB
//使用          : 80%
//文件系统      : NTFS
//序列号        : A85D-450F
//对齐          : 1 MB

//卷标          : (D:)
//容量          : 63270 MB
//剩余          : 13000 MB
//使用          : 79%
//文件系统      : NTFS
//序列号        : 7439-1345
//对齐          : 1 MB
//----------------------------------------------------