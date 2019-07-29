//============================================
//  Boss.cpp�̃w�b�_�[�t�@�C��  (Boss.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _BOSS_H_
#define _BOSS_H_

//============================================
//
//   �萔�錾
//
//============================================
#define MAX_BOSS    (4)   // �{�X�̍ő吔
#define BOSS_WIDTH  (100.0f) // �{�X�̕�
#define BOSS_HEIGHT (100.0f) // �{�X�̕�

#define LINE_OBJ_MAX (4) // �P���C���̃I�u�W�F�N�g�̍ő吔

//============================================
//
//   �\����
//
//============================================
/* �{�X�̎�� */
typedef enum
{
	BOSS_NONE = 0,
	BOSS_ONE,
	BOSS_TWO,
	BOSS_THREE,
	BOSS_MAX
}BOSS_MODE;

/* �{�X�\���� */
typedef struct
{
	BOSS_MODE nMode;              // �{�X�̎��
	D3DXVECTOR2    fPos;           // ���S���W
	D3DXVECTOR2    fUV;            // UV���W
	float          fWidth;         // ��
	float          fHeight;        // ����
	float          fFlame;         // UV�A�j���[�V�����̑�������
	bool           bMoveFlag;      // �ړ��t���O
	bool           bDrawFlag;      // �`��t���O
	bool           bUse;           // �g�p�t���O
	int            nNumHeart;     // �e�̔ԍ�
	int            nLife;          // �̗�
	int            nCntBullet;     // �e�̔���
	int            nCntBltTime;    // �e�����Ԋu
	D3DXVECTOR2    fSizeUV;        // UV��
	int            nNumNucleus[4];    // �j�̔ԍ�
	int            nNumNoMoveTime; // �ړ����Ȃ�
	int            nCntDamegeTime; // �U���Ԋu
	bool           bAttack;        // �U���t���O
	int nBossMode;			// 0:�j���[�g���� , 1:�U�� , 2����
	int nBossModeCount;	// ���̃��[�V�����܂ł̃J�E���g
	int nBossMotionCount;	// ���ݍĐ����Ă���L�[
}BOSS;
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
HRESULT InitBoss   (void);
void    UninitBoss (void);
void    UpdateBoss (void);
void    DrawBoss   (void);
void    SetBoss    (float fPosX ,	   // ������WX
	float fPosY ,	   // ������WX
BOSS_MODE nMode				   // ���
	);
BOSS*  GetBoss    (void);
void    AddDameageBoss(int nID , int nDamege);

#endif //_BOSS_H_