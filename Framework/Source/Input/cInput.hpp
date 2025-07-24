#pragma once

#include "Math/Vector.h"

struct sInput
{
    union uData
    {
        struct sKey
        {
            enum eAction : char
            {
                none    = 0,
                press   = 1,
                repeat  = 2,
                release = 3
            };

            int     hexcode;
            eAction action;
        };

        struct sMouse
        {
            math::sVector2i pos;
        };

        sKey   key;
        sMouse mouse;
    }; 
    
    enum eType : unsigned char
    {
        none = 0,
        keyboard = 1,
        mouseKey = 2,
        mouse = 3
    };

    eType type;
    uData data;
};

class iInput
{
public:
	virtual void CB( const sInput& _input ) = 0;
    virtual void* GetObject() = 0;
};

template < class t >
class cInput : public iInput
{
private:

    t* m_instance;
    void ( t::* m_memberfunc )( const sInput& );

public:

    cInput( t* _instance, void ( t::* memberfunction )( const sInput& ) ) : m_instance( _instance ), m_memberfunc(memberfunction) { }

    virtual void CB( const sInput& _input ) override { ( m_instance->*m_memberfunc )( _input ); }
    virtual void* GetObject() { return m_instance; }
};

namespace Input
{
    constexpr int KeyCode_Space         = 32;
    constexpr int KeyCode_Apostrophe    = 39;
    constexpr int KeyCode_Comma         = 44;  /* , */
    constexpr int KeyCode_Minus         = 45;  /* - */
    constexpr int KeyCode_Period        = 46;  /* . */
    constexpr int KeyCode_Slash         = 47;  /* / */
    constexpr int KeyCode_0             = 48;
    constexpr int KeyCode_1             = 49;
    constexpr int KeyCode_2             = 50;
    constexpr int KeyCode_3             = 51;
    constexpr int KeyCode_4             = 52;
    constexpr int KeyCode_5             = 53;
    constexpr int KeyCode_6             = 54;
    constexpr int KeyCode_7             = 55;
    constexpr int KeyCode_8             = 56;
    constexpr int KeyCode_9             = 57;
    constexpr int KeyCode_Semicolon     = 59;  /* ; */
    constexpr int KeyCode_Equal         = 61;  /* = */
    constexpr int KeyCode_A             = 65;
    constexpr int KeyCode_B             = 66;
    constexpr int KeyCode_C             = 67;
    constexpr int KeyCode_D             = 68;
    constexpr int KeyCode_E             = 69;
    constexpr int KeyCode_F             = 70;
    constexpr int KeyCode_G             = 71;
    constexpr int KeyCode_H             = 72;
    constexpr int KeyCode_I             = 73;
    constexpr int KeyCode_J             = 74;
    constexpr int KeyCode_K             = 75;
    constexpr int KeyCode_L             = 76;
    constexpr int KeyCode_M             = 77;
    constexpr int KeyCode_N             = 78;
    constexpr int KeyCode_O             = 79;
    constexpr int KeyCode_P             = 80;
    constexpr int KeyCode_Q             = 81;
    constexpr int KeyCode_R             = 82;
    constexpr int KeyCode_S             = 83;
    constexpr int KeyCode_T             = 84;
    constexpr int KeyCode_U             = 85;
    constexpr int KeyCode_V             = 86;
    constexpr int KeyCode_W             = 87;
    constexpr int KeyCode_X             = 88;
    constexpr int KeyCode_Y             = 89;
    constexpr int KeyCode_Z             = 90;
    constexpr int KeyCode_Left_bracket  = 91;  /* [ */
    constexpr int KeyCode_Backslash     = 92;  /* \ */
    constexpr int KeyCode_Right_bracket = 93;  /* ] */
    constexpr int KeyCode_Grave_accent  = 96;  /* ` */
    constexpr int KeyCode_World_1       = 161; /* non-US #1 */
    constexpr int KeyCode_World_2       = 162; /* non-US #2 */

