//=============================================================================
//
// モデル処理 [model.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "Player.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POLYGON_SPD (2)
#define ROLL_SPD (0.2f)
#define PLAYER_SIZE (100.0f)
#define LOAD_MODEL	(1)		//読み込むテクスチャタイプのカズ
//=============================================================================
// グローバル変数
//=============================================================================
LPD3DXBUFFER	 g_pBuffMatModel = NULL;
LPD3DXMESH		 g_pMeshModel = {};
DWORD			 g_nNumMatModel = 0;
MODEL			 g_Model[MAX_MODEL];

//int g_nIdxShadow; //影のID
//Xファイルから最大値と最小値の取得
D3DXVECTOR3 g_vtxMaxModel;		//最大値
D3DXVECTOR3 g_vtxMinModel;		//最小値

//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		// 位置・向きの初期設定
		g_Model[nCntmodel].pos		 = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		g_Model[nCntmodel].rot		 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntmodel].scale	 = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Model[nCntmodel].Diffrot	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntmodel].bUse		 = false;


		// Xファイルの読み込み
		D3DXLoadMeshFromX(
			"Data/Model/bill3.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Model[nCntmodel].aModel[0].pBuffMatModel,
			NULL,
			&g_Model[nCntmodel].aModel[0].nNumMatModel,
			&g_Model[nCntmodel].aModel[0].pMeshModel);


		//テクスチャの読み混み
		D3DXCreateTextureFromFile(pDevice,
			"Data/Texture/field000.jpg",//nendoSophie.png//olga_face.jpg
			&g_Model[nCntmodel].aModel[0].pTextureModel);

		//Xファイルから最大値と最小値の設定
		int nNumVertices;		 //頂点数
		DWORD sizeFVF;			 //頂点フォーマットのサイズ
		BYTE *pVertexBuffer;	 //頂点バッファのポインタ


		g_Model[nCntmodel].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Model[nCntmodel].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

		//頂点数を取得
		nNumVertices = g_Model[nCntmodel].aModel[0].pMeshModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Model[nCntmodel].aModel[0].pMeshModel->GetFVF());

		//頂点バッファをロック
		g_Model[nCntmodel].aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{

			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//すべての頂点情報を比較して最小・最大を抜き出す
			if (g_Model[nCntmodel].vtxMin.x > vtx.x)
			{
				g_Model[nCntmodel].vtxMin.x = vtx.x;
			}
			if (g_Model[nCntmodel].vtxMin.y > vtx.y)
			{
				g_Model[nCntmodel].vtxMin.y = vtx.y;
			}
			if (g_Model[nCntmodel].vtxMin.z > vtx.z)
			{
				g_Model[nCntmodel].vtxMin.z = vtx.z;
			}
			if (g_Model[nCntmodel].vtxMax.x < vtx.x)
			{
				g_Model[nCntmodel].vtxMax.x = vtx.x;
			}
			if (g_Model[nCntmodel].vtxMax.y < vtx.y)
			{
				g_Model[nCntmodel].vtxMax.y = vtx.y;
			}
			if (g_Model[nCntmodel].vtxMax.z < vtx.z)
			{
				g_Model[nCntmodel].vtxMax.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;//サイズ分ポインタを進める
		}
		//頂点バッファをアンロック
		g_Model[nCntmodel].aModel[0].pMeshModel->UnlockVertexBuffer();
	}
	//SetModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
}

	//g_Model[nCntmodel].nIdShadow = SetShadow(g_Model[nCntmodel].pos, g_Model[nCntmodel].rot);

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < LOAD_MODEL; nCntTex++)
	{
		//テクスチャの開放
		if (g_Model[nCntTex].aModel[0].pTextureModel != NULL)
		{
			g_Model[nCntTex].aModel[0].pTextureModel->Release();
			g_Model[nCntTex].aModel[0].pTextureModel = NULL;
		}
	}
	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		// メッシュの開放
		if (g_Model[nCntmodel].aModel[0].pMeshModel != NULL)
		{
			g_Model[nCntmodel].aModel[0].pMeshModel->Release();
			g_Model[nCntmodel].aModel[0].pMeshModel = NULL;
		}

		// マテリアルの開放
		if (g_pBuffMatModel != NULL)
		{
			g_pBuffMatModel->Release();
			g_pBuffMatModel = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9	 pDevice = GetDevice();
	D3DXMATRIX			 mtxSize, mtxRot, mtxTrans;
	D3DXMATERIAL		 *pMat;
	D3DMATERIAL9		 matDef;

	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		if (g_Model[nCntmodel].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Model[nCntmodel].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxSize, g_Model[nCntmodel].scale.x, g_Model[nCntmodel].scale.y, g_Model[nCntmodel].scale.z);
			D3DXMatrixMultiply(&g_Model[nCntmodel].mtxWorld, &g_Model[nCntmodel].mtxWorld, &mtxSize);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCntmodel].rot.y, g_Model[nCntmodel].rot.x, g_Model[nCntmodel].rot.z);
			D3DXMatrixMultiply(&g_Model[nCntmodel].mtxWorld, &g_Model[nCntmodel].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Model[nCntmodel].pos.x, g_Model[nCntmodel].pos.y, g_Model[nCntmodel].pos.z);
			D3DXMatrixMultiply(&g_Model[nCntmodel].mtxWorld, &g_Model[nCntmodel].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntmodel].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_Model[nCntmodel].aModel[nCntmodel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_Model[nCntmodel].aModel[nCntmodel].pTextureModel);
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// 描画
				g_Model[nCntmodel].aModel[nCntmodel].pMeshModel->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}

	}
}
//=============================================================================
// 当たり判定
//=============================================================================
void CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		if (pPos->x > g_Model[nCntmodel].vtxMin.x + g_Model[nCntmodel].pos.x&&
			pPos->x < g_Model[nCntmodel].vtxMax.x + g_Model[nCntmodel].pos.x)//ブロックの範囲内
		{

			//おく
			if (pPosOld->z >= g_Model[nCntmodel].vtxMax.z + g_Model[nCntmodel].pos.z&&
				pPos->z < g_Model[nCntmodel].vtxMax.z + g_Model[nCntmodel].pos.z)
			{
				pPos->z = g_Model[nCntmodel].vtxMax.z + g_Model[nCntmodel].pos.z;
				//SetFade(MODE_RESULT);
			}
			//手前の当たり判定
			else if (pPosOld->z <= g_Model[nCntmodel].vtxMin.z + g_Model[nCntmodel].pos.z &&
				pPos->z > g_Model[nCntmodel].vtxMin.z + g_Model[nCntmodel].pos.z)
			{
				pPos->z = g_Model[nCntmodel].vtxMin.z + g_Model[nCntmodel].pos.z;
				//SetFade(MODE_RESULT);
			}
		}
		//左右の当たり判定
		if (pPos->z > g_Model[nCntmodel].vtxMin.z + g_Model[nCntmodel].pos.z&&
			pPos->z < g_Model[nCntmodel].vtxMax.z + g_Model[nCntmodel].pos.z)//ブロックの範囲内
		{

			//右か左
			if (pPosOld->x >= g_Model[nCntmodel].vtxMax.x + g_Model[nCntmodel].pos.x &&
				pPos->x < g_Model[nCntmodel].vtxMax.x + g_Model[nCntmodel].pos.x)
			{
				pPos->x = g_Model[nCntmodel].vtxMax.x + g_Model[nCntmodel].pos.x;
				//SetFade(MODE_RESULT);
			}

			//右か左
			else if (pPosOld->x <= g_Model[nCntmodel].vtxMin.x + g_Model[nCntmodel].pos.x &&
				pPos->x > g_Model[nCntmodel].vtxMin.x + g_Model[nCntmodel].pos.x)
			{
				pPos->x = g_Model[nCntmodel].vtxMin.x + g_Model[nCntmodel].pos.x;
			}
		}
	}

}
//=============================================================================
// モデルの設定
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType)
{
	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		if (g_Model[nCntmodel].bUse == false)
		{
			g_Model[nCntmodel].pos = pos;
			g_Model[nCntmodel].move = move;
			g_Model[nCntmodel].rot = rot;
			g_Model[nCntmodel].scale = scale;
			g_Model[nCntmodel].bUse = true;
			g_Model[nCntmodel].nType = nType;
			break;
		}
	}
}