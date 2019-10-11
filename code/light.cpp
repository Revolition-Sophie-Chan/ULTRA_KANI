//=============================================================================
//
// ライト処理 [light.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "light.h"
#include "camera.h"
//=============================================================================
// マクロ定義
//=============================================================================


//=============================================================================
// グローバル変数
//=============================================================================
D3DLIGHT9 g_light[3];//ライト

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXVECTOR3 vecDir[3];

	for (int nCntHikari = 0; nCntHikari < 3; nCntHikari++)
	{

		// ライトをクリアする
		ZeroMemory(&g_light, sizeof(D3DLIGHT9));

		// ライトの種類を設定
		g_light[nCntHikari].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ライトの方向の設定
		vecDir[0] = D3DXVECTOR3(0.35f, -0.63f, 0.69f);
		vecDir[1] = D3DXVECTOR3(-0.72f, -0.52f, -0.46f);
		vecDir[2] = D3DXVECTOR3(-0.25f, 0.7f, -0.67f);
		//正規化

		D3DXVec3Normalize(&vecDir[nCntHikari], &vecDir[nCntHikari]);
		g_light[nCntHikari].Direction = vecDir[nCntHikari];
		
		// ライトを設定する
		pDevice->SetLight(nCntHikari, &g_light[nCntHikari]);

		// ライトを有効にする
		pDevice->LightEnable(nCntHikari, TRUE);

	}
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXVECTOR3 vecDir[3];
	CAMERA *pCamera;
	pCamera = GetCamera();
	for (int nCntHikari = 0; nCntHikari < 3; nCntHikari++)
	{
		if (pCamera->posV.y >= 300)
		{
			g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (pCamera->posV.y < 300)
		{
			g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_light[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);
			g_light[2].Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}
		//D3DXVec3Normalize(&vecDir[nCntHikari], &vecDir[nCntHikari]);//正規化
		//g_light[nCntHikari].Direction = vecDir[nCntHikari];

		// ライトを設定する
		pDevice->SetLight(nCntHikari, &g_light[nCntHikari]);

		// ライトを設定する
		pDevice->SetLight(nCntHikari, &g_light[nCntHikari]);

		// ライトを有効にする
		pDevice->LightEnable(nCntHikari, TRUE);
	}
}

