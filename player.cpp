//============================================
//  Player関数  (Player.cpp)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年05月31日
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
#include "player.h"
#include "bullet.h"
#include "fcoh.h"
#include "input.h"
#include "inputX.h"
#include "notes.h"
#include "sound.h"

#include "effect.h"

//============================================
//
//  定数宣言
//
//============================================
//読み込むテクスチャファイル名
#define POLYGON_TEXTURENAME "data/TEXTURE/GAME/PLAYER/player.png"//ファイル形式はサウンドもスクリプトもおんなじよ
                                                       //ほかにもjpg,png,tga,bmp,dds

#define POLYGON_POS_X  (50)//ポリゴンの表示位置X
#define POLYGON_POS_Y  (60)//ポリゴンの表示位置Y
#define POLYGON_WIDTH  (100)//ポリゴンの幅
#define POLYGON_HEIGHT (100)//ポリゴンの高さ
#define PLAYER_LIFE (100)
#define PLAYER_MOVE 10.0f // 何フレームで次の場所に移動するか

//============================================
//
//  グローバル変数
//
//============================================
VERTEX2D g_aVertex[NUM_VERTEX];//頂点情報を格納するための配列
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//ポリゴンの張るテクスチャ、テクスチャインターフェース

// プレイヤー
PLAYER g_aPlayer;

static float g_fPosPlayer[5][3] = {
	{POLYGON_POS_X,PLAYER_POS_1,0.0f},
	{POLYGON_POS_X,PLAYER_POS_2,0.0f},
	{POLYGON_POS_X,PLAYER_POS_3,0.0f},
	{POLYGON_POS_X,PLAYER_POS_4,0.0f},
	{POLYGON_POS_X,PLAYER_POS_5,0.0f}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PLAYER_MOTION_MAX 3	// モーション最大数

static float g_fPlayerUVSize[6][3][2] = 
{
	{{1.0f / 3.0f, 1.0f / 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f}},								// ニュートラル
	{{1.0f / 3.0f, 1.0f / 6.0f * 2.0f} , {1.0f / 3.0f * 2.0f, 1.0f / 6.0f * 2.0f} , {1.0f, 1.0f / 6.0f * 2.0f}},		// 攻撃
	{{1.0f / 3.0f, 1.0f / 6.0f * 3.0f} , {1.0f / 3.0f * 2.0f, 1.0f / 6.0f * 3.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 3.0f}},	// 前歩き
	{{1.0f / 3.0f, 1.0f / 6.0f * 4.0f} , {1.0f / 3.0f * 2.0f, 1.0f / 6.0f * 4.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 4.0f}},	// 後ろ歩き
	{{1.0f / 3.0f, 1.0f / 6.0f * 5.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 5.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 5.0f}},		// 勝ち
	{{1.0f / 3.0f, 1.0f / 6.0f * 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 6.0f}}			// 負け
};

static float g_fPlayerUV[6][3][2] = 
{
	{{0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f}},														// ニュートラル
	{{0.0f , 1.0f / 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f} , {1.0f / 3.0f * 2.0f, 1.0f / 6.0f}},				// 攻撃
	{{0.0f , 1.0f / 6.0f * 2.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 2.0f} , {0.0f, 1.0f / 6.0f * 2.0f}},	// 前歩き
	{{0.0f , 1.0f / 6.0f * 3.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 3.0f} , {0.0f, 1.0f / 6.0f * 3.0f}},	// 後ろ歩き
	{{0.0f , 1.0f / 6.0f * 4.0f} , {0.0f , 1.0f / 6.0f * 4.0f} , {0.0f , 1.0f / 6.0f * 4.0f}},				// 勝ち
	{{0.0f , 1.0f / 6.0f * 5.0f} , {0.0f , 1.0f / 6.0f * 5.0f} , {0.0f , 1.0f / 6.0f * 5.0f}}				// 負け
};

static int g_nPlayerMode = 0;			// 0:ニュートラル , 1:攻撃 , 2前歩き : ,3:後ろ歩き , 4:勝ち , 5:負け
static int g_nPlayerModeCount = 0;		// 次のモーションまでのカウント
static int g_nPlayerMotionCount = 0;	// 現在再生しているキー

static int g_nPlayerModeTime[6][3] = 
{
	{30,30,30},	// ニュートラル
	{10,5,30},	// 攻撃
	{5,5,5},	// 前歩き
	{5,5,5},	// 後ろ歩き
	{30,30,30},	// 勝ち
	{30,30,30}	// 負け
};

void SetPlayerMode(int nPlayerMode)
{
	g_nPlayerMode = nPlayerMode;
	g_nPlayerModeCount = 0;
	g_nPlayerMotionCount = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//============================================
//
//  プロトタイプ宣言
//
//============================================
void MakeVertexPlayer(LPDIRECT3DDEVICE9 pDevice);//頂点の作成

//============================================
//
//  名前  InitPlayer関数
//  引数	void
//  戻り値  void
//  説明  ポリゴン関係の初期化
//
//============================================
void InitPlayer(void)
{
	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	//頂点作成
	MakeVertexPlayer(pDevice);
	
	//テクスチャ取得
	//エラーチェック必須
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , POLYGON_TEXTURENAME , &g_pTexturePlayer )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","ひゃっほ～い",MB_OK | MB_DEFBUTTON1);
		}//EOif

	// 構造体初期化
	g_aPlayer.bUse = false;
	g_aPlayer.fMove = D3DXVECTOR3(0.0f , (g_fPosPlayer[0][1] - g_fPosPlayer[1][1]) / PLAYER_MOVE, 0.0f);
	g_aPlayer.nPos = 0;
	g_aPlayer.fPos = D3DXVECTOR3(g_fPosPlayer[g_aPlayer.nPos][0] , g_fPosPlayer[g_aPlayer.nPos][1] , 0.0f);
	g_aPlayer.fSize = D3DXVECTOR2(POLYGON_WIDTH , POLYGON_HEIGHT);
	g_aPlayer.nMovePos = 0;
	g_aPlayer.nZanki = 5;


	g_nPlayerMode = 0;			// 0:ニュートラル , 1:攻撃 , 2前歩き : ,3:後ろ歩き , 4:勝ち , 5:負け
	g_nPlayerModeCount = 0;		// 次のモーションまでのカウント
	g_nPlayerMotionCount = 0;	// 現在再生しているキー

}//EOInitPolygin

