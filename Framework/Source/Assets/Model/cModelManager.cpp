#include "cModelManager.h"

#include "glad/glad.h"

#include "cModel.h"
#include "Assets/Camera/cCamera.h"
#include "Assets/Camera/cLight.h"


cModelManager::cModelManager()
	:Super( "Shaders/Model", "Shaders/ModelShadow" )
{
}

cModelManager::~cModelManager()
{
}

void cModelManager::drawShadows(iAsset* _asset, math::sVector2i _screen)
{
	const cCamera* light = cCamera::GetMainCamera< cLight >();
	const cCamera* cam = cCamera::GetMainCamera();

	if ( !light )
		return;

	cModel& model = *( cModel* )_asset;

	glUseProgram(m_shaderProgram);
	glBindVertexArray( model.m_vao );

	const glm::mat4x4 lightSpace = light->GetProjMatrix() * cam->GetViewMatrix();

	const glm::vec3 pos = cam->m_pos;

	// Uniforms
	glUniformMatrix4fv( glGetUniformLocation( m_shaderProgram, "u_projection" ), 1, false, glm::value_ptr( cam->GetProjMatrix() ) );
	glUniformMatrix4fv( glGetUniformLocation( m_shaderProgram, "u_view"       ), 1, false, glm::value_ptr( cam->GetViewMatrix() ) );
	glUniformMatrix4fv( glGetUniformLocation( m_shaderProgram, "u_model"      ), 1, false, glm::value_ptr( model.m_mat ) );
	glUniformMatrix4fv( glGetUniformLocation( m_shaderProgram, "u_lightSpace" ), 1, false, glm::value_ptr( lightSpace ) );
	glUniform3f(        glGetUniformLocation( m_shaderProgram, "u_lightPos"   ), pos.x, pos.y, pos.z );
	glUniform3f(        glGetUniformLocation( m_shaderProgram, "u_viewPos"    ), pos.x, pos.y, pos.z );

	glDrawArrays( GL_TRIANGLES, 0, model.m_vertexCount );
	glBindVertexArray( 0 );
	glUseProgram( 0 );
}

void cModelManager::draw( iAsset* _asset, math::sVector2i _screen )
{
	const cCamera* cam = cCamera::GetMainCamera();

	if ( !cam )
		return;

	cModel& model = *( cModel* )_asset;

	glUseProgram(m_shaderProgram);
	glBindVertexArray( model.m_vao );

	// Uniforms
	glUniformMatrix4fv( glGetUniformLocation( m_shaderProgram, "u_projection" ), 1, false, glm::value_ptr( cam->GetProjMatrix() ) );
	glUniformMatrix4fv( glGetUniformLocation( m_shaderProgram, "u_view"       ), 1, false, glm::value_ptr( cam->GetViewMatrix() ) );
	glUniformMatrix4fv( glGetUniformLocation( m_shaderProgram, "u_model"      ), 1, false, glm::value_ptr( model.m_mat ) );

	glDrawArrays( GL_TRIANGLES, 0, model.m_vertexCount );
	glBindVertexArray( 0 );
	glUseProgram(0);
}
