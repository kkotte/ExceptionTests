// ExceptionTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

class CDummy
{
public:
    int _i;
    CDummy(int i) : _i(i) {}
    ~CDummy()
    {
        printf("\nCDummy %d being destroyed", _i);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    
#if 0 // Can't mix try/catch and __try/__except together in a function
    CDummy dummy(0);

    // Use synchronous exceptions (C++ exceptions)  -cannot use if you don't specify any of the /EH flags
    // Under /EHsc and /EHa following works as expected RAII handled correctly
    try
    {
        CDummy dummy2(2);
        throw 23;
    }
    catch (...)
    {
        printf("\nCaught synchronous exception");
    }
    
    // RAII below works under /EHa as expected
    // Under /EHsc, exception is not caught and program crashes before d3 is destroyed
    try
    {
        CDummy d3(3);
        char *p = nullptr;
        *p = 0;
    }
    catch (...)
    {
        printf("\nCaught asynchronous exception");
    }
#else
    // Below will not compile if you have RAII in this function anywhere - regardless of /EHsc or /EHa
    // 
    // CDummy dummy(10); // Can't have this
    __try
    {
        // CDummy d4(4); Can't have this
        char *p = nullptr;
        *p = 0;
    }
    __except(EXCEPTION_EXECUTE_HANDLER) // Catch all exceptions
    {
        printf("\nCaught asynchronous exception in SEH except block");
    }
#endif
    return 0;
}

