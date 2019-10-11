//=============================================================================
//
// �ԏ��� [ami.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "ami.h"
#include "main.h"
#include "Camera.h"
#include "effect.h"
#include "nakama.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define AMIWIDTH	(30)	//�e�N�X�`���̕�
#define AMHEIGHT	(50)	//�e�N�X�`���̍���
#define AMI_X	(30)	//�e�N�X�`���̕�
#define AMI_Y	(50)	//�e�N�X�`���̍���
#define SPEED	(0.5f)	//�e�N�X�`���̍���

//=============================================================================
// �\���̒�`
//=============================================================================
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureami = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffami = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
AMI g_aami;

//=============================================================================
// ����������
//=============================================================================
void Initami(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	// �A�C�e���̏��̏�����

		g_aami.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.bUse = false;
		g_aami.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aami.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aami.fAngle = 0.0f;
		g_aami.fLength = 0.0f;


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/ami.png", &g_pTextureami);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_AMI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffami,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffami->Lock(0, 0, (void**)&pVtx, 0);
//���W�ݒ�
	 //�A�j���[�V�����̍X�V

		pVtx[0].pos = D3DXVECTOR3(-155.0f, 155.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(155.0f, 155.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-155.0f, -155.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(155.0f, -155.0f, 0.0f);


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
		//pVtx += 4;

	
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffami->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void Uninitami(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureami != NULL)
	{
		g_pTextureami->Release();
		g_pTextureami = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffami != NULL)
	{
		g_pVtxBuffami->Release();
		g_pVtxBuffami = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Updateami(void)
{

	NAKAMA * pNakama;
	//�v���C���[�̎擾
	pNakama = Getnakama();

	VERTEX_3D *pVtx;
	int nCntami;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffami->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntami = 0; nCntami < MAX_AMI; nCntami++)
	{
		g_aami.pos += g_aami.move;
		if (pNakama->bUse == true)
		{
			Setami(D3DXVECTOR3(pNakama->pos.x, 80.0f, pNakama->pos.z), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.3f, 0.0f), D3DXVECTOR3(0.0f, SPEED, 0.0f));
		}
		else if (pNakama->bUse == false)
		{
			g_aami.bUse = false;
		}
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffami->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void Drawami(void)
{
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �|���S���̕`��
		if (g_aami.bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aami.mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &g_aami.mtxView);

			g_aami.mtxWorld._11 = g_aami.mtxView._11;
			g_aami.mtxWorld._12 = g_aami.mtxView._21;
			g_aami.mtxWorld._13 = g_aami.mtxView._31;
			g_aami.mtxWorld._21 = g_aami.mtxView._12;
			g_aami.mtxWorld._22 = g_aami.mtxView._22;
			g_aami.mtxWorld._23 = g_aami.mtxView._32;
			g_aami.mtxWorld._31 = g_aami.mtxView._13;
			g_aami.mtxWorld._32 = g_aami.mtxView._23;
			g_aami.mtxWorld._33 = g_aami.mtxView._33;

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aami.rot.y, g_aami.rot.x, g_aami.rot.z);
			D3DXMatrixMultiply(&g_aami.mtxWorld, &g_aami.mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aami.pos.x, g_aami.pos.y, g_aami.pos.z);
			D3DXMatrixMultiply(&g_aami.mtxWorld, &g_aami.mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aami.mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffami, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureami);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
}

//=============================================================================
// �Ԃ̐ݒ�
//=============================================================================
void Setami(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot,D3DXVECTOR3 move)
{

	NAKAMA * pnakama;
	//�v���C���[�̎擾
	pnakama = Getnakama();

	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffami->Lock(0, 0, (void**)&pVtx, 0);


		if (g_aami.bUse == false)	//���g�p
		{
			g_aami.pos = pos;
			g_aami.col = col;
			g_aami.rot = rot;
			g_aami.move = move;

			//���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(-155.0f, 155.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(155.0f, 155.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-155.0f, -155.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(155.0f, -155.0f, 0.0f);

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


			g_aami.bUse = true;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffami->Unlock();
}
//=============================================================================
// �Ԃ̎擾
//=============================================================================
AMI *Getami(void)
{
	return &g_aami;
}

