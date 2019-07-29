//============================================
//  Boss関数  (Boss.cpp)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2017年05月26日
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
#include "boss.h"
#include "sound.h"
#include "bulletBoss.h"
#include "notes.h"
#include "nucleusBoss.h"
#include "game.h"
#include "gate.h"

#include "castle.h"

#include "heart.h"

//============================================
//
//  定数宣言
//
//============================================
#define BOSS_UV_SPEED                (10)                  // 何フレームでUVアニメーションするか
#define BOSS_SPEED_SLOW              (0.5)               // 遅いスピード
#define BOSS_BULLET_TIME 180
#define BOSS_MOVE 30 // ボスが動けない時間
#define BOSS_NUVLESUS_TIME 120 // 核が見える時間
#define BOSS_ATTACK_TIME 120 // ボスが門に当たって攻撃する間隔
#define BOSS_ATTACK 30 // ボスが門に当たって攻撃力


// 幅高さ
#define BOSS_HEIGHT_1 (SCREEN_HEIGHT / 100.0f * 80)	// 木
#define BOSS_HEIGHT_2 (SCREEN_HEIGHT / 100.0f * 70)	// 雪
#define BOSS_HEIGHT_3 (SCREEN_HEIGHT / 100.0f * 70)	// ドラゴン

#define BOSS_WIDTH_1 (SCREEN_WIDTH / 100.0f * 30)
#define BOSS_WIDTH_2 (SCREEN_WIDTH / 100.0f * 30)
#define BOSS_WIDTH_3 (SCREEN_WIDTH / 100.0f * 30)

// ボスが来れる場所
#define BOSS_CAN_COME_1	(SCREEN_WIDTH / 100.0f * 85.0f)
#define BOSS_CAN_COME_2	(SCREEN_WIDTH / 100.0f * 90.0f)
#define BOSS_CAN_COME_3	(SCREEN_WIDTH / 100.0f * 90.0f)

#define BOSS_HP 20
#//読み込むテクスチャファイル名
#define BOSS_ONE_TEXTURENAME       "data/TEXTURE/GAME/BOSS/boss1.png"   // NBOSS_ONE
#define BOSS_TWO_TEXTURENAME       "data/TEXTURE/GAME/BOSS/Boss02.png"   // NBOSS_TWO
#define BOSS_THREE_TEXTURENAME     "data/TEXTURE/GAME/BOSS/Boss03.png"   // NBOSS_THREE

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureBoss[BOSS_MAX] = {};//Bossの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBoss = NULL;//ポインター!!&初期化

/*ボス構造体*/
BOSS g_aBoss[MAX_BOSS];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BOSS_MOTION_MAX 4	// モーション最大数 1モーションの中のキー数

static float g_fBossUVSize[3][BOSS_MOTION_MAX][2] = 
{
	{{1.0f / 4.0f, 1.0f / 3.0f} , {1.0f / 2.0f, 1.0f / 3.0f} , {1.0f / 4.0f, 1.0f / 3.0f}, {1.0f / 2.0f, 1.0f / 3.0f}},			// ニュートラル
	{{1.0f / 4.0f, 2.0f / 3.0f} , {1.0f / 2.0f, 2.0f / 3.0f} , {3.0f / 4.0f, 2.0f / 3.0f}, {1.0f , 2.0f / 3.0f}},				// 攻撃
	{{1.0f / 4.0f, 1.0f} , {1.0f / 4.0f, 1.0f} , {1.0f / 4.0f, 1.0f}, {1.0f / 4.0f, 1.0f}},										// 混乱
};

static float g_fBossUV[3][BOSS_MOTION_MAX][2] = 
{
	{{0.0f,0.0f} , {1.0f / 4.0f, 0.0f} , {0.0f, 0.0f}, {1.0f / 4.0f,0.0f}},										// ニュートラル
	{{0.0f,1.0f / 3.0f} , {1.0f / 4.0f, 1.0f / 3.0f} , {1.0f / 2.0f, 1.0f / 3.0f}, {3.0f / 4.0f,1.0f / 3.0f}},			// 攻撃
	{{0.0f,2.0f / 3.0f} , {0.0f,2.0f / 3.0f} , {0.0f,2.0f / 3.0f}, {0.0f,2.0f / 3.0f}},							// 混乱
};

