//=============================================================================
//
// �Ǐ��� [meshWall.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "meshwall.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_MESHWALL	(4)	// �ő吔


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	//Direct3D�f�o�C�X�̃|�C���^
MESHWALL g_aMeshWall[MAX_MESHWALL];
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;

LPDIRECT3DTEXTURE9 g_pTextureMeshWall= NULL;//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitMeshWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/block002.jpg",
		&g_pTextureMeshWall);

	for (nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		g_aMeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].bUse = false;
	}
	// ���_���̍쐬
	MakeVertexMeshWall(pDevice);
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -3000.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(3000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 3.14f / 2, 0.0f));
	SetMeshWall(D3DXVECTOR3(-3000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
	int nCntWall;

	//�e�N�X�`���̊J��
	for (nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_pTextureMeshWall != NULL)
		{
			g_pTextureMeshWall->Release();
			g_pTextureMeshWall = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾


	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall += 1)
	{
		if (g_aMeshWall[nCntWall].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshWall[nCntWall].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntWall].rot.y, g_aMeshWall[nCntWall].rot.x, g_aMeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntWall].pos.x, g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntWall].mtxWorld);

			pDevice->SetTexture(0, g_pTextureMeshWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			pDevice->SetIndices(g_pIdxBuffMeshWall);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, nCntWall * 14, 12);
		}
	}

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntIdx = 0;
	int nCntY;
	int nCntX;
	WORD *pIdx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9* MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//�|�C���^�擾
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	VERTEX_3D *pVtx;

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);


		pVtx += 9 * nCntWall;

		for (nCntY = 0; nCntY < 3; nCntY++)
		{
			for (nCntX = 0; nCntX < 3; nCntX++)
			{
				//���_�o�b�t�@
				pVtx[nCntX + nCntY * 3].pos.x = nCntX *3000.0f - 3000.0f;
				pVtx[nCntX + nCntY * 3].pos.y = nCntY *-300.0f + 300.0f;
				pVtx[nCntX + nCntY * 3].pos.z = 0.0f;

				//�e�N�X�`��
				pVtx[nCntX + nCntY * 3].tex.x = nCntX *1.0f - 1.0f;
				pVtx[nCntX + nCntY * 3].tex.y = nCntY *-1.0f + 1.0f;

				//�@���x�N�g��
				//pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[nCntX + nCntY * 3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				//�J���[
				pVtx[nCntX + nCntY * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}


		//���_�f�[�^�̃A�����b�N
		g_pVtxBuffMeshWall->Unlock();

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

		//pIdx +=  14 * nCntWall;

		for (int nCountY = 0; nCountY < 2; nCountY++)
		{

			//��C���f�b�N�X
			for (int nCountX = 0; nCountX < 3; nCountX++)
			{
				//�C���f�b�N�X�̐ݒ�
				pIdx[nCntIdx] = (nCountY + 1) * 3 + nCountX + 9 * nCntWall;
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
		g_pIdxBuffMeshWall->Unlock();

	}

}
//=============================================================================
// �ǂ̐ݒ�
//=============================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (!g_aMeshWall[nCntWall].bUse)
		{
			g_aMeshWall[nCntWall].pos = pos;
			g_aMeshWall[nCntWall].rot = rot;
			////���_���W�̐ݒ�
			g_aMeshWall[nCntWall].bUse = true;
			break;
		}
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();
}
