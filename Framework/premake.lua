project "Framework"
   DefaultConf "StaticLib"

   LinkProject( "GLM" )

   includedirs { GetSource( "OpenGL" ) }