//==========================================================================================
//	数字表示ヘッダ[number.h]
//	Author : KAZUNORI MARUHASHI
//
//	Update :
//		YYYY/MM/DD	Updater :
//
//		2017/05/29	Updater : KAZUNORI MARUHASHI
//			・とりあえず完成。とりあえず。
//			　流石にガバガバすぎるので後で修正する
//			・ゲーム終了後に
//				SetAchiveValue(int iValue);
//				SetComboValue(int iValue);
//				SetPhysicalValue(int iValue);
//			  の三つを呼び出してください。
//
//		2017/05/26	Updater : KAZUNORI MARUHASHI
//			・初版作成
//			
//	
//==========================================================================================

//==========================================================================================
// インクルードファイル
//==========================================================================================
#include "main.h"		//メインヘッダ
#include "number.h"		//
#include "input.h"		//
#include "inputX.h"		//
#include "sound.h"		//
#include "result.h"		//
#include "fade.h"

//==========================================================================================
// マクロ定義
//==========================================================================================
#define RESULT_OBJECT_MAX (15)

//テクスチャ関係
#define RESULT_BG_TEXTURENAME			"data/TEXTURE/RESULT/resultBG.png"			//背景画像
#define RESULT_ASC_TEXTURENAME			"data/TEXTURE/RESULT/resultASC.png"			//リザルト文字
#define RESULT_BAR_TEXTURENAME			"data/TEXTURE/RESULT/resultBar.png"			//達成度バー
#define RESULT_BARON_TEXTURENAME		"data/TEXTURE/RESULT/resultBarOn.png"		//達成度メモリ
#define RESULT_ACHIVE_TEXTURENAME		"data/TEXTURE/RESULT/achiveASC.png"			//達成度文字
#define RESULT_COMBO_TEXTURENAME		"data/TEXTURE/RESULT/comboASC.png"			//コンボ文字
#define RESULT_PHISICALASC_TEXTURENAME	"data/TEXTURE/RESULT/resultPhysicalASC.png"	//体力文字
#define RESULT_PRESENT_TEXTURENAME		"data/TEXTURE/RESULT/resultPresent.png"		//%文字
#define RESULT_RANK_TEXTURENAME			"data/TEXTURE/RESULT/rank.png"				//ランク文字
#define RESULT_RANKASC_TEXTURENAME		"data/TEXTURE/RESULT/rankASC.png"			//ランク
#define RESULT_TITLEASC_TEXTURENAME		"data/TEXTURE/RESULT/resultTitleASC.png"	//タイトルへ
#define RESULT_NUMBER_TEXTURENAME		"data/TEXTURE/RESULT/resultNumber.png"		//数字画像

//位置関連(座標は中心を指定)
#define RESULT_BG_POSX	(SCREEN_WIDTH * 0.5f)
#define RESULT_BG_POSY	(SCREEN_HEIGHT * 0.5f)
#define RESULT_BG_SIZEX (SCREEN_WIDTH)
#define RESULT_BG_SIZEY (SCREEN_HEIGHT)

//リザルト
#define RESULT_ASC_POSX	 (SCREEN_WIDTH * 0.15f)
#define RESULT_ASC_POSY	 (SCREEN_HEIGHT * 0.1f)
#define RESULT_ASC_SIZEX (SCREEN_WIDTH * 0.1f)
#define RESULT_ASC_SIZEY (SCREEN_HEIGHT * 0.05f)

//ゲージ
#define RESULT_BAR_POSX  (SCREEN_WIDTH * 0.5f)
#define RESULT_BAR_POSY  (SCREEN_HEIGHT * 0.3f)
#define RESULT_BAR_SIZEX (SCREEN_WIDTH * 0.6f)
#define RESULT_BAR_SIZEY (SCREEN_HEIGHT * 0.05f)


#define RESULT_BARON_START_POSX  (SCREEN_WIDTH * 0.3f)	//ゲージメモリの初期位置
#define RESULT_BARON_END_POSX	 (SCREEN_WIDTH * 0.7f)	//ゲージメモリの終端位置
#define RESULT_BARON_POSY  (RESULT_BAR_POSY)
#define RESULT_BARON_SIZEX (SCREEN_WIDTH * 0.02f)
#define RESULT_BARON_SIZEY (SCREEN_HEIGHT * 0.08f)

