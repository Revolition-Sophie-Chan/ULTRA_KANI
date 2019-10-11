//=============================================================================
//
// ポリゴン処理 [MeshField.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "MeshField.h"
#include "effect.h"
#include "input.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define X_CHOTEN (3);
#define Y_CHOTEN (3);
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	//Direct3Dデバイスのポインタ
D3DXVECTOR3 g_posMeshField;
D3DXVECTOR3 g_rotMeshField;	//ポリゴンの向き

LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
D3DXMATRIX g_mtxWorldMeshField;//ワールドマトリックス

int nCount;
//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/suna.png",
		&g_pTextureMeshField);

	// 位置・回転の初期設定
	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	nCount = 0;

	// 頂点情報の作成
	MakeVertexMeshField(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{

	//テクスチャの開放
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	// インデックスバッファの開放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
	nCount++;
	if (nCount >= 5)
	{
		MakeEffect_Field();//エフェクトを生成
		nCount = 0;
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	
	D3DXMATRIX mtxRot,mtxTrans;//計算用マトリックス


	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);


	pDevice->SetTexture(0, g_pTextureMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックス
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴン描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
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
		&g_pIdxBuffMeshField,
		NULL);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	for (nCntY = 0; nCntY < 3; nCntY++)
	{
		for (nCntX = 0; nCntX < 3; nCntX++)
		{
			//頂点バッファ
			pVtx[nCntX + nCntY * 3].pos.x = nCntX *3000.0f - 3000.0f;
			pVtx[nCntX + nCntY * 3].pos.y = 0.0f;
			pVtx[nCntX + nCntY * 3].pos.z = nCntY *-3000.0f + 3000.0f;

			//テクスチャ
			pVtx[nCntX + nCntY * 3].tex.x = nCntX *1.0f - 1.0f;
			pVtx[nCntX + nCntY * 3].tex.y = nCntY *-1.0f + 1.0f;

			//法線ベクトル
			pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//カラー
			pVtx[nCntX + nCntY * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	//頂点データのアンロック
	g_pVtxBuffMeshField->Unlock();
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeEffect_Field(void)
{
	int nCntItem = 0;
	//////////////////// 爆発の設定 ////////////////////
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	float fRadius = 20.0f;
	float fAngle = 0.0f;
	float fSpeed = 15.0f;
	int nLife = 20;
	////////////////////////////////////////////////////

		// 0～3.14を出す * (0 or 1)* -1で正負を決める(出す範囲)
	fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;	// 全方向出す

																			// 発生位置
	D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 4000 - 2000.0f, 0.0f, rand() % 4000 - 2000.0f);
	// 出す向き
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 10.0, 0.0f);


	// エフェクトの設定
	SetEffect(pos, move, fRadius, nLife, col, 2);

}