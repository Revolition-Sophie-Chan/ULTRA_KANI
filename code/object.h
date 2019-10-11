#pragma once
//=============================================================================
//
// ��Q������ [object.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_OBJECT	(102)
#define MAX_LOADOBJECT	(2)
//=============================================================================
// ���
//=============================================================================
typedef enum
{
	OBJECTTYPE_SANGO = 0,
	OBJECTTYPE_ROCK,
	OBJECTTYPE_MAX,
} OBJECTTYPE;
//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3	 pos;								//�|���S���̈ʒu
	D3DXVECTOR3	 posold;							//�O��ʒu
	D3DXVECTOR3	 move;								//�|���S���̈ړ�
	D3DXVECTOR3	 scale;								//�|���S���̊g��,�k��
	D3DXVECTOR3	 rot;								//�|���S���̌���
	D3DXVECTOR3	 Diffrot;							//�|���S���̌���
	D3DXMATRIX	 mtxWorldObject;						//���[���h�}�g���b�N�X
	int			 hIdxShadow;						//�e�̐ݒ�
	int			 bUse;
	int			 nType;
}OBJECT;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
OBJECT *GetObjectModel(void);

bool ColisionObject(
	D3DXVECTOR3 * ppos,
	D3DXVECTOR3 * pposOld);

void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, OBJECTTYPE nType);
#endif
