//==========================================================================================
//	ステージセレクト処理[stageselect.cpp]
//	Author : KAZUNORI MARUHASHI
//
//	Update :
//		YYYY/MM/DD	Updater :
//
//		2017/06/05	Updater : KAZUNORI MARUHASHI
//			・仕様書の内容は実装。
//			＊後は難易度選択後の処理、入れるならキャンセルSEの実装。
//			  define以外で弄りそうな所は JUMP で検索して飛んでください 
//
//		2017/06/04	Updater : KAZUNORI MARUHASHI
//			・Define関連だけ設定。
//			
//			
//	
//==========================================================================================

//==========================================================================================
// インクルードファイル
//==========================================================================================
#include "main.h"		//メイン処理
#include "input.h"		//入力処理
#include "inputX.h"		//入力処理
#include "sound.h"		//サウンド処理
#include "stageselect.h"		//ステージセレクト処理
#include "fade.h"
#include "stage.h"

//==========================================================================================
// マクロ定義
//==========================================================================================
//テクスチャ関係
#define STAGESELECT_TITLE_TEXTURENAME			"data/TEXTURE/STAGESELECT/stageSelectASC.png"		//ステージセレクト文字
#define STAGESELECT_TUTORIAL_TEXTURENAME		"data/TEXTURE/STAGESELECT/tutorialASC.png"			//チュートリアル文字
#define STAGESELECT_STAGE1_TEXTURENAME			"data/TEXTURE/STAGESELECT/stage01.png"				//村画像
#define STAGESELECT_STAGE2_TEXTURENAME			"data/TEXTURE/STAGESELECT/stage02.png"				//雪山画像
#define STAGESELECT_STAGE3_TEXTURENAME			"data/TEXTURE/STAGESELECT/stage03.png"				//火山画像
#define STAGESELECT_STAGECURSOR_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageSelectCursor.png"	//ステージセレクトカーソル
#define STAGESELECT_STAGE1DIF1_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif1.png"			//村難易度易
#define STAGESELECT_STAGE1DIF2_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif2.png"			//村難易度普
#define STAGESELECT_STAGE1DIF3_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif3.png"			//村難易度難
#define STAGESELECT_STAGE2DIF1_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif1.png"			//雪山難易度易
#define STAGESELECT_STAGE2DIF2_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif2.png"			//雪山難易度普
#define STAGESELECT_STAGE2DIF3_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif3.png"			//雪山難易度難
#define STAGESELECT_STAGE3DIF1_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif1.png"			//火山難易度易
#define STAGESELECT_STAGE3DIF2_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif2.png"			//火山難易度普
#define STAGESELECT_STAGE3DIF3_TEXTURENAME		"data/TEXTURE/STAGESELECT/stageDif3.png"			//火山難易度難
#define STAGESELECT_DIFCURSOR_TEXTURENAME		"data/TEXTURE/STAGESELECT/difSelectCursor.png"		//難易度カーソル

#define STAGESELECT_STAGE1_BG_TEXTURENAME			"data/TEXTURE/GAME/BG/stageBG01.jpg"			//村画像
#define STAGESELECT_STAGE2_BG_TEXTURENAME			"data/TEXTURE/GAME/BG/stageBG02.jpg"			//雪山画像
#define STAGESELECT_STAGE3_BG_TEXTURENAME			"data/TEXTURE/GAME/BG/stageBG03.jpg"			//火山画像

//=========位置関連(座標は中心を指定)==========//
//背景
#define STAGESELECT_BG_POSX				(SCREEN_WIDTH  * 0.5f)
#define STAGESELECT_BG_POSY				(SCREEN_HEIGHT * 0.5f)
#define STAGESELECT_BG_SIZEX			(SCREEN_WIDTH)
#define STAGESELECT_BG_SIZEY			(SCREEN_HEIGHT)

//フェード用背景
#define STAGESELECT_BGFADE_POSX			(STAGESELECT_BG_POSX)
#define STAGESELECT_BGFADE_POSY			(STAGESELECT_BG_POSY)
#define STAGESELECT_BGFADE_SIZEX		(STAGESELECT_BG_SIZEX)
#define STAGESELECT_BGFADE_SIZEY		(STAGESELECT_BG_SIZEY)

