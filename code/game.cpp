//=============================================================================
//
// ゲーム本編の処理[game.cpp]
// Author：tanaka rikiya
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
// グローバル変数
//=============================================================================
int g_nCounterGamestate = 0;
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterEnemy = 0;
int g_nCountItem = 0;
PLAYER *pPlayer;
//=============================================================================
// 初期化処理
//=============================================================================
void InitGame(void)
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

	//ハート
	InitHeart();


	//影の
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
// 終了処理
//=============================================================================
void UninitGame(void)
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

	//ハート
	UninitHeart();


	//影の
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
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	
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

	//ハート
	UpdateHeart();


	//影の
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
	//	// カメラの終了処理
	//}

	switch (g_gameState)
	{
	case GAMESTATE_END:
 	
		g_nCounterGamestate++;
		if (g_nCounterGamestate >= 60)
		{
			SaveData(GetScore());
			LoadData();
			//画面モードの設定
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
			//画面モードの設定
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
// びょうが処理
//=============================================================================
void DrawGame(void)
{

	SetCamera();


	DrawMeshField();




	//モデル
	DrawPlayer();

	//影の
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
	//網
	Drawami();

	DrawExplosion();



	//ハート
	DrawHeart();


	DrawMoji();

	DrawScore();
}
//=============================================================================
// 設定
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGamestate = 0;
}
//=============================================================================
// ゲーム状態の取得
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

int *GetGameEnemyCounter()
{
	return &g_nCounterEnemy;
}
