//============================================
//  Heart.cpp�̃w�b�_�[�t�@�C��  (Heart.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _HEART_H_
#define _HEART_H_
#include "main.h"

//============================================
//
//   �萔�錾
//
//============================================
#define MAX_HEART    (100)   // �n�[�g�̍ő吔
#define HEART_WIDTH  (20.0f) // �n�[�g�̕�
#define HEART_HEIGHT (100.0f) // �n�[�g�̕�

//============================================
//
//   �\����
//
//============================================
/* �n�[�g�\���� */
typedef struct
{
	D3DXVECTOR2    fPos;           // ���S���W
	D3DXVECTOR2    fUV;            // UV���W
	D3DXVECTOR2    fUVSize;            // UV���W
	float          fWidth;         // ��
	float          fHeight;        // ����
	bool           bUse;           // �g�p�t���O
}HEART;
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
HRESULT InitHeart   (void);
void    UninitHeart (void);
void    UpdateHeart (void);
void    DrawHeart   (void);
int     SetHeart    (float fPosX ,	   // ������WX
	float fPosY,					   // ������WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	int nHp
	);
HEART*  GetHeart    (void);
void SetPosHeart (int nIdx , D3DXVECTOR2 fPos);	// ���W
void SetUVSizeHeart(int nIdx , int nLife);	// ���C�t����uv�v�Z
void OffHeart(int nIdx);
#endif //_HEART_H_