#define RESULT_ACHIVE_POSX  (SCREEN_WIDTH * 0.3f)
#define RESULT_ACHIVE_POSY  (SCREEN_HEIGHT * 0.45f)
#define RESULT_ACHIVE_SIZEX (SCREEN_WIDTH * 0.05f)
#define RESULT_ACHIVE_SIZEY (SCREEN_HEIGHT * 0.05f)

#define RESULT_COMBO_POSX  (RESULT_ACHIVE_POSX)
#define RESULT_COMBO_POSY  (SCREEN_HEIGHT * 0.6f)
#define RESULT_COMBO_SIZEX (SCREEN_WIDTH * 0.05f)
#define RESULT_COMBO_SIZEY (SCREEN_HEIGHT * 0.05f)

#define RESULT_PHISICALASC_POSX  (RESULT_ACHIVE_POSX)
#define RESULT_PHISICALASC_POSY  (SCREEN_HEIGHT * 0.75f)
#define RESULT_PHISICALASC_SIZEX (SCREEN_WIDTH * 0.05f)
#define RESULT_PHISICALASC_SIZEY (SCREEN_HEIGHT * 0.05f)

//=== 数字関連 ===//
/*
	例外的に数字関連だけは一桁目の座標、サイズを指定する
	その他桁ごとの幅も指定
*/
#define RESULT_ACHIVE_NUM_POSX  (SCREEN_WIDTH * 0.5f)
#define RESULT_ACHIVE_NUM_POSY  (RESULT_ACHIVE_POSY)
#define RESULT_ACHIVE_NUM_SIZEX (SCREEN_WIDTH * 0.03f)
#define RESULT_ACHIVE_NUM_SIZEY (RESULT_ACHIVE_SIZEY)

#define RESULT_COMBO_NUM_POSX  (RESULT_ACHIVE_NUM_POSX)
#define RESULT_COMBO_NUM_POSY  (RESULT_COMBO_POSY)
#define RESULT_COMBO_NUM_SIZEX (RESULT_ACHIVE_NUM_SIZEX)
#define RESULT_COMBO_NUM_SIZEY (RESULT_COMBO_SIZEY)

#define RESULT_PHISICALASC_NUM_POSX  (RESULT_ACHIVE_NUM_POSX)
#define RESULT_PHISICALASC_NUM_POSY  (RESULT_PHISICALASC_POSY)
#define RESULT_PHISICALASC_NUM_SIZEX (RESULT_ACHIVE_NUM_SIZEX)
#define RESULT_PHISICALASC_NUM_SIZEY (RESULT_PHISICALASC_SIZEY)

#define RESULT_NUM_MARGIN (SCREEN_WIDTH * 0.03)
//=== 数字関連終了 ===//

#define RESULT_ACHIVE_PRESENT_POSX  (SCREEN_WIDTH * 0.6f)
#define RESULT_ACHIVE_PRESENT_POSY  (RESULT_ACHIVE_POSY)
#define RESULT_ACHIVE_PRESENT_SIZEX (RESULT_ACHIVE_NUM_SIZEX)
#define RESULT_ACHIVE_PRESENT_SIZEY (RESULT_ACHIVE_SIZEY)

#define RESULT_PHISICALASC_PRESENT_POSX  (RESULT_ACHIVE_PRESENT_POSX)
#define RESULT_PHISICALASC_PRESENT_POSY  (RESULT_PHISICALASC_POSY)
#define RESULT_PHISICALASC_PRESENT_SIZEX (RESULT_PHISICALASC_NUM_SIZEX)
#define RESULT_PHISICALASC_PRESENT_SIZEY (RESULT_PHISICALASC_SIZEY)

#define RESULT_RANK_POSX  (SCREEN_WIDTH * 0.7f)
#define RESULT_RANK_POSY  (SCREEN_HEIGHT * 0.8f)
#define RESULT_RANK_SIZEX (SCREEN_WIDTH * 0.05f)
#define RESULT_RANK_SIZEY (SCREEN_HEIGHT * 0.05f)

#define RESULT_RANKASC_POSX  (SCREEN_WIDTH * 0.78f)
#define RESULT_RANKASC_POSY  (SCREEN_HEIGHT * 0.75f)
#define RESULT_RANKASC_SIZEX (SCREEN_WIDTH * 0.15f)
#define RESULT_RANKASC_SIZEY (SCREEN_HEIGHT * 0.15f)

