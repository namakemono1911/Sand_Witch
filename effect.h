//============================================
//  Effect.cpp�̃w�b�_�[�t�@�C��  (Effect.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _EFECT_H_
#define _EFECT_H_

#include "polygon.h"

//============================================
//
//   �萔�錾
//
//============================================
#define MAX_EFECT    (100)   // �m�[�c�̍ő吔
#define EFECT_WIDTH  (100.0f) // �m�[�c�̕�
#define EFECT_HEIGHT (100.0f) // �m�[�c�̕�

//============================================
//
//   �\����
//
//============================================
/* �m�[�c�̎�� */
typedef enum
{
	EFFECT_RECOVER,					// ��Ə��				��or��
	EFFECT_KILL,					// �K�E�Z�����܂�			��
	EFFECT_KILL_ON,					// �K�E�Z�����܂�؂�����	�E�B�b�`(�v���C���[)
	EFFECT_MAGIC_ON_NORMAL_1,		// ���@����-1				�G
	EFFECT_MAGIC_ON_NORMAL_2,		// ���@����-2				�G
	EFFECT_MAGIC_ON_EXPLOSION_1,	// ���@����-����-1			�G
	EFFECT_MAGIC_ON_EXPLOSION_2,	// ���@����-����-2			�G
	EFFECT_MAGIC_ON_EXPLOSION_3,	// ���@����-����-3			�G
	EFFECT_MAX
}EFFECT_MODE;


/* �m�[�c�\���� */
typedef struct
{
	bool bUse;
	EFFECT_MODE nMode;              // �m�[�c�̎��
	int nAnimFlame;					// �A�j���[�V�����Ԋu �v���W
	int nAnimFlameMax;					// �A�j���[�V�����Ԋu
	int nAnimFlameBuf;					// �A�j���[�V�����Ԋu 4�Ԗڗp
	TEXTURE tex;
	POLYGON poly;
	float fAlpha;
	float fAlphaDif;
	bool bAnim;
}EFFECT;

//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
HRESULT InitEffect   (void);
void    UninitEffect (void);
void    UpdateEffect (void);
void    DrawEffect   (void);
void    SetEffect    (float fPosX ,	   // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	EFFECT_MODE nMode				   // ���
	);

#endif //_EFECT_H_