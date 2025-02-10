project "Base"
   DefaultConf "ConsoleApp"

   debugdir "../Game"

   filter "configurations:**Editor"
   
      defines { "EDITOR" }

      includedirs { 
         GetSource( "Editor" ),
         GetSource( "OpenGL" )
      }
      
      links {
         "OpenGL",
         "Editor",
         "Dbghelp"
      }
      
      dependson { "Editor", "Premake" }
   
   filter "configurations:not **Editor"
   
      dependson   "Game"
      LinkProject "Game"
      LinkProject "OpenGL"
