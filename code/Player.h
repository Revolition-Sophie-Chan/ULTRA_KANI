
//=============================================================================
//
// モデル処理 [player.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PLAYER	(11)//読み込むモデルの最大数
#define MAX_PARTS	(11)//表示するモデルの最大数
#define MAX_KEYSET	(5)//キーの最大数
#define MAX_CHAR	(51)//読み込むキャラ型のカズ

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	MOTION_NEUTRAL = 0,//ニュートラル
	MOTION_SWIM,
	MOTION_MOVE_TATE,
	MOTION_MOVE_YOKO,
	MOTION_MOVE_YOKO_ITEM,
	MOTION_MAX
}MOTIONTYPE;

//読み込んだモデルの構造体
typedef struct
{
	char				pXFileName[MAX_CHAR];	// ファイル名
	LPD3DXMESH			pMesh;					// メッシュ情報
	LPD3DXBUFFER		pBuffMat;				// マテリアル情報へのポイント
	DWORD				NumMat;					// マテリアルの数
	LPDIRECT3DTEXTURE9	*pTexture;				// テクスチャへのポイント
}LoadModel;

typedef struct
{
	D3DXMATRIX  mtxWorld;
	D3DXVECTOR3 pos;								// ポリゴンの位置
	D3DXVECTOR3 rot;								// ポリゴンの向き
	int nIdxModelParent;
	int nType;
}PLAYERMODEL;

typedef struct
{
	D3DXVECTOR3 pos;								// ポリゴンの位置
	D3DXVECTOR3 posOld;								// ポリゴンの位置
	D3DXVECTOR3 rot;								// ポリゴンの向き
	D3DXVECTOR3 move;								// ポリゴンの移動
	float		MoveSpeed;							// 移動量
	D3DXMATRIX  mtxWorld;							// ワールドマトリックス
	D3DXVECTOR3 vtxMinPlayer;						// 頂点座標の最小値
	D3DXVECTOR3 vtxMaxPlayer;						// 頂点座標の最大値
	float		fRadius;							// 半径
	float		fHeight;							// 高さ
	int			IdxLine;							// 線の使用番号 [インデックス]
	float		fDestAngle;							// 目的の向き
	int			hIdxShadow;							// 影の設定
	D3DXVECTOR3	size;
	bool Item;

	//モーション種類
	bool Wait;
	bool Swim;
	bool Move_TATE;
	bool Move_YOKO;
	bool Move_YOKO_ITEM;

	//<<モデル>>
	int		nLoadParts;								// 読み込むモデルの数
	int		nMaxParts;								// 使用するモデルの数
	PLAYERMODEL aPlayerModel[MAX_PLAYER];			//  モデルの情報

	//<<モーション>>
	MOTIONTYPE		nMotionTypeOld;					// 前モーションの種類
	MOTIONTYPE		nMotionType;					// モーションの種類
	int				nFrameALL;						// モーションの最大
	int				nNowFrame;

	D3DXVECTOR3 Diffrot;							// ポリゴンの向き
	bool bjump;

}PLAYER;

//モーションの構造体
typedef struct
{
	D3DXVECTOR3 pos;								// ポリゴンの位置
	D3DXVECTOR3 rot;								// ポリゴンの位置
}Offset;

//モーションの構造体
typedef struct
{
	int		frame;												// フレーム数
	D3DXVECTOR3 pos[MAX_PLAYER];								// ポリゴンの位置
	D3DXVECTOR3 rot[MAX_PLAYER];								// ポリゴンの位置
}KeySet;

typedef struct
{
	int		nLoop;				// ループ情報[0:ループしない,1:ループする]
	int		nNumKey;			// キー数
	KeySet	nKey[MAX_KEYSET];	// キー情報
}Motion;

typedef struct
{
	Motion Motion[MOTION_MAX];				// ループ情報[0:ループしない,1:ループする]
	Offset Offset[MAX_PLAYER];

}LoadMotion;

//=============================================================================
// プロトタイプ宣言
//==========================================================　===================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//モーション
void PlayerMotion(void);		// プレイヤーモーション
void CulFrame(void);			// フレーム計算

								// プレイヤ情報の読み込み
void LoadPlayer(void);

//プレイヤ-の情報
PLAYER *GetPlayer(void);


void MakeEffect_Player(void);

#endif