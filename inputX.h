//============================================
//  inputX.cppのヘッダーファイル  (inputX.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2017年04月27日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _INPUTX_H_
#define _INPUTX_H_
//============================================
//
//  マクロ定義
//
//============================================

//============================================
//
//  インクルードファイル
//
//============================================
#include <Windows.h>

//============================================
//
//  構造体
//
//============================================
// XInputボタン列挙型
typedef enum
{
	XINPUT_DPAD_UP = 0,
	XINPUT_DPAD_DOWN,
	XINPUT_DPAD_LEFT,
	XINPUT_DPAD_RIGHT,
	XINPUT_START,
	XINPUT_BACK,
	XINPUT_LEFT_THUMB,
	XINPUT_RIGHT_THUMB,
	XINPUT_LEFT_SHOULDER,
	XINPUT_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y
}XINPUT_BUTTON;

//============================================
//
//   プロトタイプ宣言
//
//============================================
void InitXInput(void);
void UninitXInput(void);
void UpdateXInput(void);
bool GetKeyXInputPress(int nkey);
bool GetKeyXInputRelease(int nkey);
bool GetKeyXInputTrigger(int nkey);
bool GetKeyXInputRepeat(int nkey);

#endif // _XINPUT_H_
