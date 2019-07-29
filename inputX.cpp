//============================================
//  inputX関数  (inputX.cpp)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2017年04月27日
//  修正日   年月日
//  修正内容:
//
//
//============================================

//============================================
//
//  インクルードファイル
//
//============================================
#include "inputX.h"
#include <XInput.h>

#pragma comment (lib , "xinput.lib")

//============================================
//
//  マクロ定義
//
//============================================
#define NUM_XINPUT_KEY_MAX	(14)	// キー最大数
#define LIMIT_COUNT_REPEAT	(30)	// リピートカウンタ

//============================================
//
//  グローバル変数
//
//============================================
static XINPUT_STATE state;									// XInput情報
// イケメン論理演算くん
static WORD g_aXInputKeyState[NUM_XINPUT_KEY_MAX];			// キーワーク
static WORD g_aXInputKeyStateTrigger[NUM_XINPUT_KEY_MAX];	// キートリガーワーク
static WORD g_aXInputKeyStateRelease[NUM_XINPUT_KEY_MAX];	// キーリリースワーク
static WORD g_aXInputKeyStateRepeat[NUM_XINPUT_KEY_MAX];	// リピートワーク
static WORD g_aXInputKeyStatePress[NUM_XINPUT_KEY_MAX];		// プレスワーク
static int g_nXInputKeyStateRepeatCount[NUM_XINPUT_KEY_MAX];					// リピートカウンタ

// bool の人たち
static bool g_bXInputKeyState[2][NUM_XINPUT_KEY_MAX];			// キーワーク
static bool g_bXInputKeyStateTrigger[2][NUM_XINPUT_KEY_MAX];	// キートリガーワーク
static bool g_bXInputKeyStateRelease[2][NUM_XINPUT_KEY_MAX];	// キーリリースワーク
static bool g_bXInputKeyStateRepeat[2][NUM_XINPUT_KEY_MAX];		// リピートワーク
static bool g_bXInputKeyStatePress[2][NUM_XINPUT_KEY_MAX];		// プレスワーク

// ボタンマスク
static const unsigned int XINPUT_BUTTON_MASK[14] = {
	0x0001,
	0x0002,
	0x0004,
	0x0008,
	0x0010,
	0x0020,
	0x0040,
	0x0080,
	0x0100,
	0x0200,
	0x1000,
	0x2000,
	0x4000,
	0x8000
};


//============================================
//
//  名前   InitXInput関数
//  引数   void
//  戻り値 void
//  説明   XInputの初期化
//
//============================================
void InitXInput(void)
{
	DWORD dw;	// エラーチェック用
	// コントローラの接続確認
	dw = XInputGetState( 0 , &state);

	if(dw != ERROR_SUCCESS)
	{
		//MessageBox(NULL , "コントローラ―が接続していません" , "ERROR" , MB_OK);
	} // EO if

	// ボタンフラグの初期化
	int i = 0;	// カウンタ1
	int ii = 0;	// カウンタ2

} // EO InitXInput

//============================================
//
//  名前   UninitXInput関数
//  引数   void
//  戻り値 void
//  説明   XInputの終了
//
//============================================
void UninitXInput(void)
{
	XInputEnable(false);
} // EO UninitXInput