    /* Function keys */
    constexpr int KeyCode_Escape        = 256;
    constexpr int KeyCode_Enter         = 257;
    constexpr int KeyCode_Tab           = 258;
    constexpr int KeyCode_Backspace     = 259;
    constexpr int KeyCode_Insert        = 260;
    constexpr int KeyCode_Delete        = 261;
    constexpr int KeyCode_Right         = 262;
    constexpr int KeyCode_Left          = 263;
    constexpr int KeyCode_Down          = 264;
    constexpr int KeyCode_Up            = 265;
    constexpr int KeyCode_Page_up       = 266;
    constexpr int KeyCode_Page_down     = 267;
    constexpr int KeyCode_Home          = 268;
    constexpr int KeyCode_End           = 269;
    constexpr int KeyCode_CapsLock      = 280;
    constexpr int KeyCode_ScrollLock    = 281;
    constexpr int KeyCode_NumLock       = 282;
    constexpr int KeyCode_PrintScreen   = 283;
    constexpr int KeyCode_Pause         = 284;
    constexpr int KeyCode_F1            = 290;
    constexpr int KeyCode_F2            = 291;
    constexpr int KeyCode_F3            = 292;
    constexpr int KeyCode_F4            = 293;
    constexpr int KeyCode_F5            = 294;
    constexpr int KeyCode_F6            = 295;
    constexpr int KeyCode_F7            = 296;
    constexpr int KeyCode_F8            = 297;
    constexpr int KeyCode_F9            = 298;
    constexpr int KeyCode_F10           = 299;
    constexpr int KeyCode_F11           = 300;
    constexpr int KeyCode_F12           = 301;
    constexpr int KeyCode_F13           = 302;
    constexpr int KeyCode_F14           = 303;
    constexpr int KeyCode_F15           = 304;
    constexpr int KeyCode_F16           = 305;
    constexpr int KeyCode_F17           = 306;
    constexpr int KeyCode_F18           = 307;
    constexpr int KeyCode_F19           = 308;
    constexpr int KeyCode_F20           = 309;
    constexpr int KeyCode_F21           = 310;
    constexpr int KeyCode_F22           = 311;
    constexpr int KeyCode_F23           = 312;
    constexpr int KeyCode_F24           = 313;
    constexpr int KeyCode_F25           = 314;
    constexpr int KeyCode_Kp0           = 320;
    constexpr int KeyCode_Kp1           = 321;
    constexpr int KeyCode_Kp2           = 322;
    constexpr int KeyCode_Kp3           = 323;
    constexpr int KeyCode_Kp4           = 324;
    constexpr int KeyCode_Kp5           = 325;
    constexpr int KeyCode_Kp6           = 326;
    constexpr int KeyCode_Kp7           = 327;
    constexpr int KeyCode_Kp8           = 328;
    constexpr int KeyCode_Kp9           = 329;
    constexpr int KeyCode_KpDecimal     = 330;
    constexpr int KeyCode_KpDivide      = 331;
    constexpr int KeyCode_KpMultiply    = 332;
    constexpr int KeyCode_KpSubtract    = 333;
    constexpr int KeyCode_KpAdd         = 334;
    constexpr int KeyCode_KpEnter       = 335;
    constexpr int KeyCode_KpEqual       = 336;
    constexpr int KeyCode_LeftShift     = 340;
    constexpr int KeyCode_LeftControl   = 341;
    constexpr int KeyCode_LeftAlt       = 342;
    constexpr int KeyCode_LeftSuper     = 343;
    constexpr int KeyCode_RightShift    = 344;
    constexpr int KeyCode_RightControl  = 345;
    constexpr int KeyCode_RightAlt      = 346;
    constexpr int KeyCode_RightSuper    = 347;
    constexpr int KeyCode_Menu          = 348;

    constexpr int KeyCode_Last          = KeyCode_Menu;
}