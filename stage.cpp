//============================================
//  Stage�֐�  (Stage.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   �N����
//  �C����   �N����
//  �C�����e:
//
//
//============================================

//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include <stdlib.h>
#include "main.h"
#include "stage.h"
#include "notes.h"
#include "boss.h"
#include "human.h"
#include "warning.h"
#include "tutorial.h"
#include "input.h"

//============================================
//
//  �}�N����`
//
//============================================
#define STAGE_TIME_0 (5640) // �{�X�܂ł̎���-�`���[�g���A��
#define STAGE_TIME_1 (6360) // �{�X�܂ł̎���-��-easy
#define STAGE_TIME_2 (5640) // �{�X�܂ł̎���-��-normal
#define STAGE_TIME_3 (5640) // �{�X�܂ł̎���-��-hard
#define STAGE_TIME_4 (5640) // �{�X�܂ł̎���-�ΎR-easy
#define STAGE_TIME_5 (5640) // �{�X�܂ł̎���-�ΎR-normal
#define STAGE_TIME_6 (5640) // �{�X�܂ł̎���-�ΎR-hard
#define STAGE_TIME_7 (5640) // �{�X�܂ł̎���-��R-easy
#define STAGE_TIME_8 (5640) // �{�X�܂ł̎���-��R-normal
#define STAGE_TIME_9 (5640) // �{�X�܂ł̎���-��R-hard

#define STAGE_NOTES_ENEMY (SCREEN_WIDTH + 20.0f)	// �G��u���ꏊ

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================


static NOTES_MODE g_aNotes[LINE_OBJ_MAX];
static int i;
static bool bBoss;
void ReStage(void) // �X�e�[�W��init�ŌĂ��
{
	bBoss = false;
	i = 0;
}
STAGE_NUM	g_stageNum = STAGE_NUM_MAX;		//�X�e�[�W�i���o�[

//============================================
//
//  ���O  SetStage00�֐�
//  ����
//  �߂�l
//  ����	�`���[�g���A��
//
//============================================
void SetStage00(void)
{

	i++;	// �^�C������

	// �G�o��
	// ���[��1
	// ���[��2
	// ���[��3
	// ���[��4
	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	// �{�X
	if(i == STAGE_TIME_0 && GetZeroNotes() == true && bBoss == false)
	{
		bBoss = true;
		SetWarning(0 , WARNING_BOSS);
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		startPopdown();
	}

} // EO SetStage00

//============================================
//
//  ���O  SetStage01�֐�
//  ����
//  �߂�l
//  ����	��-easy
//
//============================================
void SetStage01(void)
{

	i++;	// �^�C������

	if(i == 60)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_TWO);
		SetHuman(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_TWO);
	}

	// �G�o��
	// ���[��1///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i == 2100)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_ONE);
	}

	if(i == 4200)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_ONE);
	}

	if(i == 5100)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_FOUR);
	}

	if(i == 5500)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
	}

	if(i == 6060)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_ONE);
	}

	if(i == 7200)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_ONE);
	}

	// ���[��2///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i == 1620)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_ONE);
	}

	if(i == 2940)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FIVE);
	}

	if(i == 3300)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_TWO);
	}

	if(i == 4080)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FOUR);
	}

	if(i == 4680)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_ONE);
	}

	if(i == 5000)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_ONE);
	}

	if(i == 5400)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FIVE);
	}

	if(i == 6000)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_ONE);
	}

	if(i == 6540)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FOUR);
	}

	if(i == 6960)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FIVE);
	}

	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i == 300)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_ONE);
	}

	if(i == 2160)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_ONE);
	}

	if(i == 3300)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , HUMAN_ONE);
	}

	if(i == 4260)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_FIVE);
	}

	if(i == 4740)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_FOUR);
	}

	if(i == 6600)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_FIVE);
	}

	// ���[��4///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i == 1000)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_ONE);
	}

	if(i == 2580)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , NOTES_ONE);
	}

	if(i == 4320)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , NOTES_FOUR);
	}

	if(i == 4740)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , NOTES_ONE);
	}

	if(i == 5400)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , NOTES_ONE);
	}

	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	if(i == STAGE_TIME_1)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_ONE);
	}
	// �{�X
	if(i >= STAGE_TIME_1 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
	}

} // EO SetStage01

