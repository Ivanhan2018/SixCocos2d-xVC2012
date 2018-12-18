#if !defined(ALU_H)
#define ALU_H

#define			OF			0X0800
#define			DF			0X0400
#define			IF			0X0200
#define			TF			0X0100
#define			SF			0X0080
#define			ZF			0X0040
#define			AF			0X0010
#define			PF			0X0004
#define			CF			0X0001

//	 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0   
//	+-----------------------------------------------+
//	|  |  |  |  |OF|DF|IF|TF|SF|ZF|  |AF|  |PF|  |CF|      
//	+-----------------------------------------------+

//#define			LO32 ( (nn_Temp) )		( (unsigned long)( ( (nn_Temp) & ( (unsigned __int64)(0X00000000FFFFFFFF))		 ) )   )
//#define			HI32 ( (nn_Temp) )		( (unsigned long)( ( (nn_Temp) & (((unsigned __int64)(0XFFFFFFFF00000000)) >> 32 ) ) ) )

#define			NOFLAG		0
#define			MAX			0XFFFFFFFF

//#ifndef WIN32
typedef unsigned long long UINT64;
typedef unsigned int UINT32;
typedef unsigned int UINT;
//#endif

class CALU  
{
public:
	void MUL( UINT64& DST, UINT32 SRC1, UINT32 SRC2 );
	inline void ADD ( UINT32& DST, UINT32 SRC );
	inline void ADC ( UINT32& DST, UINT32 SRC );
		   void ADD ( UINT32& DST, UINT32 SRC1, UINT32 SRC2 );
		   void ADC ( UINT32& DST, UINT32 SRC1, UINT32 SRC2 );

	inline void SUB ( UINT32& DST, UINT32 SRC );
	inline void SBB ( UINT32& DST, UINT32 SRC );
		   void SUB ( UINT32& DST, UINT32 SRC1, UINT32 SRC2 );
		   void SBB ( UINT32& DST, UINT32 SRC1, UINT32 SRC2 );

		   void AND ( UINT32& DST, const UINT32 SRC );
		   void OR  ( UINT32& DST, const UINT32 SRC );
		   void NOT ( UINT32& DST );
		   void XOR ( UINT32& DST, UINT32 SRC );
		   void TEST( const UINT32 OPR1, const UINT32 OPR2 );

		   void SHL	( UINT32& OPR, const UINT CNT );
		   void SHL	( UINT32& DST, UINT32& SRC, const UINT CNT );
		   void SHL	( UINT32& DSTH,UINT32& DSTL,UINT32 SRC, const UINT CNT );

		   void SHR	( UINT32& OPR, const UINT CNT );
	   	   void SHR	( UINT32& SRC, UINT32& DST, const UINT CNT );
		   void SHR	( UINT32  SRC, UINT32& DSTH,UINT32& DSTL, const UINT CNT);

		   void STC	( void );
		   void CMC	( void );
		   void CLC	( void );

		   UINT32 HI32( const UINT64& nnTemp );
		   UINT32 LO32( const UINT64& nnTemp );

private:
	
	inline void ClearPSW( const unsigned short Flag );
	inline void SetPSW	( const unsigned short Flag );
	inline bool GetPSW	( const unsigned short Flag ) const;
	inline void SetPSW	( unsigned short Flag, const UINT32& Set );

protected:
	
	CALU();
	virtual ~CALU();

private:


	unsigned short	PSW;
};

#endif
