//=============================================================================
//
// 仲間ポインター処理 [nakama_pointer.h]
// Author : tanaka rikiya

//=============================================================================
#ifndef _NAKAMA_POINTER_H_
#define _NAKAMA_POINTER_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_POINTER	(1)	// 最大数
#define ITEMSIZE_X	(70)	//テクスチャの幅
#define ITEMSIZE_Y	(70)	//テクスチャの高さ

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	NAKAMA_POINTERTYPE_NORMAL = 0,
	NAKAMA_POINTERTYPE_COIN,//横移動
	NAKAMA_POINTERTYPE_MAX,
}POINTERTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;
	bool bUse;
	bool bItem;
	int nType;
}POINTER;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPointer(void);
void UninitPointer(void);
void UpdatePointer(void);
void DrawPointer(void);
void SetPointer(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
POINTER *GetPointer(void);
#endif
