//============================================
//  Warning.c�̃w�b�_�[�t�@�C��  (Warning.h)
//
//  Author  InformaWarningon
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N06��29��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _WARNING_H_
#define _WARNING_H_
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
/*���[�j���O�^�C�v�񋓌^*/
typedef enum 
{
	WARNING_NORMAL = 0,
	WARNING_BOSS
}WARNING_TYPE;
/* ���[�j���O�\���� */
typedef struct
{
	bool bUse;            // �g�p�t���O
	D3DXVECTOR2 fPos;     // �ꏊ
	bool bFlash;          // �_�Ńt���O
	int  nMaxFlash;       // �_�Ő؂�ւ��t���[��(���t���[���Ń���0�ɂȂ邩)
	int  nCntflash;       // �_�ŃJ�E���g(�����t���[����)
	float fAlpha;         // ���l
	WARNING_TYPE type;
}WARNING;
//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
HRESULT InitWarning(void);
void UninitWarning(void);
void UpdateWarning(void);
void DrawWarning(void);
int  SetWarning(float fPosY , WARNING_TYPE type); // ���[�j���O���Z�b�g����
void OffWarning(int nIndex);
#endif//_Warning_H_