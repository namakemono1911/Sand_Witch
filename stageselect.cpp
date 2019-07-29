//==========================================================================================
//	�X�e�[�W�Z���N�g����[stageselect.cpp]
//	Author : KAZUNORI MARUHASHI
//
//	Update :
//		YYYY/MM/DD	Updater :
//
//		2017/06/05	Updater : KAZUNORI MARUHASHI
//			�E�d�l���̓��e�͎����B
//			����͓�Փx�I����̏����A�����Ȃ�L�����Z��SE�̎����B
//			  define�ȊO�ŘM�肻���ȏ��� JUMP �Ō������Ĕ��ł������� 
//
//		2017/06/04	Updater : KAZUNORI MARUHASHI
//			�EDefine�֘A�����ݒ�B
//			
//			
//	
//==========================================================================================

//==========================================================================================
// �C���N���[�h�t�@�C��
//==========================================================================================
#include "main.h"		//���C������
#include "input.h"		//���͏���
#include "inputX.h"		//���͏���
#include "sound.h"		//�T�E���h����
#include "stageselect.h"		//�X�e�[�W�Z���N�g����
#include "fade.h"
#include "stage.h"

//==========================================================================================
// �}�N����`
//==========================================================================================
//�e�N�X�`���֌W
#define STAGESELECT_TITLE_TEXTURENAME			"data/TEXTURE/STAGESELECT/stageSelectASC.png"		//�X�e�[�W�Z���N�g����
#define STAGESELECT_TUTORIAL_TEXTURENAME		"data/TEXTURE/STAGESELECT/tutorialASC.png"			//�`���[�g���A������
#define STAGESELECT_STAGE1_TEXTURENAME			"data/TEXTURE/STAGESELECT/stage01.png"				//���摜
#define STAGESELECT_STAGE2_TEXTURENAME			"data/TEXTURE/STAGESELECT/stage02.png"				//��R�摜
#define STAGESELECT_STAGE3_TEXTURENAME			"data/TEXTURE/STAGESELECT/stage03.png"				//�ΎR�摜
#define STAGESELECT_STAGECURSOR_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageSelectCursor.png"	//�X�e�[�W�Z���N�g�J�[�\��
#define STAGESELECT_STAGE1DIF1_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif1.png"			//����Փx��
#define STAGESELECT_STAGE1DIF2_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif2.png"			//����Փx��
#define STAGESELECT_STAGE1DIF3_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif3.png"			//����Փx��
#define STAGESELECT_STAGE2DIF1_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif1.png"			//��R��Փx��
#define STAGESELECT_STAGE2DIF2_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif2.png"			//��R��Փx��
#define STAGESELECT_STAGE2DIF3_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif3.png"			//��R��Փx��
#define STAGESELECT_STAGE3DIF1_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif1.png"			//�ΎR��Փx��
#define STAGESELECT_STAGE3DIF2_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif2.png"			//�ΎR��Փx��
#define STAGESELECT_STAGE3DIF3_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif3.png"			//�ΎR��Փx��
#define STAGESELECT_DIFCURSOR_TEXTURENAME		"data/TEXTURE/STAGESELECT/difSelectCursor.png"		//��Փx�J�[�\��

#define STAGESELECT_STAGE1_BG_TEXTURENAME			"data/TEXTURE/GAME/BG/stageBG01.jpg"			//���摜
#define STAGESELECT_STAGE2_BG_TEXTURENAME			"data/TEXTURE/GAME/BG/stageBG02.jpg"			//��R�摜
#define STAGESELECT_STAGE3_BG_TEXTURENAME			"data/TEXTURE/GAME/BG/stageBG03.jpg"			//�ΎR�摜

//=========�ʒu�֘A(���W�͒��S���w��)==========//
//�w�i
#define STAGESELECT_BG_POSX				(SCREEN_WIDTH  * 0.5f)
#define STAGESELECT_BG_POSY				(SCREEN_HEIGHT * 0.5f)
#define STAGESELECT_BG_SIZEX			(SCREEN_WIDTH)
#define STAGESELECT_BG_SIZEY			(SCREEN_HEIGHT)

//�t�F�[�h�p�w�i
#define STAGESELECT_BGFADE_POSX			(STAGESELECT_BG_POSX)
#define STAGESELECT_BGFADE_POSY			(STAGESELECT_BG_POSY)
#define STAGESELECT_BGFADE_SIZEX		(STAGESELECT_BG_SIZEX)
#define STAGESELECT_BGFADE_SIZEY		(STAGESELECT_BG_SIZEY)

//�X�e�[�W�Z���N�g����
#define STAGESELECT_TITLE_POSX			(SCREEN_WIDTH  * 0.25f)
#define STAGESELECT_TITLE_POSY			(SCREEN_HEIGHT * 0.12f)
#define STAGESELECT_TITLE_SIZEX			(SCREEN_WIDTH  * 0.3f)
#define STAGESELECT_TITLE_SIZEY			(SCREEN_HEIGHT * 0.25f)

//�`���[�g���A��
#define STAGESELECT_TUTORIAL_POSX		(SCREEN_WIDTH  * 0.23f)
#define STAGESELECT_TUTORIAL_POSY		(SCREEN_HEIGHT * 0.35f)
#define STAGESELECT_TUTORIAL_SIZEX		(SCREEN_WIDTH  * 0.17f)
#define STAGESELECT_TUTORIAL_SIZEY		(SCREEN_HEIGHT * 0.17f)

