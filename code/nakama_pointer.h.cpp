//=============================================================================
//
// ���ԃ|�C���^�[���� [nakama_pointer.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "nakama_pointer.h"
#include "main.h"
#include "Camera.h"
#include "effect.h"
#include "player.h"
#include "nakama.h"
#include "ami.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POINTERWIDTH	(50)	//�e�N�X�`���̕�
#define POINTERHEIGHT	(50)	//�e�N�X�`���̍���
#define POINTER_X		(30)	//�e�N�X�`���̕�
#define POINTER_Y		(50)	//�e�N�X�`���̍���
#define HITSIZE_X	(50)
#define HITSIZE_Y	(50)
#define POINTERCOUNT	(20)
#define MAX_TEXTURE	(3)
#define	TEXTURE_NAKAMA0		"Data/Texture/Help_down.png"	//�w���v�A�C�R��
#define	TEXTURE_NAKAMA1		"Data/Texture/Help_left.png.png"		//�������w���v
#define	TEXTURE_NAKAMA2		"Data/Texture/Help_right.png.png"	//�E�����w���v
#define SPEED	(0.5f)	//�e�N�X�`���̍���
#define POINTSET_Y (85)	//���f���̏�Ƀ|�C���^�[��u��

//=============================================================================
// �\���̒�`
//=============================================================================
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePointer = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPointer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
POINTER g_aPointer;

D3DXVECTOR3 g_vtxMaxPointer;		//�ő�l
D3DXVECTOR3 g_vtxMinPointer;		//�ŏ��l
int g_nCounterPointer;								//�A�j���[�V�����J�E���^�[
int g_nPattenPointer;									//�A�j���[�V�����p�^�[��


//=============================================================================
// ����������
//=============================================================================
void InitPointer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	g_nCounterPointer=0;								//�A�j���[�V�����J�E���^�[
	g_nPattenPointer =0;									//�A�j���[�V�����p�^�[��


	// �A�C�e���̏��̏�����

		g_aPointer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPointer.bUse = false;
		g_aPointer.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPointer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPointer.nType = 0;


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAKAMA0,
		&g_pTexturePointer);


	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPointer,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPointer->Lock(0, 0, (void**)&pVtx, 0);

//���W�ݒ�
	 //�A�j���[�V�����̍X�V

		pVtx[0].pos = D3DXVECTOR3(-POINTERWIDTH, POINTERWIDTH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(POINTERWIDTH, POINTERWIDTH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-POINTERWIDTH, -POINTERWIDTH, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(POINTERWIDTH, -POINTERWIDTH, 0.0f);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);


		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPointer->Unlock();
	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPointer(void)
{

	// �e�N�X�`���̊J��
	if (g_pTexturePointer != NULL)
	{
		g_pTexturePointer->Release();
		g_pTexturePointer = NULL;
	}


	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPointer != NULL)
	{
		g_pVtxBuffPointer->Release();
		g_pVtxBuffPointer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePointer(void)
{

	NAKAMA * pNakama;
	//�v���C���[�̎擾
	pNakama = Getnakama();
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPointer->Lock(0, 0, (void**)&pVtx, 0);


	g_aPointer.pos += g_aPointer.move;
	if (pNakama->bUse == true)
	{
		g_aPointer.bUse = false;
		SetPointer(D3DXVECTOR3(pNakama->pos.x, pNakama->pos.y + POINTSET_Y, pNakama->pos.z), D3DXVECTOR3(0.0f, SPEED, 0.0f), 0);
	}
	else if (pNakama->bUse == false)
	{
		g_aPointer.bUse = false;
	}
	if (g_aPointer.nType == 0)
	{
		g_nCounterPointer++;
		if (g_nCounterPointer % 40 == 0)
		{
			g_nPattenPointer = (g_nPattenPointer + 1) % 2;
			if (g_nPattenPointer == 0)
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, 0);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, 0);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, 0);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, 0);
			}
			else
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);
			}
		}
		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffPointer->Unlock();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPointer(void)
{

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �|���S���̕`��
	if (g_aPointer.bUse == true)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aPointer.mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &g_aPointer.mtxView);

		g_aPointer.mtxWorld._11 = g_aPointer.mtxView._11;
		g_aPointer.mtxWorld._12 = g_aPointer.mtxView._21;
		g_aPointer.mtxWorld._13 = g_aPointer.mtxView._31;
		g_aPointer.mtxWorld._21 = g_aPointer.mtxView._12;
		g_aPointer.mtxWorld._22 = g_aPointer.mtxView._22;
		g_aPointer.mtxWorld._23 = g_aPointer.mtxView._32;
		g_aPointer.mtxWorld._31 = g_aPointer.mtxView._13;
		g_aPointer.mtxWorld._32 = g_aPointer.mtxView._23;
		g_aPointer.mtxWorld._33 = g_aPointer.mtxView._33;


		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aPointer.pos.x, g_aPointer.pos.y, g_aPointer.pos.z);
		D3DXMatrixMultiply(&g_aPointer.mtxWorld, &g_aPointer.mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aPointer.mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffPointer, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);


		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePointer);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ���ԃ|�C���^�[�̐ݒ�
//=============================================================================
void SetPointer(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	VERTEX_3D *pVtx;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPointer->Lock(0, 0, (void**)&pVtx, 0);


	if (g_aPointer.bUse == false)	//���g�p
	{
		g_aPointer.pos = pos;
		g_aPointer.move = move;
		g_aPointer.nType = nType;
		g_aPointer.bUse = true;

		pVtx[0].pos = D3DXVECTOR3(-POINTERWIDTH, POINTERWIDTH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(POINTERWIDTH, POINTERWIDTH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-POINTERWIDTH, -POINTERWIDTH, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(POINTERWIDTH, -POINTERWIDTH, 0.0f);

		//�A�j���[�V�����̍X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPointer->Unlock();
}
//=============================================================================
// ���ԃ|�C���^�[�̎擾
//=============================================================================
POINTER *GetPointer(void)
{
	return &g_aPointer;
}