#define RESULT_TITLEASC_POSX  (SCREEN_WIDTH * 0.8f)
#define RESULT_TITLEASC_POSY  (SCREEN_HEIGHT * 0.9f)
#define RESULT_TITLEASC_SIZEX (SCREEN_WIDTH * 0.15f)
#define RESULT_TITLEASC_SIZEY (SCREEN_HEIGHT * 0.1f)

//点数評価しきい値
/*
	各要素に点数を付けその合計でランク決め
*/
#define RESULT_ACHIVE_RANKB (30)
#define RESULT_ACHIVE_RANKA (70)
#define RESULT_ACHIVE_RANKS (100)

#define RESULT_COMBO_RANKB (10)
#define RESULT_COMBO_RANKA (30)
#define RESULT_COMBO_RANKS (50)

#define RESULT_PHISICALASC_RANKB (50)
#define RESULT_PHISICALASC_RANKA (70)
#define RESULT_PHISICALASC_RANKS (90)

#define RANK_SOUND (20)	//ランク音を鳴らすフレーム

//==========================================================================================
// 構造体定義
//==========================================================================================


//==========================================================================================
// プロトタイプ宣言
//==========================================================================================
HRESULT MakeVertexResult(LPDIRECT3DDEVICE9 pDevice);
void SetNumberPos(float fPosX, float fPosY);
void CreateTexture(LPDIRECT3DDEVICE9 pDevice);
int SetRank(void);	//ランクの設定

//==========================================================================================
// グローバル変数
//==========================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferResult = NULL;
LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_MAX] = {};	//数字を除いたテクスチャインターフェース

RESULT g_ResultObj[RESULT_OBJECT_MAX];

int g_iPhase;	//処理フェーズ
int g_iFrame;	//フレーム数カウント用
int g_iRank;	//ランク格納用

//次のフェーズへ移行するフレーム数(60 = 1秒)
const float g_fPhaseFrame[7] = 
{
	60, 60, 60, 60, 60, 60. -1
};

//達成度
int g_iAchiveValue;		//実数
float g_fAchiveDrawValue;	//描画数値

//コンボ数
int g_iComboValue;		//実数
float g_fComboDrawValue;	//描画数値

//残体力数
int g_iPhysicalValue;		//実数
float g_fPhysicalDrawValue;	//描画数値

