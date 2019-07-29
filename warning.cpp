//============================================
//  Warning関係  (Warning.c)
//
//  Author  Information
//  クラス  AT12D249
//  出席番号  1番
//  名前  石井  雄大
//  作成日   2016年6月29日
//  修正日   年月日
//
//============================================

//============================================
//
//  インクルードファイル
//
//============================================
#include "main.h"
#include "warning.h"
#include "player.h"
#include "notes.h"

//============================================
//
//  変数定義
//
//============================================
/*背景関係*/
#define WARNING_FILE_NAME   "data/TEXTURE/GAME/UI/warn.png"          //バックグラウンドのファイル名
#define WARNING_FILE_NAME1  "data/TEXTURE/GAME/UI/warning.png"          //バックグラウンドのファイル名
#define WARNING_NUM         (20)                 // ワーニングの数
#define WARNING_X           (0.0f)            //ワーニング1枚目のX座標
#define WARNING_Y           (90.0f)             //ワーニング1枚目のY座標
#define WARNING_WIDTH       (100)             //ワーニング1枚の幅
#define WARNING_HEIGHT      (LINE_HEIGHT- 20.0f)             //ワーニング1枚の高さ
#define WARNING_MAX_FLAME   (45.0f)               // ワーニングが点滅する間隔
#define WARNING_SUB         (1.0f / WARNING_MAX_FLAME) // 透明になる間隔

#define WARNING_ANIM_COUNT 3

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexWarning(LPDIRECT3DDEVICE9 pDevice);			// 頂点作成

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureWarning[2] = {};//BGの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferWarning = NULL;//ポインター!!&初期化

WARNING		  g_aWarning[WARNING_NUM];		  // 表示ワーニング構造体

//============================================
//
//  名前  InitWarning関数
//  引数   void
//  戻り値 void
//  説明 ワーニング関係の初期化処理
//
//============================================
HRESULT InitWarning()
{
	int nCnt = 0;

	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	
	//テクスチャ取得
	//エラーチェック必須
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , WARNING_FILE_NAME , &g_pTextureWarning[0] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "ワーニングテクスチャが取得できませんでした。","ひゃっほ～い",MB_OK | MB_DEFBUTTON1);
		}//EOif
	//エラーチェック必須
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , WARNING_FILE_NAME1 , &g_pTextureWarning[1] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "ワーニングテクスチャが取得できませんでした。","ひゃっほ～い",MB_OK | MB_DEFBUTTON1);
		}//EOif
	
	// 表示ワーニング構造体の初期化
	for(nCnt = 0; nCnt < WARNING_NUM;nCnt++)
	{
		g_aWarning[nCnt].bUse = false;
		g_aWarning[nCnt].fPos.x = WARNING_X;
		g_aWarning[nCnt].fPos.y = WARNING_Y;
		g_aWarning[nCnt].bFlash = false;
		g_aWarning[nCnt].fAlpha = 0.0f;
		g_aWarning[nCnt].nCntflash = 0;
		g_aWarning[nCnt].nMaxFlash = WARNING_MAX_FLAME;

	} // EO for

	//頂点作成
	if(FAILED(MakeVertexWarning(pDevice)))
	{
		return E_FAIL;
	}//EOif

	return S_OK;
}//EOInitWarning

//============================================
//
//  名前  UnitnitWarning関数
//  引数   void
//  戻り値 void
//  説明 ワーニング関係の終了処理
//
//============================================
void UninitWarning()
{
	// テクスチャインターフェイス
	SAFE_RELEASE(g_pTextureWarning[0]);
	SAFE_RELEASE(g_pTextureWarning[1]);

	// 頂点バッファ管理インターフェイス
	if (g_pVtxBufferWarning != NULL)
	{
		g_pVtxBufferWarning->Release();			// 頂点バッファ管理インターフェイスの解放
		g_pVtxBufferWarning = NULL;				// アドレスをNULLにする
	}
}//EOUninitWarning

