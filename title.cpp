//==========================================================================================
//	タイトル処理[title.cpp]
//	Author : KAZUNORI MARUHASHI
//
//	Update :
//		YYYY/MM/DD	Updater :
//
//		2017/06/12	Updater : KAZUNORI MARUHASHI
//			・初版作成
//			・決定キー押下後の処理は JUMP 検索
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
#include "title.h"		//ステージセレクト処理
#include "fade.h"		//フェード処理

//==========================================================================================
// マクロ定義
//==========================================================================================
//テクスチャ関係
#define TITLE_TITLE_TEXTURENAME		"data/TEXTURE/TITLE/title.png"		//ステージセレクト文字
#define TITLE_START_TEXTURENAME		"data/TEXTURE/TITLE/titleASC.png"	//チュートリアル文字
#define TITLE_STAGE1_TEXTURENAME	"data/TEXTURE/GAME/BG/stageBG01.jpg"	//村画像
#define TITLE_STAGE2_TEXTURENAME	"data/TEXTURE/GAME/BG/stageBG02.jpg"	//雪山画像
#define TITLE_STAGE3_TEXTURENAME	"data/TEXTURE/GAME/BG/stageBG03.jpg"	//火山画像


//=========位置関連(座標は中心を指定)==========//
//背景
#define TITLE_BG_POSX		(SCREEN_WIDTH  * 0.5f)
#define TITLE_BG_POSY		(SCREEN_HEIGHT * 0.5f)
#define TITLE_BG_SIZEX		(SCREEN_WIDTH)
#define TITLE_BG_SIZEY		(SCREEN_HEIGHT)

//タイトル文字
#define TITLE_TITLE_POSX	(SCREEN_WIDTH  * 0.50f)
#define TITLE_TITLE_POSY	(SCREEN_HEIGHT * 0.25f)
#define TITLE_TITLE_SIZEX	(SCREEN_WIDTH  * 0.50f)
#define TITLE_TITLE_SIZEY	(SCREEN_HEIGHT * 0.20f)

//ゲームスタート
#define TITLE_START_POSX	(SCREEN_WIDTH  * 0.50f)
#define TITLE_START_POSY	(SCREEN_HEIGHT * 0.65f)
#define TITLE_START_SIZEX	(SCREEN_WIDTH  * 0.30f)
#define TITLE_START_SIZEY	(SCREEN_HEIGHT * 0.20f)

//背景テクスチャの初期U値
#define TITLE_TEXTURE_SIZEU (0.7f)	

//背景テクスチャ移動量
#define TITLE_TEXTURE_MOVEU (0.001f)

//背景フェード速度
#define TITLE_BGFADE_FRAME (120)

#define ONESECOND_FRAME (60)	//１秒のフレーム数

#define START_FADE_FRAME (ONESECOND_FRAME * 2)		//通常時のスタート文字点滅速度
#define START_FADE_DICISION_FRAME (ONESECOND_FRAME)	//決定キー押下時のスタート文字点滅速度

#define DICISION_KEY (DIK_Z)	//決定キー
#define CANCEL_KEY (DIK_X)		//キャンセルキー

//==========================================================================================
// 構造体定義
//==========================================================================================
//テクスチャ情報登録用構造体
struct CREATETEX
{
	char cStr[256];
	TITLE_TEX_LABEL label;
};

//==========================================================================================
// プロトタイプ宣言
//==========================================================================================
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

//==========================================================================================
// グローバル変数
//==========================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTitle = NULL;
TITLE g_TitleObj[TITLE_OBJ_MAX];
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_TEX_MAX] = {};	//テクスチャインターフェース

bool bDicision;	//決定キーを押されたか
bool bBGAlpha;	//背景BG
bool bStartAlpha;	//スタート文字点滅可否
	
