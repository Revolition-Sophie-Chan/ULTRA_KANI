#pragma once
//=============================================================================
//
// �Ǐ��� [meshwall.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

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
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	bool bUse;
} MESHWALL;


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);


#endif