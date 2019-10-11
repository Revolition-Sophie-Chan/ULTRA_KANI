//=============================================================================
//
// 仲間処理 [nakama.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include <time.h>
#include "fade.h"
#include "nakama.h"
#include "input.h"
#include "camera.h"
#include "effect.h"
#include "player.h"
#include "ami.h"
#include "score.h"
#include "ami.h"
#include "game.h"
#include "sound.h"
#include "heart.h"
#include "input.h"
//#include "shadow.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define NAKAMA_01 "Data/Model/nakama/ebi.x"	//読み込むテクスチャファイル名
#define NAKAMA_02 "Data/Model/nakama/sakana.x"	//読み込むテクスチャファイル名
#define POLTGON0_TEX "Data/Texture/.jpg"	//読み込むテクスチャファイル名
#define SPEED		(0.5f)

//////////////////// 爆発の設定 ////////////////////
#define EFFECT_RADIUS	20.0f;
#define EFFECT_ANGLE	0.0f;
#define EFFECT_SPEED	5.0f;
#define EFFECT_COL		D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.95f);
#define EFFECT_LIFE		20;
////////////////////////////////////////////////////

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTexturenakama = NULL;
LPD3DXMESH				 g_pMeshnakama = {};
LPD3DXBUFFER			 g_pBuffMatnakama = NULL;
DWORD					 g_NumMatnakama = 0;

NAKAMA					 g_nakama[MAX_NAKAMA];

int randomNakama;

//Xファイルから最大値と最小値の取得
D3DXVECTOR3 g_vtxMaxnakama;		//最大値
D3DXVECTOR3 g_vtxMinnakama;		//最小値

