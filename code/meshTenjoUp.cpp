//=============================================================================
//
// �g�i������j���� [MeshTenjoUp.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "MeshTenjoUp.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define X_CHOTEN (3);
#define Y_CHOTEN (3);
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshTenjoUp(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshTenjoUp = NULL;	//Direct3D�f�o�C�X�̃|�C���^
D3DXVECTOR3 g_posMeshTenjoUp;
D3DXVECTOR3 g_rotMeshTenjoUp;	//�|���S���̌���

LPDIRECT3DTEXTURE9 g_pTextureMeshTenjoUp = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshTenjoUp = NULL;
D3DXMATRIX g_mtxWorldMeshTenjoUp;//���[���h�}�g���b�N�X
int nCntUmiUp;
//=============================================================================
// ����������
//=============================================================================
void InitMeshTenjoUp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/suimen.png",
		&g_pTextureMeshTenjoUp);

	// �ʒu�E��]�̏����ݒ�
	g_posMeshTenjoUp = D3DXVECTOR3(0.0f, 310.0f, 0.0f);
	g_rotMeshTenjoUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	nCntUmiUp = 0;

	// ���_���̍쐬
	MakeVertexMeshTenjoUp(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshTenjoUp(void)
{

	//�e�N�X�`���̊J��
	if (g_pTextureMeshTenjoUp != NULL)
	{
		g_pTextureMeshTenjoUp->Release();
		g_pTextureMeshTenjoUp = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshTenjoUp != NULL)
	{
		g_pVtxBuffMeshTenjoUp->Release();
		g_pVtxBuffMeshTenjoUp = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshTenjoUp != NULL)
	{
		g_pIdxBuffMeshTenjoUp->Release();
		g_pIdxBuffMeshTenjoUp = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshTenjoUp(void)
{

	nCntUmiUp++;
	if (nCntUmiUp <= 100)
	{
		g_posMeshTenjoUp.y -= sinf(0.35f);
	}
	if (nCntUmiUp >= 100)
	{
		g_posMeshTenjoUp.y += sinf(0.35f);
	}

	if (nCntUmiUp >= 200)
	{
		nCntUmiUp = 0;
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshTenjoUp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	
	D3DXMATRIX mtxRot,mtxTrans;//�v�Z�p�}�g���b�N�X


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshTenjoUp);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshTenjoUp.y, g_rotMeshTenjoUp.x, g_rotMeshTenjoUp.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTenjoUp, &g_mtxWorldMeshTenjoUp, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshTenjoUp.x, g_posMeshTenjoUp.y, g_posMeshTenjoUp.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTenjoUp, &g_mtxWorldMeshTenjoUp, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshTenjoUp);


	pDevice->SetTexture(0, g_pTextureMeshTenjoUp);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshTenjoUp, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X
	pDevice->SetIndices(g_pIdxBuffMeshTenjoUp);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//�|���S���`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);


	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshTenjoUp(LPDIRECT3DDEVICE9 pDevice)
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
		&g_pIdxBuffMeshTenjoUp,
		NULL);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshTenjoUp,
		NULL);

	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeshTenjoUp->Lock(0, 0, (void**)&pVtx, 0);
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
			//pVtx[0].tex = D3DXVECTOR2(-1.0f, 1.0f);
			//pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(-1.0f, 0.0f);
			//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
			//pVtx[6].tex = D3DXVECTOR2(-1.0f, -1.0f);
			//pVtx[7].tex = D3DXVECTOR2(0.0f, -1.0f);
			//pVtx[8].tex = D3DXVECTOR2(1.0f, -1.0f);

			//�@���x�N�g��
			pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(3.14f/2, 0.0f, 0.0f);
			//�J���[
			pVtx[nCntX + nCntY * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f);
		}
	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffMeshTenjoUp->Unlock();
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pIdxBuffMeshTenjoUp->Lock(0, 0, (void**)&pIdx, 0);

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
	//pIdx[0] = 3;
	//pIdx[1] = 0;

	//pIdx[2] = 4;
	//pIdx[3] = 1;

	//pIdx[4] = 5;
	//pIdx[5] = 2;

	//pIdx[6] = 2;
	//pIdx[7] = 6;

	//pIdx[8] = 6;
	//pIdx[9] = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;

	//���_�f�[�^�̃A�����b�N
	g_pIdxBuffMeshTenjoUp->Unlock();
}

