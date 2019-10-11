//=============================================================================
//
// �������� [explosion.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "explosion.h"
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_EXPLOSION (58)	// �����̍ő吔
#define TEXWIDTH	(40)	//�e�N�X�`���̕�
#define TEXHEIGHT	(40)	//�e�N�X�`���̍���
#define POLYGON_SPD	(15.0f)	//�ړ����x
#define POLYGON_X	(500)	//���_��X���W
#define POLYGON_Y	(380)	//���_��Y���W

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
EXPLOSION g_aExplosion;

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	// �����̏��̏�����

	g_aExplosion.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aExplosion.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aExplosion.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aExplosion.nCounterAnim = 0;
	g_aExplosion.nPattenAnim = 0;
	g_aExplosion.bUse = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/bakuhatsu.png", &g_pTextureExplosion);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	{//���W�ݒ�
	 //�A�j���[�V�����̍X�V

		pVtx[0].pos = D3DXVECTOR3(-250.0f, 250.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(250.0f, 250.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-250.0f, -250.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(250.0f, -250.0f, 0.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);



	if (g_aExplosion.bUse == true)	//�����g�p
	{
		g_aExplosion.nCounterAnim++;
		if (g_aExplosion.nCounterAnim % 7 == 0)
		{
			g_aExplosion.nPattenAnim = (g_aExplosion.nPattenAnim + 1) % 9;

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f + g_aExplosion.nPattenAnim*0.1428f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1428f + g_aExplosion.nPattenAnim*0.1428f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_aExplosion.nPattenAnim*0.1428f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1428f + g_aExplosion.nPattenAnim*0.1428f, 1.0f);

			if (g_aExplosion.nPattenAnim >= 8)
			{
				g_aExplosion.bUse = false;
			}
		}
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// �|���S���̕`��
	if (g_aExplosion.bUse == true)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aExplosion.mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &g_aExplosion.mtxView);

		g_aExplosion.mtxWorld._11 = g_aExplosion.mtxView._11;
		g_aExplosion.mtxWorld._12 = g_aExplosion.mtxView._21;
		g_aExplosion.mtxWorld._13 = g_aExplosion.mtxView._31;
		g_aExplosion.mtxWorld._21 = g_aExplosion.mtxView._12;
		g_aExplosion.mtxWorld._22 = g_aExplosion.mtxView._22;
		g_aExplosion.mtxWorld._23 = g_aExplosion.mtxView._32;
		g_aExplosion.mtxWorld._31 = g_aExplosion.mtxView._13;
		g_aExplosion.mtxWorld._32 = g_aExplosion.mtxView._23;
		g_aExplosion.mtxWorld._33 = g_aExplosion.mtxView._33;

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aExplosion.rot.y, g_aExplosion.rot.x, g_aExplosion.rot.z);
		D3DXMatrixMultiply(&g_aExplosion.mtxWorld, &g_aExplosion.mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion.pos.x, g_aExplosion.pos.y, g_aExplosion.pos.z);
		D3DXMatrixMultiply(&g_aExplosion.mtxWorld, &g_aExplosion.mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion.mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureExplosion);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//=============================================================================
// �����̐ݒ�
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot)
{

	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aExplosion.bUse == false)	//���g�p
	{
		g_aExplosion.pos = pos;
		g_aExplosion.col = col;
		g_aExplosion.rot = rot;
		g_aExplosion.nCounterAnim = 0;
		g_aExplosion.nPattenAnim = 0;

		pVtx[0].pos = D3DXVECTOR3(-250.0f, 250.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(250.0f, 250.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-250.0f, -250.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(250.0f, -250.0f, 0.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_aExplosion.bUse = true;

	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}