//ステージセレクト文字
#define STAGESELECT_TITLE_POSX			(SCREEN_WIDTH  * 0.25f)
#define STAGESELECT_TITLE_POSY			(SCREEN_HEIGHT * 0.12f)
#define STAGESELECT_TITLE_SIZEX			(SCREEN_WIDTH  * 0.3f)
#define STAGESELECT_TITLE_SIZEY			(SCREEN_HEIGHT * 0.25f)

//チュートリアル
#define STAGESELECT_TUTORIAL_POSX		(SCREEN_WIDTH  * 0.23f)
#define STAGESELECT_TUTORIAL_POSY		(SCREEN_HEIGHT * 0.35f)
#define STAGESELECT_TUTORIAL_SIZEX		(SCREEN_WIDTH  * 0.17f)
#define STAGESELECT_TUTORIAL_SIZEY		(SCREEN_HEIGHT * 0.17f)

//=================ここから左原点========================//
//横幅が左が原点になります。縦は通常通りです
//村
#define STAGESELECT_STAGE1_POSX			(SCREEN_WIDTH  * 0.15f)
#define STAGESELECT_STAGE1_POSY			(STAGESELECT_TUTORIAL_POSY + SCREEN_HEIGHT * 0.17f)
#define STAGESELECT_STAGE1_SIZEX		(STAGESELECT_TUTORIAL_SIZEX)
#define STAGESELECT_STAGE1_SIZEY		(STAGESELECT_TUTORIAL_SIZEY)

//雪山
#define STAGESELECT_STAGE2_POSX			(STAGESELECT_STAGE1_POSX)
#define STAGESELECT_STAGE2_POSY			(STAGESELECT_STAGE1_POSY + SCREEN_HEIGHT * 0.17f )
#define STAGESELECT_STAGE2_SIZEX		(STAGESELECT_STAGE1_SIZEX  )
#define STAGESELECT_STAGE2_SIZEY		(STAGESELECT_STAGE1_SIZEY )

//火山
#define STAGESELECT_STAGE3_POSX			(STAGESELECT_STAGE1_POSX)
#define STAGESELECT_STAGE3_POSY			(STAGESELECT_STAGE2_POSY + SCREEN_HEIGHT * 0.17f )
#define STAGESELECT_STAGE3_SIZEX		(STAGESELECT_STAGE1_SIZEX  )
#define STAGESELECT_STAGE3_SIZEY		(STAGESELECT_STAGE1_SIZEY )

//共通
#define	STAGESELECT_STAGE_LONGSIZEX		(SCREEN_WIDTH  * 0.70f)	//選択時右へどれ程伸ばすか
#define STAGESELECT_STAGE_UV			(0.3f)		//ステージアイコン縮小時のUV
//=================ここまで左原点========================//

//ステージセレクトカーソル
#define STAGESELECT_CURSOL_POSX			(SCREEN_WIDTH  * 0.1f)
#define STAGESELECT_CURSOL_POSY			(STAGESELECT_STAGE1_POSY)
#define STAGESELECT_CURSOL_SIZEX		(SCREEN_WIDTH  * 0.08f)
#define STAGESELECT_CURSOL_SIZEY		(SCREEN_HEIGHT * 0.1f)

//村易
#define STAGESELECT_STAGE1DIF1_POSX		(SCREEN_WIDTH  * 0.50f)
#define STAGESELECT_STAGE1DIF1_POSY		(STAGESELECT_STAGE1_POSY )
#define STAGESELECT_STAGE1DIF1_SIZEX	(SCREEN_WIDTH  * 0.05f)
#define STAGESELECT_STAGE1DIF1_SIZEY	(SCREEN_HEIGHT * 0.08f)

