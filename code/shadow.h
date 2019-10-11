//=============================================================================
//
// 影処理 [shadow.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void DeleteShadow(int nIdxShadow);


#endif