//=================�������獶���_========================//
//�������������_�ɂȂ�܂��B�c�͒ʏ�ʂ�ł�
//��
#define STAGESELECT_STAGE1_POSX			(SCREEN_WIDTH  * 0.15f)
#define STAGESELECT_STAGE1_POSY			(STAGESELECT_TUTORIAL_POSY + SCREEN_HEIGHT * 0.17f)
#define STAGESELECT_STAGE1_SIZEX		(STAGESELECT_TUTORIAL_SIZEX)
#define STAGESELECT_STAGE1_SIZEY		(STAGESELECT_TUTORIAL_SIZEY)

//��R
#define STAGESELECT_STAGE2_POSX			(STAGESELECT_STAGE1_POSX)
#define STAGESELECT_STAGE2_POSY			(STAGESELECT_STAGE1_POSY + SCREEN_HEIGHT * 0.17f )
#define STAGESELECT_STAGE2_SIZEX		(STAGESELECT_STAGE1_SIZEX  )
#define STAGESELECT_STAGE2_SIZEY		(STAGESELECT_STAGE1_SIZEY )

//�ΎR
#define STAGESELECT_STAGE3_POSX			(STAGESELECT_STAGE1_POSX)
#define STAGESELECT_STAGE3_POSY			(STAGESELECT_STAGE2_POSY + SCREEN_HEIGHT * 0.17f )
#define STAGESELECT_STAGE3_SIZEX		(STAGESELECT_STAGE1_SIZEX  )
#define STAGESELECT_STAGE3_SIZEY		(STAGESELECT_STAGE1_SIZEY )

//����
#define	STAGESELECT_STAGE_LONGSIZEX		(SCREEN_WIDTH  * 0.70f)	//�I�����E�ւǂ���L�΂���
#define STAGESELECT_STAGE_UV			(0.3f)		//�X�e�[�W�A�C�R���k������UV
//=================�����܂ō����_========================//

//�X�e�[�W�Z���N�g�J�[�\��
#define STAGESELECT_CURSOL_POSX			(SCREEN_WIDTH  * 0.1f)
#define STAGESELECT_CURSOL_POSY			(STAGESELECT_STAGE1_POSY)
#define STAGESELECT_CURSOL_SIZEX		(SCREEN_WIDTH  * 0.08f)
#define STAGESELECT_CURSOL_SIZEY		(SCREEN_HEIGHT * 0.1f)

//����
#define STAGESELECT_STAGE1DIF1_POSX		(SCREEN_WIDTH  * 0.50f)
#define STAGESELECT_STAGE1DIF1_POSY		(STAGESELECT_STAGE1_POSY )
#define STAGESELECT_STAGE1DIF1_SIZEX	(SCREEN_WIDTH  * 0.05f)
#define STAGESELECT_STAGE1DIF1_SIZEY	(SCREEN_HEIGHT * 0.08f)

//����
#define STAGESELECT_STAGE1DIF2_POSX		(SCREEN_WIDTH  * 0.60f)
#define STAGESELECT_STAGE1DIF2_POSY		(STAGESELECT_STAGE1DIF1_POSY )
#define STAGESELECT_STAGE1DIF2_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX  )
#define STAGESELECT_STAGE1DIF2_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//����
#define STAGESELECT_STAGE1DIF3_POSX		(SCREEN_WIDTH  * 0.70f)
#define STAGESELECT_STAGE1DIF3_POSY		(STAGESELECT_STAGE1DIF1_POSY )
#define STAGESELECT_STAGE1DIF3_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX  )
#define STAGESELECT_STAGE1DIF3_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//��R��
#define STAGESELECT_STAGE2DIF1_POSX		(STAGESELECT_STAGE1DIF1_POSX  )
#define STAGESELECT_STAGE2DIF1_POSY		(STAGESELECT_STAGE2_POSY )
#define STAGESELECT_STAGE2DIF1_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX  )
#define STAGESELECT_STAGE2DIF1_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//��R��
#define STAGESELECT_STAGE2DIF2_POSX		(STAGESELECT_STAGE1DIF2_POSX  )
#define STAGESELECT_STAGE2DIF2_POSY		(STAGESELECT_STAGE2_POSY )
#define STAGESELECT_STAGE2DIF2_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX  )
#define STAGESELECT_STAGE2DIF2_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//��R��
#define STAGESELECT_STAGE2DIF3_POSX		(STAGESELECT_STAGE1DIF3_POSX  )
#define STAGESELECT_STAGE2DIF3_POSY		(STAGESELECT_STAGE2_POSY	  )
#define STAGESELECT_STAGE2DIF3_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX )
#define STAGESELECT_STAGE2DIF3_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//�ΎR��
#define STAGESELECT_STAGE3DIF1_POSX		(STAGESELECT_STAGE1DIF1_POSX  )
#define STAGESELECT_STAGE3DIF1_POSY		(STAGESELECT_STAGE3_POSY	  )
#define STAGESELECT_STAGE3DIF1_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX )
#define STAGESELECT_STAGE3DIF1_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )
		