static int g_nBossModeTime[6][BOSS_MOTION_MAX] = 
{
	{30,30,30 , 30},	// ニュートラル
	{30,30,30,30},	// 攻撃
	{30,30,30,5}	// 負け
};

void SetBossMode(int nIndex ,int nBossMode)
{
	g_aBoss[nIndex].nBossMode = nBossMode;
	g_aBoss[nIndex].nBossModeCount = 0;
	g_aBoss[nIndex].nBossMotionCount = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexBoss(LPDIRECT3DDEVICE9 pDevice);//頂点の作成

//============================================
//
//  名前  InitBoss関数
//  引数	void
//  戻り値  void
//  説明  Boss関係の初期化
//
//============================================
HRESULT InitBoss(void)
{
	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//頂点作成
	if(FAILED(MakeVertexBoss(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//テクスチャ取得
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , BOSS_ONE_TEXTURENAME , &g_pTextureBoss[0] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSS_ONE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , BOSS_TWO_TEXTURENAME , &g_pTextureBoss[1] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSS_TWO",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , BOSS_THREE_TEXTURENAME , &g_pTextureBoss[2] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSS_THREE",MB_OK | MB_DEFBUTTON1);
		}//EOif


	// ボス構造体の初期化
	for(int nCntBoss = 0 ; nCntBoss < MAX_BOSS ; nCntBoss++)
	{
		g_aBoss[nCntBoss].bUse = false;
		g_aBoss[nCntBoss].nMode = BOSS_NONE;
		g_aBoss[nCntBoss].fHeight = 0.0f;
		g_aBoss[nCntBoss].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aBoss[nCntBoss].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aBoss[nCntBoss].fHeight = 0.0f;
		g_aBoss[nCntBoss].fWidth = 0.0f;
		g_aBoss[nCntBoss].fFlame = 0;
		g_aBoss[nCntBoss].nCntBltTime = BOSS_BULLET_TIME;
		g_aBoss[nCntBoss].nLife = 0;
		g_aBoss[nCntBoss].nNumNoMoveTime = 0;
		g_aBoss[nCntBoss].nCntDamegeTime = 0;
		g_aBoss[nCntBoss].bAttack = false;
		g_aBoss[nCntBoss].nBossMode = 0;
		g_aBoss[nCntBoss].nBossModeCount = 0;
		g_aBoss[nCntBoss].nBossMotionCount = 0;
		g_aBoss[nCntBoss].nNumHeart = -1;
	} // EO for

	return S_OK;
}//EOInitBoss

//============================================
//
//  名前  UninitBoss関数
//  引数	void
//  戻り値  void
//  説明  Boss関係の終了処理
//
//============================================
void UninitBoss(void)
{
	for(int nCntBoss = 0 ; nCntBoss < BOSS_MAX  ; nCntBoss++)
	{
		//テクスチャインターフェースの後片付け
		SAFE_RELEASE( g_pTextureBoss[nCntBoss] );
	} // EO for

	//頂点バッファの後片付け
	SAFE_RELEASE( g_pVtxBufferBoss );
}//EOUninitBoss

//============================================
//
//  名前  UpdateBoss関数
//  引数	void
//  戻り値  void
//  説明  Boss関係の更新処理
//
//============================================
void UpdateBoss(void)
{
	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo

		//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferBoss -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

	GATE* pGate = GetGate();

	bool bAttack = false;

	// UVアニメーションでボス
	for(int nCntBoss = 0 ; nCntBoss < MAX_BOSS ; nCntBoss++)
	{
		// 使用チェック
		if(g_aBoss[nCntBoss].bUse == true)
		{
			g_aBoss[nCntBoss].bMoveFlag = true;

			//頂点座標の設定(2D座標 , 右回り )
			pVtx [ 0 + 4*nCntBoss] . pos = D3DXVECTOR3 (g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f ,
				g_aBoss[nCntBoss].fPos.y  - g_aBoss[nCntBoss].fHeight / 2.0f, 0.0f);
			pVtx [ 1 + 4*nCntBoss] . pos = D3DXVECTOR3 (g_aBoss[nCntBoss].fPos.x + g_aBoss[nCntBoss].fWidth / 2.0f ,
				g_aBoss[nCntBoss].fPos.y - g_aBoss[nCntBoss].fHeight / 2.0f , 0.0f);
			pVtx [ 2 + 4*nCntBoss] . pos = D3DXVECTOR3 (g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f ,
				g_aBoss[nCntBoss].fPos.y + g_aBoss[nCntBoss].fHeight / 2.0f, 0.0f);
			pVtx [ 3 + 4*nCntBoss] . pos = D3DXVECTOR3 (g_aBoss[nCntBoss].fPos.x + g_aBoss[nCntBoss].fWidth / 2.0f ,
				g_aBoss[nCntBoss].fPos.y + g_aBoss[nCntBoss].fHeight / 2.0f, 0.0f);

		    //各頂点のテクスチャ座標の設定
			pVtx [ 0 + 4*nCntBoss] . tex = D3DXVECTOR2 (g_fBossUV[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][0] ,
				g_fBossUV[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][1]);

			pVtx [ 1 + 4*nCntBoss] . tex = D3DXVECTOR2 (g_fBossUVSize[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][0]  ,
				g_fBossUV[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][1]);

			pVtx [ 2 + 4*nCntBoss] . tex = D3DXVECTOR2 (g_fBossUV[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][0] ,
				g_fBossUVSize[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][1]);

			pVtx [ 3 + 4*nCntBoss] . tex = D3DXVECTOR2 (g_fBossUVSize[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][0] ,
				g_fBossUVSize[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][1]);

			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// モーション
			g_aBoss[nCntBoss].nBossModeCount++;


			if(g_aBoss[nCntBoss].nBossModeCount >= g_nBossModeTime[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount])
			{
				g_aBoss[nCntBoss].nBossModeCount = 0;
				g_aBoss[nCntBoss].nBossMotionCount++;
				if(g_aBoss[nCntBoss].nBossMotionCount >= BOSS_MOTION_MAX)
				{
					// モーションが終わったら、ニュートラルにつなげる
					SetBossMode(nCntBoss , 0);
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// 門の当たり判定
			for(int i = 0 ; i < GATE_NUM ; i++)
			{
				if((pGate + i)->bUse == true && (pGate + i)->nHp > 0)
				{
					if((pGate + i)->fPos.x + (pGate + i)->fSize.x >= g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f)
					{
						g_aBoss[nCntBoss].bMoveFlag = false;
						bAttack = true;
					}
				}
			}

		if(bAttack == true)
		{
			g_aBoss[nCntBoss].nCntDamegeTime++;
			if(g_aBoss[nCntBoss].nCntDamegeTime >= BOSS_ATTACK_TIME)
			{
				for(int i = 0 ; i < GATE_NUM ; i++)
				{
					if((pGate + i)->bUse == true && (pGate + i)->nHp > 0)
					{
						if((pGate + i)->fPos.x + (pGate + i)->fSize.x >= g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f)
						{
							g_aBoss[nCntBoss].nCntDamegeTime = 0;
							AddLife(i , -BOSS_ATTACK);
						}
					}
				}
			}
		}
			//////////////////////////////////////////////////
			//  もしUVアニメーションするならここ、爆発参照  //
			//////////////////////////////////////////////////


			// 核の表示
		OnDrawNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[0] , 2);
		OnDrawNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[1] , 2);
		OnDrawNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[2] , 2);
		OnDrawNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[3] , 2);

		////////////////////////
			//  移動量の場合分け  //
			////////////////////////
			// 毎フレームの移動   //
			//////////////////////////////////////////////////
			float fWidth = 100.0f;	// 弾の大きさ
			float fHeight = 200.0f;	// 弾の大きさ

			switch(g_aBoss[nCntBoss].nMode)
			{
			case BOSS_ONE:
				// 再端かつ歩行モーションなら歩かない
				if(g_aBoss[nCntBoss].nBossMode == 0 && g_aBoss[nCntBoss].fPos.x <= BOSS_CAN_COME_1)
				{
					SetBossMode(nCntBoss , 0);
				}

				if(g_aBoss[nCntBoss].nBossMode == 1)
				{
					g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
				}

				if(g_aBoss[nCntBoss].nCntBullet >= g_aBoss[nCntBoss].nCntBltTime)
				{
					SetBossMode(nCntBoss ,1);
					g_aBoss[nCntBoss].nCntBullet = 0;
				}
				else
				{
					g_aBoss[nCntBoss].nCntBullet++;
					
				}

				if(g_aBoss[nCntBoss].nBossMode == 1 && g_aBoss[nCntBoss].nBossMotionCount == 2&& g_aBoss[nCntBoss].nBossModeCount == 5)
					{
						g_aBoss[nCntBoss].nCntBullet = 0;
						switch(rand() % 4)
						{
						case 0:
							SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_ONE + 50,fWidth , fHeight , BOSSBULLET_ONE);
							break;
						case 1:
							SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_TWO+ 50,fWidth ,  fHeight , BOSSBULLET_ONE);
							break;
						case 2:
							SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_THREE+ 50 ,fWidth , fHeight , BOSSBULLET_ONE);
							break;
						case 3:
							SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_FOUR + 50,fWidth , fHeight , BOSSBULLET_ONE);
							break;
						}
					}

				if(g_aBoss[nCntBoss].nNumNoMoveTime <= 0)
				{
					if(g_aBoss[nCntBoss].bMoveFlag == true)
					{
						g_aBoss[nCntBoss].fPos.x -= BOSS_SPEED_SLOW;
					}
				} // EO if
				else
				{
					g_aBoss[nCntBoss].nNumNoMoveTime--;
				}

				// 核の座標セット
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[0] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 60.0f , LINE_ONE + LINE_HEIGHT * 0.45f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[1] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 40.0f , LINE_TWO + LINE_HEIGHT * 0.45f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[2] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x + 30.0f , LINE_ONE + LINE_HEIGHT * 0.45f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[3] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x + 80.0f , LINE_TWO + LINE_HEIGHT * 0.45f));

				// ボスをこれ以上行かせない
				if(g_aBoss[nCntBoss].fPos.x <= BOSS_CAN_COME_1)
				{
					g_aBoss[nCntBoss].fPos.x = BOSS_CAN_COME_1;
				}

			break;

			case BOSS_TWO:
				if(g_aBoss[nCntBoss].nCntBullet >= g_aBoss[nCntBoss].nCntBltTime)
				{
					g_aBoss[nCntBoss].nCntBullet = 0;
					switch(rand() % 100)
					{
					case 0:
						g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
						SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_ONE + fWidth/2.0f,fWidth , fWidth , BOSSBULLET_TWO);
						break;
					case 1:
						g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
						SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_TWO  + fWidth/2.0f,fWidth , fWidth , BOSSBULLET_TWO);
						break;
					case 2:
						g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
						SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_THREE  + fWidth/2.0f,fWidth , fWidth , BOSSBULLET_TWO);
						break;
					case 3:
						g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
						SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_FOUR + fWidth/2.0f ,fWidth , fWidth , BOSSBULLET_TWO);
						break;
					}
				}
				else
				{
					g_aBoss[nCntBoss].nCntBullet++;
					
				}

				if(g_aBoss[nCntBoss].nNumNoMoveTime == 0)
				{
					if(g_aBoss[nCntBoss].bMoveFlag == true)
					{
						g_aBoss[nCntBoss].fPos.x -= BOSS_SPEED_SLOW;
					}
				} // EO if
				else
				{
					g_aBoss[nCntBoss].nNumNoMoveTime--;
				}

				// 核の座標セット
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[0] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_ONE + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[1] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_TWO + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[2] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_THREE + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[3] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_FOUR + LINE_HEIGHT * 0.5f));

				// ボスをこれ以上行かせない
				if(g_aBoss[nCntBoss].fPos.x <= BOSS_CAN_COME_2)
				{
					g_aBoss[nCntBoss].fPos.x = BOSS_CAN_COME_2;
				}
				break;

			case BOSS_THREE:
				if(g_aBoss[nCntBoss].nCntBullet >= g_aBoss[nCntBoss].nCntBltTime)
				{
					g_aBoss[nCntBoss].nCntBullet = 0;
					switch(rand() % 100)
					{
					case 0:
						g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
						SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_ONE + fWidth/2.0f,fWidth , fWidth , BOSSBULLET_THREE);
						break;
					case 1:
						g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
						SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_TWO  + fWidth/2.0f,fWidth , fWidth , BOSSBULLET_THREE);
						break;
					case 2:
						g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
						SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_THREE  + fWidth/2.0f,fWidth , fWidth , BOSSBULLET_THREE);
						break;
					case 3:
						g_aBoss[nCntBoss].nNumNoMoveTime = BOSS_MOVE;
						SetBulletBoss(g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f , LINE_FOUR + fWidth/2.0f ,fWidth , fWidth , BOSSBULLET_THREE);
						break;
					}
				}
				else
				{
					g_aBoss[nCntBoss].nCntBullet++;
					
				}
				

				if(g_aBoss[nCntBoss].nNumNoMoveTime <= 0)
				{
					if(g_aBoss[nCntBoss].bMoveFlag == true)
					{
						g_aBoss[nCntBoss].fPos.x -= BOSS_SPEED_SLOW;
					}
				} // EO if
				else
				{
					g_aBoss[nCntBoss].nNumNoMoveTime--;
				}

				// 核の座標セット
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[0] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_ONE + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[1] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_TWO + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[2] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_THREE + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[3] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_FOUR + LINE_HEIGHT * 0.5f));

				// ボスをこれ以上行かせない
				if(g_aBoss[nCntBoss].fPos.x <= BOSS_CAN_COME_3)
				{
					g_aBoss[nCntBoss].fPos.x = BOSS_CAN_COME_3;
				}
				break;
			} // EO switch
			//////////////////////////////////////////////////

			////////////////////
			// 壁来たら消える //
			//////////////////////////////////////////////////
			if(g_aBoss[nCntBoss].fPos.x + g_aBoss[nCntBoss].fWidth <= 0)
			{
				// ライフ0により消滅
				g_aBoss[nCntBoss].bUse = false;

				AddDamegeCastle(300);

			} // EO if
			//////////////////////////////////////////////////

			////////////////////////
			// 非攻撃タイムの消化 //
			//////////////////////////////////////////////////
			if(g_aBoss[nCntBoss].bAttack == true)
			{
				// ライフ0により消滅
				g_aBoss[nCntBoss].nCntDamegeTime++;

				if(g_aBoss[nCntBoss].nCntDamegeTime >= 120 )
				{
					g_aBoss[nCntBoss].bAttack = false;
					g_aBoss[nCntBoss].nCntDamegeTime = 0;
				} // EO if
			} // EO if
			//////////////////////////////////////////////////

			//////////////////////////
			// 体力なくなったら爆発 //
			//////////////////////////////////////////////////
			if(g_aBoss[nCntBoss].nLife <= 0)
			{
				// ライフ0により消滅
				g_aBoss[nCntBoss].bUse = false;

			} // EO if
			//////////////////////////////////////////////////

			// 体力
			SetPosHeart(g_aBoss[nCntBoss].nNumHeart , D3DXVECTOR2(g_aBoss[nCntBoss].fPos.x - 100 , g_aBoss[nCntBoss].fPos.y));
			SetUVSizeHeart(g_aBoss[nCntBoss].nNumHeart , g_aBoss[nCntBoss].nLife);

			// 体力によって赤くなる
			float x = (float)g_aBoss[nCntBoss].nLife / (float)BOSS_HP;
			pVtx[0 + 4 * nCntBoss].color = D3DXCOLOR(1.0f , 1.0f * x , 1.0f * x , 1.0f);
			pVtx[1 + 4 * nCntBoss].color = D3DXCOLOR(1.0f , 1.0f * x , 1.0f * x , 1.0f);
			pVtx[2 + 4 * nCntBoss].color = D3DXCOLOR(1.0f , 1.0f * x , 1.0f * x , 1.0f);
			pVtx[3 + 4 * nCntBoss].color = D3DXCOLOR(1.0f , 1.0f * x , 1.0f * x , 1.0f);

		} // EO if
	} // EO for

	g_pVtxBufferBoss->Unlock ();												//ロック解除

}//EOUpdateBoss

