//=============================================================================
//
// �̗͏��� [heart.cpp]
// Author : Tanaka rikiya
//
//=============================================================================
#include "heart.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_HEART		"Data/Texture/heart.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXWIDTH	(150)	//�e�N�X�`���̕�
#define TEXHEIGHT	(150)	//�e�N�X�`���̍���
#define MAXHEARTNUM	(3)

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
	int nNum;
}heart;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexheart(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureheart = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffheart = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
heart  g_aheart[MAXHEARTNUM];
int	g_nheart;				// �̗�

//=============================================================================
// ����������
//=============================================================================
void InitHeart(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nheart = 6;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXHEARTNUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffheart,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_HEART,		// �t�@�C���̖��O
		&g_pTextureheart);	// �ǂݍ��ރ������[

							// ���_���̍쐬
	MakeVertexheart(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitHeart(void)
{
	// �e�N�X�`���̊J��

	if (g_pTextureheart != NULL)
	{
		g_pTextureheart->Release();
		g_pTextureheart = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffheart != NULL)
	{
		g_pVtxBuffheart->Release();
		g_pVtxBuffheart = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHeart(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHeart(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntheart;

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffheart, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureheart);

	// �|���S���̕`��
	for (nCntheart = 0; nCntheart < MAXHEARTNUM; nCntheart++)
	{
		//pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntheart * 4, 2);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexheart(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntheart;
	VERTEX_2D *pVtx;
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffheart->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	for (nCntheart = 0; nCntheart < MAXHEARTNUM; nCntheart++)
	{
		g_aheart[nCntheart].pos = D3DXVECTOR3(80.0f + TEXWIDTH * nCntheart * 1.0f, 80.0f, 0.0f);
		g_aheart[nCntheart].nNum = 0;

		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aheart[nCntheart].pos.x - TEXWIDTH / 2, g_aheart[nCntheart].pos.y - TEXHEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aheart[nCntheart].pos.x + TEXWIDTH / 2, g_aheart[nCntheart].pos.y - TEXHEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aheart[nCntheart].pos.x - TEXWIDTH / 2, g_aheart[nCntheart].pos.y + TEXHEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aheart[nCntheart].pos.x + TEXWIDTH / 2, g_aheart[nCntheart].pos.y + TEXHEIGHT / 2, 0.0f);

		//�A�j���[�V�����̍X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.33f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.33f, 1.0f);

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
	g_pVtxBuffheart->Unlock();
}

//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void AddHeart(int nValue)
{
	VERTEX_2D *pVtx;
	g_nheart += nValue;
	int nCntheart;

	int nFullHeart = g_nheart / 2;
	int nHalfHeart = g_nheart % 2;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffheart->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntheart = 0; nCntheart < MAXHEARTNUM; nCntheart++)
	{
		if (nCntheart < nFullHeart)
		{
			g_aheart[nCntheart].nNum = 0;
		}
		else if (nCntheart >= nFullHeart && nCntheart < nFullHeart + nHalfHeart)
		{
			g_aheart[nCntheart].nNum = 1;
		}
		else
		{
			g_aheart[nCntheart].nNum = 2;
		}

		//�e�N�X�`�����W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aheart[nCntheart].nNum*0.33f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aheart[nCntheart].nNum*0.33f + 0.33f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aheart[nCntheart].nNum*0.33f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aheart[nCntheart].nNum*0.33f + 0.33f, 1.0f);

		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffheart->Unlock();
}