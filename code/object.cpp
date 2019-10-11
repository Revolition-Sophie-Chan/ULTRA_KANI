//=============================================================================
//
// ��Q������ [Object.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "object.h"
#include "input.h"
#include "camera.h"
#include "effect.h"
#include "player.h"
#include "fade.h"
#include "game.h"
#include "explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define Object_01 "Data/Model/object/sango.x"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define Object_02 "Data/Model/object/rock.x"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define POLTGON0_TEX "Data/Texture/.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C����

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXMATRIX			 mtxWorldObject;
	LPD3DXMESH			 pMeshObject;
	LPD3DXBUFFER		 pBuffMatObject;
	LPDIRECT3DTEXTURE9	 pTextureObject;
	DWORD				 nNumMatObject;

} OBJECTRESOURCE;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
OBJECTRESOURCE		g_ObjectModel[OBJECTTYPE_MAX];
OBJECT				g_Object[MAX_OBJECT];
GAMESTATE g_gameStateObject = GAMESTATE_NONE;


//X�t�@�C������ő�l�ƍŏ��l�̎擾
D3DXVECTOR3 g_vtxMaxObject;		//�ő�l
D3DXVECTOR3 g_vtxMinObject;		//�ŏ��l

//=============================================================================
// ����������
//=============================================================================
void InitObject(void)
{
	int nCntObject;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// �ʒu�E�����̏����ݒ�
		g_Object[nCntObject].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_Object[nCntObject].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��ʒu
		g_Object[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Object[nCntObject].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].bUse = false;
		g_Object[nCntObject].nType = OBJECTTYPE_SANGO;
		//g_Object[nCntModel].hIdxShadow = SetShadow(g_Model[nCntModel].pos, g_Model[nCntModel].rot);
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		Object_01,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectModel[0].pBuffMatObject,
		NULL,
		&g_ObjectModel[0].nNumMatObject,
		&g_ObjectModel[0].pMeshObject);

	D3DXLoadMeshFromX(
		Object_02,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectModel[1].pBuffMatObject,
		NULL,
		&g_ObjectModel[1].nNumMatObject,
		&g_ObjectModel[1].pMeshObject);

	D3DXCreateTextureFromFile(
		pDevice,	//�擾
		POLTGON0_TEX,
		&g_ObjectModel[0].pTextureObject);


	//X�t�@�C������ő�l�ƍŏ��l�̐ݒ�
	int nNumVertices;		//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVertexBuffer;	//���_�o�b�t�@�̃|�C���^

	g_vtxMinObject = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_vtxMaxObject = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{

		//���_�����擾
		nNumVertices = g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->GetFVF());

		//���_�o�b�t�@�����b�N
		g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//���ׂĂ̕ϐ����r���čŏ��E�ő�l�����߂�
			if (g_vtxMinObject.x > vtx.x)
			{
				g_vtxMinObject.x = vtx.x;
			}
			if (g_vtxMaxObject.x < vtx.x)
			{
				g_vtxMaxObject.x = vtx.x;
			}
			if (g_vtxMinObject.y > vtx.y)
			{
				g_vtxMinObject.y = vtx.y;
			}
			if (g_vtxMaxObject.y < vtx.y)
			{
				g_vtxMaxObject.y = vtx.y;
			}
			if (g_vtxMinObject.z > vtx.z)
			{
				g_vtxMinObject.z = vtx.z;
			}
			if (g_vtxMaxObject.z < vtx.z)
			{
				g_vtxMaxObject.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@�̃A�����b�N
		g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->UnlockVertexBuffer();
	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_LOADOBJECT; nCntObject++)
	{
		// ���b�V���̊J��
		if (g_ObjectModel[nCntObject].pMeshObject != NULL)
		{
			g_ObjectModel[nCntObject].pMeshObject->Release();
			g_ObjectModel[nCntObject].pMeshObject = NULL;
		}
		// �}�e���A���̊J��
		if (g_ObjectModel[nCntObject].pBuffMatObject != NULL)
		{
			g_ObjectModel[nCntObject].pBuffMatObject->Release();
			g_ObjectModel[nCntObject].pBuffMatObject = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObject(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9	 pDevice = GetDevice();
	D3DXMATRIX			 mtxSize, mtxRot, mtxTrans;				//�v�Z�p
	D3DXMATERIAL		 *pMat;
	D3DMATERIAL9		 matDef;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Object[nCntObject].mtxWorldObject);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxSize, g_Object[nCntObject].scale.x, g_Object[nCntObject].scale.y, g_Object[nCntObject].scale.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorldObject, &g_Object[nCntObject].mtxWorldObject, &mtxSize);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nCntObject].rot.y, g_Object[nCntObject].rot.x, g_Object[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorldObject, &g_Object[nCntObject].mtxWorldObject, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorldObject, &g_Object[nCntObject].mtxWorldObject, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCntObject].mtxWorldObject);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_ObjectModel[g_Object[nCntObject].nType].pBuffMatObject->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ObjectModel[g_Object[nCntObject].nType].nNumMatObject; nCntMat++)
			{
				//�e�N�X�`���̐ݒ�
				//pDevice->SetTexture(0, g_ObjectModel[nCntObject].pTextureObject);
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �`��
				g_ObjectModel[g_Object[nCntObject].nType].pMeshObject->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//============================================================================
// ��Q���̎擾
//=============================================================================
OBJECT * GetObjectModel(void)
{
	return &g_Object[0];
}

//============================================================================
// ��Q���̐ݒ�
//=============================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, OBJECTTYPE nType)
{
	// �ϐ��錾
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == false)
		{
			g_Object[nCntObject].pos = pos;
			g_Object[nCntObject].move = move;
			g_Object[nCntObject].rot = rot;
			g_Object[nCntObject].scale = scale;
			g_Object[nCntObject].bUse = true;
			g_Object[nCntObject].nType = nType;
			break;
		}
	}
}
//=======================================================================================
// ��Q���̓����蔻��
//=======================================================================================
bool ColisionObject(D3DXVECTOR3 * ppos, D3DXVECTOR3 * pposOld)
{
	bool bLand = false;
	int nCntObject;
	PLAYER * pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	//if (*ppObjectRet != NULL)
	//{
	//	*ppObjectRet = NULL;
	//}

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse)
		{
			if (pPlayer->pos.y + 100 >= g_Object[nCntObject].pos.y&&
				pPlayer->pos.y <= g_Object[nCntObject].pos.y + 100)
			{
				//g_ObjectModel[g_Object[nCntObject].nType].MaxObject

				if (ppos->x + pPlayer->size.x > 0 + g_Object[nCntObject].pos.x&&
					ppos->x + pPlayer->size.x < 100 + g_Object[nCntObject].pos.x)
				{
					//��O�̓����蔻�菈��
					if (pposOld->z + pPlayer->size.z <= g_Object[nCntObject].pos.z - 100 &&
						ppos->z + pPlayer->size.z >= g_Object[nCntObject].pos.z - 100)
					{
						ppos->z = g_Object[nCntObject].pos.z - pPlayer->size.z - 100;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					//���̓����蔻�菈��
					if (pposOld->z - pPlayer->size.z >= g_Object[nCntObject].pos.z - 0 &&
						ppos->z - pPlayer->size.z < g_Object[nCntObject].pos.z - 00)
					{
						ppos->z = g_Object[nCntObject].pos.z + pPlayer->size.z - 00;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
			}
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_Object[nCntObject].pos.y&&
				pPlayer->pos.y <= g_Object[nCntObject].pos.y + g_vtxMaxObject.y)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinObject.z + g_Object[nCntObject].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxObject.z + g_Object[nCntObject].pos.z)
				{
					//���̓����蔻�菈��
					if (pposOld->x + pPlayer->size.x <= g_Object[nCntObject].pos.x - g_vtxMaxObject.x&&
						ppos->x + pPlayer->size.x >= g_Object[nCntObject].pos.x - g_vtxMaxObject.x)
					{
						ppos->x = g_Object[nCntObject].pos.x - pPlayer->size.x - g_vtxMaxObject.x;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					//�E�̓����蔻�菈��
					if (pposOld->x - pPlayer->size.x >= g_Object[nCntObject].pos.x - g_vtxMinObject.x&&
						ppos->x - pPlayer->size.x <= g_Object[nCntObject].pos.x - g_vtxMinObject.x)
					{
						ppos->x = g_Object[nCntObject].pos.x + pPlayer->size.x - g_vtxMinObject.x;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
			}
			if (ppos->x + pPlayer->size.x > g_vtxMinObject.x + g_Object[nCntObject].pos.x&&
				ppos->x + pPlayer->size.x < g_vtxMaxObject.x + g_Object[nCntObject].pos.x)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinObject.z + g_Object[nCntObject].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxObject.z + g_Object[nCntObject].pos.z)
				{
					////��̓����蔻�菈��
					//if (pposOld->y - pPlayer->size.y >= g_vtxMinObject.y - g_Object[nCntObject].pos.y &&
					//	ppos->y - pPlayer->size.y <= g_vtxMaxObject.y - g_Object[nCntObject].pos.y)
					//{
					//	//ppos->y = g_Object[nCntObject].pos.y + pPlayer->size.y + g_vtxMaxObject.y;
					//g_Object[nCntObject].bUse = false;
					//SetGameState(GAMESTATE_END);
					//SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					//}
					//���̓����蔻�菈��
					if (pPlayer->posOld.y + pPlayer->vtxMaxPlayer.y >= g_Object[nCntObject].pos.y)
					{
						//ppos->y = g_Object[nCntObject].pos.y + pPlayer->size.y + g_vtxMaxObject.y;
						g_Object[nCntObject].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					}
				}
			}
		}
	}
	return bLand;
}


