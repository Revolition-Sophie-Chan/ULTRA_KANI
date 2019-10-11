//=============================================================================
//
// �ԏ��� [ami.h]
// Author : tanaka rikiya
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#ifndef _AMI_H_
#define _AMI_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_AMI	(1)	// �ő吔
#define AMISIZE_X	(70)	//�e�N�X�`���̕�
#define AMISIZE_Y	(70)	//�e�N�X�`���̍���

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	AMITYPE_NORMAL = 0,
	AMITYPE_COIN,//���ړ�
	AMITYPE_MAX,
}AMITYPE;

typedef struct
{
	D3DXVECTOR3 rot;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;
	float fAngle;
	float fLength;
	bool bUse;
}AMI;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void Initami(void);
void Uninitami(void);
void Updateami(void);
void Drawami(void);
void Setami(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot, D3DXVECTOR3 move);
AMI *Getami(void);
#endif
