
//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "effect.h"
#include "nakama.h"
#include "item.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"


//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_FILE					"Data/text/player.txt"			// �t�@�C����
#define PLAY_MOTION					(true)							// ���[�V���� [On,Off]
#define MOTIONBREADFRAME			(10)							// ���[�V�����u�����h�̃t���[����
#define SPEED						(0.15f)
#define POLYGON_SPD (2)
#define POLYGON_SPD_ITEM (4)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LoadModel				g_LoadPlayer[MAX_PARTS];		// �ǂݍ��񂾃��f���̏��
LoadMotion				g_Motion;						// �ǂݍ��񂾃��[�V�������
PLAYER					g_Player;						// �v���C���[�̏��
int						g_nCounterKeySet;				// �L�[�Z�b�g�̃J�E���^�[
int						g_nCounterFrame;				// �t���[�����̃J�E���^�[
int						g_nMotionBlendFrame;			// ���[�V�����u�����h�p�̃t���[����
int						g_Item;							// ���[�V�����u�����h�p�̃t���[����
D3DXVECTOR3				g_posDiff[MAX_PARTS];			// �P�t���[��������̍��� [pos]
D3DXVECTOR3				g_RotDiff[MAX_PARTS];			// �P�t���[��������̍��� [Rot]

D3DXVECTOR3				g_fDistanceP;