//==========================================================================================
// 初期化処理
//==========================================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得

	//頂点の設定
	if(FAILED(MakeVertexResult(pDevice)))
	{
		MessageBox(NULL, "頂点バッファの設定に失敗しました。", " ", MB_OK);
		return;
	}

	//テクスチャ生成用関数
	CreateTexture(pDevice);

	//フェーズを初期に戻す
	g_iPhase = 0;
	g_iFrame = 0;

	g_ResultObj[0].Pos = D3DXVECTOR3(RESULT_BG_POSX, RESULT_BG_POSY, 0.0f);
	g_ResultObj[0].Size = D3DXVECTOR3(RESULT_BG_SIZEX, RESULT_BG_SIZEY, 0.0f);
	g_ResultObj[0].label = RESULT_BG;

	g_ResultObj[1].Pos = D3DXVECTOR3(RESULT_ASC_POSX, RESULT_ASC_POSY, 0.0f);
	g_ResultObj[1].Size = D3DXVECTOR3(RESULT_ASC_SIZEX, RESULT_ASC_SIZEY, 0.0f);
	g_ResultObj[1].label = RESULT_ASC;

	g_ResultObj[2].Pos = D3DXVECTOR3(RESULT_BAR_POSX, RESULT_BAR_POSY, 0.0f);
	g_ResultObj[2].Size = D3DXVECTOR3(RESULT_BAR_SIZEX, RESULT_BAR_SIZEY, 0.0f);
	g_ResultObj[2].label = RESULT_BAR;

	g_ResultObj[3].Pos = D3DXVECTOR3(RESULT_BARON_START_POSX, RESULT_BARON_POSY, 0.0f);
	g_ResultObj[3].Size = D3DXVECTOR3(RESULT_BARON_SIZEX, RESULT_BARON_SIZEY, 0.0f);
	g_ResultObj[3].label = RESULT_BARON;

	g_ResultObj[4].Pos = D3DXVECTOR3(RESULT_ACHIVE_POSX, RESULT_ACHIVE_POSY, 0.0f);
	g_ResultObj[4].Size = D3DXVECTOR3(RESULT_ACHIVE_SIZEX, RESULT_ACHIVE_SIZEY, 0.0f);
	g_ResultObj[4].label = RESULT_ACHIVE;

	g_ResultObj[5].Pos = D3DXVECTOR3(RESULT_COMBO_POSX, RESULT_COMBO_POSY, 0.0f);
	g_ResultObj[5].Size = D3DXVECTOR3(RESULT_COMBO_SIZEX, RESULT_COMBO_SIZEY, 0.0f);
	g_ResultObj[5].label = RESULT_COMBO;

	g_ResultObj[6].Pos = D3DXVECTOR3(RESULT_PHISICALASC_POSX, RESULT_PHISICALASC_POSY, 0.0f);
	g_ResultObj[6].Size = D3DXVECTOR3(RESULT_PHISICALASC_SIZEX, RESULT_PHISICALASC_SIZEY, 0.0f);
	g_ResultObj[6].label = RESULT_PHISICALASC;

	g_ResultObj[7].Pos = D3DXVECTOR3(RESULT_ACHIVE_NUM_POSX, RESULT_ACHIVE_NUM_POSY, 0.0f);
	g_ResultObj[7].Size = D3DXVECTOR3(RESULT_ACHIVE_NUM_SIZEX, RESULT_ACHIVE_NUM_SIZEY, 0.0f);
	g_ResultObj[7].label = RESULT_NUMBER;

	g_ResultObj[8].Pos = D3DXVECTOR3(RESULT_COMBO_NUM_POSX, RESULT_COMBO_NUM_POSY, 0.0f);
	g_ResultObj[8].Size = D3DXVECTOR3(RESULT_COMBO_NUM_SIZEX, RESULT_COMBO_NUM_SIZEY, 0.0f);
	g_ResultObj[8].label = RESULT_NUMBER;

	g_ResultObj[9].Pos = D3DXVECTOR3(RESULT_PHISICALASC_NUM_POSX, RESULT_PHISICALASC_NUM_POSY, 0.0f);
	g_ResultObj[9].Size = D3DXVECTOR3(RESULT_PHISICALASC_NUM_SIZEX, RESULT_PHISICALASC_NUM_SIZEY, 0.0f);
	g_ResultObj[9].label = RESULT_NUMBER;

	g_ResultObj[10].Pos = D3DXVECTOR3(RESULT_ACHIVE_PRESENT_POSX, RESULT_ACHIVE_PRESENT_POSY, 0.0f);
	g_ResultObj[10].Size = D3DXVECTOR3(RESULT_ACHIVE_PRESENT_SIZEX, RESULT_ACHIVE_PRESENT_SIZEY, 0.0f);
	g_ResultObj[10].label = RESULT_PRESENT;

	g_ResultObj[11].Pos = D3DXVECTOR3(RESULT_PHISICALASC_PRESENT_POSX, RESULT_PHISICALASC_PRESENT_POSY, 0.0f);
	g_ResultObj[11].Size = D3DXVECTOR3(RESULT_PHISICALASC_PRESENT_SIZEX, RESULT_PHISICALASC_PRESENT_SIZEY, 0.0f);
	g_ResultObj[11].label = RESULT_PRESENT;

	g_ResultObj[12].Pos = D3DXVECTOR3(RESULT_RANK_POSX, RESULT_RANK_POSY, 0.0f);
	g_ResultObj[12].Size = D3DXVECTOR3(RESULT_RANK_SIZEX, RESULT_RANK_SIZEY, 0.0f);
	g_ResultObj[12].label = RESULT_RANK;

	g_ResultObj[13].Pos = D3DXVECTOR3(RESULT_RANKASC_POSX, RESULT_RANKASC_POSY, 0.0f);
	g_ResultObj[13].Size = D3DXVECTOR3(RESULT_RANKASC_SIZEX, RESULT_RANKASC_SIZEY, 0.0f);
	g_ResultObj[13].label = RESULT_RANKASC;

	g_ResultObj[14].Pos = D3DXVECTOR3(RESULT_TITLEASC_POSX, RESULT_TITLEASC_POSY, 0.0f);
	g_ResultObj[14].Size = D3DXVECTOR3(RESULT_TITLEASC_SIZEX, RESULT_TITLEASC_SIZEY, 0.0f);
	g_ResultObj[14].label = RESULT_TITLEASC;

	//固有値以外一括設定
	for(int i = 0; i < RESULT_OBJECT_MAX; i++){
		g_ResultObj[i].fAlpha = 0.0f;
		g_ResultObj[i].bDraw = false;
		g_ResultObj[i].UV = D3DXVECTOR2(0.0f, 0.0f);
		g_ResultObj[i].UVSize = D3DXVECTOR2(1.0f, 1.0f);
	}

	//背景だけは描画する
	g_ResultObj[0].bDraw = true;

	//数字描画処理の初期化
	InitNumber();

	PlaySound(BGM_RESULT);
}

