project "Game"
   DefaultConf "SharedLib"

   files "Shaders/**.glsl"

   LinkProject( "Framework" )
   LinkProject( "OpenGL" )
   LinkProject( "GLM" )