//�ΎR��
#define STAGESELECT_STAGE3DIF2_POSX		(STAGESELECT_STAGE1DIF2_POSX  )
#define STAGESELECT_STAGE3DIF2_POSY		(STAGESELECT_STAGE3_POSY	  )
#define STAGESELECT_STAGE3DIF2_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX )
#define STAGESELECT_STAGE3DIF2_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )
		
//�ΎR��
#define STAGESELECT_STAGE3DIF3_POSX		(STAGESELECT_STAGE1DIF3_POSX  )
#define STAGESELECT_STAGE3DIF3_POSY		(STAGESELECT_STAGE3_POSY	  )
#define STAGESELECT_STAGE3DIF3_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX )
#define STAGESELECT_STAGE3DIF3_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//��Փx�Z���N�g�J�[�\��(POS�͌�ɐݒ肷��̂Ŗ���)
#define STAGESELECT_DIFCURSOL_SIZEX		(SCREEN_WIDTH  * 0.06f)
#define STAGESELECT_DIFCURSOL_SIZEY		(SCREEN_HEIGHT * 0.09f)

//�X�e�[�W���ڍő吔
#define STAGESELECT_NUM (4)
#define STAGESELECT_DIF_NUM (3)
#define ONESECOND_FRAME (60)	//�P�b�̃t���[����
#define STAGEBAR_MOVE_FRAME (30)	//�X�e�[�W�|���S���̐L�k�t���[����
#define BG_FADE_FRAME (ONESECOND_FRAME * 2)		//�w�i�̃t�F�[�h�t���[��

#define DICIDION_KEY (DIK_Z)	//����L�[
#define CANCEL_KEY (DIK_X)		//�L�����Z���L�[

//==========================================================================================
// �\���̒�`
//==========================================================================================


//==========================================================================================
// �v���g�^�C�v�錾
//==========================================================================================
HRESULT MakeVertexStageSelect(LPDIRECT3DDEVICE9 pDevice);
void CreateTextureStageselect(LPDIRECT3DDEVICE9 pDevice);

void SelectStage(void);				//�X�e�[�W�I������
void SelectDifficulty(void);		//��Փx�I������
void SelectStageBarExtend(void);	//�X�e�[�W�o�[�������΂�����
void SelectDifficultyCancel(void);	//�X�e�[�W�o�[�k������

//==========================================================================================
// �O���[�o���ϐ�
//==========================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferStageSelect = NULL;
STAGESELECT g_StageSelectObj[STAGESELECT_OBJ_MAX];
LPDIRECT3DTEXTURE9 g_pTextureStageSelect[STAGESELECT_TEX_MAX] = {};	//�e�N�X�`���C���^�[�t�F�[�X

static int g_iStageCursor;		//���ݑI��ł���X�e�[�W
static int g_iSelectDifCursor;	//���ݑI��ł����Փx
static int g_iPhase;			//�������e
static int g_iFrame;			//�t���[�����J�E���g
static int g_ibgFrame;			//�w�i�p�t���[�����J�E���g

