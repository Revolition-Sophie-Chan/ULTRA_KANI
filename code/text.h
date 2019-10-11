//=============================================================================
//
// 画像データ読み込みの処理[text.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"
//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;								//ポリゴンの位置
	int scale_X;
	int scale_Y;
	int bUse;
	int nTextType;
}TEXT;
//=============================================================================
//プロトタイプ宣言
//=============================================================================
void InitMoji(void);
void UninitMoji(void);
void UpdateMoji(void);
void DrawMoji(void);
void SetText(D3DXVECTOR3 pos, int scale_X,int scale_Y, int nTextType);
TEXT *GetText(void);

#endif