//村普
#define STAGESELECT_STAGE1DIF2_POSX		(SCREEN_WIDTH  * 0.60f)
#define STAGESELECT_STAGE1DIF2_POSY		(STAGESELECT_STAGE1DIF1_POSY )
#define STAGESELECT_STAGE1DIF2_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX  )
#define STAGESELECT_STAGE1DIF2_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//村難
#define STAGESELECT_STAGE1DIF3_POSX		(SCREEN_WIDTH  * 0.70f)
#define STAGESELECT_STAGE1DIF3_POSY		(STAGESELECT_STAGE1DIF1_POSY )
#define STAGESELECT_STAGE1DIF3_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX  )
#define STAGESELECT_STAGE1DIF3_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//雪山易
#define STAGESELECT_STAGE2DIF1_POSX		(STAGESELECT_STAGE1DIF1_POSX  )
#define STAGESELECT_STAGE2DIF1_POSY		(STAGESELECT_STAGE2_POSY )
#define STAGESELECT_STAGE2DIF1_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX  )
#define STAGESELECT_STAGE2DIF1_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//雪山普
#define STAGESELECT_STAGE2DIF2_POSX		(STAGESELECT_STAGE1DIF2_POSX  )
#define STAGESELECT_STAGE2DIF2_POSY		(STAGESELECT_STAGE2_POSY )
#define STAGESELECT_STAGE2DIF2_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX  )
#define STAGESELECT_STAGE2DIF2_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//雪山難
#define STAGESELECT_STAGE2DIF3_POSX		(STAGESELECT_STAGE1DIF3_POSX  )
#define STAGESELECT_STAGE2DIF3_POSY		(STAGESELECT_STAGE2_POSY	  )
#define STAGESELECT_STAGE2DIF3_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX )
#define STAGESELECT_STAGE2DIF3_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//火山易
#define STAGESELECT_STAGE3DIF1_POSX		(STAGESELECT_STAGE1DIF1_POSX  )
#define STAGESELECT_STAGE3DIF1_POSY		(STAGESELECT_STAGE3_POSY	  )
#define STAGESELECT_STAGE3DIF1_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX )
#define STAGESELECT_STAGE3DIF1_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )
		
//火山普
#define STAGESELECT_STAGE3DIF2_POSX		(STAGESELECT_STAGE1DIF2_POSX  )
#define STAGESELECT_STAGE3DIF2_POSY		(STAGESELECT_STAGE3_POSY	  )
#define STAGESELECT_STAGE3DIF2_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX )
#define STAGESELECT_STAGE3DIF2_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )
		
//火山難
#define STAGESELECT_STAGE3DIF3_POSX		(STAGESELECT_STAGE1DIF3_POSX  )
#define STAGESELECT_STAGE3DIF3_POSY		(STAGESELECT_STAGE3_POSY	  )
#define STAGESELECT_STAGE3DIF3_SIZEX	(STAGESELECT_STAGE1DIF1_SIZEX )
#define STAGESELECT_STAGE3DIF3_SIZEY	(STAGESELECT_STAGE1DIF1_SIZEY )

//難易度セレクトカーソル(POSは後に設定するので無し)
#define STAGESELECT_DIFCURSOL_SIZEX		(SCREEN_WIDTH  * 0.06f)
#define STAGESELECT_DIFCURSOL_SIZEY		(SCREEN_HEIGHT * 0.09f)

//ステージ項目最大数
#define STAGESELECT_NUM (4)
#define STAGESELECT_DIF_NUM (3)
#define ONESECOND_FRAME (60)	//１秒のフレーム数
#define STAGEBAR_MOVE_FRAME (30)	//ステージポリゴンの伸縮フレーム数
#define BG_FADE_FRAME (ONESECOND_FRAME * 2)		//背景のフェードフレーム

#define DICIDION_KEY (DIK_Z)	//決定キー
#define CANCEL_KEY (DIK_X)		//キャンセルキー

//==========================================================================================
// 構造体定義
//==========================================================================================


//==========================================================================================
// プロトタイプ宣言
//==========================================================================================
HRESULT MakeVertexStageSelect(LPDIRECT3DDEVICE9 pDevice);
void CreateTextureStageselect(LPDIRECT3DDEVICE9 pDevice);

void SelectStage(void);				//ステージ選択処理
void SelectDifficulty(void);		//難易度選択処理
void SelectStageBarExtend(void);	//ステージバー引き延ばし処理
void SelectDifficultyCancel(void);	//ステージバー縮小処理

