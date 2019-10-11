//=============================================================================
//
// �w�i���� [Haikei.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "Haikei.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexHaikei(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHaikei = NULL;	//Direct3D�f�o�C�X�̃|�C���^
HAIKEI g_aHaikei[MAX_HAIKEI];
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffHaikei = NULL;

LPDIRECT3DTEXTURE9 g_pTextureHaikei = NULL;//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitHaikei(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/sora.png",//nendoSophie.png//olga_face.jpg
		&g_pTextureHaikei);

	for (nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall++)
	{
		g_aHaikei[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aHaikei[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aHaikei[nCntWall].bUse = false;
	}
	// ���_���̍쐬
	MakeVertexHaikei(pDevice);
	SetHaikei(D3DXVECTOR3(0.0f, -1000.0f, 4000.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetHaikei(D3DXVECTOR3(0.0f, -1000.0f, -4000.0f ),D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetHaikei(D3DXVECTOR3(4000.0f, -1000.0f, 0.0f),D3DXVECTOR3(0.0f, 3.14f / 2, 0.0f));
	SetHaikei(D3DXVECTOR3(-4000.0f, -1000.0f, 0.0f), D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitHaikei(void)
{
	int nCntWall;

	//�e�N�X�`���̊J��
	for (nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall++)
	{
		if (g_pTextureHaikei != NULL)
		{
			g_pTextureHaikei->Release();
			g_pTextureHaikei = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffHaikei != NULL)
	{
		g_pVtxBuffHaikei->Release();
		g_pVtxBuffHaikei = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHaikei(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHaikei(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾


	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

								//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (int nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall += 1)
	{
		if (g_aHaikei[nCntWall].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aHaikei[nCntWall].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aHaikei[nCntWall].rot.y, g_aHaikei[nCntWall].rot.x, g_aHaikei[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aHaikei[nCntWall].mtxWorld, &g_aHaikei[nCntWall].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aHaikei[nCntWall].pos.x, g_aHaikei[nCntWall].pos.y, g_aHaikei[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aHaikei[nCntWall].mtxWorld, &g_aHaikei[nCntWall].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aHaikei[nCntWall].mtxWorld);

			pDevice->SetTexture(0, g_pTextureHaikei);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffHaikei, 0, sizeof(VERTEX_3D));

			pDevice->SetIndices(g_pIdxBuffHaikei);

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
void MakeVertexHaikei(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntIdx = 0;
	int nCntY;
	int nCntX;
	WORD *pIdx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * MAX_HAIKEI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHaikei,
		NULL);

	//�|�C���^�擾
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * MAX_HAIKEI,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffHaikei,
		NULL);

	VERTEX_3D *pVtx;

	for (int nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall++)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffHaikei->Lock(0, 0, (void**)&pVtx, 0);


		pVtx += 9 * nCntWall;

		for (nCntY = 0; nCntY < 3; nCntY++)
		{
			for (nCntX = 0; nCntX < 3; nCntX++)
			{
				//���_�o�b�t�@
				//pVtx[nCntX + nCntY * 3].pos.x = nCntX *1000.0f - 1000.0f;
				//pVtx[nCntX + nCntY * 3].pos.y = nCntY *-90.0f + 180.0f;
				//pVtx[nCntX + nCntY * 3].pos.z = 0.0f;
				pVtx[nCntX + nCntY * 3].pos.x = nCntX *6000.0f - 6000.0f;
				pVtx[nCntX + nCntY * 3].pos.y = nCntY *-3000.0f + 3000.0f;
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
		g_pVtxBuffHaikei->Unlock();

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pIdxBuffHaikei->Lock(0, 0, (void**)&pIdx, 0);

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
		g_pIdxBuffHaikei->Unlock();

	}

}
//=============================================================================
// �ǂ̐ݒ�
//=============================================================================
void SetHaikei(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffHaikei->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWall = 0; nCntWall < MAX_HAIKEI; nCntWall++)
	{
		if (!g_aHaikei[nCntWall].bUse)
		{
			g_aHaikei[nCntWall].pos = pos;
			g_aHaikei[nCntWall].rot = rot;
			////���_���W�̐ݒ�
			g_aHaikei[nCntWall].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffHaikei->Unlock();
}
