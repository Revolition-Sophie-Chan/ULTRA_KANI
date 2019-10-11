//=============================================================================
//
// �A�C�e������ [Item.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "Item.h"
#include "main.h"
#include "Camera.h"
#include "effect.h"
#include "player.h"
#include "score.h"


//=============================================================================
// �}�N����`
//=============================================================================
#define ITEMWIDTH	(30)	//�e�N�X�`���̕�
#define ITEMHEIGHT	(50)	//�e�N�X�`���̍���
#define ITEM_X		(30)	//�e�N�X�`���̕�
#define ITEM_Y		(50)	//�e�N�X�`���̍���
#define HITSIZE_X	(50)
#define HITSIZE_Y	(50)
#define ITEMCOUNT	(20)
#define MAX_P	(11)//�v���C���[�̃p�[�c��

//=============================================================================
// �\���̒�`
//=============================================================================
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
ITEM g_aItem;

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	int nCntItem;

	// �A�C�e���̏��̏�����
		g_aItem.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem.bUse = false;
		g_aItem.bItem = false;
		g_aItem.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aItem.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/chikuwa.png", &g_pTextureItem);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem<MAX_ITEM; nCntItem++)
	{//���W�ݒ�
	 //�A�j���[�V�����̍X�V

		pVtx[0].pos = D3DXVECTOR3(-25.0f, 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(25.0f, 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-25.0f, -25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(25.0f, -25.0f, 0.0f);


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

	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{


	VERTEX_3D *pVtx;

	PLAYER * pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//g_aItem[1].pos += g_aItem[1].move.y;
	for (int nCountPlayer = 0; nCountPlayer < MAX_P; nCountPlayer++)
	{
		if (g_aItem.bUse == true)
		{
			if (pPlayer[nCountPlayer].pos.x + HITSIZE_X / 2 >= g_aItem.pos.x &&
				pPlayer[nCountPlayer].pos.x - HITSIZE_X / 2 <= g_aItem.pos.x &&
				pPlayer[nCountPlayer].pos.z + HITSIZE_Y / 2 >= g_aItem.pos.z &&
				pPlayer[nCountPlayer].pos.z - HITSIZE_Y / 2 <= g_aItem.pos.z)
			{
				g_aItem.bUse = false;
				g_aItem.bItem = true;	//�A�C�e���擾
				if (g_aItem.bUse == false)
				{
					MakeEffect_Item();
				}
				for (int nCnt = 0; nCnt < ITEMCOUNT; nCnt++)
				{
					// 0�`3.14���o�� * (0 or 1)* -1�Ő��������߂�(�o���͈�)
					//fAngle = (rand() % 628 / 100.0f) * (rand() % 2) * -1;	// �S�����o��

					// �����ʒu
					D3DXVECTOR3 pos = D3DXVECTOR3(g_aItem.pos.x, g_aItem.pos.y, g_aItem.pos.z);
				}
				//break;
				// �������N����
				// �������N����


			}
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�f�[�^���A�����b�N����
			g_pVtxBuffItem->Unlock();
		}
	}


}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �|���S���̕`��

	if (g_aItem.bUse == true)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aItem.mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &g_aItem.mtxView);

		g_aItem.mtxWorld._11 = g_aItem.mtxView._11;
		g_aItem.mtxWorld._12 = g_aItem.mtxView._21;
		g_aItem.mtxWorld._13 = g_aItem.mtxView._31;
		g_aItem.mtxWorld._21 = g_aItem.mtxView._12;
		g_aItem.mtxWorld._22 = g_aItem.mtxView._22;
		g_aItem.mtxWorld._23 = g_aItem.mtxView._32;
		g_aItem.mtxWorld._31 = g_aItem.mtxView._13;
		g_aItem.mtxWorld._32 = g_aItem.mtxView._23;
		g_aItem.mtxWorld._33 = g_aItem.mtxView._33;


		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aItem.pos.x, g_aItem.pos.y, g_aItem.pos.z);
		D3DXMatrixMultiply(&g_aItem.mtxWorld, &g_aItem.mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aItem.mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureItem);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
		if (g_aItem.bUse == false)	//���g�p
		{
			g_aItem.pos = pos;
			g_aItem.col = col;;

			//���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(-25.0f, 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(25.0f, 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-25.0f, -25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(25.0f, -25.0f, 0.0f);

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

			g_aItem.bUse = true;
		//pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffItem->Unlock();
}
//=============================================================================
// �A�C�e���̎擾
//=============================================================================
ITEM *GetItem(void)
{
	return &g_aItem;
}
//=======================================================================================
// �p�[�e�B�N���֐�
//=======================================================================================
void MakeEffect_Item(void)
{
	int nCntItem = 0;
	//////////////////// �����̐ݒ� ////////////////////
	D3DXCOLOR col	= D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	float fRadius	= 20.0f;
	float fAngle	= 0.0f;
	float fSpeed	= 15.0f;
	int nLife		= 20;
	////////////////////////////////////////////////////
	for (int nCnt = 0; nCnt < 60; nCnt++)
	{
		// 0�`3.14���o�� * (0 or 1)* -1�Ő��������߂�(�o���͈�)
		fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;	// �S�����o��

																				// �����ʒu
		D3DXVECTOR3 pos1 = D3DXVECTOR3(g_aItem.pos.x, g_aItem.pos.y, g_aItem.pos.z);

		// �o������
		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed, 0.0f);
		D3DXVECTOR3 move1 = D3DXVECTOR3(sinf(fAngle)*fSpeed, 0.0f, cosf(fAngle)*fSpeed);
		D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed);

		// �G�t�F�N�g�̐ݒ�
		SetEffect(pos1, move, fRadius, nLife, col, 0);
		SetEffect(pos1, move1, fRadius, nLife, col, 0);
		SetEffect(pos1, move2, fRadius, nLife, col, 0);
	}
}