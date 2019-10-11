//=============================================================================
//
// 体力処理 [heart.cpp]
// Author : Tanaka rikiya
//
//=============================================================================
#include "heart.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_HEART		"Data/Texture/heart.png"	// 読み込むテクスチャファイル名
#define TEXWIDTH	(150)	//テクスチャの幅
#define TEXHEIGHT	(150)	//テクスチャの高さ
#define MAXHEARTNUM	(3)

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
	int nNum;
}heart;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexheart(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureheart = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffheart = NULL;	// 頂点バッファへのポインタ
heart  g_aheart[MAXHEARTNUM];
int	g_nheart;				// 体力

//=============================================================================
// 初期化処理
//=============================================================================
void InitHeart(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nheart = 6;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXHEARTNUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffheart,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_HEART,		// ファイルの名前
		&g_pTextureheart);	// 読み込むメモリー

							// 頂点情報の作成
	MakeVertexheart(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHeart(void)
{
	// テクスチャの開放

	if (g_pTextureheart != NULL)
	{
		g_pTextureheart->Release();
		g_pTextureheart = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffheart != NULL)
	{
		g_pVtxBuffheart->Release();
		g_pVtxBuffheart = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHeart(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHeart(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntheart;

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffheart, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureheart);

	// ポリゴンの描画
	for (nCntheart = 0; nCntheart < MAXHEARTNUM; nCntheart++)
	{
		//pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntheart * 4, 2);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexheart(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntheart;
	VERTEX_2D *pVtx;
	// オブジェクトの頂点バッファを生成

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffheart->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	for (nCntheart = 0; nCntheart < MAXHEARTNUM; nCntheart++)
	{
		g_aheart[nCntheart].pos = D3DXVECTOR3(80.0f + TEXWIDTH * nCntheart * 1.0f, 80.0f, 0.0f);
		g_aheart[nCntheart].nNum = 0;

		//座標設定
		pVtx[0].pos = D3DXVECTOR3(g_aheart[nCntheart].pos.x - TEXWIDTH / 2, g_aheart[nCntheart].pos.y - TEXHEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aheart[nCntheart].pos.x + TEXWIDTH / 2, g_aheart[nCntheart].pos.y - TEXHEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aheart[nCntheart].pos.x - TEXWIDTH / 2, g_aheart[nCntheart].pos.y + TEXHEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aheart[nCntheart].pos.x + TEXWIDTH / 2, g_aheart[nCntheart].pos.y + TEXHEIGHT / 2, 0.0f);

		//アニメーションの更新
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.33f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.33f, 1.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx += 4;
	}

	// 頂点データをアンロックする
	g_pVtxBuffheart->Unlock();
}

//=============================================================================
// スコアの変更
//=============================================================================
void AddHeart(int nValue)
{
	VERTEX_2D *pVtx;
	g_nheart += nValue;
	int nCntheart;

	int nFullHeart = g_nheart / 2;
	int nHalfHeart = g_nheart % 2;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffheart->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntheart = 0; nCntheart < MAXHEARTNUM; nCntheart++)
	{
		if (nCntheart < nFullHeart)
		{
			g_aheart[nCntheart].nNum = 0;
		}
		else if (nCntheart >= nFullHeart && nCntheart < nFullHeart + nHalfHeart)
		{
			g_aheart[nCntheart].nNum = 1;
		}
		else
		{
			g_aheart[nCntheart].nNum = 2;
		}

		//テクスチャ座標設定
		pVtx[0].tex = D3DXVECTOR2(g_aheart[nCntheart].nNum*0.33f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aheart[nCntheart].nNum*0.33f + 0.33f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aheart[nCntheart].nNum*0.33f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aheart[nCntheart].nNum*0.33f + 0.33f, 1.0f);

		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffheart->Unlock();
}