//============================================
//
//  名前  UninitPlayer関数
//  引数	void
//  戻り値  void
//  説明  ポリゴン関係の終了処理
//
//============================================
void UninitPlayer(void)
{
	//テクスチャインターフェースの後片付け
	SAFE_RELEASE( g_pTexturePlayer );
}//EOUninitPlayer

//============================================
//
//  名前  UpdatePlayer関数
//  引数	void
//  戻り値  void
//  説明  ポリゴン関係の更新処理
//
//============================================
void UpdatePlayer(void)
{
	// 更新
	int nNow = g_aPlayer.nPos; // 現在の位置の確保

	// 上下
	if(GetKeyboardTrigger(DIK_UP) || GetKeyXInputTrigger(XINPUT_DPAD_UP))
	{
		if(g_aPlayer.nPos > 0)
		{
			g_aPlayer.nPos--;
			g_aPlayer.fPos.x = g_fPosPlayer[g_aPlayer.nPos][0];
			SetPlayerMode(3);
			PlaySound(SE_GAME_PLAEYR_FOOT_VILLEGE);

		} // EO if
	} // EO if

	if(GetKeyboardTrigger(DIK_DOWN) || GetKeyXInputTrigger(XINPUT_DPAD_DOWN))
	{
		if(g_aPlayer.nPos < 4)
		{
			g_aPlayer.nPos++;
			g_aPlayer.fPos.x = g_fPosPlayer[g_aPlayer.nPos][0];
			SetPlayerMode(2);
			PlaySound(SE_GAME_PLAEYR_FOOT_VILLEGE);
		} // EO if
	} // EO if


	// もし移動場所が変わったら
	if(nNow != g_aPlayer.nPos)
	{
		g_aPlayer.fMove.y = (g_fPosPlayer[g_aPlayer.nPos][1] - g_aPlayer.fPos.y) / PLAYER_MOVE;
	}
	
	if(g_aPlayer.fPos.y >= g_fPosPlayer[g_aPlayer.nPos][1] - 0.01f && g_aPlayer.fPos.y <= g_fPosPlayer[g_aPlayer.nPos][1] + 0.01f)
	{
		g_aPlayer.fPos.y = g_fPosPlayer[g_aPlayer.nPos][1];
	}

	if(g_aPlayer.fPos.y != g_fPosPlayer[g_aPlayer.nPos][1])
	{
			g_aPlayer.fPos.y += g_aPlayer.fMove.y;
	//	if(g_aPlayer.fPos.y >= g_fPosPlayer[g_aPlayer.nPos][1])
	//	{
	//		g_aPlayer.fPos.y += g_aPlayer.fMove.y;
	//	} // EO if
	//	else
	//	{
	//		g_aPlayer.fPos.y -= g_aPlayer.fMove.y;
	//	}
	//}
	}
	//弾発射
	if(GetKeyboardTrigger(DIK_Z) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A))
	{
		setBullet(D3DXVECTOR3(
			g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
			g_fPosPlayer[g_aPlayer.nPos][1],
			0.f),
			BULLET000);
			SetPlayerMode(1);
			PlaySound(SE_GAME_MAGIC_GO);
	}
	if(GetKeyboardTrigger(DIK_X) || GetKeyXInputTrigger(XINPUT_GAMEPAD_B))
	{
		setBullet(D3DXVECTOR3(
			g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
			g_fPosPlayer[g_aPlayer.nPos][1],
			0.f), BULLET001);
			SetPlayerMode(1);
			PlaySound(SE_GAME_MAGIC_GO);
	}
	if(GetKeyboardTrigger(DIK_C) || GetKeyXInputTrigger(XINPUT_GAMEPAD_X))
	{
		setBullet(D3DXVECTOR3(
			g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
			g_fPosPlayer[g_aPlayer.nPos][1],
			0.f), BULLET002);
			SetPlayerMode(1);
			PlaySound(SE_GAME_MAGIC_GO_BOMM);
	}
	//if (GetKeyboardTrigger(DIK_V) || GetKeyXInputTrigger(XINPUT_GAMEPAD_X))
	//{
	//	setBullet(D3DXVECTOR3(
	//		g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
	//		g_fPosPlayer[g_aPlayer.nPos][1],
	//		0.f), BULLET003);
	//		SetPlayerMode(1);
	//		PlaySound(SE_GAME_MAGIC_GO_DIFISION);
	//}
	if (GetKeyboardTrigger(DIK_SPACE)  || GetKeyXInputTrigger(XINPUT_RIGHT_SHOULDER))
	{
		setFcoh();
		SetPlayerMode(1);
		PlaySound(SE_GAME_MAGIC_ON_KILL);
	}

	//if(GetKeyXInputTrigger(XINPUT_GAMEPAD_A))
	//{
	//	setBullet(D3DXVECTOR3(
	//		g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
	//		g_fPosPlayer[g_aPlayer.nPos][1],
	//		0.f), BULLET000);
	//		SetPlayerMode(1);
	//}
	//if(GetKeyXInputTrigger(XINPUT_GAMEPAD_B))
	//{
	//	setBullet(D3DXVECTOR3(
	//		g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
	//		g_fPosPlayer[g_aPlayer.nPos][1],
	//		0.f), BULLET001);
	//		SetPlayerMode(1);
	//}
	// END更新

	// モーション
	g_nPlayerModeCount++;
	if(g_nPlayerModeCount >= g_nPlayerModeTime[g_nPlayerMode][g_nPlayerMotionCount])
	{
		g_nPlayerModeCount = 0;
		g_nPlayerMotionCount++;
		if(g_nPlayerMotionCount >= PLAYER_MOTION_MAX)
		{
			// モーションが終わったら、ニュートラルにつなげる
			SetPlayerMode(0);
		}
	}

	//頂点座標の設定(2D座標・右回り)
	g_aVertex[0].pos = D3DXVECTOR3(g_aPlayer.fPos.x - g_aPlayer.fSize.x / 2.0f,//X
		g_aPlayer.fPos.y - g_aPlayer.fSize.y / 2.0f,//Y
		0.0f);//Z,これで1つの頂点
	g_aVertex[1].pos = D3DXVECTOR3(g_aPlayer.fPos.x + g_aPlayer.fSize.x / 2.0f ,//X
		g_aPlayer.fPos.y - g_aPlayer.fSize.y / 2.0f,//Y
		0.0f);//Z,これで1つの頂点
	g_aVertex[2].pos = D3DXVECTOR3(g_aPlayer.fPos.x - g_aPlayer.fSize.x / 2.0f ,//X
		g_aPlayer.fPos.y + g_aPlayer.fSize.y / 2.0f,//Y
		0.0f);//Z,これで1つの頂点
	g_aVertex[3].pos = D3DXVECTOR3(g_aPlayer.fPos.x + g_aPlayer.fSize.x / 2.0f,//X
		g_aPlayer.fPos.y + g_aPlayer.fSize.y / 2.0f,//Y
		0.0f);//Z,これで1つの頂点

	//rhwの設定(必ず1.0fを入れる!!!!!!!!)
	g_aVertex[0].rhw = 1.0f;
	g_aVertex[1].rhw = 1.0f;
	g_aVertex[2].rhw = 1.0f;
	g_aVertex[3].rhw = 1.0f;

	//頂点カラー(0～255の整数値)
	g_aVertex[0].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[1].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[2].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[3].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	//頂点UV値の設定
	g_aVertex[0].tex = D3DXVECTOR2( g_fPlayerUV[g_nPlayerMode][g_nPlayerMotionCount][0] ,
		g_fPlayerUV[g_nPlayerMode][g_nPlayerMotionCount][1] );
	g_aVertex[1].tex = D3DXVECTOR2(  g_fPlayerUVSize[g_nPlayerMode][g_nPlayerMotionCount][0] ,
		g_fPlayerUV[g_nPlayerMode][g_nPlayerMotionCount][1]  );
	g_aVertex[2].tex = D3DXVECTOR2( g_fPlayerUV[g_nPlayerMode][g_nPlayerMotionCount][0] ,
		 g_fPlayerUVSize[g_nPlayerMode][g_nPlayerMotionCount][1] );
	g_aVertex[3].tex = D3DXVECTOR2( g_fPlayerUVSize[g_nPlayerMode][g_nPlayerMotionCount][0],
		 g_fPlayerUVSize[g_nPlayerMode][g_nPlayerMotionCount][1]  );

}//EOUpdatePlayer