//各オブジェクトの初期設定(位置、サイズ、UV値、UVサイズ、テクスチャID, α値, 描画有無)
const TITLE coTitleObj[TITLE_OBJ_MAX] =
{
	//背景
	{D3DXVECTOR3(TITLE_BG_POSX, TITLE_BG_POSY, 0.0f),
	 D3DXVECTOR3(TITLE_BG_SIZEX, TITLE_BG_SIZEY, 0.0f), 
	 D3DXVECTOR2(0.0f, 0.0f),
	 D3DXVECTOR2(TITLE_TEXTURE_SIZEU, 1.0f),
	 TITLE_TEX_STAGE1, 
	 1.0f, 
	 true
	}, 

	//背景フェード用
	{D3DXVECTOR3(TITLE_BG_POSX, TITLE_BG_POSY, 0.0f),
	 D3DXVECTOR3(TITLE_BG_SIZEX, TITLE_BG_SIZEY, 0.0f), 
	 D3DXVECTOR2(0.0f, 0.0f),
	 D3DXVECTOR2(1.0f, 1.0f),
	 TITLE_TEX_NONE, 
	 0.0f, 
	 true
	},

	//タイトル文字
	{D3DXVECTOR3(TITLE_TITLE_POSX, TITLE_TITLE_POSY, 0.0f),
	 D3DXVECTOR3(TITLE_TITLE_SIZEX, TITLE_TITLE_SIZEY, 0.0f), 
	 D3DXVECTOR2(0.0f, 0.0f),
	 D3DXVECTOR2(1.0f, 1.0f),
	 TITLE_TEX_TITLE, 
	 1.0f, 
	 true
	}, 

	//ゲームスタート文字
	{D3DXVECTOR3(TITLE_START_POSX, TITLE_START_POSY, 0.0f),
	 D3DXVECTOR3(TITLE_START_SIZEX, TITLE_START_SIZEY, 0.0f), 
	 D3DXVECTOR2(0.0f, 0.0f),
	 D3DXVECTOR2(1.0f, 1.0f),
	 TITLE_TEX_GAMESTART, 
	 1.0f, 
	 true
	}, 


};

//テクスチャの登録情報(ファイルアドレス, ラベル)
const CREATETEX coTitleTex[TITLE_TEX_MAX] =
{
	{"", TITLE_TEX_NONE},
	{TITLE_STAGE1_TEXTURENAME, TITLE_TEX_STAGE1}, 
	{TITLE_STAGE2_TEXTURENAME, TITLE_TEX_STAGE2}, 
	{TITLE_STAGE3_TEXTURENAME, TITLE_TEX_STAGE3}, 
	{TITLE_TITLE_TEXTURENAME, TITLE_TEX_TITLE}, 
	{TITLE_START_TEXTURENAME, TITLE_TEX_GAMESTART}, 
};

//==========================================================================================
// 初期化処理
//==========================================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得

	//頂点の設定
	if(FAILED(MakeVertexTitle(pDevice)))
	{
		MessageBox(NULL, "頂点バッファの設定に失敗しました。", " ", MB_OK);
		return;
	}

	//フェードイン
	startFadeIn(60, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//テクスチャ生成
	for(int i = 0; i < TITLE_TEX_MAX; i++){
		if(coTitleTex[i].label != TITLE_TEX_NONE){
			char cErrmsg[256] = "";
			strcat(cErrmsg, coTitleTex[i].cStr);
			strcat(cErrmsg, "の生成に失敗しました。");

			if(FAILED(D3DXCreateTextureFromFile(
					  pDevice , 
					  coTitleTex[i].cStr,
					  &g_pTextureTitle[coTitleTex[i].label] )))
					  {
							//エラーメッセージ
							MessageBox(NULL , cErrmsg, "エラー",MB_OK | MB_DEFBUTTON1);
					  }//EOif
		}
	}

	//オブジェクト初期内容設定
	for(int i = 0; i < TITLE_OBJ_MAX; i++){
		g_TitleObj[i] = coTitleObj[i];
	}

	//点滅関連初期化
	bDicision = false;
	bBGAlpha = false;
	bStartAlpha = false;

	//BGM再生
	PlaySound(BGM_TITLE);
}

//==========================================================================================
// 終了処理
//==========================================================================================
void UninitTitle(void)
{
	if(g_pVtxBufferTitle != NULL)
	{
		g_pVtxBufferTitle -> Release();
		g_pVtxBufferTitle = NULL;
	}
	for(int iSelf = 0; iSelf < TITLE_TEX_MAX; iSelf++){
		if(g_pTextureTitle[iSelf] != NULL){
			g_pTextureTitle[iSelf] -> Release();
			g_pTextureTitle[iSelf] = NULL;
		}
	}
	StopSound(BGM_TITLE);
}

