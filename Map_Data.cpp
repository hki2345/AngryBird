#include "GameData.h"
#include <ResourceManager.h>

#include "Container_Class.h"
#include "Panza.h"
#include "Bird.h"
#include "Bottom.h"
#include "Bird_Launcher.h"
#include "Bomb.h"
#include "Grass.h"
#include "Pig.h"

#include <KRigid_2D.h>
#include <Renderer_Sprite.h>


std::unordered_map<int, std::list<KPtr<TheOne>>> Map_Data::m_MapList;

void Map_Data::Map_Save(KPtr<State> _State, const wchar_t* _Path)
{

	WriteStream NewStream = WriteStream(_Path);

	int Temp = Save_Count(_State);


	NewStream.write(&Temp, sizeof(int));


	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator S_MAP = m_MapList.begin();
	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator E_MAP = m_MapList.end();
	for (; S_MAP != E_MAP; ++S_MAP)
	{
		std::list<KPtr<TheOne>>::iterator S_One = S_MAP->second.begin();
		std::list<KPtr<TheOne>>::iterator E_One = S_MAP->second.end();

		for (; S_One != E_One; ++S_One)
		{
			std::wstring OneName = (*S_One)->name();
			if (L"Panza" == OneName)
			{
				TypeData TD;
				PanzaData PD;

				TD.m_Type = MAP_TYPE::PANZA;
				NewStream.write(&TD, sizeof(TypeData));

				PD.m_Trans.m_Vector3 = (*S_One)->Local_Pos().m_Vector3;
				PD.m_Trans.m4 = (*S_One)->transform()->Local_Rotate_Degree().z;

				KPtr<Panza> ThisPanza = (*S_One)->Get_Component<Panza>();

				PD.m_PMATT = ThisPanza->Material_Type();
				PD.m_PSHPT = ThisPanza->Shape_Type();
				PD.m_PSIZT = ThisPanza->Size_Type();

				NewStream.write(&PD, sizeof(PanzaData));
			}
			else if (L"Bottom" == OneName)
			{
				TypeData TD;
				BottomData BOD;

				TD.m_Type = MAP_TYPE::BOTTOM;
				NewStream.write(&TD, sizeof(TypeData));

				std::vector<KVector2> ThisVert = *(*S_One)->Get_Component<KRigid_2D>()->Mesh_Data();
				int VertSize = ThisVert.size();
				NewStream.write(&VertSize, sizeof(int));

				for (int i = 0; i < VertSize; i++)
				{
					NewStream.write(&ThisVert[i], sizeof(KVector2));
				}
			}
			else if (L"Launcher" == OneName)
			{
				TypeData TD;
				LauncherData LD;
				std::list<KPtr<Bird>> BL = (*S_One)->Get_Component<Bird_Launcher>()->BirdList();
				std::list<KPtr<Bird>>::iterator SBL = BL.begin();
				std::list<KPtr<Bird>>::iterator EBL = BL.end();

				TD.m_Type = MAP_TYPE::LAUNCHER;
				NewStream.write(&TD, sizeof(TypeData));

				int* TempScore = (*S_One)->Get_Component<Bird_Launcher>()->HighScore();

				for (size_t i = 0; i < 3; i++)
				{
					LD.HighScore[i] = TempScore[i];
				}
				LD.m_Trans.m_Vector3 = (*S_One)->Local_Pos().m_Vector3;
				LD.Size = BL.size();
				NewStream.write(&LD, sizeof(LauncherData));


				for (; SBL != EBL; ++SBL)
				{
					NewStream.write(&(*SBL)->Bird_Type(), sizeof(Bird::BIRD_TYPE));
				}
			}

			else if (L"Pig" == OneName)
			{
				TypeData TD;
				PigData PD;

				TD.m_Type = MAP_TYPE::PIG;
				NewStream.write(&TD, sizeof(TypeData));

				PD.Trans.m_Vector3 = (*S_One)->Local_Pos().m_Vector3;
				PD.Trans.m4 = (*S_One)->transform()->Local_Rotate_Degree().z;
				PD.Size = (*S_One)->Get_Component<Pig>()->Size_Type();
				NewStream.write(&PD, sizeof(PigData));
			}

			else if (L"Grass" == OneName)
			{
				TypeData TD;
				GrassData GD;

				TD.m_Type = MAP_TYPE::GRASS;
				NewStream.write(&TD, sizeof(TypeData));

				GD.Trans.m_Vector3 = (*S_One)->Local_Pos().m_Vector3;
				GD.Trans.m4 = (*S_One)->transform()->Local_Rotate_Degree().z;
				GD.ImageNumber = (*S_One)->Get_Component<Renderer_Sprite>()->index();
				NewStream.write(&GD, sizeof(GrassData));
			}
			else if (L"Bomb" == OneName)
			{
				TypeData TD;
				BombData BD;

				TD.m_Type = MAP_TYPE::BOMB;
				NewStream.write(&TD, sizeof(TypeData));

				BD.Trans.m_Vector3 = (*S_One)->Local_Pos().m_Vector3;
				BD.Trans.m4 = (*S_One)->transform()->Local_Rotate_Degree().z;
				NewStream.write(&BD, sizeof(BombData));
			}
		}
	}
}

