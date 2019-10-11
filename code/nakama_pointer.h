//=============================================================================
//
// ���ԃ|�C���^�[���� [nakama_pointer.h]
// Author : tanaka rikiya

//=============================================================================
#ifndef _NAKAMA_POINTER_H_
#define _NAKAMA_POINTER_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_POINTER	(1)	// �ő吔
#define ITEMSIZE_X	(70)	//�e�N�X�`���̕�
#define ITEMSIZE_Y	(70)	//�e�N�X�`���̍���

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	NAKAMA_POINTERTYPE_NORMAL = 0,
	NAKAMA_POINTERTYPE_COIN,//���ړ�
	NAKAMA_POINTERTYPE_MAX,
}POINTERTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;
	bool bUse;
	bool bItem;
	int nType;
}POINTER;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPointer(void);
void UninitPointer(void);
void UpdatePointer(void);
void DrawPointer(void);
void SetPointer(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
POINTER *GetPointer(void);
#endif
