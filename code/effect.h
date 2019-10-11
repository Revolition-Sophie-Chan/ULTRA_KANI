//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// ���
//=============================================================================

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	float fRadius;			// ���a
	float fSpeed;
	float fAngle;
	int nType;				// �^�C�v
	int nLife;				// ���C�t
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

//void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, D3DXVECTOR3 rot,D3DXVECTOR3 move);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius ,int nLife, D3DXCOLOR col, int nType);
#endif