//==========================================================================================
// ����������
//==========================================================================================
void InitStageSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�̎擾

	//�t�F�[�h�C��
	startFadeIn(60, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//���_�̐ݒ�
	if(FAILED(MakeVertexStageSelect(pDevice)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐ݒ�Ɏ��s���܂����B", " ", MB_OK);
		return;
	}

	//�e�N�X�`�������p�֐�
	CreateTextureStageselect(pDevice);

	//
	g_StageSelectObj[STAGESELECT_OBJ_BG].Pos = D3DXVECTOR3(STAGESELECT_BG_POSX, STAGESELECT_BG_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_BG].Size = D3DXVECTOR3(STAGESELECT_BG_SIZEX, STAGESELECT_BG_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_BG].label = STAGESELECT_TEX_BG_STAGE1;
	  
	g_StageSelectObj[STAGESELECT_OBJ_BGFADE].Pos = D3DXVECTOR3(STAGESELECT_BGFADE_POSX, STAGESELECT_BGFADE_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_BGFADE].Size = D3DXVECTOR3(STAGESELECT_BGFADE_SIZEX, STAGESELECT_BGFADE_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label = STAGESELECT_TEX_STAGE1;
	  
	g_StageSelectObj[STAGESELECT_OBJ_TITLE].Pos = D3DXVECTOR3(STAGESELECT_TITLE_POSX, STAGESELECT_TITLE_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_TITLE].Size = D3DXVECTOR3(STAGESELECT_TITLE_SIZEX, STAGESELECT_TITLE_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_TITLE].label = STAGESELECT_TEX_TITLE;
	  
	g_StageSelectObj[STAGESELECT_OBJ_TURORIAL].Pos = D3DXVECTOR3(STAGESELECT_TUTORIAL_POSX, STAGESELECT_TUTORIAL_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_TURORIAL].Size = D3DXVECTOR3(STAGESELECT_TUTORIAL_SIZEX, STAGESELECT_TUTORIAL_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_TURORIAL].label = STAGESELECT_TEX_TURORIAL;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1].Pos = D3DXVECTOR3(STAGESELECT_STAGE1_POSX, STAGESELECT_STAGE1_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1].Size = D3DXVECTOR3(STAGESELECT_STAGE1_SIZEX, STAGESELECT_STAGE1_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1].label = STAGESELECT_TEX_STAGE1;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2].Pos = D3DXVECTOR3(STAGESELECT_STAGE2_POSX, STAGESELECT_STAGE2_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2].Size = D3DXVECTOR3(STAGESELECT_STAGE2_SIZEX, STAGESELECT_STAGE2_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2].label = STAGESELECT_TEX_STAGE2;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3].Pos = D3DXVECTOR3(STAGESELECT_STAGE3_POSX, STAGESELECT_STAGE3_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3].Size = D3DXVECTOR3(STAGESELECT_STAGE3_SIZEX, STAGESELECT_STAGE3_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3].label = STAGESELECT_TEX_STAGE3;
	  
	g_StageSelectObj[STAGESELECT_OBJ_CURSOL].Pos = D3DXVECTOR3(STAGESELECT_CURSOL_POSX, STAGESELECT_CURSOL_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_CURSOL].Size = D3DXVECTOR3(STAGESELECT_CURSOL_SIZEX, STAGESELECT_CURSOL_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_CURSOL].label = STAGESELECT_TEX_CURSOL;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].Pos = D3DXVECTOR3(STAGESELECT_STAGE1DIF1_POSX, STAGESELECT_STAGE1DIF1_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].Size = D3DXVECTOR3(STAGESELECT_STAGE1DIF1_SIZEX, STAGESELECT_STAGE1DIF1_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].label = STAGESELECT_TEX_STAGE1DIF1;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].Pos = D3DXVECTOR3(STAGESELECT_STAGE1DIF2_POSX, STAGESELECT_STAGE1DIF2_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].Size = D3DXVECTOR3(STAGESELECT_STAGE1DIF2_SIZEX, STAGESELECT_STAGE1DIF2_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].label = STAGESELECT_TEX_STAGE1DIF2;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].Pos = D3DXVECTOR3(STAGESELECT_STAGE1DIF3_POSX, STAGESELECT_STAGE1DIF3_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].Size = D3DXVECTOR3(STAGESELECT_STAGE1DIF3_SIZEX, STAGESELECT_STAGE1DIF3_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].label = STAGESELECT_TEX_STAGE1DIF3;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].Pos = D3DXVECTOR3(STAGESELECT_STAGE2DIF1_POSX, STAGESELECT_STAGE2DIF1_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].Size = D3DXVECTOR3(STAGESELECT_STAGE2DIF1_SIZEX, STAGESELECT_STAGE2DIF1_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].label = STAGESELECT_TEX_STAGE2DIF1;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].Pos = D3DXVECTOR3(STAGESELECT_STAGE2DIF2_POSX, STAGESELECT_STAGE2DIF2_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].Size = D3DXVECTOR3(STAGESELECT_STAGE2DIF2_SIZEX, STAGESELECT_STAGE2DIF2_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].label = STAGESELECT_TEX_STAGE2DIF2;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].Pos = D3DXVECTOR3(STAGESELECT_STAGE2DIF3_POSX, STAGESELECT_STAGE2DIF3_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].Size = D3DXVECTOR3(STAGESELECT_STAGE2DIF3_SIZEX, STAGESELECT_STAGE2DIF3_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].label = STAGESELECT_TEX_STAGE2DIF3;
	  
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].Pos = D3DXVECTOR3(STAGESELECT_STAGE3DIF1_POSX, STAGESELECT_STAGE3DIF1_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].Size = D3DXVECTOR3(STAGESELECT_STAGE3DIF1_SIZEX, STAGESELECT_STAGE3DIF1_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].label = STAGESELECT_TEX_STAGE3DIF1;

	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].Pos = D3DXVECTOR3(STAGESELECT_STAGE3DIF2_POSX, STAGESELECT_STAGE3DIF2_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].Size = D3DXVECTOR3(STAGESELECT_STAGE3DIF2_SIZEX, STAGESELECT_STAGE3DIF2_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].label = STAGESELECT_TEX_STAGE3DIF2;

	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].Pos = D3DXVECTOR3(STAGESELECT_STAGE3DIF3_POSX, STAGESELECT_STAGE3DIF3_POSY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].Size = D3DXVECTOR3(STAGESELECT_STAGE3DIF3_SIZEX, STAGESELECT_STAGE3DIF3_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].label = STAGESELECT_TEX_STAGE3DIF3;

	g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Size = D3DXVECTOR3(STAGESELECT_DIFCURSOL_SIZEX, STAGESELECT_DIFCURSOL_SIZEY, 0.0f);
	g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].label = STAGESELECT_TEX_DIFCURSOL;

	//�ŗL�l�ȊO�ꊇ�ݒ�
	for(int i = 0; i < STAGESELECT_OBJ_MAX; i++){
		g_StageSelectObj[i].fAlpha = 1.0f;
		g_StageSelectObj[i].bDraw = true;
		g_StageSelectObj[i].UV = D3DXVECTOR2(0.0f, 0.0f);
		g_StageSelectObj[i].UVSize = D3DXVECTOR2(1.0f, 1.0f);
	}

	//��Փx�֘A��`��
	for(int i = STAGESELECT_OBJ_STAGE1DIF1; i <= STAGESELECT_OBJ_STAGE3DIF3; i++){
		g_StageSelectObj[i].fAlpha = 0.0f;
		g_StageSelectObj[i].bDraw = false;
	}

	//�X�e�[�W�A�C�R���̏���UV�T�C�Y�̐ݒ�
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1].UVSize.x = STAGESELECT_STAGE_UV;
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2].UVSize.x = STAGESELECT_STAGE_UV;
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3].UVSize.x = STAGESELECT_STAGE_UV;


	//��Փx�I���\��
	g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].bDraw = false;

	//�t�F�[�h�̃��l0
	g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha = 0.0f;

	g_iStageCursor = 0;		//���ݑI��ł���X�e�[�W�i�����F�`���[�g���A���j
	g_iSelectDifCursor = 0;	//���ݑI��ł����Փx�i�����F�Ձj
	g_iPhase = 0;			//�������e
	g_ibgFrame = 0;

	//BGM�Đ�
	PlaySound(BGM_STAGESELECT);
}