//==========================================================================================
// 終了処理
//==========================================================================================
void UninitResult(void)
{
	UninitNumber();

	if(g_pVtxBufferResult != NULL)
	{
		g_pVtxBufferResult -> Release();
		g_pVtxBufferResult = NULL;
	}
	for(int iSelf = 0; iSelf < RESULT_MAX; iSelf++){
		if(g_pTextureResult[iSelf] != NULL){
			g_pTextureResult[iSelf] -> Release();
			g_pTextureResult[iSelf] = NULL;
		}
	}
	for (int iSelf = 0; iSelf < RESULT_OBJECT_MAX; iSelf++) {
		g_ResultObj[iSelf].bDraw = false;
	}
}

//==========================================================================================
// 更新処理
//==========================================================================================
void UpdateResult(void)
{
	float fSelfESC = RESULT_BARON_END_POSX - RESULT_BARON_START_POSX;
	float fSelf;
	static bool bFlash;

	//フレーム数カウント
	g_iFrame++;

	//フェーズ毎の処理
	switch(g_iPhase){
	case 0:	//背景を浮かびあがらせる
		//徐々に不透明にする
		g_ResultObj[0].fAlpha += 0.5f / g_fPhaseFrame[g_iPhase];

		//既定のフレーム数を超えたとき
		if(g_iFrame > g_fPhaseFrame[g_iPhase]){
			g_ResultObj[0].fAlpha = 0.5f;
			g_iPhase++;		//次のフェーズへ移行
			g_iFrame = 0;
			//次のオブジェクトの描画許可
			for(int i = 1; i <= 11; i++){
				g_ResultObj[i].bDraw = true;
			}
		}
		break;

	case 1:		//ゲージとか色々描画
		//徐々に不透明にする
		for(int i = 1; i <= 11; i++){
				g_ResultObj[i].fAlpha += 1.0f / g_fPhaseFrame[g_iPhase];
		}

		if(g_iFrame > g_fPhaseFrame[g_iPhase]){
			//全て不透明に設定
			for(int i = 1; i <= 11; i++){
				g_ResultObj[i].fAlpha = 1.0f;
			}
			g_iPhase++;
			g_iFrame = 0;
		}
		break;

	case 2:		//達成度関連描画
		//SE再生
		PlaySound(SE_RESULT_NUMBER);

		g_fAchiveDrawValue = g_iAchiveValue / (g_fPhaseFrame[g_iPhase] / g_iFrame);
		
		fSelf = fSelfESC * (g_iAchiveValue * 0.01);
		
		g_ResultObj[3].Pos.x += (fSelf / g_fPhaseFrame[g_iPhase]);

		if(g_iFrame > g_fPhaseFrame[g_iPhase] || GetKeyboardTrigger(DIK_RETURN)){
			
			//数値カウント停止音再生
			PlaySound(SE_RESULT_NUMBER_ON);
			//数値カウント音停止
			StopSound(SE_RESULT_NUMBER);

			//全て不透明に設定
			g_fAchiveDrawValue = g_iAchiveValue;
			g_ResultObj[3].Pos.x = RESULT_BARON_START_POSX + (fSelfESC * (g_fAchiveDrawValue * 0.01));
			g_iPhase++;
			g_iFrame = 0;
		}
		break;

	case 3:		//コンボ関連描画
		//SE再生
		PlaySound(SE_RESULT_NUMBER);

		g_fComboDrawValue = g_iComboValue / (g_fPhaseFrame[g_iPhase] / g_iFrame);

		if(g_iFrame > g_fPhaseFrame[g_iPhase] || GetKeyboardTrigger(DIK_RETURN)){
			//数値カウント停止音再生
			PlaySound(SE_RESULT_NUMBER_ON);
			//数値カウント音停止
			StopSound(SE_RESULT_NUMBER);
			//全て不透明に設定
			g_fComboDrawValue = g_iComboValue;
			g_iPhase++;
			g_iFrame = 0;
		}
		break;

	case 4:		//体力関連描画
		//SE再生
		PlaySound(SE_RESULT_NUMBER);

		g_fPhysicalDrawValue = g_iPhysicalValue / (g_fPhaseFrame[g_iPhase] / g_iFrame);

		if(g_iFrame > g_fPhaseFrame[g_iPhase] || GetKeyboardTrigger(DIK_RETURN)){
			//数値カウント停止音再生
			PlaySound(SE_RESULT_NUMBER_ON);
			//数値カウント音停止
			StopSound(SE_RESULT_NUMBER);
			//全て不透明に設定
			g_fPhysicalDrawValue = g_iPhysicalValue;
			g_iPhase++;
			g_iFrame = 0;

			//ランクの設定
			g_iRank = SetRank();
			g_ResultObj[13].UVSize.x = 0.25f;
			g_ResultObj[13].UV.x = 0.25f*g_iRank;
			g_ResultObj[12].bDraw = true;
			g_ResultObj[13].bDraw = true;
		}
		break;

	case 5:		//ランク関連描画
		g_ResultObj[12].fAlpha += 1.0f / g_fPhaseFrame[g_iPhase];
		g_ResultObj[13].fAlpha += 1.0f / g_fPhaseFrame[g_iPhase];

		if(g_iFrame == RANK_SOUND){
			switch(g_iRank)
			{
			case 0:
				PlaySound(SE_RESULT_RANK_C);
				break;
			case 1:
				PlaySound(SE_RESULT_RANK_B);
				break;
			case 2:
				PlaySound(SE_RESULT_RANK_A);
				break;
			case 3:
				PlaySound(SE_RESULT_RANK_S);
				break;
			}
		}

		if(g_iFrame > g_fPhaseFrame[g_iPhase]){
			g_ResultObj[12].fAlpha = 1.0f;
			g_ResultObj[13].fAlpha = 1.0f;

			//全て不透明に設定
			g_iPhase++;
			g_iFrame = 0;
			g_ResultObj[14].bDraw = true;
		}
		break;

	case 6:		//タイトルへ戻る
		if(bFlash == true){
			g_ResultObj[14].fAlpha += 1.0f / 60;
		}
		else{
			g_ResultObj[14].fAlpha -= 1.0f / 60;
		}

		if(g_ResultObj[14].fAlpha >= 1.0f){
			bFlash = false;
		}
		else if(g_ResultObj[14].fAlpha <= 0.0f){
			bFlash = true;
		}

		if(GetKeyboardTrigger(DIK_RETURN) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A)){
			PlaySound(SE_PUSH);
			StopSound(BGM_RESULT);
			startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), TITLE_MODE);
		}
	break;
	}

	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ
	//仮想アドレスを取得する
	g_pVtxBufferResult -> Lock(0, 0, (void**)&pVtx, 0);

	for(int VtxLoop = 0; VtxLoop < RESULT_OBJECT_MAX; VtxLoop++){

		//頂点座標の設定（x, y, z）
		pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_ResultObj[VtxLoop].Pos.x - g_ResultObj[VtxLoop].Size.x * 0.5f,
											g_ResultObj[VtxLoop].Pos.y - g_ResultObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_ResultObj[VtxLoop].Pos.x + g_ResultObj[VtxLoop].Size.x * 0.5f,
											g_ResultObj[VtxLoop].Pos.y - g_ResultObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_ResultObj[VtxLoop].Pos.x - g_ResultObj[VtxLoop].Size.x * 0.5f,
											g_ResultObj[VtxLoop].Pos.y + g_ResultObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_ResultObj[VtxLoop].Pos.x + g_ResultObj[VtxLoop].Size.x * 0.5f,
											g_ResultObj[VtxLoop].Pos.y + g_ResultObj[VtxLoop].Size.y * 0.5f, 0.0f);

		//カラーの設定
		pVtx[0+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_ResultObj[VtxLoop].fAlpha);
		pVtx[1+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_ResultObj[VtxLoop].fAlpha);
		pVtx[2+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_ResultObj[VtxLoop].fAlpha);
		pVtx[3+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_ResultObj[VtxLoop].fAlpha);

		//テクスチャ―座標の設定
		pVtx[0+4*VtxLoop].tex = D3DXVECTOR2(g_ResultObj[VtxLoop].UV.x,
											g_ResultObj[VtxLoop].UV.y);
		pVtx[1+4*VtxLoop].tex = D3DXVECTOR2(g_ResultObj[VtxLoop].UV.x + g_ResultObj[VtxLoop].UVSize.x, 
											g_ResultObj[VtxLoop].UV.y);
		pVtx[2+4*VtxLoop].tex = D3DXVECTOR2(g_ResultObj[VtxLoop].UV.x, 
											g_ResultObj[VtxLoop].UV.y + g_ResultObj[VtxLoop].UVSize.y);
		pVtx[3+4*VtxLoop].tex = D3DXVECTOR2(g_ResultObj[VtxLoop].UV.x + g_ResultObj[VtxLoop].UVSize.x, 
											g_ResultObj[VtxLoop].UV.y + g_ResultObj[VtxLoop].UVSize.y);
	}

	g_pVtxBufferResult -> Unlock();
}

