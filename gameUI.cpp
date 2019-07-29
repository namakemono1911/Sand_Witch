/*****************************************************************************
gameUI.cpp
Aythor	: ���@��
Data	: 2017_05_21
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "bulletUI.h"
#include "gameUI.h"
#include "texture.h"

#include "stage.h"
#include "notes.h"
#include "castle.h"

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
float g_par = 0;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initGameUI
//�Ԃ�l	: 
//����		: �Q�[��UI������
//////////////////////////////////////////////////////////////////////////////
void	initGameUI	( void )
{
	//�eUI������
	initBulletUI();
	setBulletUI(
		D3DXVECTOR3(SCREEN_WIDTH / 100.0f * 25.5, SCREEN_HEIGHT / 100.0f * 15.5, 0.f),
		D3DXVECTOR3(SCREEN_WIDTH / 100.0f * 24, SCREEN_HEIGHT / 100.0f * 6.5, 0.f),
		D3DCOLOR_RGBA(192, 255, 192, 255));
	setBulletUI(
		D3DXVECTOR3(SCREEN_WIDTH / 100.0f * 25.5, SCREEN_HEIGHT / 100.0f * 8, 0.f),
		D3DXVECTOR3(SCREEN_WIDTH / 100.0f * 24, SCREEN_HEIGHT / 100.0f * 7, 0.f),
		D3DCOLOR_RGBA(192, 192, 255, 255));

	// UI
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

	// �e
	SetTexture(7 , SCREEN_WIDTH / 100.0f * 4 , SCREEN_HEIGHT / 100.0f * 4 * 3.1f, SCREEN_WIDTH / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4 , 0 , 0 , 1 , 1 , 2);
	SetTexture(8 , SCREEN_WIDTH / 100.0f * 4 *2.1f, SCREEN_HEIGHT / 100.0f * 4 * 3.1f, SCREEN_WIDTH / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4 , 0 , 0 , 1 , 1 , 2);
	SetTexture(9 , SCREEN_WIDTH / 100.0f * 4 * 1.55f , SCREEN_HEIGHT / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4 , 0 , 0 , 1 , 1 , 2);
//	SetTexture(10 , SCREEN_WIDTH / 100.0f * 4 *2.1f, SCREEN_HEIGHT / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4 , SCREEN_WIDTH / 100.0f * 4 , 0 , 0 , 1 , 1 , 2);

	// �i�s�x
	SetTexture(11 , SCREEN_WIDTH / 100.0f * 58 , SCREEN_HEIGHT / 100.0f * 4, SCREEN_WIDTH / 100.0f * 40 , SCREEN_HEIGHT / 100.0f * 15 , 0 , 0 , 1 , 1 , 2);
	SetTexture(12 , SCREEN_WIDTH / 100.0f * 60, SCREEN_HEIGHT / 100.0f * 6, SCREEN_WIDTH / 100.0f * 5 , SCREEN_WIDTH / 100.0f * 5 , 0 , 0 , 1 , 1 , 2);

	//���鏉����
	InitCastle(0);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitGameUI
//�Ԃ�l	: 
//����		: �Q�[��UI�I��
//////////////////////////////////////////////////////////////////////////////
void	uninitGameUI	( void )
{
	//�eUI�I��
	uninitBulletUI();

	//����I��
	UninitCastle();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateGameUI
//�Ԃ�l	: 
//����		: �Q�[��UI�X�V
//////////////////////////////////////////////////////////////////////////////
void	updateGameUI	( void )
{
	//�eUI�X�V
	updateBulletUI();

	// 
	int i = 0;
	for(i = 1 ; i < 6 ; i++)
	{
		//MoveUVTexture(i , 0.0002f , 1.0f);					// �e�N�X�`����UV�ړ�
	}

	// �i�s�x�ōX�V
	float fPosx = 0.0f;
	// �ő厞�ԂƎ擾
	int nMaxTime = GetTimeGame(0);
	// ���݂̎��Ԏ擾
	int nNowTime = GetTimeGameNow();

	if(nNowTime > nMaxTime)
	{
		nNowTime = nMaxTime;
	}

	// �i�s�x��S�����ŏo��
	g_par = (float)nNowTime / (float)nMaxTime;
	fPosx = 31.5f * g_par;
	// SCREEN_WIDTH / 100.0f * 60���犄���ő����Ă�����
	fPosx = SCREEN_WIDTH / 100.0f * 90- SCREEN_WIDTH / 100.0f * fPosx;
	if(fPosx <= SCREEN_WIDTH / 100.0f * 60)
	{
		fPosx = SCREEN_WIDTH / 100.0f * 60;
	}

		// 12�Ԗڂɓn���B
	SetPosTexture(12 , fPosx , SCREEN_HEIGHT / 100.0f * 6);					// �e�N�X�`���̃|�W�V���w��

	//����X�V
	UpdateCastle();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawGameUI
//�Ԃ�l	: 
//����		: �Q�[��UI�`��
//////////////////////////////////////////////////////////////////////////////
void	drawGameUI	( void )
{
	//�eUI�`��
	drawBulletUI();

	DrawTexture(2);

	//����`��
	DrawCastle();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: getParcent
//�Ԃ�l	: 
//����		: �Q�[���i�s�x�擾
//////////////////////////////////////////////////////////////////////////////
float	getParcent(void)
{
	return g_par;
}