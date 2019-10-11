//=============================================================================
//
// 波（下向き）処理 [MeshTenjo.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "MeshTenjo.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define X_CHOTEN (3);
#define Y_CHOTEN (3);
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexMeshTenjo(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshTenjo = NULL;	//Direct3Dデバイスのポインタ
D3DXVECTOR3 g_posMeshTenjo;
D3DXVECTOR3 g_rotMeshTenjo;	//ポリゴンの向き

LPDIRECT3DTEXTURE9 g_pTextureMeshTenjo = NULL;//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshTenjo = NULL;
D3DXMATRIX g_mtxWorldMeshTenjo;//ワールドマトリックス
int nCntUmi;
//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshTenjo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/suimen.png",
		&g_pTextureMeshTenjo);

	// 位置・回転の初期設定
	g_posMeshTenjo = D3DXVECTOR3(0.0f, 310.0f, 0.0f);
	g_rotMeshTenjo = D3DXVECTOR3(3.14f, 0.0f, 0.0f);
	nCntUmi=0;

	// 頂点情報の作成
	MakeVertexMeshTenjo(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshTenjo(void)
{

	//テクスチャの開放
	if (g_pTextureMeshTenjo != NULL)
	{
		g_pTextureMeshTenjo->Release();
		g_pTextureMeshTenjo = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffMeshTenjo != NULL)
	{
		g_pVtxBuffMeshTenjo->Release();
		g_pVtxBuffMeshTenjo = NULL;
	}
	// インデックスバッファの開放
	if (g_pIdxBuffMeshTenjo != NULL)
	{
		g_pIdxBuffMeshTenjo->Release();
		g_pIdxBuffMeshTenjo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshTenjo(void)
{

	nCntUmi++;
	if (nCntUmi <= 100)
	{
		g_posMeshTenjo.y -= sinf(0.55f);
	}
	if (nCntUmi >= 100)
	{
		g_posMeshTenjo.y += sinf(0.55f);
	}
	if (nCntUmi >= 200)
	{
		nCntUmi = 0;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshTenjo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXMATRIX mtxRot,mtxTrans;//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshTenjo);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshTenjo.y, g_rotMeshTenjo.x, g_rotMeshTenjo.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTenjo, &g_mtxWorldMeshTenjo, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshTenjo.x, g_posMeshTenjo.y, g_posMeshTenjo.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTenjo, &g_mtxWorldMeshTenjo, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshTenjo);


	pDevice->SetTexture(0, g_pTextureMeshTenjo);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshTenjo, 0, sizeof(VERTEX_3D));

	//インデックス
	pDevice->SetIndices(g_pIdxBuffMeshTenjo);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴン描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshTenjo(LPDIRECT3DDEVICE9 pDevice)
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
		&g_pIdxBuffMeshTenjo,
		NULL);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshTenjo,
		NULL);

	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffMeshTenjo->Lock(0, 0, (void**)&pVtx, 0);
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

			//法線ベクトル
			pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(3.14f, 1.0f, 0.0f);
			//カラー
			pVtx[nCntX + nCntY * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f);
		}
	}
	//頂点データのアンロック
	g_pVtxBuffMeshTenjo->Unlock();
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pIdxBuffMeshTenjo->Lock(0, 0, (void**)&pIdx, 0);

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
	//頂点データのアンロック
	g_pIdxBuffMeshTenjo->Unlock();
}

