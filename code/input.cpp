//=============================================================================
//
// 入力処理 [input.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#include"input.h"
#include"main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	NUM_KEY_MAX			(256)	// キーの最大数

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECTINPUT8 g_pInput = NULL;//
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//
BYTE g_aKeyState[NUM_KEY_MAX];//
BYTE g_aKeyStateTrigger[256];//単発
BYTE g_aKeyStateRelease[256];//溜め

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	
	// 入力デバイス（キーボード）の作成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	
	// データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	// 入力デバイス(キーボード)の開放
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//キーのアクセス権
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	
	// DirectInputオブジェクトの開放
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//
	int nCntkey;
	
	// デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKeyStateTrigger[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & aKeyState[nCntkey];
			g_aKeyState[nCntkey] = aKeyState[nCntkey];//
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//
	}		
}

//=============================================================================
//　プレス処理
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// トリガー処理
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
