//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 状態
//=============================================================================

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// 色
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	float fRadius;			// 半径
	float fSpeed;
	float fAngle;
	int nType;				// タイプ
	int nLife;				// ライフ
	bool bUse;				// 使用しているかどうか
} EFFECT;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

//void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, D3DXVECTOR3 rot,D3DXVECTOR3 move);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius ,int nLife, D3DXCOLOR col, int nType);
#endif