//============================================
//
//  名前  DrawBoss関数
//  引数	void
//  戻り値  void
//  説明  Boss関係の描画処理
//
//============================================
void DrawBoss(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//パイプラインの設定
	pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
						g_pVtxBufferBoss ,//データのある場所(先頭アドレス)
						0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
						sizeof(VERTEX2D) );//ストライド量(一個の単位の大きさ)

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// 最大数チェック
	for(int nCntBoss = 0 ; nCntBoss < MAX_BOSS ; nCntBoss++)
	{
		if(g_aBoss[nCntBoss].bUse == true)
		{
			if(g_aBoss[nCntBoss].bDrawFlag == true)
			{
				// 種類で分ける
				switch(g_aBoss[nCntBoss].nMode)
				{
				case BOSS_ONE:

					//Bossの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureBoss[0] );

					break;
				case BOSS_TWO:

					//Bossの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureBoss[1] );

					break;
				case BOSS_THREE:

					//Bossの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureBoss[2] );

					break;
				} // EO switch

				//プリミティブの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
					nCntBoss * 4 ,//オフセット(頂点数)何頂点目からとるか
					NUM_POLYGON );//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。
			} // EO if
			else
			{
				g_aBoss[nCntBoss].bDrawFlag = true;
			} // EO if
		} // EO if
	} // EO for
}//EODarwBoss