//============================================
//
//  名前  DrawPlayer関数
//  引数	void
//  戻り値  void
//  説明  ポリゴン関係の描画処理
//
//============================================
void DrawPlayer(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	//ポリゴンの描画をする寸前
	pDevice -> SetTexture( 0 , g_pTexturePlayer );
	//プリミティブの描画
	pDevice -> DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		NUM_POLYGON,//プリミティブの数、ポリゴンの増やし忘れに注意
		&g_aVertex[0],//頂点データの先頭アドレス
		sizeof(VERTEX2D)//頂点データ一個分のサイズ(単位はバイト)
		);
}//EODarwPlayer

//============================================
//
//  名前  MakeVertexPlayer関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
void MakeVertexPlayer(LPDIRECT3DDEVICE9 pDevice)
{
	//頂点座標の設定(2D座標・右回り)
	g_aVertex[0].pos = D3DXVECTOR3(g_aPlayer.fPos.x ,//X
		g_aPlayer.fPos.y ,//Y
		0.0f);//Z,これで1つの頂点
	g_aVertex[1].pos = D3DXVECTOR3(g_aPlayer.fPos.x + g_aPlayer.fSize.x ,//X
		g_aPlayer.fPos.y ,//Y
		0.0f);//Z,これで1つの頂点
	g_aVertex[2].pos = D3DXVECTOR3(g_aPlayer.fPos.x ,//X
		g_aPlayer.fPos.y + g_aPlayer.fSize.y ,//Y
		0.0f);//Z,これで1つの頂点
	g_aVertex[3].pos = D3DXVECTOR3(g_aPlayer.fPos.x + g_aPlayer.fSize.x ,//X
		g_aPlayer.fPos.y + g_aPlayer.fSize.y ,//Y
		0.0f);//Z,これで1つの頂点

	//rhwの設定(必ず1.0fを入れる!!!!!!!!)
	g_aVertex[0].rhw = 1.0f;
	g_aVertex[1].rhw = 1.0f;
	g_aVertex[2].rhw = 1.0f;
	g_aVertex[3].rhw = 1.0f;

	//頂点カラー(0～255の整数値)
	g_aVertex[0].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[1].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[2].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[3].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	//頂点UV値の設定
	g_aVertex[0].tex = D3DXVECTOR2( 0.0f , 0.0f );
	g_aVertex[1].tex = D3DXVECTOR2( 1.0f , 0.0f );
	g_aVertex[2].tex = D3DXVECTOR2( 0.0f , 1.0f );
	g_aVertex[3].tex = D3DXVECTOR2( 1.0f , 1.0f );
}//EOMakeVertexPlayer

PLAYER* GetPlayer(void)
{
	return &g_aPlayer;
}
