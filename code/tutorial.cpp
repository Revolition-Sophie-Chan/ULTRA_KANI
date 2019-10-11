//=============================================================================
//
// チュートリアルの処理[tutorial.cpp]
// Author：tanaka rikiya
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
// グローバル変数
//=============================================================================
int g_nCounterTutorialstate = 0;
TUTORIALSTATE g_TutorialState = TUTORIALSTATE_NONE;
LPD3DXFONT			g_pMessageFont = NULL;	// フォントへのポインタ
LPDIRECT3DDEVICE9	g_pMessageD3DDevice = NULL;	// Direct3Dデバイスへのポインタ(描画に必要)
//PLAYER *pPlayer;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTutorial(void)
{
	// カメラの終了処理
	InitCamera();
	
	InitMoji();

	// ライトの終了処理
	InitLight();

	// 3Dポリゴンの終了処理
	InitMeshField();

	InitMeshTenjo();

	InitMeshTenjoUp();
	//モデル
	InitPlayer();

	//影の
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
// 終了処理
//=============================================================================
void UninitTutorial(void)
{

	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	UninitMoji();

	// 3Dポリゴンの終了処理
	UninitMeshField();
	UninitMeshTenjo();
	UninitMeshTenjoUp();
	//モデル
	UninitPlayer();

	//影の
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
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	TEXT *pText;
	pText = GetText();

	// カメラの終了処理
	UpdateCamera();

	UpdateMoji();

	// ライトの終了処理
	UpdateLight();

	// 3Dポリゴンの終了処理
	UpdateMeshField();

	UpdateMeshTenjo();

	UpdateMeshTenjoUp();
	//モデル
	UpdatePlayer();


	//影の
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
// びょうが処理
//=============================================================================
void DrawTutorial(void)
{
	TEXT *pText;
	pText = GetText();

	SetCamera();
	// 3Dポリゴンの終了処理
	DrawMeshField();


	//DrawMeshTenjoUp();
	DrawMeshTenjo();
	//モデル
	DrawPlayer();
	DrawMeshTenjoUp();
	DrawMoji();

	//影の
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
// 設定
//=============================================================================
void SetTutorialState(TUTORIALSTATE state)
{
	g_TutorialState = state;
	g_nCounterTutorialstate = 0;
}
//=============================================================================
// ゲーム状態の取得
//=============================================================================
TUTORIALSTATE GetTutorialState(void)
{
	return g_TutorialState;
}