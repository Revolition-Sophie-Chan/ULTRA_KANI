//=============================================================================
//
// チュートリアル（一枚絵）の処理[Tutorial0.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _Tutorial0_H_
#define _Tutorial0_H_

#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"
//=============================================================================
// 状態
//=============================================================================
typedef enum
{
	TUTORIAL0STATE_NONE = 0,	//何もしていない
	TUTORIAL0STATE_NORMAL,	//通常状態
	TUTORIAL0STATE_END,		//クリア
	TUTORIAL0STATE_BADEND,	//死亡
	TUTORIAL0STATE_MAX
} TUTORIAL0STATE;
//=============================================================================
//プロトタイプ宣言
//=============================================================================
void InitTutorial0(void);
void UninitTutorial0(void);
void UpdateTutorial0(void);
void DrawTutorial0(void);
void SetTutorial0State(TUTORIAL0STATE state);
TUTORIAL0STATE GetTutorial0State(void);
#endif