//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E�����̏����ݒ�
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.fRadius = 100.0f;
	g_Player.fHeight = 0.0f;
	g_Player.IdxLine = 0;
	g_Player.fDestAngle = D3DX_PI;
	g_Player.bjump = false;
	g_Player.Item = false;
	g_Player.hIdxShadow = 1;

	g_Player.Wait	 = false;
	g_Player.Move_TATE	 = false;
	g_Player.Move_YOKO	 = false;
	g_Player.Swim	 = false;
	g_Player.Move_YOKO_ITEM = false;
	g_Item++;


	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// ���f���̏��
		g_Player.aPlayerModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���f���̈ʒu
		g_Player.aPlayerModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���f���̌���
		g_Player.aPlayerModel[nCntModel].nType = 0;												// ���f���̎��
		g_Player.aPlayerModel[nCntModel].nIdxModelParent = -1;									// �e���f���̃C���f�b�N�X
	}

	// ���[�V���� 
	g_Player.nMotionTypeOld = MOTION_MAX;			// �O���[�V�����̎��
	g_Player.nMotionType = MOTION_NEUTRAL;			// ���[�V�����̎��
	g_Player.nFrameALL = 0;							// ���[�V�����̍ő�t���[����
	g_Player.nNowFrame = 0;							// ���[�V�����̌��݂̃t���[����

	g_nCounterKeySet = 0;							// �L�[�Z�b�g�̃J�E���^�[
	g_nCounterFrame = 0;							// �t���[�����̃J�E���^�[
	g_nMotionBlendFrame = 0;						// ���[�V�����u�����h�p�̃t���[����

	g_Player.nMaxParts = 0;							// �g�p���邷�郂�f���̐�

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// ���f���̍ő吔
		g_posDiff[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �P�t���[��������̍��� [pos]
		g_RotDiff[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �P�t���[��������̍��� [Rot]
	}

	//==============================
	// �t�@�C���ǂݍ���
	//==============================
	LoadPlayer();

	//#if 1
	//==============================
	// X�t�@�C���ǂݍ���
	//==============================

	for (int nCntModel = 0; nCntModel < g_Player.nLoadParts; nCntModel++)
	{// �ǂݍ��ރ��f���̍ő吔
		D3DXLoadMeshFromX(g_LoadPlayer[nCntModel].pXFileName,		// �ǂݍ���X�t�@�C����
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_LoadPlayer[nCntModel].pBuffMat,		// �}�e���A�����|�C���^
			NULL,
			&g_LoadPlayer[nCntModel].NumMat,		// �}�e���A�����̐�
			&g_LoadPlayer[nCntModel].pMesh);		// ���b�V�����|�C���^

													//�e�N�X�`���̓ǂݍ���
		D3DXMATERIAL *pMat;							// X�t�@�C��������o�����}�e���A����������

		// X�t�@�C������}�e���A�������擾
		pMat = (D3DXMATERIAL*)g_LoadPlayer[nCntModel].pBuffMat->GetBufferPointer();

		// �e�N�X�`���̃|�C���^���}�e���A�����̐����z��
		g_LoadPlayer[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[(int)g_LoadPlayer[nCntModel].NumMat];	// int�^�ɒ���

																										// �擾�����t�@�C���������
		for (int nCntNumMat = 0; nCntNumMat < (int)g_LoadPlayer[nCntModel].NumMat; nCntNumMat++)	// DWORD�^����int�^�ɕϊ�����
		{
			// �e�N�X�`���̃|�C���^������
			g_LoadPlayer[nCntModel].pTexture[nCntNumMat] = NULL;

			// �e�N�X�`���t�@�C�����������Ă���ꍇ�A�ǂݍ���
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename,
					&g_LoadPlayer[nCntModel].pTexture[nCntNumMat]);
			}
		}
	}
	//X�t�@�C������ő�l�ƍŏ��l�̐ݒ�
	int nNumVertices;						//���_��
	DWORD sizeFVF;							//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVertexBuffer;					//���_�o�b�t�@�̃|�C���^

	g_Player.vtxMinPlayer = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_Player.vtxMaxPlayer = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//���_�����擾
		nNumVertices = g_LoadPlayer[nCntPlayer].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_LoadPlayer[nCntPlayer].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_LoadPlayer[nCntPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//���ׂĂ̕ϐ����r���čŏ��E�ő�l�����߂�
			if (g_Player.vtxMinPlayer.x > vtx.x)
			{
				g_Player.vtxMinPlayer.x = vtx.x;
			}
			if (g_Player.vtxMaxPlayer.x < vtx.x)
			{
				g_Player.vtxMaxPlayer.x = vtx.x;
			}
			if (g_Player.vtxMinPlayer.y > vtx.y)
			{
				g_Player.vtxMinPlayer.y = vtx.y;
			}
			if (g_Player.vtxMaxPlayer.y < vtx.y)
			{
				g_Player.vtxMaxPlayer.y = vtx.y;
			}
			if (g_Player.vtxMinPlayer.z > vtx.z)
			{
				g_Player.vtxMinPlayer.z = vtx.z;
			}
			if (g_Player.vtxMaxPlayer.z < vtx.z)
			{
				g_Player.vtxMaxPlayer.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}

		//�����̌v�Z
		g_Player.size = (g_Player.vtxMaxPlayer - g_Player.vtxMinPlayer) * 0.01f;

		//���_�o�b�t�@�̃A�����b�N
		g_LoadPlayer[nCntPlayer].pMesh->UnlockVertexBuffer();

		//g_Player.hIdxShadow = SetShadow(g_Player.pos, g_Player.rot);

	}

}
//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// ���b�V���̊J��
		if (g_LoadPlayer[nCntPlayer].pMesh != NULL)
		{
			g_LoadPlayer[nCntPlayer].pMesh->Release();
			g_LoadPlayer[nCntPlayer].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_LoadPlayer[nCntPlayer].pBuffMat != NULL)
		{
			g_LoadPlayer[nCntPlayer].pBuffMat->Release();
			g_LoadPlayer[nCntPlayer].pBuffMat = NULL;
		}
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//�d��
	g_Player.move.y -= 0.5f;

	CAMERA *pCamera;
	pCamera = GetCamera();
	ITEM *pItem;
	pItem = GetItem();
	//SetPositionShadow(g_Player.hIdxShadow, g_Player.pos);
	g_Player.move *= 0.7f;
	g_Player.posOld = g_Player.pos;
	g_Player.pos += g_Player.move;
	Collisionnakama(&g_Player.pos, &g_Player.posOld);
	//CollisionItem(&g_Player.pos, &g_Player.posOld);
	ColisionEnemy(&g_Player.pos, &g_Player.posOld);

	g_Player.posOld = g_Player.pos;

	// �O��̃��[�V�������L��
	g_Player.nMotionTypeOld = g_Player.nMotionType;

	if (pItem->bItem == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			PlaySound(SOUND_LABEL_SE_SWIM);
			g_Player.Wait = false;
			g_Player.Move_TATE = false;
			g_Player.Move_YOKO = false;
			g_Player.Swim = true;
			g_Player.Move_YOKO_ITEM = false;

			g_Player.move.x += sinf(D3DX_PI*0.0f + pCamera->rot.y) * 25;
			g_Player.move.z += cosf(D3DX_PI*0.0f + pCamera->rot.y) * 25;
			g_Player.move.y += 12;
		}
		if (g_Player.Swim == false)
		{

			if (GetKeyboardPress(DIK_A))
			{
				//���΂߂�
				if (GetKeyboardPress(DIK_W))
				{
					g_Player.Wait = false;
					g_Player.Move_TATE = true;
					g_Player.Move_YOKO = false;
					g_Player.Swim = false;
					g_Player.Move_YOKO_ITEM = false;

					g_Player.move.x += sinf(-D3DX_PI*0.25f + pCamera->rot.y)*POLYGON_SPD;
					g_Player.move.z += cosf(-D3DX_PI*0.25f + pCamera->rot.y)*POLYGON_SPD;
					//g_Player.rot.y = (D3DX_PI*0.75f + pCamera->rot.y);
				}
				else if (GetKeyboardPress(DIK_S))
				{
					g_Player.Wait = false;
					g_Player.Move_TATE = true;
					g_Player.Move_YOKO = false;
					g_Player.Swim = false;
					g_Player.Move_YOKO_ITEM = false;

					g_Player.move.x += sinf(-D3DX_PI*0.75f + pCamera->rot.y)*POLYGON_SPD;
					g_Player.move.z += cosf(-D3DX_PI*0.75f + pCamera->rot.y)*POLYGON_SPD;
					//g_Player.rot.y = (D3DX_PI*0.25f + pCamera->rot.y);
				}
				//��
				else
				{
					g_Player.Wait = false;
					g_Player.Move_TATE = false;
					g_Player.Move_YOKO = true;
					g_Player.Swim = false;
					g_Player.Move_YOKO_ITEM = false;

					g_Player.move.x += sinf(-D3DX_PI*0.5f + pCamera->rot.y)*POLYGON_SPD * 2;
					g_Player.move.z += cosf(-D3DX_PI*0.5f + pCamera->rot.y)*POLYGON_SPD * 2;
					//g_Player.rot.y = (D3DX_PI*0.5f + pCamera->rot.y);

				}
			}
			else if (GetKeyboardPress(DIK_D))
			{
				//�E�̎΂�
				if (GetKeyboardPress(DIK_W))
				{
					g_Player.Wait = false;
					g_Player.Move_TATE = true;
					g_Player.Move_YOKO = false;
					g_Player.Swim = false;
					g_Player.Move_YOKO_ITEM = false;

					g_Player.move.x += sinf(D3DX_PI*0.25f + pCamera->rot.y)*POLYGON_SPD;
					g_Player.move.z += cosf(D3DX_PI*0.25f + pCamera->rot.y)*POLYGON_SPD;
					//g_Player.rot.y = (-D3DX_PI*0.75f + pCamera->rot.y);
	
				}
				else if (GetKeyboardPress(DIK_S))
				{
					g_Player.Wait = false;
					g_Player.Move_TATE = true;
					g_Player.Move_YOKO = false;
					g_Player.Swim = false;
					g_Player.Move_YOKO_ITEM = false;

					g_Player.move.x += sinf(D3DX_PI*0.75f + pCamera->rot.y)*POLYGON_SPD;
					g_Player.move.z += cosf(D3DX_PI*0.75f + pCamera->rot.y)*POLYGON_SPD;
					//g_Player.rot.y = (-D3DX_PI*0.25f + pCamera->rot.y);
				}
				//�E
				else
				{
					g_Player.Wait = false;
					g_Player.Move_TATE = false;
					g_Player.Move_YOKO = true;
					g_Player.Swim = false;
					g_Player.Move_YOKO_ITEM = false;

					g_Player.move.x += sinf(D3DX_PI*0.5f + pCamera->rot.y)*POLYGON_SPD * 2;
					g_Player.move.z += cosf(D3DX_PI*0.5f + pCamera->rot.y)*POLYGON_SPD * 2;
					//g_Player.rot.y = (-D3DX_PI*0.5f + pCamera->rot.y);

				}
			}
			else if (GetKeyboardPress(DIK_W))
			{
				g_Player.Wait = false;
				g_Player.Move_TATE = true;
				g_Player.Move_YOKO = false;
				g_Player.Swim = false;
				g_Player.Move_YOKO_ITEM = false;

				g_Player.move.x += sinf(D3DX_PI*0.0f + pCamera->rot.y)*POLYGON_SPD;
				g_Player.move.z += cosf(D3DX_PI*0.0f + pCamera->rot.y)*POLYGON_SPD;
				//g_Player.rot.y = (D3DX_PI*1.0f + pCamera->rot.y);

			}
			else if (GetKeyboardPress(DIK_S))
			{
				g_Player.Wait = false;
				g_Player.Move_TATE = true;
				g_Player.Move_YOKO = false;
				g_Player.Swim = false;
				g_Player.Move_YOKO_ITEM = false;

				g_Player.move.x += sinf(D3DX_PI*1.0f + pCamera->rot.y)*POLYGON_SPD;
				g_Player.move.z += cosf(D3DX_PI*1.0f + pCamera->rot.y)*POLYGON_SPD;
				if (GetKeyboardTrigger(DIK_SPACE))
				{
					PlaySound(SOUND_LABEL_SE_SWIM);
					g_Player.Wait = false;
					g_Player.Move_TATE = false;
					g_Player.Move_YOKO = false;
					g_Player.Swim = true;
					g_Player.Move_YOKO_ITEM = false;

					g_Player.move.x += sinf(D3DX_PI*1.0f + pCamera->rot.y) * 25;
					g_Player.move.z += cosf(D3DX_PI*1.0f + pCamera->rot.y) * 25;
					g_Player.move.y += 12;
				}
			}
			//else if (GetKeyboardTrigger(DIK_SPACE))
			//{
			//	PlaySound(SOUND_LABEL_SE_SWIM);
			//	g_Player.Wait = false;
			//	g_Player.Move_TATE = false;
			//	g_Player.Move_YOKO = false;
			//	g_Player.Swim = true;
			//	g_Player.Move_YOKO_ITEM = false;

			//	g_Player.move.x += sinf(D3DX_PI*0.0f + pCamera->rot.y) * 25;
			//	g_Player.move.z += cosf(D3DX_PI*0.0f + pCamera->rot.y) * 25;
			//	g_Player.move.y += 12;
			//}
		}
	}
				
	if (pItem->bItem == true)
	{
		g_Item++;
		if (g_Item <= 540)
		{
			if (g_Item % 2 == 0)
			{
				MakeEffect_Player();//�G�t�F�N�g�𐶐�
			}

			if (GetKeyboardTrigger(DIK_SPACE))
			{
				PlaySound(SOUND_LABEL_SE_SWIM);
				g_Player.Wait = false;
				g_Player.Move_TATE = false;
				g_Player.Move_YOKO = false;
				g_Player.Swim = true;
				g_Player.Move_YOKO_ITEM = false;
				g_Player.move.x += sinf(D3DX_PI*0.0f + pCamera->rot.y) * 35;
				g_Player.move.z += cosf(D3DX_PI*0.0f + pCamera->rot.y) * 35;
				g_Player.move.y += 20;
			}
			if (g_Player.Swim == false)
			{

				if (GetKeyboardPress(DIK_A))
				{
					//���΂߂�
					if (GetKeyboardPress(DIK_W))
					{
						g_Player.Wait = false;
						g_Player.Move_TATE = true;
						g_Player.Move_YOKO = false;
						g_Player.Swim = false;
						g_Player.Move_YOKO_ITEM = false;
						g_Player.move.x += sinf(-D3DX_PI*0.25f + pCamera->rot.y)*POLYGON_SPD_ITEM;
						g_Player.move.z += cosf(-D3DX_PI*0.25f + pCamera->rot.y)*POLYGON_SPD_ITEM;
						//g_Player.rot.y = (D3DX_PI*0.75f + pCamera->rot.y);
					}
					else if (GetKeyboardPress(DIK_S))
					{
						g_Player.Wait = false;
						g_Player.Move_TATE = true;
						g_Player.Move_YOKO = false;
						g_Player.Swim = false;
						g_Player.Move_YOKO_ITEM = false;
						g_Player.move.x += sinf(-D3DX_PI*0.75f + pCamera->rot.y)*POLYGON_SPD_ITEM;
						g_Player.move.z += cosf(-D3DX_PI*0.75f + pCamera->rot.y)*POLYGON_SPD_ITEM;
						//g_Player.rot.y = (D3DX_PI*0.25f + pCamera->rot.y);
					}
					//��
					else
					{
						g_Player.Wait = false;
						g_Player.Move_TATE = false;
						g_Player.Move_YOKO = false;
						g_Player.Swim = false;
						g_Player.Move_YOKO_ITEM = true;
						g_Player.move.x += sinf(-D3DX_PI*0.5f + pCamera->rot.y)*POLYGON_SPD_ITEM * 2;
						g_Player.move.z += cosf(-D3DX_PI*0.5f + pCamera->rot.y)*POLYGON_SPD_ITEM * 2;
						//g_Player.rot.y = (D3DX_PI*0.5f + pCamera->rot.y);
					}
				}
				else if (GetKeyboardPress(DIK_D))
				{
					//�E�̎΂߂�
					if (GetKeyboardPress(DIK_W))
					{
						g_Player.Wait = false;
						g_Player.Move_TATE = true;
						g_Player.Move_YOKO = false;
						g_Player.Swim = false;
						g_Player.Move_YOKO_ITEM = false;
						g_Player.move.x += sinf(D3DX_PI*0.25f + pCamera->rot.y)*POLYGON_SPD_ITEM;
						g_Player.move.z += cosf(D3DX_PI*0.25f + pCamera->rot.y)*POLYGON_SPD_ITEM;
						//g_Player.rot.y = (-D3DX_PI*0.75f + pCamera->rot.y);
					}
					else if (GetKeyboardPress(DIK_S))
					{
						g_Player.Wait = false;
						g_Player.Move_TATE = true;
						g_Player.Move_YOKO = false;
						g_Player.Swim = false;
						g_Player.Move_YOKO_ITEM = false;
						g_Player.move.x += sinf(D3DX_PI*0.75f + pCamera->rot.y)*POLYGON_SPD_ITEM;
						g_Player.move.z += cosf(D3DX_PI*0.75f + pCamera->rot.y)*POLYGON_SPD_ITEM;
						//g_Player.rot.y = (-D3DX_PI*0.25f + pCamera->rot.y);

					}
					//�E
					else
					{
						g_Player.Wait = false;
						g_Player.Move_TATE = false;
						g_Player.Move_YOKO = false;
						g_Player.Swim = false;
						g_Player.Move_YOKO_ITEM = true;
						g_Player.move.x += sinf(D3DX_PI*0.5f + pCamera->rot.y)*POLYGON_SPD_ITEM * 2;
						g_Player.move.z += cosf(D3DX_PI*0.5f + pCamera->rot.y)*POLYGON_SPD_ITEM * 2;
						//g_Player.rot.y = (-D3DX_PI*0.5f + pCamera->rot.y);

					}
				}
				else if (GetKeyboardPress(DIK_W))
				{
					g_Player.Wait = false;
					g_Player.Move_TATE = true;
					g_Player.Move_YOKO = false;
					g_Player.Swim = false;
					g_Player.Move_YOKO_ITEM = false;
					g_Player.move.x += sinf(D3DX_PI*0.0f + pCamera->rot.y)*POLYGON_SPD_ITEM;
					g_Player.move.z += cosf(D3DX_PI*0.0f + pCamera->rot.y)*POLYGON_SPD_ITEM;
					//g_Player.rot.y = (D3DX_PI*1.0f + pCamera->rot.y);

				}
				else if (GetKeyboardPress(DIK_S))
				{
					g_Player.Wait = false;
					g_Player.Move_TATE = true;
					g_Player.Move_YOKO = false;
					g_Player.Swim = false;
					g_Player.Move_YOKO_ITEM = false;
					g_Player.move.x += sinf(D3DX_PI*1.0f + pCamera->rot.y)*POLYGON_SPD_ITEM;
					g_Player.move.z += cosf(D3DX_PI*1.0f + pCamera->rot.y)*POLYGON_SPD_ITEM;

				}
				else if (GetKeyboardTrigger(DIK_SPACE))
				{
					PlaySound(SOUND_LABEL_SE_SWIM);
					g_Player.Wait = false;
					g_Player.Move_TATE = false;
					g_Player.Move_YOKO = false;
					g_Player.Swim = true;
					g_Player.Move_YOKO_ITEM = false;

					g_Player.move.y += 20;
				}
			}

		}
		if (g_Item >= 540)
		{
			pItem->bItem = false;
			if (pItem->bItem == false)
			{
				g_Item = 0;
			}
		}
	}
	if (g_Player.pos.x < -2000)
	{
		g_Player.pos.x = -2000;
	}
	if (g_Player.pos.x > 2000)
	{
		g_Player.pos.x = 2000;
	}
	if (g_Player.pos.z < -2000)
	{
		g_Player.pos.z = -2000;
	}
	if (g_Player.pos.z > 2000)
	{
		g_Player.pos.z = 2000;
	}
	if (g_Player.pos.y < 40)
	{
		g_Player.pos.y = 40;
	}
	if (g_Player.pos.y >290)
	{
		g_Player.pos.y = 290;
	}
	// ���[�V����

	// �ҋ@
	if (!g_Player.Move_TATE || !g_Player.Move_YOKO || !g_Player.Move_YOKO_ITEM || !g_Player.Swim)
	{
		g_Player.nMotionType = MOTION_NEUTRAL;
	}

	//�@����
	if (g_Player.Move_TATE)
	{
		g_Player.nMotionType = MOTION_MOVE_TATE;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// �Ō�܂ōĐ����ꂽ�ꍇ
			g_Player.Move_TATE = false;
		}
	}
	//�@����
	if (g_Player.Move_YOKO)
	{
		g_Player.nMotionType = MOTION_MOVE_YOKO;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// �Ō�܂ōĐ����ꂽ�ꍇ
			g_Player.Move_YOKO = false;
		}
	}
	//�A�C�e�����̕���
	if (g_Player.Move_YOKO_ITEM)
	{
		g_Player.nMotionType = MOTION_MOVE_YOKO_ITEM;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// �Ō�܂ōĐ����ꂽ�ꍇ
			g_Player.Move_YOKO_ITEM = false;
		}
	}

	//�@�W�����v
	if (g_Player.Swim)
	{
		g_Player.nMotionType = MOTION_SWIM;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// �Ō�܂ōĐ����ꂽ�ꍇ
			g_Player.Swim = false;
		}
	}
