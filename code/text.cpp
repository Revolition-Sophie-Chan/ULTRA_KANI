//=============================================================================
//
// 画像読み込みの処理[Text.cpp]
// Author：tanaka rikiya
//
//=============================================================================
//インクルードファイル
#include "main.h"
#include "Player.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "text.h"
//#include "sound.h"
//#include "tutorial.h"
//#include "joystick.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXT		(8)		//読み込むテクスチャの数
#define	TEXTURE_TEXT0		"Data/Texture/text03.png"	//Pressエンタ
#define	TEXTURE_TEXT1		"Data/Texture/kaniロゴ.png"	//ロゴ
#define	TEXTURE_TEXT2		"Data/Texture/text01.png"		//助けた仲間
#define	TEXTURE_TEXT3		"Data/Texture/tutorial2.png"	//チュートリアルメッセージ
#define	TEXTURE_TEXT4		"Data/Texture/Help_down.png"	//ヘルプアイコン
#define	TEXTURE_TEXT5		"Data/Texture/text02.png"		//左方向ヘルプ
#define	TEXTURE_TEXT6		"Data/Texture/rank.png"	//ランキング
#define	TEXTURE_TEXT7		"Data/Texture/tutorial.png"	//チュートリアル

//=============================================================================
//グローバル変数
//=============================================================================
VERTEX_2D g_aVertex[4];
LPDIRECT3DTEXTURE9 g_pTextureText[MAX_TEXT] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffText = NULL;		//頂点バッファへのポインタ

TEXT				 g_nText[MAX_TEXT];

int g_nCounterText;								//アニメーションカウンター
int g_nPattenText;									//アニメーションパターン
int g_nCounterText2;								//アニメーションカウンター
int g_nPattenText2;									//アニメーションパターン

//=============================================================================
// ポリゴンの初期化
//=============================================================================
void InitMoji(void)
{

	int nCntText;
	g_nCounterText=0;		//アニメーションカウンター
	g_nPattenText=0;

	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		g_nText[nCntText].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//ポリゴンの位置
		g_nText[nCntText].bUse = false;
		g_nText[nCntText].nTextType = 0;
		g_nText[nCntText].scale_X = 0;
		g_nText[nCntText].scale_Y = 0;
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT0,	//Pressエンタ
		&g_pTextureText[0]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT1,	//ロゴ
		&g_pTextureText[1]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT2,	//助けた仲間
		&g_pTextureText[2]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT3,	//チュートリアルメッセージ
		&g_pTextureText[3]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT4,	//ロゴ
		&g_pTextureText[4]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT5,	//左ヘルプ
		&g_pTextureText[5]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT6,	//ランキング
		&g_pTextureText[6]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT7,	//チュートリアル
		&g_pTextureText[7]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffText,
		NULL);


	VERTEX_2D *pVtx;//頂点情報へのポインタ
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffText->Lock(0, 0, (void**)&pVtx, 0);
	//頂点の設定	
	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_nText[nCntText].pos.x - g_nText[nCntText].scale_X, g_nText[nCntText].pos.y - g_nText[nCntText].scale_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_nText[nCntText].pos.x  + g_nText[nCntText].scale_X, g_nText[nCntText].pos.y - g_nText[nCntText].scale_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_nText[nCntText].pos.x  - g_nText[nCntText].scale_X, g_nText[nCntText].pos.y + g_nText[nCntText].scale_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_nText[nCntText].pos.x  + g_nText[nCntText].scale_X, g_nText[nCntText].pos.y + g_nText[nCntText].scale_Y, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//頂点データのアンロック
	g_pVtxBuffText->Unlock();
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void UninitMoji(void)
{
	int nCntText;

	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		//テクスチャの開放
		if (g_pTextureText[nCntText] != NULL)
		{
			g_pTextureText[nCntText]->Release();
			g_pTextureText[nCntText] = NULL;
		}
	}
	if (g_pVtxBuffText != NULL)
	{
		g_pVtxBuffText->Release();
		g_pVtxBuffText = NULL;
	}
}
//=============================================================================
// polygon更新処理
//=============================================================================
void UpdateMoji(void)
{
	int nCntText;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffText->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		if (g_nText[nCntText].nTextType == 0)
		{
			g_nCounterText++;
			if (g_nCounterText % 40 == 0)
			{
				g_nPattenText = (g_nPattenText + 1) % 2;
				if (g_nPattenText == 0)
				{
					pVtx[0].col = D3DXCOLOR(255, 255, 255, 0);
					pVtx[1].col = D3DXCOLOR(255, 255, 255, 0);
					pVtx[2].col = D3DXCOLOR(255, 255, 255, 0);
					pVtx[3].col = D3DXCOLOR(255, 255, 255, 0);
				}
				else
				{
					pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
					pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
					pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
					pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);
				}
			}
		}
		pVtx += 4;
	}
	//頂点データのアンロック
	g_pVtxBuffText->Unlock();

}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void DrawMoji(void)
{

	int nCntText;
	LPDIRECT3DDEVICE9 pDevice;
	////バックバッファとフロントバッファの入れかえ
	//g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデバイスのデータストリートにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffText, 0, sizeof(VERTEX_2D));

	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		if (g_nText[nCntText].bUse)
		{
			pDevice->SetTexture(0, g_pTextureText[g_nText[nCntText].nTextType]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntText * 4, 2);
		}
	}
}

//=============================================================================
// テキストの設定
//=============================================================================
void SetText(D3DXVECTOR3 pos, int scale_X, int scale_Y,int nTextType)
{
	int nCntText;
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffText->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{

		if (g_nText[nCntText].bUse == false)	//未使用
		{
			g_nText[nCntText].pos = pos;
			g_nText[nCntText].nTextType = nTextType;
			g_nText[nCntText].scale_X = scale_X;
			g_nText[nCntText].scale_Y = scale_Y;

			//座標設定
			pVtx[0].pos = D3DXVECTOR3(g_nText[nCntText].pos.x - g_nText[nCntText].scale_X, g_nText[nCntText].pos.y - g_nText[nCntText].scale_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_nText[nCntText].pos.x + g_nText[nCntText].scale_X, g_nText[nCntText].pos.y - g_nText[nCntText].scale_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_nText[nCntText].pos.x - g_nText[nCntText].scale_X, g_nText[nCntText].pos.y + g_nText[nCntText].scale_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_nText[nCntText].pos.x + g_nText[nCntText].scale_X, g_nText[nCntText].pos.y + g_nText[nCntText].scale_Y, 0.0f);
			//pVtx += 4;

			g_nText[nCntText].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffText->Unlock();
}
//=============================================================================
// アイテムの取得
//=============================================================================
TEXT *GetText(void)
{
	return &g_nText[0];
}