//============================================
//
//  名前  MakeVertexBoss関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexBoss(LPDIRECT3DDEVICE9 pDevice)
{

	//頂点バッファ作成
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_BOSS,//作成したい頂点バッファのサイズ = 1つの頂点のサイズ * 頂点数
																	//どれくらいメモリほしいか、ここをめっちゃふやすんでーーー
			D3DUSAGE_WRITEONLY,									//頂点バッファの使用方法、書き込み専用なので、恐らく最速
			FVF_VERTEX_2D,										//NULLや0でも大丈夫、マナー的には書こうよ。このバッファの頂点フォーマットを問う
			D3DPOOL_MANAGED,									//メモリ管理どうする設定、この状態はデバイスにお任せ
			&g_pVtxBufferBoss,						//出来上がった頂点バッファを管理するアドレス
			NULL)												//謎だけれどNULL
	))
	{
		return E_FAIL;
	}


	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferBoss -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

		// 最大数回す
	for(int nCntBoss = 0 ; nCntBoss < MAX_BOSS ; nCntBoss++)
	{
		//rhwの設定(必ず1.0fを入れる!!!!!!!!)
		pVtx[0 + 4 * nCntBoss].rhw = 1.0f;
		pVtx[1 + 4 * nCntBoss].rhw = 1.0f;
		pVtx[2 + 4 * nCntBoss].rhw = 1.0f;
		pVtx[3 + 4 * nCntBoss].rhw = 1.0f;

		//頂点カラー(0～255の整数値)
		pVtx[0 + 4 * nCntBoss].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntBoss].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntBoss].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntBoss].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//鍵をアンロック
	g_pVtxBufferBoss -> Unlock();

	return S_OK;

}//EOMakeVertexBoss

