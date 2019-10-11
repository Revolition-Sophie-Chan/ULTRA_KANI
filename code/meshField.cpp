//=============================================================================
//
// �|���S������ [MeshField.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "MeshField.h"
#include "effect.h"
#include "input.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define X_CHOTEN (3);
#define Y_CHOTEN (3);
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	//Direct3D�f�o�C�X�̃|�C���^
D3DXVECTOR3 g_posMeshField;
D3DXVECTOR3 g_rotMeshField;	//�|���S���̌���

LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
D3DXMATRIX g_mtxWorldMeshField;//���[���h�}�g���b�N�X

int nCount;
//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/suna.png",
		&g_pTextureMeshField);

	// �ʒu�E��]�̏����ݒ�
	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	nCount = 0;

	// ���_���̍쐬
	MakeVertexMeshField(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{

	//�e�N�X�`���̊J��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
	nCount++;
	if (nCount >= 5)
	{
		MakeEffect_Field();//�G�t�F�N�g�𐶐�
		nCount = 0;
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	
	D3DXMATRIX mtxRot,mtxTrans;//�v�Z�p�}�g���b�N�X


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);


	pDevice->SetTexture(0, g_pTextureMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
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
		&g_pIdxBuffMeshField,
		NULL);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	for (nCntY = 0; nCntY < 3; nCntY++)
	{
		for (nCntX = 0; nCntX < 3; nCntX++)
		{
			//���_�o�b�t�@
			pVtx[nCntX + nCntY * 3].pos.x = nCntX *3000.0f - 3000.0f;
			pVtx[nCntX + nCntY * 3].pos.y = 0.0f;
			pVtx[nCntX + nCntY * 3].pos.z = nCntY *-3000.0f + 3000.0f;

			//�e�N�X�`��
			pVtx[nCntX + nCntY * 3].tex.x = nCntX *1.0f - 1.0f;
			pVtx[nCntX + nCntY * 3].tex.y = nCntY *-1.0f + 1.0f;

			//�@���x�N�g��
			pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//�J���[
			pVtx[nCntX + nCntY * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffMeshField->Unlock();
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeEffect_Field(void)
{
	int nCntItem = 0;
	//////////////////// �����̐ݒ� ////////////////////
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	float fRadius = 20.0f;
	float fAngle = 0.0f;
	float fSpeed = 15.0f;
	int nLife = 20;
	////////////////////////////////////////////////////

		// 0�`3.14���o�� * (0 or 1)* -1�Ő��������߂�(�o���͈�)
	fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;	// �S�����o��

																			// �����ʒu
	D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 4000 - 2000.0f, 0.0f, rand() % 4000 - 2000.0f);
	// �o������
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 10.0, 0.0f);


	// �G�t�F�N�g�̐ݒ�
	SetEffect(pos, move, fRadius, nLife, col, 2);

}