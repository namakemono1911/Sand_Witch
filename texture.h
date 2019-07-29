//============================================
//  texture.cpp�̃w�b�_�[�t�@�C��  (texture.h)
//
//  Author  Information
//  ���O  ���쏫�P
//  �쐬��   2016�N08��25��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================

//============================================
//
//  �\���̒�`
//
//============================================
// �e�N�X�`�����̍\����
typedef struct
{
	char aName[128];		// ���O
	float fPosX;			// �ʒuX
	float fPosY;			// �ʒuY
	float fWidth;			// ��
	float fHeight;			// ����
	float fTposu;			// U�l
	float fTposv;			// V�l
	float fTwidth;			// UV�l�̕�
	float fTheight;			// UV�l�̍���
	bool  bUse;				// �g�p�t���O
	int   nLayer;           // ���Ԗڂɕ`�悷�邩
}TEXTURE_a;

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT InitTexture(void);		// ������
void UninitTexture(void);		// �I��
void UpdateTexture(void);		// �X�V
void DrawTexture(int nLayer);			// �`��
void SetTexture(int nTextureIndex, float fPosX, float fPosY, float fWidth, float fHeight,
	float fTposu, float fTposv, float fTwidth, float fTheight , int nLayer);					// �e�N�X�`���ݒ�
void OffTexture(int nIndex);													// �w�肵���|���S����j��
void AllOffTexture(void);													// �w�肵���|���S����j��
void MovePosTexture(int nIndex , float fMoveX , float fMoveY);					// �e�N�X�`���̃|�W�V�����ړ�
void MoveUVTexture(int nIndex , float fMoveU , float fMoveV);					// �e�N�X�`����UV�ړ�
float GetTexturePosX(int nIndex);												// X���W�̎擾
float GetTexturePosY(int nIndex);												// Y���W�̎擾
void SetPosTexture(int nIndex , float fMoveX , float fMoveY);					// �e�N�X�`���̃|�W�V���w��
void SetUVTexture(int nIndex , float fMoveU , float fMoveV);					// �e�N�X�`����UV�w��
void SetColorTexture(int nIndex , float r , float g , float b , float alpha);			// �e�N�X�`���̐F�w��
TEXTURE_a* GetTexture(int nIndex);
#endif _TEXTURE_H_