-- premake5.lua

function DefaultConf( _type )
   kind ( _type )
   language "C++"

   files { "Source/**.h", "Source/**.cpp", "Source/**.c" }

   location "../Out/Sln"

   includedirs { "Source" }
end	

function GetSource( _project )
   return "../" .. _project .. "/Source"
end

workspace "Project"
   configurations { "Debug", "Release" }

   architecture "x86_64"

   cppdialect "c++20"
   cdialect   "C17"

   targetdir "Out/Bin/%{cfg.buildcfg}"
   objdir    "Out/Obj/%{cfg.buildcfg}"

   libdirs { "Libs" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "RELEASE" }
      optimize "On"

   dofile ( "Base/premake.lua"   )
   dofile ( "OpenGL/premake.lua" )
   dofile ( "ImGUI/premake.lua"  )
   dofile ( "Editor/premake.lua" )
   dofile ( "Game/premake.lua"   )