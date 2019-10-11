//=============================================================================
//
// 仲間ポインター処理 [nakama_pointer.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "nakama_pointer.h"
#include "main.h"
#include "Camera.h"
#include "effect.h"
#include "player.h"
#include "nakama.h"
#include "ami.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POINTERWIDTH	(50)	//テクスチャの幅
#define POINTERHEIGHT	(50)	//テクスチャの高さ
#define POINTER_X		(30)	//テクスチャの幅
#define POINTER_Y		(50)	//テクスチャの高さ
#define HITSIZE_X	(50)
#define HITSIZE_Y	(50)
#define POINTERCOUNT	(20)
#define MAX_TEXTURE	(3)
#define	TEXTURE_NAKAMA0		"Data/Texture/Help_down.png"	//ヘルプアイコン
#define	TEXTURE_NAKAMA1		"Data/Texture/Help_left.png.png"		//左方向ヘルプ
#define	TEXTURE_NAKAMA2		"Data/Texture/Help_right.png.png"	//右方向ヘルプ
#define SPEED	(0.5f)	//テクスチャの高さ
#define POINTSET_Y (85)	//モデルの上にポインターを置く

//=============================================================================
// 構造体定義
//=============================================================================
//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePointer = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPointer = NULL;	// 頂点バッファへのポインタ
POINTER g_aPointer;

D3DXVECTOR3 g_vtxMaxPointer;		//最大値
D3DXVECTOR3 g_vtxMinPointer;		//最小値
int g_nCounterPointer;								//アニメーションカウンター
int g_nPattenPointer;									//アニメーションパターン


//=============================================================================
// 初期化処理
//=============================================================================
void InitPointer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	g_nCounterPointer=0;								//アニメーションカウンター
	g_nPattenPointer =0;									//アニメーションパターン


	// アイテムの情報の初期化

		g_aPointer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPointer.bUse = false;
		g_aPointer.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPointer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPointer.nType = 0;


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAKAMA0,
		&g_pTexturePointer);


	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPointer,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPointer->Lock(0, 0, (void**)&pVtx, 0);

//座標設定
	 //アニメーションの更新

		pVtx[0].pos = D3DXVECTOR3(-POINTERWIDTH, POINTERWIDTH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(POINTERWIDTH, POINTERWIDTH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-POINTERWIDTH, -POINTERWIDTH, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(POINTERWIDTH, -POINTERWIDTH, 0.0f);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);


		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	// 頂点データをアンロックする
	g_pVtxBuffPointer->Unlock();
	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPointer(void)
{

	// テクスチャの開放
	if (g_pTexturePointer != NULL)
	{
		g_pTexturePointer->Release();
		g_pTexturePointer = NULL;
	}


	// 頂点バッファの開放
	if (g_pVtxBuffPointer != NULL)
	{
		g_pVtxBuffPointer->Release();
		g_pVtxBuffPointer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePointer(void)
{

	NAKAMA * pNakama;
	//プレイヤーの取得
	pNakama = Getnakama();
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPointer->Lock(0, 0, (void**)&pVtx, 0);


	g_aPointer.pos += g_aPointer.move;
	if (pNakama->bUse == true)
	{
		g_aPointer.bUse = false;
		SetPointer(D3DXVECTOR3(pNakama->pos.x, pNakama->pos.y + POINTSET_Y, pNakama->pos.z), D3DXVECTOR3(0.0f, SPEED, 0.0f), 0);
	}
	else if (pNakama->bUse == false)
	{
		g_aPointer.bUse = false;
	}
	if (g_aPointer.nType == 0)
	{
		g_nCounterPointer++;
		if (g_nCounterPointer % 40 == 0)
		{
			g_nPattenPointer = (g_nPattenPointer + 1) % 2;
			if (g_nPattenPointer == 0)
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, 0);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, 0);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, 0);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, 0);
			}
			else
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);
			}
		}
		// 頂点データをアンロックする
		g_pVtxBuffPointer->Unlock();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPointer(void)
{

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ポリゴンの描画
	if (g_aPointer.bUse == true)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aPointer.mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &g_aPointer.mtxView);

		g_aPointer.mtxWorld._11 = g_aPointer.mtxView._11;
		g_aPointer.mtxWorld._12 = g_aPointer.mtxView._21;
		g_aPointer.mtxWorld._13 = g_aPointer.mtxView._31;
		g_aPointer.mtxWorld._21 = g_aPointer.mtxView._12;
		g_aPointer.mtxWorld._22 = g_aPointer.mtxView._22;
		g_aPointer.mtxWorld._23 = g_aPointer.mtxView._32;
		g_aPointer.mtxWorld._31 = g_aPointer.mtxView._13;
		g_aPointer.mtxWorld._32 = g_aPointer.mtxView._23;
		g_aPointer.mtxWorld._33 = g_aPointer.mtxView._33;


		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aPointer.pos.x, g_aPointer.pos.y, g_aPointer.pos.z);
		D3DXMatrixMultiply(&g_aPointer.mtxWorld, &g_aPointer.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aPointer.mtxWorld);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxBuffPointer, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);


		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePointer);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// 仲間ポインターの設定
//=============================================================================
void SetPointer(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	VERTEX_3D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPointer->Lock(0, 0, (void**)&pVtx, 0);


	if (g_aPointer.bUse == false)	//未使用
	{
		g_aPointer.pos = pos;
		g_aPointer.move = move;
		g_aPointer.nType = nType;
		g_aPointer.bUse = true;

		pVtx[0].pos = D3DXVECTOR3(-POINTERWIDTH, POINTERWIDTH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(POINTERWIDTH, POINTERWIDTH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-POINTERWIDTH, -POINTERWIDTH, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(POINTERWIDTH, -POINTERWIDTH, 0.0f);

		//アニメーションの更新
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	// 頂点データをアンロックする
	g_pVtxBuffPointer->Unlock();
}
//=============================================================================
// 仲間ポインターの取得
//=============================================================================
POINTER *GetPointer(void)
{
	return &g_aPointer;
}