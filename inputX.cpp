//============================================
//  inputX�֐�  (inputX.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2017�N04��27��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include "inputX.h"
#include <XInput.h>

#pragma comment (lib , "xinput.lib")

//============================================
//
//  �}�N����`
//
//============================================
#define NUM_XINPUT_KEY_MAX	(14)	// �L�[�ő吔
#define LIMIT_COUNT_REPEAT	(30)	// ���s�[�g�J�E���^

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
static XINPUT_STATE state;									// XInput���
// �C�P�����_�����Z����
static WORD g_aXInputKeyState[NUM_XINPUT_KEY_MAX];			// �L�[���[�N
static WORD g_aXInputKeyStateTrigger[NUM_XINPUT_KEY_MAX];	// �L�[�g���K�[���[�N
static WORD g_aXInputKeyStateRelease[NUM_XINPUT_KEY_MAX];	// �L�[�����[�X���[�N
static WORD g_aXInputKeyStateRepeat[NUM_XINPUT_KEY_MAX];	// ���s�[�g���[�N
static WORD g_aXInputKeyStatePress[NUM_XINPUT_KEY_MAX];		// �v���X���[�N
static int g_nXInputKeyStateRepeatCount[NUM_XINPUT_KEY_MAX];					// ���s�[�g�J�E���^

// bool �̐l����
static bool g_bXInputKeyState[2][NUM_XINPUT_KEY_MAX];			// �L�[���[�N
static bool g_bXInputKeyStateTrigger[2][NUM_XINPUT_KEY_MAX];	// �L�[�g���K�[���[�N
static bool g_bXInputKeyStateRelease[2][NUM_XINPUT_KEY_MAX];	// �L�[�����[�X���[�N
static bool g_bXInputKeyStateRepeat[2][NUM_XINPUT_KEY_MAX];		// ���s�[�g���[�N
static bool g_bXInputKeyStatePress[2][NUM_XINPUT_KEY_MAX];		// �v���X���[�N

// �{�^���}�X�N
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
//  ���O   InitXInput�֐�
//  ����   void
//  �߂�l void
//  ����   XInput�̏�����
//
//============================================
void InitXInput(void)
{
	DWORD dw;	// �G���[�`�F�b�N�p
	// �R���g���[���̐ڑ��m�F
	dw = XInputGetState( 0 , &state);

	if(dw != ERROR_SUCCESS)
	{
		//MessageBox(NULL , "�R���g���[���\���ڑ����Ă��܂���" , "ERROR" , MB_OK);
	} // EO if

	// �{�^���t���O�̏�����
	int i = 0;	// �J�E���^1
	int ii = 0;	// �J�E���^2

} // EO InitXInput

//============================================
//
//  ���O   UninitXInput�֐�
//  ����   void
//  �߂�l void
//  ����   XInput�̏I��
//
//============================================
void UninitXInput(void)
{
	XInputEnable(false);
} // EO UninitXInput

//============================================
//
//  ���O   UpdateXInput�֐�
//  ����   void
//  �߂�l void
//  ����   XInput�̍X�V
//
//============================================
void UpdateXInput(void)
{
	DWORD dw;	// �G���[�`�F�b�N�p
	// �R���g���[���̐ڑ��m�F
	dw = XInputGetState( 0 , &state);

	if(dw != ERROR_SUCCESS)
	{
		return;
	} // EO if

	// �L�[�`�F�b�N
	WORD aKeyState[NUM_XINPUT_KEY_MAX];

	for(int i = 0 ; i < NUM_XINPUT_KEY_MAX ; i++)
	{
		aKeyState[i] = state.Gamepad.wButtons;

		// �v���X
		g_aXInputKeyStatePress[i] = g_aXInputKeyState[i];

		// �g���K�[
		g_aXInputKeyStateTrigger[i] = (g_aXInputKeyState[i] ^ aKeyState[i]) & aKeyState[i];

		// �����[�X
		g_aXInputKeyStateRelease[i] = (g_aXInputKeyState[i] ^ aKeyState[i]) & g_aXInputKeyState[i];

		g_aXInputKeyState[i] =aKeyState[i];
	} // EO for




	//for(int nCnKey = 0; nCnKey < NUM_XINPUT_KEY_MAX; nCnKey++)
	//{
	//	//�L�[�g���K�[���̎擾
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

	//	// �L�[�v���X����ۑ�
	//	g_aXInputKeyState[nCnKey] = aKeyState[nCnKey];
	//}

	/*
	// �\���L�[��
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		g_
		MessageBox(NULL , "XINPUT_GAMEPAD_DPAD_UP" , "" ,  MB_OK); 
	} // EO if

	// �\���L�[��
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_DPAD_DOWN" , "" ,  MB_OK); 
	} // EO if

	// �\���L�[��
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_DPAD_LEFT" , "" ,  MB_OK); 
	} // EO if

	// �\���L�[�E
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

	// ���X�e�B�b�N��������
	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
	{
		MessageBox(NULL , "XINPUT_GAMEPAD_LEFT_THUMB" , "" ,  MB_OK); 
	} // EO if

	// �E�X�e�B�b�N��������
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
//  ���O   GetKeyXInputPress�֐�
//  ����   WORD
//  �߂�l bool
//  ����   XInput�̃L�[�v���X���
//
//============================================
bool GetKeyXInputPress(int nKey)
{
	return (g_aXInputKeyStatePress[nKey] & XINPUT_BUTTON_MASK[nKey]) ? true: false;
//	return false;
} // EO GetKeyXInputPress

//============================================
//
//  ���O   GetKeyXInputRelease�֐�
//  ����   WORD
//  �߂�l bool
//  ����   XInput�̃L�[�����[�X���
//
//============================================
bool GetKeyXInputRelease(int nkey)
{
	return (g_aXInputKeyStateRelease[nkey] & XINPUT_BUTTON_MASK[nkey]) ? true: false;
} // EO GetKeyXInputRelease

//============================================
//
//  ���O   GetKeyXInputTrigger�֐�
//  ����   WORD
//  �߂�l bool
//  ����   XInput�̃L�[�g���K�[���
//
//============================================
bool GetKeyXInputTrigger(int nkey)
{
	return (g_aXInputKeyStateTrigger[nkey] & XINPUT_BUTTON_MASK[nkey]) ? true: false;
} // EO GetKeyXInputTrigger

//============================================
//
//  ���O   GetKeyXInputRepeat�֐�
//  ����   WORD
//  �߂�l bool
//  ����    XInput�̃L�[���s�[�g���
//
//============================================
bool GetKeyXInputRepeat(int nkey)
{
	return (g_aXInputKeyStateRepeat[nkey] & XINPUT_BUTTON_MASK[nkey]) ? true: false;
} // EO GetKeyXInputRepeat
