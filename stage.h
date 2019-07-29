//============================================
//  stage.cppのヘッダーファイル  (stage.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   年月日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _STAGE_H_
#define _STAGE_H_
//============================================
//
//  マクロ定義
//
//============================================


//============================================
//
//  インクルードファイル
//
//============================================


//============================================
//
//  構造体
//
//============================================
typedef enum
{
	STAGE_00 = 0,		//チュートリアル
	STAGE_01,			//村-easy
	STAGE_02,			//村-normal
	STAGE_03,			//村-hard
	STAGE_04,			//火山-easy
	STAGE_05,			//火山-norm
	STAGE_06,			//火山-hard
	STAGE_07,			//雪山-easy
	STAGE_08,			//雪山-norm
	STAGE_09,			//雪山 - hard
	STAGE_NUM_MAX,		//ステージの総数
}STAGE_NUM;



//============================================
//
//   プロトタイプ宣言
//
//============================================
// ランダムで実行(スコアで見る)
void SetStage00(void);	// チュートリアル
void SetStage01(void);	// 村-easy
void SetStage02(void);	// 村-normal
void SetStage03(void);	// 村-hard
void SetStage04(void);	// 火山-easy
void SetStage05(void);	// 火山-normal
void SetStage06(void);	// 火山-hard
void SetStage07(void);	// 雪山-easy
void SetStage08(void);	// 雪山-normal
void SetStage09(void);	// 雪山-hard

STAGE_NUM getStgNum(void);	//ステージナンバー取得
void setStgNum(STAGE_NUM stage);	//ステージナンバー設定
void resetStgNum(void);	//ステージナンバー初期化

int GetTimeGame(int nStage);
void ReStage(void); // ステージのinitで呼んで

#endif