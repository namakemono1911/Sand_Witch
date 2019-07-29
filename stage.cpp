//============================================
//  Stage関数  (Stage.cpp)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   年月日
//  修正日   年月日
//  修正内容:
//
//
//============================================

//============================================
//
//  インクルードファイル
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
//  マクロ定義
//
//============================================
#define STAGE_TIME_0 (5640) // ボスまでの時間-チュートリアル
#define STAGE_TIME_1 (6360) // ボスまでの時間-村-easy
#define STAGE_TIME_2 (5640) // ボスまでの時間-村-normal
#define STAGE_TIME_3 (5640) // ボスまでの時間-村-hard
#define STAGE_TIME_4 (5640) // ボスまでの時間-火山-easy
#define STAGE_TIME_5 (5640) // ボスまでの時間-火山-normal
#define STAGE_TIME_6 (5640) // ボスまでの時間-火山-hard
#define STAGE_TIME_7 (5640) // ボスまでの時間-雪山-easy
#define STAGE_TIME_8 (5640) // ボスまでの時間-雪山-normal
#define STAGE_TIME_9 (5640) // ボスまでの時間-雪山-hard

#define STAGE_NOTES_ENEMY (SCREEN_WIDTH + 20.0f)	// 敵を置く場所

//============================================
//
//  プロトタイプ宣言
//
//============================================


static NOTES_MODE g_aNotes[LINE_OBJ_MAX];
static int i;
static bool bBoss;
void ReStage(void) // ステージのinitで呼んで
{
	bBoss = false;
	i = 0;
}
STAGE_NUM	g_stageNum = STAGE_NUM_MAX;		//ステージナンバー

//============================================
//
//  名前  SetStage00関数
//  引数
//  戻り値
//  説明	チュートリアル
//
//============================================
void SetStage00(void)
{

	i++;	// タイム増加

	// 敵出現
	// レーン1
	// レーン2
	// レーン3
	// レーン4
	// stage_timeが超えたら、雑魚を検索して、いなければボス
	// ボス
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
//  名前  SetStage01関数
//  引数
//  戻り値
//  説明	村-easy
//
//============================================
void SetStage01(void)
{

	i++;	// タイム増加

	if(i == 60)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_TWO);
		SetHuman(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_TWO);
	}

	// 敵出現
	// レーン1///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// レーン2///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// レーン4///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// stage_timeが超えたら、雑魚を検索して、いなければボス
	if(i == STAGE_TIME_1)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_ONE);
	}
	// ボス
	if(i >= STAGE_TIME_1 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
	}

} // EO SetStage01

//============================================
//
//  名前  SetStage02関数
//  引数
//  戻り値
//  説明	村-noemal
//
//============================================
void SetStage02(void)
{

	i++;	// タイム増加

	// 敵出現
	if(i == 60)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_TWO , 100 , 100 , HUMAN_TWO);
		SetHuman(STAGE_NOTES_ENEMY , LINE_THREE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_TWO);
	}

	// 敵出現
	// レーン1///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// レーン2///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// レーン4///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// stage_timeが超えたら、雑魚を検索して、いなければボス
	if(i == STAGE_TIME_1)
	{
		SetHuman(STAGE_NOTES_ENEMY , LINE_ONE , 100 , 100 , HUMAN_ONE);
		SetHuman(STAGE_NOTES_ENEMY , LINE_FOUR , 100 , 100 , HUMAN_ONE);
	}
	// ボス
	if(i == STAGE_TIME_2 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
	}

} // EO SetStage02

//============================================
//
//  名前  SetStage03関数
//  引数
//  戻り値
//  説明	村-hard
//
//============================================
void SetStage03(void)
{

	i++;	// タイム増加

	// 敵出現
	// レーン1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_timeが超えたら、雑魚を検索して、いなければボス
	// ボス
	if(i == STAGE_TIME_3 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
	}

} // EO SetStage03

//============================================
//
//  名前  SetStage04関数
//  引数
//  戻り値
//  説明	火山-easy
//
//============================================
void SetStage04(void)
{

	i++;	// タイム増加

	// 敵出現
	// レーン1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_timeが超えたら、雑魚を検索して、いなければボス
	// ボス
	if(i == STAGE_TIME_4 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_TWO);
	}

} // EO SetStage04

//============================================
//
//  名前  SetStage05関数
//  引数
//  戻り値
//  説明	火山-noemal
//
//============================================
void SetStage05(void)
{

	i++;	// タイム増加

	// 敵出現
	// レーン1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_timeが超えたら、雑魚を検索して、いなければボス
	// ボス
	if(i == STAGE_TIME_5 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_TWO);
	}

} // EO SetStage05

//============================================
//
//  名前  SetStage06関数
//  引数
//  戻り値
//  説明	火山-hard
//
//============================================
void SetStage06(void)
{

	i++;	// タイム増加

	// 敵出現
	// レーン1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_timeが超えたら、雑魚を検索して、いなければボス
	// ボス
	if(i == STAGE_TIME_6  && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_TWO);
	}

} // EO SetStage06

//============================================
//
//  名前  SetStage07関数
//  引数
//  戻り値
//  説明	雪山-easy
//
//============================================
void SetStage07(void)
{

	i++;	// タイム増加

	// 敵出現
	// レーン1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_timeが超えたら、雑魚を検索して、いなければボス
	// ボス
	if(i == STAGE_TIME_7 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_THREE);
	}

} // EO SetStage07

//============================================
//
//  名前  SetStage08関数
//  引数
//  戻り値
//  説明	雪山-noemal
//
//============================================
void SetStage08(void)
{

	i++;	// タイム増加

	// 敵出現
	// レーン1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_timeが超えたら、雑魚を検索して、いなければボス
	// ボス
	if(i == STAGE_TIME_8 && GetZeroNotes() == true && bBoss == false)
	{
		SetWarning(0 , WARNING_BOSS);
		bBoss = true;
		SetBoss(SCREEN_WIDTH * 1.25f , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_THREE);
	}

} // EO SetStage08

//============================================
//
//  名前  SetStage09関数
//  引数
//  戻り値
//  説明	雪山-hard
//
//============================================
void SetStage09(void)
{

	i++;	// タイム増加

	// 敵出現
	// レーン1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// レーン4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stage_timeが超えたら、雑魚を検索して、いなければボス
	// ボス
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
	case 0:	// チュートリアル
		return STAGE_TIME_0;
		break;
	case 1:	// 村-easy
		return STAGE_TIME_1;
		break;
	case 2:	// 村-normal
		return STAGE_TIME_2;
		break;
	case 3:	// 村-hard
		return STAGE_TIME_3;
		break;
	case 4:	// 火山-easy
		return STAGE_TIME_4;
		break;
	case 5:	// 火山-normal
		return STAGE_TIME_5;
		break;
	case 6:	// 火山-hard
		return STAGE_TIME_6;
		break;
	case 7:	// 雪山-easy
		return STAGE_TIME_7;
		break;
	case 8:	// 雪山-normal
		return STAGE_TIME_8;
		break;
	case 9:	// 雪山-hard
		return STAGE_TIME_9;
		break;
	}
	return -1;
}

//============================================
//
//  名前  getStgNum関数
//  引数
//  戻り値
//  説明
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
//  名前  resetStgNum関数
//  引数
//  戻り値
//  説明
//
//============================================
void resetStgNum(void)
{
	g_stageNum = STAGE_NUM_MAX;
}
