//============================================
//  gate.cpp�̃w�b�_�[�t�@�C��  (gate.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2017�N04��21��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _GATE_H_
#define _GATE_H_
//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include "main.h"
#include "polygon.h"

//============================================
//
//  �}�N����`
//
//============================================
#define GATE_NUM (4)	// ��̐�
#define POSX (150.0f)

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
	bool        bCol;	// �Փ�flag
	int nHeart;
	TEXTURE tex;
}GATE;


//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
void InitGate(void);
void UninitGate(void);
void UpdateGate(void);
void DrawGate(void);
GATE* GetGate(void);
void AddLife(int nIdx , int nLife);
#endif // _GATE_H_