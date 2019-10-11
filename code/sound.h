//=============================================================================
//
// サウンド処理 [sound.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
// サウンドファイル
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGMタイトル	1
	SOUND_LABEL_BGM001,			// BGM戦闘		2
	SOUND_LABEL_BGM002,			// BGMクリア	3
	SOUND_LABEL_BGM003,			// BGMgameover	4
	SOUND_LABEL_SE_SWIM,		// 泳ぐ			5
	SOUND_LABEL_SE_GET,			// 獲得音		6
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
