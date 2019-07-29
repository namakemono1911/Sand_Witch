//============================================
//  NucleusBoss.cpp�̃w�b�_�[�t�@�C��  (NucleusBoss.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _BOSSNUCLEUS_H_
#define _BOSSNUCLEUS_H_

//============================================
//
//   �萔�錾
//
//============================================
#define MAX_BOSSNUCLEUS (100) // �ő�{�X�̒e��

//============================================
//
//   �\����
//
//============================================
/* �{�X�̒e�̎�� */
typedef enum
{
	BOSSNUCLEUS_NONE,
	BOSSNUCLEUS_ONE,
	BOSSNUCLEUS_TWO,
	BOSSNUCLEUS_THREE,
	BOSSNUCLEUS_MAX
}BOSSNUCLEUS_TYPE;

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
	bool           bDraw;   // �`��t���O
	int            nDrawTime; // �`�掞��
	BOSSNUCLEUS_TYPE       nType;   // ���
}BOSSNUCLEUS;
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
HRESULT InitNucleusBoss   (void);
void    UninitNucleusBoss (void);
void    UpdateNucleusBoss (void);
void    DrawNucleusBoss   (void);
int     SetNucleusBoss    (float fPosX , // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	BOSSNUCLEUS_TYPE nType
	);
void SetPosNucleusBoss(int nIndex , D3DXVECTOR2 fPos);
void OffDrawNucleusBoss(int nIndex);
void OnDrawNucleusBoss(int nIndex , int nTime);
void ReleaseNucleusBoss(int nIdx);
void OffNucleusBoss(int nIndex);
BOSSNUCLEUS*    GetNucleusBoss    (void);
void AddDmgNucBoss(int damage, int num);

#endif //_NucleusBoss_H_