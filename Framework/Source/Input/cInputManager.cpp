#include "cInputManager.h"

#include "GLFW/glfw3.h"

void Cursor( GLFWwindow* window, double xpos, double ypos)
{
	
}

sInput::uData::sKey::eAction GetAction( int _action )
{
	switch ( _action )
	{
		case ( GLFW_PRESS   ): return sInput::uData::sKey::eAction::press;
		case ( GLFW_REPEAT  ): return sInput::uData::sKey::eAction::repeat;
		case ( GLFW_RELEASE ): return sInput::uData::sKey::eAction::release;
	}

	return sInput::uData::sKey::eAction::none;
}

void MouseButton( GLFWwindow* window, int button, int action, int mods )
{

}

void Key( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	sInput input = sInput
	{
		.type = sInput::eType::keyboard,
		.data = sInput::uData::sKey
		{
			.hexcode = key,
			.action = GetAction( action )
		}
	};

	cInputManager::GetR().CallCallbacks( input );
}

cInputManager::cInputManager(void* _window)
{
	GLFWwindow* window = ( GLFWwindow* )_window;
	glfwSetCursorPosCallback( window, Cursor );
	glfwSetMouseButtonCallback( window, MouseButton );
	glfwSetKeyCallback( window, Key );
}

cInputManager::~cInputManager()
{
	for ( iInput* input : m_callbacks)
	{
		delete input;
	}
}

void cInputManager::CallCallbacks( const sInput& _input )
{
	for ( iInput* input : m_callbacks )
	{
		input->CB( _input );
	}
}

void cInputManager::UnSubscribe( void* _owner )
{
	for ( int i = m_callbacks.size() - 1; i >= 0; i-- )
	{
		if( _owner == m_callbacks[ i ]->GetObject() )
		{
			m_callbacks.erase( m_callbacks.begin() + i );
		}
	}
}