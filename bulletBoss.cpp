//============================================
//  BulletBoss関数  (BulletBoss.cpp)
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
#include "sound.h"
#include "bulletBoss.h"
#include "gate.h"

//============================================
//
//  定数宣言
//
//============================================
#define BOSSBULLET_NUM_SIDE                  (10.0f)                  // 画像1枚の横の数
#define BOSSBULLET_NUM_VERTICAL              (1)                   // 画像1枚の縦の数
#define BOSSBULLET_WIDTH           ( 1.0f / BOSSBULLET_NUM_SIDE )        // 1Uの幅
#define BOSSBULLET_HEIGHT          (1.0f)    // 1Vの高さ
#define BOSSBULLET_NUM_SPEED                 (5.5f)                  // 移動速度
#define BOSSBULLET_LIFE                      (1) // 一かいの表示フレーム数
#define BOSSBULLET_ANIME                     (6) // 一かい

#define BOSSBULLET_ATTACK                    (10) // 攻撃力
#//読み込むテクスチャファイル名
#define BOSSBULLET_TEXTURENAME_ONE      "data/TEXTURE/GAME/BULLET/BossBullet01.png"
#define BOSSBULLET_TEXTURENAME_TWO      "data/TEXTURE/GAME/BULLET/BossBullet02.png"
#define BOSSBULLET_TEXTURENAME_THREE    "data/TEXTURE/GAME/BULLET/BossBullet03.png"

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureBulletBoss[BOSSBULLET_MAX] = {};//BulletBossの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBulletBoss[MAX_BOSSBULLET] = {};//ポインター!!&初期化

/*ボスの弾構造体*/
BOSSBULLET g_aBulletBoss[MAX_BOSSBULLET];

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexBulletBoss(LPDIRECT3DDEVICE9 pDevice);//頂点の作成

