-- premake5.lua

workspace "Project"
   configurations { "Debug", "Release" }

filter "configurations:Debug"
   defines { "DEBUG" }
   symbols "On"

filter "configurations:Release"
   defines { "RELEASE" }
   optimize "On"


cppdialect "c++20"
cdialect   "C17"

dofile ( "Base/premake.lua"   )
dofile ( "Editor/premake.lua" )
dofile ( "Game/premake.lua"   )