//============================================
//
//  ���O  SetStage02�֐�
//  ����
//  �߂�l
//  ����	��-noemal
//
//============================================
void SetStage02(void)
{

	i++;	// �^�C������

	// �G�o��
	if(i == 60)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_TWO);
		SetHuman(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_TWO);
	}

	// �G�o��
	// ���[��1///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i == 2100)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_ONE);
	}

	if(i == 4200)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_ONE);
	}

	if(i == 5100)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_FOUR);
	}

	if(i == 5500)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
	}

	if(i == 6060)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_ONE);
	}

	if(i == 7200)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , NOTES_ONE);
	}

	// ���[��2///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i == 1620)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_ONE);
	}

	if(i == 2000)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_ONE);
	}

	if(i == 2940)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FIVE);
	}

	if(i == 3300)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_TWO);
	}

	if(i == 4080)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FOUR);
	}

	if(i == 4680)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_ONE);
	}

	if(i == 5000)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_ONE);
	}

	if(i == 5400)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FIVE);
	}

	if(i == 6000)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_ONE);
	}

	if(i == 6540)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FOUR);
	}

	if(i == 6960)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , NOTES_FIVE);
	}

	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i == 300)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_ONE);
	}

	if(i == 2160)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_ONE);
	}

	if(i == 3300)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , HUMAN_ONE);
	}

	if(i == 4260)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_FIVE);
	}

	if(i == 4740)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_FOUR);
	}

	if(i == 6600)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , NOTES_FIVE);
	}

	// ���[��4///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i == 1000)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_ONE);
	}

	if(i == 2580)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , NOTES_FIVE);
	}

	if(i == 4320)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , NOTES_FOUR);
	}

	if(i == 4740)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , NOTES_ONE);
	}

	if(i == 5400)
	{
		SetNotes(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , NOTES_FOUR);
	}

	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	if(i == STAGE_TIME_1)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_ONE);
	}
	// �{�X
	if(i == STAGE_TIME_2 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
	}

} // EO SetStage02

//============================================
//
//  ���O  SetStage03�֐�
//  ����
//  �߂�l
//  ����	��-hard
//
//============================================
void SetStage03(void)
{

	i++;	// �^�C������

	// �G�o��
	// ���[��1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	// �{�X
	if(i == STAGE_TIME_3 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
	}

} // EO SetStage03

//============================================
//
//  ���O  SetStage04�֐�
//  ����
//  �߂�l
//  ����	�ΎR-easy
//
//============================================
void SetStage04(void)
{

	i++;	// �^�C������

	// �G�o��
	// ���[��1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	// �{�X
	if(i == STAGE_TIME_4 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_TWO);
	}

} // EO SetStage04

//============================================
//
//  ���O  SetStage05�֐�
//  ����
//  �߂�l
//  ����	�ΎR-noemal
//
//============================================
void SetStage05(void)
{

	i++;	// �^�C������

	// �G�o��
	// ���[��1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	// �{�X
	if(i == STAGE_TIME_5 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_TWO);
	}

} // EO SetStage05

//============================================
//
//  ���O  SetStage06�֐�
//  ����
//  �߂�l
//  ����	�ΎR-hard
//
//============================================
void SetStage06(void)
{

	i++;	// �^�C������

	// �G�o��
	// ���[��1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	// �{�X
	if(i == STAGE_TIME_6  && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_TWO);
	}

} // EO SetStage06

//============================================
//
//  ���O  SetStage07�֐�
//  ����
//  �߂�l
//  ����	��R-easy
//
//============================================
void SetStage07(void)
{

	i++;	// �^�C������

	// �G�o��
	// ���[��1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	// �{�X
	if(i == STAGE_TIME_7 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_THREE);
	}

} // EO SetStage07

//============================================
//
//  ���O  SetStage08�֐�
//  ����
//  �߂�l
//  ����	��R-noemal
//
//============================================
void SetStage08(void)
{

	i++;	// �^�C������

	// �G�o��
	// ���[��1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	// �{�X
	if(i == STAGE_TIME_8 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_THREE);
	}

} // EO SetStage08

//============================================
//
//  ���O  SetStage09�֐�
//  ����
//  �߂�l
//  ����	��R-hard
//
//============================================
void SetStage09(void)
{

	i++;	// �^�C������

	// �G�o��
	// ���[��1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���[��4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_time����������A�G�����������āA���Ȃ���΃{�X
	// �{�X
	if(i == STAGE_TIME_9 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_THREE);
	}

} // EO SetStage09

int GetTimeGame(int nStage)
{
	switch(nStage)
	{
	case 0:	// �`���[�g���A��
		return STAGE_TIME_0;
		break;
	case 1:	// ��-easy
		return STAGE_TIME_1;
		break;
	case 2:	// ��-normal
		return STAGE_TIME_2;
		break;
	case 3:	// ��-hard
		return STAGE_TIME_3;
		break;
	case 4:	// �ΎR-easy
		return STAGE_TIME_4;
		break;
	case 5:	// �ΎR-normal
		return STAGE_TIME_5;
		break;
	case 6:	// �ΎR-hard
		return STAGE_TIME_6;
		break;
	case 7:	// ��R-easy
		return STAGE_TIME_7;
		break;
	case 8:	// ��R-normal
		return STAGE_TIME_8;
		break;
	case 9:	// ��R-hard
		return STAGE_TIME_9;
		break;
	}
	return -1;
}

//============================================
//
//  ���O  getStgNum�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
STAGE_NUM getStgNum(void)
{
	return g_stageNum;
}

void setStgNum(STAGE_NUM stage)
{
	g_stageNum = stage;
}

//============================================
//
//  ���O  resetStgNum�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void resetStgNum(void)
{
	g_stageNum = STAGE_NUM_MAX;
}
