project "Base"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs { "../Editor/Source" }

   files { "Source/**.h", "Source/**.cpp" }

   links "Editor"