//============================================
//
//  名前  InitBulletBoss関数
//  引数	void
//  戻り値  void
//  説明  BulletBoss関係の初期化
//
//============================================
HRESULT InitBulletBoss(void)
{
	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//頂点作成
	if(FAILED(MakeVertexBulletBoss(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//テクスチャ取得
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSBULLET_TEXTURENAME_ONE , &g_pTextureBulletBoss[0] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSSBULLET",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSBULLET_TEXTURENAME_TWO , &g_pTextureBulletBoss[1] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSSBULLET",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSBULLET_TEXTURENAME_THREE , &g_pTextureBulletBoss[2] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSSBULLET",MB_OK | MB_DEFBUTTON1);
		}//EOif


	// ボスの弾構造体の初期化
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		g_aBulletBoss[nCntEx].bUse = false;
		g_aBulletBoss[nCntEx].fHeight = 0.0f;
		g_aBulletBoss[nCntEx].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aBulletBoss[nCntEx].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aBulletBoss[nCntEx].fHeight = 0.0f;
		g_aBulletBoss[nCntEx].fWidth = 0.0f;
		g_aBulletBoss[nCntEx].nFlame = 0;
		g_aBulletBoss[nCntEx].nLife = BOSSBULLET_LIFE;
		g_aBulletBoss[nCntEx].nType = BOSSBULLET_NONE;
	} // EO for
	return S_OK;
}//EOInitPolygin

//============================================
//
//  名前  UninitBulletBoss関数
//  引数	void
//  戻り値  void
//  説明  BulletBoss関係の終了処理
//
//============================================
void UninitBulletBoss(void)
{
	//テクスチャインターフェースの後片付け
	for(int i = 0 ; i < 2 ; i++)
	{
		SAFE_RELEASE( g_pTextureBulletBoss[i] );
	} // EO for

	for(int nCntExp = 0 ; nCntExp < MAX_BOSSBULLET ; nCntExp++)
	{
		//頂点バッファの後片付け
		SAFE_RELEASE( g_pVtxBufferBulletBoss[nCntExp] );
	} // EO for
}//EOUninitBulletBoss

//============================================
//
//  名前  UpdateBulletBoss関数
//  引数	void
//  戻り値  void
//  説明  BulletBoss関係の更新処理
//
//============================================
void UpdateBulletBoss(void)
{
	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
	GATE* pGate = GetGate();

	// UVアニメーションでボスの弾
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		// 使用チェック
		if(g_aBulletBoss[nCntEx].bUse == true)
		{
			// 移動
			g_aBulletBoss[nCntEx].fPos.x -= 2.1f;

			// 門
			for(int i = 0 ; i < GATE_NUM ; i++)
			{
				if((pGate+i)->bUse == true && (pGate+i)->nHp > 0)
				{
					if((pGate+i)->fPos.x + (pGate+i)->fSize.x >= g_aBulletBoss[nCntEx].fPos.x - g_aBulletBoss[nCntEx].fWidth / 2 &&
						(pGate+i)->fPos.y <= g_aBulletBoss[nCntEx].fPos.y &&
						(pGate+i)->fPos.y + (pGate+i)->fSize.y>= g_aBulletBoss[nCntEx].fPos.y)
					{
						g_aBulletBoss[nCntEx].bUse = false;
						AddLife(i , -1 * BOSSBULLET_ATTACK);
					}
				}
			}
			// 座標の保存
			g_pVtxBufferBulletBoss[ nCntEx ]->Lock ( 0 , 0 , (void**)&pVtx , 0);				//ロック

			//頂点座標の設定(2D座標 , 右回り )
			pVtx [ 0 ] . pos = D3DXVECTOR3 (g_aBulletBoss[nCntEx].fPos.x - g_aBulletBoss[nCntEx].fWidth / 2 ,
				g_aBulletBoss[nCntEx].fPos.y - g_aBulletBoss[nCntEx].fHeight / 2 , 0.0f);
			pVtx [ 1 ] . pos = D3DXVECTOR3 (g_aBulletBoss[nCntEx].fPos.x + g_aBulletBoss[nCntEx].fWidth / 2 ,
				g_aBulletBoss[nCntEx].fPos.y - g_aBulletBoss[nCntEx].fHeight / 2, 0.0f);
			pVtx [ 2 ] . pos = D3DXVECTOR3 (g_aBulletBoss[nCntEx].fPos.x - g_aBulletBoss[nCntEx].fWidth / 2 ,
				g_aBulletBoss[nCntEx].fPos.y + g_aBulletBoss[nCntEx].fHeight / 2, 0.0f);
			pVtx [ 3 ] . pos = D3DXVECTOR3 (g_aBulletBoss[nCntEx].fPos.x + g_aBulletBoss[nCntEx].fWidth / 2 ,
				g_aBulletBoss[nCntEx].fPos.y + g_aBulletBoss[nCntEx].fHeight / 2, 0.0f);

			//各頂点のテクスチャ座標の設定
			pVtx [ 0 ] . tex = D3DXVECTOR2 (g_aBulletBoss[nCntEx].fUV.x , g_aBulletBoss[nCntEx].fUV.y);
			pVtx [ 1 ] . tex = D3DXVECTOR2 (g_aBulletBoss[nCntEx].fUV.x  +BOSSBULLET_WIDTH, g_aBulletBoss[nCntEx].fUV.y);
			pVtx [ 2 ] . tex = D3DXVECTOR2 (g_aBulletBoss[nCntEx].fUV.x , g_aBulletBoss[nCntEx].fUV.y + BOSSBULLET_HEIGHT);
			pVtx [ 3 ] . tex = D3DXVECTOR2 (g_aBulletBoss[nCntEx].fUV.x + BOSSBULLET_WIDTH, g_aBulletBoss[nCntEx].fUV.y+ BOSSBULLET_HEIGHT);

			g_pVtxBufferBulletBoss[ nCntEx ]->Unlock ();												//ロック解除

			g_aBulletBoss[nCntEx].fUV.x += BOSSBULLET_WIDTH;
		} // EO if
	} // EO for
}//EOUpdateBulletBoss

