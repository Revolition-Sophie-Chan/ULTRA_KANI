//=============================================================================
//
// アイテム処理 [item.h]
// Author : tanaka rikiya

//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_ITEM	(1)	// 最大数
#define ITEMSIZE_X	(70)	//テクスチャの幅
#define ITEMSIZE_Y	(70)	//テクスチャの高さ

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	ITEMTYPE_NORMAL = 0,
	ITEMTYPE_COIN,//横移動
	ITEMTYPE_MAX,
}ITEMTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;
	bool bUse;
	bool bItem;
}ITEM;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col);
ITEM *GetItem(void);
void MakeEffect_Item(void);
#endif
