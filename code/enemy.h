#pragma once
//=============================================================================
//
// �G���� [enemy.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ENEMY	(102)
#define MAX_LOADENEMY	(2)
//=============================================================================
// ���
//=============================================================================
typedef enum
{
	ENEMYTYPE_SHIP = 0,
	ENEMYTYPE_GYOSEN,
	ENEMYTYPE_MAX,
} ENEMYTYPE_ENEMY;
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
	D3DXMATRIX	 mtxWorldEnemy;						//���[���h�}�g���b�N�X
	int			 hIdxShadow;						//�e�̐ݒ�
	int			 bUse;
	int			 nType;
}ENEMY;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);

bool ColisionEnemy(
	D3DXVECTOR3 * ppos,
	D3DXVECTOR3 * pposOld);

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, ENEMYTYPE_ENEMY nType);
#endif
