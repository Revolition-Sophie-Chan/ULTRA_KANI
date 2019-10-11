//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Tanaka rikiya
//
//=============================================================================
#include "score.h"
#include "save.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_SCORE		"Data/Texture/number001.png"	// 読み込むテクスチャファイル名
#define TEXWIDTH	(40)	//テクスチャの幅
#define TEXHEIGHT	(80)	//テクスチャの高さ]
#define MAXSCORENUM	(3)
#define SCORE_POS_X			(1100)
#define SCORE_POS_Y			(648)
#define SCORE_SIZE_X		(45)
#define SCORE_SIZE_Y		(85)

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
	int nNum;
}SCORE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	// 頂点バッファへのポインタ
SCORE  g_aScore[MAXSCORENUM];
int g_nScore;				// スコア

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{

	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		g_aScore[MAXSCORENUM].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[MAXSCORENUM].nNum = 0;
		g_aScore[MAXSCORENUM].bUse = false;


		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		g_nScore = 0;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXSCORENUM,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffScore,
			NULL);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
			TEXTURE_SCORE,		// ファイルの名前
			&g_pTextureScore);	// 読み込むメモリー

		// 頂点情報の作成
		MakeVertexScore(pDevice);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放

	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	// ポリゴンの描画
	for (nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	float nCntScore;
	VERTEX_2D *pVtx;
	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 10, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	for (nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		//座標設定
		pVtx[0].pos = D3DXVECTOR3(SCORE_POS_X - SCORE_SIZE_X / 2 + nCntScore * SCORE_SIZE_X, SCORE_POS_Y - SCORE_SIZE_Y / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCORE_POS_X + SCORE_SIZE_X / 2 + nCntScore * SCORE_SIZE_X, SCORE_POS_Y - SCORE_SIZE_Y / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCORE_POS_X - SCORE_SIZE_X / 2 + nCntScore * SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCORE_POS_X + SCORE_SIZE_X / 2 + nCntScore * SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y / 2, 0.0f);

		//アニメーションの更新
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

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
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// スコアの変更
//=============================================================================
void AddScore(int nValue)
{

	SAVE *pSave;
	pSave = GetSave();
	VERTEX_2D *pVtx;
	g_nScore += nValue;

	int nCntScore;
	int Digits;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		Digits = g_nScore % (int)powf(10.0f, 3.0f - nCntScore) / (int)powf(10.0f, 3.0f - nCntScore - 1.0f);
		
		//テクスチャ座標設定
		pVtx[0].tex = D3DXVECTOR2((Digits*0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((Digits*0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((Digits*0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((Digits*0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// scoreの取得
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}
