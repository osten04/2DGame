project "Editor"
   kind "SharedLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "Source/**.h", "Source/**.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "RELEASE" }
      optimize "On"