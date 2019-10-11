//=============================================================================
//
// ���C������ [main.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <windows.h>
#include <stdio.h>
#include "d3dx9.h"
#include "xaudio2.h"

#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"

//=============================================================================
// ���C�u�����̃����N
//=============================================================================
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

typedef enum
{//���
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_TUTORIAL0,
	MODE_GAME,
	MODE_RESULT,
	MODE_END,
	MODE_RANKING,
	MODE_MAX
} MODE;
//=============================================================================
// �}�N����`
//=============================================================================
#define SCREEN_WIDTH	(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̍���

// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// 3�c�|���S�����_�t�H�[�}�b�g
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE|D3DFVF_TEX1)
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;
	D3DXVECTOR3 move;	// 
} VERTEX_3D;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#ifdef _DEBUG
void DrawFPS(void);
#endif
#endif