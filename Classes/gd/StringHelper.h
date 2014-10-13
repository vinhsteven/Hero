
#ifndef _GD_STRING_HELPER_H_
#define _GD_STRING_HELPER_H_

/////////////////////////////////////////////////////////////////
// Macros
/////////////////////////////////////////////////////////////////

///* Write formatted data to buffer */
//#define GD_STRING_FORMAT(pBuffer, pFormat, ...) sprintf(pBuffer, pFormat, ##__VA_ARGS__)
//
///* Write formatted data to sized buffer */
//#define GD_SIZED_STRING_FORMAT(pBuffer, nDestSize, pFormat, ...)    snprintf(pBuffer, nDestSize, pFormat, ##__VA_ARGS__)

/////////////////////////////////////////////////////////////////
// Helpers
/////////////////////////////////////////////////////////////////

/* Writes formatted data to buffer */
int gdStringFormat(char *pBuffer, const char *pFormat, ... );

/* Writes formatted data to sized buffer */
int gdStringFormat(char *pBuffer, size_t nDestSize, const char *pFormat, ... );

/* Gets a string from the given formatted data */
const char* gdGetString(const char *pFormat, ... );

/////////////////////////////////////////////////////////////////
// Unit testing
/////////////////////////////////////////////////////////////////

#ifdef DEBUG
void gdTestStringFormat(void);
#endif

#endif // _GD_STRING_HELPER_H_
