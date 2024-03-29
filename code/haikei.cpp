//=============================================================================
//
// 背景処理 [Haikei.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "Haikei.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexHaikei(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHaikei = NULL;	//Direct3Dデバイスのポインタ
HAIKEI g_aHaikei[MAX_HAIKEI];
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffHaikei = NULL;

LPDIRECT3DTEXTURE9 g_pTextureHaikei = NULL;//テクスチャへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitHaikei(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/sora.png",//nendoSophie.png//olga_face.jpg
		&g_pTextureHaikei);

	for (nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall++)
	{
		g_aHaikei[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aHaikei[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aHaikei[nCntWall].bUse = false;
	}
	// 頂点情報の作成
	MakeVertexHaikei(pDevice);
	SetHaikei(D3DXVECTOR3(0.0f, -1000.0f, 4000.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetHaikei(D3DXVECTOR3(0.0f, -1000.0f, -4000.0f ),D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetHaikei(D3DXVECTOR3(4000.0f, -1000.0f, 0.0f),D3DXVECTOR3(0.0f, 3.14f / 2, 0.0f));
	SetHaikei(D3DXVECTOR3(-4000.0f, -1000.0f, 0.0f), D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHaikei(void)
{
	int nCntWall;

	//テクスチャの開放
	for (nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall++)
	{
		if (g_pTextureHaikei != NULL)
		{
			g_pTextureHaikei->Release();
			g_pTextureHaikei = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffHaikei != NULL)
	{
		g_pVtxBuffHaikei->Release();
		g_pVtxBuffHaikei = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHaikei(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHaikei(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得


	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

								//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (int nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall += 1)
	{
		if (g_aHaikei[nCntWall].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aHaikei[nCntWall].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aHaikei[nCntWall].rot.y, g_aHaikei[nCntWall].rot.x, g_aHaikei[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aHaikei[nCntWall].mtxWorld, &g_aHaikei[nCntWall].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aHaikei[nCntWall].pos.x, g_aHaikei[nCntWall].pos.y, g_aHaikei[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aHaikei[nCntWall].mtxWorld, &g_aHaikei[nCntWall].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aHaikei[nCntWall].mtxWorld);

			pDevice->SetTexture(0, g_pTextureHaikei);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffHaikei, 0, sizeof(VERTEX_3D));

			pDevice->SetIndices(g_pIdxBuffHaikei);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴン描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, nCntWall * 14, 12);
		}
	}

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexHaikei(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntIdx = 0;
	int nCntY;
	int nCntX;
	WORD *pIdx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * MAX_HAIKEI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHaikei,
		NULL);

	//ポインタ取得
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * MAX_HAIKEI,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffHaikei,
		NULL);

	VERTEX_3D *pVtx;

	for (int nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall++)
	{
		//頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffHaikei->Lock(0, 0, (void**)&pVtx, 0);


		pVtx += 9 * nCntWall;

		for (nCntY = 0; nCntY < 3; nCntY++)
		{
			for (nCntX = 0; nCntX < 3; nCntX++)
			{
				//頂点バッファ
				//pVtx[nCntX + nCntY * 3].pos.x = nCntX *1000.0f - 1000.0f;
				//pVtx[nCntX + nCntY * 3].pos.y = nCntY *-90.0f + 180.0f;
				//pVtx[nCntX + nCntY * 3].pos.z = 0.0f;
				pVtx[nCntX + nCntY * 3].pos.x = nCntX *6000.0f - 6000.0f;
				pVtx[nCntX + nCntY * 3].pos.y = nCntY *-3000.0f + 3000.0f;
				pVtx[nCntX + nCntY * 3].pos.z = 0.0f;

				//テクスチャ
				pVtx[nCntX + nCntY * 3].tex.x = nCntX *1.0f - 1.0f;
				pVtx[nCntX + nCntY * 3].tex.y = nCntY *-1.0f + 1.0f;

				//法線ベクトル
				//pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				//カラー
				pVtx[nCntX + nCntY * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}


		//頂点データのアンロック
		g_pVtxBuffHaikei->Unlock();

		//頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pIdxBuffHaikei->Lock(0, 0, (void**)&pIdx, 0);

		//pIdx +=  14 * nCntWall;

		for (int nCountY = 0; nCountY < 2; nCountY++)
		{

			//環状インデックス
			for (int nCountX = 0; nCountX < 3; nCountX++)
			{
				//インデックスの設定
				pIdx[nCntIdx] = (nCountY + 1) * 3 + nCountX + 9 * nCntWall;
				pIdx[nCntIdx + 1] = pIdx[nCntIdx] - 3;
				nCntIdx += 2;

				//縮退分
				if (nCountX == 2 && nCountY < 1)
				{
					pIdx[nCntIdx] = pIdx[nCntIdx - 1];
					pIdx[nCntIdx + 1] = pIdx[nCntIdx - 1] + 3 + 1;
					nCntIdx += 2;
				}
			}
		}

		//頂点データのアンロック
		g_pIdxBuffHaikei->Unlock();

	}

}
//=============================================================================
// 壁の設定
//=============================================================================
void SetHaikei(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffHaikei->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall++)
	{
		if (!g_aHaikei[nCntWall].bUse)
		{
			g_aHaikei[nCntWall].pos = pos;
			g_aHaikei[nCntWall].rot = rot;
			////頂点座標の設定
			g_aHaikei[nCntWall].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffHaikei->Unlock();
}
