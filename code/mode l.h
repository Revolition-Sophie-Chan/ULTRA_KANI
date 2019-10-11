#pragma once
//=============================================================================
//
// ���f������ [model.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MODEL (13)

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct 
{
	LPDIRECT3DTEXTURE9	 pTextureModel = NULL;//�e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER		 pBuffMatModel;
	D3DXVECTOR3			 pos;
	D3DXVECTOR3			 rot;
	D3DXMATRIX			 mtxWorldModel;
	LPD3DXMESH			 pMeshModel;
	DWORD				 nNumMatModel;
	int					 nIdModelParent;
} MODELOBJ;

typedef struct
{
	D3DXVECTOR3	 pos;
	D3DXVECTOR3	 move;
	D3DXVECTOR3	 rot;
	D3DXVECTOR3	 scale;								//�|���S���̌���
	D3DXVECTOR3	 Diffrot;							//�|���S���̌���
	D3DXMATRIX	 mtxWorld;
	D3DXMATRIX	 mtxView;
	D3DXVECTOR3	 vtxMin;
	D3DXVECTOR3	 vtxMax;
	MODELOBJ	 aModel[1];
	bool		 bUse;
	int			 nType;
	int			 nIdShadow;
} MODEL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

void CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld);

void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType);

#endif
