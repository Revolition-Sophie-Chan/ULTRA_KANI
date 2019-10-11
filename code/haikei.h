//=============================================================================
//
// �w�i���� [Haitei.h]
// Author : tanaka rikiya

//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#ifndef _HAIKEI_H_
#define _HAIKEI_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_HAIKEI	(4)	// �ő吔
#define HAIKEISIZE_X	(70)	//�e�N�X�`���̕�
#define HAIKEISIZE_Y	(70)	//�e�N�X�`���̍���

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	HAIKEITYPE_NORMAL = 0,
	HAIKEITYPE_COIN,//���ړ�
	HAIKEITYPE_MAX,
}HAIKEITYPE;

typedef struct
{
	D3DXVECTOR3 rot;
	D3DXVECTOR3 pos;
	D3DXMATRIX mtxWorld;
	bool bUse;
}HAIKEI;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitHaikei(void);
void UninitHaikei(void);
void UpdateHaikei(void);
void DrawHaikei(void);
void SetHaikei(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif