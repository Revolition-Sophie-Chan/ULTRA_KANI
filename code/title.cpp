//=============================================================================
//
// タイトルの処理[Title.cpp]
// Author：tanaka rikiya
//
//=============================================================================
//インクルードファイル
#include "main.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "sound.h"
#include "title.h"
#include "text.h"
#include "effect.h"

//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
VERTEX_3D g_aVertex[4];
int g_nCounterFade;

//=============================================================================
// ポリゴンの初期化
//=============================================================================
void InitTitle(void)
{
	// カメラの終了処理
	InitCamera();

	// ライトの終了処理
	InitLight();

	// 3Dポリゴンの終了処理
	InitMeshField();

	InitMoji();

	InitEffect();

	SetText(D3DXVECTOR3(620.0f, 270.0f, 000.0f),530,180,1);

	SetText(D3DXVECTOR3(630.0f, 600.0f, 000.0f), 130, 30, 0);
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void UninitTitle(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// 3Dポリゴンの終了処理
	UninitMeshField();

	UninitMoji();

	UninitEffect();
}
//=============================================================================
// polygon更新処理
//=============================================================================
void UpdateTitle(void)
{

	// カメラの終了処理
	UpdateCamera();

	// ライトの終了処理
	UpdateLight();

	// 3Dポリゴンの終了処理
	UpdateMeshField();

	UpdateMoji();

	UpdateEffect();

	g_nCounterFade++;
	if (g_nCounterFade >= 520)
	{
		SetFade(MODE_RANKING);
		g_nCounterFade = 0;
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(MODE_TUTORIAL0);
		g_nCounterFade = 0;
	}
}

//=============================================================================
// 描画
//=============================================================================
void DrawTitle(void)
{
	SetCamera();
	// 3Dポリゴンの終了処理
	DrawMeshField();

	DrawMoji();

	DrawEffect();
}