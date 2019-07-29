//==========================================================================================
//	�X�e�[�W�Z���N�g����[stageselect.cpp]
//	Author : KAZUNORI MARUHASHI
//
//	Update :
//		YYYY/MM/DD	Updater :
//
//		2017/06/04	Updater : KAZUNORI MARUHASHI
//			
//			
//	
//==========================================================================================
#ifndef _STAGESELECT_H_	//��d�C���N���[�h�h�~
#define _STAGESELECT_H_

//==========================================================================================
//	�C���N���[�h�t�@�C��
//==========================================================================================
//����w�b�_

//�V�K�w�b�_
#include "main.h"

//==========================================================================================
//	�\���̒�`
//==========================================================================================
typedef enum
{
	STAGESELECT_TEX_TITLE = 0,		//�X�e�[�W�Z���N�g����
	STAGESELECT_TEX_TURORIAL,		//�`���[�g���A��
	STAGESELECT_TEX_STAGE1,			//���A�C�R��
	STAGESELECT_TEX_STAGE2,			//��R�A�C�R��
	STAGESELECT_TEX_STAGE3,			//�ΎR�A�C�R��
	STAGESELECT_TEX_CURSOL,			//�X�e�[�W�J�[�\��
	STAGESELECT_TEX_STAGE1DIF1,		//����Փx��
	STAGESELECT_TEX_STAGE1DIF2,		//����Փx��
	STAGESELECT_TEX_STAGE1DIF3,		//����Փx��
	STAGESELECT_TEX_STAGE2DIF1,		//��R��Փx��
	STAGESELECT_TEX_STAGE2DIF2,		//��R��Փx��
	STAGESELECT_TEX_STAGE2DIF3,		//��R��Փx��
	STAGESELECT_TEX_STAGE3DIF1,		//�ΎR��Փx��
	STAGESELECT_TEX_STAGE3DIF2,		//�ΎR��Փx��
	STAGESELECT_TEX_STAGE3DIF3,		//�ΎR��Փx��
	STAGESELECT_TEX_DIFCURSOL,		//��Փx�J�[�\��

	STAGESELECT_TEX_BG_STAGE1,			//���A�C�R��
	STAGESELECT_TEX_BG_STAGE2,			//��R�A�C�R��
	STAGESELECT_TEX_BG_STAGE3,			//�ΎR�A�C�R��

	STAGESELECT_TEX_MAX,			//���U���g�e�N�X�`������
} STAGESELECT_TEX_LABEL;	//�e�N�X�`���p���x��

typedef enum
{
	STAGESELECT_OBJ_BG = 0,		//�w�i�摜
	STAGESELECT_OBJ_BGFADE,		//�w�i�摜�t�F�[�h
	STAGESELECT_OBJ_TITLE,		//�X�e�[�W�Z���N�g����
	STAGESELECT_OBJ_TURORIAL,	//�`���[�g���A��
	STAGESELECT_OBJ_STAGE1,		//���A�C�R��
	STAGESELECT_OBJ_STAGE2,		//��R�A�C�R��
	STAGESELECT_OBJ_STAGE3,		//�ΎR�A�C�R��
	STAGESELECT_OBJ_CURSOL,		//�X�e�[�W�J�[�\��
	STAGESELECT_OBJ_DIFCURSOL,	//��Փx�J�[�\��
	STAGESELECT_OBJ_STAGE1DIF1,	//����Փx��
	STAGESELECT_OBJ_STAGE1DIF2,	//����Փx��
	STAGESELECT_OBJ_STAGE1DIF3,	//����Փx��
	STAGESELECT_OBJ_STAGE2DIF1,	//��R��Փx��
	STAGESELECT_OBJ_STAGE2DIF2,	//��R��Փx��
	STAGESELECT_OBJ_STAGE2DIF3,	//��R��Փx��
	STAGESELECT_OBJ_STAGE3DIF1,	//�ΎR��Փx��
	STAGESELECT_OBJ_STAGE3DIF2,	//�ΎR��Փx��
	STAGESELECT_OBJ_STAGE3DIF3,	//�ΎR��Փx��
	STAGESELECT_OBJ_MAX,		//���U���g�e�N�X�`������
} STAGESELECT_OBJ_LABEL;	//�I�u�W�F�N�g�p���x��

struct STAGESELECT
{
	D3DXVECTOR3		Pos;		//�摜�ʒu
	D3DXVECTOR3		Size;		//�摜�T�C�Y
	D3DXVECTOR2		UV;			//UV�l
	D3DXVECTOR2		UVSize;		//UV�T�C�Y
	STAGESELECT_TEX_LABEL	label;	//�`��e�N�X�`��
	float			fAlpha;		//���l
	bool			bDraw;		//�`���
};

//==========================================================================================
//	�N���X��`
//==========================================================================================

//==========================================================================================
//	�}�N����`
//==========================================================================================
void InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);

//==========================================================================================
//	�v���g�^�C�v�錾
//==========================================================================================


#endif