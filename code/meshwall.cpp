//=============================================================================
//
// 壁処理 [meshWall.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "meshwall.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_MESHWALL	(4)	// 最大数


//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	//Direct3Dデバイスのポインタ
MESHWALL g_aMeshWall[MAX_MESHWALL];
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;

LPDIRECT3DTEXTURE9 g_pTextureMeshWall= NULL;//テクスチャへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/block002.jpg",
		&g_pTextureMeshWall);

	for (nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		g_aMeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].bUse = false;
	}
	// 頂点情報の作成
	MakeVertexMeshWall(pDevice);
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -3000.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(3000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 3.14f / 2, 0.0f));
	SetMeshWall(D3DXVECTOR3(-3000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshWall(void)
{
	int nCntWall;

	//テクスチャの開放
	for (nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_pTextureMeshWall != NULL)
		{
			g_pTextureMeshWall->Release();
			g_pTextureMeshWall = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshWall(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得


	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall += 1)
	{
		if (g_aMeshWall[nCntWall].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aMeshWall[nCntWall].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntWall].rot.y, g_aMeshWall[nCntWall].rot.x, g_aMeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntWall].pos.x, g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntWall].mtxWorld);

			pDevice->SetTexture(0, g_pTextureMeshWall);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			pDevice->SetIndices(g_pIdxBuffMeshWall);

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
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntIdx = 0;
	int nCntY;
	int nCntX;
	WORD *pIdx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9* MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//ポインタ取得
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	VERTEX_3D *pVtx;

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		//頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);


		pVtx += 9 * nCntWall;

		for (nCntY = 0; nCntY < 3; nCntY++)
		{
			for (nCntX = 0; nCntX < 3; nCntX++)
			{
				//頂点バッファ
				pVtx[nCntX + nCntY * 3].pos.x = nCntX *3000.0f - 3000.0f;
				pVtx[nCntX + nCntY * 3].pos.y = nCntY *-300.0f + 300.0f;
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
		g_pVtxBuffMeshWall->Unlock();

		//頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

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
		g_pIdxBuffMeshWall->Unlock();

	}

}
//=============================================================================
// 壁の設定
//=============================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (!g_aMeshWall[nCntWall].bUse)
		{
			g_aMeshWall[nCntWall].pos = pos;
			g_aMeshWall[nCntWall].rot = rot;
			////頂点座標の設定
			g_aMeshWall[nCntWall].bUse = true;
			break;
		}
	}
	// 頂点データをアンロックする
	g_pVtxBuffMeshWall->Unlock();
}
