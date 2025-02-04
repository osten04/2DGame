-- premake5.lua

workspace "Project"
   configurations { "Debug", "Release" }

   architecture "x86_64"

   cppdialect   "c++20"
   cdialect     "C17"

   targetdir "Out/Bin/%{cfg.buildcfg}"
   objdir    "Out/Obj/%{cfg.buildcfg}"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "RELEASE" }
      optimize "On"

dofile ( "Base/premake.lua"   )
dofile ( "Editor/premake.lua" )
dofile ( "Game/premake.lua"   )