//=============================================================================
// 初期化処理
//=============================================================================
void Initnakama(void)
{
	randomNakama = 0;

	srand((int)time(NULL)); //乱数使える
	int nCntnakama = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		// 位置・向きの初期設定
		g_nakama[nCntnakama].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_nakama[nCntnakama].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_nakama[nCntnakama].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_nakama[nCntnakama].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_nakama[nCntnakama].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_nakama[nCntnakama].bUse = false;
		g_nakama[nCntnakama].bFirst = false;
		g_nakama[nCntnakama].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回位置
		g_nakama[nCntnakama].nType = 0;
		g_nakama[nCntnakama].nCountGameover = 3;
		//g_nakama[nCntnakama].nIdxShadow = SetShadow(g_nakama[nCntnakama].pos, g_nakama[nCntnakama].rot);


	// テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			POLTGON0_TEX,
			&g_nakama[nCntnakama].aNakama[0].pTextureNakama);

		// Xファイルの読み込み
		D3DXLoadMeshFromX(
			NAKAMA_01,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_nakama[nCntnakama].aNakama[0].pBuffMatnakama,
			NULL,
			&g_nakama[nCntnakama].aNakama[0].nNumMatnakama,
			&g_nakama[nCntnakama].aNakama[0].pMeshnakama);

		// Xファイルの読み込み
		D3DXLoadMeshFromX(
			NAKAMA_02,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_nakama[nCntnakama].aNakama[1].pBuffMatnakama,
			NULL,
			&g_nakama[nCntnakama].aNakama[1].nNumMatnakama,
			&g_nakama[nCntnakama].aNakama[1].pMeshnakama);

		//Xファイルから最大値と最小値の設定
		int nNumVertices;						//頂点数
		DWORD sizeFVF;							//頂点フォーマットのサイズ
		BYTE *pVertexBuffer;					//頂点バッファのポインタ

		g_vtxMinnakama = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_vtxMaxnakama = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

		//頂点数を取得
		nNumVertices = g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->GetFVF());

		//頂点バッファをロック
		g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//すべての変数を比較して最小・最大値を決める
			if (g_vtxMinnakama.x > vtx.x)
			{
				g_vtxMinnakama.x = vtx.x;
			}
			if (g_vtxMaxnakama.x < vtx.x)
			{
				g_vtxMaxnakama.x = vtx.x;
			}
			if (g_vtxMinnakama.y > vtx.y)
			{
				g_vtxMinnakama.y = vtx.y;
			}
			if (g_vtxMaxnakama.y < vtx.y)
			{
				g_vtxMaxnakama.y = vtx.y;
			}
			if (g_vtxMinnakama.z > vtx.z)
			{
				g_vtxMinnakama.z = vtx.z;
			}
			if (g_vtxMaxnakama.z < vtx.z)
			{
				g_vtxMaxnakama.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;		//サイズ分ポインタを進める
		}

		//頂点バッファのアンロック
		g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->UnlockVertexBuffer();

	}


	//Setnakama(D3DXVECTOR3(0.0f, 0.0f, 000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
}
//=============================================================================
// 終了処理
//=============================================================================
void Uninitnakama(void)
{
	for (int nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		// メッシュの開放
		if (g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama != NULL)
		{
			g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->Release();
			g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatnakama != NULL)
		{
			g_pBuffMatnakama->Release();
			g_pBuffMatnakama = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Updatenakama(void)
{

	int nCntnakama;

	for (nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{

		g_nakama[nCntnakama].pos += g_nakama[nCntnakama].move;


			//if()
		if (GetMode() == MODE_GAME)
		{


			if (g_nakama[nCntnakama].bUse == false)
			{
				if (g_nakama[nCntnakama].bFirst == false)
				{
					Setnakama(D3DXVECTOR3(500.0f, 0.0f, 500.0f) , D3DXVECTOR3(0.0f, SPEED, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
					g_nakama[nCntnakama].bFirst = true;
				}
				else
				{
					D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 4000 - 2000.0f, 0.0f, rand() % 4000 - 2000.0f);
					Setnakama(pos, D3DXVECTOR3(0.0f, SPEED, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
				}
				// 影を消す
				//DeleteShadow(g_nakama[nCntnakama].nIdxShadow);
				//Setnakama(pos, D3DXVECTOR3(0.0f, SPEED, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
				//g_nakama[nCntnakama].bUse = true;
			}

			if (g_nakama[nCntnakama].pos.y >= 400)
			{
				AddHeart(-2);
				g_nakama[nCntnakama].nCountGameover--;
				g_nakama[nCntnakama].bUse = false;
				if (g_nakama[nCntnakama].nCountGameover <= 0)
				{
					SetFade(MODE_END);
				}
			}

			// 影の位置を設定
			//SetPositionShadow(g_nakama[nCntnakama].nIdxShadow, g_nakama[nCntnakama].pos);

		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void Drawnakama(void)
{
	LPDIRECT3DDEVICE9	 pDevice = GetDevice();
	D3DXMATRIX			 mtxSize, mtxRot, mtxTrans;				//計算用
	D3DXMATERIAL		 *pMat;
	D3DMATERIAL9		 matDef;

	for (int nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		if (g_nakama[nCntnakama].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_nakama[nCntnakama].mtxWorldnakama);

			// スケールを反映
			D3DXMatrixScaling(&mtxSize, g_nakama[nCntnakama].scale.x, g_nakama[nCntnakama].scale.y, g_nakama[nCntnakama].scale.z);
			D3DXMatrixMultiply(&g_nakama[nCntnakama].mtxWorldnakama, &g_nakama[nCntnakama].mtxWorldnakama, &mtxSize);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_nakama[nCntnakama].rot.y, g_nakama[nCntnakama].rot.x, g_nakama[nCntnakama].rot.z);
			D3DXMatrixMultiply(&g_nakama[nCntnakama].mtxWorldnakama, &g_nakama[nCntnakama].mtxWorldnakama, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_nakama[nCntnakama].pos.x, g_nakama[nCntnakama].pos.y, g_nakama[nCntnakama].pos.z);
			D3DXMatrixMultiply(&g_nakama[nCntnakama].mtxWorldnakama, &g_nakama[nCntnakama].mtxWorldnakama, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_nakama[nCntnakama].mtxWorldnakama);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_nakama[nCntnakama].aNakama[nCntnakama].pBuffMatnakama->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nakama[nCntnakama].aNakama[nCntnakama].nNumMatnakama; nCntMat++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTexturenakama);
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// 描画
				g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//============================================================================
// 仲間の取得
//=============================================================================
NAKAMA * Getnakama(void)
{
	return &g_nakama[0];
}

//============================================================================
// 仲間の設定
//=============================================================================
void Setnakama(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType)
{
	// 変数宣言
	int nCntnakama;
	for (nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		if (g_nakama[nCntnakama].bUse == false)
		{
			g_nakama[nCntnakama].pos = pos;
			g_nakama[nCntnakama].move = move;
			g_nakama[nCntnakama].rot = rot;
			g_nakama[nCntnakama].scale = scale;
			g_nakama[nCntnakama].bUse = true;
			g_nakama[nCntnakama].nType = nType;

			// 影の作成
			//g_nakama[nCntnakama].nIdxShadow = SetShadow(g_nakama[nCntnakama].pos, g_nakama[nCntnakama].rot);

			break;
		}
	}
}
//=======================================================================================
// 仲間の当たり判定
//=======================================================================================
bool Collisionnakama(D3DXVECTOR3 * ppos, D3DXVECTOR3 * pposOld)
{
	bool bLand = false;
	int nCntnakama;

	PLAYER * pPlayer;
	//プレイヤーの取得
	pPlayer = GetPlayer();

	AMI * pAmi;
	//プレイヤーの取得
	pAmi = Getami();

	//if (*ppnakamaRet != NULL)
	//{
	//	*ppnakamaRet = NULL;
	//}

	for (nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		if (g_nakama[nCntnakama].bUse)
		{
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_nakama[nCntnakama].pos.y&&
				pPlayer->pos.y <= g_nakama[nCntnakama].pos.y + g_vtxMaxnakama.y) 
			{
				if (ppos->x + pPlayer->size.x > g_vtxMinnakama.x + g_nakama[nCntnakama].pos.x&&
					ppos->x + pPlayer->size.x < g_vtxMaxnakama.x + g_nakama[nCntnakama].pos.x)
				{
					//手前の当たり判定処理
					if (pposOld->z + pPlayer->size.z <= g_nakama[nCntnakama].pos.z - g_vtxMaxnakama.z&&
						ppos->z + pPlayer->size.z >= g_nakama[nCntnakama].pos.z - g_vtxMaxnakama.z||
						pposOld->z - pPlayer->size.z >= g_nakama[nCntnakama].pos.z - g_vtxMinnakama.z &&
						ppos->z - pPlayer->size.z < g_nakama[nCntnakama].pos.z - g_vtxMinnakama.z)
					{
						PlaySound(SOUND_LABEL_SE_GET);
						AddScore(1);
						g_nakama[nCntnakama].bUse = false;
						pAmi->bUse = false;
						MakeEffect_Nakama();
						//ppos->z = g_nakama[nCntnakama].pos.z - pPlayer->size.z - g_vtxMaxnakama.z;
					}

					////奥の当たり判定処理
					//if (pposOld->z - pPlayer->size.z >= g_nakama[nCntnakama].pos.z - g_vtxMinnakama.z &&
					//	ppos->z - pPlayer->size.z < g_nakama[nCntnakama].pos.z - g_vtxMinnakama.z)
					//{
					//	PlaySound(SOUND_LABEL_SE_GET);
					//	AddScore(1);
					//	g_nakama[nCntnakama].bUse = false;
					//	pAmi->bUse = false;
					//	MakeEffect_Nakama();
					//	//ppos->z = g_nakama[nCntnakama].pos.z + pPlayer->size.z - g_vtxMinnakama.z;
					//}
				}
			}
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_nakama[nCntnakama].pos.y&&
				pPlayer->pos.y <= g_nakama[nCntnakama].pos.y + g_vtxMaxnakama.y) 
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinnakama.z + g_nakama[nCntnakama].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxnakama.z + g_nakama[nCntnakama].pos.z)
				{
					//左の当たり判定処理
					if (pposOld->x + pPlayer->size.x <= g_nakama[nCntnakama].pos.x - g_vtxMaxnakama.x&&
						ppos->x + pPlayer->size.x >= g_nakama[nCntnakama].pos.x - g_vtxMaxnakama.x||
						pposOld->x - pPlayer->size.x >= g_nakama[nCntnakama].pos.x - g_vtxMinnakama.x&&
						ppos->x - pPlayer->size.x <= g_nakama[nCntnakama].pos.x - g_vtxMinnakama.x)
					{
						PlaySound(SOUND_LABEL_SE_GET);
						AddScore(1);
						g_nakama[nCntnakama].bUse = false;
						pAmi->bUse = false;
						MakeEffect_Nakama();
						//ppos->x = g_nakama[nCntnakama].pos.x - pPlayer->size.x - g_vtxMaxnakama.x;
					}

					////右の当たり判定処理
					//if (pposOld->x - pPlayer->size.x >= g_nakama[nCntnakama].pos.x - g_vtxMinnakama.x&&
					//	ppos->x - pPlayer->size.x <= g_nakama[nCntnakama].pos.x - g_vtxMinnakama.x)
					//{
					//	PlaySound(SOUND_LABEL_SE_GET);
					//	AddScore(1);
					//	g_nakama[nCntnakama].bUse = false;
					//	pAmi->bUse = false;
					//	MakeEffect_Nakama();
					//	//ppos->x = g_nakama[nCntnakama].pos.x + pPlayer->size.x - g_vtxMinnakama.x;
					//}
				}
			}
			if (ppos->x + pPlayer->size.x > g_vtxMinnakama.x + g_nakama[nCntnakama].pos.x&&
				ppos->x + pPlayer->size.x < g_vtxMaxnakama.x + g_nakama[nCntnakama].pos.x)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinnakama.z + g_nakama[nCntnakama].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxnakama.z + g_nakama[nCntnakama].pos.z)
				{
					//上の当たり判定処理
					if (pposOld->y - pPlayer->size.y >= g_vtxMinnakama.y - g_nakama[nCntnakama].pos.y &&
						ppos->y - pPlayer->size.y <= g_vtxMaxnakama.y - g_nakama[nCntnakama].pos.y||
						pPlayer->posOld.y + pPlayer->vtxMaxPlayer.y >= g_nakama[nCntnakama].pos.y)
					{
						PlaySound(SOUND_LABEL_SE_GET);
						AddScore(1);
						g_nakama[nCntnakama].bUse = false;
						pAmi->bUse = false;
						MakeEffect_Nakama();
						//ppos->y = g_nakama[nCntnakama].pos.y + pPlayer->size.y + g_vtxMaxnakama.y;
					}
				}
			}
		}
	}
	return bLand;
}
//=======================================================================================
// パーティクル関数
//=======================================================================================
void MakeEffect_Nakama(void)
{
	int nCntnakama=0;

	//////////////////// 爆発の設定 ////////////////////
	D3DXCOLOR col	= EFFECT_COL;
	float fRadius	= EFFECT_RADIUS;
	float fAngle	= EFFECT_ANGLE;
	float fSpeed	= EFFECT_SPEED;
	int nLife		= EFFECT_LIFE;
	////////////////////////////////////////////////////
	for (int nCnt = 0; nCnt < 60; nCnt++)
	{
		// 0～3.14を出す * (0 or 1)* -1で正負を決める(出す範囲)
		fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;	// 全方向出す

																				// 発生位置
		D3DXVECTOR3 pos1 = D3DXVECTOR3(g_nakama[nCntnakama].pos.x, g_nakama[nCntnakama].pos.y, g_nakama[nCntnakama].pos.z);

		// 出す向き
		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed, 0.0f);
		D3DXVECTOR3 move1 = D3DXVECTOR3(sinf(fAngle)*fSpeed, 0.0f, cosf(fAngle)*fSpeed);
		D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed);

		// エフェクトの設定
		SetEffect(pos1, move, fRadius, nLife, col,	0);
		SetEffect(pos1, move1, fRadius, nLife, col, 0);
		SetEffect(pos1, move2, fRadius, nLife, col, 0);
	}
}
