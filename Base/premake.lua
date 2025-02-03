project "Base"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "Source/**.h", "Source/**.cpp" }