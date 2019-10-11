#pragma once
//=============================================================================
//
// ���ԏ��� [nakama.h]
// Author : 
//
//=============================================================================
#ifndef _NAKAMA_H_
#define _NAKAMA_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_NAKAMA	(1)

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXMATRIX			 mtxWorldnakama;
	LPD3DXMESH			 pMeshnakama;
	LPD3DXBUFFER		 pBuffMatnakama;
	LPDIRECT3DTEXTURE9	 pTextureNakama;
	DWORD				 nNumMatnakama;
} NAKAMATYPE;
typedef struct
{
	D3DXVECTOR3 pos;								//�|���S���̈ʒu
	D3DXVECTOR3 posold;								//�O��ʒu
	D3DXVECTOR3 move;								//�|���S���̈ړ�
	D3DXVECTOR3 scale;								//�|���S���̊g��,�k��
	D3DXVECTOR3 rot;								//�|���S���̌���
	D3DXVECTOR3 Diffrot;							//�|���S���̌���
	D3DXMATRIX mtxWorldnakama;						//���[���h�}�g���b�N�X
	int nIdxShadow;									//�e�̐ݒ�
	bool bUse;
	bool bFirst;
	int nType;
	int nCountGameover;
	NAKAMATYPE aNakama[2];
}NAKAMA;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void Initnakama(void);
void Uninitnakama(void);
void Updatenakama(void);
void Drawnakama(void);
NAKAMA *Getnakama(void);
bool Collisionnakama(D3DXVECTOR3 * ppos,D3DXVECTOR3 * pposOld);
void Setnakama(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType);
void MakeEffect_Nakama(void);
#endif
