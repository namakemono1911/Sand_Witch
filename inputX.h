//============================================
//  inputX.cpp�̃w�b�_�[�t�@�C��  (inputX.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2017�N04��27��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _INPUTX_H_
#define _INPUTX_H_
//============================================
//
//  �}�N����`
//
//============================================

//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include <Windows.h>

//============================================
//
//  �\����
//
//============================================
// XInput�{�^���񋓌^
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
//   �v���g�^�C�v�錾
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
