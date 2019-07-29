//============================================
//  BulletBoss.cpp�̃w�b�_�[�t�@�C��  (BulletBoss.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _BOSSBULLET_H_
#define _BOSSBULLET_H_

//============================================
//
//   �萔�錾
//
//============================================
#define MAX_BOSSBULLET (100) // �ő�{�X�̒e��

//============================================
//
//   �\����
//
//============================================
/* �{�X�̒e�̎�� */
typedef enum
{
	BOSSBULLET_NONE,
	BOSSBULLET_ONE,
	BOSSBULLET_TWO,
	BOSSBULLET_THREE,
	BOSSBULLET_MAX
}BOSSBULLET_TYPE;

/* �{�X�̒e�\���� */
typedef struct
{
	D3DXVECTOR2    fPos;    // ���S���W
	D3DXVECTOR2    fUV;     // UV���W
	float          fWidth;  // ��
	float          fHeight; // ����
	int            nFlame;  // UV�A�j���[�V�����̑�������
	bool           bUse;    // �g�p�t���O
	int            nLife;   // ����
	BOSSBULLET_TYPE       nType;   // ���
}BOSSBULLET;
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
HRESULT InitBulletBoss   (void);
void    UninitBulletBoss (void);
void    UpdateBulletBoss (void);
void    DrawBulletBoss   (void);
void    SetBulletBoss    (float fPosX , // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	BOSSBULLET_TYPE nType
	);
BOSSBULLET*    GetBulletBoss    (void);
void	AddDmgBulletBoss(int numBullet, int damage);

#endif //_BulletBoss_H_