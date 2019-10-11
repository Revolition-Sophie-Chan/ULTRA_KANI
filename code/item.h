//=============================================================================
//
// �A�C�e������ [item.h]
// Author : tanaka rikiya

//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_ITEM	(1)	// �ő吔
#define ITEMSIZE_X	(70)	//�e�N�X�`���̕�
#define ITEMSIZE_Y	(70)	//�e�N�X�`���̍���

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	ITEMTYPE_NORMAL = 0,
	ITEMTYPE_COIN,//���ړ�
	ITEMTYPE_MAX,
}ITEMTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;
	bool bUse;
	bool bItem;
}ITEM;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col);
ITEM *GetItem(void);
void MakeEffect_Item(void);
#endif
