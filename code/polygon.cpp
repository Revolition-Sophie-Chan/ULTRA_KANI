//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "polygon.h"

//=============================================================================
// �}�N����`
//=============================================================================


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//Direct3D�f�o�C�X�̃|�C���^
D3DXVECTOR3 g_posPolygon;
D3DXVECTOR3 g_rotPolygon;	//�|���S���̌���

LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;//�e�N�X�`���ւ̃|�C���^

D3DXMATRIX g_mtxWorldPolygon;//���[���h�}�g���b�N�X
//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/gyosen.png",//nendoSophie.png//olga_face.jpg
		&g_pTexturePolygon);

	// �ʒu�E��]�̏����ݒ�
	g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_���̍쐬
	MakeVertexPolygon(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{

	//�e�N�X�`���̊J��
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	
	D3DXMATRIX mtxRot,mtxTrans;//�v�Z�p�}�g���b�N�X


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);


	pDevice->SetTexture(0, g_pTexturePolygon);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	pVtx[4].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	pVtx[6].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	pVtx[7].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	pVtx[8].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	pVtx[9].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	pVtx[11].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[12].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);



	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 1.0f);
		//��[13�_�f�[�^�̃A�����b�N
	g_pVtxBuffPolygon->Unlock();
}

