project "Base"
   kind "ConsoleApp"
   language "C++"

   includedirs { "../Editor/Source" }

   files { "Source/**.h", "Source/**.cpp" }

   location "../Out/Sln"

   links "Editor"
   dependson { "editor" }