//==========================================================================================
// 描画処理
//==========================================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得
	
	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferResult,
							  0,					//オフセット
							  sizeof(VERTEX2D));		//ストライド量
	

	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	for(int iDraw = 0; iDraw < RESULT_OBJECT_MAX; iDraw++){
		if(g_ResultObj[iDraw].bDraw == true){
			
			pDevice -> SetTexture(0, g_pTextureResult[g_ResultObj[iDraw].label]);

			//プリミティブの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
										iDraw * 4,					//オフセット(頂点数)
										NUM_POLYGON);			//プリミティブ数
		}
	}

	//数字の描画
	for(int iDraw = 7; iDraw <= 9; iDraw++){
		if(g_ResultObj[iDraw].bDraw == true){
			if(iDraw == 7){
					
				DrawNumber(g_fAchiveDrawValue, 3, 
							D3DXVECTOR2(g_ResultObj[iDraw].Pos.x, g_ResultObj[iDraw].Pos.y),
							D3DXVECTOR2(g_ResultObj[iDraw].Size.x, g_ResultObj[iDraw].Size.y), 
							RESULT_NUM_MARGIN, g_pTextureResult[RESULT_NUMBER]);
			}
			if(iDraw == 8){
				DrawNumber(g_fComboDrawValue, 3, 
							D3DXVECTOR2(g_ResultObj[iDraw].Pos.x, g_ResultObj[iDraw].Pos.y),
							D3DXVECTOR2(g_ResultObj[iDraw].Size.x, g_ResultObj[iDraw].Size.y), 
							RESULT_NUM_MARGIN, g_pTextureResult[RESULT_NUMBER]);
			}
			if(iDraw == 9){
				DrawNumber(g_fPhysicalDrawValue, 3, 
							D3DXVECTOR2(g_ResultObj[iDraw].Pos.x, g_ResultObj[iDraw].Pos.y),
							D3DXVECTOR2(g_ResultObj[iDraw].Size.x, g_ResultObj[iDraw].Size.y), 
							RESULT_NUM_MARGIN, g_pTextureResult[RESULT_NUMBER]);
			}
		}
	}
}

