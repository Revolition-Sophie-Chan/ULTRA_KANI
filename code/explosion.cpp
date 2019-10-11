//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "explosion.h"
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_EXPLOSION (58)	// 爆発の最大数
#define TEXWIDTH	(40)	//テクスチャの幅
#define TEXHEIGHT	(40)	//テクスチャの高さ
#define POLYGON_SPD	(15.0f)	//移動速度
#define POLYGON_X	(500)	//頂点のX座標
#define POLYGON_Y	(380)	//頂点のY座標

//=============================================================================
// プロトタイプ宣言
//=============================================================================


//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファへのポインタ
EXPLOSION g_aExplosion;

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	// 爆発の情報の初期化

	g_aExplosion.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aExplosion.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aExplosion.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aExplosion.nCounterAnim = 0;
	g_aExplosion.nPattenAnim = 0;
	g_aExplosion.bUse = false;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/bakuhatsu.png", &g_pTextureExplosion);

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	{//座標設定
	 //アニメーションの更新

		pVtx[0].pos = D3DXVECTOR3(-250.0f, 250.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(250.0f, 250.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-250.0f, -250.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(250.0f, -250.0f, 0.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// 頂点データをアンロックする
		g_pVtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);



	if (g_aExplosion.bUse == true)	//爆発使用
	{
		g_aExplosion.nCounterAnim++;
		if (g_aExplosion.nCounterAnim % 7 == 0)
		{
			g_aExplosion.nPattenAnim = (g_aExplosion.nPattenAnim + 1) % 9;

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f + g_aExplosion.nPattenAnim*0.1428f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1428f + g_aExplosion.nPattenAnim*0.1428f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_aExplosion.nPattenAnim*0.1428f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1428f + g_aExplosion.nPattenAnim*0.1428f, 1.0f);

			if (g_aExplosion.nPattenAnim >= 8)
			{
				g_aExplosion.bUse = false;
			}
		}
	}
	// 頂点データをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// ポリゴンの描画
	if (g_aExplosion.bUse == true)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aExplosion.mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &g_aExplosion.mtxView);

		g_aExplosion.mtxWorld._11 = g_aExplosion.mtxView._11;
		g_aExplosion.mtxWorld._12 = g_aExplosion.mtxView._21;
		g_aExplosion.mtxWorld._13 = g_aExplosion.mtxView._31;
		g_aExplosion.mtxWorld._21 = g_aExplosion.mtxView._12;
		g_aExplosion.mtxWorld._22 = g_aExplosion.mtxView._22;
		g_aExplosion.mtxWorld._23 = g_aExplosion.mtxView._32;
		g_aExplosion.mtxWorld._31 = g_aExplosion.mtxView._13;
		g_aExplosion.mtxWorld._32 = g_aExplosion.mtxView._23;
		g_aExplosion.mtxWorld._33 = g_aExplosion.mtxView._33;

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aExplosion.rot.y, g_aExplosion.rot.x, g_aExplosion.rot.z);
		D3DXMatrixMultiply(&g_aExplosion.mtxWorld, &g_aExplosion.mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion.pos.x, g_aExplosion.pos.y, g_aExplosion.pos.z);
		D3DXMatrixMultiply(&g_aExplosion.mtxWorld, &g_aExplosion.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion.mtxWorld);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureExplosion);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//=============================================================================
// 爆発の設定
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot)
{

	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aExplosion.bUse == false)	//未使用
	{
		g_aExplosion.pos = pos;
		g_aExplosion.col = col;
		g_aExplosion.rot = rot;
		g_aExplosion.nCounterAnim = 0;
		g_aExplosion.nPattenAnim = 0;

		pVtx[0].pos = D3DXVECTOR3(-250.0f, 250.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(250.0f, 250.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-250.0f, -250.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(250.0f, -250.0f, 0.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_aExplosion.bUse = true;

	}
	// 頂点データをアンロックする
	g_pVtxBuffExplosion->Unlock();
}