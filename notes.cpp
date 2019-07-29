//============================================
//  Notes関数  (Notes.cpp)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
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
#include "main.h"
#include "notes.h"
#include "player.h"
#include "stage.h"
#include "input.h"
#include "sound.h"

#include "castle.h"
#include "gate.h"

#include "heart.h"
#include "warning.h"

//============================================
//
//  定数宣言
//
//============================================
#define NOTES_UV_SPEED                (5)						// 何フレームでUVアニメーションするか
#define NOTES_U_WIDTH                 (0.5f)					// U幅
#define NOTES_V_HEIGHT                (1.0f)					// V高さ
#define NOTES_POINT_TYPE_ONE          (5)						// 攻撃力1 スライム
#define NOTES_POINT_TYPE_FOUR         (5)						// 攻撃力2 ゴーレム
#define NOTES_POINT_TYPE_FIVE         (5)						// 攻撃力3 パンサー
#define NOTES_ATTACK_TIME             (120)						// 攻撃間隔

#define NOTES_SPEED_SLOW              (1.0f)					// 遅いスピード
#define NOTES_SPEED_NORMAL            (5.0f)					// 普通スピード
#define NOTES_SPEED_FAST              (3.0f)					// 速いスピード
#define NOTES_NUM_TIMEPLASS           (10)						// タイムが増加する敵の数
#define NOTES_DIST_TIMEPLASS          (SCREEN_WIDTH / 5 * 2)	// タイムが増加する敵の位置
#define NOTES_POINT_TYPE_TWO          (5)						// 攻撃力2
#define NOTES_POINT_TYPE_THREE        (5)						// 攻撃力3
#define NOTES_POINT_TYPE_SIX          (5)						// 点数6
#define NOTES_POINT_TYPE_SEVEN        (5)						// 点数7

#define NOTES_ANIM_SPEED_1 30 // アニメーションスピード スライム
#define NOTES_ANIM_SPEED_2 60 // アニメーションスピード ゴーレム
#define NOTES_ANIM_SPEED_3 90 // アニメーションスピード

#define NOTES_STOP_TIME 30 // 止まる時間

//読み込むテクスチャファイル名
#define NOTES_ONE_TEXTURENAME       "data/TEXTURE/GAME/ENEMY/Notes01.png"   // NNOTES_ONE
#define NOTES_TWO_TEXTURENAME       "data/TEXTURE/GAME/ENEMY/Notes02.png"   // NNOTES_TWO
#define NOTES_THREE_TEXTURENAME     "data/TEXTURE/GAME/ENEMY/Notes03.png"   // NNOTES_THREE
#define NOTES_FOUR_TEXTURENAME      "data/TEXTURE/GAME/ENEMY/Notes04.png"   // NNOTES_FOUR
#define NOTES_FIVE_TEXTURENAME      "data/TEXTURE/GAME/ENEMY/Notes05.png"   // NNOTES_FIVE
#define NOTES_SIX_TEXTURENAME       "data/TEXTURE/GAME/ENEMY/Notes06.png"   // NNOTES_SIX
#define NOTES_SEVEN_TEXTURENAME     "data/TEXTURE/GAME/ENEMY/Notes07.png"   // NNOTES_SEVEN
#define NOTES_SEVEN_2_TEXTURENAME   "data/TEXTURE/GAME/ENEMY/Notes07-2.png" // NNOTES_SEVEN-2

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureNotes[NOTES_MAX] = {};//Notesの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferNotes = NULL;//ポインター!!&初期化

/*ノーツ構造体*/
NOTES g_aNotes[MAX_NOTES];
int g_nEnemyTime; // 時間が戻る敵のカウント
int g_nTimeGame; // ゲーム時間のカウント

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexNotes(LPDIRECT3DDEVICE9 pDevice);//頂点の作成