//==========================================================================================
// グローバル変数
//==========================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferStageSelect = NULL;
STAGESELECT g_StageSelectObj[STAGESELECT_OBJ_MAX];
LPDIRECT3DTEXTURE9 g_pTextureStageSelect[STAGESELECT_TEX_MAX] = {};	//テクスチャインターフェース

static int g_iStageCursor;		//現在選んでいるステージ
static int g_iSelectDifCursor;	//現在選んでいる難易度
static int g_iPhase;			//処理内容
static int g_iFrame;			//フレーム数カウント
static int g_ibgFrame;			//背景用フレーム数カウント

//==========================================================================================
// 初期化処理
//==========================================================================================
void InitStageSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得

	//フェードイン
	startFadeIn(60, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//頂点の設定
	if(FAILED(MakeVertexStageSelect(pDevice)))
	{
		MessageBox(NULL, "頂点バッファの設定に失敗しました。", " ", MB_OK);
		return;
	}

	//テクスチャ生成用関数
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

	//固有値以外一括設定
	for(int i = 0; i < STAGESELECT_OBJ_MAX; i++){
		g_StageSelectObj[i].fAlpha = 1.0f;
		g_StageSelectObj[i].bDraw = true;
		g_StageSelectObj[i].UV = D3DXVECTOR2(0.0f, 0.0f);
		g_StageSelectObj[i].UVSize = D3DXVECTOR2(1.0f, 1.0f);
	}

	//難易度関連非描画
	for(int i = STAGESELECT_OBJ_STAGE1DIF1; i <= STAGESELECT_OBJ_STAGE3DIF3; i++){
		g_StageSelectObj[i].fAlpha = 0.0f;
		g_StageSelectObj[i].bDraw = false;
	}

	//ステージアイコンの初期UVサイズの設定
	g_StageSelectObj[STAGESELECT_OBJ_STAGE1].UVSize.x = STAGESELECT_STAGE_UV;
	g_StageSelectObj[STAGESELECT_OBJ_STAGE2].UVSize.x = STAGESELECT_STAGE_UV;
	g_StageSelectObj[STAGESELECT_OBJ_STAGE3].UVSize.x = STAGESELECT_STAGE_UV;


	//難易度選択非表示
	g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].bDraw = false;

	//フェードのα値0
	g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha = 0.0f;

	g_iStageCursor = 0;		//現在選んでいるステージ（初期：チュートリアル）
	g_iSelectDifCursor = 0;	//現在選んでいる難易度（初期：易）
	g_iPhase = 0;			//処理内容
	g_ibgFrame = 0;

	//BGM再生
	PlaySound(BGM_STAGESELECT);
}

