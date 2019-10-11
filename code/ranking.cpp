//====================================================================================================
//
// ランキング処理 [ranking.cpp]
// Author : tanaka rikiya
//
//====================================================================================================
//====================================================================================================
//インクルードファイル
//===================================================================================================
#include "main.h"
#include "ranking.h"
#include "camera.h"
#include "player.h"
#include "meshfield.h"
#include "text.h"
#include "effect.h"
#include "load.h"
#include "input.h"
#include "fade.h"
#include "light.h"
//#include "sound.h"

// ====================================================================================================
// マクロ定義
// ====================================================================================================
#define	TEXTURE_RANKING	"Data/Texture/number001.png"	// 読み込むテクスチャファイル名

#define RANKING_SIZE	(30)								// ランキングの大きさ
#define RANKING_MAX		(3)									// 数値
#define RANKING_DATA	(5)									// ランキング数

#define COUNTRANK (500)
#define SAVE_FILE_NAME	("Data/text/rank.txt")							// セーブファイル

// ====================================================================================================
// プロトタイプ宣言
// ====================================================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

// ====================================================================================================
// グローバル変数宣言
// ====================================================================================================
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// 頂点バッファへのポインタ
D3DXVECTOR3				g_RankingPos;					// ランキングボードのポジション
RANKING					g_aRanking[RANKING_DATA];		// ランキング変数
int						g_nRanking;						// ランキング
int						g_nCnt;
// ====================================================================================================
// 初期化処理
// ====================================================================================================
void InitRanking(void)
{	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_RankingPos = D3DXVECTOR3(800.0f, 180.0f, 0.0f);
	g_nRanking = 0;
	g_nCnt = 0;
	for (int nCntRank = 0; nCntRank < RANKING_DATA; nCntRank++)
	{
		g_aRanking[nCntRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCntRank].aName[0];
		g_aRanking[nCntRank].nPoint = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_RANKING,								// ファイルの名前
		&g_pTextureRanking);							// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexRanking(pDevice);

	// カメラの終了処理
	InitCamera();

	// カメラの終了処理
	InitEffect();

	// ライトの終了処理
	InitLight();

	// 3Dポリゴンの終了処理
	InitMeshField();

	InitMoji();

	SetText(D3DXVECTOR3(640.0f, 360.0f, 000.0f), 1280/2, 720/2, 6);
	//SetText(D3DXVECTOR3(200.0f, 100.0f, 000.0f), 150, 60, 5);
}

// ====================================================================================================
// 終了処理
// ====================================================================================================
void UninitRanking(void)
{
	UninitEffect();

	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// 3Dポリゴンの終了処理
	UninitMeshField();

	UninitMoji();
	// テクスチャの開放
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

// ====================================================================================================
// 更新処理
// ====================================================================================================
void UpdateRanking(void)
{

	UpdateEffect();
	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	// 3Dポリゴンの更新処理
	UpdateMeshField();

	UpdateMoji();

	g_nCnt++;
	
	if (GetKeyboardTrigger(DIK_RETURN) || g_nCnt >= COUNTRANK)
	{
		//PlaySound(SOUND_LABEL_SE_ENTER);
		SetFade(MODE_TITLE);
		g_nCnt =0;
	}

}

// ====================================================================================================
// 描画処理
// ====================================================================================================
void DrawRanking(void)
{
	SetCamera();
	// 3Dポリゴンの終了処理
	DrawMeshField();
	DrawEffect();

	DrawMoji();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

	// ポリゴンの描画
	for (int nCntRanking = 0; nCntRanking < RANKING_MAX * RANKING_DATA; nCntRanking++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRanking, 2);
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


}

// ====================================================================================================
// 頂点の作成
// ====================================================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;			// 頂点情報へのポイント

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKING_MAX * RANKING_DATA, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	g_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点情報の設定
	for (int nCntRankingData = 0; nCntRankingData < RANKING_DATA; nCntRankingData++)
	{
		for (int nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// 一つ目の頂点
			pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// 二つ目の頂点
			pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// 三つ目の頂点
			pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// 四つ目の頂点

			pVtx[0].rhw = 1.0f;									// 一つ目の頂点作成
			pVtx[1].rhw = 1.0f;									// 二つ目の頂点作成
			pVtx[2].rhw = 1.0f;									// 三つ目の頂点作成
			pVtx[3].rhw = 1.0f;									// 四つ目の頂点作成

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 一つ目の色設定
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 二つ目の色設定
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 三つ目の色設定
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 四つ目の色設定

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				// 一つ目のテクスチャ
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);				// 二つ目のテクスチャ
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				// 三つ目のテクスチャ
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);				// 四つ目のテクスチャ

			pVtx += 4;
		}
	}
	// アンロック
	g_pVtxBuffRanking->Unlock();
}

// ====================================================================================================
// ランキングの変更
// ====================================================================================================
void AddRanking(int nPoint, int nRankingCnt)
{
	VERTEX_2D *pVtx;		// 頂点情報へのポイント
	LOAD *pLoad;

	int nCntRanking;		// ランキングカウント
	int nCntRankingData;	// ランキングカウント
	int nRanking;			// 桁ランキング
	float fRanking;

	pLoad = GetLoad();

	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	g_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingData = 0; nCntRankingData < RANKING_DATA; nCntRankingData++, pLoad++)
	{
		g_aRanking[nCntRankingData].nPoint = pLoad->nPoint;

		for (nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			nRanking = g_aRanking[nCntRankingData].nPoint % (int)powf(10.0f, (float)nCntRanking + 1.0f) / (int)powf(10.0f, (float)nCntRanking);
			fRanking = (float)nRanking / 10.0f;

			pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// 一つ目の頂点
			pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// 二つ目の頂点
			pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// 三つ目の頂点
			pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// 四つ目の頂点

			pVtx[0].tex = D3DXVECTOR2(fRanking, 0.0f);				// 一つ目のテクスチャ
			pVtx[1].tex = D3DXVECTOR2(fRanking + 0.1f, 0.0f);		// 二つ目のテクスチャ
			pVtx[2].tex = D3DXVECTOR2(fRanking, 1.0f);				// 三つ目のテクスチャ
			pVtx[3].tex = D3DXVECTOR2(fRanking + 0.1f, 1.0f);		// 四つ目のテクスチャ

			pVtx += 4;
		}
	}
	// アンロック
	g_pVtxBuffRanking->Unlock();
}