//============================================
//
//  名前   UpdateXInput関数
//  引数   void
//  戻り値 void
//  説明   XInputの更新
//
//============================================
void UpdateXInput(void)
{
	DWORD dw;	// エラーチェック用
	// コントローラの接続確認
	dw = XInputGetState( 0 , &state);

	if(dw != ERROR_SUCCESS)
	{
		return;
	} // EO if

	// キーチェック
	WORD aKeyState[NUM_XINPUT_KEY_MAX];

	for(int i = 0 ; i < NUM_XINPUT_KEY_MAX ; i++)
	{
		aKeyState[i] = state.Gamepad.wButtons;

		// プレス
		g_aXInputKeyStatePress[i] = g_aXInputKeyState[i];

		// トリガー
		g_aXInputKeyStateTrigger[i] = (g_aXInputKeyState[i] ^ aKeyState[i]) & aKeyState[i];

		// リリース
		g_aXInputKeyStateRelease[i] = (g_aXInputKeyState[i] ^ aKeyState[i]) & g_aXInputKeyState[i];

		g_aXInputKeyState[i] =aKeyState[i];
	} // EO for




	//for(int nCnKey = 0; nCnKey < NUM_XINPUT_KEY_MAX; nCnKey++)
	//{
	//	//キートリガー情報の取得
	//	g_aXInputKeyStateTrigger[nCnKey] = (g_aXInputKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
	//	g_aXInputKeyStateRelease[nCnKey] = (g_aXInputKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aXInputKeyState[nCnKey];


	//	if(aKeyState[nCnKey] & 0x80)
	//	{
	//		if(g_nXInputKeyStateRepeatCount[nCnKey] < LIMIT_COUNT_REPEAT)
	//		{
	//			g_nXInputKeyStateRepeatCount[nCnKey]++;
	//				
	//			if(g_aXInputKeyState[nCnKey] == 1 || g_nXInputKeyStateRepeatCount[nCnKey] >=  LIMIT_COUNT_REPEAT)
	//			{
	//				g_aXInputKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
	//			}
	//		}
	//		else
	//		{
	//			g_aXInputKeyStateRepeat[nCnKey] = 0;
	//		}
	//	}
	//	else
	//	{
	//		g_aXInputKeyStateRepeat[nCnKey] = 0;
	//		g_nXInputKeyStateRepeatCount[nCnKey] = 0;
	//	}

	//	// キープレス情報を保存
	//	g_aXInputKeyState[nCnKey] = aKeyState[nCnKey];
	//}

	/*
	// 十字キー上
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		g_
		MessageBox(NULL , "XINPUT_GAMEPAD_DPAD_UP" , "" ,  MB_OK); 
	} // EO if

	// 十字キー下
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_DPAD_DOWN" , "" ,  MB_OK); 
	} // EO if

	// 十字キー左
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_DPAD_LEFT" , "" ,  MB_OK); 
	} // EO if

	// 十字キー右
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_DPAD_RIGHT" , "" ,  MB_OK); 
	} // EO if

	// START
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_START" , "" ,  MB_OK); 
	} // EO if

	// BACK
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_BACK" , "" ,  MB_OK); 
	} // EO if

	// 左スティック押し込み
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_LEFT_THUMB" , "" ,  MB_OK); 
	} // EO if

	// 右スティック押し込み
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_RIGHT_THUMB" , "" ,  MB_OK); 
	} // EO if

	// L1
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_LEFT_SHOULDER" , "" ,  MB_OK); 
	} // EO if

	// R1
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_RIGHT_SHOULDER" , "" ,  MB_OK); 
	} // EO if

	// A
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_A" , "" ,  MB_OK); 
	} // EO if

	// B
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_B" , "" ,  MB_OK); 
	} // EO if

	// X
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_X" , "" ,  MB_OK); 
	} // EO if

	// Y
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_Y" , "" ,  MB_OK); 
	} // EO if

	*/
} // EO UpdateXInput

//============================================
//
//  名前   GetKeyXInputPress関数
//  引数   WORD
//  戻り値 bool
//  説明   XInputのキープレス情報
//
//============================================
bool GetKeyXInputPress(int nKey)
{
	return (g_aXInputKeyStatePress[nKey] & XINPUT_BUTTON_MASK[nKey]) ? true: false;
//	return false;
} // EO GetKeyXInputPress

//============================================
//
//  名前   GetKeyXInputRelease関数
//  引数   WORD
//  戻り値 bool
//  説明   XInputのキーリリース情報
//
//============================================
bool GetKeyXInputRelease(int nkey)
{
	return (g_aXInputKeyStateRelease[nkey] & XINPUT_BUTTON_MASK[nkey]) ? true: false;
} // EO GetKeyXInputRelease

//============================================
//
//  名前   GetKeyXInputTrigger関数
//  引数   WORD
//  戻り値 bool
//  説明   XInputのキートリガー情報
//
//============================================
bool GetKeyXInputTrigger(int nkey)
{
	return (g_aXInputKeyStateTrigger[nkey] & XINPUT_BUTTON_MASK[nkey]) ? true: false;
} // EO GetKeyXInputTrigger

//============================================
//
//  名前   GetKeyXInputRepeat関数
//  引数   WORD
//  戻り値 bool
//  説明    XInputのキーリピート情報
//
//============================================
bool GetKeyXInputRepeat(int nkey)
{
	return (g_aXInputKeyStateRepeat[nkey] & XINPUT_BUTTON_MASK[nkey]) ? true: false;
} // EO GetKeyXInputRepeat
