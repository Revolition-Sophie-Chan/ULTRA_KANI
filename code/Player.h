
//=============================================================================
//
// ���f������ [player.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER	(11)//�ǂݍ��ރ��f���̍ő吔
#define MAX_PARTS	(11)//�\�����郂�f���̍ő吔
#define MAX_KEYSET	(5)//�L�[�̍ő吔
#define MAX_CHAR	(51)//�ǂݍ��ރL�����^�̃J�Y

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	MOTION_NEUTRAL = 0,//�j���[�g����
	MOTION_SWIM,
	MOTION_MOVE_TATE,
	MOTION_MOVE_YOKO,
	MOTION_MOVE_YOKO_ITEM,
	MOTION_MAX
}MOTIONTYPE;

//�ǂݍ��񂾃��f���̍\����
typedef struct
{
	char				pXFileName[MAX_CHAR];	// �t�@�C����
	LPD3DXMESH			pMesh;					// ���b�V�����
	LPD3DXBUFFER		pBuffMat;				// �}�e���A�����ւ̃|�C���g
	DWORD				NumMat;					// �}�e���A���̐�
	LPDIRECT3DTEXTURE9	*pTexture;				// �e�N�X�`���ւ̃|�C���g
}LoadModel;

typedef struct
{
	D3DXMATRIX  mtxWorld;
	D3DXVECTOR3 pos;								// �|���S���̈ʒu
	D3DXVECTOR3 rot;								// �|���S���̌���
	int nIdxModelParent;
	int nType;
}PLAYERMODEL;

typedef struct
{
	D3DXVECTOR3 pos;								// �|���S���̈ʒu
	D3DXVECTOR3 posOld;								// �|���S���̈ʒu
	D3DXVECTOR3 rot;								// �|���S���̌���
	D3DXVECTOR3 move;								// �|���S���̈ړ�
	float		MoveSpeed;							// �ړ���
	D3DXMATRIX  mtxWorld;							// ���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMinPlayer;						// ���_���W�̍ŏ��l
	D3DXVECTOR3 vtxMaxPlayer;						// ���_���W�̍ő�l
	float		fRadius;							// ���a
	float		fHeight;							// ����
	int			IdxLine;							// ���̎g�p�ԍ� [�C���f�b�N�X]
	float		fDestAngle;							// �ړI�̌���
	int			hIdxShadow;							// �e�̐ݒ�
	D3DXVECTOR3	size;
	bool Item;

	//���[�V�������
	bool Wait;
	bool Swim;
	bool Move_TATE;
	bool Move_YOKO;
	bool Move_YOKO_ITEM;

	//<<���f��>>
	int		nLoadParts;								// �ǂݍ��ރ��f���̐�
	int		nMaxParts;								// �g�p���郂�f���̐�
	PLAYERMODEL aPlayerModel[MAX_PLAYER];			//  ���f���̏��

	//<<���[�V����>>
	MOTIONTYPE		nMotionTypeOld;					// �O���[�V�����̎��
	MOTIONTYPE		nMotionType;					// ���[�V�����̎��
	int				nFrameALL;						// ���[�V�����̍ő�
	int				nNowFrame;

	D3DXVECTOR3 Diffrot;							// �|���S���̌���
	bool bjump;

}PLAYER;

//���[�V�����̍\����
typedef struct
{
	D3DXVECTOR3 pos;								// �|���S���̈ʒu
	D3DXVECTOR3 rot;								// �|���S���̈ʒu
}Offset;

//���[�V�����̍\����
typedef struct
{
	int		frame;												// �t���[����
	D3DXVECTOR3 pos[MAX_PLAYER];								// �|���S���̈ʒu
	D3DXVECTOR3 rot[MAX_PLAYER];								// �|���S���̈ʒu
}KeySet;

typedef struct
{
	int		nLoop;				// ���[�v���[0:���[�v���Ȃ�,1:���[�v����]
	int		nNumKey;			// �L�[��
	KeySet	nKey[MAX_KEYSET];	// �L�[���
}Motion;

typedef struct
{
	Motion Motion[MOTION_MAX];				// ���[�v���[0:���[�v���Ȃ�,1:���[�v����]
	Offset Offset[MAX_PLAYER];

}LoadMotion;

//=============================================================================
// �v���g�^�C�v�錾
//==========================================================�@===================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//���[�V����
void PlayerMotion(void);		// �v���C���[���[�V����
void CulFrame(void);			// �t���[���v�Z

								// �v���C�����̓ǂݍ���
void LoadPlayer(void);

//�v���C��-�̏��
PLAYER *GetPlayer(void);


void MakeEffect_Player(void);

#endif