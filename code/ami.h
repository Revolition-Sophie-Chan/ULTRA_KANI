//=============================================================================
//
// 網処理 [ami.h]
// Author : tanaka rikiya
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#ifndef _AMI_H_
#define _AMI_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_AMI	(1)	// 最大数
#define AMISIZE_X	(70)	//テクスチャの幅
#define AMISIZE_Y	(70)	//テクスチャの高さ

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	AMITYPE_NORMAL = 0,
	AMITYPE_COIN,//横移動
	AMITYPE_MAX,
}AMITYPE;

typedef struct
{
	D3DXVECTOR3 rot;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;
	float fAngle;
	float fLength;
	bool bUse;
}AMI;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void Initami(void);
void Uninitami(void);
void Updateami(void);
void Drawami(void);
void Setami(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot, D3DXVECTOR3 move);
AMI *Getami(void);
#endif