//==========================================================================================
// 更新処理
//==========================================================================================
void UpdateTitle(void)
{
	//スタート文字点滅
	if(false == bDicision){
		if(false == bStartAlpha){
			g_TitleObj[TITLE_OBJ_START].fAlpha += 1.0f / START_FADE_FRAME;
			if(g_TitleObj[TITLE_OBJ_START].fAlpha >= 1.0f){
				g_TitleObj[TITLE_OBJ_START].fAlpha = 1.0f;
				bStartAlpha = true;
			}
		}
		else{
			g_TitleObj[TITLE_OBJ_START].fAlpha -= 1.0f / START_FADE_FRAME;
			if(g_TitleObj[TITLE_OBJ_START].fAlpha <= 0.0f){
				g_TitleObj[TITLE_OBJ_START].fAlpha = 0.0f;
				bStartAlpha = false;
			}
		}
	}
	else{
		if(false == bStartAlpha){
			g_TitleObj[TITLE_OBJ_START].fAlpha += 1.0f / START_FADE_DICISION_FRAME;
			if(g_TitleObj[TITLE_OBJ_START].fAlpha >= 1.0f){
				g_TitleObj[TITLE_OBJ_START].fAlpha = 1.0f;
				bStartAlpha = true;
			}
		}
		else{
			g_TitleObj[TITLE_OBJ_START].fAlpha -= 1.0f / START_FADE_DICISION_FRAME;
			if(g_TitleObj[TITLE_OBJ_START].fAlpha <= 0.0f){
				g_TitleObj[TITLE_OBJ_START].fAlpha = 0.0f;
				bStartAlpha = false;
			}
		}
	}
	

	//背景移動
	static TITLE_TEX_LABEL label;
	if(g_TitleObj[TITLE_OBJ_BG].UV.x + TITLE_TEXTURE_SIZEU < 1.0f){
		g_TitleObj[TITLE_OBJ_BG].UV.x += TITLE_TEXTURE_MOVEU;
		g_TitleObj[TITLE_OBJ_BGFADE].fAlpha -= 1.0f / TITLE_BGFADE_FRAME;
		label = g_TitleObj[TITLE_OBJ_BG].label;

		if(g_TitleObj[TITLE_OBJ_BGFADE].fAlpha <= 0.0f){
			g_TitleObj[TITLE_OBJ_BGFADE].fAlpha = 0.0f;
		}
	}

	if(g_TitleObj[TITLE_OBJ_BG].UV.x + TITLE_TEXTURE_SIZEU >= 1.0f){
		//背景フェード
		if(g_TitleObj[TITLE_OBJ_BGFADE].fAlpha < 1.0f){
			g_TitleObj[TITLE_OBJ_BG].UV.x = 1.0f - TITLE_TEXTURE_SIZEU;
			g_TitleObj[TITLE_OBJ_BGFADE].fAlpha += 1.0f / TITLE_BGFADE_FRAME;
		}
		else if(g_TitleObj[TITLE_OBJ_BGFADE].fAlpha >- 1.0f && g_TitleObj[TITLE_OBJ_BG].label == label) {
			g_TitleObj[TITLE_OBJ_BGFADE].fAlpha = 1.0f;
			//描画するテクスチャの変更
			if(g_TitleObj[TITLE_OBJ_BG].label == TITLE_TEX_STAGE1){
				g_TitleObj[TITLE_OBJ_BG].label = TITLE_TEX_STAGE2;
				g_TitleObj[TITLE_OBJ_BG].UV.x = 0.0f;
			}
			else if(g_TitleObj[TITLE_OBJ_BG].label == TITLE_TEX_STAGE2){
				g_TitleObj[TITLE_OBJ_BG].label = TITLE_TEX_STAGE3;
				g_TitleObj[TITLE_OBJ_BG].UV.x = 0.0f;
			}
			else{
				g_TitleObj[TITLE_OBJ_BG].label = TITLE_TEX_STAGE1;
				g_TitleObj[TITLE_OBJ_BG].UV.x = 0.0f;
			}
		}
	}

	//決定キーを押した時
	if(GetKeyboardTrigger(DICISION_KEY) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A)){
		bDicision = true;
		g_TitleObj[TITLE_OBJ_START].fAlpha = 1.0f;
		bStartAlpha = true;
		PlaySound(SE_PUSH);

		// JUMP //
		startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), STAGE_SELECT);
	}


	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ
	//仮想アドレスを取得する
	g_pVtxBufferTitle -> Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	for(int VtxLoop = 0; VtxLoop < TITLE_OBJ_MAX; VtxLoop++){
		//頂点座標の設定（x, y, z）
		pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x - g_TitleObj[VtxLoop].Size.x * 0.5f,
											g_TitleObj[VtxLoop].Pos.y - g_TitleObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x + g_TitleObj[VtxLoop].Size.x * 0.5f,
											g_TitleObj[VtxLoop].Pos.y - g_TitleObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x - g_TitleObj[VtxLoop].Size.x * 0.5f,
											g_TitleObj[VtxLoop].Pos.y + g_TitleObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x + g_TitleObj[VtxLoop].Size.x * 0.5f,
											g_TitleObj[VtxLoop].Pos.y + g_TitleObj[VtxLoop].Size.y * 0.5f, 0.0f);		

		//カラーの設定
		pVtx[0+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleObj[VtxLoop].fAlpha);
		pVtx[1+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleObj[VtxLoop].fAlpha);
		pVtx[2+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleObj[VtxLoop].fAlpha);
		pVtx[3+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleObj[VtxLoop].fAlpha);

		//テクスチャ―座標の設定
		pVtx[0+4*VtxLoop].tex = D3DXVECTOR2(g_TitleObj[VtxLoop].UV.x,
											g_TitleObj[VtxLoop].UV.y);
		pVtx[1+4*VtxLoop].tex = D3DXVECTOR2(g_TitleObj[VtxLoop].UV.x + g_TitleObj[VtxLoop].UVSize.x, 
											g_TitleObj[VtxLoop].UV.y);
		pVtx[2+4*VtxLoop].tex = D3DXVECTOR2(g_TitleObj[VtxLoop].UV.x, 
											g_TitleObj[VtxLoop].UV.y + g_TitleObj[VtxLoop].UVSize.y);
		pVtx[3+4*VtxLoop].tex = D3DXVECTOR2(g_TitleObj[VtxLoop].UV.x + g_TitleObj[VtxLoop].UVSize.x, 
											g_TitleObj[VtxLoop].UV.y + g_TitleObj[VtxLoop].UVSize.y);
	}

	g_pVtxBufferTitle -> Unlock();
}

