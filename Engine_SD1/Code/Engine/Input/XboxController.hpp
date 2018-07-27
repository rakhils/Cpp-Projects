#pragma once
#include "Engine\Math\Vector2.hpp"

struct XButtonInputState
{
	bool m_wasJustPressed;
	bool m_wasJustReleased;
	bool m_isKeyDown;
};

struct AnalogJoystick
{
	float Rx;
	float Ry;
	float RawX;
	float RawY;
	float degrees;
	const float innerDeadZone = 0.3f;
	const float outerDeadZone = 0.9f;
};

enum XBoxInputs :unsigned char
{
	INP_DPadLeft,		
	INP_DPadRight,	
	INP_DPadTop,		
	INP_DpadBottom,	
	INP_X,			
	INP_Y,			
	INP_A,			
	INP_B,			
	INP_LeftBumper,	
	INP_RigthBumper,	
	INP_Menu,			
	INP_View,			
	INP_LeftThumb,	
	INP_RigthThumb,	
};

class XboxController
{
public:
	//@purpose : MASK VALUES

	unsigned short		VK_DPadLeft		= 4;
	unsigned short		VK_DPadRight	= 8;
	unsigned short		VK_DPadTop		= 1;
	unsigned short		VK_DpadBottom	= 2;
	unsigned short		VK_X			= 16384;
	unsigned short		VK_Y			= 32768;
	unsigned short		VK_A			= 4096;
	unsigned short		VK_B			= 8192;
	unsigned short		VK_LeftBumper	= 256;
	unsigned short		VK_RigthBumper	= 512;
	unsigned short		VK_Menu			= 16;
	unsigned short		VK_View			= 32;
	unsigned short		VK_LeftThumb	= 64;
	unsigned short		VK_RigthThumb	= 128;

	XButtonInputState	XInputState[14];
	AnalogJoystick		LeftJoyStick;
	AnalogJoystick		RightJoyStick;

public:
	int m_controllerNumber = 0;

	float LeftStickRX = 0;
	float LeftStickRY = 0;

	float RightStickRX = 0;
	float RightStickRY = 0;

	bool directionL = false;
	bool directionR = false;
	bool directionU = false;
	bool directionT = false;

	bool AKey = false;
	bool XKey = false;
	bool BKey = false;
	bool YKey = false;

	bool leftTrigger = false;
	bool rightTrigger = false;

	bool leftBumper = false;
	bool rigthBumper = false;

	bool viewButton = false;
	bool menuButton = false;


	XboxController();
	XboxController(int controllerNumber);
	
	void XboxController::updateContoller();
	void XboxController::clearKeyStates();
	void XboxController::updateButton(unsigned short button,unsigned short flags,int index);
	bool XboxController::isConnected();
	
	void XboxController::updateRightTrigger();
	void XboxController::updateLeftTrigger(); 

	bool XboxController::isXBOXAPressed();
	bool XboxController::isXBOXBPressed();
	bool XboxController::isXBOXXPressed();
	bool XboxController::isXBOXYPressed();

	bool XboxController::isXBOXAJustPressed();
	bool XboxController::isXBOXBJustPressed();
	bool XboxController::isXBOXXJustPressed();
	bool XboxController::isXBOXYJustPressed();

	bool XboxController::isDirectionLPressed();
	bool XboxController::isDirectionRPressed();
	bool XboxController::isDirectionUPressed();
	bool XboxController::isDirectionBPressed();

	bool XboxController::isLeftTriggerPressed();
	bool XboxController::isRightTriggerPressed();
	bool XboxController::isLeftBumperPressed();
	bool XboxController::isRightBumperPressed();

	float XboxController::getRightStickXValue();
	float XboxController::getRigthStickYValue();

	bool IsKeyDown( unsigned char keyCode ) const;
	bool WasKeyJustPressed( unsigned char keyCode ) const;
	bool WasKeyJustReleased( unsigned char keyCode ) const;

	void XboxController::CalculateRightStick();
	void XboxController::CalculateLeftStick();

	Vector2 XboxController::getLeftStickVector();
	Vector2 XboxController::getRigthStickVector();

};