#if PLAY_MOTION
	PlayerMotion();
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;						// �}�e���A���ւ̃|�C���^
	D3DXMATRIX			mtxParent;					// �e�̃}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// �������킹��}�g���b�N�X�̐ݒ�
	for (int nCntModel = 0; nCntModel < g_Player.nMaxParts; nCntModel++)
	{
		if (g_Player.aPlayerModel[nCntModel].nIdxModelParent == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aPlayerModel[g_Player.aPlayerModel[nCntModel].nIdxModelParent].mtxWorld;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aPlayerModel[nCntModel].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player.aPlayerModel[nCntModel].rot.y, g_Player.aPlayerModel[nCntModel].rot.x, g_Player.aPlayerModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_Player.aPlayerModel[nCntModel].pos.x, g_Player.aPlayerModel[nCntModel].pos.y, g_Player.aPlayerModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxTrans);

		// �e���f���̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aPlayerModel[nCntModel].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̔��f
			pDevice->SetTexture(0, 0);

			// ���f��(�p�[�c)�̕`��
			g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}

}

//===============================================================================
// �v���C���[�̃��[�V����
//===============================================================================
void PlayerMotion(void)
{

	// ���[�V�����̏�����

	if (g_Player.nMotionTypeOld != g_Player.nMotionType)
	{// ���[�V�������O��ƈقȂ�
	 // �L�[�t���[��
		g_nCounterKeySet = 0;
		// �t���[����
		g_nCounterFrame = 0;
		// ���[�V�����u�����h�̃t���[���������߂�
		g_nMotionBlendFrame = MOTIONBREADFRAME;
		// �t���[�����̌v�Z
		CulFrame();
	}
	// �L�[�̐ؑ�

	switch (g_Motion.Motion[g_Player.nMotionType].nLoop)
	{// ���[�V�����̎�ނ̃��[�v��
	case 0:		// ���[�v���Ȃ�
		if (g_nCounterFrame == g_nMotionBlendFrame && g_Motion.Motion[g_Player.nMotionType].nNumKey == g_nCounterKeySet + 1)
		{// �ŏI�t���[���@&& �ŏI�L�[�ɂȂ���
		 // �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = g_Motion.Motion[g_Player.nMotionType].nNumKey - 1;		// �Ō�̃L�[�Z�b�g��ݒ肷��
																						// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].frame;
		}
		else if (g_nCounterFrame == g_nMotionBlendFrame && g_Motion.Motion[g_Player.nMotionType].nNumKey != g_nCounterKeySet)
		{// �Ō�̃t���[�� && �ŏI�L�[�ł͂Ȃ�
		 // �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = (g_nCounterKeySet + 1) % g_Motion.Motion[g_Player.nMotionType].nNumKey;
			// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].frame;
		}
		break;

	case 1:		// ���[�v����
		if (g_nCounterFrame == g_nMotionBlendFrame)
		{// �Ō�̃t���[��
		 // �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = (g_nCounterKeySet + 1) % g_Motion.Motion[g_Player.nMotionType].nNumKey;
			// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].frame;
		}
		break;
	}

	if (g_nCounterFrame == 0)
	{// �ŏ��̃t���[���ɂȂ�����A���̃L�[�Z�b�g�Ƃ̍����v�Z
		for (int nCntParts = 0; nCntParts < MAX_PLAYER; nCntParts++)
		{
			// �e�p�[�c�̈ʒu�̍��� = ([��]�̃L�[�Z�b�g�̊e�p�[�c�̈ʒu + �e�p�[�c�̏����I�t�Z�b�g[�ʒu]) - [����]�̊e�p�[�c�̈ʒu
			g_posDiff[nCntParts] = (g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].pos[nCntParts] +
				g_Motion.Offset[nCntParts].pos) - g_Player.aPlayerModel[nCntParts].pos;

			// �e�p�[�c�̌����̍��� = [��]�̃L�[�Z�b�g�̊e�p�[�c�̌��� + �e�p�[�c�̏����I�t�Z�b�g[����] - [����]�̊e�p�[�c�̌���
			g_RotDiff[nCntParts] = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].rot[nCntParts] +
				g_Motion.Offset[nCntParts].rot - g_Player.aPlayerModel[nCntParts].rot;

			// �������t���[�����Ŋ���
			/* �P�t���[��������̍��� = (�e�p�[�c�̈ʒu[x]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����,
			�e�p�[�c�̈ʒu[y]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����,
			�e�p�[�c�̈ʒu[z]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����)*/
			g_posDiff[nCntParts] = D3DXVECTOR3(g_posDiff[nCntParts].x / g_nMotionBlendFrame,
				g_posDiff[nCntParts].y / g_nMotionBlendFrame,
				g_posDiff[nCntParts].z / g_nMotionBlendFrame);

			g_RotDiff[nCntParts] = D3DXVECTOR3(g_RotDiff[nCntParts].x / g_nMotionBlendFrame,
				g_RotDiff[nCntParts].y / g_nMotionBlendFrame,
				g_RotDiff[nCntParts].z / g_nMotionBlendFrame);
		}
	}

	// ���[�V�����X�V
	for (int nCntParts = 0; nCntParts < MAX_PLAYER; nCntParts++)
	{
		g_Player.aPlayerModel[nCntParts].pos += g_posDiff[nCntParts];
		g_Player.aPlayerModel[nCntParts].rot += g_RotDiff[nCntParts];

		if (g_Player.aPlayerModel[nCntParts].rot.x > D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.x -= D3DX_PI * 2;
		}
		else if (g_Player.aPlayerModel[nCntParts].rot.x < -D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.x += D3DX_PI * 2;
		}
		if (g_Player.aPlayerModel[nCntParts].rot.y > D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.y -= D3DX_PI * 2;
		}
		else if (g_Player.aPlayerModel[nCntParts].rot.y < -D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.y += D3DX_PI * 2;
		}
		if (g_Player.aPlayerModel[nCntParts].rot.y > D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.z -= D3DX_PI * 2;
		}
		else if (g_Player.aPlayerModel[nCntParts].rot.z < -D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.z += D3DX_PI * 2;
		}
	}
	// �t���[�����̉��Z
	g_nCounterFrame++;

	if (g_Player.nNowFrame < g_Player.nFrameALL)
	{
		// ���݂̃t���[���������Z
		g_Player.nNowFrame++;
	}
}

