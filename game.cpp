/*****************************************************************************
game.cpp
Aythor	: ���@��
Data	: 2017_05_20
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "game.h"
#include "gameBG.h"
#include "bossHp.h"
#include "bullet.h"
#include "bulletEffect.h"
#include "gameUI.h"
#include "castle.h"
#include "bulletUI.h"
#include "player.h"
#include "notes.h"
#include "stage.h"
#include "gate.h"
#include "fade.h"
#include "input.h"
#include "inputX.h"
#include "texture.h"
#include "sound.h"
#include "activate.h"
#include "fcoh.h"
#include "explo.h"
#include "tutorial.h"

#include "boss.h"
#include "bulletBoss.h"
#include "nucleusBoss.h"
#include "human.h"

#include "result.h"

#include "heart.h"
#include "warning.h"

#include "effect.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define COUNT	(30)	//�K�E�Z��Q�[�����A�܂ł̎���

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
int	g_count = 0;			//�J�E���g�_�E��
bool g_countFlag = false;	//�J�E���g�_�E���t���O
STATE g_gameState = NONE;	//�Q�[���̏��
int	g_combo = 0;			//�R���{��
int g_maxCombo = 0;			//�ő�R���{

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initGame
//�Ԃ�l	: 
//����		: �Q�[��������
//////////////////////////////////////////////////////////////////////////////
void	initGame	( void )
{
	//�ϐ�������
	g_combo = 0;
	g_countFlag = false;
	g_count = 0;
	g_gameState = NONE;
	g_maxCombo = 0;

	InitEffect();


	//UI������
	InitTexture();
	initGameUI();

	// �G�z�u�̏�����
	ReStage();

	//�`���[�g���A��������
	if (getStgNum() == STAGE_00)
	{
		initTuto();
	}

	//�t�F�[�h�C��
	startFadeIn(60, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	InitWarning();
	InitHeart();

	//HP������
	initBossHp();

	//�v���C���[������
	InitPlayer();

	//�e������
	initBullet();

	//�e�G�t�F�N�g������
	initBulletEffect();

	//����������
	initExplo();

	//�X�e�[�W������
	InitNotes();

	//�叉����
	InitGate();

	//���@����������
	initActive();

	//�K�E�Z������
	initFcoh();

	// �l������
	InitHuman();

	InitBoss();
	InitBulletBoss();
	InitNucleusBoss();

	SetTexture(0 , 0.0f , 0.0f , SCREEN_WIDTH , SCREEN_HEIGHT / 100.0f * 23.6f , 0 , 0 , 1 , 1 , 1);
	
	
	SetTexture(1 , 10.0f , SCREEN_HEIGHT / 100.0f * 22.6f ,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);
	
	SetTexture(2 , 10.0f , SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);
	SetTexture(3 , 10.0f , SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 2,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);
	SetTexture(4 , 10.0f , SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 3,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);
	SetTexture(5 , 10.0f , SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);

	PlaySound(GAME_BGM_01);

	//�w�i�摜�ݒ�
	initGameBG();
	setGameBGType(GAMEBG_VILLAGE);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitGame
//�Ԃ�l	: 
//����		: �Q�[���I��
//////////////////////////////////////////////////////////////////////////////
void	uninitGame	( void )
{
	//�K�E�Z�I��
	uninitFcoh();

	//���@�����I��
	uninitActive();

	//��I��
	UninitGate();

	//�`���[�g���A���I��
	if (getStgNum() == STAGE_00)
	{
		uninitTuto();
	}

	//�X�e�[�W�I��
	UninitNotes();

	//�����I��
	uninitExplo();

	//�e�G�t�F�N�g�I��
	uninitBulletEffect();

	//�e�I��
	uninitBullet();

	//�v���C���[�I��
	UninitPlayer();

	//HP�I��
	uninitBossHp();

	//UI�I��
	uninitGameUI();

	// �l�I��
	UninitHuman();

	//�{�X�I��
	UninitBoss();
	UninitBulletBoss();
	UninitNucleusBoss();

	UninitTexture();

	//�w�i�I��
	uninitGameBG();

	UninitWarning();
	UninitHeart();

	UninitEffect();

	StopSound();

	resetStgNum();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateGame
//�Ԃ�l	: 
//����		: �Q�[���X�V
//////////////////////////////////////////////////////////////////////////////
void	updateGame	( void )
{
	//�K�E�Z�X�V
	updateFcoh();

	//�K�E�Z���͍X�V����Ȃ�
	if(getFcohFlag() == false && g_count <= 0)
	{
		//�w�i�X�V
		updateGameBG();

		//HP�X�V
		updateBossHp();

		//�v���C���[�X�V
		UpdatePlayer();

		//�e�X�V
		updateBullet();

		//�e�G�t�F�N�g�X�V
		updateBulletEffect();

		//�����X�V
		updateExplo();

		//���@�����X�V
		updateActive();

		//�X�e�[�W�X�V
		UpdateNotes();

		//�`���[�g���A���X�V
		if (getStgNum() == STAGE_00)
		{
			updateTuto();
		}

		//��X�V
		UpdateGate();

		UpdateTexture();
	
		//UI�X�V
		updateGameUI();

		// �l�X�V
		UpdateHuman();

		UpdateBoss();
		UpdateBulletBoss();
		UpdateNucleusBoss();

		UpdateWarning();
		UpdateHeart();

		UpdateEffect();

		//�{�X�o��
		if(GetKeyboardTrigger(DIK_4))
		{
			SetWarning(0 , WARNING_BOSS);
			SetBoss(SCREEN_WIDTH , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
		}
	}
	if(getFcohFlag() == true)
	{
		g_count = COUNT;
		g_countFlag = true;
	}

	if(g_count > 0)
	{
		g_count--;
	}
	else if(g_countFlag == true)
	{
		g_count = 0;
		damageFcoh();
		g_countFlag = false;
	}

	//�V�[���J��
	if (g_gameState == VICTORY)				//�������ꍇ
	{
		SetAchiveValue(100);				//�B���x�ݒ�
		SetComboValue(g_maxCombo);			//�R���{���ݒ�
		SetPhysicalValue(GetCastleHp());	//�c�̗͐ݒ�
		//startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), RESULT_MODE);
	}
	if (g_gameState == LOSE)			//�������ꍇ
	{
		SetAchiveValue(getParcent());	//�B���x�ݒ�
		SetComboValue(g_maxCombo);		//�R���{���ݒ�
		SetPhysicalValue(100);			//�c�̗͐ݒ�
		//startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), RESULT_MODE);
	}
	if (GetKeyboardTrigger(DIK_N))
	{
		SetAchiveValue(getParcent());	//�B���x�ݒ�
		SetComboValue(g_maxCombo);		//�R���{���ݒ�
		SetPhysicalValue(100);			//�c�̗͐ݒ�
		//startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), RESULT_MODE);
		setMode(RESULT_MODE);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawGame
//�Ԃ�l	: 
//����		: �Q�[���`��
//////////////////////////////////////////////////////////////////////////////
void	drawGame	( void )
{
	//�w�i�`��
	drawGameBG();

	DrawTexture(1);
	DrawTexture(0);

	//���@�����`��
	drawActive();

	//�X�e�[�W�`��
	DrawNotes();

	//�v���C���[�`��
	DrawPlayer();

	//�����`��
	drawExplo();

	//���@�G�t�F�N�g�`��
	drawBulletEffect();

	//�e�`��
	drawBullet();

	//hp�`��
	//drawBossHp();

	//��X�V
	DrawGate();

	//�K�E�Z
	drawFcoh();

	//UI�`��
	drawGameUI();

	DrawHeart();

	// �l�`��
	DrawHuman();

	DrawBoss();
	DrawBulletBoss();
	DrawNucleusBoss();

	DrawWarning();

	DrawEffect();

	//�`���[�g���A���`��
	if (getStgNum() == STAGE_00)
	{
		drawTuto();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setGameState
//�Ԃ�l	: 
//����		: �Q�[����Ԑݒ�
//////////////////////////////////////////////////////////////////////////////
void	setGameState(STATE state)
{
	g_gameState = state;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: addCombo
//�Ԃ�l	: 
//����		: �R���{���Z
//////////////////////////////////////////////////////////////////////////////
void	addCombo(void)
{
	g_combo++;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: resetCombo
//�Ԃ�l	: 
//����		: �R���{���Z�b�g
//////////////////////////////////////////////////////////////////////////////
void	resetCombo(void)
{
	if (g_maxCombo < g_combo)
	{
		g_maxCombo = g_combo;
	}
	g_combo = 0;
}