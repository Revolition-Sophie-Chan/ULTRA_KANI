#pragma once
//=============================================================================
//
// 爆発処理 [explosion.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;		//色
	int nCounterAnim;	//カウンター
	int nPattenAnim;	//パターンNo
	bool bUse;			//使用してるかどうか
}EXPLOSION;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot);

#endif