//============================================
//
//  名前  DrawBulletBoss関数
//  引数	void
//  戻り値  void
//  説明  BulletBoss関係の描画処理
//
//============================================
void DrawBulletBoss(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// 最大数チェック
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		if(g_aBulletBoss[nCntEx].bUse == true)
		{
			//パイプラインの設定
			pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
								g_pVtxBufferBulletBoss[nCntEx] ,//データのある場所(先頭アドレス)
								0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
								sizeof(VERTEX2D));//ストライド量(一個の単位の大きさ)


			//頂点フォーマットの設定
			pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

			switch(g_aBulletBoss[nCntEx].nType)
			{
			case BOSSBULLET_ONE:
				pDevice -> SetTexture( 0 , g_pTextureBulletBoss[0] );
				break;
			case BOSSBULLET_TWO:
				pDevice -> SetTexture( 0 , g_pTextureBulletBoss[1] );
				break;
			case BOSSBULLET_THREE:
				pDevice -> SetTexture( 0 , g_pTextureBulletBoss[2] );
				break;
			} // EO switch
			//プリミティブの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				0,//オフセット(頂点数)何頂点目からとるか
				NUM_POLYGON);//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。

		} // EO if
	} // EO for
}//EODarwBulletBoss

//============================================
//
//  名前  MakeVertexBulletBoss関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexBulletBoss(LPDIRECT3DDEVICE9 pDevice)
{
	// 最大数回す
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		//頂点バッファ作成
		if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX,//作成したい頂点バッファのサイズ = 1つの頂点のサイズ * 頂点数
																	 //どれくらいメモリほしいか、ここをめっちゃふやすんでーーー
				D3DUSAGE_WRITEONLY,									//頂点バッファの使用方法、書き込み専用なので、恐らく最速
				FVF_VERTEX_2D,										//NULLや0でも大丈夫、マナー的には書こうよ。このバッファの頂点フォーマットを問う
				D3DPOOL_MANAGED,									//メモリ管理どうする設定、この状態はデバイスにお任せ
				&g_pVtxBufferBulletBoss[nCntEx],						//出来上がった頂点バッファを管理するアドレス
				NULL)												//謎だけれどNULL
		))
		{
			return E_FAIL;
		}

		//頂点バッファ
		VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
		//頂点バッファをロックして、仮想アドレスを取得する
		g_pVtxBufferBulletBoss[nCntEx] -> Lock(0,	//どこからロックするか
									0,				//どこまでロックするか(0~0で全部ロック)
									(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
									0);				//四つ目調べると面白いかも。
		//頂点バッファ使用
		
		//rhwの設定(必ず1.0fを入れる!!!!!!!!)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー(0～255の整数値)
		pVtx[0].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

		//鍵をアンロック
		g_pVtxBufferBulletBoss[nCntEx] -> Unlock();
	} // EO for
	return S_OK;

}//EOMakeVertexBulletBoss

//============================================
//
//  名前  SetBulletBoss関数
//  引数	void
//  戻り値  float fPosX ,float fPosY,float fWidth,float fHeught,EXPLOSION_MODE nMode
//  説明  ボスの弾をセット
//
//============================================
void    SetBulletBoss    (float fPosX , // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,				   // 高さ
	BOSSBULLET_TYPE nType
	)
{
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		if(g_aBulletBoss[nCntEx].bUse == false)
		{
			g_aBulletBoss[nCntEx].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aBulletBoss[nCntEx].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aBulletBoss[nCntEx].fWidth = 200;
			g_aBulletBoss[nCntEx].fHeight = 100;
			g_aBulletBoss[nCntEx].nFlame = 0;
			g_aBulletBoss[nCntEx].bUse = true;
			g_aBulletBoss[nCntEx].nLife = BOSSBULLET_LIFE;
			g_aBulletBoss[nCntEx].nType = nType;
			break;
		} // EO if
	} // EO for
} // EO SetBulletBoss

//============================================
//
//  名前  MakeVertexBulletBoss関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
BOSSBULLET* GetBulletBoss(void)
{
	return &g_aBulletBoss[0];
} // EO GetBulletBoss

  //============================================
  //
  //  名前  AddDmgBulletBoss関数
  //  引数	numBullet	配列番号
  //		damage		ダメージ数
  //  戻り値  void
  //  説明  頂点の作成
  //
  //============================================
void AddDmgBulletBoss(int numBullet, int damage)
{
	g_aBulletBoss[numBullet].nLife -= damage;

	//ライフ0以下で削除
	if(g_aBulletBoss[numBullet].nLife <= 0)
		g_aBulletBoss[numBullet].bUse = false;
}
