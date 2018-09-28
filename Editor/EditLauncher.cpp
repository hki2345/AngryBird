#include "stdafx.h"
#include "EditLauncher.h"
#include <Core_Class.h>
#include <KWindow.h>

#include <ResourceManager.h>
#include <Sprite_Changer.h>
#include <Texture.h>
#include <InputManager.h>
#include <KFont.h>
#include <KSound.h>


#include "Edit_Class.h"

EditLauncher::EditLauncher()
{
}


EditLauncher::~EditLauncher()
{
}


void EditLauncher::Build()
{
	Core_Class::Main_Window().Init_Device();

	InputManager::Create_Command(L"MOUSE_MB", VK_MBUTTON);
	InputManager::Create_Command(L"MOUSE_LB", VK_LBUTTON);
	InputManager::Create_Command(L"MOUSE_RB", VK_RBUTTON);
	InputManager::Create_Command(L"Up", 'W');
	InputManager::Create_Command(L"Left", 'A');
	InputManager::Create_Command(L"Down", 'S');
	InputManager::Create_Command(L"Right", 'D');

	InputManager::Create_Command(L"LeftRot", 'Q');
	InputManager::Create_Command(L"RightRot", 'E');

	InputManager::Create_Command(L"Quit", 'X');


	PathManager::Create_ForderPath(L"Sprite_Data", L"Data\\Sprite");
	PathManager::Create_ForderPath(L"Sprite_Back", L"Data\\Back\\Sprite");
	PathManager::Create_ForderPath(L"KRigid2D_Data", L"Data\\KRigid2D");
	PathManager::Create_ForderPath(L"KRigid2D_Back", L"Data\\Back\\KRigid2D");
	PathManager::Create_ForderPath(L"Panza", L"Data\\Panza");
	PathManager::Create_ForderPath(L"State", L"Data\\State");
	PathManager::Create_ForderPath(L"User", L"Data\\User");

	ResourceManager<KFont>::Create(L"AngryBirds", L"AngryBirds");

	ResourceManager<KImage>::All_Image_Load(L"Texture");
	ResourceManager<KSound>::All_Sound_Load(L"Sound");
}