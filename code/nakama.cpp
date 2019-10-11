//=============================================================================
//
// ���ԏ��� [nakama.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include <time.h>
#include "fade.h"
#include "nakama.h"
#include "input.h"
#include "camera.h"
#include "effect.h"
#include "player.h"
#include "ami.h"
#include "score.h"
#include "ami.h"
#include "game.h"
#include "sound.h"
#include "heart.h"
#include "input.h"
//#include "shadow.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NAKAMA_01 "Data/Model/nakama/ebi.x"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define NAKAMA_02 "Data/Model/nakama/sakana.x"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define POLTGON0_TEX "Data/Texture/.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define SPEED		(0.5f)

//////////////////// �����̐ݒ� ////////////////////
#define EFFECT_RADIUS	20.0f;
#define EFFECT_ANGLE	0.0f;
#define EFFECT_SPEED	5.0f;
#define EFFECT_COL		D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.95f);
#define EFFECT_LIFE		20;
////////////////////////////////////////////////////

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTexturenakama = NULL;
LPD3DXMESH				 g_pMeshnakama = {};
LPD3DXBUFFER			 g_pBuffMatnakama = NULL;
DWORD					 g_NumMatnakama = 0;

NAKAMA					 g_nakama[MAX_NAKAMA];

int randomNakama;

//X�t�@�C������ő�l�ƍŏ��l�̎擾
D3DXVECTOR3 g_vtxMaxnakama;		//�ő�l
D3DXVECTOR3 g_vtxMinnakama;		//�ŏ��l

