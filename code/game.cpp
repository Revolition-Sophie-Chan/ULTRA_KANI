//=============================================================================
//
// �Q�[���{�҂̏���[game.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include"game.h"
#include <time.h>
#include"Player.h"
#include"explosion.h"
#include"tutorial.h"
#include"effect.h"
#include"fade.h"
#include"input.h"
#include"camera.h"
#include"light.h"
#include"meshField.h"
#include"meshwall.h"
//#include"shadow.h"
#include"nakama.h"
#include"enemy.h"
#include"item.h"
#include"ami.h"
#include"text.h"
#include"load.h"
#include"save.h"
#include"score.h"
#include"MeshTenjo.h"
#include"MeshTenjoUp.h"
#include"haikei.h"
#include"sound.h"
#include"heart.h"
#include"nakama_pointer.h"
#include"object.h"


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int g_nCounterGamestate = 0;
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterEnemy = 0;
int g_nCountItem = 0;
PLAYER *pPlayer;
//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	// �J�����̏I������
	InitCamera();

	InitMoji();

	// ���C�g�̏I������
	InitLight();

	// 3D�|���S���̏I������
	InitMeshField();

	InitMeshTenjo();

	InitMeshTenjoUp();
	//���f��
	InitPlayer();

	//�n�[�g
	InitHeart();


	//�e��
	//InitShadow();

	//
	InitMeshWall();


	InitExplosion();


	InitEffect();

	InitItem();

	Initami();

	Initnakama();

	InitEnemy();
	InitObject();

	InitHaikei();

	InitScore();

	InitPointer();
	
	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGamestate;

	SetEnemy(D3DXVECTOR3(-800.0f, 270.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_GYOSEN);

	SetText(D3DXVECTOR3(950.0f, 650.0f, 000.0f), 130, 40, 2);

}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	UninitMoji();

	// 3D�|���S���̏I������
	UninitMeshField();
	UninitMeshTenjo();
	UninitMeshTenjoUp();
	//���f��
	UninitPlayer();

	//�n�[�g
	UninitHeart();


	//�e��
	//UninitShadow();

	//
	UninitMeshWall();


	UninitExplosion();


	UninitEffect();

	UninitItem();

	Uninitami();


	Uninitnakama();

	UninitEnemy();
	UninitObject();

	UninitScore();

	UninitHaikei();

	UninitPointer();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	
	// �J�����̏I������
	UpdateCamera();

	UpdateMoji();

	// ���C�g�̏I������
	UpdateLight();

	// 3D�|���S���̏I������
	UpdateMeshField();

	UpdateMeshTenjo();

	UpdateMeshTenjoUp();
	//���f��
	UpdatePlayer();

	//�n�[�g
	UpdateHeart();


	//�e��
	//UpdateShadow();

	//
	UpdateMeshWall();

	UpdateExplosion();

	UpdateEffect();

	Updatenakama();

	UpdateItem();

	Updateami();

	UpdateEnemy();
	UpdateObject();

	UpdateScore();

	UpdateHaikei();

	UpdatePointer();

	//if (GetKeyboardTrigger(DIK_RETURN))
	//{
	//	g_gameState = GAMESTATE_END;
	//	// �J�����̏I������
	//}

	switch (g_gameState)
	{
	case GAMESTATE_END:
 	
		g_nCounterGamestate++;
		if (g_nCounterGamestate >= 60)
		{
			SaveData(GetScore());
			LoadData();
			//��ʃ��[�h�̐ݒ�
			SetFade(MODE_RESULT);
			g_nCounterGamestate = 0;
		}break;
	case GAMESTATE_BADEND:

		g_nCounterEnemy=0;
		g_nCounterGamestate++;
		if (g_nCounterGamestate >= 60)
		{
			SaveData(GetScore());
			LoadData();
			g_gameState = GAMESTATE_NONE;
			//��ʃ��[�h�̐ݒ�
			SetFade(MODE_END);
		}
	}
	g_nCountItem++;
	if (g_nCountItem >= 540)
	{
		SetItem(D3DXVECTOR3(rand() % 100 / -0.08f, 50.0f, rand() % 50 / 0.08f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		g_nCountItem = 0;
	}

}
//=============================================================================
// �т傤������
//=============================================================================
void DrawGame(void)
{

	SetCamera();


	DrawMeshField();




	//���f��
	DrawPlayer();

	//�e��
	//DrawShadow();

	//
	DrawHaikei();
	DrawMeshWall();
	DrawMeshTenjoUp();
	DrawMeshTenjo();

	Drawnakama();

	DrawEnemy();
	DrawObject();

	DrawItem();





	DrawEffect();

	DrawPointer();
	//��
	Drawami();

	DrawExplosion();



	//�n�[�g
	DrawHeart();


	DrawMoji();

	DrawScore();
}
//=============================================================================
// �ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGamestate = 0;
}
//=============================================================================
// �Q�[����Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

int *GetGameEnemyCounter()
{
	return &g_nCounterEnemy;
}
