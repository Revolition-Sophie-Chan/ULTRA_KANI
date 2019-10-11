#pragma once
//=============================================================================
//
// 敵処理 [enemy.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMY	(102)
#define MAX_LOADENEMY	(2)
//=============================================================================
// 状態
//=============================================================================
typedef enum
{
	ENEMYTYPE_SHIP = 0,
	ENEMYTYPE_GYOSEN,
	ENEMYTYPE_MAX,
} ENEMYTYPE_ENEMY;
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
	D3DXMATRIX	 mtxWorldEnemy;						//ワールドマトリックス
	int			 hIdxShadow;						//影の設定
	int			 bUse;
	int			 nType;
}ENEMY;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);

bool ColisionEnemy(
	D3DXVECTOR3 * ppos,
	D3DXVECTOR3 * pposOld);

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, ENEMYTYPE_ENEMY nType);
#endif
