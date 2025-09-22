#pragma once

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "GLFW/glfw3.h"

#include "Input/cInput.hpp"

class cCamera
{
private:
	template< typename t >
	class cCameraHolder
	{
	public:
		inline static t* m_mainCamera = nullptr;
	};
protected:
	inline static cCamera* m_mainCamera = nullptr;

public:
	cCamera( bool _input );
	~cCamera();

	template< typename t, class... args >
	static void Init( args... ARGS ) { cCameraHolder< t >::m_mainCamera = new t( ARGS... ); }
	template< typename t >
	static void Deinit() { delete cCameraHolder< t >::m_mainCamera; cCameraHolder< t >::m_mainCamera = nullptr; }

	virtual void Update( float _deltaTime, int _width, int _height );

	template< typename t >
	static t* GetMainCamera() { return ( t* )cCameraHolder< t >::m_mainCamera; };
	static cCamera* GetMainCamera() { return m_mainCamera; };

	const glm::mat4x4& GetViewMatrix() const { return m_view; }
	const glm::mat4x4& GetProjMatrix() const { return m_proj; }

	virtual void Input( const sInput& _input ) { };
protected:
	friend class cModelManager;
	glm::dvec3 m_pos{}, m_rot{};

	glm::vec3 direction = glm::vec3();

	glm::mat4 m_view = glm::mat4x4( 1.0f );
	glm::mat4 m_proj = glm::mat4x4( 1.0f );
};