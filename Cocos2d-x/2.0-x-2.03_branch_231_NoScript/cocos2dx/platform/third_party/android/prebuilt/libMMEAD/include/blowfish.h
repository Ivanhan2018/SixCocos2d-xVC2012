// blowfish.h     interface file for blowfish.cpp
// _THE BLOWFISH ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger
#pragma once
#ifdef WIN32
#include <Windows.h>
#endif
#define MAXKEYBYTES 	56		// 448 bits max
#define NPASS           16		// SBox passes

class CBlowFish
{
private:
	unsigned long 		* PArray ;
	unsigned long		(* SBoxes)[256];
	void 		Blowfish_encipher (unsigned long *xl, unsigned long *xr) ;
	void 		Blowfish_decipher (unsigned long *xl, unsigned long *xr) ;

public:
			CBlowFish () ;
			~CBlowFish () ;
	void 		Initialize (unsigned char key[], int keybytes) ;
	unsigned long		GetOutputLength (unsigned long lInputLong) ;
	unsigned long		Encode (unsigned char * pInput, unsigned char * pOutput, unsigned long lSize) ;
	void		Decode (unsigned char * pInput, unsigned char * pOutput, unsigned long lSize) ;

} ;

// choose a byte order for your hardware
#define ORDER_DCBA	// chosing Intel in this case

#ifdef ORDER_DCBA  	// DCBA - little endian - intel
	union aword {
	  unsigned long dword;
	  unsigned char byte [4];
	  struct {
	    unsigned int byte3:8;
	    unsigned int byte2:8;
	    unsigned int byte1:8;
	    unsigned int byte0:8;
	  } w;
	};
#endif

#ifdef ORDER_ABCD  	// ABCD - big endian - motorola
	union aword {
	  unsigned long dword;
	  unsigned char byte [4];
	  struct {
	    unsigned int byte0:8;
	    unsigned int byte1:8;
	    unsigned int byte2:8;
	    unsigned int byte3:8;
	  } w;
	};
#endif

#ifdef ORDER_BADC  	// BADC - vax
	union aword {
	  unsigned long dword;
	  unsigned char byte [4];
	  struct {
	    unsigned int byte1:8;
	    unsigned int byte0:8;
	    unsigned int byte3:8;
	    unsigned int byte2:8;
	  } w;
};
#endif