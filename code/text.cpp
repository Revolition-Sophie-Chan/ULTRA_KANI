//=============================================================================
//
// �摜�ǂݍ��݂̏���[Text.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
//�C���N���[�h�t�@�C��
#include "main.h"
#include "Player.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "text.h"
//#include "sound.h"
//#include "tutorial.h"
//#include "joystick.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXT		(8)		//�ǂݍ��ރe�N�X�`���̐�
#define	TEXTURE_TEXT0		"Data/Texture/text03.png"	//Press�G���^
#define	TEXTURE_TEXT1		"Data/Texture/kani���S.png"	//���S
#define	TEXTURE_TEXT2		"Data/Texture/text01.png"		//����������
#define	TEXTURE_TEXT3		"Data/Texture/tutorial2.png"	//�`���[�g���A�����b�Z�[�W
#define	TEXTURE_TEXT4		"Data/Texture/Help_down.png"	//�w���v�A�C�R��
#define	TEXTURE_TEXT5		"Data/Texture/text02.png"		//�������w���v
#define	TEXTURE_TEXT6		"Data/Texture/rank.png"	//�����L���O
#define	TEXTURE_TEXT7		"Data/Texture/tutorial.png"	//�`���[�g���A��

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
VERTEX_2D g_aVertex[4];
LPDIRECT3DTEXTURE9 g_pTextureText[MAX_TEXT] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffText = NULL;		//���_�o�b�t�@�ւ̃|�C���^

TEXT				 g_nText[MAX_TEXT];

int g_nCounterText;								//�A�j���[�V�����J�E���^�[
int g_nPattenText;									//�A�j���[�V�����p�^�[��
int g_nCounterText2;								//�A�j���[�V�����J�E���^�[
int g_nPattenText2;									//�A�j���[�V�����p�^�[��

//=============================================================================
// �|���S���̏�����
//=============================================================================
void InitMoji(void)
{

	int nCntText;
	g_nCounterText=0;		//�A�j���[�V�����J�E���^�[
	g_nPattenText=0;

	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		g_nText[nCntText].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�|���S���̈ʒu
		g_nText[nCntText].bUse = false;
		g_nText[nCntText].nTextType = 0;
		g_nText[nCntText].scale_X = 0;
		g_nText[nCntText].scale_Y = 0;
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT0,	//Press�G���^
		&g_pTextureText[0]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT1,	//���S
		&g_pTextureText[1]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT2,	//����������
		&g_pTextureText[2]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT3,	//�`���[�g���A�����b�Z�[�W
		&g_pTextureText[3]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT4,	//���S
		&g_pTextureText[4]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT5,	//���w���v
		&g_pTextureText[5]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT6,	//�����L���O
		&g_pTextureText[6]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT7,	//�`���[�g���A��
		&g_pTextureText[7]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffText,
		NULL);


	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffText->Lock(0, 0, (void**)&pVtx, 0);
	//���_�̐ݒ�	
	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_nText[nCntText].pos.x - g_nText[nCntText].scale_X, g_nText[nCntText].pos.y - g_nText[nCntText].scale_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_nText[nCntText].pos.x  + g_nText[nCntText].scale_X, g_nText[nCntText].pos.y - g_nText[nCntText].scale_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_nText[nCntText].pos.x  - g_nText[nCntText].scale_X, g_nText[nCntText].pos.y + g_nText[nCntText].scale_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_nText[nCntText].pos.x  + g_nText[nCntText].scale_X, g_nText[nCntText].pos.y + g_nText[nCntText].scale_Y, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffText->Unlock();
}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void UninitMoji(void)
{
	int nCntText;

	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureText[nCntText] != NULL)
		{
			g_pTextureText[nCntText]->Release();
			g_pTextureText[nCntText] = NULL;
		}
	}
	if (g_pVtxBuffText != NULL)
	{
		g_pVtxBuffText->Release();
		g_pVtxBuffText = NULL;
	}
}
//=============================================================================
// polygon�X�V����
//=============================================================================
void UpdateMoji(void)
{
	int nCntText;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffText->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		if (g_nText[nCntText].nTextType == 0)
		{
			g_nCounterText++;
			if (g_nCounterText % 40 == 0)
			{
				g_nPattenText = (g_nPattenText + 1) % 2;
				if (g_nPattenText == 0)
				{
					pVtx[0].col = D3DXCOLOR(255, 255, 255, 0);
					pVtx[1].col = D3DXCOLOR(255, 255, 255, 0);
					pVtx[2].col = D3DXCOLOR(255, 255, 255, 0);
					pVtx[3].col = D3DXCOLOR(255, 255, 255, 0);
				}
				else
				{
					pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
					pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
					pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
					pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);
				}
			}
		}
		pVtx += 4;
	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffText->Unlock();

}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void DrawMoji(void)
{

	int nCntText;
	LPDIRECT3DDEVICE9 pDevice;
	////�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓��ꂩ��
	//g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[�g�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffText, 0, sizeof(VERTEX_2D));

	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{
		if (g_nText[nCntText].bUse)
		{
			pDevice->SetTexture(0, g_pTextureText[g_nText[nCntText].nTextType]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntText * 4, 2);
		}
	}
}

//=============================================================================
// �e�L�X�g�̐ݒ�
//=============================================================================
void SetText(D3DXVECTOR3 pos, int scale_X, int scale_Y,int nTextType)
{
	int nCntText;
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffText->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntText = 0; nCntText < MAX_TEXT; nCntText++)
	{

		if (g_nText[nCntText].bUse == false)	//���g�p
		{
			g_nText[nCntText].pos = pos;
			g_nText[nCntText].nTextType = nTextType;
			g_nText[nCntText].scale_X = scale_X;
			g_nText[nCntText].scale_Y = scale_Y;

			//���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_nText[nCntText].pos.x - g_nText[nCntText].scale_X, g_nText[nCntText].pos.y - g_nText[nCntText].scale_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_nText[nCntText].pos.x + g_nText[nCntText].scale_X, g_nText[nCntText].pos.y - g_nText[nCntText].scale_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_nText[nCntText].pos.x - g_nText[nCntText].scale_X, g_nText[nCntText].pos.y + g_nText[nCntText].scale_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_nText[nCntText].pos.x + g_nText[nCntText].scale_X, g_nText[nCntText].pos.y + g_nText[nCntText].scale_Y, 0.0f);
			//pVtx += 4;

			g_nText[nCntText].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffText->Unlock();
}
//=============================================================================
// �A�C�e���̎擾
//=============================================================================
TEXT *GetText(void)
{
	return &g_nText[0];
}