//=============================================================================
//
// �X�R�A���� [score.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue);
int GetScore(void);
#endif