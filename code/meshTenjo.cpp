//=============================================================================
//
// �g�i�������j���� [MeshTenjo.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "MeshTenjo.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define X_CHOTEN (3);
#define Y_CHOTEN (3);
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshTenjo(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshTenjo = NULL;	//Direct3D�f�o�C�X�̃|�C���^
D3DXVECTOR3 g_posMeshTenjo;
D3DXVECTOR3 g_rotMeshTenjo;	//�|���S���̌���

LPDIRECT3DTEXTURE9 g_pTextureMeshTenjo = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshTenjo = NULL;
D3DXMATRIX g_mtxWorldMeshTenjo;//���[���h�}�g���b�N�X
int nCntUmi;
//=============================================================================
// ����������
//=============================================================================
void InitMeshTenjo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/suimen.png",
		&g_pTextureMeshTenjo);

	// �ʒu�E��]�̏����ݒ�
	g_posMeshTenjo = D3DXVECTOR3(0.0f, 310.0f, 0.0f);
	g_rotMeshTenjo = D3DXVECTOR3(3.14f, 0.0f, 0.0f);
	nCntUmi=0;

	// ���_���̍쐬
	MakeVertexMeshTenjo(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshTenjo(void)
{

	//�e�N�X�`���̊J��
	if (g_pTextureMeshTenjo != NULL)
	{
		g_pTextureMeshTenjo->Release();
		g_pTextureMeshTenjo = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshTenjo != NULL)
	{
		g_pVtxBuffMeshTenjo->Release();
		g_pVtxBuffMeshTenjo = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshTenjo != NULL)
	{
		g_pIdxBuffMeshTenjo->Release();
		g_pIdxBuffMeshTenjo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshTenjo(void)
{

	nCntUmi++;
	if (nCntUmi <= 100)
	{
		g_posMeshTenjo.y -= sinf(0.55f);
	}
	if (nCntUmi >= 100)
	{
		g_posMeshTenjo.y += sinf(0.55f);
	}
	if (nCntUmi >= 200)
	{
		nCntUmi = 0;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshTenjo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXMATRIX mtxRot,mtxTrans;//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshTenjo);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshTenjo.y, g_rotMeshTenjo.x, g_rotMeshTenjo.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTenjo, &g_mtxWorldMeshTenjo, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshTenjo.x, g_posMeshTenjo.y, g_posMeshTenjo.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTenjo, &g_mtxWorldMeshTenjo, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshTenjo);


	pDevice->SetTexture(0, g_pTextureMeshTenjo);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshTenjo, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X
	pDevice->SetIndices(g_pIdxBuffMeshTenjo);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshTenjo(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntIdx=0;
	int nCntY;
	int nCntX;
	WORD *pIdx;

	//�|�C���^�擾
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshTenjo,
		NULL);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshTenjo,
		NULL);

	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeshTenjo->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	for (nCntY = 0; nCntY < 3; nCntY++)
	{
		for (nCntX = 0; nCntX < 3; nCntX++)
		{
			//���_�o�b�t�@
			pVtx[nCntX + nCntY * 3].pos.x = nCntX *4000.0f - 4000.0f;
			pVtx[nCntX + nCntY * 3].pos.y = 0.0f;
			pVtx[nCntX + nCntY * 3].pos.z = nCntY *-4000.0f + 4000.0f;

			//�e�N�X�`��
			pVtx[nCntX + nCntY * 3].tex.x = nCntX *1.0f - 1.0f;
			pVtx[nCntX + nCntY * 3].tex.y = nCntY *-1.0f + 1.0f;

			//�@���x�N�g��
			pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(3.14f, 1.0f, 0.0f);
			//�J���[
			pVtx[nCntX + nCntY * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f);
		}
	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffMeshTenjo->Unlock();
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pIdxBuffMeshTenjo->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCountY = 0; nCountY < 2; nCountY++)
	{
		//��C���f�b�N�X
		for (int nCountX = 0; nCountX < 3; nCountX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[nCntIdx] = (nCountY + 1) * 3 + nCountX;
			pIdx[nCntIdx + 1] = pIdx[nCntIdx] - 3;
			nCntIdx += 2;

			//�k�ޕ�
			if (nCountX == 2 && nCountY < 1)
			{
				pIdx[nCntIdx] = pIdx[nCntIdx - 1];
				pIdx[nCntIdx + 1] = pIdx[nCntIdx - 1] + 3 + 1;
				nCntIdx += 2;
			}
		}
	}
	//���_�f�[�^�̃A�����b�N
	g_pIdxBuffMeshTenjo->Unlock();
}

