//=============================================================================
//
// �|���S������ [Wall.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "Wall.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_WALL	(4)	// �ő吔

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	bool bUse;
} WALL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//Direct3D�f�o�C�X�̃|�C���^
WALL g_aWall[MAX_WALL];

LPDIRECT3DTEXTURE9 g_pTextureWall[MAX_WALL] = {};//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice,"Data/Texture/gyosen.png",//nendoSophie.png//olga_face.jpg
		&g_pTextureWall[0]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/gyosen.png",//nendoSophie.png//olga_face.jpg
		&g_pTextureWall[1]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/gyosen.png",//nendoSophie.png//olga_face.jpg
		&g_pTextureWall[2]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/gyosen.png",//nendoSophie.png//olga_face.jpg
		&g_pTextureWall[3]);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}
	// ���_���̍쐬
	MakeVertexWall(pDevice);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 3.14f/2, 0.0f));
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -3.14f/2, 0.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	int nCntWall;

	//�e�N�X�`���̊J��
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_pTextureWall[nCntWall] != NULL)
		{
			g_pTextureWall[nCntWall]->Release();
			g_pTextureWall[nCntWall] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	
	D3DXMATRIX mtxRot,mtxTrans;//�v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall+=1)
	{
		if (g_aWall[nCntWall].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//pDevice->GetTransform(D3DTS_VIEW, &g_aWall[nCntWall].mtxView);

			//g_aWall[nCntWall].mtxWorld._11 = g_aWall[nCntWall].mtxView._11;
			//g_aWall[nCntWall].mtxWorld._12 = g_aWall[nCntWall].mtxView._21;
			//g_aWall[nCntWall].mtxWorld._13 = g_aWall[nCntWall].mtxView._31;
			//g_aWall[nCntWall].mtxWorld._21 = g_aWall[nCntWall].mtxView._12;
			//g_aWall[nCntWall].mtxWorld._22 = g_aWall[nCntWall].mtxView._22;
			//g_aWall[nCntWall].mtxWorld._23 = g_aWall[nCntWall].mtxView._32;
			//g_aWall[nCntWall].mtxWorld._31 = g_aWall[nCntWall].mtxView._13;
			//g_aWall[nCntWall].mtxWorld._32 = g_aWall[nCntWall].mtxView._23;
			//g_aWall[nCntWall].mtxWorld._33 = g_aWall[nCntWall].mtxView._33;

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			pDevice->SetTexture(0, g_pTextureWall[nCntWall]);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-100.0f, 60.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 60.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}
//=============================================================================
// �ǂ̐ݒ�
//=============================================================================
void SetWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	int nCntWall;
	VERTEX_3D *pVtx;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (!g_aWall[nCntWall].bUse)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-100.0f, 80.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(100.0f, 80.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
			g_aWall[nCntWall].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffWall->Unlock();
}
