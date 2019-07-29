//============================================
//  stage.cpp�̃w�b�_�[�t�@�C��  (stage.h)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   �N����
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _STAGE_H_
#define _STAGE_H_
//============================================
//
//  �}�N����`
//
//============================================


//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================


//============================================
//
//  �\����
//
//============================================
typedef enum
{
	STAGE_00 = 0,		//�`���[�g���A��
	STAGE_01,			//��-easy
	STAGE_02,			//��-normal
	STAGE_03,			//��-hard
	STAGE_04,			//�ΎR-easy
	STAGE_05,			//�ΎR-norm
	STAGE_06,			//�ΎR-hard
	STAGE_07,			//��R-easy
	STAGE_08,			//��R-norm
	STAGE_09,			//��R - hard
	STAGE_NUM_MAX,		//�X�e�[�W�̑���
}STAGE_NUM;



//============================================
//
//   �v���g�^�C�v�錾
//
//============================================
// �����_���Ŏ��s(�X�R�A�Ō���)
void SetStage00(void);	// �`���[�g���A��
void SetStage01(void);	// ��-easy
void SetStage02(void);	// ��-normal
void SetStage03(void);	// ��-hard
void SetStage04(void);	// �ΎR-easy
void SetStage05(void);	// �ΎR-normal
void SetStage06(void);	// �ΎR-hard
void SetStage07(void);	// ��R-easy
void SetStage08(void);	// ��R-normal
void SetStage09(void);	// ��R-hard

STAGE_NUM getStgNum(void);	//�X�e�[�W�i���o�[�擾
void setStgNum(STAGE_NUM stage);	//�X�e�[�W�i���o�[�ݒ�
void resetStgNum(void);	//�X�e�[�W�i���o�[������

int GetTimeGame(int nStage);
void ReStage(void); // �X�e�[�W��init�ŌĂ��

#endif