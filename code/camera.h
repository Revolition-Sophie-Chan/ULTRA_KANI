//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// カメラの構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;			//移動
	D3DXVECTOR3 rot;			//回転
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	float fDistance;

}CAMERA;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
CAMERA *GetCamera(void);
#endif
