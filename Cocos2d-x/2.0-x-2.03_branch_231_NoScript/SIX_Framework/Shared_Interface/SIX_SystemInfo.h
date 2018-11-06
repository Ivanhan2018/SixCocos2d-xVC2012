/*********************************************************
Name��SIX_SystemInfo
Desc��Ӳ����Ϣ��
Auth��Cool.Cat@2013-09-30
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

// ���ص����ݽṹ���ܹ�512�ֽ�(256��unsigned short int)
typedef struct _IDSECTOR
{
	// 0=������Ϣ��
	unsigned short wGenConfig;
	// 1=������
	unsigned short wNumCyls;
	// 2=����
	unsigned short wReserved;
	// 3=��ͷ��
	unsigned short wNumHeads;
	// 4=ÿ�ŵ��ֽ���
	unsigned short wBytesPerTrack;
	// 5=ÿ�����ֽ���
	unsigned short wBytesPerSector;
	// 6=ÿ�ŵ�������
	unsigned short wSectorsPerTrack;
	// 7��9=����Ԥ��
	unsigned short wVendorUnique[3];
	// 10��19=���к�
	char sSerialNumber[20];
	// 20=��������
	unsigned short wBufferType;
	// 21=�����С
	unsigned short wBufferSize;
	// 22=ECCУ���С
	unsigned short wECCSize;
	// 23��26=�̼��汾
	char sFirmwareRev[8];
	// 27��46=�ڲ��ͺ�
	char sModelNumber[40];
	// 47=����Ԥ��
	unsigned short wMoreVendorUnique;
	// 48=???
	unsigned short wDoubleWordIO;
	// 49=һ������
	struct {
		unsigned short reserved1:8;
		unsigned short DMA:1;				// 1=֧��DMA
		unsigned short LBA:1;				// 1=֧��LBA
		unsigned short DisIORDY:1;			// 1=�ɲ�ʹ��IORDY
		unsigned short IORDY:1;				// 1=֧��IORDY
		unsigned short SoftReset:1;			// 1=��ҪATA������
		unsigned short Overlap:1;			// 1=֧���ص�����
		unsigned short Queue:1;				// 1=֧���������
		unsigned short InlDMA:1;			// 1=֧�ֽ����ȡDMA
	} wCapabilities;
	// 50=����
	unsigned short wReserved1;
	// 51=PIOʱ��
	unsigned short wPIOTiming;
	// 52=DMAʱ��
	unsigned short wDMATiming;
	// 53=�����ֶ���Ч�Ա�־
	struct {
		unsigned short CHSNumber:1;			// 1=WORD 54-58��Ч
		unsigned short CycleNumber:1;		// 1=WORD 64-70��Ч
		unsigned short UnltraDMA:1;			// 1=WORD 88��Ч
		unsigned short reserved:13;
	} wFieldValidity;
	// 54=CHS��Ѱַ��������
	unsigned short wNumCurrentCyls;
	// 55=CHS��Ѱַ�Ĵ�ͷ��
	unsigned short wNumCurrentHeads;
	// 56=CHS��Ѱַÿ�ŵ�������
	unsigned short wNumCurrentSectorsPerTrack;
	// 57=CHS��Ѱַ��������(��λ)
	unsigned short wCurrentSectorsLow;
	// 58=CHS��Ѱַ��������(��λ)
	unsigned short wCurrentSectorsHigh;
	// 59=��������д�趨
	struct {
		unsigned short CurNumber:8;			// ��ǰһ���Կɶ�д������
		unsigned short Multi:1;				// 1=��ѡ���������д
		unsigned short reserved1:7;
	} wMultSectorStuff;
	// 60��61=LBA��Ѱַ��������
	unsigned long ulTotalAddressableSectors;
	// 62=���ֽ�DMA֧������
	unsigned short wSingleWordDMA;
	// 63=���ֽ�DMA֧������
	struct {
		unsigned short Mode0:1;				// 1=֧��ģʽ0 (4.17Mb/s)
		unsigned short Mode1:1;				// 1=֧��ģʽ1 (13.3Mb/s)
		unsigned short Mode2:1;				// 1=֧��ģʽ2 (16.7Mb/s)
		unsigned short Reserved1:5;
		unsigned short Mode0Sel:1;			// 1=��ѡ��ģʽ0
		unsigned short Mode1Sel:1;			// 1=��ѡ��ģʽ1
		unsigned short Mode2Sel:1;			// 1=��ѡ��ģʽ2
		unsigned short Reserved2:5;
	} wMultiWordDMA;
	// 64=�߼�PIO֧������
	struct {
		// ֧�ָ߼�POIģʽ��
		unsigned short AdvPOIModes:8;
		unsigned short reserved:8;
	} wPIOCapacity;
	// 65=���ֽ�DMA�������ڵ���Сֵ
	unsigned short wMinMultiWordDMACycle;
	// 66=���ֽ�DMA�������ڵĽ���ֵ
	unsigned short wRecMultiWordDMACycle;
	// 67=��������ʱPIO�������ڵ���Сֵ
	unsigned short wMinPIONoFlowCycle;
	// 68=��������ʱPIO�������ڵ���Сֵ
	unsigned short wMinPOIFlowCycle;
	// 69��79=����
	unsigned short wReserved69[11];
	// 80=���屾
	struct {
		unsigned short Reserved1:1;
		unsigned short ATA1:1;						// 1=֧��ATA-1
		unsigned short ATA2:1;						// 1=֧��ATA-2
		unsigned short ATA3:1;						// 1=֧��ATA-3
		unsigned short ATA4:1;						// 1=֧��ATA/ATAPI-4
		unsigned short ATA5:1;						// 1=֧��ATA/ATAPI-5
		unsigned short ATA6:1;						// 1=֧��ATA/ATAPI-6
		unsigned short ATA7:1;						// 1=֧��ATA/ATAPI-7
		unsigned short ATA8:1;						// 1=֧��ATA/ATAPI-8
		unsigned short ATA9:1;						// 1=֧��ATA/ATAPI-9
		unsigned short ATA10:1;						// 1=֧��ATA/ATAPI-10
		unsigned short ATA11:1;						// 1=֧��ATA/ATAPI-11
		unsigned short ATA12:1;						// 1=֧��ATA/ATAPI-12
		unsigned short ATA13:1;						// 1=֧��ATA/ATAPI-13
		unsigned short ATA14:1;						// 1=֧��ATA/ATAPI-14
		unsigned short Reserved2:1;
	} wMajorVersion;
	// 81=���汾
	unsigned short wMinorVersion;
	// 82��87=����
	unsigned short wReserved82[6];
	// 88=Ultra DMA֧������
	struct {
		unsigned short Mode0:1;						// 1=֧��ģʽ0 (16.7Mb/s)
		unsigned short Mode1:1;						// 1=֧��ģʽ1 (25Mb/s)
		unsigned short Mode2:1;						// 1=֧��ģʽ2 (33Mb/s)
		unsigned short Mode3:1;						// 1=֧��ģʽ3 (44Mb/s)
		unsigned short Mode4:1;						// 1=֧��ģʽ4 (66Mb/s)
		unsigned short Mode5:1;						// 1=֧��ģʽ5 (100Mb/s)
		unsigned short Mode6:1;						// 1=֧��ģʽ6 (133Mb/s)
		unsigned short Mode7:1;						// 1=֧��ģʽ7 (166Mb/s) ???
		unsigned short Mode0Sel:1;					// 1=��ѡ��ģʽ0
		unsigned short Mode1Sel:1;					// 1=��ѡ��ģʽ1
		unsigned short Mode2Sel:1;					// 1=��ѡ��ģʽ2
		unsigned short Mode3Sel:1;					// 1=��ѡ��ģʽ3
		unsigned short Mode4Sel:1;					// 1=��ѡ��ģʽ4
		unsigned short Mode5Sel:1;					// 1=��ѡ��ģʽ5
		unsigned short Mode6Sel:1;					// 1=��ѡ��ģʽ6
		unsigned short Mode7Sel:1;					// 1=��ѡ��ģʽ7
	} wUltraDMA;
	// 89��255=����
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

// HD Tuneרҵ�棺ATA     KINGSTON SV300S3 ��Ϣ
//----------------------------------------------------
//�̼��汾 :         505ABBF0
//���к� :           50026B722B01F5E0
//���� :             120.0 gB (111.8 GB)
//�����С :         ��
//������С :         512 bytes
//��׼ :             ATA8-ACS - SATA III
//֧��ģʽ :         UDMA Mode 6
//��ǰģʽ :         UDMA Mode 5
//ƽ���ٶ� :         953 MB/��
//����ת�� :         0 RPM

//S.M.A.R.T :                    ��
//48λѰַ :                     ��
//Ԥ�ȶ�ȡ :                     ��
//д�뻺�� :                     ��
//���������� :                   ��
//�豸���ø��� :                 ��
//�̼����� :                     ��
//�Զ��������� :                 ��
//��Դ���� :                     ��
//�߼���Դ���� :                 ��
//�ӿڵ�Դ���� :                 ��
//����ʱͨ�� :                   ��
//��ȫģʽ :                     ��
//SCT Tables :                   ��
//ԭ��ָ������ (NCQ) :           ��
//Trimָ�� (����ɾ��֪ͨ) :      ��

//���          : ϵͳ���� (Z:)
//����          : 99 MB
//ʣ��          : 71 MB
//ʹ��          : 28%
//�ļ�ϵͳ      : NTFS
//���к�        : FA48-3F16
//����          : 1 MB

//���          : (C:)
//����          : 51099 MB
//ʣ��          : 10448 MB
//ʹ��          : 80%
//�ļ�ϵͳ      : NTFS
//���к�        : A85D-450F
//����          : 1 MB

//���          : (D:)
//����          : 63270 MB
//ʣ��          : 13000 MB
//ʹ��          : 79%
//�ļ�ϵͳ      : NTFS
//���к�        : 7439-1345
//����          : 1 MB
//----------------------------------------------------