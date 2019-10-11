//=============================================================================
//
// ゲームの処理[Game.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"
//=============================================================================
// 状態
//=============================================================================
typedef enum
{
	GAMESTATE_NONE = 0,	//何もしていない
	GAMESTATE_NORMAL,	//通常状態
	GAMESTATE_END,		//クリア
	GAMESTATE_BADEND,	//死亡
	GAMESTATE_MAX
} GAMESTATE;
//=============================================================================
//プロトタイプ宣言
//=============================================================================
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

int *GetGameEnemyCounter();

#endif