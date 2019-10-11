//=============================================================================
//
// 障害物処理 [Object.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "object.h"
#include "input.h"
#include "camera.h"
#include "effect.h"
#include "player.h"
#include "fade.h"
#include "game.h"
#include "explosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define Object_01 "Data/Model/object/sango.x"	//読み込むテクスチャファイル名
#define Object_02 "Data/Model/object/rock.x"	//読み込むテクスチャファイル名
#define POLTGON0_TEX "Data/Texture/.jpg"	//読み込むテクスチャファイル名

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXMATRIX			 mtxWorldObject;
	LPD3DXMESH			 pMeshObject;
	LPD3DXBUFFER		 pBuffMatObject;
	LPDIRECT3DTEXTURE9	 pTextureObject;
	DWORD				 nNumMatObject;

} OBJECTRESOURCE;

//=============================================================================
// グローバル変数
//=============================================================================
OBJECTRESOURCE		g_ObjectModel[OBJECTTYPE_MAX];
OBJECT				g_Object[MAX_OBJECT];
GAMESTATE g_gameStateObject = GAMESTATE_NONE;


//Xファイルから最大値と最小値の取得
D3DXVECTOR3 g_vtxMaxObject;		//最大値
D3DXVECTOR3 g_vtxMinObject;		//最小値

