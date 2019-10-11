//====================================================================================================
//
// �����L���O���� [ranking.cpp]
// Author : tanaka rikiya
//
//====================================================================================================
//====================================================================================================
//�C���N���[�h�t�@�C��
//===================================================================================================
#include "main.h"
#include "ranking.h"
#include "camera.h"
#include "player.h"
#include "meshfield.h"
#include "text.h"
#include "effect.h"
#include "load.h"
#include "input.h"
#include "fade.h"
#include "light.h"
//#include "sound.h"

// ====================================================================================================
// �}�N����`
// ====================================================================================================
#define	TEXTURE_RANKING	"Data/Texture/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define RANKING_SIZE	(30)								// �����L���O�̑傫��
#define RANKING_MAX		(3)									// ���l
#define RANKING_DATA	(5)									// �����L���O��

#define COUNTRANK (500)
#define SAVE_FILE_NAME	("Data/text/rank.txt")							// �Z�[�u�t�@�C��

// ====================================================================================================
// �v���g�^�C�v�錾
// ====================================================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

// ====================================================================================================
// �O���[�o���ϐ��錾
// ====================================================================================================
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_RankingPos;					// �����L���O�{�[�h�̃|�W�V����
RANKING					g_aRanking[RANKING_DATA];		// �����L���O�ϐ�
int						g_nRanking;						// �����L���O
int						g_nCnt;
// ====================================================================================================
// ����������
// ====================================================================================================
void InitRanking(void)
{	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_RankingPos = D3DXVECTOR3(800.0f, 180.0f, 0.0f);
	g_nRanking = 0;
	g_nCnt = 0;
	for (int nCntRank = 0; nCntRank < RANKING_DATA; nCntRank++)
	{
		g_aRanking[nCntRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCntRank].aName[0];
		g_aRanking[nCntRank].nPoint = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING,								// �t�@�C���̖��O
		&g_pTextureRanking);							// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexRanking(pDevice);

	// �J�����̏I������
	InitCamera();

	// �J�����̏I������
	InitEffect();

	// ���C�g�̏I������
	InitLight();

	// 3D�|���S���̏I������
	InitMeshField();

	InitMoji();

	SetText(D3DXVECTOR3(640.0f, 360.0f, 000.0f), 1280/2, 720/2, 6);
	//SetText(D3DXVECTOR3(200.0f, 100.0f, 000.0f), 150, 60, 5);
}

// ====================================================================================================
// �I������
// ====================================================================================================
void UninitRanking(void)
{
	UninitEffect();

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// 3D�|���S���̏I������
	UninitMeshField();

	UninitMoji();
	// �e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

// ====================================================================================================
// �X�V����
// ====================================================================================================
void UpdateRanking(void)
{

	UpdateEffect();
	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	// 3D�|���S���̍X�V����
	UpdateMeshField();

	UpdateMoji();

	g_nCnt++;
	
	if (GetKeyboardTrigger(DIK_RETURN) || g_nCnt >= COUNTRANK)
	{
		//PlaySound(SOUND_LABEL_SE_ENTER);
		SetFade(MODE_TITLE);
		g_nCnt =0;
	}

}

// ====================================================================================================
// �`�揈��
// ====================================================================================================
void DrawRanking(void)
{
	SetCamera();
	// 3D�|���S���̏I������
	DrawMeshField();
	DrawEffect();

	DrawMoji();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

	// �|���S���̕`��
	for (int nCntRanking = 0; nCntRanking < RANKING_MAX * RANKING_DATA; nCntRanking++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRanking, 2);
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


}

// ====================================================================================================
// ���_�̍쐬
// ====================================================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���g

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKING_MAX * RANKING_DATA, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);

	// ���_���̐ݒ�
	for (int nCntRankingData = 0; nCntRankingData < RANKING_DATA; nCntRankingData++)
	{
		for (int nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// ��ڂ̒��_
			pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// ��ڂ̒��_
			pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// �O�ڂ̒��_
			pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// �l�ڂ̒��_

			pVtx[0].rhw = 1.0f;									// ��ڂ̒��_�쐬
			pVtx[1].rhw = 1.0f;									// ��ڂ̒��_�쐬
			pVtx[2].rhw = 1.0f;									// �O�ڂ̒��_�쐬
			pVtx[3].rhw = 1.0f;									// �l�ڂ̒��_�쐬

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ��ڂ̐F�ݒ�
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ��ڂ̐F�ݒ�
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �O�ڂ̐F�ݒ�
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �l�ڂ̐F�ݒ�

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				// ��ڂ̃e�N�X�`��
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);				// ��ڂ̃e�N�X�`��
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				// �O�ڂ̃e�N�X�`��
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);				// �l�ڂ̃e�N�X�`��

			pVtx += 4;
		}
	}
	// �A�����b�N
	g_pVtxBuffRanking->Unlock();
}

// ====================================================================================================
// �����L���O�̕ύX
// ====================================================================================================
void AddRanking(int nPoint, int nRankingCnt)
{
	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���g
	LOAD *pLoad;

	int nCntRanking;		// �����L���O�J�E���g
	int nCntRankingData;	// �����L���O�J�E���g
	int nRanking;			// �������L���O
	float fRanking;

	pLoad = GetLoad();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingData = 0; nCntRankingData < RANKING_DATA; nCntRankingData++, pLoad++)
	{
		g_aRanking[nCntRankingData].nPoint = pLoad->nPoint;

		for (nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			nRanking = g_aRanking[nCntRankingData].nPoint % (int)powf(10.0f, (float)nCntRanking + 1.0f) / (int)powf(10.0f, (float)nCntRanking);
			fRanking = (float)nRanking / 10.0f;

			pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// ��ڂ̒��_
			pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// ��ڂ̒��_
			pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// �O�ڂ̒��_
			pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// �l�ڂ̒��_

			pVtx[0].tex = D3DXVECTOR2(fRanking, 0.0f);				// ��ڂ̃e�N�X�`��
			pVtx[1].tex = D3DXVECTOR2(fRanking + 0.1f, 0.0f);		// ��ڂ̃e�N�X�`��
			pVtx[2].tex = D3DXVECTOR2(fRanking, 1.0f);				// �O�ڂ̃e�N�X�`��
			pVtx[3].tex = D3DXVECTOR2(fRanking + 0.1f, 1.0f);		// �l�ڂ̃e�N�X�`��

			pVtx += 4;
		}
	}
	// �A�����b�N
	g_pVtxBuffRanking->Unlock();
}