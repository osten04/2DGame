project "Base"
   DefaultConf "ConsoleApp"

   debugdir "../Game"

   includedirs { 
      GetSource( "Editor" ),
      GetSource( "OpenGL" )
   }

   links {
      "OpenGL",
      "Editor"
   }

   dependson { "Editor" }