//============================================
//
//  名前  InitNotes関数
//  引数	void
//  戻り値  void
//  説明  Notes関係の初期化
//
//============================================
HRESULT InitNotes(void)
{
	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//頂点作成
	if(FAILED(MakeVertexNotes(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//テクスチャ取得
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_ONE_TEXTURENAME , &g_pTextureNotes[0] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","NOTES_ONE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_TWO_TEXTURENAME , &g_pTextureNotes[1] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","NOTES_TWO",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_THREE_TEXTURENAME , &g_pTextureNotes[2] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","NOTES_THREE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_FOUR_TEXTURENAME , &g_pTextureNotes[3] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","NOTES_FOUR",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_FIVE_TEXTURENAME , &g_pTextureNotes[4] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","NOTES_FIVE",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_SIX_TEXTURENAME , &g_pTextureNotes[5] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","NOTES_SIX",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_SEVEN_TEXTURENAME , &g_pTextureNotes[6] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","NOTES_SEVEN",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_SEVEN_2_TEXTURENAME , &g_pTextureNotes[7] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","NOTES_SEVEN_2",MB_OK | MB_DEFBUTTON1);
		}//EOif
	// ノーツ構造体の初期化
	for(int nCntNotes = 0 ; nCntNotes < MAX_NOTES ; nCntNotes++)
	{
		g_aNotes[nCntNotes].bUse = false;
		g_aNotes[nCntNotes].nMode = NOTES_NONE;
		g_aNotes[nCntNotes].fHeight = 0.0f;
		g_aNotes[nCntNotes].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aNotes[nCntNotes].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aNotes[nCntNotes].fHeight = 1.0f;
		g_aNotes[nCntNotes].fWidth = 0.5f;
		g_aNotes[nCntNotes].fFlame = 0;
		g_aNotes[nCntNotes].nLife = 0;
		g_aNotes[nCntNotes].nNumWarning = 0;
		g_aNotes[nCntNotes].nTimeAttack = 0;
		g_aNotes[nCntNotes].nAnimTime = 0;
		g_aNotes[nCntNotes].nNumHp = -1;
		g_aNotes[nCntNotes].bMoveFlag = true;

		g_aNotes[nCntNotes].bStop = false;
		g_aNotes[nCntNotes].nCntDamegeTime = 0;
		g_aNotes[nCntNotes].nStopDamage = 0;
	} // EO for

	// タイム増加の敵破壊数のリセット
	g_nEnemyTime = 0;
	g_nTimeGame = 0;
	return S_OK;
}//EOInitNotes

//============================================
//
//  名前  UninitNotes関数
//  引数	void
//  戻り値  void
//  説明  Notes関係の終了処理
//
//============================================
void UninitNotes(void)
{
	for(int nCntNotes = 0 ; nCntNotes < NOTES_MAX  ; nCntNotes++)
	{
		//テクスチャインターフェースの後片付け
		SAFE_RELEASE( g_pTextureNotes[nCntNotes] );
	} // EO for

	//頂点バッファの後片付け
	SAFE_RELEASE( g_pVtxBufferNotes );
}//EOUninitNotes

//============================================
//
//  名前  UpdateNotes関数
//  引数	void
//  戻り値  void
//  説明  Notes関係の更新処理
//
//============================================
void UpdateNotes(void)
{
	// 敵の発生
	switch(getStgNum())
	{
	case STAGE_00:
	{
		SetStage00();
		break;
	}

	case STAGE_01:
	{
		SetStage01();
		break;
	}

	case STAGE_02:
	{
		SetStage02();
		break;
	}

	case STAGE_03:
	{
		SetStage03();
		break;
	}

	case STAGE_04:
	{
		SetStage04();
		break;
	}

	case STAGE_05:
	{
		SetStage05();
		break;
	}

	case STAGE_06:
	{
		SetStage07();
		break;
	}

	case STAGE_08:
	{
		SetStage08();
		break;
	}

	case STAGE_09:
	{
		SetStage09();
		break;
	}
	}

	g_nTimeGame++;
	GATE* pGate = GetGate();

	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo

		//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferNotes -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

	// UVアニメーションでノーツ
	for(int nCntNotes = 0 ; nCntNotes < MAX_NOTES ; nCntNotes++)
	{
		// 使用チェック
		if(g_aNotes[nCntNotes].bUse == true)
		{
			//頂点座標の設定(2D座標 , 右回り )
			pVtx [ 0 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aNotes[nCntNotes].fPos.x , g_aNotes[nCntNotes].fPos.y , 0.0f);
			pVtx [ 1 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aNotes[nCntNotes].fPos.x + g_aNotes[nCntNotes].fWidth ,g_aNotes[nCntNotes].fPos.y , 0.0f);
			pVtx [ 2 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aNotes[nCntNotes].fPos.x , g_aNotes[nCntNotes].fPos.y + g_aNotes[nCntNotes].fHeight , 0.0f);
			pVtx [ 3 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aNotes[nCntNotes].fPos.x + g_aNotes[nCntNotes].fWidth , g_aNotes[nCntNotes].fPos.y + g_aNotes[nCntNotes].fHeight , 0.0f);

		    //各頂点のテクスチャ座標の設定
			pVtx [ 0 + 4*nCntNotes] . tex = D3DXVECTOR2 (g_aNotes[nCntNotes].fUV.x , g_aNotes[nCntNotes].fUV.y);
			pVtx [ 1 + 4*nCntNotes] . tex = D3DXVECTOR2 (g_aNotes[nCntNotes].fUV.x + NOTES_U_WIDTH , g_aNotes[nCntNotes].fUV.y);
			pVtx [ 2 + 4*nCntNotes] . tex = D3DXVECTOR2 (g_aNotes[nCntNotes].fUV.x , g_aNotes[nCntNotes].fUV.y + NOTES_V_HEIGHT);
			pVtx [ 3 + 4*nCntNotes] . tex = D3DXVECTOR2 (g_aNotes[nCntNotes].fUV.x + NOTES_U_WIDTH , g_aNotes[nCntNotes].fUV.y+ NOTES_V_HEIGHT);


			// 体力によって赤くなる
			float par = (float)g_aNotes[nCntNotes].nLife / (float)g_aNotes[nCntNotes].nNumLife;
			//頂点カラー(0～255の整数値)
			pVtx[0 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f * par, 1.0f * par , 1.0f);
			pVtx[1 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f * par, 1.0f * par , 1.0f);
			pVtx[2 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f * par, 1.0f * par , 1.0f);
			pVtx[3 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f * par, 1.0f * par , 1.0f);

		//////////////////////////////////////////////////
			//  もしUVアニメーションするならここ、爆発参照  //
			//////////////////////////////////////////////////

			// 門の当たり判定
			for(int i = 0 ; i < GATE_NUM ; i++)
			{
				if((pGate + i)->bUse == true && (pGate + i)->nHp > 0)
				{
					if((pGate + i)->fPos.x + (pGate + i)->fSize.x >= g_aNotes[nCntNotes].fPos.x &&
						(pGate + i)->fPos.x <= g_aNotes[nCntNotes].fPos.x &&
						(pGate + i)->fPos.y <= g_aNotes[nCntNotes].fPos.y + g_aNotes[nCntNotes].fHeight / 2.0f&&
						(pGate + i)->fPos.y + (pGate + i)->fSize.y >= g_aNotes[nCntNotes].fPos.y + g_aNotes[nCntNotes].fHeight / 2.0f)
					{
						g_aNotes[nCntNotes].bUpdateFlag = false;
						g_aNotes[nCntNotes].nTimeAttack++;
						if(g_aNotes[nCntNotes].nTimeAttack >= NOTES_ATTACK_TIME)
						{
							g_aNotes[nCntNotes].nTimeAttack = 0;
							AddLife(i , g_aNotes[nCntNotes].nPoint * -1);
						}
					}
				}
			}

			////////////////////////
			//  移動量の場合分け  //
			////////////////////////
			// 毎フレームの移動   //
			//////////////////////////////////////////////////
			// プレイヤーの位置把握
			PLAYER* pPlayer = GetPlayer();


			if(g_aNotes[nCntNotes].bStop == false)
			{
				switch(g_aNotes[nCntNotes].nMode)
				{
				case NOTES_ONE: // 直進
					if(g_aNotes[nCntNotes].bUpdateFlag == true)
					{
						g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_SLOW;
					}
					g_aNotes[nCntNotes].nAnimTime++;
					if(g_aNotes[nCntNotes].nAnimTime >= NOTES_ANIM_SPEED_1)
					{
						g_aNotes[nCntNotes].nAnimTime = 0;
						g_aNotes[nCntNotes].bUpdateFlag = !g_aNotes[nCntNotes].bUpdateFlag;
						g_aNotes[nCntNotes].fUV.x += 0.5f;
					}
					break;
				case NOTES_TWO: // Yがプレイヤーに向かってくる
					g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_NORMAL;
					if(g_aNotes[nCntNotes].fPos.y >= pPlayer -> fPos.y)
					{
						g_aNotes[nCntNotes].fPos.y -= 1.0f;
					} // EO if
					else
					{
						g_aNotes[nCntNotes].fPos.y += 1.0f;
					} // EO else
					break;
				case NOTES_THREE: // cosカーブ
					g_aNotes[nCntNotes].fFlame += 0.05f;
					g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_NORMAL;
					g_aNotes[nCntNotes].fPos.y -= cosf(g_aNotes[nCntNotes].fFlame) * 10;
					if(g_aNotes[nCntNotes].fFlame >= D3DX_PI)
					{
						g_aNotes[nCntNotes].fFlame = 0.0f;
					} // EO if
					break;
				case NOTES_FOUR: // 直進して、一時停止
					g_aNotes[nCntNotes].nAnimTime++;
					if(g_aNotes[nCntNotes].nAnimTime >= NOTES_ANIM_SPEED_3)
					{
						g_aNotes[nCntNotes].nAnimTime = 0;
						g_aNotes[nCntNotes].bUpdateFlag = !g_aNotes[nCntNotes].bUpdateFlag;
						g_aNotes[nCntNotes].fUV.x += 0.5f;
					}

					if(g_aNotes[nCntNotes].bUpdateFlag == true)
					{
						g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_FAST;
					} // EO if
					break;
				case NOTES_FIVE: // ゆっくり直進
					g_aNotes[nCntNotes].nAnimTime++;
					if(g_aNotes[nCntNotes].bUpdateFlag == true)
					{
						g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_SLOW;
					}
					if(g_aNotes[nCntNotes].nAnimTime >= NOTES_ANIM_SPEED_2)
					{
						g_aNotes[nCntNotes].nAnimTime = 0;
						g_aNotes[nCntNotes].bUpdateFlag = !g_aNotes[nCntNotes].bUpdateFlag;
						g_aNotes[nCntNotes].fUV.x += 0.5f;
					}
				break;
				case NOTES_SIX: // 早く直進(倒されない)
					g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_FAST;


					break;
				case NOTES_SEVEN:
					if(g_aNotes[nCntNotes].fFlame <= 1)
					{
						g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_NORMAL;

						// 左まで来たら
						if(g_aNotes[nCntNotes].fPos.x <= 0)
						{
							g_aNotes[nCntNotes].fFlame = 3;
							g_aNotes[nCntNotes].fPos.x = 0;
						} // EO if
					} // EO if

					// 跳ね返る
					if(g_aNotes[nCntNotes].fFlame > 1)
					{
						g_aNotes[nCntNotes].fPos.x += NOTES_SPEED_NORMAL;

						// 壁まで来たら
						if(g_aNotes[nCntNotes].fPos.x > SCREEN_WIDTH)
						{
							g_aNotes[nCntNotes].bUse = false;
						} // EO if
					} // EO if

					// Yがプレイヤーを追う
					if(g_aNotes[nCntNotes].fPos.y >= pPlayer -> fPos.y)
					{
						g_aNotes[nCntNotes].fPos.y -= 3.0f;
					} // EO if
					else
					{
						g_aNotes[nCntNotes].fPos.y += 1.0f;
					} // EO else

					break;
				} // EO switch
			}
			else
			{
				g_aNotes[nCntNotes].nCntDamegeTime++;
				if(g_aNotes[nCntNotes].nCntDamegeTime >= NOTES_STOP_TIME)
				{
					g_aNotes[nCntNotes].nCntDamegeTime = 0;
					AddDameage(nCntNotes , g_aNotes[nCntNotes].nStopDamage);
					g_aNotes[nCntNotes].bStop = false;
				}
			}
			//////////////////////////////////////////////////

			////////////////////
			// 壁来たら消える //
			//////////////////////////////////////////////////
			if(g_aNotes[nCntNotes].fPos.x + g_aNotes[nCntNotes].fWidth <= 0)
			{
				// ライフ0により消滅
				g_aNotes[nCntNotes].bUse = false;

				// 城にダメージ
				AddDamegeCastle(g_aNotes[nCntNotes].nPoint);

				PlaySound(SE_GAME_CASTLE_BREAK);

			} // EO if
			//////////////////////////////////////////////////

			//////////////////////////
			// 体力なくなったら爆発 //
			//////////////////////////////////////////////////
			if(g_aNotes[nCntNotes].nLife <= 0)
			{
				// ライフ0により消滅
				//PlaySound(SOUND_LABEL_SE002);
				g_aNotes[nCntNotes].bUse = false;
				switch(g_aNotes[nCntNotes].nMode)
				{
				case NOTES_ONE:	// スライム
					PlaySound(SE_GAME_ENEMY_KILL_SURAIMU);
					break;
				case NOTES_FIVE:	// ゴーレム
					PlaySound(SE_GAME_ENEMY_KILL_GOREMU);
					break;
				case NOTES_SEVEN:	// パンサー
					PlaySound(SE_GAME_ENEMY_KILL_PANSER);
					break;
				}

			} // EO if
			//////////////////////////////////////////////////

			// 体力更新
			SetUVSizeHeart(g_aNotes[nCntNotes].nNumHp , g_aNotes[nCntNotes].nLife);
			SetPosHeart(g_aNotes[nCntNotes].nNumHp , g_aNotes[nCntNotes].fPos);

			if(g_aNotes[nCntNotes].bUpdateFlag == false)
			{
				int i = 0;
			}
		} // EO if
	} // EO for

	g_pVtxBufferNotes->Unlock ();												//ロック解除

}//EOUpdateNotes

//============================================
//
//  名前  DrawNotes関数
//  引数	void
//  戻り値  void
//  説明  Notes関係の描画処理
//
//============================================
void DrawNotes(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//パイプラインの設定
	pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
						g_pVtxBufferNotes ,//データのある場所(先頭アドレス)
						0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
						sizeof(VERTEX2D) );//ストライド量(一個の単位の大きさ)

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// 最大数チェック
	for(int nCntNotes = 0 ; nCntNotes < MAX_NOTES ; nCntNotes++)
	{
		if(g_aNotes[nCntNotes].bUse == true)
		{
			if(g_aNotes[nCntNotes].bDrawFlag == true)
			{
				// 種類で分ける
				switch(g_aNotes[nCntNotes].nMode)
				{
				case NOTES_ONE:

					//Notesの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureNotes[0] );

					break;
				case NOTES_TWO:

					//Notesの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureNotes[1] );

					break;
				case NOTES_THREE:

					//Notesの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureNotes[2] );

					break;
				case NOTES_FOUR:

					//Notesの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureNotes[3] );

					break;
				case NOTES_FIVE:

					//Notesの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureNotes[4] );

					break;
				case NOTES_SIX:

					//Notesの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureNotes[5] );

					break;
				case NOTES_SEVEN:

					//Notesの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureNotes[6] );
					if(g_aNotes[nCntNotes].fFlame > 1)
					{
						pDevice -> SetTexture( 0 , g_pTextureNotes[7] );
					} // EO if

					break;
				} // EO switch

				//プリミティブの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
					nCntNotes * 4 ,//オフセット(頂点数)何頂点目からとるか
					NUM_POLYGON );//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。
			} // EO if
			else
			{
				g_aNotes[nCntNotes].bDrawFlag = true;
			} // EO if
		} // EO if
	} // EO for
}//EODarwNotes

