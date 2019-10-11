#pragma once
//=============================================================================
//
// 仲間処理 [nakama.h]
// Author : 
//
//=============================================================================
#ifndef _NAKAMA_H_
#define _NAKAMA_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_NAKAMA	(1)

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXMATRIX			 mtxWorldnakama;
	LPD3DXMESH			 pMeshnakama;
	LPD3DXBUFFER		 pBuffMatnakama;
	LPDIRECT3DTEXTURE9	 pTextureNakama;
	DWORD				 nNumMatnakama;
} NAKAMATYPE;
typedef struct
{
	D3DXVECTOR3 pos;								//ポリゴンの位置
	D3DXVECTOR3 posold;								//前回位置
	D3DXVECTOR3 move;								//ポリゴンの移動
	D3DXVECTOR3 scale;								//ポリゴンの拡大,縮小
	D3DXVECTOR3 rot;								//ポリゴンの向き
	D3DXVECTOR3 Diffrot;							//ポリゴンの向き
	D3DXMATRIX mtxWorldnakama;						//ワールドマトリックス
	int nIdxShadow;									//影の設定
	bool bUse;
	bool bFirst;
	int nType;
	int nCountGameover;
	NAKAMATYPE aNakama[2];
}NAKAMA;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void Initnakama(void);
void Uninitnakama(void);
void Updatenakama(void);
void Drawnakama(void);
NAKAMA *Getnakama(void);
bool Collisionnakama(D3DXVECTOR3 * ppos,D3DXVECTOR3 * pposOld);
void Setnakama(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType);
void MakeEffect_Nakama(void);
#endif
