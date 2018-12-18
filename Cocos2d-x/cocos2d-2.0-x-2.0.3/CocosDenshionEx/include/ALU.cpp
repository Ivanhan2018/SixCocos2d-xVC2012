//#include "Int128.h"
#include "ALU.h"

CALU::CALU()
{
	PSW = NOFLAG;
}

CALU::~CALU()
{

}

// Set Flag
inline void CALU::SetPSW(unsigned short Flag, const UINT32& Set)
{
	if ( Set )
		 PSW |=  Flag;
	else PSW &= ~Flag;
}

// Get Flag
inline bool CALU::GetPSW(const unsigned short Flag) const
{
	return ( ( PSW & Flag ) != 0 );
}

// Set Flag
inline void CALU::SetPSW(const unsigned short Flag)
{
	PSW |= Flag;
}

// Clear Flag
inline void CALU::ClearPSW(const unsigned short Flag)
{
	PSW &= ~Flag;
}

// Get Low 32 Bit ( unsinged __int64 )
UINT32 CALU::LO32(const UINT64 &nnTemp)
{
	return ( (UINT32)( (  (UINT64)(nnTemp)) & ((UINT64)(0X00000000FFFFFFFF)) ) );
}

// Get High 32 Bit ( unsinged __int64 )
UINT32 CALU::HI32(const UINT64 &nnTemp)
{
	return ( (UINT32)( ( ((UINT64)(nnTemp)) & ((UINT64)(0XFFFFFFFF00000000))) >> 32 ) );		
}

// Clear Carry
void CALU::CLC()
{
	ClearPSW( CF );
}

// Complement Carry
inline void CALU::CMC()
{
	if ( GetPSW( CF ) )
		 CLC();
	else STC();
}

// Set Carry
inline void CALU::STC()
{
	SetPSW( CF );
}

// Test
void CALU::TEST(const UINT32 OPR1, const UINT32 OPR2)
{
	SetPSW( ZF, ( ( OPR1 & OPR2 )==0 ) );
}

// And
void CALU::AND(UINT32 &DST, const UINT32 SRC)
{
	DST &= SRC;
}

// Or
void CALU::OR(UINT32 &DST, const UINT32 SRC)
{
	DST |= SRC;
}

// Not
void CALU::NOT(UINT32 &DST)
{
	DST = ~DST;
}

// Exclusive or
void CALU::XOR(UINT32 &DST, UINT32 SRC)
{
	DST ^= SRC;
}

// Add
inline void CALU::ADD(UINT32 &DST, UINT32 SRC)
{
	UINT64	nnTemp;

	nnTemp = (UINT64)DST + (UINT64)SRC;

	SetPSW( CF, ( nnTemp > MAX ) );

	DST = LO32( nnTemp );
}

// Add width Carry
inline void CALU::ADC(UINT32 &DST, UINT32 SRC)
{
	UINT64	nnTemp;

	nnTemp = (UINT64)DST + (UINT64)SRC + (int)GetPSW( CF );

	SetPSW( CF, ( nnTemp > MAX ) );

	DST = LO32( nnTemp ); 
}

// Add 3 Parameters
void CALU::ADD(UINT32 &DST, UINT32 SRC1, UINT32 SRC2)
{
	ADD( SRC1, SRC2 );

	DST = SRC1;
}

// Add With Carry	3 Parameter
void CALU::ADC(UINT32 &DST, UINT32 SRC1, UINT32 SRC2)
{
	ADC( SRC1, SRC2 );

	DST = SRC1;
}

// Subtract
inline void CALU::SUB(UINT32 &DST, UINT32 SRC)
{
	UINT64	nnTemp;

	nnTemp = (UINT64)DST - (UINT64)SRC;

	SetPSW( CF, ( nnTemp > MAX ) );

	DST = (UINT32)nnTemp;
}

// Subtract with borrow
inline void CALU::SBB(UINT32 &DST, UINT32 SRC)
{
	UINT64	nnTemp;

	nnTemp = (UINT64)DST - (UINT64)SRC - (int)GetPSW( CF );

	SetPSW( CF, ( nnTemp > MAX ) );

	DST = (UINT32)nnTemp;
}

// Subtract 3 Parameters
void CALU::SUB(UINT32 &DST, UINT32 SRC1, UINT32 SRC2)
{
	SUB( SRC1, SRC2 );

	DST = SRC1;
}

// Subtrace with borrow 3 Parameters
void CALU::SBB(UINT32 &DST, UINT32 SRC1, UINT32 SRC2)
{
	SBB( SRC1, SRC2 );

	DST = SRC1;
}

// Shift logical left  ( CNT >= 1 )
void CALU::SHL(UINT32 &OPR, const UINT CNT)
{
	OPR <<= ( CNT - 1 );
	
	SetPSW( CF, ( ( OPR & 0X80000000 ) != 0 ) );

	OPR <<= 1;
}

// Shift logical left  ( CNT >= 1 )	 return Low 32 Bit
void CALU::SHL( UINT32& DSTH, UINT32& DSTL, UINT32 SRC, const UINT CNT)
{
	UINT64	nnTemp = (UINT64)SRC;

	nnTemp <<= ( CNT - 1 );
	
	SetPSW( CF, ( ( nnTemp & UINT64(0X8000000000000000) ) != 0 ) );

	nnTemp <<= 1;

	DSTH = HI32( nnTemp );
	DSTL = LO32( nnTemp );
}

// Mov uShift Bit To DST 
void CALU::SHL(UINT32 &DST, UINT32 &SRC, const UINT CNT)
{
	UINT32	DSTH = 0;

	SHL( DSTH, SRC, SRC, CNT );

	DST |= DSTH;
}

// Shift Arithmetic right	CNT >= 1
void CALU::SHR(UINT32 &OPR, const UINT CNT)
{
	OPR >>= ( CNT - 1 );
	
	SetPSW( CF, ( ( OPR & 0X00000001 ) != 0 ) );

	OPR >>= 1;	
}

// 
void CALU::SHR(UINT32 SRC, UINT32 &DSTH, UINT32 &DSTL, const UINT CNT)
{
	UINT64	nnTemp = (UINT64)SRC;

	nnTemp <<= 32;

	nnTemp >>= ( CNT - 1 );

	SetPSW( CF, ( ( nnTemp & 0X0000000000000001 ) != 0 ) );

	nnTemp >>= 1;

	DSTH = HI32( nnTemp );
	DSTL = LO32( nnTemp );
}

// 
void CALU::SHR(UINT32 &SRC, UINT32 &DST, const UINT CNT)
{
	UINT32	DSTL = 0;
	
	SHR( SRC, SRC, DSTL, CNT ); 

	DST |= DSTL;
}

void CALU::MUL(UINT64 &DST, UINT32 SRC1, UINT32 SRC2)
{
	 DST = ( SRC1 * SRC2 );
}