void Map_Data::Map_Load(KPtr<State> _State, const wchar_t* _Path)
{
	Map_Erase(_State);

	ReadStream NewStream = ReadStream(_Path);

	int Size = 0;

	NewStream.read(&Size, sizeof(int));

	if (Size == 0)
	{
		return;
	}



	for (int i = 0; i < Size; i++)
	{
		TypeData TD;
		NewStream.read(&TD, sizeof(TypeData));

		KPtr<TheOne> NewOne = _State->Create_TheOne();

		switch (TD.m_Type)
		{
		case MAP_TYPE::BOTTOM:
		{
			int VSize = 0;
			NewStream.read(&VSize, sizeof(int));
			NewOne->Add_Component<Bottom>();

			std::vector<KVector2> NewVert;
			NewVert.reserve(VSize);

			for (int i = 0; i < VSize; i++)
			{
				KVector2 Temp;
				NewStream.read(&Temp, sizeof(KVector2));
				NewVert.push_back(Temp);
			}

			NewOne->Get_Component<KRigid_2D>()->Insert_VertexList(NewVert);
			NewOne->Get_Component<KRigid_2D>()->ColDown();
			break;
		}
		case MAP_TYPE::PANZA:
		{
			PanzaData PD;
			NewStream.read(&PD, sizeof(PanzaData));

			NewOne->Add_Component<Panza>(PD.m_PMATT, PD.m_PSHPT, PD.m_PSIZT);
			NewOne->Local_Pos(PD.m_Trans.m_Vector3);
			NewOne->Local_Rotate({ .0f, .0f, PD.m_Trans.m4 , .0f });
			NewOne->name(L"Panza");
			break;
		}
		case MAP_TYPE::LAUNCHER:
		{
			LauncherData LD;
			NewStream.read(&LD, sizeof(LauncherData));

			KPtr<Bird_Launcher> BL = NewOne->Add_Component<Bird_Launcher>();
			Container_Class::Insert_BirdLauncher(_State, BL);

			BL->HighScore(LD.HighScore);
			NewOne->Local_Pos(LD.m_Trans.m_Vector3);
			NewOne->name(L"Launcher");

			for (int i = 0; i < LD.Size; i++)
			{
				Bird::BIRD_TYPE BT;
				NewStream.read(&BT, sizeof(Bird::BIRD_TYPE));
				BL->CreateBird(BT);
			}

			break;
		}

		case MAP_TYPE::BOMB:
		{
			BombData BD;
			NewStream.read(&BD, sizeof(BombData));

			NewOne->Add_Component<Bomb>();
			NewOne->Local_Pos(BD.Trans.m_Vector3);
			NewOne->Local_Rotate({ .0f, .0f, BD.Trans.m4 , .0f });
			NewOne->name(L"Bomb");

			break;
		}

		case MAP_TYPE::GRASS:
		{
			GrassData GD;
			NewStream.read(&GD, sizeof(GrassData));

			KPtr<Grass> NewGrass = NewOne->Add_Component<Grass>(GD.ImageNumber);
			NewGrass->Col_One()->Local_Pos(GD.Trans.m_Vector3);
			NewOne->Local_Rotate({ .0f, .0f, GD.Trans.m4 , .0f });
			NewOne->name(L"Grass");

			break;
		}

		case MAP_TYPE::PIG:
		{
			PigData PD;
			NewStream.read(&PD, sizeof(PigData));

			NewOne->Add_Component<Pig>(PD.Size);
			NewOne->Local_Pos(PD.Trans.m_Vector3);
			NewOne->Local_Rotate({ .0f, .0f, PD.Trans.m4 , .0f });
			NewOne->name(L"Pig");

			break;
		}

		default:
			break;
		}
	}
}



