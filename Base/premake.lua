project "Base"
   DefaultConf "ConsoleApp"


   includedirs { 
      GetSource( "Editor" ),
      GetSource( "OpenGL" )
   }

   links {
      "OpenGL",
      "Editor"
   }

   dependson { "Editor" }