//=============================================================================
// ����������
//=============================================================================
void Initnakama(void)
{
	randomNakama = 0;

	srand((int)time(NULL)); //�����g����
	int nCntnakama = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		// �ʒu�E�����̏����ݒ�
		g_nakama[nCntnakama].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_nakama[nCntnakama].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_nakama[nCntnakama].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_nakama[nCntnakama].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_nakama[nCntnakama].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_nakama[nCntnakama].bUse = false;
		g_nakama[nCntnakama].bFirst = false;
		g_nakama[nCntnakama].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��ʒu
		g_nakama[nCntnakama].nType = 0;
		g_nakama[nCntnakama].nCountGameover = 3;
		//g_nakama[nCntnakama].nIdxShadow = SetShadow(g_nakama[nCntnakama].pos, g_nakama[nCntnakama].rot);


	// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			POLTGON0_TEX,
			&g_nakama[nCntnakama].aNakama[0].pTextureNakama);

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			NAKAMA_01,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_nakama[nCntnakama].aNakama[0].pBuffMatnakama,
			NULL,
			&g_nakama[nCntnakama].aNakama[0].nNumMatnakama,
			&g_nakama[nCntnakama].aNakama[0].pMeshnakama);

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			NAKAMA_02,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_nakama[nCntnakama].aNakama[1].pBuffMatnakama,
			NULL,
			&g_nakama[nCntnakama].aNakama[1].nNumMatnakama,
			&g_nakama[nCntnakama].aNakama[1].pMeshnakama);

		//X�t�@�C������ő�l�ƍŏ��l�̐ݒ�
		int nNumVertices;						//���_��
		DWORD sizeFVF;							//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVertexBuffer;					//���_�o�b�t�@�̃|�C���^

		g_vtxMinnakama = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_vtxMaxnakama = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

		//���_�����擾
		nNumVertices = g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->GetFVF());

		//���_�o�b�t�@�����b�N
		g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//���ׂĂ̕ϐ����r���čŏ��E�ő�l�����߂�
			if (g_vtxMinnakama.x > vtx.x)
			{
				g_vtxMinnakama.x = vtx.x;
			}
			if (g_vtxMaxnakama.x < vtx.x)
			{
				g_vtxMaxnakama.x = vtx.x;
			}
			if (g_vtxMinnakama.y > vtx.y)
			{
				g_vtxMinnakama.y = vtx.y;
			}
			if (g_vtxMaxnakama.y < vtx.y)
			{
				g_vtxMaxnakama.y = vtx.y;
			}
			if (g_vtxMinnakama.z > vtx.z)
			{
				g_vtxMinnakama.z = vtx.z;
			}
			if (g_vtxMaxnakama.z < vtx.z)
			{
				g_vtxMaxnakama.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@�̃A�����b�N
		g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->UnlockVertexBuffer();

	}


	//Setnakama(D3DXVECTOR3(0.0f, 0.0f, 000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
}
//=============================================================================
// �I������
//=============================================================================
void Uninitnakama(void)
{
	for (int nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		// ���b�V���̊J��
		if (g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama != NULL)
		{
			g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->Release();
			g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatnakama != NULL)
		{
			g_pBuffMatnakama->Release();
			g_pBuffMatnakama = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Updatenakama(void)
{

	int nCntnakama;

	for (nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{

		g_nakama[nCntnakama].pos += g_nakama[nCntnakama].move;


			//if()
		if (GetMode() == MODE_GAME)
		{


			if (g_nakama[nCntnakama].bUse == false)
			{
				if (g_nakama[nCntnakama].bFirst == false)
				{
					Setnakama(D3DXVECTOR3(500.0f, 0.0f, 500.0f) , D3DXVECTOR3(0.0f, SPEED, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
					g_nakama[nCntnakama].bFirst = true;
				}
				else
				{
					D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 4000 - 2000.0f, 0.0f, rand() % 4000 - 2000.0f);
					Setnakama(pos, D3DXVECTOR3(0.0f, SPEED, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
				}
				// �e������
				//DeleteShadow(g_nakama[nCntnakama].nIdxShadow);
				//Setnakama(pos, D3DXVECTOR3(0.0f, SPEED, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
				//g_nakama[nCntnakama].bUse = true;
			}

			if (g_nakama[nCntnakama].pos.y >= 400)
			{
				AddHeart(-2);
				g_nakama[nCntnakama].nCountGameover--;
				g_nakama[nCntnakama].bUse = false;
				if (g_nakama[nCntnakama].nCountGameover <= 0)
				{
					SetFade(MODE_END);
				}
			}

			// �e�̈ʒu��ݒ�
			//SetPositionShadow(g_nakama[nCntnakama].nIdxShadow, g_nakama[nCntnakama].pos);

		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void Drawnakama(void)
{
	LPDIRECT3DDEVICE9	 pDevice = GetDevice();
	D3DXMATRIX			 mtxSize, mtxRot, mtxTrans;				//�v�Z�p
	D3DXMATERIAL		 *pMat;
	D3DMATERIAL9		 matDef;

	for (int nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		if (g_nakama[nCntnakama].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_nakama[nCntnakama].mtxWorldnakama);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxSize, g_nakama[nCntnakama].scale.x, g_nakama[nCntnakama].scale.y, g_nakama[nCntnakama].scale.z);
			D3DXMatrixMultiply(&g_nakama[nCntnakama].mtxWorldnakama, &g_nakama[nCntnakama].mtxWorldnakama, &mtxSize);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_nakama[nCntnakama].rot.y, g_nakama[nCntnakama].rot.x, g_nakama[nCntnakama].rot.z);
			D3DXMatrixMultiply(&g_nakama[nCntnakama].mtxWorldnakama, &g_nakama[nCntnakama].mtxWorldnakama, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_nakama[nCntnakama].pos.x, g_nakama[nCntnakama].pos.y, g_nakama[nCntnakama].pos.z);
			D3DXMatrixMultiply(&g_nakama[nCntnakama].mtxWorldnakama, &g_nakama[nCntnakama].mtxWorldnakama, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_nakama[nCntnakama].mtxWorldnakama);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_nakama[nCntnakama].aNakama[nCntnakama].pBuffMatnakama->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nakama[nCntnakama].aNakama[nCntnakama].nNumMatnakama; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturenakama);
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �`��
				g_nakama[nCntnakama].aNakama[nCntnakama].pMeshnakama->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//============================================================================
// ���Ԃ̎擾
//=============================================================================
NAKAMA * Getnakama(void)
{
	return &g_nakama[0];
}

//============================================================================
// ���Ԃ̐ݒ�
//=============================================================================
void Setnakama(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType)
{
	// �ϐ��錾
	int nCntnakama;
	for (nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		if (g_nakama[nCntnakama].bUse == false)
		{
			g_nakama[nCntnakama].pos = pos;
			g_nakama[nCntnakama].move = move;
			g_nakama[nCntnakama].rot = rot;
			g_nakama[nCntnakama].scale = scale;
			g_nakama[nCntnakama].bUse = true;
			g_nakama[nCntnakama].nType = nType;

			// �e�̍쐬
			//g_nakama[nCntnakama].nIdxShadow = SetShadow(g_nakama[nCntnakama].pos, g_nakama[nCntnakama].rot);

			break;
		}
	}
}
//=======================================================================================
// ���Ԃ̓����蔻��
//=======================================================================================
bool Collisionnakama(D3DXVECTOR3 * ppos, D3DXVECTOR3 * pposOld)
{
	bool bLand = false;
	int nCntnakama;

	PLAYER * pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	AMI * pAmi;
	//�v���C���[�̎擾
	pAmi = Getami();

	//if (*ppnakamaRet != NULL)
	//{
	//	*ppnakamaRet = NULL;
	//}

	for (nCntnakama = 0; nCntnakama < MAX_NAKAMA; nCntnakama++)
	{
		if (g_nakama[nCntnakama].bUse)
		{
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_nakama[nCntnakama].pos.y&&
				pPlayer->pos.y <= g_nakama[nCntnakama].pos.y + g_vtxMaxnakama.y) 
			{
				if (ppos->x + pPlayer->size.x > g_vtxMinnakama.x + g_nakama[nCntnakama].pos.x&&
					ppos->x + pPlayer->size.x < g_vtxMaxnakama.x + g_nakama[nCntnakama].pos.x)
				{
					//��O�̓����蔻�菈��
					if (pposOld->z + pPlayer->size.z <= g_nakama[nCntnakama].pos.z - g_vtxMaxnakama.z&&
						ppos->z + pPlayer->size.z >= g_nakama[nCntnakama].pos.z - g_vtxMaxnakama.z||
						pposOld->z - pPlayer->size.z >= g_nakama[nCntnakama].pos.z - g_vtxMinnakama.z &&
						ppos->z - pPlayer->size.z < g_nakama[nCntnakama].pos.z - g_vtxMinnakama.z)
					{
						PlaySound(SOUND_LABEL_SE_GET);
						AddScore(1);
						g_nakama[nCntnakama].bUse = false;
						pAmi->bUse = false;
						MakeEffect_Nakama();
						//ppos->z = g_nakama[nCntnakama].pos.z - pPlayer->size.z - g_vtxMaxnakama.z;
					}

					////���̓����蔻�菈��
					//if (pposOld->z - pPlayer->size.z >= g_nakama[nCntnakama].pos.z - g_vtxMinnakama.z &&
					//	ppos->z - pPlayer->size.z < g_nakama[nCntnakama].pos.z - g_vtxMinnakama.z)
					//{
					//	PlaySound(SOUND_LABEL_SE_GET);
					//	AddScore(1);
					//	g_nakama[nCntnakama].bUse = false;
					//	pAmi->bUse = false;
					//	MakeEffect_Nakama();
					//	//ppos->z = g_nakama[nCntnakama].pos.z + pPlayer->size.z - g_vtxMinnakama.z;
					//}
				}
			}
			if (pPlayer->pos.y + pPlayer->vtxMaxPlayer.y >= g_nakama[nCntnakama].pos.y&&
				pPlayer->pos.y <= g_nakama[nCntnakama].pos.y + g_vtxMaxnakama.y) 
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinnakama.z + g_nakama[nCntnakama].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxnakama.z + g_nakama[nCntnakama].pos.z)
				{
					//���̓����蔻�菈��
					if (pposOld->x + pPlayer->size.x <= g_nakama[nCntnakama].pos.x - g_vtxMaxnakama.x&&
						ppos->x + pPlayer->size.x >= g_nakama[nCntnakama].pos.x - g_vtxMaxnakama.x||
						pposOld->x - pPlayer->size.x >= g_nakama[nCntnakama].pos.x - g_vtxMinnakama.x&&
						ppos->x - pPlayer->size.x <= g_nakama[nCntnakama].pos.x - g_vtxMinnakama.x)
					{
						PlaySound(SOUND_LABEL_SE_GET);
						AddScore(1);
						g_nakama[nCntnakama].bUse = false;
						pAmi->bUse = false;
						MakeEffect_Nakama();
						//ppos->x = g_nakama[nCntnakama].pos.x - pPlayer->size.x - g_vtxMaxnakama.x;
					}

					////�E�̓����蔻�菈��
					//if (pposOld->x - pPlayer->size.x >= g_nakama[nCntnakama].pos.x - g_vtxMinnakama.x&&
					//	ppos->x - pPlayer->size.x <= g_nakama[nCntnakama].pos.x - g_vtxMinnakama.x)
					//{
					//	PlaySound(SOUND_LABEL_SE_GET);
					//	AddScore(1);
					//	g_nakama[nCntnakama].bUse = false;
					//	pAmi->bUse = false;
					//	MakeEffect_Nakama();
					//	//ppos->x = g_nakama[nCntnakama].pos.x + pPlayer->size.x - g_vtxMinnakama.x;
					//}
				}
			}
			if (ppos->x + pPlayer->size.x > g_vtxMinnakama.x + g_nakama[nCntnakama].pos.x&&
				ppos->x + pPlayer->size.x < g_vtxMaxnakama.x + g_nakama[nCntnakama].pos.x)
			{
				if (ppos->z + pPlayer->size.z > g_vtxMinnakama.z + g_nakama[nCntnakama].pos.z&&
					ppos->z + pPlayer->size.z < g_vtxMaxnakama.z + g_nakama[nCntnakama].pos.z)
				{
					//��̓����蔻�菈��
					if (pposOld->y - pPlayer->size.y >= g_vtxMinnakama.y - g_nakama[nCntnakama].pos.y &&
						ppos->y - pPlayer->size.y <= g_vtxMaxnakama.y - g_nakama[nCntnakama].pos.y||
						pPlayer->posOld.y + pPlayer->vtxMaxPlayer.y >= g_nakama[nCntnakama].pos.y)
					{
						PlaySound(SOUND_LABEL_SE_GET);
						AddScore(1);
						g_nakama[nCntnakama].bUse = false;
						pAmi->bUse = false;
						MakeEffect_Nakama();
						//ppos->y = g_nakama[nCntnakama].pos.y + pPlayer->size.y + g_vtxMaxnakama.y;
					}
				}
			}
		}
	}
	return bLand;
}
//=======================================================================================
// �p�[�e�B�N���֐�
//=======================================================================================
void MakeEffect_Nakama(void)
{
	int nCntnakama=0;

	//////////////////// �����̐ݒ� ////////////////////
	D3DXCOLOR col	= EFFECT_COL;
	float fRadius	= EFFECT_RADIUS;
	float fAngle	= EFFECT_ANGLE;
	float fSpeed	= EFFECT_SPEED;
	int nLife		= EFFECT_LIFE;
	////////////////////////////////////////////////////
	for (int nCnt = 0; nCnt < 60; nCnt++)
	{
		// 0�`3.14���o�� * (0 or 1)* -1�Ő��������߂�(�o���͈�)
		fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;	// �S�����o��

																				// �����ʒu
		D3DXVECTOR3 pos1 = D3DXVECTOR3(g_nakama[nCntnakama].pos.x, g_nakama[nCntnakama].pos.y, g_nakama[nCntnakama].pos.z);

		// �o������
		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed, 0.0f);
		D3DXVECTOR3 move1 = D3DXVECTOR3(sinf(fAngle)*fSpeed, 0.0f, cosf(fAngle)*fSpeed);
		D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed);

		// �G�t�F�N�g�̐ݒ�
		SetEffect(pos1, move, fRadius, nLife, col,	0);
		SetEffect(pos1, move1, fRadius, nLife, col, 0);
		SetEffect(pos1, move2, fRadius, nLife, col, 0);
	}
}
