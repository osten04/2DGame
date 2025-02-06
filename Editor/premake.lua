project "Editor"
   DefaultConf "SharedLib"

   dependson { "Game" }

   LinkProject( "OpenGL"    )
   LinkProject( "ImGUI"     )
   LinkProject( "Framework" )

   filter "configurations:Debug**"
      defines { "GAMEDLL=\"../Out/Bin/Debug/Game.dll\"" }
      
   filter "configurations:Release**"
      defines { "GAMEDLL=\"../Out/Bin/Release/Game.dll\"" }
