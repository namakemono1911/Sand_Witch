//============================================
//  polygon.cpp�̃w�b�_�[�t�@�C��  (polygon.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N05��31��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _POLYGON_H_
#define _POLYGON_H_
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
#include "main.h"

//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
typedef struct
{
	bool bUse;			// �g�p
	int  nPos;			// �̗�
	int  nZanki;		// �c�@
	D3DXVECTOR3 fPos;	// ���ݍ��W
	D3DXVECTOR3 fMove;	// �ړ���
	D3DXVECTOR2 fSize;	// ���A����
	int  nMovePos;		// ���i�K�̍��W
}PLAYER;

#define PLAYER_POS_1 (SCREEN_HEIGHT / 100.0f * 23.6f + 15.0f)
#define PLAYER_POS_2 (SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT + 15.0f)
#define PLAYER_POS_3 (SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 2 + 15.0f)
#define PLAYER_POS_4 (SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 3 + 15.0f)
#define PLAYER_POS_5 (SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4 + 15.0f)
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

#endif