//==========================================================================================
// 終了処理
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
// 更新処理
//==========================================================================================
void UpdateStageSelect(void)
{
	switch(g_iPhase){
	//ステージの選択
	case 0:
		//ステージの選択
		SelectStage();			

		break;

	//ステージバーの引き伸ばし
	case 1:
		//ステージバーの引き伸ばし
		SelectStageBarExtend();

		break;

	//難易度選択
	case 2:
		//難易度選択
		SelectDifficulty();	

		break;

	//ステージバー縮小
	case 3:
		//ステージバー縮小
		SelectDifficultyCancel();	
		
		break;

	default:
		break;
	}
	
	//======背景フェード
	if(g_StageSelectObj[STAGESELECT_OBJ_BG].label != g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label){
		g_ibgFrame++;

		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha = (1.0f / ONESECOND_FRAME) * g_ibgFrame;
		if(g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha >= 1.0f){
			g_StageSelectObj[STAGESELECT_OBJ_BG].label = g_StageSelectObj[STAGESELECT_OBJ_BGFADE].label;
			g_ibgFrame = 0;
		}
	}

	
	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ
	//仮想アドレスを取得する
	g_pVtxBufferStageSelect -> Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	for(int VtxLoop = 0; VtxLoop < STAGESELECT_OBJ_MAX; VtxLoop++){
		if(g_StageSelectObj[VtxLoop].bDraw == true){
			if(VtxLoop == STAGESELECT_OBJ_STAGE1 || VtxLoop == STAGESELECT_OBJ_STAGE2 || VtxLoop == STAGESELECT_OBJ_STAGE3)
			{
				//頂点座標の設定（左上原点）（x, y, z）
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
				//頂点座標の設定（x, y, z）
				pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x - g_StageSelectObj[VtxLoop].Size.x * 0.5f,
													g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x * 0.5f,
													g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x - g_StageSelectObj[VtxLoop].Size.x * 0.5f,
													g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);

				pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x * 0.5f,
													g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y * 0.5f, 0.0f);		
			}
			//カラーの設定
			pVtx[0+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_StageSelectObj[VtxLoop].fAlpha);
			pVtx[1+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_StageSelectObj[VtxLoop].fAlpha);
			pVtx[2+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_StageSelectObj[VtxLoop].fAlpha);
			pVtx[3+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_StageSelectObj[VtxLoop].fAlpha);

			//テクスチャ―座標の設定
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
// 描画処理
//==========================================================================================
void DrawStageSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得
	
	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferStageSelect,
							  0,					//オフセット
							  sizeof(VERTEX2D));		//ストライド量

	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	//ポリゴンの描画
	for(int iDraw = 0; iDraw < STAGESELECT_OBJ_MAX; iDraw++){
		//描画をする場合
		if(g_StageSelectObj[iDraw].bDraw == true){
			
			pDevice -> SetTexture(0, g_pTextureStageSelect[g_StageSelectObj[iDraw].label]);

			//プリミティブの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
										iDraw * 4,					//オフセット(頂点数)
										NUM_POLYGON);			//プリミティブ数
		}
	}
}

//==========================================================================================
// 頂点の生成
//==========================================================================================
HRESULT MakeVertexStageSelect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ

	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX2D)*NUM_VERTEX*STAGESELECT_OBJ_MAX,	//確保したい頂点バッファの数＊頂点数
								  D3DUSAGE_WRITEONLY,	//確保した後中を見ることはできない
								  FVF_VERTEX_2D,		//一応書かずとも平気
								  D3DPOOL_MANAGED,		//メモリ管理をどうするか(これはお任せ)
								  &g_pVtxBufferStageSelect,
								  NULL)))
	{
		return E_FAIL;
	}

	//仮想アドレスを取得する
	g_pVtxBufferStageSelect -> Lock(0, 0, (void**)&pVtx, 0);

	for(int VtxLoop = 0; VtxLoop < STAGESELECT_OBJ_MAX; VtxLoop++){

		//頂点座標の設定（x, y, z）
		pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x - g_StageSelectObj[VtxLoop].Size.x,
											g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y, 0.0f);

		pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x,
											g_StageSelectObj[VtxLoop].Pos.y - g_StageSelectObj[VtxLoop].Size.y, 0.0f);

		pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x - g_StageSelectObj[VtxLoop].Size.x,
											g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y, 0.0f);

		pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_StageSelectObj[VtxLoop].Pos.x + g_StageSelectObj[VtxLoop].Size.x,
											g_StageSelectObj[VtxLoop].Pos.y + g_StageSelectObj[VtxLoop].Size.y, 0.0f);

		//rhwの設定(必ず1.0f)
		pVtx[0+4*VtxLoop].rhw =
		pVtx[1+4*VtxLoop].rhw =
		pVtx[2+4*VtxLoop].rhw = 
		pVtx[3+4*VtxLoop].rhw = 1.0f;

		//カラーの設定
		pVtx[0+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[1+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[2+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[3+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);

		//テクスチャ―座標の設定
		pVtx[0+4*VtxLoop].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1+4*VtxLoop].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2+4*VtxLoop].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+4*VtxLoop].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	g_pVtxBufferStageSelect -> Unlock();

	return S_OK;
}

