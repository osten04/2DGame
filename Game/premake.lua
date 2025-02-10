project "Game"
   DefaultConf "SharedLib"

   files "Shaders/**.glsl"

   includedirs { 
      GetSource( "OpenGL" )
   }

   links {
      "OpenGL"
   }