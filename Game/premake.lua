project "Game"
   kind "SharedLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "Source/**.h", "Source/**.cpp" }