//==========================================================================================
// テクスチャ生成
//==========================================================================================
void CreateTextureStageselect(LPDIRECT3DDEVICE9 pDevice)
{
	UINT nID;  //メッセージボックスの返り値を入れる

	//テクスチャ取得
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_TITLE_TEXTURENAME,
		&g_pTextureStageSelect[0] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_TITLE_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_TUTORIAL_TEXTURENAME,
		&g_pTextureStageSelect[1] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_TUTORIAL_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1_TEXTURENAME,
		&g_pTextureStageSelect[2] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE1_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2_TEXTURENAME,
		&g_pTextureStageSelect[3] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE2_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3_TEXTURENAME,
		&g_pTextureStageSelect[4] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE3_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGECURSOR_TEXTURENAME,
		&g_pTextureStageSelect[5] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGECURSOR_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1DIF1_TEXTURENAME,
		&g_pTextureStageSelect[6] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE1DIF1_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1DIF2_TEXTURENAME,
		&g_pTextureStageSelect[7] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE1DIF2_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1DIF3_TEXTURENAME,
		&g_pTextureStageSelect[8] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE1DIF3_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2DIF1_TEXTURENAME,
		&g_pTextureStageSelect[9] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE2DIF1_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2DIF2_TEXTURENAME,
		&g_pTextureStageSelect[10] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE2DIF2_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2DIF3_TEXTURENAME,
		&g_pTextureStageSelect[11] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE2DIF3_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3DIF1_TEXTURENAME,
		&g_pTextureStageSelect[12] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE3DIF1_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3DIF2_TEXTURENAME,
		&g_pTextureStageSelect[13] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE3DIF2_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3DIF3_TEXTURENAME,
		&g_pTextureStageSelect[14] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE3DIF3_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_DIFCURSOR_TEXTURENAME,
		&g_pTextureStageSelect[15] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_DIFCURSOR_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE1_BG_TEXTURENAME,
		&g_pTextureStageSelect[16] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE1_BG_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE2_BG_TEXTURENAME,
		&g_pTextureStageSelect[17] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE2_BG_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		STAGESELECT_STAGE3_BG_TEXTURENAME,
		&g_pTextureStageSelect[18] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","STAGESELECT_STAGE3_BG_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
}

//==========================================================================================
// ステージ選択処理
//==========================================================================================
void SelectStage(void)
{
	//上下移動
	if(GetKeyboardTrigger(DIK_DOWN) || GetKeyXInputTrigger(XINPUT_DPAD_DOWN)){
		//選択SE再生
		PlaySound(SE_STAGESELECT_CORSOR);
		g_iStageCursor++;

		g_ibgFrame = 0;
		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha = 0.0f;
	}else
	if(GetKeyboardTrigger(DIK_UP) || GetKeyXInputTrigger(XINPUT_DPAD_UP)){
		//選択SE再生
		PlaySound(SE_STAGESELECT_CORSOR);
		g_iStageCursor--;

		g_ibgFrame = 0;
		g_StageSelectObj[STAGESELECT_OBJ_BGFADE].fAlpha = 0.0f;
	}

	//限界時ループ
	if(g_iStageCursor > STAGESELECT_NUM-1){
		g_iStageCursor = 0;
	}else
	if(g_iStageCursor < 0){
		g_iStageCursor = STAGESELECT_NUM-1;
	}

	//カーソル位置移動
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

	//決定キー押下時
	if(GetKeyboardTrigger(DICIDION_KEY) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A)){
		//決定SE再生
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
// 難易度選択処理
//==========================================================================================
void SelectDifficulty(void)
{
	g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].bDraw = true;

	//左右移動
	if(GetKeyboardTrigger(DIK_LEFT) || GetKeyXInputTrigger(XINPUT_DPAD_LEFT)){
		//選択SE再生
		PlaySound(SE_STAGESELECT_CORSOR);
		g_iSelectDifCursor--;
	}else
	if(GetKeyboardTrigger(DIK_RIGHT) || GetKeyXInputTrigger(XINPUT_DPAD_RIGHT)){
		//選択SE再生
		PlaySound(SE_STAGESELECT_CORSOR);
		g_iSelectDifCursor++;
	}

	//左右ループ
	if(g_iSelectDifCursor > STAGESELECT_DIF_NUM-1){
		g_iSelectDifCursor = 0;
	}else
	if(g_iSelectDifCursor < 0){
		g_iSelectDifCursor = STAGESELECT_DIF_NUM-1;
	}

	//カーソル位置移動
	switch(g_iStageCursor){
	case 1:
		g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].Pos.y;

		//各難移動の位置へ移動
		if	   (g_iSelectDifCursor == 0){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].Pos.x;}
		else if(g_iSelectDifCursor == 1){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].Pos.x;}
		else if(g_iSelectDifCursor == 2){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].Pos.x;}
		break;
	case 2:
		g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].Pos.y;

		//各難移動の位置へ移動
		if	   (g_iSelectDifCursor == 0){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].Pos.x;}
		else if(g_iSelectDifCursor == 1){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].Pos.x;}
		else if(g_iSelectDifCursor == 2){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].Pos.x;}
		break;
	case 3:
		g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.y = g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].Pos.y;

		//各難移動の位置へ移動
		if	   (g_iSelectDifCursor == 0){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF1].Pos.x;}
		else if(g_iSelectDifCursor == 1){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF2].Pos.x;}
		else if(g_iSelectDifCursor == 2){g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].Pos.x = g_StageSelectObj[STAGESELECT_OBJ_STAGE3DIF3].Pos.x;}
		break;
	default:
		break;
	}

	//決定キー押下時
	if(GetKeyboardTrigger(DICIDION_KEY) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A)){
		//決定SE再生
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

		//フェードアウト
		startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), GAME_MODE);
	}
	//キャンセルキー押下時
	else if(GetKeyboardTrigger(CANCEL_KEY) || GetKeyXInputTrigger(XINPUT_GAMEPAD_B)){
		//JUMP
		//キャンセルSE再生
		PlaySound(SE_STAGESELECT_CANCEL);

		g_StageSelectObj[STAGESELECT_OBJ_DIFCURSOL].bDraw = false;
		g_iSelectDifCursor = 0;
		g_iPhase = 3;
	}
}

