//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "effect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_EFFECT0		"Data/Texture/effect000.jpg"	//読み込むテクスチャファイル名
#define	TEXTURE_EFFECT1		"Data/Texture/effect001.jpg"	//読み込むテクスチャファイル名
#define	TEXTURE_EFFECT2		"Data/Texture/effect002.jpg"	//読み込むテクスチャファイル名
#define	MAX_EFFECT	(2008)							//エフェクトの最大数
#define TEXWIDTH	(20)							//テクスチャの幅
#define TEXHEIGHT	(20)							//テクスチャの高さ
#define MAX_EFFECT_TEXTURE	(3)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_EFFECT_TEXTURE]={};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ

EFFECT					g_aEffect[MAX_EFFECT];		// エフェクト情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;

	for(nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].fSpeed = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].nType = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	// テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,	//取得
		TEXTURE_EFFECT0,
		&g_pTextureEffect[0]);

	D3DXCreateTextureFromFile(pDevice,	//強化
		TEXTURE_EFFECT1,
		&g_pTextureEffect[1]);

	D3DXCreateTextureFromFile(pDevice,	//泡
		TEXTURE_EFFECT2,
		&g_pTextureEffect[2]);

	// 頂点情報の作成
	MakeVertexEffect(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT_TEXTURE; nCntEffect++)
	{
		// テクスチャの開放
		if (g_pTextureEffect[nCntEffect] != NULL)
		{
			g_pTextureEffect[nCntEffect]->Release();
			g_pTextureEffect[nCntEffect] = NULL;
		}
	}

	// 頂点バッファの開放
	if(g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{

	int nCntEffect;
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;
			g_aEffect[nCntEffect].col.a -= 0.008f;
			g_aEffect[nCntEffect].fRadius -= 0.1f;;
			g_aEffect[nCntEffect].nLife--;

			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aEffect[nCntEffect].col.a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aEffect[nCntEffect].col.a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aEffect[nCntEffect].col.a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aEffect[nCntEffect].col.a);

		}
		if (g_aEffect[nCntEffect].nLife <= 0)
		{
			g_aEffect[nCntEffect].bUse = false;
		}
		pVtx += 4;

	}
	//頂点データをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxView;//計算用マトリックス
	int nCntEffect;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// レンダーステート(加算合成処理)
	pDevice->SetRenderState(D3DRS_BLENDOP,	 D3DBLENDOP_ADD);			//計算方式
	pDevice->SetRenderState(D3DRS_SRCBLEND,	 D3DBLEND_SRCALPHA);	//αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//αディスとネーションカラーの指定

	// Zテストの設定を戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	// Zテストは常にパスする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// ポリゴンの描画
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEffect[nCntEffect].rot.y, g_aEffect[nCntEffect].rot.x, g_aEffect[nCntEffect].rot.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}


	// レンダーステート(通常ブレンド処理)
	pDevice->SetRenderState(D3DRS_BLENDOP,	 D3DBLENDOP_ADD);		//計算方式
	pDevice->SetRenderState(D3DRS_SRCBLEND,	 D3DBLEND_SRCALPHA);	//αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//αディスとネーションカラーの指定



	// Zテストの設定
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntEffect;
	VERTEX_3D *pVtx;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		//座標設定
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

		//アニメーションの更新
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = g_aEffect[nCntEffect].col;
		pVtx[1].col = g_aEffect[nCntEffect].col;
		pVtx[2].col = g_aEffect[nCntEffect].col;
		pVtx[3].col = g_aEffect[nCntEffect].col;
		pVtx += 4;
	}

	// 頂点データをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// エフェクト設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius,int nLife, D3DXCOLOR col,int nType)
{
	int nCntEffect;
	VERTEX_3D *pVtx;

	// 頂点情報の設定
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			//g_aEffect[nCntEffect].rot = rot;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].nType = nType;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffEffect->Unlock();
}