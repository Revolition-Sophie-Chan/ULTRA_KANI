//=============================================================================
//
// �`���[�g���A���i�ꖇ�G�j�̏���[Tutorial0.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _Tutorial0_H_
#define _Tutorial0_H_

#define _CRT_SECURE_NO_WARNINGS

//�C���N���[�h�t�@�C��
#include "main.h"
//=============================================================================
// ���
//=============================================================================
typedef enum
{
	TUTORIAL0STATE_NONE = 0,	//�������Ă��Ȃ�
	TUTORIAL0STATE_NORMAL,	//�ʏ���
	TUTORIAL0STATE_END,		//�N���A
	TUTORIAL0STATE_BADEND,	//���S
	TUTORIAL0STATE_MAX
} TUTORIAL0STATE;
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
void InitTutorial0(void);
void UninitTutorial0(void);
void UpdateTutorial0(void);
void DrawTutorial0(void);
void SetTutorial0State(TUTORIAL0STATE state);
TUTORIAL0STATE GetTutorial0State(void);
#endif