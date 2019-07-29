//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	//SE/////////////////////////
	SELECT_TITLE = 0,
	CURSOR,
	DECISITON,
	SELECT_STAGE,

	//BGM////////////////////////
	TITLE_BGM,
	GAME_BGM_01,
	RESULT_BGM,

	// BGM
	BGM_TITLE,			// タイトルBGM
	BGM_STAGESELECT,	// ステージセレクトBGM
	BGM_GAME,			// ゲームBGM
	BGM_RESULT,			// リザルトBGM

	// SE
	// Title
	SE_PUSH,	// 決定音

	// StageSelect
	SE_STAGESELECT_PUSH,	// 決定音
	SE_STAGESELECT_CORSOR,	// カーソル移動
	SE_STAGESELECT_CANCEL,	// キャンセル

	// Game
	/*プレイヤー*/
	SE_GAME_WIN,						// 勝ち
	SE_GAME_LOSE,						// 負け
	SE_GAME_PLAEYR_FOOT_VILLEGE,		// 足音ー村
	SE_GAME_PLAEYR_FOOT_VOLCANO,		// 足音ー火山
	SE_GAME_PLAEYR_FOOT_SNOW,			// 足音ー雪山

	/*魔法*/
	SE_GAME_MAGIC_GO,				// 魔法発射-普通
	SE_GAME_MAGIC_GO_BOMM,			// 魔法発射-ボム
	SE_GAME_MAGIC_GO_DIFISION,		// 魔法発射-拡散
	SE_GAME_MAGIC_ON,				// 魔法発動-普通
	SE_GAME_MAGIC_ON_BOMM,			// 魔法発動-ボム
	SE_GAME_MAGIC_ON_DIFISION,		// 魔法発動-拡散
	SE_GAME_MAGIC_ON_KILL,			// 魔法発動-必殺技
	/*敵*/
	SE_GAME_ENEMY_KILL_SURAIMU,		// 殺-スライム
	SE_GAME_ENEMY_KILL_GOREMU,		// 殺-ゴーレム
	SE_GAME_ENEMY_KILL_PANSER,		// 殺-パンサー
	/*門*/
	SE_GAME_GATE_BREAK,			// 門が壊れちゃった
	SE_GAME_GATE_BREAK_ALL,		// 門が壊れちゃった、完全に
	/*城*/
	SE_GAME_CASTLE_BREAK,			// 城が壊れちゃった
	SE_GAME_CASTLE_BREAK_ALL,		// 城が壊れちゃった、完全に
	// Result
	SE_RESULT_NUMBER,		// ドラム
	SE_RESULT_NUMBER_ON,	// 数字決定
	SE_RESULT_RANK_C,		// ランクc
	SE_RESULT_RANK_B,		// ランクb
	SE_RESULT_RANK_A,		// ランクa
	SE_RESULT_RANK_S,		// ランクs
	
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