//==========================================================================================
// �I������
//==========================================================================================
void UninitStageSelect(void)
{
	if(g_pVtxBufferStageSelect != NULL)
	{
		g_pVtxBufferStageSelect -> Release();
		g_pVtxBufferStageSelect = NULL;
	}
	for(int iSelf = 0; iSelf < STAGESELECT_TEX_MAX; iSelf++){
		if(g_pTextureStageSelect[iSelf] != NULL){
			g_pTextureStageSelect[iSelf] -> Release();
			g_pTextureStageSelect[iSelf] = NULL;
		}
	}
	StopSound(BGM_STAGESELECT);
}

//==========================================================================================
// �X�V����
//==========================================================================================
void UpdateStageSelect(void)
{
	switch(g_iPhase){
	//�X�e�[�W�̑I��
	case 0:
		//�X�e�[�W�̑I��
		SelectStage();			

		break;

	//�X�e�[�W�o�[�̈����L�΂�
	case 1:
		//�X�e�[�W�o�[�̈����L�΂�
		SelectStageBarExtend();

		break;

	//��Փx�I��
	case 2:
		//��Փx�I��
		SelectDifficulty();	

		break;

	//�X�e�[�W�o�[�k��
	case 3:
		//�X�e�[�W�o�[�k��
		SelectDifficultyCancel();	
		
		break;

	default:
		break;
	}
	
	//======�w�i�t�F�[�h
	if(g_StageSelectObj[STAGESELECT_OBJ_BG].label != g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label){
		g_ibgFrame++;

		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha = (1.0f / ONESECOND_FRAME) * g_ibgFrame;
		if(g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha >= 1.0f){
			g_StageSelectObj[STAGESELECT_OBJ_BG].label = g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label;
			g_ibgFrame = 0;
		}
	}

	
	VERTEX2D* pVtx;	//���z�A�h���X�擾�p�|�C���^
	//���z�A�h���X���擾����
	g_pVtxBufferStageSelect -> Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	for(int VtxLoop = 0; VtxLoop < STAGESELECT_OBJ_MAX; VtxLoop++){
		if(g_StageSelectObj[VtxLoop].bDraw == true){
			if(VtxLoop == STAGESELECT_OBJ_STAGE1 || VtxLoop == STAGESELECT_OBJ_STAGE2 || VtxLoop == STAGESELECT_OBJ_STAGE3)
			{
				//���_���W�̐ݒ�i���㌴�_�j�ix, y, z�j
				pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x,
													g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x,
													g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x,
													g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x,
													g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);
			}
			else
			{
				//���_���W�̐ݒ�ix, y, z�j
				pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x - g_StageSelectObj[VtxLoop].Size.x * 0.5f,
													g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x * 0.5f,
													g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x - g_StageSelectObj[VtxLoop].Size.x * 0.5f,
													g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x * 0.5f,
													g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);		
			}
			//�J���[�̐ݒ�
			pVtx[0+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_StageSelectObj[VtxLoop].fAlpha);
			pVtx[1+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_StageSelectObj[VtxLoop].fAlpha);
			pVtx[2+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_StageSelectObj[VtxLoop].fAlpha);
			pVtx[3+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_StageSelectObj[VtxLoop].fAlpha);

			//�e�N�X�`���\���W�̐ݒ�
			pVtx[0+4*VtxLoop].tex = D3DXVECTOR2(g_StageSelectObj[VtxLoop].UV.x,
												g_StageSelectObj[VtxLoop].UV.y);
			pVtx[1+4*VtxLoop].tex = D3DXVECTOR2(g_StageSelectObj[VtxLoop].UV.x + g_StageSelectObj[VtxLoop].UVSize.x, 
												g_StageSelectObj[VtxLoop].UV.y);
			pVtx[2+4*VtxLoop].tex = D3DXVECTOR2(g_StageSelectObj[VtxLoop].UV.x, 
												g_StageSelectObj[VtxLoop].UV.y + g_StageSelectObj[VtxLoop].UVSize.y);
			pVtx[3+4*VtxLoop].tex = D3DXVECTOR2(g_StageSelectObj[VtxLoop].UV.x + g_StageSelectObj[VtxLoop].UVSize.x, 
												g_StageSelectObj[VtxLoop].UV.y + g_StageSelectObj[VtxLoop].UVSize.y);
		}
	}

	g_pVtxBufferStageSelect -> Unlock();
}

