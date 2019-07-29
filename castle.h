//============================================
//  castle.cpp�̃w�b�_�[�t�@�C��  (castle.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2017�N04��21��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _CASTLE_H_
#define _CASTLE_H_
//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include "main.h"

//============================================
//
//  �}�N����`
//
//============================================
#define CASTLE_NUM (1)	// ��̐�
#define CASTLE_POSX (SCREEN_WIDTH / 100.0f * 54)
#define CASTLE_POSY (SCREEN_HEIGHT / 100.0f * 6)
#define CASTLE_WIDTH (SCREEN_WIDTH / 100.0f * 8)
#define CASTLE_HEIGHT (SCREEN_HEIGHT / 100.0f * 10)

//============================================
//
//  �\����
//
//============================================
// ��\����
typedef struct
{
	bool bUse;	// �g�p�t���O
	D3DXVECTOR3 fPos;	// ���W
	D3DXVECTOR2 fSize;	// ������
	D3DXVECTOR2 fUV;	// UV
	int         nHp;	// HP
}CASTLE;


//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
void InitCastle(int nStage);
void UninitCastle(void);
void UpdateCastle(void);
void DrawCastle(void);
void AddDamegeCastle(int nDamege);
int GetCastleHp(void);
#endif // _CASTLE_H_