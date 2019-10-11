//=============================================================================
//
// 背景処理 [Haitei.h]
// Author : tanaka rikiya

//=============================================================================
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#ifndef _HAIKEI_H_
#define _HAIKEI_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_HAIKEI	(4)	// 最大数
#define HAIKEISIZE_X	(70)	//テクスチャの幅
#define HAIKEISIZE_Y	(70)	//テクスチャの高さ

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	HAIKEITYPE_NORMAL = 0,
	HAIKEITYPE_COIN,//横移動
	HAIKEITYPE_MAX,
}HAIKEITYPE;

typedef struct
{
	D3DXVECTOR3 rot;
	D3DXVECTOR3 pos;
	D3DXMATRIX mtxWorld;
	bool bUse;
}HAIKEI;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitHaikei(void);
void UninitHaikei(void);
void UpdateHaikei(void);
void DrawHaikei(void);
void SetHaikei(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif
