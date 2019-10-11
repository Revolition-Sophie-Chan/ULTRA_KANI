//=============================================================================
//
// �J�������� [camera.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �J�����̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;			//�ړ�
	D3DXVECTOR3 rot;			//��]
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	float fDistance;

}CAMERA;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
CAMERA *GetCamera(void);
#endif
