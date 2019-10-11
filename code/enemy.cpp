//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "enemy.h"
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
#define Enemy_01 "Data/Model/enemy/tsuribito.x"	//読み込むテクスチャファイル名
#define Enemy_02 "Data/Model/enemy/gyosen.x"	//読み込むテクスチャファイル名
#define POLTGON0_TEX "Data/Texture/.jpg"	//読み込むテクスチャファイル名

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXMATRIX			 mtxWorldEnemy;
	LPD3DXMESH			 pMeshEnemy;
	LPD3DXBUFFER		 pBuffMatEnemy;
	LPDIRECT3DTEXTURE9	 pTextureEnemy;
	DWORD				 nNumMatEnemy;

} ENEMYRESOURCE;

//=============================================================================
// グローバル変数
//=============================================================================
ENEMYRESOURCE		g_EnemyModel[ENEMYTYPE_MAX];
ENEMY				g_Enemy[MAX_ENEMY];
GAMESTATE g_gameStateEnemy = GAMESTATE_NONE;


//Xファイルから最大値と最小値の取得
D3DXVECTOR3 g_vtxMaxEnemy;		//最大値
D3DXVECTOR3 g_vtxMinEnemy;		//最小値

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	int nCntEnemy;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// 位置・向きの初期設定
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回位置
		g_Enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Enemy[nCntEnemy].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].bUse = false;
		g_Enemy[nCntEnemy].nType = ENEMYTYPE_GYOSEN;
		//g_Enemy[nCntModel].hIdxShadow = SetShadow(g_Model[nCntModel].pos, g_Model[nCntModel].rot);
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		Enemy_01,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyModel[0].pBuffMatEnemy,
		NULL,
		&g_EnemyModel[0].nNumMatEnemy,
		&g_EnemyModel[0].pMeshEnemy);

	D3DXLoadMeshFromX(
		Enemy_02,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyModel[1].pBuffMatEnemy,
		NULL,
		&g_EnemyModel[1].nNumMatEnemy,
		&g_EnemyModel[1].pMeshEnemy);



	//Xファイルから最大値と最小値の設定
	int nNumVertices;		//頂点数
	DWORD sizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVertexBuffer;	//頂点バッファのポインタ

	g_vtxMinEnemy = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_vtxMaxEnemy = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		//頂点数を取得
		nNumVertices = g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->GetFVF());

		//頂点バッファをロック
		g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//すべての変数を比較して最小・最大値を決める
			if (g_vtxMinEnemy.x > vtx.x)
			{
				g_vtxMinEnemy.x = vtx.x;
			}
			if (g_vtxMaxEnemy.x < vtx.x)
			{
				g_vtxMaxEnemy.x = vtx.x;
			}
			if (g_vtxMinEnemy.y > vtx.y)
			{
				g_vtxMinEnemy.y = vtx.y;
			}
			if (g_vtxMaxEnemy.y < vtx.y)
			{
				g_vtxMaxEnemy.y = vtx.y;
			}
			if (g_vtxMinEnemy.z > vtx.z)
			{
				g_vtxMinEnemy.z = vtx.z;
			}
			if (g_vtxMaxEnemy.z < vtx.z)
			{
				g_vtxMaxEnemy.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;//サイズ分ポインタを進める
		}
		//頂点バッファのアンロック
		g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->UnlockVertexBuffer();
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_LOADENEMY; nCntEnemy++)
	{
		// メッシュの開放
		if (g_EnemyModel[nCntEnemy].pMeshEnemy != NULL)
		{
			g_EnemyModel[nCntEnemy].pMeshEnemy->Release();
			g_EnemyModel[nCntEnemy].pMeshEnemy = NULL;
		}
		// マテリアルの開放
		if (g_EnemyModel[nCntEnemy].pBuffMatEnemy != NULL)
		{
			g_EnemyModel[nCntEnemy].pBuffMatEnemy->Release();
			g_EnemyModel[nCntEnemy].pBuffMatEnemy = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9	 pDevice = GetDevice();
	D3DXMATRIX			 mtxSize, mtxRot, mtxTrans;				//計算用
	D3DXMATERIAL		 *pMat;
	D3DMATERIAL9		 matDef;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorldEnemy);

			// スケールを反映
			D3DXMatrixScaling(&mtxSize, g_Enemy[nCntEnemy].scale.x, g_Enemy[nCntEnemy].scale.y, g_Enemy[nCntEnemy].scale.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntEnemy].mtxWorldEnemy, &mtxSize);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntEnemy].mtxWorldEnemy, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntEnemy].mtxWorldEnemy, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorldEnemy);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_EnemyModel[g_Enemy[nCntEnemy].nType].pBuffMatEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_EnemyModel[g_Enemy[nCntEnemy].nType].nNumMatEnemy; nCntMat++)
			{
				//テクスチャの設定
				//pDevice->SetTexture(0, g_EnemyModel[nCntEnemy].pTextureEnemy);
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// 描画
				g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//============================================================================
// 敵の取得
//=============================================================================
ENEMY * GetEnemy(void)
{
	return &g_Enemy[0];
}

//============================================================================
// モデルの設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, ENEMYTYPE_ENEMY nType)
{
	// 変数宣言
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{
			g_Enemy[nCntEnemy].pos = pos;
			g_Enemy[nCntEnemy].move = move;
			g_Enemy[nCntEnemy].rot = rot;
			g_Enemy[nCntEnemy].scale = scale;
			g_Enemy[nCntEnemy].bUse = true;
			g_Enemy[nCntEnemy].nType = nType;
			break;
		}
	}
}
//=======================================================================================
// 敵の当たり判定
//=======================================================================================
bool ColisionEnemy(D3DXVECTOR3 * ppos, D3DXVECTOR3 * pposOld)
{
	bool bLand = false;
	int nCntEnemy;
	PLAYER * pPlayer;
	//プレイヤーの取得
	pPlayer = GetPlayer();

	//if (*ppEnemyRet != NULL)
	//{
	//	*ppEnemyRet = NULL;
	//}

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse)
		{
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_Enemy[nCntEnemy].pos.y&&
				pPlayer->pos.y <= g_Enemy[nCntEnemy].pos.y + g_vtxMaxEnemy.y)
			{
				//g_EnemyModel[g_Enemy[nCntEnemy].nType].MaxEnemy

				if (ppos->x + pPlayer->size.x > g_vtxMinEnemy.x + g_Enemy[nCntEnemy].pos.x&&
					ppos->x + pPlayer->size.x < g_vtxMaxEnemy.x + g_Enemy[nCntEnemy].pos.x)
				{
					//手前の当たり判定処理
					if (pposOld->z + pPlayer->size.z <= g_Enemy[nCntEnemy].pos.z - g_vtxMaxEnemy.z&&
						ppos->z + pPlayer->size.z >= g_Enemy[nCntEnemy].pos.z - g_vtxMaxEnemy.z)
					{
						ppos->z = g_Enemy[nCntEnemy].pos.z - pPlayer->size.z - g_vtxMaxEnemy.z;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					//奥の当たり判定処理
					if (pposOld->z - pPlayer->size.z >= g_Enemy[nCntEnemy].pos.z - g_vtxMinEnemy.z &&
						ppos->z - pPlayer->size.z < g_Enemy[nCntEnemy].pos.z - g_vtxMinEnemy.z)
					{
						ppos->z = g_Enemy[nCntEnemy].pos.z + pPlayer->size.z - g_vtxMinEnemy.z;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
			}
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_Enemy[nCntEnemy].pos.y&&
				pPlayer->pos.y <= g_Enemy[nCntEnemy].pos.y + g_vtxMaxEnemy.y)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinEnemy.z + g_Enemy[nCntEnemy].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxEnemy.z + g_Enemy[nCntEnemy].pos.z)
				{
					//左の当たり判定処理
					if (pposOld->x + pPlayer->size.x <= g_Enemy[nCntEnemy].pos.x - g_vtxMaxEnemy.x&&
						ppos->x + pPlayer->size.x >= g_Enemy[nCntEnemy].pos.x - g_vtxMaxEnemy.x)
					{
						ppos->x = g_Enemy[nCntEnemy].pos.x - pPlayer->size.x - g_vtxMaxEnemy.x;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					//右の当たり判定処理
					if (pposOld->x - pPlayer->size.x >= g_Enemy[nCntEnemy].pos.x - g_vtxMinEnemy.x&&
						ppos->x - pPlayer->size.x <= g_Enemy[nCntEnemy].pos.x - g_vtxMinEnemy.x)
					{
						ppos->x = g_Enemy[nCntEnemy].pos.x + pPlayer->size.x - g_vtxMinEnemy.x;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
			}
			if (ppos->x + pPlayer->size.x > g_vtxMinEnemy.x + g_Enemy[nCntEnemy].pos.x&&
				ppos->x + pPlayer->size.x < g_vtxMaxEnemy.x + g_Enemy[nCntEnemy].pos.x)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinEnemy.z + g_Enemy[nCntEnemy].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxEnemy.z + g_Enemy[nCntEnemy].pos.z)
				{
					////上の当たり判定処理
					//if (pposOld->y - pPlayer->size.y >= g_vtxMinEnemy.y - g_Enemy[nCntEnemy].pos.y &&
					//	ppos->y - pPlayer->size.y <= g_vtxMaxEnemy.y - g_Enemy[nCntEnemy].pos.y)
					//{
					//	//ppos->y = g_Enemy[nCntEnemy].pos.y + pPlayer->size.y + g_vtxMaxEnemy.y;
						//g_Enemy[nCntEnemy].bUse = false;
						//SetGameState(GAMESTATE_END);
					//SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					//}
					//下の当たり判定処理
					if (pPlayer->posOld.y + pPlayer->vtxMaxPlayer.y >= g_Enemy[nCntEnemy].pos.y)
					{
						//ppos->y = g_Enemy[nCntEnemy].pos.y + pPlayer->size.y + g_vtxMaxEnemy.y;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					}
				}
			}
		}
	}
	return bLand;
}