//===============================================================================
// ���[�V�����̃t���[�����̌v�Z
//===============================================================================
void CulFrame(void)
{
	// ���݂̃t���[���������Z�b�g
	g_Player.nNowFrame = 0;

	// ���[�V�����̑��t���[���������Z�b�g
	g_Player.nFrameALL = 0;

	// ���[�V�����̑��t���[�������v�Z
	for (int nCntKey = 0; nCntKey < g_Motion.Motion[g_Player.nMotionType].nNumKey; nCntKey++)
	{
		g_Player.nFrameALL += g_Motion.Motion[g_Player.nMotionType].nKey[nCntKey].frame;
	}
}

//===============================================================================
// �v���C���[�̓ǂݍ���
//===============================================================================
void LoadPlayer(void)
{
	//�ǂݍ��񂾃��f���̏��̏�����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nText = 0; nText < MAX_CHAR; nText++)
		{
			g_LoadPlayer[nCntPlayer].pXFileName[nText] = NULL;		//�t�@�C����
		}
		g_LoadPlayer[nCntPlayer].pMesh = NULL;						//���b�V�����ւ̃|�C���^
		g_LoadPlayer[nCntPlayer].pBuffMat = NULL;					//�}�e���A�����ւ̃|�C���^
		g_LoadPlayer[nCntPlayer].NumMat = 0;						//�}�e���A���̐�
		g_LoadPlayer[nCntPlayer].pTexture = NULL;					//�e�N�X�`���ւ̃|�C���^
	}

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// ���f���̍ő吔
		g_Motion.Offset[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �I�t�Z�b�g[�ʒu]
		g_Motion.Offset[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �I�t�Z�b�g[����]
	}

	for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
	{// ���[�V�����̎��
		g_Motion.Motion[nCntMotion].nLoop;				// ���[�v��� [0 : ���[�v���Ȃ�, 1 : ���[�v����]
		g_Motion.Motion[nCntMotion].nNumKey = 0;		// �L�[��

														// �L�[���
		for (int nNumKeySet = 0; nNumKeySet < MAX_KEYSET; nNumKeySet++)
		{// �L�[�Z�b�g�̍ő吔
			g_Motion.Motion[nCntMotion].nKey[nNumKeySet].frame = 0;				// �t���[����
			for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
			{// ���f���̍ő吔
				g_Motion.Motion[nCntMotion].nKey[nNumKeySet].pos[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
				g_Motion.Motion[nCntMotion].nKey[nNumKeySet].rot[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
			}
		}
	}

	//#if 1
	// ���[�J���ϐ��錾
	FILE *pFile;				// �t�@�C���̃|�C���^
	char ReadText[256];			// �ǂݍ��񂾕���������Ă���
	char HeadText[256];			// ��r�p
	char DustBox[256];			// �g�p���Ȃ����̂����Ă���
	int nCntText = 0;			// ���f���t�@�C����
	int nCntModel = 0;			// ���f����
	int nCntMotion = 0;			// ���[�V������
	int nCntKeySet = 0;			// �L�[�Z�b�g��

								// �t�@�C���I�[�v��
	pFile = fopen(PLAYER_FILE, "r");		// �t�@�C�����J��[�ǂݍ��݌^]

	if (pFile != NULL)		// �t�@�C������ł͂Ȃ�
	{//�t�@�C�����J�����ꍇ
		while (strcmp(HeadText, "SCRIPT") != 0)
		{// "SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
		}

		if (strcmp(HeadText, "SCRIPT") == 0)
		{// "SCRIPT" ���ǂݎ�ꂽ�ꍇ�A�����J�n
			while (strcmp(HeadText, "END_SCRIPT") != 0)
			{// "END_SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);

				if (strcmp(HeadText, "\n") == 0)
				{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
				 //int nCnt = 0;
				}
				if (strcmp(HeadText, "NUM_MODEL") == 0)
				{// �ǂݍ��ރ��f���̍ő吔
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.nLoadParts);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// ���f���t�@�C����
					if (g_Player.nLoadParts > nCntText)
					{// �ő吔�ȏ㏈�����Ȃ�
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_LoadPlayer[nCntText].pXFileName[0]);
						nCntText++;
					}
				}
				else if (strcmp(HeadText, "CHARACTERSET") == 0)
				{
		//--- �L�����N�^�[��� ---//
					while (strcmp(HeadText, "END_CHARACTERSET") != 0)
					{// "END_CHARACTERSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "\n") == 0)
						{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
							int nCnt = 0;
						}

						else if (strcmp(HeadText, "MOVE") == 0)
						{// �ړ���
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.MoveSpeed);
						}
						else if (strcmp(HeadText, "pos") == 0)
						{// �ꏊ
							sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_Player.pos.x, &g_Player.pos.y, &g_Player.pos.z);
						}
						else if (strcmp(HeadText, "RADIUS") == 0)
						{// ���a
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.fRadius);
						}
						else if (strcmp(HeadText, "HEIGHT") == 0)
						{// ����
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.fHeight);
						}
						else if (strcmp(HeadText, "NUM_PARTS") == 0)
						{// �v���C���[�P�̂ɑ΂��郂�f���̎g�p��
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.nMaxParts);
						}

						g_Player.nMaxParts = 11;

						// ���f���̔z�u���
						if (strcmp(HeadText, "PARTSSET") == 0)
						{
							if (g_Player.nMaxParts > nCntModel)
							{
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{// "END_PARTSSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "INDEX") == 0)
									{// ����
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.aPlayerModel[nCntModel].nType);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{// �e�̃C���f�b�N�X
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.aPlayerModel[nCntModel].nIdxModelParent);
									}
									else if (strcmp(HeadText, "pos") == 0)
									{// �ʒu
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Player.aPlayerModel[nCntModel].pos.x,
											&g_Player.aPlayerModel[nCntModel].pos.y,
											&g_Player.aPlayerModel[nCntModel].pos.z);

										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Motion.Offset[nCntModel].pos.x,
											&g_Motion.Offset[nCntModel].pos.y,
											&g_Motion.Offset[nCntModel].pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{// ����
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Player.aPlayerModel[nCntModel].rot.x,
											&g_Player.aPlayerModel[nCntModel].rot.y,
											&g_Player.aPlayerModel[nCntModel].rot.z);
									}
								}
								nCntModel++;		// ���f������i�߂�
							}
						}
					}
				}

				// ���[�V�������
				else if (strcmp(HeadText, "MOTIONSET") == 0)
				{
					nCntModel = 0;		// ���f�����̃��Z�b�g

					while (strcmp(HeadText, "END_MOTIONSET") != 0)
					{// "END_MOTIONSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "LOOP") == 0)
						{// ���[�v���
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nLoop);
						}
						else if (strcmp(HeadText, "NUM_KEY") == 0)
						{// �L�[��
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nNumKey);
						}
						else if (strcmp(HeadText, "KEYSET") == 0)
						{// �L�[�Z�b�g
							while (strcmp(HeadText, "END_KEYSET") != 0)
							{// "END_KEYSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
								fgets(ReadText, sizeof(ReadText), pFile);
								sscanf(ReadText, "%s", &HeadText);

								if (strcmp(HeadText, "FRAME") == 0)
								{// �t���[����
									sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nKey[nCntKeySet].frame);
								}
								else if (strcmp(HeadText, "KEY") == 0)
								{// �L�[
									while (strcmp(HeadText, "END_KEY") != 0)
									{// "END_KEY" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
										fgets(ReadText, sizeof(ReadText), pFile);
										sscanf(ReadText, "%s", &HeadText);

										if (strcmp(HeadText, "pos") == 0)
										{// �ʒu
											sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].x,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].y,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].z);
										}
										else if (strcmp(HeadText, "ROT") == 0)
										{// ����
											sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].x,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].y,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].z);
										}
									}
									nCntModel++;		// ���f������i�߂�
								}
							}
							nCntKeySet++;		// �L�[�Z�b�g����i�߂�
							nCntModel = 0;		// ���f�����̃��Z�b�g
						}
					}
					nCntMotion++;			// ���[�V�����̎�ނ�i�߂�
					nCntKeySet = 0;			// �L�[�Z�b�g���̃��Z�b�g
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �J���Ȃ������ꍇ
		MessageBox(NULL, "�L�����N�^�[���t�@�C�����J���܂���ł����B", NULL, MB_OK);
	}
}
//===============================================================================
// �v���C���[�̎擾
//===============================================================================
PLAYER * GetPlayer(void)
{
	return &g_Player;
}
//=======================================================================================
// �p�[�e�B�N���֐�
//=======================================================================================
void MakeEffect_Player(void)
{
	int nCntItem = 0;
	//////////////////// �����̐ݒ� ////////////////////
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float fRadius = 10.0f;
	float fAngle = 0.0f;
	float fSpeed = 0.0f;
	int nLife = 70;
	////////////////////////////////////////////////////

		// 0�`3.14���o�� * (0 or 1)* -1�Ő��������߂�(�o���͈�)
		fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;	// �S�����o��

																				// �����ʒu
		D3DXVECTOR3 pos1 = D3DXVECTOR3(g_Player.pos.x+ rand() % 100-50.0f, g_Player.pos.y+rand() % 70, g_Player.pos.z+ rand() % 100 - 50.0f);

		// �o������
		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed, 0.0f);
		D3DXVECTOR3 move1 = D3DXVECTOR3(sinf(fAngle)*fSpeed, 0.0f, cosf(fAngle)*fSpeed);
		D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed);

		// �G�t�F�N�g�̐ݒ�
		SetEffect(pos1, move, fRadius, nLife, col, 1);
		SetEffect(pos1, move1, fRadius, nLife, col,1);
		SetEffect(pos1, move2, fRadius, nLife, col,1);
}