void Map_Data::Map_Erase(KPtr<State> _State)
{
	m_MapList = *(_State->All_One());

	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator S_MAP = m_MapList.begin();
	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator E_MAP = m_MapList.end();
	for (; S_MAP != E_MAP; ++S_MAP)
	{
		std::list<KPtr<TheOne>>::iterator S_One = S_MAP->second.begin();
		std::list<KPtr<TheOne>>::iterator E_One = S_MAP->second.end();

		for (; S_One != E_One; )
		{
			std::wstring OneName = (*S_One)->name();

			if (L"Panza" == OneName ||
				L"Bottom" == OneName ||
				L"Launcher" == OneName ||
				L"Bird" == OneName ||
				L"Pig" == OneName ||
				L"Bomb" == OneName ||
				L"Grass" == OneName)
			{
				(*S_One)->set_Death();
				S_One = S_MAP->second.erase(S_One);
				continue;
			}
			++S_One;
		}
	}
}

size_t Map_Data::Map_Count(KPtr<State> _State)
{
	size_t Count = 0;
	m_MapList = *(_State->All_One());

	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator S_MAP = m_MapList.begin();
	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator E_MAP = m_MapList.end();
	for (; S_MAP != E_MAP; ++S_MAP)
	{
		std::list<KPtr<TheOne>>::iterator S_One = S_MAP->second.begin();
		std::list<KPtr<TheOne>>::iterator E_One = S_MAP->second.end();

		for (; S_One != E_One; ++S_One)
		{
			std::wstring OneName = (*S_One)->name();

			if (L"Panza" == OneName ||
				L"Bottom" == OneName ||
				L"Launcher" == OneName ||
				L"Bird" == OneName ||
				L"Pig" == OneName ||
				L"Bomb" == OneName ||
				L"Grass" == OneName)
			{
				++Count;
			}
		}
	}

	return Count;
}

size_t Map_Data::Save_Count(KPtr<State> _State)
{
	size_t Count = 0;
	m_MapList = *(_State->All_One());

	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator S_MAP = m_MapList.begin();
	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator E_MAP = m_MapList.end();
	for (; S_MAP != E_MAP; ++S_MAP)
	{
		std::list<KPtr<TheOne>>::iterator S_One = S_MAP->second.begin();
		std::list<KPtr<TheOne>>::iterator E_One = S_MAP->second.end();

		for (; S_One != E_One; ++S_One)
		{
			std::wstring OneName = (*S_One)->name();

			if (L"Panza" == OneName ||
				L"Bottom" == OneName ||
				L"Launcher" == OneName ||
				L"Pig" == OneName ||
				L"Bomb" == OneName ||
				L"Grass" == OneName)
			{
				++Count;
			}
		}
	}

	return Count;
}

size_t Map_Data::CountingStar()
{
	int ScoreData[3] = {};
	int LScore = Container_Class::This_BirdLauncher()->GameScore();

	for (size_t i = 0; i < 3; i++)
	{
		ScoreData[i] = Container_Class::This_BirdLauncher()->HighScore()[i];
	}


	// 최대 점수
	if (ScoreData[2] < LScore)
	{
		return 3;
	}
	// 최저 점수
	if (ScoreData[1] > LScore)
	{
		return 1;
	}
	// 나머지 - 두 개
	return 2;
}