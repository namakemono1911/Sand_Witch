//============================================
//  NucleusBoss関数  (NucleusBoss.cpp)
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
#include "nucleusBoss.h"

//============================================
//
//  定数宣言
//
//============================================
#define BOSSNUCLEUS_NUM_SIDE        (1.0f)							// 画像1枚の横の数
#define BOSSNUCLEUS_NUM_VERTICAL	(1)								// 画像1枚の縦の数
#define BOSSNUCLEUS_WIDTH           ( 1.0f / BOSSNUCLEUS_NUM_SIDE )	// 1Uの幅
#define BOSSNUCLEUS_HEIGHT          (1.0f)							// 1Vの高さ
#define BOSSNUCLEUS_NUM_SPEED       (0.0f)							// 移動速度
#define BOSSNUCLEUS_LIFE            (30)							// 一かいの表示フレーム数
#define BOSSNUCLEUS_ANIME           (6)								// 一かい

#//読み込むテクスチャファイル名
#define BOSSNUCLEUS_TEXTURENAME_ONE      "data/TEXTURE/GAME/NUCLEUS/BossNuc01.png"
#define BOSSNUCLEUS_TEXTURENAME_TWO      "data/TEXTURE/GAME/NUCLEUS/BossNuc02.png"
#define BOSSNUCLEUS_TEXTURENAME_THREE    "data/TEXTURE/GAME/NUCLEUS/BossNuc03.png"

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureNucleusBoss[BOSSNUCLEUS_MAX] = {};//NucleusBossの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferNucleusBoss[MAX_BOSSNUCLEUS] = {};//ポインター!!&初期化

/*ボスの弾構造体*/
BOSSNUCLEUS g_aNucleusBoss[MAX_BOSSNUCLEUS];

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexNucleusBoss(LPDIRECT3DDEVICE9 pDevice);//頂点の作成

