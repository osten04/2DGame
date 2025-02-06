#include "DllLoad.h"

#include <windows.h>
#include <iostream>

#define GAMEAPI extern "C"

GAMEAPI typedef int ( *initFunc )(void);
GAMEAPI typedef int ( *DrawFunc )( int, int );

DrawFunc DLLDraw;
HINSTANCE hGetProcIDDLL = nullptr;

#include <string>

int InitGameDll( void )
{
    //CopyFile( TEXT( GAMEDLL ), L"temp/game.dll", false );

    hGetProcIDDLL = LoadLibrary( TEXT( GAMEDLL ) );

    if (!hGetProcIDDLL) {
        std::cout << "could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    // resolve function address here
    initFunc dllInit = (initFunc)GetProcAddress(hGetProcIDDLL, "init");
    if (!dllInit) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    DLLDraw = (DrawFunc)GetProcAddress(hGetProcIDDLL, "draw");
    if (!DLLDraw) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    return dllInit();
}

int unload(void)
{
    if ( !hGetProcIDDLL )
        return 0;

    FreeLibrary( hGetProcIDDLL );
    hGetProcIDDLL = nullptr;

    return 0;
}

int DrawGameDll(int width, int height)
{ 
    return DLLDraw( width, height );
}
