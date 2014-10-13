
#include "gd.h"

/////////////////////////////////////////////////////////////////
// Helpers
/////////////////////////////////////////////////////////////////

/* Write formatted data to buffer */
int gdStringFormat(char *pBuffer, const char *pFormat, ... )
{
    GD_ASSERT(pBuffer != NULL, "E000000001");
    GD_ASSERT(pFormat != NULL, "E000000002");
    
    int nRet = -1;
    
    va_list args;
	va_start(args, pFormat);
	nRet = vsprintf(pBuffer, pFormat, args);
	va_end(args);
    
    return nRet;
}

/* Write formatted data to sized buffer */
int gdStringFormat(char *pBuffer, size_t nDestSize, const char *pFormat, ... )
{
    GD_ASSERT(pBuffer != NULL, "E000000003");
    GD_ASSERT(nDestSize > 0, "E000000004");
    GD_ASSERT(pFormat != NULL, "E000000005");
    
    int nRet = -1;
    
    va_list args;
	va_start(args, pFormat);
	nRet = vsnprintf(pBuffer, nDestSize, pFormat, args);
	va_end(args);
    
    return nRet;
}

const char* gdGetString(const char *pFormat, ... )
{
    GD_ASSERT(pFormat != NULL, "E000000006");
    
    static char szBuffer[1024];
    
    va_list args;
	va_start(args, pFormat);
	vsprintf(szBuffer, pFormat, args);
	va_end(args);
    
    return szBuffer;
}

/////////////////////////////////////////////////////////////////
// Unit testing
/////////////////////////////////////////////////////////////////

#ifdef DEBUG
void gdTestStringFormat(void)
{
    char szBuffer[128];
    int nRet;
    
    nRet = gdStringFormat(szBuffer, "Hello %s!", "World");
    
    GD_LOG("%s (%d)", szBuffer, nRet);
    
    nRet = gdStringFormat(szBuffer, 128, "%d %s %d = %d", 2, "+", 3, 2 + 3);
    
    GD_LOG("%s (%d)", szBuffer, nRet);
}
#endif