//==========================================================================================
// 頂点の生成
//==========================================================================================
HRESULT MakeVertexResult(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ

	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX2D)*NUM_VERTEX*RESULT_OBJECT_MAX,	//確保したい頂点バッファの数＊頂点数
								  D3DUSAGE_WRITEONLY,	//確保した後中を見ることはできない
								  FVF_VERTEX_2D,		//一応書かずとも平気
								  D3DPOOL_MANAGED,		//メモリ管理をどうするか(これはお任せ)
								  &g_pVtxBufferResult,
								  NULL)))
	{
		return E_FAIL;
	}

	//仮想アドレスを取得する
	g_pVtxBufferResult -> Lock(0, 0, (void**)&pVtx, 0);

	for(int VtxLoop = 0; VtxLoop < RESULT_OBJECT_MAX; VtxLoop++){

		//頂点座標の設定（x, y, z）
		pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_ResultObj[VtxLoop].Pos.x - g_ResultObj[VtxLoop].Size.x,
											g_ResultObj[VtxLoop].Pos.y - g_ResultObj[VtxLoop].Size.y, 0.0f);

		pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_ResultObj[VtxLoop].Pos.x + g_ResultObj[VtxLoop].Size.x,
											g_ResultObj[VtxLoop].Pos.y - g_ResultObj[VtxLoop].Size.y, 0.0f);

		pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_ResultObj[VtxLoop].Pos.x - g_ResultObj[VtxLoop].Size.x,
											g_ResultObj[VtxLoop].Pos.y + g_ResultObj[VtxLoop].Size.y, 0.0f);

		pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_ResultObj[VtxLoop].Pos.x + g_ResultObj[VtxLoop].Size.x,
											g_ResultObj[VtxLoop].Pos.y + g_ResultObj[VtxLoop].Size.y, 0.0f);

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

	g_pVtxBufferResult -> Unlock();

	return S_OK;
}