//============================================
//
//  名前  UpdataWarning関数
//  引数   void
//  戻り値 void
//  説明 ワーニング関係の更新処理
//
//============================================
void UpdateWarning()
{
	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferWarning -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

		// 最大数回す
	for(int nCntNotes = 0 ; nCntNotes < WARNING_NUM ; nCntNotes++)
	{
		if(g_aWarning[nCntNotes].bUse == true)
		{
			switch(g_aWarning[nCntNotes].type)
			{
			case WARNING_NORMAL:
				{
					g_aWarning[nCntNotes].fAlpha -= 0.005f;
					if(g_aWarning[nCntNotes].fAlpha >= 1.0f)
					{
						g_aWarning[nCntNotes].bUse = false;
					}
					//頂点カラー(0～255の整数値)
					pVtx[0 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[1 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[2 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[3 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);

					pVtx [ 0 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x , g_aWarning[nCntNotes].fPos.y , 0.0f);
					pVtx [ 1 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x + WARNING_WIDTH ,g_aWarning[nCntNotes].fPos.y , 0.0f);
					pVtx [ 2 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x , g_aWarning[nCntNotes].fPos.y + WARNING_HEIGHT , 0.0f);
					pVtx [ 3 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x + WARNING_WIDTH , g_aWarning[nCntNotes].fPos.y +WARNING_HEIGHT , 0.0f);
				}
				break;
			case WARNING_BOSS:
				{

					if(g_aWarning[nCntNotes].bFlash == false)
					{

						g_aWarning[nCntNotes].fAlpha -= 0.05f;
						if(g_aWarning[nCntNotes].fAlpha <= 0.0f)
						{
							g_aWarning[nCntNotes].nCntflash++;
								if(g_aWarning[nCntNotes].nCntflash >= WARNING_ANIM_COUNT)
							{
								g_aWarning[nCntNotes].bUse = false;
							}
							g_aWarning[nCntNotes].bFlash = true;
						} // EO if
					} // EO if
					else
					{
						g_aWarning[nCntNotes].fAlpha += 0.05f;
						if(g_aWarning[nCntNotes].fAlpha >= 1.0f)
						{
							g_aWarning[nCntNotes].bFlash = false;
						} // EO if
					}
					//頂点カラー(0～255の整数値)
					pVtx[0 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[1 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[2 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[3 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);

					pVtx [ 0 + 4*nCntNotes] . pos = D3DXVECTOR3 (0.0f , 0.0f , 0.0f);
					pVtx [ 1 + 4*nCntNotes] . pos = D3DXVECTOR3 (SCREEN_WIDTH,0.0f, 0.0f);
					pVtx [ 2 + 4*nCntNotes] . pos = D3DXVECTOR3 (0.0f ,SCREEN_HEIGHT, 0.0f);
					pVtx [ 3 + 4*nCntNotes] . pos = D3DXVECTOR3 (SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
				}
				break;
			}

		} // EO if
	} // EO for

	//鍵をアンロック
	g_pVtxBufferWarning -> Unlock();
}//EOUpdateWarning

//============================================
//
//  名前  DrawWarning関数
//  引数   void
//  戻り値 void
//  説明  ワーニング関係の描画処理
//
//============================================
void DrawWarning()
{
	/*変数宣言*/
	int i = 0;

	//テクスチャ設定
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// プリミティブの設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBufferWarning,
		0,								// オフセット(単位バイト)
		sizeof(VERTEX2D));				// ストライド量。頂点データ1個分のサイズ

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	// 描画
	for (int i  = 0; i < WARNING_NUM; i++)
	{
		// 使用フラグがONなら描画
		if (g_aWarning[i].bUse == true)
		{
			// テクスチャの設定
			switch(g_aWarning[i].type)
			{
			case WARNING_NORMAL:
				{
					pDevice->SetTexture(0, g_pTextureWarning[0]);
				}
				break;
			case WARNING_BOSS:
				{
					pDevice->SetTexture(0, g_pTextureWarning[1]);
				}
				break;
			}

			// プリミティブの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				i * 4,				// オフセット(頂点数)
				NUM_POLYGON);					// プリミティブ数
		}
	}
}//EODrawWarning

//============================================
//
//  名前  MakeVertexWarning関数
//  引数
//  戻り値
//  説明
//
//============================================
HRESULT MakeVertexWarning(LPDIRECT3DDEVICE9 pDevice)
{
	//頂点バッファ作成
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * WARNING_NUM,//作成したい頂点バッファのサイズ = 1つの頂点のサイズ * 頂点数
																	//どれくらいメモリほしいか、ここをめっちゃふやすんでーーー
			D3DUSAGE_WRITEONLY,									//頂点バッファの使用方法、書き込み専用なので、恐らく最速
			FVF_VERTEX_2D,										//NULLや0でも大丈夫、マナー的には書こうよ。このバッファの頂点フォーマットを問う
			D3DPOOL_MANAGED,									//メモリ管理どうする設定、この状態はデバイスにお任せ
			&g_pVtxBufferWarning,						//出来上がった頂点バッファを管理するアドレス
			NULL)												//謎だけれどNULL
	))
	{
		return E_FAIL;
	}


	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferWarning -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

		// 最大数回す
	for(int nCntNotes = 0 ; nCntNotes < WARNING_NUM ; nCntNotes++)
	{
		
		//頂点座標の設定(2D座標 , 右回り )
		pVtx [ 0 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x , g_aWarning[nCntNotes].fPos.y , 0.0f);
		pVtx [ 1 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x + WARNING_WIDTH ,g_aWarning[nCntNotes].fPos.y , 0.0f);
		pVtx [ 2 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x , g_aWarning[nCntNotes].fPos.y + WARNING_HEIGHT , 0.0f);
		pVtx [ 3 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x + WARNING_WIDTH , g_aWarning[nCntNotes].fPos.y +WARNING_HEIGHT , 0.0f);

	    //各頂点のテクスチャ座標の設定
		pVtx [ 0 + 4*nCntNotes] . tex = D3DXVECTOR2 (0 , 0);
		pVtx [ 1 + 4*nCntNotes] . tex = D3DXVECTOR2 (1 , 0);
		pVtx [ 2 + 4*nCntNotes] . tex = D3DXVECTOR2 (0 , 1);
		pVtx [ 3 + 4*nCntNotes] . tex = D3DXVECTOR2 (1 , 1);

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
	g_pVtxBufferWarning -> Unlock();

	return S_OK;
}

//============================================
//
//  名前  SetWarning関数
//  引数   void
//  戻り値 void
//  説明  ワーニングのセット
//
//============================================
int SetWarning (float fPosY  , WARNING_TYPE type)
{
	for(int nCnt = 0 ; WARNING_NUM ; nCnt++)
	{
		if(g_aWarning[nCnt].bUse == false)
		{
			g_aWarning[nCnt].bFlash = true;
			g_aWarning[nCnt].fAlpha = 1.0f;
			g_aWarning[nCnt].fPos = D3DXVECTOR2(0.0f , fPosY);
			g_aWarning[nCnt].nCntflash = 0;
			g_aWarning[nCnt].nMaxFlash = WARNING_MAX_FLAME;
			g_aWarning[nCnt].bUse = true;
			g_aWarning[nCnt].type = type;
			switch(type)
			{
			case WARNING_NORMAL:
				{
					float x = SCREEN_WIDTH / 100.0f * 90;
					g_aWarning[nCnt].fPos.x = x;
				}
				break;
			case WARNING_BOSS:
				{
					g_aWarning[nCnt].fPos.x = 0.0f;
				}
				break;
			}
			return nCnt;
		} // EO if
	} // EO for

	return -1;
}//EOSetWarning

//============================================
//
//  名前  OffWarning関数
//  引数   int nIndex
//  戻り値 void
//  説明 ワーニングのインデックス指定終了
//
//============================================
void OffWarning(int nIndex)
{
	if(g_aWarning[nIndex].bUse == true && nIndex != -1)
	{
		g_aWarning[nIndex].bUse = false;
	} // EO if
}//EOUninitWarning
