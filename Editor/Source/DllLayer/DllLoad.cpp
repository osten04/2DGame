#include "DllLoad.h"

#include <windows.h>
#include <iostream>

#define GAMEAPI extern "C"

GAMEAPI typedef int    ( *initFunc  )( void );
GAMEAPI typedef int    ( *closeFunc )( void );
GAMEAPI typedef GLenum ( *DrawFunc  )( int, int );

DrawFunc  DLLDraw;
closeFunc DLLClose;
HINSTANCE hGetProcIDDLL = nullptr;

#include <string>

int InitGameDll( void )
{
    CreateDirectory( L"../Out/Temp", NULL );

    CopyFile( TEXT( GAMEDLL ), L"../Out/Temp/game.dll", false );

    hGetProcIDDLL = LoadLibrary( L"../Out/Temp/game.dll" );

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

    DLLClose = (closeFunc)GetProcAddress(hGetProcIDDLL, "close");
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

    DLLClose();
    FreeLibrary( hGetProcIDDLL );
    hGetProcIDDLL = nullptr;

    return 0;
}

GLenum DrawGameDll(int width, int height)
{ 
    return DLLDraw( width, height );
}
