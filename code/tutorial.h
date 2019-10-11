//=============================================================================
//
// �`���[�g���A���̏���[tutorial.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#define _CRT_SECURE_NO_WARNINGS

//�C���N���[�h�t�@�C��
#include "main.h"
//=============================================================================
// ���
//=============================================================================
typedef enum
{
	TUTORIALSTATE_NONE = 0,	//�������Ă��Ȃ�
	TUTORIALSTATE_NORMAL,	//�ʏ���
	TUTORIALSTATE_END,		//�N���A
	TUTORIALSTATE_BADEND,	//���S
	TUTORIALSTATE_MAX
} TUTORIALSTATE;
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorialState(TUTORIALSTATE state);
TUTORIALSTATE GetTutorialState(void);
#endif