//==========================================================================================
// 描画処理
//==========================================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得
	
	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferTitle,
							  0,					//オフセット
							  sizeof(VERTEX2D));		//ストライド量

	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	//ポリゴンの描画
	for(int iDraw = 0; iDraw < TITLE_OBJ_MAX; iDraw++){
		//描画をする場合
		if(g_TitleObj[iDraw].bDraw == true){
			
			//テクスチャを使用するかどうか
			if(g_TitleObj[iDraw].label != TITLE_TEX_NONE){
				pDevice -> SetTexture(0, g_pTextureTitle[g_TitleObj[iDraw].label]);
			}
			else{
				pDevice -> SetTexture(0, NULL);
			}
			
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
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ

	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX2D)*NUM_VERTEX*TITLE_OBJ_MAX,	//確保したい頂点バッファの数＊頂点数
								  D3DUSAGE_WRITEONLY,	//確保した後中を見ることはできない
								  FVF_VERTEX_2D,		//一応書かずとも平気
								  D3DPOOL_MANAGED,		//メモリ管理をどうするか(これはお任せ)
								  &g_pVtxBufferTitle,
								  NULL)))
	{
		return E_FAIL;
	}

	//仮想アドレスを取得する
	g_pVtxBufferTitle -> Lock(0, 0, (void**)&pVtx, 0);

	for(int VtxLoop = 0; VtxLoop < TITLE_OBJ_MAX; VtxLoop++){

		//頂点座標の設定（x, y, z）
		pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x - g_TitleObj[VtxLoop].Size.x,
											g_TitleObj[VtxLoop].Pos.y - g_TitleObj[VtxLoop].Size.y, 0.0f);

		pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x + g_TitleObj[VtxLoop].Size.x,
											g_TitleObj[VtxLoop].Pos.y - g_TitleObj[VtxLoop].Size.y, 0.0f);

		pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x - g_TitleObj[VtxLoop].Size.x,
											g_TitleObj[VtxLoop].Pos.y + g_TitleObj[VtxLoop].Size.y, 0.0f);

		pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x + g_TitleObj[VtxLoop].Size.x,
											g_TitleObj[VtxLoop].Pos.y + g_TitleObj[VtxLoop].Size.y, 0.0f);

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

	g_pVtxBufferTitle -> Unlock();

	return S_OK;
}