//=============================================================================
// 初期化処理
//=============================================================================
void InitObject(void)
{
	int nCntObject;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// 位置・向きの初期設定
		g_Object[nCntObject].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_Object[nCntObject].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回位置
		g_Object[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Object[nCntObject].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].bUse = false;
		g_Object[nCntObject].nType = OBJECTTYPE_SANGO;
		//g_Object[nCntModel].hIdxShadow = SetShadow(g_Model[nCntModel].pos, g_Model[nCntModel].rot);
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		Object_01,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectModel[0].pBuffMatObject,
		NULL,
		&g_ObjectModel[0].nNumMatObject,
		&g_ObjectModel[0].pMeshObject);

	D3DXLoadMeshFromX(
		Object_02,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectModel[1].pBuffMatObject,
		NULL,
		&g_ObjectModel[1].nNumMatObject,
		&g_ObjectModel[1].pMeshObject);

	D3DXCreateTextureFromFile(
		pDevice,	//取得
		POLTGON0_TEX,
		&g_ObjectModel[0].pTextureObject);


	//Xファイルから最大値と最小値の設定
	int nNumVertices;		//頂点数
	DWORD sizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVertexBuffer;	//頂点バッファのポインタ

	g_vtxMinObject = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_vtxMaxObject = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{

		//頂点数を取得
		nNumVertices = g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->GetFVF());

		//頂点バッファをロック
		g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//すべての変数を比較して最小・最大値を決める
			if (g_vtxMinObject.x > vtx.x)
			{
				g_vtxMinObject.x = vtx.x;
			}
			if (g_vtxMaxObject.x < vtx.x)
			{
				g_vtxMaxObject.x = vtx.x;
			}
			if (g_vtxMinObject.y > vtx.y)
			{
				g_vtxMinObject.y = vtx.y;
			}
			if (g_vtxMaxObject.y < vtx.y)
			{
				g_vtxMaxObject.y = vtx.y;
			}
			if (g_vtxMinObject.z > vtx.z)
			{
				g_vtxMinObject.z = vtx.z;
			}
			if (g_vtxMaxObject.z < vtx.z)
			{
				g_vtxMaxObject.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;//サイズ分ポインタを進める
		}
		//頂点バッファのアンロック
		g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->UnlockVertexBuffer();
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_LOADOBJECT; nCntObject++)
	{
		// メッシュの開放
		if (g_ObjectModel[nCntObject].pMeshObject != NULL)
		{
			g_ObjectModel[nCntObject].pMeshObject->Release();
			g_ObjectModel[nCntObject].pMeshObject = NULL;
		}
		// マテリアルの開放
		if (g_ObjectModel[nCntObject].pBuffMatObject != NULL)
		{
			g_ObjectModel[nCntObject].pBuffMatObject->Release();
			g_ObjectModel[nCntObject].pBuffMatObject = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObject(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9	 pDevice = GetDevice();
	D3DXMATRIX			 mtxSize, mtxRot, mtxTrans;				//計算用
	D3DXMATERIAL		 *pMat;
	D3DMATERIAL9		 matDef;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Object[nCntObject].mtxWorldObject);

			// スケールを反映
			D3DXMatrixScaling(&mtxSize, g_Object[nCntObject].scale.x, g_Object[nCntObject].scale.y, g_Object[nCntObject].scale.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorldObject, &g_Object[nCntObject].mtxWorldObject, &mtxSize);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nCntObject].rot.y, g_Object[nCntObject].rot.x, g_Object[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorldObject, &g_Object[nCntObject].mtxWorldObject, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorldObject, &g_Object[nCntObject].mtxWorldObject, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCntObject].mtxWorldObject);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_ObjectModel[g_Object[nCntObject].nType].pBuffMatObject->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ObjectModel[g_Object[nCntObject].nType].nNumMatObject; nCntMat++)
			{
				//テクスチャの設定
				//pDevice->SetTexture(0, g_ObjectModel[nCntObject].pTextureObject);
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// 描画
				g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//============================================================================
// 障害物の取得
//=============================================================================
OBJECT * GetObjectModel(void)
{
	return &g_Object[0];
}

//============================================================================
// 障害物の設定
//=============================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, OBJECTTYPE nType)
{
	// 変数宣言
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == false)
		{
			g_Object[nCntObject].pos = pos;
			g_Object[nCntObject].move = move;
			g_Object[nCntObject].rot = rot;
			g_Object[nCntObject].scale = scale;
			g_Object[nCntObject].bUse = true;
			g_Object[nCntObject].nType = nType;
			break;
		}
	}
}
//=======================================================================================
// 障害物の当たり判定
//=======================================================================================
bool ColisionObject(D3DXVECTOR3 * ppos, D3DXVECTOR3 * pposOld)
{
	bool bLand = false;
	int nCntObject;
	PLAYER * pPlayer;
	//プレイヤーの取得
	pPlayer = GetPlayer();

	//if (*ppObjectRet != NULL)
	//{
	//	*ppObjectRet = NULL;
	//}

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse)
		{
			if (pPlayer->pos.y + 100 >= g_Object[nCntObject].pos.y&&
				pPlayer->pos.y <= g_Object[nCntObject].pos.y + 100)
			{
				//g_ObjectModel[g_Object[nCntObject].nType].MaxObject

				if (ppos->x + pPlayer->size.x > 0 + g_Object[nCntObject].pos.x&&
					ppos->x + pPlayer->size.x < 100 + g_Object[nCntObject].pos.x)
				{
					//手前の当たり判定処理
					if (pposOld->z + pPlayer->size.z <= g_Object[nCntObject].pos.z - 100 &&
						ppos->z + pPlayer->size.z >= g_Object[nCntObject].pos.z - 100)
					{
						ppos->z = g_Object[nCntObject].pos.z - pPlayer->size.z - 100;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					//奥の当たり判定処理
					if (pposOld->z - pPlayer->size.z >= g_Object[nCntObject].pos.z - 0 &&
						ppos->z - pPlayer->size.z < g_Object[nCntObject].pos.z - 00)
					{
						ppos->z = g_Object[nCntObject].pos.z + pPlayer->size.z - 00;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
			}
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_Object[nCntObject].pos.y&&
				pPlayer->pos.y <= g_Object[nCntObject].pos.y + g_vtxMaxObject.y)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinObject.z + g_Object[nCntObject].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxObject.z + g_Object[nCntObject].pos.z)
				{
					//左の当たり判定処理
					if (pposOld->x + pPlayer->size.x <= g_Object[nCntObject].pos.x - g_vtxMaxObject.x&&
						ppos->x + pPlayer->size.x >= g_Object[nCntObject].pos.x - g_vtxMaxObject.x)
					{
						ppos->x = g_Object[nCntObject].pos.x - pPlayer->size.x - g_vtxMaxObject.x;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					//右の当たり判定処理
					if (pposOld->x - pPlayer->size.x >= g_Object[nCntObject].pos.x - g_vtxMinObject.x&&
						ppos->x - pPlayer->size.x <= g_Object[nCntObject].pos.x - g_vtxMinObject.x)
					{
						ppos->x = g_Object[nCntObject].pos.x + pPlayer->size.x - g_vtxMinObject.x;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
			}
			if (ppos->x + pPlayer->size.x > g_vtxMinObject.x + g_Object[nCntObject].pos.x&&
				ppos->x + pPlayer->size.x < g_vtxMaxObject.x + g_Object[nCntObject].pos.x)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinObject.z + g_Object[nCntObject].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxObject.z + g_Object[nCntObject].pos.z)
				{
					////上の当たり判定処理
					//if (pposOld->y - pPlayer->size.y >= g_vtxMinObject.y - g_Object[nCntObject].pos.y &&
					//	ppos->y - pPlayer->size.y <= g_vtxMaxObject.y - g_Object[nCntObject].pos.y)
					//{
					//	//ppos->y = g_Object[nCntObject].pos.y + pPlayer->size.y + g_vtxMaxObject.y;
					//g_Object[nCntObject].bUse = false;
					//SetGameState(GAMESTATE_END);
					//SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					//}
					//下の当たり判定処理
					if (pPlayer->posOld.y + pPlayer->vtxMaxPlayer.y >= g_Object[nCntObject].pos.y)
					{
						//ppos->y = g_Object[nCntObject].pos.y + pPlayer->size.y + g_vtxMaxObject.y;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					}
				}
			}
		}
	}
	return bLand;
}