//============================================
//
//  名前  SetBoss関数
//  引数	void
//  戻り値  float fPosX ,float fPosY,float fWidth,float fHeught,Boss_MODE nMode
//  説明  ボスをセット
//
//============================================
void    SetBoss    (float fPosX , // 中心座標X
float fPosY ,
BOSS_MODE nMode			   // 種類
	)
{
	for(int nCntBoss = 0 ; nCntBoss < MAX_BOSS ; nCntBoss++)
	{
		if(g_aBoss[nCntBoss].bUse == false)
		{
			g_aBoss[nCntBoss].bUse = true;
			g_aBoss[nCntBoss].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aBoss[nCntBoss].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aBoss[nCntBoss].fSizeUV = D3DXVECTOR2(1.0f , 1.0f);
			g_aBoss[nCntBoss].fFlame = 0;
			g_aBoss[nCntBoss].nMode = nMode;
			g_aBoss[nCntBoss].bMoveFlag = true;
			g_aBoss[nCntBoss].nLife = BOSS_HP;
			g_aBoss[nCntBoss].nNumHeart = -1;
			switch(nMode)
			{
			case BOSS_ONE:
				g_aBoss[nCntBoss].nNumNucleus[0] = SetNucleusBoss(fPosX , LINE_ONE , 100 , 100 , BOSSNUCLEUS_ONE);
				g_aBoss[nCntBoss].nNumNucleus[1]= SetNucleusBoss(fPosX , LINE_TWO , 100 , 100 , BOSSNUCLEUS_ONE);
				g_aBoss[nCntBoss].nNumNucleus[2] = SetNucleusBoss(fPosX , LINE_THREE , 100 , 100 , BOSSNUCLEUS_ONE);
				g_aBoss[nCntBoss].nNumNucleus[3] = SetNucleusBoss(fPosX , LINE_FOUR , 100 , 100 , BOSSNUCLEUS_ONE);

				// 幅高さ
				g_aBoss[nCntBoss].fWidth =  BOSS_WIDTH_1;
				g_aBoss[nCntBoss].fHeight = BOSS_HEIGHT_1;
				break;
			case BOSS_TWO:
				g_aBoss[nCntBoss].nNumNucleus[0] = SetNucleusBoss(fPosX , LINE_TWO , 100 , 100 , BOSSNUCLEUS_TWO);
				g_aBoss[nCntBoss].fWidth =  BOSS_WIDTH_2;
				g_aBoss[nCntBoss].fHeight = BOSS_HEIGHT_2;
				break;
			case BOSS_THREE:
				g_aBoss[nCntBoss].nNumNucleus[0] = SetNucleusBoss(fPosX , LINE_TWO , 100 , 100 , BOSSNUCLEUS_THREE);
				g_aBoss[nCntBoss].fWidth =  BOSS_WIDTH_3;
				g_aBoss[nCntBoss].fHeight = BOSS_HEIGHT_3;
				break;
			} // EO switch
			break;
		} // EO if
	} // EO for
} // EO SetBoss

//============================================
//
//  名前  GetBoss関数
//  引数	void
//  戻り値  BOSS *g_aBoss[0]
//  説明  g_aBossの先頭アドレスを渡す
//
//============================================
BOSS* GetBoss()
{
	return &g_aBoss[0];
} // EO GetBoss

void    AddDameageBoss(int nID , int nDamege)
{
	if(g_aBoss[nID].bUse == true)
	{
		g_aBoss[nID].nLife -= nDamege;
		if(g_aBoss[nID].nLife <= 0)
		{
			PlaySound(SE_GAME_ENEMY_KILL_SURAIMU);
			ReleaseNucleusBoss(g_aBoss[nID].nNumNucleus[0]);
			ReleaseNucleusBoss(g_aBoss[nID].nNumNucleus[1]);
			ReleaseNucleusBoss(g_aBoss[nID].nNumNucleus[2]);
			ReleaseNucleusBoss(g_aBoss[nID].nNumNucleus[3]);
			setGameState(VICTORY);

			g_aBoss[nID].bUse = false;
		} // EO if
	} // EO if
} // EO AddDameage