//==========================================================================================
// �`�揈��
//==========================================================================================
void DrawStageSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�̎擾
	
	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferStageSelect,
							  0,					//�I�t�Z�b�g
							  sizeof(VERTEX2D));		//�X�g���C�h��

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	//�|���S���̕`��
	for(int iDraw = 0; iDraw < STAGESELECT_OBJ_MAX; iDraw++){
		//�`�������ꍇ
		if(g_StageSelectObj[iDraw].bDraw == true){
			
			pDevice -> SetTexture(0, g_pTextureStageSelect[g_StageSelectObj[iDraw].label]);

			//�v���~�e�B�u�̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
										iDraw * 4,					//�I�t�Z�b�g(���_��)
										NUM_POLYGON);			//�v���~�e�B�u��
		}
	}
}

//==========================================================================================
// ���_�̐���
//==========================================================================================
HRESULT MakeVertexStageSelect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX2D* pVtx;	//���z�A�h���X�擾�p�|�C���^

	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX2D)*NUM_VERTEX*STAGESELECT_OBJ_MAX,	//�m�ۂ��������_�o�b�t�@�̐������_��
								  D3DUSAGE_WRITEONLY,	//�m�ۂ����㒆�����邱�Ƃ͂ł��Ȃ�
								  FVF_VERTEX_2D,		//�ꉞ�������Ƃ����C
								  D3DPOOL_MANAGED,		//�������Ǘ����ǂ����邩(����͂��C��)
								  &g_pVtxBufferStageSelect,
								  NULL)))
	{
		return E_FAIL;
	}

	//���z�A�h���X���擾����
	g_pVtxBufferStageSelect -> Lock(0, 0, (void**)&pVtx, 0);

	for(int VtxLoop = 0; VtxLoop < STAGESELECT_OBJ_MAX; VtxLoop++){

		//���_���W�̐ݒ�ix, y, z�j
		pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x - g_StageSelectObj[VtxLoop].Size.x,
											g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y, 0.0f);

		pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x,
											g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y, 0.0f);

		pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x - g_StageSelectObj[VtxLoop].Size.x,
											g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y, 0.0f);

		pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x,
											g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y, 0.0f);

		//rhw�̐ݒ�(�K��1.0f)
		pVtx[0+4*VtxLoop].rhw =
		pVtx[1+4*VtxLoop].rhw =
		pVtx[2+4*VtxLoop].rhw = 
		pVtx[3+4*VtxLoop].rhw = 1.0f;

		//�J���[�̐ݒ�
		pVtx[0+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[1+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[2+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[3+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);

		//�e�N�X�`���\���W�̐ݒ�
		pVtx[0+4*VtxLoop].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1+4*VtxLoop].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2+4*VtxLoop].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+4*VtxLoop].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	g_pVtxBufferStageSelect -> Unlock();

	return S_OK;
}

//==========================================================================================
// �e�N�X�`������
//==========================================================================================
void CreateTextureStageselect(LPDIRECT3DDEVICE9 pDevice)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������

	//�e�N�X�`���擾
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_TITLE_TEXTURENAME,
		&g_pTextureStageSelect[0] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_TITLE_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_TUTORIAL_TEXTURENAME,
		&g_pTextureStageSelect[1] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_TUTORIAL_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1_TEXTURENAME,
		&g_pTextureStageSelect[2] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE1_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2_TEXTURENAME,
		&g_pTextureStageSelect[3] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE2_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3_TEXTURENAME,
		&g_pTextureStageSelect[4] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE3_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGECURSOR_TEXTURENAME,
		&g_pTextureStageSelect[5] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGECURSOR_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1DIF1_TEXTURENAME,
		&g_pTextureStageSelect[6] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE1DIF1_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1DIF2_TEXTURENAME,
		&g_pTextureStageSelect[7] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE1DIF2_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1DIF3_TEXTURENAME,
		&g_pTextureStageSelect[8] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE1DIF3_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2DIF1_TEXTURENAME,
		&g_pTextureStageSelect[9] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE2DIF1_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2DIF2_TEXTURENAME,
		&g_pTextureStageSelect[10] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE2DIF2_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2DIF3_TEXTURENAME,
		&g_pTextureStageSelect[11] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE2DIF3_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3DIF1_TEXTURENAME,
		&g_pTextureStageSelect[12] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE3DIF1_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3DIF2_TEXTURENAME,
		&g_pTextureStageSelect[13] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE3DIF2_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3DIF3_TEXTURENAME,
		&g_pTextureStageSelect[14] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE3DIF3_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_DIFCURSOR_TEXTURENAME,
		&g_pTextureStageSelect[15] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_DIFCURSOR_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1_BG_TEXTURENAME,
		&g_pTextureStageSelect[16] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE1_BG_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2_BG_TEXTURENAME,
		&g_pTextureStageSelect[17] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE2_BG_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3_BG_TEXTURENAME,
		&g_pTextureStageSelect[18] )))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","STAGESELECT_STAGE3_BG_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
}