//============================================
//
//  名前  InitNucleusBoss関数
//  引数	void
//  戻り値  void
//  説明  NucleusBoss関係の初期化
//
//============================================
HRESULT InitNucleusBoss(void)
{
	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//頂点作成
	if(FAILED(MakeVertexNucleusBoss(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//テクスチャ取得
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSNUCLEUS_TEXTURENAME_ONE , &g_pTextureNucleusBoss[0] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSSNUCLEUS",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSNUCLEUS_TEXTURENAME_TWO , &g_pTextureNucleusBoss[1] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSSNUCLEUS",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSNUCLEUS_TEXTURENAME_THREE , &g_pTextureNucleusBoss[2] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","BOSSNUCLEUS",MB_OK | MB_DEFBUTTON1);
		}//EOif


	// ボスの弾構造体の初期化
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		g_aNucleusBoss[nCntEx].bUse = false;
		g_aNucleusBoss[nCntEx].bDraw = false;
		g_aNucleusBoss[nCntEx].fHeight = 0.0f;
		g_aNucleusBoss[nCntEx].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aNucleusBoss[nCntEx].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aNucleusBoss[nCntEx].fHeight = 0.0f;
		g_aNucleusBoss[nCntEx].fWidth = 0.0f;
		g_aNucleusBoss[nCntEx].nFlame = 0;
		g_aNucleusBoss[nCntEx].nLife = BOSSNUCLEUS_LIFE;
		g_aNucleusBoss[nCntEx].nType = BOSSNUCLEUS_NONE;
	} // EO for
	return S_OK;
}//EOInitPolygin

//============================================
//
//  名前  UninitNucleusBoss関数
//  引数	void
//  戻り値  void
//  説明  NucleusBoss関係の終了処理
//
//============================================
void UninitNucleusBoss(void)
{
	//テクスチャインターフェースの後片付け
	for(int i = 0 ; i < 2 ; i++)
	{
		SAFE_RELEASE( g_pTextureNucleusBoss[i] );
	} // EO for

	for(int nCntExp = 0 ; nCntExp < MAX_BOSSNUCLEUS ; nCntExp++)
	{
		//頂点バッファの後片付け
		SAFE_RELEASE( g_pVtxBufferNucleusBoss[nCntExp] );
	} // EO for
}//EOUninitNucleusBoss

//============================================
//
//  名前  UpdateNucleusBoss関数
//  引数	void
//  戻り値  void
//  説明  NucleusBoss関係の更新処理
//
//============================================
void UpdateNucleusBoss(void)
{
	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo

	// UVアニメーションでボスの弾
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		// 使用チェック
		if(g_aNucleusBoss[nCntEx].bUse == true)
		{
			if(g_aNucleusBoss[nCntEx].nDrawTime > 0)
			{
				g_aNucleusBoss[nCntEx].nDrawTime--;
				if(g_aNucleusBoss[nCntEx].nDrawTime <= 0)
				{
					OffDrawNucleusBoss(nCntEx);
				} // EO if
			} // EO if

			// 座標の保存
			g_pVtxBufferNucleusBoss[ nCntEx ]->Lock ( 0 , 0 , (void**)&pVtx , 0);				//ロック

			//頂点座標の設定(2D座標 , 右回り )
			pVtx [ 0 ] . pos = D3DXVECTOR3 (g_aNucleusBoss[nCntEx].fPos.x - g_aNucleusBoss[nCntEx].fWidth / 2 ,
				g_aNucleusBoss[nCntEx].fPos.y - g_aNucleusBoss[nCntEx].fHeight / 2 , 0.0f);
			pVtx [ 1 ] . pos = D3DXVECTOR3 (g_aNucleusBoss[nCntEx].fPos.x + g_aNucleusBoss[nCntEx].fWidth / 2 ,
				g_aNucleusBoss[nCntEx].fPos.y - g_aNucleusBoss[nCntEx].fHeight / 2, 0.0f);
			pVtx [ 2 ] . pos = D3DXVECTOR3 (g_aNucleusBoss[nCntEx].fPos.x - g_aNucleusBoss[nCntEx].fWidth / 2 ,
				g_aNucleusBoss[nCntEx].fPos.y + g_aNucleusBoss[nCntEx].fHeight / 2, 0.0f);
			pVtx [ 3 ] . pos = D3DXVECTOR3 (g_aNucleusBoss[nCntEx].fPos.x + g_aNucleusBoss[nCntEx].fWidth / 2 ,
				g_aNucleusBoss[nCntEx].fPos.y + g_aNucleusBoss[nCntEx].fHeight / 2, 0.0f);

			//各頂点のテクスチャ座標の設定
			pVtx [ 0 ] . tex = D3DXVECTOR2 (g_aNucleusBoss[nCntEx].fUV.x , g_aNucleusBoss[nCntEx].fUV.y);
			pVtx [ 1 ] . tex = D3DXVECTOR2 (g_aNucleusBoss[nCntEx].fUV.x  +BOSSNUCLEUS_WIDTH, g_aNucleusBoss[nCntEx].fUV.y);
			pVtx [ 2 ] . tex = D3DXVECTOR2 (g_aNucleusBoss[nCntEx].fUV.x , g_aNucleusBoss[nCntEx].fUV.y + BOSSNUCLEUS_HEIGHT);
			pVtx [ 3 ] . tex = D3DXVECTOR2 (g_aNucleusBoss[nCntEx].fUV.x + BOSSNUCLEUS_WIDTH, g_aNucleusBoss[nCntEx].fUV.y+ BOSSNUCLEUS_HEIGHT);

			g_pVtxBufferNucleusBoss[ nCntEx ]->Unlock ();												//ロック解除

		} // EO if
	} // EO for
}//EOUpdateNucleusBoss

//============================================
//
//  名前  DrawNucleusBoss関数
//  引数	void
//  戻り値  void
//  説明  NucleusBoss関係の描画処理
//
//============================================
void DrawNucleusBoss(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// 最大数チェック
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		if(g_aNucleusBoss[nCntEx].bUse == true && g_aNucleusBoss[nCntEx].bDraw == true )
		{
			//パイプラインの設定
			pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
								g_pVtxBufferNucleusBoss[nCntEx] ,//データのある場所(先頭アドレス)
								0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
								sizeof(VERTEX2D));//ストライド量(一個の単位の大きさ)


			//頂点フォーマットの設定
			pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

			switch(g_aNucleusBoss[nCntEx].nType)
			{
			case BOSSNUCLEUS_ONE:
				pDevice -> SetTexture( 0 , g_pTextureNucleusBoss[0] );
				break;
			case BOSSNUCLEUS_TWO:
				pDevice -> SetTexture( 0 , g_pTextureNucleusBoss[1] );
				break;
			case BOSSNUCLEUS_THREE:
				pDevice -> SetTexture( 0 , g_pTextureNucleusBoss[2] );
				break;
			} // EO switch
			//プリミティブの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				0,//オフセット(頂点数)何頂点目からとるか
				NUM_POLYGON);//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。

		} // EO if
	} // EO for
}//EODarwNucleusBoss

