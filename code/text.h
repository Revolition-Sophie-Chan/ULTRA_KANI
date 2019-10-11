//=============================================================================
//
// �摜�f�[�^�ǂݍ��݂̏���[text.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

#define _CRT_SECURE_NO_WARNINGS

//�C���N���[�h�t�@�C��
#include "main.h"
//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;								//�|���S���̈ʒu
	int scale_X;
	int scale_Y;
	int bUse;
	int nTextType;
}TEXT;
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
void InitMoji(void);
void UninitMoji(void);
void UpdateMoji(void);
void DrawMoji(void);
void SetText(D3DXVECTOR3 pos, int scale_X,int scale_Y, int nTextType);
TEXT *GetText(void);

#endif