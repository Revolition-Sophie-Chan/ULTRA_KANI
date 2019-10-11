//=============================================================================
//
// チュートリアルの処理[tutorial.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"
//=============================================================================
// 状態
//=============================================================================
typedef enum
{
	TUTORIALSTATE_NONE = 0,	//何もしていない
	TUTORIALSTATE_NORMAL,	//通常状態
	TUTORIALSTATE_END,		//クリア
	TUTORIALSTATE_BADEND,	//死亡
	TUTORIALSTATE_MAX
} TUTORIALSTATE;
//=============================================================================
//プロトタイプ宣言
//=============================================================================
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorialState(TUTORIALSTATE state);
TUTORIALSTATE GetTutorialState(void);
#endif