project "Editor"
   DefaultConf "SharedLib"

   includedirs { 
      GetSource( "OpenGL" ),
      GetSource( "ImGUI"  )
   }

   links {
      "OpenGL",
      "ImGUI"
   }

   filter "configurations:Debug"
      defines { "GAMEDLL=\"../Out/Bin/Debug/Game.dll\"" }
      
   filter "configurations:Release"
      defines { "GAMEDLL=\"../Out/Bin/Release/Game.dll\"" }