//============================================
//
//  名前  MakeVertexNucleusBoss関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexNucleusBoss(LPDIRECT3DDEVICE9 pDevice)
{
	// 最大数回す
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		//頂点バッファ作成
		if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX,//作成したい頂点バッファのサイズ = 1つの頂点のサイズ * 頂点数
																	 //どれくらいメモリほしいか、ここをめっちゃふやすんでーーー
				D3DUSAGE_WRITEONLY,									//頂点バッファの使用方法、書き込み専用なので、恐らく最速
				FVF_VERTEX_2D,										//NULLや0でも大丈夫、マナー的には書こうよ。このバッファの頂点フォーマットを問う
				D3DPOOL_MANAGED,									//メモリ管理どうする設定、この状態はデバイスにお任せ
				&g_pVtxBufferNucleusBoss[nCntEx],						//出来上がった頂点バッファを管理するアドレス
				NULL)												//謎だけれどNULL
		))
		{
			return E_FAIL;
		}

		//頂点バッファ
		VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
		//頂点バッファをロックして、仮想アドレスを取得する
		g_pVtxBufferNucleusBoss[nCntEx] -> Lock(0,	//どこからロックするか
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
		g_pVtxBufferNucleusBoss[nCntEx] -> Unlock();
	} // EO for
	return S_OK;

}//EOMakeVertexNucleusBoss

//============================================
//
//  名前  SetNucleusBoss関数
//  引数	void
//  戻り値  float fPosX ,float fPosY,float fWidth,float fHeught,EXPLOSION_MODE nMode
//  説明  ボスの弾をセット
//
//============================================
int    SetNucleusBoss    (float fPosX , // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,				   // 高さ
	BOSSNUCLEUS_TYPE nType
	)
{
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		if(g_aNucleusBoss[nCntEx].bUse == false)
		{
			g_aNucleusBoss[nCntEx].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aNucleusBoss[nCntEx].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aNucleusBoss[nCntEx].fWidth = fWidth;
			g_aNucleusBoss[nCntEx].fHeight = fHeught;
			g_aNucleusBoss[nCntEx].nFlame = 0;
			g_aNucleusBoss[nCntEx].bUse = true;
			g_aNucleusBoss[nCntEx].nLife = BOSSNUCLEUS_LIFE;
			g_aNucleusBoss[nCntEx].nType = nType;
			return nCntEx;
		} // EO if
	} // EO for

	return -1;
} // EO SetNucleusBoss

//============================================
//
//  名前  MakeVertexNucleusBoss関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
BOSSNUCLEUS* GetNucleusBoss(void)
{
	return &g_aNucleusBoss[0];
} // EO GetNucleusBoss

void AddDmgNucBoss(int damage, int num)
{
	g_aNucleusBoss[num].nLife -= damage;
}

void SetPosNucleusBoss(int nIndex , D3DXVECTOR2 fPos)
{
	if(g_aNucleusBoss[nIndex].bUse == false)
	{
		return;
	} // EO if
	
	g_aNucleusBoss[nIndex].fPos = fPos;
} // EO SetPosNucleusBoss

void OffDrawNucleusBoss(int nIndex)
{
	if(g_aNucleusBoss[nIndex].bUse == false)
	{
		return;
	} // EO if

	g_aNucleusBoss[nIndex].bDraw = false;
} // EO OffDrawNucleusBoss


void OnDrawNucleusBoss(int nIndex , int nTime)
{
	if(g_aNucleusBoss[nIndex].bUse == false)
	{
		return;
	} // EO if
		g_aNucleusBoss[nIndex].bDraw = true;
		g_aNucleusBoss[nIndex].nDrawTime = nTime;
} // EO 

void ReleaseNucleusBoss(int nIdx)
{
	g_aNucleusBoss[nIdx].bUse = false;
}

void OffNucleusBoss(int nIndex)
{
	g_aNucleusBoss[nIndex].bUse = false;
} // EO OffDrawNucleusBoss