//==========================================================================================
// �X�e�[�W�I������
//==========================================================================================
void SelectStage(void)
{
	//�㉺�ړ�
	if(GetKeyboardTrigger(DIK_DOWN) || GetKeyXInputTrigger(XINPUT_DPAD_DOWN)){
		//�I��SE�Đ�
		PlaySound(SE_STAGESELECT_CORSOR);
		g_iStageCursor++;

		g_ibgFrame = 0;
		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha = 0.0f;
	}else
	if(GetKeyboardTrigger(DIK_UP) || GetKeyXInputTrigger(XINPUT_DPAD_UP)){
		//�I��SE�Đ�
		PlaySound(SE_STAGESELECT_CORSOR);
		g_iStageCursor--;

		g_ibgFrame = 0;
		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha = 0.0f;
	}

	//���E�����[�v
	if(g_iStageCursor > STAGESELECT_NUM-1){
		g_iStageCursor = 0;
	}else
	if(g_iStageCursor < 0){
		g_iStageCursor = STAGESELECT_NUM-1;
	}

	//�J�[�\���ʒu�ړ�
	switch(g_iStageCursor){
	case 0:
		g_StageSelectObj[STAGESELECT_OBJ_CURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_TURORIAL].Pos.y;
		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label = STAGESELECT_TEX_BG_STAGE1;
		break;
	case 1:
		g_StageSelectObj[STAGESELECT_OBJ_CURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE1].Pos.y;
		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label = STAGESELECT_TEX_BG_STAGE1;
		break;
	case 2:
		g_StageSelectObj[STAGESELECT_OBJ_CURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE2].Pos.y;
		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label = STAGESELECT_TEX_BG_STAGE2;
		break;
	case 3:
		g_StageSelectObj[STAGESELECT_OBJ_CURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE3].Pos.y;
		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label = STAGESELECT_TEX_BG_STAGE3;
		break;
	default:
		break;
	}

	//����L�[������
	if(GetKeyboardTrigger(DICIDION_KEY) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A)){
		//����SE�Đ�
		PlaySound(SE_STAGESELECT_PUSH);
		g_iPhase = 1;
		g_iFrame = 0;
		if (g_iStageCursor == 0)
		{
			setStgNum(STAGE_00);
			startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), GAME_MODE);
		}
	}
}

//==========================================================================================
// ��Փx�I������
//==========================================================================================
void SelectDifficulty(void)
{
	g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].bDraw = true;

	//���E�ړ�
	if(GetKeyboardTrigger(DIK_LEFT) || GetKeyXInputTrigger(XINPUT_DPAD_LEFT)){
		//�I��SE�Đ�
		PlaySound(SE_STAGESELECT_CORSOR);
		g_iSelectDifCursor--;
	}else
	if(GetKeyboardTrigger(DIK_RIGHT) || GetKeyXInputTrigger(XINPUT_DPAD_RIGHT)){
		//�I��SE�Đ�
		PlaySound(SE_STAGESELECT_CORSOR);
		g_iSelectDifCursor++;
	}

	//���E���[�v
	if(g_iSelectDifCursor > STAGESELECT_DIF_NUM-1){
		g_iSelectDifCursor = 0;
	}else
	if(g_iSelectDifCursor < 0){
		g_iSelectDifCursor = STAGESELECT_DIF_NUM-1;
	}

	//�J�[�\���ʒu�ړ�
	switch(g_iStageCursor){
	case 1:
		g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].Pos.y;

		//�e��ړ��̈ʒu�ֈړ�
		if	   (g_iSelectDifCursor == 0){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].Pos.x;}
		else if(g_iSelectDifCursor == 1){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].Pos.x;}
		else if(g_iSelectDifCursor == 2){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].Pos.x;}
		break;
	case 2:
		g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].Pos.y;

		//�e��ړ��̈ʒu�ֈړ�
		if	   (g_iSelectDifCursor == 0){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].Pos.x;}
		else if(g_iSelectDifCursor == 1){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].Pos.x;}
		else if(g_iSelectDifCursor == 2){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].Pos.x;}
		break;
	case 3:
		g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].Pos.y;

		//�e��ړ��̈ʒu�ֈړ�
		if	   (g_iSelectDifCursor == 0){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].Pos.x;}
		else if(g_iSelectDifCursor == 1){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].Pos.x;}
		else if(g_iSelectDifCursor == 2){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].Pos.x;}
		break;
	default:
		break;
	}

	//����L�[������
	if(GetKeyboardTrigger(DICIDION_KEY) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A)){
		//����SE�Đ�
		PlaySound(SE_STAGESELECT_PUSH);

		//JUMP
		switch (g_iStageCursor)
		{
		case 1:
		{
			switch (g_iSelectDifCursor)
			{
			case 0:
			{
				setStgNum(STAGE_01);
				break;
			}

			case 1:
			{
				setStgNum(STAGE_02);
				break;
			}

			case 2:
			{
				setStgNum(STAGE_03);
				break;
			}
			}
			break;
		}
		case 2:
		{
			switch (g_iSelectDifCursor)
			{
			case 0:
			{
				setStgNum(STAGE_04);
				break;
			}

			case 1:
			{
				setStgNum(STAGE_05);
				break;
			}

			case 2:
			{
				setStgNum(STAGE_06);
				break;
			}
			}
			break;
		}

		case 3:
		{
			switch (g_iSelectDifCursor)
			{
			case 0:
			{
				setStgNum(STAGE_07);
				break;
			}

			case 1:
			{
				setStgNum(STAGE_08);
				break;
			}

			case 2:
			{
				setStgNum(STAGE_09);
				break;
			}
			}
			break;
		}

		}

		//�t�F�[�h�A�E�g
		startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), GAME_MODE);
	}
	//�L�����Z���L�[������
	else if(GetKeyboardTrigger(CANCEL_KEY) || GetKeyXInputTrigger(XINPUT_GAMEPAD_B)){
		//JUMP
		//�L�����Z��SE�Đ�
		PlaySound(SE_STAGESELECT_CANCEL);

		g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].bDraw = false;
		g_iSelectDifCursor = 0;
		g_iPhase = 3;
	}
}

