#pragma once
/*\class  : App
* \group  : <GroupName>
* \brief  : App is main class which gets called from Main_win32 Application file. 
* \TODO:  :
* \note   :
* \author : Rakhil Soman
* \version: 1.0
* \date   : 
* \contact: srsrakhil@gmail.com
*/
class App
{
public:
	// VARIABLES

	

	// FUNCTIONS
	App::App();
	App::~App();

	void RunFrame();
	void Update(float deltaTime);
	void Render();

	void RequestToQuit();
	bool IsReadyToQuit();

};
