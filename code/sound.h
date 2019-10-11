//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
// �T�E���h�t�@�C��
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM�^�C�g��	1
	SOUND_LABEL_BGM001,			// BGM�퓬		2
	SOUND_LABEL_BGM002,			// BGM�N���A	3
	SOUND_LABEL_BGM003,			// BGMgameover	4
	SOUND_LABEL_SE_SWIM,		// �j��			5
	SOUND_LABEL_SE_GET,			// �l����		6
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
