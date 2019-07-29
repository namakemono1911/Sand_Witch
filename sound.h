//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	//SE/////////////////////////
	SELECT_TITLE = 0,
	CURSOR,
	DECISITON,
	SELECT_STAGE,

	//BGM////////////////////////
	TITLE_BGM,
	GAME_BGM_01,
	RESULT_BGM,

	// BGM
	BGM_TITLE,			// �^�C�g��BGM
	BGM_STAGESELECT,	// �X�e�[�W�Z���N�gBGM
	BGM_GAME,			// �Q�[��BGM
	BGM_RESULT,			// ���U���gBGM

	// SE
	// Title
	SE_PUSH,	// ���艹

	// StageSelect
	SE_STAGESELECT_PUSH,	// ���艹
	SE_STAGESELECT_CORSOR,	// �J�[�\���ړ�
	SE_STAGESELECT_CANCEL,	// �L�����Z��

	// Game
	/*�v���C���[*/
	SE_GAME_WIN,						// ����
	SE_GAME_LOSE,						// ����
	SE_GAME_PLAEYR_FOOT_VILLEGE,		// �����[��
	SE_GAME_PLAEYR_FOOT_VOLCANO,		// �����[�ΎR
	SE_GAME_PLAEYR_FOOT_SNOW,			// �����[��R

	/*���@*/
	SE_GAME_MAGIC_GO,				// ���@����-����
	SE_GAME_MAGIC_GO_BOMM,			// ���@����-�{��
	SE_GAME_MAGIC_GO_DIFISION,		// ���@����-�g�U
	SE_GAME_MAGIC_ON,				// ���@����-����
	SE_GAME_MAGIC_ON_BOMM,			// ���@����-�{��
	SE_GAME_MAGIC_ON_DIFISION,		// ���@����-�g�U
	SE_GAME_MAGIC_ON_KILL,			// ���@����-�K�E�Z
	/*�G*/
	SE_GAME_ENEMY_KILL_SURAIMU,		// �E-�X���C��
	SE_GAME_ENEMY_KILL_GOREMU,		// �E-�S�[����
	SE_GAME_ENEMY_KILL_PANSER,		// �E-�p���T�[
	/*��*/
	SE_GAME_GATE_BREAK,			// �傪��ꂿ�����
	SE_GAME_GATE_BREAK_ALL,		// �傪��ꂿ������A���S��
	/*��*/
	SE_GAME_CASTLE_BREAK,			// �邪��ꂿ�����
	SE_GAME_CASTLE_BREAK_ALL,		// �邪��ꂿ������A���S��
	// Result
	SE_RESULT_NUMBER,		// �h����
	SE_RESULT_NUMBER_ON,	// ��������
	SE_RESULT_RANK_C,		// �����Nc
	SE_RESULT_RANK_B,		// �����Nb
	SE_RESULT_RANK_A,		// �����Na
	SE_RESULT_RANK_S,		// �����Ns
	
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
