//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POLYGON_SPD (4)
#define ROLL_SPD (0.3f)
#define CAMERA_Y (150.0f)
#define CAMERA_Z (-500.0f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CAMERA g_camera;//�J�������
float g_fLength;

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	g_camera.posV = D3DXVECTOR3(0.0f, CAMERA_Y, CAMERA_Z);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = 0.0f;

	D3DXVECTOR3 g_fLength = g_camera.posV - g_camera.posR;

	g_camera.fDistance = sqrtf(g_fLength.y * g_fLength.y + g_fLength.z * g_fLength.z);

	//g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y)*g_fLength;
	//g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y)*g_fLength;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{

	PLAYER *pPlayer;
	pPlayer = GetPlayer();


	if (GetMode() == MODE_TITLE|| GetMode() == MODE_RESULT)
	{
		g_camera.rot.y += 0.005f;
	}
	else if(GetMode() == MODE_GAME || GetMode() == MODE_TUTORIAL)
	{
		//�����_�𒍖ڂ��ăJ��������]
		if (GetKeyboardPress(DIK_LEFT))
		{
			g_camera.rot.y -= 0.05f;
			pPlayer->rot.y = g_camera.rot.y;
		}

		if (GetKeyboardPress(DIK_RIGHT))
		{
			g_camera.rot.y += 0.05f;
			pPlayer->rot.y = g_camera.rot.y;
		}
	}

		g_camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y)*ROLL_SPD;
		g_camera.posRDest.y = pPlayer->pos.y + 0.0f;
		g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y)*ROLL_SPD;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posVDest.y = pPlayer->pos.y + CAMERA_Y;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y)*g_camera.fDistance;

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x)*ROLL_SPD;
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y)*ROLL_SPD;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z)*ROLL_SPD;
		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x)*ROLL_SPD;
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y)*ROLL_SPD;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z)*ROLL_SPD;
	}
	

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH/ (float)SCREEN_HEIGHT,
		10.0f,
		7000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void)
{
	return &g_camera;
}
