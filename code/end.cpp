//=============================================================================
//
// 終了の処理[End.cpp]
// Author：tanaka rikiya
//
//=============================================================================
//インクルードファイル
#include"main.h"
#include"Player.h"
#include"input.h"
#include"fade.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "sound.h"
#include "title.h"
#include "sound.h"
#include "effect.h"
#include "text.h"
//#include "joystick.h"

//#include"End.h"

//=============================================================================
//グローバル変数
//=============================================================================
//VERTEX_2D g_aVertex[4];
LPDIRECT3DTEXTURE9 g_pTextureEnd = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnd = NULL;//頂点バッファへのポインタ
//int g_nCounterTitleFade;
//=============================================================================
// ポリゴンの初期化
//=============================================================================
void InitEnd(void)
{

	InitCamera();
	InitPlayer();

	// カメラの終了処理
	InitCamera();

	// ライトの終了処理
	InitLight();

	// 3Dポリゴンの終了処理
	InitMeshField();

	InitEffect();

	InitMoji();


	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/game_over.png",
		&g_pTextureEnd);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnd,
		NULL);

	VERTEX_2D *pVtx;//頂点情報へのポインタ
					//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffEnd->Lock(0, 0, (void**)&pVtx, 0);
	//頂点の設定	

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 720, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280, 720, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	////テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データのアンロック
	g_pVtxBuffEnd->Unlock();
	
	SetText(D3DXVECTOR3(630.0f, 600.0f, 000.0f), 130, 30, 0);
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void UninitEnd(void)
{
	//UninitSound();
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// 3Dポリゴンの終了処理
	UninitMeshField();

	UninitEffect();

	UninitMoji();

}
//=============================================================================
// polygon更新処理
//=============================================================================
void UpdateEnd(void)
{

	// カメラの終了処理
	UpdateCamera();

	// ライトの終了処理
	UpdateLight();

	// 3Dポリゴンの終了処理
	UpdateMeshField();

	UpdateEffect();

	UpdateMoji();
	//g_nCounterTitleFade++;
	//if (g_nCounterTitleFade >= 120)
	//{
	//	SetFade(MODE_TITLE);
	//	g_nCounterTitleFade = 0;
	//}
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(MODE_TITLE);
	}
}
//=============================================================================
// ポリゴン描画
//=============================================================================
void DrawEnd(void)
{
	SetCamera();
	// 3Dポリゴンの終了処理
	DrawMeshField();

	DrawEffect();

	DrawMoji();

	LPDIRECT3DDEVICE9 pDevice;
	////バックバッファとフロントバッファの入れかえ
	//g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, g_pTextureEnd);
	//頂点バッファをデバイスのデータストリートにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffEnd, 0, sizeof(VERTEX_2D));
	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}