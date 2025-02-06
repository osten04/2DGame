-- premake5.lua

function DefaultConf( _type )
   kind ( _type )
   language "C++"

   files { "Source/**.h", "Source/**.cpp", "Source/**.c", "Source/**.hpp" }

   location "../Out/Sln"

   includedirs { "Source" }
end	

function GetSource( _project )
   return "../" .. _project .. "/Source"
end

function LinkProject( _project )
   links       { _project }
   includedirs { GetSource( _project ) }
end

workspace "Project"
   configurations { "Debug", "Release", "Debug Editor", "Release Editor" }

   architecture "x86_64"

   cppdialect "c++20"
   cdialect   "C17"

   

   libdirs { "Libs" }
   
   filter "configurations:Debug**"
      defines { "DEBUG" }
      symbols "On"
      targetdir "Out/Bin/Debug"
      objdir    "Out/Obj/Debug"

   filter "configurations:Release**"
      defines { "RELEASE" }
      optimize "On"
      targetdir "Out/Bin/Release"
      objdir    "Out/Obj/Release"

   dofile ( "Framework/premake.lua" )
   dofile ( "Base/premake.lua"      )
   dofile ( "OpenGL/premake.lua"    )
   dofile ( "ImGUI/premake.lua"     )
   dofile ( "Editor/premake.lua"    )
   dofile ( "Game/premake.lua"      )