//=============================================================================
//
// 波（上向き）処理 [MeshTenjoUp.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "MeshTenjoUp.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define X_CHOTEN (3);
#define Y_CHOTEN (3);
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexMeshTenjoUp(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshTenjoUp = NULL;	//Direct3Dデバイスのポインタ
D3DXVECTOR3 g_posMeshTenjoUp;
D3DXVECTOR3 g_rotMeshTenjoUp;	//ポリゴンの向き

LPDIRECT3DTEXTURE9 g_pTextureMeshTenjoUp = NULL;//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshTenjoUp = NULL;
D3DXMATRIX g_mtxWorldMeshTenjoUp;//ワールドマトリックス
int nCntUmiUp;
//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshTenjoUp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/suimen.png",
		&g_pTextureMeshTenjoUp);

	// 位置・回転の初期設定
	g_posMeshTenjoUp = D3DXVECTOR3(0.0f, 310.0f, 0.0f);
	g_rotMeshTenjoUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	nCntUmiUp = 0;

	// 頂点情報の作成
	MakeVertexMeshTenjoUp(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshTenjoUp(void)
{

	//テクスチャの開放
	if (g_pTextureMeshTenjoUp != NULL)
	{
		g_pTextureMeshTenjoUp->Release();
		g_pTextureMeshTenjoUp = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffMeshTenjoUp != NULL)
	{
		g_pVtxBuffMeshTenjoUp->Release();
		g_pVtxBuffMeshTenjoUp = NULL;
	}
	// インデックスバッファの開放
	if (g_pIdxBuffMeshTenjoUp != NULL)
	{
		g_pIdxBuffMeshTenjoUp->Release();
		g_pIdxBuffMeshTenjoUp = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshTenjoUp(void)
{

	nCntUmiUp++;
	if (nCntUmiUp <= 100)
	{
		g_posMeshTenjoUp.y -= sinf(0.35f);
	}
	if (nCntUmiUp >= 100)
	{
		g_posMeshTenjoUp.y += sinf(0.35f);
	}

	if (nCntUmiUp >= 200)
	{
		nCntUmiUp = 0;
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshTenjoUp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	
	D3DXMATRIX mtxRot,mtxTrans;//計算用マトリックス


	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshTenjoUp);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshTenjoUp.y, g_rotMeshTenjoUp.x, g_rotMeshTenjoUp.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTenjoUp, &g_mtxWorldMeshTenjoUp, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshTenjoUp.x, g_posMeshTenjoUp.y, g_posMeshTenjoUp.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTenjoUp, &g_mtxWorldMeshTenjoUp, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshTenjoUp);


	pDevice->SetTexture(0, g_pTextureMeshTenjoUp);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshTenjoUp, 0, sizeof(VERTEX_3D));

	//インデックス
	pDevice->SetIndices(g_pIdxBuffMeshTenjoUp);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//ポリゴン描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);


	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshTenjoUp(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntIdx=0;
	int nCntY;
	int nCntX;
	WORD *pIdx;

	//ポインタ取得
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshTenjoUp,
		NULL);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshTenjoUp,
		NULL);

	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffMeshTenjoUp->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	for (nCntY = 0; nCntY < 3; nCntY++)
	{
		for (nCntX = 0; nCntX < 3; nCntX++)
		{
			//頂点バッファ
			pVtx[nCntX + nCntY * 3].pos.x = nCntX *4000.0f - 4000.0f;
			pVtx[nCntX + nCntY * 3].pos.y = 0.0f;
			pVtx[nCntX + nCntY * 3].pos.z = nCntY *-4000.0f + 4000.0f;

			//テクスチャ
			pVtx[nCntX + nCntY * 3].tex.x = nCntX *1.0f - 1.0f;
			pVtx[nCntX + nCntY * 3].tex.y = nCntY *-1.0f + 1.0f;
			//pVtx[0].tex = D3DXVECTOR2(-1.0f, 1.0f);
			//pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(-1.0f, 0.0f);
			//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
			//pVtx[6].tex = D3DXVECTOR2(-1.0f, -1.0f);
			//pVtx[7].tex = D3DXVECTOR2(0.0f, -1.0f);
			//pVtx[8].tex = D3DXVECTOR2(1.0f, -1.0f);

			//法線ベクトル
			pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(3.14f/2, 0.0f, 0.0f);
			//カラー
			pVtx[nCntX + nCntY * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f);
		}
	}
	//頂点データのアンロック
	g_pVtxBuffMeshTenjoUp->Unlock();
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pIdxBuffMeshTenjoUp->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCountY = 0; nCountY < 2; nCountY++)
	{
		//環状インデックス
		for (int nCountX = 0; nCountX < 3; nCountX++)
		{
			//インデックスの設定
			pIdx[nCntIdx] = (nCountY + 1) * 3 + nCountX;
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
	//pIdx[0] = 3;
	//pIdx[1] = 0;

	//pIdx[2] = 4;
	//pIdx[3] = 1;

	//pIdx[4] = 5;
	//pIdx[5] = 2;

	//pIdx[6] = 2;
	//pIdx[7] = 6;

	//pIdx[8] = 6;
	//pIdx[9] = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;

	//頂点データのアンロック
	g_pIdxBuffMeshTenjoUp->Unlock();
}