//============================================
//
//  名前  MakeVertexNotes関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexNotes(LPDIRECT3DDEVICE9 pDevice)
{

	//頂点バッファ作成
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_NOTES,//作成したい頂点バッファのサイズ = 1つの頂点のサイズ * 頂点数
																	//どれくらいメモリほしいか、ここをめっちゃふやすんでーーー
			D3DUSAGE_WRITEONLY,									//頂点バッファの使用方法、書き込み専用なので、恐らく最速
			FVF_VERTEX_2D,										//NULLや0でも大丈夫、マナー的には書こうよ。このバッファの頂点フォーマットを問う
			D3DPOOL_MANAGED,									//メモリ管理どうする設定、この状態はデバイスにお任せ
			&g_pVtxBufferNotes,						//出来上がった頂点バッファを管理するアドレス
			NULL)												//謎だけれどNULL
	))
	{
		return E_FAIL;
	}


	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferNotes -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

		// 最大数回す
	for(int nCntNotes = 0 ; nCntNotes < MAX_NOTES ; nCntNotes++)
	{
		//rhwの設定(必ず1.0fを入れる!!!!!!!!)
		pVtx[0 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[1 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[2 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[3 + 4 * nCntNotes].rhw = 1.0f;

		//頂点カラー(0～255の整数値)
		pVtx[0 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//鍵をアンロック
	g_pVtxBufferNotes -> Unlock();

	return S_OK;

}//EOMakeVertexNotes

//============================================
//
//  名前  SetNotes関数
//  引数	void
//  戻り値  float fPosX ,float fPosY,float fWidth,float fHeught,Notes_MODE nMode
//  説明  ノーツをセット
//
//============================================
void    SetNotes    (float fPosX , // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	NOTES_MODE nMode			   // 種類
	)
{
	for(int nCntNotes = 0 ; nCntNotes < MAX_NOTES ; nCntNotes++)
	{
		if(g_aNotes[nCntNotes].bUse == false)
		{
			SetWarning(fPosY , WARNING_NORMAL);

			g_aNotes[nCntNotes].bUse = true;
			g_aNotes[nCntNotes].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aNotes[nCntNotes].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aNotes[nCntNotes].fWidth = fWidth;
			g_aNotes[nCntNotes].fHeight = fHeught;
			g_aNotes[nCntNotes].fFlame = 0;
			g_aNotes[nCntNotes].nAnimTime = 0;
			g_aNotes[nCntNotes].nMode = nMode;
			g_aNotes[nCntNotes].bMoveFlag = true;
			g_aNotes[nCntNotes].nLife = 1;
			g_aNotes[nCntNotes].nNumLife = 1;
			g_aNotes[nCntNotes].nTimeAttack = 0;
			if(nMode == NOTES_FIVE)
			{
				g_aNotes[nCntNotes].nLife = 2;
				g_aNotes[nCntNotes].nNumLife = 2;
			}


			g_aNotes[nCntNotes].nNumHp = SetHeart(fPosX , fPosY , 20 , 20 , g_aNotes[nCntNotes].nLife);

			g_aNotes[nCntNotes].nNumWarning = -1;

			switch(nMode)
			{
			case NOTES_ONE:

				g_aNotes[nCntNotes].nPoint = NOTES_POINT_TYPE_ONE;

				break;
			case NOTES_TWO:

				g_aNotes[nCntNotes].nPoint = NOTES_POINT_TYPE_TWO;


				break;
			case NOTES_THREE:

				g_aNotes[nCntNotes].nPoint = NOTES_POINT_TYPE_THREE;


				break;
			case NOTES_FOUR:

				g_aNotes[nCntNotes].nPoint = NOTES_POINT_TYPE_FOUR;


				break;
			case NOTES_FIVE:

				g_aNotes[nCntNotes].nPoint = NOTES_POINT_TYPE_FIVE;


				break;
			case NOTES_SIX:

				g_aNotes[nCntNotes].nPoint = NOTES_POINT_TYPE_SIX;


				break;
			case NOTES_SEVEN:
				g_aNotes[nCntNotes].nPoint = NOTES_POINT_TYPE_SEVEN;

				break;
			} // EO switch
			break;
		} // EO if
	} // EO for
} // EO SetNotes

//============================================
//
//  名前  GetNotes関数
//  引数	void
//  戻り値  NOTES *g_aNotes[0]
//  説明  g_aNotesの先頭アドレスを渡す
//
//============================================
NOTES* GetNotes()
{
	return &g_aNotes[0];
} // EO GetNotes

//============================================
//
//  名前  CheckEnemyTime関数
//  引数	void
//  戻り値  true or false
//  説明  敵破壊数が規定を満たしているかどうかを返す
//
//============================================
bool CheckEnemyTime (void)
{
	// 敵破壊数が一定までいっていたら
	if(g_nEnemyTime >= NOTES_NUM_TIMEPLASS)
	{
		g_nEnemyTime = 0;

		return true;
	} // EO if
	return false;
} // EO CheckEnemyTime

void    AddDameage(int nID , int nDamege)
{
	if(g_aNotes[nID].bUse == true)
	{
		g_aNotes[nID].nLife -= nDamege;
		if(g_aNotes[nID].nLife <= 0)
		{
			//PlaySound(SOUND_LABEL_SE002);
				switch(g_aNotes[nID].nMode)
				{
				case NOTES_ONE:	// スライム
					PlaySound(SE_GAME_ENEMY_KILL_SURAIMU);
					break;
				case NOTES_FIVE:	// ゴーレム
					PlaySound(SE_GAME_ENEMY_KILL_GOREMU);
					break;
				case NOTES_SEVEN:	// パンサー
					PlaySound(SE_GAME_ENEMY_KILL_PANSER);
					break;
				}
				OffHeart(g_aNotes[nID].nNumHp);
			g_aNotes[nID].bUse = false;
		} // EO if
	} // EO if
} // EO AddDameage

D3DXVECTOR3    GetEnemyPos(int n)
{
	if(g_aNotes[n].bUse == true)
		return D3DXVECTOR3(g_aNotes[n].fPos.x , g_aNotes[n].fPos.y , 0.0f);

	return D3DXVECTOR3(0.0f , 0.0f , 0.0f);
}

int GetTimeGameNow()
{
	return g_nTimeGame;
}

bool GetZeroNotes(void)	// 敵がすべてfalseならtrue,そうでないならfalseを返す
{
	int i;
	for(i = 0 ; i < MAX_NOTES; i++)
	{
		if(g_aNotes[i].bUse == true)
		{
			return false;
		}
	}
	return true;
}

void StopDamage(int nIndex , int nDamage)
{
	if(g_aNotes[nIndex].bUse == false)
	{
		return;
	}

	g_aNotes[nIndex].bStop = true;
	g_aNotes[nIndex].nStopDamage = nDamage;
}
