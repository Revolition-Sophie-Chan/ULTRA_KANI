//=============================================================================
//
// �`���[�g���A���̏���[tutorial.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include <time.h>
#include"Player.h"
#include"tutorial.h"
#include"effect.h"
#include"fade.h"
#include"input.h"
#include"camera.h"
#include"light.h"
#include"meshField.h"
#include"meshwall.h"
#include"nakama.h"
#include"enemy.h"
#include"item.h"
#include"ami.h"
#include"text.h"
#include"score.h"
#include"MeshTenjo.h"
#include"MeshTenjoUp.h"
#include"sound.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int g_nCounterTutorialstate = 0;
TUTORIALSTATE g_TutorialState = TUTORIALSTATE_NONE;
LPD3DXFONT			g_pMessageFont = NULL;	// �t�H���g�ւ̃|�C���^
LPDIRECT3DDEVICE9	g_pMessageD3DDevice = NULL;	// Direct3D�f�o�C�X�ւ̃|�C���^(�`��ɕK�v)
//PLAYER *pPlayer;
//=============================================================================
// ����������
//=============================================================================
void InitTutorial(void)
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

	//�e��
	//InitShadow();

	//
	InitMeshWall();

	InitEffect();

	InitItem();

	Initami();

	Initnakama();

	InitEnemy();

	InitScore();

	g_TutorialState = TUTORIALSTATE_NORMAL;
	g_nCounterTutorialstate;

	SetText(D3DXVECTOR3(640.0f, 350.0f, 000.0f), 1280 / 2, 720 / 2, 3);
	SetText(D3DXVECTOR3(630.0f, 600.0f, 000.0f), 130, 30, 0);

}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
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

	//�e��
	//UninitShadow();

	//
	UninitMeshWall();


	UninitEffect();

	UninitItem();

	Uninitami();

	Uninitnakama();

	UninitEnemy();

	UninitScore();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	TEXT *pText;
	pText = GetText();

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


	//�e��
	//UpdateShadow();

	//
	UpdateMeshWall();

	UpdateEffect();

	Updatenakama();

	UpdateItem();

	Updateami();

	UpdateEnemy();

	UpdateScore();



	if (GetKeyboardTrigger(DIK_P)|| GetKeyboardTrigger(DIK_RETURN))
	{
		g_TutorialState = TUTORIALSTATE_NONE;
		SetFade(MODE_GAME);
	}

}
//=============================================================================
// �т傤������
//=============================================================================
void DrawTutorial(void)
{
	TEXT *pText;
	pText = GetText();

	SetCamera();
	// 3D�|���S���̏I������
	DrawMeshField();


	//DrawMeshTenjoUp();
	DrawMeshTenjo();
	//���f��
	DrawPlayer();
	DrawMeshTenjoUp();
	DrawMoji();

	//�e��
	//DrawShadow();

	//
	DrawMeshWall();


	DrawEffect();

	Drawnakama();

	DrawEnemy();

	DrawItem();

	Drawami();

	//DrawScore();

}
//=============================================================================
// �ݒ�
//=============================================================================
void SetTutorialState(TUTORIALSTATE state)
{
	g_TutorialState = state;
	g_nCounterTutorialstate = 0;
}
//=============================================================================
// �Q�[����Ԃ̎擾
//=============================================================================
TUTORIALSTATE GetTutorialState(void)
{
	return g_TutorialState;
}