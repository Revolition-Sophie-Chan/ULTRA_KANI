#pragma once
//=============================================================================
//
// �������� [explosion.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;		//�F
	int nCounterAnim;	//�J�E���^�[
	int nPattenAnim;	//�p�^�[��No
	bool bUse;			//�g�p���Ă邩�ǂ���
}EXPLOSION;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot);

#endif
