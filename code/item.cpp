//=============================================================================
//
// アイテム処理 [Item.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "Item.h"
#include "main.h"
#include "Camera.h"
#include "effect.h"
#include "player.h"
#include "score.h"


//=============================================================================
// マクロ定義
//=============================================================================
#define ITEMWIDTH	(30)	//テクスチャの幅
#define ITEMHEIGHT	(50)	//テクスチャの高さ
#define ITEM_X		(30)	//テクスチャの幅
#define ITEM_Y		(50)	//テクスチャの高さ
#define HITSIZE_X	(50)
#define HITSIZE_Y	(50)
#define ITEMCOUNT	(20)
#define MAX_P	(11)//プレイヤーのパーツ数

//=============================================================================
// 構造体定義
//=============================================================================
//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// 頂点バッファへのポインタ
ITEM g_aItem;

//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	int nCntItem;

	// アイテムの情報の初期化
		g_aItem.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem.bUse = false;
		g_aItem.bItem = false;
		g_aItem.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aItem.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/chikuwa.png", &g_pTextureItem);

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem<MAX_ITEM; nCntItem++)
	{//座標設定
	 //アニメーションの更新

		pVtx[0].pos = D3DXVECTOR3(-25.0f, 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(25.0f, 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-25.0f, -25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(25.0f, -25.0f, 0.0f);


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

	}
	// 頂点データをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	// テクスチャの開放
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{


	VERTEX_3D *pVtx;

	PLAYER * pPlayer;
	//プレイヤーの取得
	pPlayer = GetPlayer();

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//g_aItem[1].pos += g_aItem[1].move.y;
	for (int nCountPlayer = 0; nCountPlayer < MAX_P; nCountPlayer++)
	{
		if (g_aItem.bUse == true)
		{
			if (pPlayer[nCountPlayer].pos.x + HITSIZE_X / 2 >= g_aItem.pos.x &&
				pPlayer[nCountPlayer].pos.x - HITSIZE_X / 2 <= g_aItem.pos.x &&
				pPlayer[nCountPlayer].pos.z + HITSIZE_Y / 2 >= g_aItem.pos.z &&
				pPlayer[nCountPlayer].pos.z - HITSIZE_Y / 2 <= g_aItem.pos.z)
			{
				g_aItem.bUse = false;
				g_aItem.bItem = true;	//アイテム取得
				if (g_aItem.bUse == false)
				{
					MakeEffect_Item();
				}
				for (int nCnt = 0; nCnt < ITEMCOUNT; nCnt++)
				{
					// 0～3.14を出す * (0 or 1)* -1で正負を決める(出す範囲)
					//fAngle = (rand() % 628 / 100.0f) * (rand() % 2) * -1;	// 全方向出す

					// 発生位置
					D3DXVECTOR3 pos = D3DXVECTOR3(g_aItem.pos.x, g_aItem.pos.y, g_aItem.pos.z);
				}
				//break;
				// 爆発を起こす
				// 爆発を起こす


			}
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点データをアンロックする
			g_pVtxBuffItem->Unlock();
		}
	}


}
//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ポリゴンの描画

	if (g_aItem.bUse == true)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aItem.mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &g_aItem.mtxView);

		g_aItem.mtxWorld._11 = g_aItem.mtxView._11;
		g_aItem.mtxWorld._12 = g_aItem.mtxView._21;
		g_aItem.mtxWorld._13 = g_aItem.mtxView._31;
		g_aItem.mtxWorld._21 = g_aItem.mtxView._12;
		g_aItem.mtxWorld._22 = g_aItem.mtxView._22;
		g_aItem.mtxWorld._23 = g_aItem.mtxView._32;
		g_aItem.mtxWorld._31 = g_aItem.mtxView._13;
		g_aItem.mtxWorld._32 = g_aItem.mtxView._23;
		g_aItem.mtxWorld._33 = g_aItem.mtxView._33;


		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aItem.pos.x, g_aItem.pos.y, g_aItem.pos.z);
		D3DXMatrixMultiply(&g_aItem.mtxWorld, &g_aItem.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aItem.mtxWorld);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureItem);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// アイテムの設定
//=============================================================================
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
		if (g_aItem.bUse == false)	//未使用
		{
			g_aItem.pos = pos;
			g_aItem.col = col;;

			//座標設定
			pVtx[0].pos = D3DXVECTOR3(-25.0f, 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(25.0f, 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-25.0f, -25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(25.0f, -25.0f, 0.0f);

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

			g_aItem.bUse = true;
		//pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffItem->Unlock();
}
//=============================================================================
// アイテムの取得
//=============================================================================
ITEM *GetItem(void)
{
	return &g_aItem;
}
//=======================================================================================
// パーティクル関数
//=======================================================================================
void MakeEffect_Item(void)
{
	int nCntItem = 0;
	//////////////////// 爆発の設定 ////////////////////
	D3DXCOLOR col	= D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	float fRadius	= 20.0f;
	float fAngle	= 0.0f;
	float fSpeed	= 15.0f;
	int nLife		= 20;
	////////////////////////////////////////////////////
	for (int nCnt = 0; nCnt < 60; nCnt++)
	{
		// 0～3.14を出す * (0 or 1)* -1で正負を決める(出す範囲)
		fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;	// 全方向出す

																				// 発生位置
		D3DXVECTOR3 pos1 = D3DXVECTOR3(g_aItem.pos.x, g_aItem.pos.y, g_aItem.pos.z);

		// 出す向き
		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed, 0.0f);
		D3DXVECTOR3 move1 = D3DXVECTOR3(sinf(fAngle)*fSpeed, 0.0f, cosf(fAngle)*fSpeed);
		D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed);

		// エフェクトの設定
		SetEffect(pos1, move, fRadius, nLife, col, 0);
		SetEffect(pos1, move1, fRadius, nLife, col, 0);
		SetEffect(pos1, move2, fRadius, nLife, col, 0);
	}
}