//==========================================================================================
// ステージバー引き延ばし処理
//==========================================================================================
void SelectStageBarExtend(void)
{
	//フレームカウント
	g_iFrame++;

	//ステージバーの引き延ばし処理
	if(g_iFrame <= STAGEBAR_MOVE_FRAME){
		//カーソル位置移動
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
			//カーソル位置移動
			switch(g_iStageCursor){
			case 1:
				//描画可
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].bDraw = true;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				break;
			case 2:
				//描画可
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].bDraw = true;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].bDraw = true;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].fAlpha = (1.0f / ONESECOND_FRAME) * (g_iFrame - STAGEBAR_MOVE_FRAME);
				break;
			case 3:
				//描画可
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
// ステージバー縮小処理
//==========================================================================================
void SelectDifficultyCancel(void)
{
	//フレームカウント
	g_iFrame++;

	//難易度の表示の消去
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
		//バーを下に戻す
		if(g_iFrame <= ONESECOND_FRAME + STAGEBAR_MOVE_FRAME){
			switch(g_iStageCursor){
			case 1:
				//描画可
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF1].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF2].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1DIF3].bDraw = false;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE1].Size.x = STAGESELECT_STAGE1_SIZEX + (STAGESELECT_STAGE_LONGSIZEX / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));
				g_StageSelectObj[STAGESELECT_OBJ_STAGE1].UVSize.x = STAGESELECT_STAGE_UV + ((1.0f - STAGESELECT_STAGE_UV) / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));

				break;
			case 2:
				//描画可
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF1].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF2].bDraw = false;
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2DIF3].bDraw = false;

				g_StageSelectObj[STAGESELECT_OBJ_STAGE2].Size.x = STAGESELECT_STAGE2_SIZEX + (STAGESELECT_STAGE_LONGSIZEX / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));
				g_StageSelectObj[STAGESELECT_OBJ_STAGE2].UVSize.x = STAGESELECT_STAGE_UV + ((1.0f - STAGESELECT_STAGE_UV) / STAGEBAR_MOVE_FRAME) * (STAGEBAR_MOVE_FRAME - (g_iFrame - ONESECOND_FRAME));
				break;
			case 3:
				//描画可
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
