//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Tanaka rikiya
//
//=============================================================================
#include "score.h"
#include "save.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_SCORE		"Data/Texture/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXWIDTH	(40)	//�e�N�X�`���̕�
#define TEXHEIGHT	(80)	//�e�N�X�`���̍���]
#define MAXSCORENUM	(3)
#define SCORE_POS_X			(1100)
#define SCORE_POS_Y			(648)
#define SCORE_SIZE_X		(45)
#define SCORE_SIZE_Y		(85)

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
	int nNum;
}SCORE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
SCORE  g_aScore[MAXSCORENUM];
int g_nScore;				// �X�R�A

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{

	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		g_aScore[MAXSCORENUM].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[MAXSCORENUM].nNum = 0;
		g_aScore[MAXSCORENUM].bUse = false;


		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		g_nScore = 0;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXSCORENUM,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffScore,
			NULL);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
			TEXTURE_SCORE,		// �t�@�C���̖��O
			&g_pTextureScore);	// �ǂݍ��ރ������[

		// ���_���̍쐬
		MakeVertexScore(pDevice);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��

	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	float nCntScore;
	VERTEX_2D *pVtx;
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 10, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	for (nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(SCORE_POS_X - SCORE_SIZE_X / 2 + nCntScore * SCORE_SIZE_X, SCORE_POS_Y - SCORE_SIZE_Y / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCORE_POS_X + SCORE_SIZE_X / 2 + nCntScore * SCORE_SIZE_X, SCORE_POS_Y - SCORE_SIZE_Y / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCORE_POS_X - SCORE_SIZE_X / 2 + nCntScore * SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCORE_POS_X + SCORE_SIZE_X / 2 + nCntScore * SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y / 2, 0.0f);

		//�A�j���[�V�����̍X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx += 4;
		
	}	

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void AddScore(int nValue)
{

	SAVE *pSave;
	pSave = GetSave();
	VERTEX_2D *pVtx;
	g_nScore += nValue;

	int nCntScore;
	int Digits;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		Digits = g_nScore % (int)powf(10.0f, 3.0f - nCntScore) / (int)powf(10.0f, 3.0f - nCntScore - 1.0f);
		
		//�e�N�X�`�����W�ݒ�
		pVtx[0].tex = D3DXVECTOR2((Digits*0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((Digits*0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((Digits*0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((Digits*0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// score�̎擾
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}
