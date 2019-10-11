//=============================================================================
//
// �I���̏���[End.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
//�C���N���[�h�t�@�C��
#include"main.h"
#include"Player.h"
#include"input.h"
#include"fade.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "sound.h"
#include "title.h"
#include "sound.h"
#include "effect.h"
#include "text.h"
//#include "joystick.h"

//#include"End.h"

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
//VERTEX_2D g_aVertex[4];
LPDIRECT3DTEXTURE9 g_pTextureEnd = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnd = NULL;//���_�o�b�t�@�ւ̃|�C���^
//int g_nCounterTitleFade;
//=============================================================================
// �|���S���̏�����
//=============================================================================
void InitEnd(void)
{

	InitCamera();
	InitPlayer();

	// �J�����̏I������
	InitCamera();

	// ���C�g�̏I������
	InitLight();

	// 3D�|���S���̏I������
	InitMeshField();

	InitEffect();

	InitMoji();


	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/game_over.png",
		&g_pTextureEnd);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnd,
		NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
					//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffEnd->Lock(0, 0, (void**)&pVtx, 0);
	//���_�̐ݒ�	

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 720, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280, 720, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	////�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffEnd->Unlock();
	
	SetText(D3DXVECTOR3(630.0f, 600.0f, 000.0f), 130, 30, 0);
}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void UninitEnd(void)
{
	//UninitSound();
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// 3D�|���S���̏I������
	UninitMeshField();

	UninitEffect();

	UninitMoji();

}
//=============================================================================
// polygon�X�V����
//=============================================================================
void UpdateEnd(void)
{

	// �J�����̏I������
	UpdateCamera();

	// ���C�g�̏I������
	UpdateLight();

	// 3D�|���S���̏I������
	UpdateMeshField();

	UpdateEffect();

	UpdateMoji();
	//g_nCounterTitleFade++;
	//if (g_nCounterTitleFade >= 120)
	//{
	//	SetFade(MODE_TITLE);
	//	g_nCounterTitleFade = 0;
	//}
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(MODE_TITLE);
	}
}
//=============================================================================
// �|���S���`��
//=============================================================================
void DrawEnd(void)
{
	SetCamera();
	// 3D�|���S���̏I������
	DrawMeshField();

	DrawEffect();

	DrawMoji();

	LPDIRECT3DDEVICE9 pDevice;
	////�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓��ꂩ��
	//g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, g_pTextureEnd);
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[�g�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffEnd, 0, sizeof(VERTEX_2D));
	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}