//============================================
//  Human.cpp�̃w�b�_�[�t�@�C��  (Human.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _HUMAN_H_
#define _HUMAN_H_

//============================================
//
//   �萔�錾
//
//============================================
#define MAX_HUMAN    (100)   // �l�̍ő吔
#define HUMAN_WIDTH  (100.0f) // �l�̕�
#define HUMAN_HEIGHT (100.0f) // �l�̕�

//============================================
//
//   �\����
//
//============================================
/* �l�̎�� */
typedef enum
{
	HUMAN_NONE = 0,
	HUMAN_ONE,
	HUMAN_TWO,
	HUMAN_THREE,
	HUMAN_FOUR,
	HUMAN_FIVE,
	HUMAN_SIX,
	HUMAN_SEVEN,
	HUMAN_SEVEN_2,
	HUMAN_MAX
}HUMAN_MODE;

/* �l�\���� */
typedef struct
{
	HUMAN_MODE nMode;              // �l�̎��
	D3DXVECTOR2    fPos;           // ���S���W
	D3DXVECTOR2    fUV;            // UV���W
	float          fWidth;         // ��
	float          fHeight;        // ����
	float          fFlame;         // UV�A�j���[�V�����̑�������
	int            nPoint;         // ���_
	bool           bMoveFlag;      // �ړ��t���O
	bool           bDrawFlag;      // �`��t���O
	bool           bUse;           // �g�p�t���O
	int            nNumShadow;     // �e�̔ԍ�
	int            nLife;          // �̗�
	int            nParticleFlame; // �p�[�e�B�N���̂ł�t���[��
	int            nNumWarning;    // ���[�j���O�̔ԍ�
	int            nCntDamegeTime; // �U������
	bool           bAttack;        // �U���t���O
	bool           bUpdateFlag;    // �X�V�t���O
	int            nCntAnim;         // ���_

	float fAlpha;
	bool bAlpha;
}HUMAN;
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
HRESULT InitHuman   (void);
void    UninitHuman (void);
void    UpdateHuman (void);
void    DrawHuman   (void);
void    SetHuman    (float fPosX ,	   // ������WX
	float fPosY,					   // ������WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	HUMAN_MODE nMode				   // ���
	);
HUMAN*  GetHuman    (void);
bool    CheckHumanTime(void);
void    AddDameageHuman(int nID , int nDamege);
D3DXVECTOR3    GetHumanPos(int n);
#endif //_HUMAN_H_