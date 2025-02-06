project "Game"
   DefaultConf "SharedLib"

   includedirs { 
      GetSource( "OpenGL" )
   }

   links {
      "OpenGL"
   }