//==========================================================================================
// �X�e�[�W�o�[�������΂�����
//==========================================================================================
void SelectStageBarExtend(void)
{
	//�t���[���J�E���g
	g_iFrame++;

	//�X�e�[�W�o�[�̈������΂�����
	if(g_iFrame <= STAGEBAR_MOVE_FRAME){
		//�J�[�\���ʒu�ړ�
		switch(g_iStageCursor){
		case 1:
			g_StageSelectObj[STAGESELECT_OBJ_STAGE1].Size.x = STAGESELECT_STAGE1_SIZEX + (STAGESELECT_STAGE_LONGSIZEX / STAGEBAR_MOVE_FRAME) * g_iFrame;
			g_StageSelectObj[STAGESELECT_OBJ_STAGE1].UVSize.x = STAGESELECT_STAGE_UV + (1.0f - STAGESELECT_STAGE_UV) / STAGEBAR_MOVE_FRAME * g_iFrame;
			break;
		case 2:
			g_StageSelectObj[STAGESELECT_OBJ_STAGE2].Size.x = STAGESELECT_STAGE2_SIZEX + (STAGESELECT_STAGE_LONGSIZEX / STAGEBAR_MOVE_FRAME) * g_iFrame;
			g_StageSelectObj[STAGESELECT_OBJ_STAGE2].UVSize.x = STAGESELECT_STAGE_UV + (1.0f - STAGESELECT_STAGE_UV) / STAGEBAR_MOVE_FRAME * g_iFrame;
			break;
		case 3:
			g_StageSelectObj[STAGESELECT_OBJ_STAGE3].Size.x = STAGESELECT_STAGE3_SIZEX + (STAGESELECT_STAGE_LONGSIZEX / STAGEBAR_MOVE_FRAME) * g_iFrame;
			g_StageSelectObj[STAGESELECT_OBJ_STAGE3].UVSize.x = STAGESELECT_STAGE_UV + (1.0f - STAGESELECT_STAGE_UV) / STAGEBAR_MOVE_FRAME * g_iFrame;
			break;
		default:
			break;
		}
	}
	else{
		if(g_iFrame <= STAGEBAR_MOVE_FRAME + ONESECOND_FRAME){
			//�J�[�\���ʒu�ړ�
			switch(g_iStageCursor){
			case 1:
				//�`���
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].bDraw = true;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				break;
			case 2:
				//�`���
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].bDraw = true;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				break;
			case 3:
				//�`���
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].bDraw = true;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				break;
			default:
				break;
			}
		}
		if(g_iFrame == STAGEBAR_MOVE_FRAME + ONESECOND_FRAME){
			g_iFrame = 0;
			g_iPhase = 2;
		}
	}
}

//==========================================================================================
// �X�e�[�W�o�[�k������
//==========================================================================================
void SelectDifficultyCancel(void)
{
	//�t���[���J�E���g
	g_iFrame++;

	//��Փx�̕\���̏���
	if(g_iFrame <= ONESECOND_FRAME){
		switch(g_iStageCursor){
		case 1:
			g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			break;																			 						  
		case 2:																				 						  
			g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			break;																			 						  
		case 3:																				 						  
			g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].fAlpha = (1.0f / ONESECOND_FRAME) * (ONESECOND_FRAME - g_iFrame);
			break;
		default:
			break;
		}
	}
	else{
		//�o�[�����ɖ߂�
		if(g_iFrame <= ONESECOND_FRAME + STAGEBAR_MOVE_FRAME){
			switch(g_iStageCursor){
			case 1:
				//�`���
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].bDraw = false;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE1].Size.x = STAGESELECT_STAGE1_SIZEX + (STAGESELECT_STAGE_LONGSIZEX / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1].UVSize.x = STAGESELECT_STAGE_UV + ((1.0f - STAGESELECT_STAGE_UV) / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));

				break;
			case 2:
				//�`���
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].bDraw = false;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE2].Size.x = STAGESELECT_STAGE2_SIZEX + (STAGESELECT_STAGE_LONGSIZEX / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2].UVSize.x = STAGESELECT_STAGE_UV + ((1.0f - STAGESELECT_STAGE_UV) / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));
				break;
			case 3:
				//�`���
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].bDraw = false;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE3].Size.x = STAGESELECT_STAGE3_SIZEX + (STAGESELECT_STAGE_LONGSIZEX / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));
				g_StageSelectObj[STAGESELECT_OBJ_STAGE3].UVSize.x = STAGESELECT_STAGE_UV + ((1.0f - STAGESELECT_STAGE_UV) / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));
				break;
			default:
				break;
			}
		}
		if(g_iFrame == STAGEBAR_MOVE_FRAME + ONESECOND_FRAME){
			g_iPhase = 0;
		}
	}
}
