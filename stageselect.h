//==========================================================================================
//	ステージセレクト処理[stageselect.cpp]
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
#ifndef _STAGESELECT_H_	//二重インクルード防止
#define _STAGESELECT_H_

//==========================================================================================
//	インクルードファイル
//==========================================================================================
//既定ヘッダ

//新規ヘッダ
#include "main.h"

//==========================================================================================
//	構造体定義
//==========================================================================================
typedef enum
{
	STAGESELECT_TEX_TITLE = 0,		//ステージセレクト文字
	STAGESELECT_TEX_TURORIAL,		//チュートリアル
	STAGESELECT_TEX_STAGE1,			//村アイコン
	STAGESELECT_TEX_STAGE2,			//雪山アイコン
	STAGESELECT_TEX_STAGE3,			//火山アイコン
	STAGESELECT_TEX_CURSOL,			//ステージカーソル
	STAGESELECT_TEX_STAGE1DIF1,		//村難易度易
	STAGESELECT_TEX_STAGE1DIF2,		//村難易度普
	STAGESELECT_TEX_STAGE1DIF3,		//村難易度難
	STAGESELECT_TEX_STAGE2DIF1,		//雪山難易度易
	STAGESELECT_TEX_STAGE2DIF2,		//雪山難易度普
	STAGESELECT_TEX_STAGE2DIF3,		//雪山難易度難
	STAGESELECT_TEX_STAGE3DIF1,		//火山難易度易
	STAGESELECT_TEX_STAGE3DIF2,		//火山難易度普
	STAGESELECT_TEX_STAGE3DIF3,		//火山難易度難
	STAGESELECT_TEX_DIFCURSOL,		//難易度カーソル

	STAGESELECT_TEX_BG_STAGE1,			//村アイコン
	STAGESELECT_TEX_BG_STAGE2,			//雪山アイコン
	STAGESELECT_TEX_BG_STAGE3,			//火山アイコン

	STAGESELECT_TEX_MAX,			//リザルトテクスチャ総数
} STAGESELECT_TEX_LABEL;	//テクスチャ用ラベル

typedef enum
{
	STAGESELECT_OBJ_BG = 0,		//背景画像
	STAGESELECT_OBJ_BGFADE,		//背景画像フェード
	STAGESELECT_OBJ_TITLE,		//ステージセレクト文字
	STAGESELECT_OBJ_TURORIAL,	//チュートリアル
	STAGESELECT_OBJ_STAGE1,		//村アイコン
	STAGESELECT_OBJ_STAGE2,		//雪山アイコン
	STAGESELECT_OBJ_STAGE3,		//火山アイコン
	STAGESELECT_OBJ_CURSOL,		//ステージカーソル
	STAGESELECT_OBJ_DIFCURSOL,	//難易度カーソル
	STAGESELECT_OBJ_STAGE1DIF1,	//村難易度易
	STAGESELECT_OBJ_STAGE1DIF2,	//村難易度普
	STAGESELECT_OBJ_STAGE1DIF3,	//村難易度難
	STAGESELECT_OBJ_STAGE2DIF1,	//雪山難易度易
	STAGESELECT_OBJ_STAGE2DIF2,	//雪山難易度普
	STAGESELECT_OBJ_STAGE2DIF3,	//雪山難易度難
	STAGESELECT_OBJ_STAGE3DIF1,	//火山難易度易
	STAGESELECT_OBJ_STAGE3DIF2,	//火山難易度普
	STAGESELECT_OBJ_STAGE3DIF3,	//火山難易度難
	STAGESELECT_OBJ_MAX,		//リザルトテクスチャ総数
} STAGESELECT_OBJ_LABEL;	//オブジェクト用ラベル

struct STAGESELECT
{
	D3DXVECTOR3		Pos;		//画像位置
	D3DXVECTOR3		Size;		//画像サイズ
	D3DXVECTOR2		UV;			//UV値
	D3DXVECTOR2		UVSize;		//UVサイズ
	STAGESELECT_TEX_LABEL	label;	//描画テクスチャ
	float			fAlpha;		//α値
	bool			bDraw;		//描画可否
};

//==========================================================================================
//	クラス定義
//==========================================================================================

//==========================================================================================
//	マクロ定義
//==========================================================================================
void InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);

//==========================================================================================
//	プロトタイプ宣言
//==========================================================================================


#endif