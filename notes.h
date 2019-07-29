//============================================
//  Notes.cpp�̃w�b�_�[�t�@�C��  (Notes.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _NOTES_H_
#define _NOTES_H_

//============================================
//
//   �萔�錾
//
//============================================
#define MAX_NOTES    (100)   // �m�[�c�̍ő吔
#define NOTES_WIDTH  (100.0f) // �m�[�c�̕�
#define NOTES_HEIGHT (100.0f) // �m�[�c�̕�

#define LINE_OBJ_MAX (4) // �P���C���̃I�u�W�F�N�g�̍ő吔

#define LINE_FD (SCREEN_HEIGHT / 3  - (SCREEN_HEIGHT / 100 * 6.0f))
#define LINE_HEIGHT (SCREEN_HEIGHT / 100 * 18.0f)
#define LINE_ONE	(LINE_FD)
#define LINE_TWO	(LINE_FD + LINE_HEIGHT)
#define LINE_THREE	(LINE_FD + LINE_HEIGHT * 2)
#define LINE_FOUR	(LINE_FD + LINE_HEIGHT * 3)

//============================================
//
//   �\����
//
//============================================
/* �m�[�c�̎�� */
typedef enum
{
	NOTES_NONE = 0,
	NOTES_ONE,
	NOTES_TWO,
	NOTES_THREE,
	NOTES_FOUR,
	NOTES_FIVE,
	NOTES_SIX,
	NOTES_SEVEN,
	NOTES_SEVEN_2,
	NOTES_MAX
}NOTES_MODE;

/* �m�[�c�\���� */
typedef struct
{
	NOTES_MODE nMode;              // �m�[�c�̎��
	D3DXVECTOR2    fPos;           // ���S���W
	D3DXVECTOR2    fUV;            // UV���W
	float          fWidth;         // ��
	float          fHeight;        // ����
	float          fFlame;         // UV�A�j���[�V�����̑�������
	int            nPoint;         // ���_
	bool           bMoveFlag;      // �ړ��t���O
	bool           bDrawFlag;      // �`��t���O
	bool           bUse;           // �g�p�t���O
	int            nNumHp;     // �e�̔ԍ�
	int            nLife;          // �̗�
	int            nParticleFlame; // �p�[�e�B�N���̂ł�t���[��
	int            nNumWarning;    // ���[�j���O�̔ԍ�
	int            nCntDamegeTime; // �U������
	bool           bAttack;        // �U���t���O
	bool           bUpdateFlag;    // �X�V�t���O
	int nNumLife;					// ���̗̑�

	int nTimeAttack;

	int nAnimTime;	// �A�j���[�V�����J�E���g

	int nStopTime;		// �~�܂�J�E���^�[
	bool bStop;			// �~�܂�t���O
	int nStopDamage;	// �~�܂������̃_���[�W

}NOTES;
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
HRESULT InitNotes   (void);
void    UninitNotes (void);
void    UpdateNotes (void);
void    DrawNotes   (void);
void    SetNotes    (float fPosX ,	   // ������WX
	float fPosY,					   // ������WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	NOTES_MODE nMode				   // ���
	);
NOTES*  GetNotes    (void);
bool    CheckEnemyTime(void);
void    AddDameage(int nID , int nDamege);
D3DXVECTOR3    GetEnemyPos(int n);
int GetTimeGameNow();
bool GetZeroNotes(void);	// �G�����ׂ�false�Ȃ�true,�����łȂ��Ȃ�false��Ԃ�

void StopDamage(int nIndex , int nDamage);

#endif //_NOTES_H_