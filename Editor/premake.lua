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
