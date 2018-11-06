#ifndef __COMMON_H__
#define __COMMON_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
	// Microsoft visual studio, version 6 and higher.
	#define ANS_SNPRINTF _snprintf
#else
	#define ANS_SNPRINTF snprintf
#endif	

#endif  // __COMMON_H__