//==========================================================================================
// テクスチャ生成
//==========================================================================================
void CreateTexture(LPDIRECT3DDEVICE9 pDevice)
{
	UINT nID;  //メッセージボックスの返り値を入れる

	//テクスチャ取得
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_BG_TEXTURENAME,
		&g_pTextureResult[RESULT_BG] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_BG_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_ASC_TEXTURENAME,
		&g_pTextureResult[RESULT_ASC] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_ASC_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_BAR_TEXTURENAME,
		&g_pTextureResult[RESULT_BAR] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_BAR_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_BARON_TEXTURENAME,
		&g_pTextureResult[RESULT_BARON] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_BARON_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_ACHIVE_TEXTURENAME,
		&g_pTextureResult[RESULT_ACHIVE] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_ACHIVE_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_COMBO_TEXTURENAME,
		&g_pTextureResult[RESULT_COMBO] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_COMBO_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_PHISICALASC_TEXTURENAME,
		&g_pTextureResult[RESULT_PHISICALASC] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_PHISICALASC_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_PRESENT_TEXTURENAME,
		&g_pTextureResult[RESULT_PRESENT] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_PRESENT_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_RANK_TEXTURENAME,
		&g_pTextureResult[RESULT_RANK] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_RANK_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_RANKASC_TEXTURENAME,
		&g_pTextureResult[RESULT_RANKASC] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_RANKASC_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_TITLEASC_TEXTURENAME,
		&g_pTextureResult[RESULT_TITLEASC] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_TITLEASC_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(D3DXCreateTextureFromFile(
		pDevice , 
		RESULT_NUMBER_TEXTURENAME,
		&g_pTextureResult[RESULT_NUMBER] )))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","RESULT_NUMBER_TEXTURENAME",MB_OK | MB_DEFBUTTON1);
		}//EOif
	
}
//==========================================================================================
// 達成度設定
//==========================================================================================
void SetAchiveValue(int iValue)
{
	g_iAchiveValue = iValue;
}

//==========================================================================================
// コンボ数設定
//==========================================================================================
void SetComboValue(int iValue)
{
	g_iComboValue = iValue;
}

//==========================================================================================
// 残体力設定
//==========================================================================================
void SetPhysicalValue(int iValue)
{
	g_iPhysicalValue = iValue;
}

//==========================================================================================
// ランクの設定
//==========================================================================================
int SetRank(void)
{
	int iRank = 0;

	//達成度ランク計算
	if(RESULT_ACHIVE_RANKS == g_iAchiveValue){
		iRank += 3;
	}
	else if(RESULT_ACHIVE_RANKA <= g_iAchiveValue){
		iRank += 2;
	}
	else if(RESULT_ACHIVE_RANKB <= g_iAchiveValue){
		iRank += 1;
	}
	else{
		iRank += 0;
	}
	
	//コンボランク計算
	if(RESULT_COMBO_RANKS <= g_iComboValue){
		iRank += 3;
	}
	else if(RESULT_COMBO_RANKA <= g_iComboValue){
		iRank += 2;
	}
	else if(RESULT_COMBO_RANKB <= g_iComboValue){
		iRank += 1;
	}
	else{
		iRank += 0;
	}
	
	//ライフランク計算
	if(RESULT_PHISICALASC_RANKS <= g_iPhysicalValue){
		iRank += 3;
	}
	else if(RESULT_PHISICALASC_RANKA <= g_iPhysicalValue){
		iRank += 2;
	}
	else if(RESULT_PHISICALASC_RANKB <= g_iPhysicalValue){
		iRank += 1;
	}
	else{
		iRank += 0;
	}

	//ライフランク計算
	if(8 <= g_iPhysicalValue){
		iRank = 3;
	}
	else if(6 <= g_iPhysicalValue){
		iRank = 2;
	}
	else if(3 <= g_iPhysicalValue){
		iRank = 1;
	}
	else{
		iRank = 0;
	}

	return iRank;
}