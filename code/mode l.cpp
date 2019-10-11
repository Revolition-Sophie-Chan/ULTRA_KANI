//=============================================================================
//
// ���f������ [model.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "Player.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POLYGON_SPD (2)
#define ROLL_SPD (0.2f)
#define PLAYER_SIZE (100.0f)
#define LOAD_MODEL	(1)		//�ǂݍ��ރe�N�X�`���^�C�v�̃J�Y
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXBUFFER	 g_pBuffMatModel = NULL;
LPD3DXMESH		 g_pMeshModel = {};
DWORD			 g_nNumMatModel = 0;
MODEL			 g_Model[MAX_MODEL];

//int g_nIdxShadow; //�e��ID
//X�t�@�C������ő�l�ƍŏ��l�̎擾
D3DXVECTOR3 g_vtxMaxModel;		//�ő�l
D3DXVECTOR3 g_vtxMinModel;		//�ŏ��l

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		// �ʒu�E�����̏����ݒ�
		g_Model[nCntmodel].pos		 = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		g_Model[nCntmodel].rot		 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntmodel].scale	 = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Model[nCntmodel].Diffrot	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntmodel].bUse		 = false;


		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			"Data/Model/bill3.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Model[nCntmodel].aModel[0].pBuffMatModel,
			NULL,
			&g_Model[nCntmodel].aModel[0].nNumMatModel,
			&g_Model[nCntmodel].aModel[0].pMeshModel);


		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"Data/Texture/field000.jpg",//nendoSophie.png//olga_face.jpg
			&g_Model[nCntmodel].aModel[0].pTextureModel);

		//X�t�@�C������ő�l�ƍŏ��l�̐ݒ�
		int nNumVertices;		 //���_��
		DWORD sizeFVF;			 //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVertexBuffer;	 //���_�o�b�t�@�̃|�C���^


		g_Model[nCntmodel].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Model[nCntmodel].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

		//���_�����擾
		nNumVertices = g_Model[nCntmodel].aModel[0].pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Model[nCntmodel].aModel[0].pMeshModel->GetFVF());

		//���_�o�b�t�@�����b�N
		g_Model[nCntmodel].aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{

			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//���ׂĂ̒��_�����r���čŏ��E�ő�𔲂��o��
			if (g_Model[nCntmodel].vtxMin.x > vtx.x)
			{
				g_Model[nCntmodel].vtxMin.x = vtx.x;
			}
			if (g_Model[nCntmodel].vtxMin.y > vtx.y)
			{
				g_Model[nCntmodel].vtxMin.y = vtx.y;
			}
			if (g_Model[nCntmodel].vtxMin.z > vtx.z)
			{
				g_Model[nCntmodel].vtxMin.z = vtx.z;
			}
			if (g_Model[nCntmodel].vtxMax.x < vtx.x)
			{
				g_Model[nCntmodel].vtxMax.x = vtx.x;
			}
			if (g_Model[nCntmodel].vtxMax.y < vtx.y)
			{
				g_Model[nCntmodel].vtxMax.y = vtx.y;
			}
			if (g_Model[nCntmodel].vtxMax.z < vtx.z)
			{
				g_Model[nCntmodel].vtxMax.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_Model[nCntmodel].aModel[0].pMeshModel->UnlockVertexBuffer();
	}
	//SetModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
}

	//g_Model[nCntmodel].nIdShadow = SetShadow(g_Model[nCntmodel].pos, g_Model[nCntmodel].rot);

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < LOAD_MODEL; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_Model[nCntTex].aModel[0].pTextureModel != NULL)
		{
			g_Model[nCntTex].aModel[0].pTextureModel->Release();
			g_Model[nCntTex].aModel[0].pTextureModel = NULL;
		}
	}
	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		// ���b�V���̊J��
		if (g_Model[nCntmodel].aModel[0].pMeshModel != NULL)
		{
			g_Model[nCntmodel].aModel[0].pMeshModel->Release();
			g_Model[nCntmodel].aModel[0].pMeshModel = NULL;
		}

		// �}�e���A���̊J��
		if (g_pBuffMatModel != NULL)
		{
			g_pBuffMatModel->Release();
			g_pBuffMatModel = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9	 pDevice = GetDevice();
	D3DXMATRIX			 mtxSize, mtxRot, mtxTrans;
	D3DXMATERIAL		 *pMat;
	D3DMATERIAL9		 matDef;

	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		if (g_Model[nCntmodel].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Model[nCntmodel].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxSize, g_Model[nCntmodel].scale.x, g_Model[nCntmodel].scale.y, g_Model[nCntmodel].scale.z);
			D3DXMatrixMultiply(&g_Model[nCntmodel].mtxWorld, &g_Model[nCntmodel].mtxWorld, &mtxSize);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCntmodel].rot.y, g_Model[nCntmodel].rot.x, g_Model[nCntmodel].rot.z);
			D3DXMatrixMultiply(&g_Model[nCntmodel].mtxWorld, &g_Model[nCntmodel].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Model[nCntmodel].pos.x, g_Model[nCntmodel].pos.y, g_Model[nCntmodel].pos.z);
			D3DXMatrixMultiply(&g_Model[nCntmodel].mtxWorld, &g_Model[nCntmodel].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntmodel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Model[nCntmodel].aModel[nCntmodel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Model[nCntmodel].aModel[nCntmodel].pTextureModel);
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �`��
				g_Model[nCntmodel].aModel[nCntmodel].pMeshModel->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}

	}
}
//=============================================================================
// �����蔻��
//=============================================================================
void CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		if (pPos->x > g_Model[nCntmodel].vtxMin.x + g_Model[nCntmodel].pos.x&&
			pPos->x < g_Model[nCntmodel].vtxMax.x + g_Model[nCntmodel].pos.x)//�u���b�N�͈͓̔�
		{

			//����
			if (pPosOld->z >= g_Model[nCntmodel].vtxMax.z + g_Model[nCntmodel].pos.z&&
				pPos->z < g_Model[nCntmodel].vtxMax.z + g_Model[nCntmodel].pos.z)
			{
				pPos->z = g_Model[nCntmodel].vtxMax.z + g_Model[nCntmodel].pos.z;
				//SetFade(MODE_RESULT);
			}
			//��O�̓����蔻��
			else if (pPosOld->z <= g_Model[nCntmodel].vtxMin.z + g_Model[nCntmodel].pos.z &&
				pPos->z > g_Model[nCntmodel].vtxMin.z + g_Model[nCntmodel].pos.z)
			{
				pPos->z = g_Model[nCntmodel].vtxMin.z + g_Model[nCntmodel].pos.z;
				//SetFade(MODE_RESULT);
			}
		}
		//���E�̓����蔻��
		if (pPos->z > g_Model[nCntmodel].vtxMin.z + g_Model[nCntmodel].pos.z&&
			pPos->z < g_Model[nCntmodel].vtxMax.z + g_Model[nCntmodel].pos.z)//�u���b�N�͈͓̔�
		{

			//�E����
			if (pPosOld->x >= g_Model[nCntmodel].vtxMax.x + g_Model[nCntmodel].pos.x &&
				pPos->x < g_Model[nCntmodel].vtxMax.x + g_Model[nCntmodel].pos.x)
			{
				pPos->x = g_Model[nCntmodel].vtxMax.x + g_Model[nCntmodel].pos.x;
				//SetFade(MODE_RESULT);
			}

			//�E����
			else if (pPosOld->x <= g_Model[nCntmodel].vtxMin.x + g_Model[nCntmodel].pos.x &&
				pPos->x > g_Model[nCntmodel].vtxMin.x + g_Model[nCntmodel].pos.x)
			{
				pPos->x = g_Model[nCntmodel].vtxMin.x + g_Model[nCntmodel].pos.x;
			}
		}
	}

}
//=============================================================================
// ���f���̐ݒ�
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType)
{
	for (int nCntmodel = 0; nCntmodel < MAX_MODEL; nCntmodel++)
	{
		if (g_Model[nCntmodel].bUse == false)
		{
			g_Model[nCntmodel].pos = pos;
			g_Model[nCntmodel].move = move;
			g_Model[nCntmodel].rot = rot;
			g_Model[nCntmodel].scale = scale;
			g_Model[nCntmodel].bUse = true;
			g_Model[nCntmodel].nType = nType;
			break;
		}
	}
}