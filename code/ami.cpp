//=============================================================================
//
// 網処理 [ami.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "ami.h"
#include "main.h"
#include "Camera.h"
#include "effect.h"
#include "nakama.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define AMIWIDTH	(30)	//テクスチャの幅
#define AMHEIGHT	(50)	//テクスチャの高さ
#define AMI_X	(30)	//テクスチャの幅
#define AMI_Y	(50)	//テクスチャの高さ
#define SPEED	(0.5f)	//テクスチャの高さ

//=============================================================================
// 構造体定義
//=============================================================================
//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureami = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffami = NULL;	// 頂点バッファへのポインタ
AMI g_aami;

//=============================================================================
// 初期化処理
//=============================================================================
void Initami(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	// アイテムの情報の初期化

		g_aami.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.bUse = false;
		g_aami.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aami.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.fAngle = 0.0f;
		g_aami.fLength = 0.0f;


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/ami.png", &g_pTextureami);

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_AMI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffami,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffami->Lock(0, 0, (void**)&pVtx, 0);
//座標設定
	 //アニメーションの更新

		pVtx[0].pos = D3DXVECTOR3(-155.0f, 155.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(155.0f, 155.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-155.0f, -155.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(155.0f, -155.0f, 0.0f);


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
		//pVtx += 4;

	
	// 頂点データをアンロックする
	g_pVtxBuffami->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninitami(void)
{
	// テクスチャの開放
	if (g_pTextureami != NULL)
	{
		g_pTextureami->Release();
		g_pTextureami = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffami != NULL)
	{
		g_pVtxBuffami->Release();
		g_pVtxBuffami = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Updateami(void)
{

	NAKAMA * pNakama;
	//プレイヤーの取得
	pNakama = Getnakama();

	VERTEX_3D *pVtx;
	int nCntami;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffami->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntami = 0; nCntami < MAX_AMI; nCntami++)
	{
		g_aami.pos += g_aami.move;
		if (pNakama->bUse == true)
		{
			Setami(D3DXVECTOR3(pNakama->pos.x, 80.0f, pNakama->pos.z), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.3f, 0.0f), D3DXVECTOR3(0.0f, SPEED, 0.0f));
		}
		else if (pNakama->bUse == false)
		{
			g_aami.bUse = false;
		}
	}

	// 頂点データをアンロックする
	g_pVtxBuffami->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void Drawami(void)
{
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ポリゴンの描画
		if (g_aami.bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aami.mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &g_aami.mtxView);

			g_aami.mtxWorld._11 = g_aami.mtxView._11;
			g_aami.mtxWorld._12 = g_aami.mtxView._21;
			g_aami.mtxWorld._13 = g_aami.mtxView._31;
			g_aami.mtxWorld._21 = g_aami.mtxView._12;
			g_aami.mtxWorld._22 = g_aami.mtxView._22;
			g_aami.mtxWorld._23 = g_aami.mtxView._32;
			g_aami.mtxWorld._31 = g_aami.mtxView._13;
			g_aami.mtxWorld._32 = g_aami.mtxView._23;
			g_aami.mtxWorld._33 = g_aami.mtxView._33;

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aami.rot.y, g_aami.rot.x, g_aami.rot.z);
			D3DXMatrixMultiply(&g_aami.mtxWorld, &g_aami.mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aami.pos.x, g_aami.pos.y, g_aami.pos.z);
			D3DXMatrixMultiply(&g_aami.mtxWorld, &g_aami.mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aami.mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffami, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureami);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
}

//=============================================================================
// 網の設定
//=============================================================================
void Setami(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot,D3DXVECTOR3 move)
{

	NAKAMA * pnakama;
	//プレイヤーの取得
	pnakama = Getnakama();

	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffami->Lock(0, 0, (void**)&pVtx, 0);


		if (g_aami.bUse == false)	//未使用
		{
			g_aami.pos = pos;
			g_aami.col = col;
			g_aami.rot = rot;
			g_aami.move = move;

			//座標設定
			pVtx[0].pos = D3DXVECTOR3(-155.0f, 155.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(155.0f, 155.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-155.0f, -155.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(155.0f, -155.0f, 0.0f);

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


			g_aami.bUse = true;
	}
	// 頂点データをアンロックする
	g_pVtxBuffami->Unlock();
}
//=============================================================================
// 網の取得
//=============================================================================
AMI *Getami(void)
{
	return &g_aami;
}

