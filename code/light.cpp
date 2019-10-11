//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================
#include "light.h"
#include "camera.h"
//=============================================================================
// �}�N����`
//=============================================================================


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
D3DLIGHT9 g_light[3];//���C�g

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[3];

	for (int nCntHikari = 0; nCntHikari < 3; nCntHikari++)
	{

		// ���C�g���N���A����
		ZeroMemory(&g_light, sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		g_light[nCntHikari].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���C�g�̕����̐ݒ�
		vecDir[0] = D3DXVECTOR3(0.35f, -0.63f, 0.69f);
		vecDir[1] = D3DXVECTOR3(-0.72f, -0.52f, -0.46f);
		vecDir[2] = D3DXVECTOR3(-0.25f, 0.7f, -0.67f);
		//���K��

		D3DXVec3Normalize(&vecDir[nCntHikari], &vecDir[nCntHikari]);
		g_light[nCntHikari].Direction = vecDir[nCntHikari];
		
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntHikari, &g_light[nCntHikari]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntHikari, TRUE);

	}
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[3];
	CAMERA *pCamera;
	pCamera = GetCamera();
	for (int nCntHikari = 0; nCntHikari < 3; nCntHikari++)
	{
		if (pCamera->posV.y >= 300)
		{
			g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (pCamera->posV.y < 300)
		{
			g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_light[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);
			g_light[2].Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}
		//D3DXVec3Normalize(&vecDir[nCntHikari], &vecDir[nCntHikari]);//���K��
		//g_light[nCntHikari].Direction = vecDir[nCntHikari];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntHikari, &g_light[nCntHikari]);

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntHikari, &g_light[nCntHikari]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntHikari, TRUE);
	}
}

