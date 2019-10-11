//=============================================================================
//
// �G���� [enemy.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "enemy.h"
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
#define Enemy_01 "Data/Model/enemy/tsuribito.x"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define Enemy_02 "Data/Model/enemy/gyosen.x"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define POLTGON0_TEX "Data/Texture/.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C����

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXMATRIX			 mtxWorldEnemy;
	LPD3DXMESH			 pMeshEnemy;
	LPD3DXBUFFER		 pBuffMatEnemy;
	LPDIRECT3DTEXTURE9	 pTextureEnemy;
	DWORD				 nNumMatEnemy;

} ENEMYRESOURCE;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
ENEMYRESOURCE		g_EnemyModel[ENEMYTYPE_MAX];
ENEMY				g_Enemy[MAX_ENEMY];
GAMESTATE g_gameStateEnemy = GAMESTATE_NONE;


//X�t�@�C������ő�l�ƍŏ��l�̎擾
D3DXVECTOR3 g_vtxMaxEnemy;		//�ő�l
D3DXVECTOR3 g_vtxMinEnemy;		//�ŏ��l

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	int nCntEnemy;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// �ʒu�E�����̏����ݒ�
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��ʒu
		g_Enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Enemy[nCntEnemy].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].bUse = false;
		g_Enemy[nCntEnemy].nType = ENEMYTYPE_GYOSEN;
		//g_Enemy[nCntModel].hIdxShadow = SetShadow(g_Model[nCntModel].pos, g_Model[nCntModel].rot);
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		Enemy_01,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyModel[0].pBuffMatEnemy,
		NULL,
		&g_EnemyModel[0].nNumMatEnemy,
		&g_EnemyModel[0].pMeshEnemy);

	D3DXLoadMeshFromX(
		Enemy_02,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyModel[1].pBuffMatEnemy,
		NULL,
		&g_EnemyModel[1].nNumMatEnemy,
		&g_EnemyModel[1].pMeshEnemy);



	//X�t�@�C������ő�l�ƍŏ��l�̐ݒ�
	int nNumVertices;		//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVertexBuffer;	//���_�o�b�t�@�̃|�C���^

	g_vtxMinEnemy = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_vtxMaxEnemy = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		//���_�����擾
		nNumVertices = g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->GetFVF());

		//���_�o�b�t�@�����b�N
		g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//���ׂĂ̕ϐ����r���čŏ��E�ő�l�����߂�
			if (g_vtxMinEnemy.x > vtx.x)
			{
				g_vtxMinEnemy.x = vtx.x;
			}
			if (g_vtxMaxEnemy.x < vtx.x)
			{
				g_vtxMaxEnemy.x = vtx.x;
			}
			if (g_vtxMinEnemy.y > vtx.y)
			{
				g_vtxMinEnemy.y = vtx.y;
			}
			if (g_vtxMaxEnemy.y < vtx.y)
			{
				g_vtxMaxEnemy.y = vtx.y;
			}
			if (g_vtxMinEnemy.z > vtx.z)
			{
				g_vtxMinEnemy.z = vtx.z;
			}
			if (g_vtxMaxEnemy.z < vtx.z)
			{
				g_vtxMaxEnemy.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@�̃A�����b�N
		g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->UnlockVertexBuffer();
	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_LOADENEMY; nCntEnemy++)
	{
		// ���b�V���̊J��
		if (g_EnemyModel[nCntEnemy].pMeshEnemy != NULL)
		{
			g_EnemyModel[nCntEnemy].pMeshEnemy->Release();
			g_EnemyModel[nCntEnemy].pMeshEnemy = NULL;
		}
		// �}�e���A���̊J��
		if (g_EnemyModel[nCntEnemy].pBuffMatEnemy != NULL)
		{
			g_EnemyModel[nCntEnemy].pBuffMatEnemy->Release();
			g_EnemyModel[nCntEnemy].pBuffMatEnemy = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9	 pDevice = GetDevice();
	D3DXMATRIX			 mtxSize, mtxRot, mtxTrans;				//�v�Z�p
	D3DXMATERIAL		 *pMat;
	D3DMATERIAL9		 matDef;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorldEnemy);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxSize, g_Enemy[nCntEnemy].scale.x, g_Enemy[nCntEnemy].scale.y, g_Enemy[nCntEnemy].scale.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntEnemy].mtxWorldEnemy, &mtxSize);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntEnemy].mtxWorldEnemy, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntEnemy].mtxWorldEnemy, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorldEnemy);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_EnemyModel[g_Enemy[nCntEnemy].nType].pBuffMatEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_EnemyModel[g_Enemy[nCntEnemy].nType].nNumMatEnemy; nCntMat++)
			{
				//�e�N�X�`���̐ݒ�
				//pDevice->SetTexture(0, g_EnemyModel[nCntEnemy].pTextureEnemy);
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �`��
				g_EnemyModel[g_Enemy[nCntEnemy].nType].pMeshEnemy->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//============================================================================
// �G�̎擾
//=============================================================================
ENEMY * GetEnemy(void)
{
	return &g_Enemy[0];
}

//============================================================================
// ���f���̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, ENEMYTYPE_ENEMY nType)
{
	// �ϐ��錾
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{
			g_Enemy[nCntEnemy].pos = pos;
			g_Enemy[nCntEnemy].move = move;
			g_Enemy[nCntEnemy].rot = rot;
			g_Enemy[nCntEnemy].scale = scale;
			g_Enemy[nCntEnemy].bUse = true;
			g_Enemy[nCntEnemy].nType = nType;
			break;
		}
	}
}
//=======================================================================================
// �G�̓����蔻��
//=======================================================================================
bool ColisionEnemy(D3DXVECTOR3 * ppos, D3DXVECTOR3 * pposOld)
{
	bool bLand = false;
	int nCntEnemy;
	PLAYER * pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	//if (*ppEnemyRet != NULL)
	//{
	//	*ppEnemyRet = NULL;
	//}

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse)
		{
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_Enemy[nCntEnemy].pos.y&&
				pPlayer->pos.y <= g_Enemy[nCntEnemy].pos.y + g_vtxMaxEnemy.y)
			{
				//g_EnemyModel[g_Enemy[nCntEnemy].nType].MaxEnemy

				if (ppos->x + pPlayer->size.x > g_vtxMinEnemy.x + g_Enemy[nCntEnemy].pos.x&&
					ppos->x + pPlayer->size.x < g_vtxMaxEnemy.x + g_Enemy[nCntEnemy].pos.x)
				{
					//��O�̓����蔻�菈��
					if (pposOld->z + pPlayer->size.z <= g_Enemy[nCntEnemy].pos.z - g_vtxMaxEnemy.z&&
						ppos->z + pPlayer->size.z >= g_Enemy[nCntEnemy].pos.z - g_vtxMaxEnemy.z)
					{
						ppos->z = g_Enemy[nCntEnemy].pos.z - pPlayer->size.z - g_vtxMaxEnemy.z;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					//���̓����蔻�菈��
					if (pposOld->z - pPlayer->size.z >= g_Enemy[nCntEnemy].pos.z - g_vtxMinEnemy.z &&
						ppos->z - pPlayer->size.z < g_Enemy[nCntEnemy].pos.z - g_vtxMinEnemy.z)
					{
						ppos->z = g_Enemy[nCntEnemy].pos.z + pPlayer->size.z - g_vtxMinEnemy.z;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
			}
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_Enemy[nCntEnemy].pos.y&&
				pPlayer->pos.y <= g_Enemy[nCntEnemy].pos.y + g_vtxMaxEnemy.y)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinEnemy.z + g_Enemy[nCntEnemy].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxEnemy.z + g_Enemy[nCntEnemy].pos.z)
				{
					//���̓����蔻�菈��
					if (pposOld->x + pPlayer->size.x <= g_Enemy[nCntEnemy].pos.x - g_vtxMaxEnemy.x&&
						ppos->x + pPlayer->size.x >= g_Enemy[nCntEnemy].pos.x - g_vtxMaxEnemy.x)
					{
						ppos->x = g_Enemy[nCntEnemy].pos.x - pPlayer->size.x - g_vtxMaxEnemy.x;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					//�E�̓����蔻�菈��
					if (pposOld->x - pPlayer->size.x >= g_Enemy[nCntEnemy].pos.x - g_vtxMinEnemy.x&&
						ppos->x - pPlayer->size.x <= g_Enemy[nCntEnemy].pos.x - g_vtxMinEnemy.x)
					{
						ppos->x = g_Enemy[nCntEnemy].pos.x + pPlayer->size.x - g_vtxMinEnemy.x;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
			}
			if (ppos->x + pPlayer->size.x > g_vtxMinEnemy.x + g_Enemy[nCntEnemy].pos.x&&
				ppos->x + pPlayer->size.x < g_vtxMaxEnemy.x + g_Enemy[nCntEnemy].pos.x)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinEnemy.z + g_Enemy[nCntEnemy].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxEnemy.z + g_Enemy[nCntEnemy].pos.z)
				{
					////��̓����蔻�菈��
					//if (pposOld->y - pPlayer->size.y >= g_vtxMinEnemy.y - g_Enemy[nCntEnemy].pos.y &&
					//	ppos->y - pPlayer->size.y <= g_vtxMaxEnemy.y - g_Enemy[nCntEnemy].pos.y)
					//{
					//	//ppos->y = g_Enemy[nCntEnemy].pos.y + pPlayer->size.y + g_vtxMaxEnemy.y;
						//g_Enemy[nCntEnemy].bUse = false;
						//SetGameState(GAMESTATE_END);
					//SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					//}
					//���̓����蔻�菈��
					if (pPlayer->posOld.y + pPlayer->vtxMaxPlayer.y >= g_Enemy[nCntEnemy].pos.y)
					{
						//ppos->y = g_Enemy[nCntEnemy].pos.y + pPlayer->size.y + g_vtxMaxEnemy.y;
						g_Enemy[nCntEnemy].bUse = false;
						SetGameState(GAMESTATE_END);
						SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					}
				}
			}
		}
	}
	return bLand;
}


