#if !defined(INT128)
#include "Export.h"
#define INT128

#include "alu.h"
#include<string>

/*
 127				 0
+-----------------------+
| m_D | m_C | m_B | m_A |
+-----------------------+
*/



class EXPORT_DLL CHSInt128  : private CALU
{
public:
	UINT32	m_A;												// Low 32 Bit
	UINT32	m_B;
	UINT32	m_C;	
	UINT32	m_D;												// Heigh 32 Bit

public:
	CHSInt128		( const int		 nValue  );
	CHSInt128		( const long	 lValue  );
	CHSInt128		( const __int64& nnValue );
	//CHSInt128		( const UINT	 uValue  );
	CHSInt128		( const UINT32	 dwValue );
	CHSInt128		( const UINT64&	 nnValue );
	CHSInt128		( const CHSInt128& iValue  );
	CHSInt128		();
	virtual			~CHSInt128();

	bool			ToStr		( std::string& strValue );
	bool			FromStr		( const char *lpszValue );
	CHSInt128&		operator=	( const CHSInt128& iValue );
	
	CHSInt128		operator-	( const CHSInt128& iValue );	// const;
	CHSInt128&		operator-=	( const CHSInt128& iValue );
	CHSInt128		operator+	( const CHSInt128& iValue );	// const;
	CHSInt128&		operator+=	( const CHSInt128& iValue );
	CHSInt128		operator*	( const CHSInt128& iValue ) const;
	CHSInt128&		operator*=	( const CHSInt128& iValue );
	CHSInt128		operator/	( const CHSInt128& iValue ) const;
	CHSInt128&		operator/=	( const CHSInt128& iValue );
	CHSInt128		operator%	( const CHSInt128& iValue ) const;
	CHSInt128&		operator%=	( const CHSInt128& iValue );

	CHSInt128&		operator++	( void );						// ++n		
	CHSInt128&		operator--	( void );						// --n	
	CHSInt128		operator++	( int );						// n++			
	CHSInt128		operator--	( int );						// n--

	CHSInt128		operator^	( const CHSInt128& iValue ) const;
	CHSInt128		operator&	( const CHSInt128& iValue ) const;
	CHSInt128		operator|	( const CHSInt128& iValue ) const;
	CHSInt128		operator~	( void ) const;

	CHSInt128&		operator^=	( const CHSInt128& iValue );
	CHSInt128&		operator&=	( const CHSInt128& iValue );
	CHSInt128&		operator|=	( const CHSInt128& iValue );

	CHSInt128		operator<< 	( const UINT nShift );
	CHSInt128&		operator<<= ( const UINT nShift );
	CHSInt128		operator>>  ( const UINT nShift );
	CHSInt128&		operator>>= ( const UINT nShift );

	bool			operator==	( const CHSInt128& iValue ) const;
	bool			operator!=	( const CHSInt128& iValue ) const;
	bool			operator>	( const CHSInt128& iValue ) const;
	bool			operator<	( const CHSInt128& iValue ) const;
	bool			operator>=	( const CHSInt128& iValue ) const;
	bool			operator<=	( const CHSInt128& iValue ) const;
/*
	operator	int();
	operator	unsigned int();
	operator	long();
	operator	unsigned long();
	operator	__int64();
	operator	unsigned __int64();
*/

	void			SetPositiveFlag	 ( void );
	void			SetNegativeFlag	 ( void );
	void			Complement		 ( void );
	void			ComplementInverse( void );
	void			Min				 ( void );
	void			Max				 ( void );
	void			Zero			 ( void );
	void			SetAt			 ( UINT uIndex, bool bSet );

	bool			IsZero			 ( void ) const;
	bool			IsNegative		 ( void ) const;
	bool			IsPositive		 ( void ) const;
	bool			GetAt			 ( UINT uIndex ) const;
	CHSInt128		GetRight		 ( UINT uCount ) const;
	CHSInt128		GetLeft			 ( UINT uCount ) const;

	void		Division			 ( const CHSInt128& iDivisor, CHSInt128& iQuotient, CHSInt128& iRemainder) const;

};

#endif