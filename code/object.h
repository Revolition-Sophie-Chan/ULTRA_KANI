#pragma once
//=============================================================================
//
// 障害物処理 [object.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_OBJECT	(102)
#define MAX_LOADOBJECT	(2)
//=============================================================================
// 状態
//=============================================================================
typedef enum
{
	OBJECTTYPE_SANGO = 0,
	OBJECTTYPE_ROCK,
	OBJECTTYPE_MAX,
} OBJECTTYPE;
//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3	 pos;								//ポリゴンの位置
	D3DXVECTOR3	 posold;							//前回位置
	D3DXVECTOR3	 move;								//ポリゴンの移動
	D3DXVECTOR3	 scale;								//ポリゴンの拡大,縮小
	D3DXVECTOR3	 rot;								//ポリゴンの向き
	D3DXVECTOR3	 Diffrot;							//ポリゴンの向き
	D3DXMATRIX	 mtxWorldObject;						//ワールドマトリックス
	int			 hIdxShadow;						//影の設定
	int			 bUse;
	int			 nType;
}OBJECT;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
OBJECT *GetObjectModel(void);

bool ColisionObject(
	D3DXVECTOR3 * ppos,
	D3DXVECTOR3 * pposOld);

void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, OBJECTTYPE nType);
#endif
