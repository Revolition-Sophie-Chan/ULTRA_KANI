#pragma once
//=============================================================================
//
// 壁処理 [meshwall.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

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
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	bool bUse;
} MESHWALL;


//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);


#endif