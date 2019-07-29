//============================================
//  Human関数  (Human.cpp)
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
#include "human.h"
#include "player.h"
#include "stage.h"
#include "input.h"
#include "sound.h"

#include "castle.h"
#include "gate.h"
#include "fcoh.h"
#include "effect.h"

#include "notes.h"
//============================================
//
//  定数宣言
//
//============================================
#define HUMAN_UV_SPEED                (5)                  // 何フレームでUVアニメーションするか
#define HUMAN_U_WIDTH                 (0.5f)               // U幅
#define HUMAN_V_HEIGHT                (1.0f)               // V高さ
#define HUMAN_POINT_TYPE_ONE          (10)                 // 点数1
#define HUMAN_POINT_TYPE_TWO          (30)                 // 点数2
#define HUMAN_POINT_TYPE_THREE        (50)                 // 点数3
#define HUMAN_POINT_TYPE_FOUR         (80)                 // 点数4
#define HUMAN_POINT_TYPE_FIVE         (100)                // 点数5
#define HUMAN_POINT_TYPE_SIX          (200)                // 点数6
#define HUMAN_POINT_TYPE_SEVEN        (130)                // 点数7
#define HUMAN_SPEED_SLOW              (1.0f)               // 遅いスピード
#define HUMAN_SPEED_NORMAL            (5.0f)               // 普通スピード
#define HUMAN_SPEED_FAST              (20.0f)              // 速いスピード
#define HUMAN_NUM_TIMEPLASS           (10)                 // タイムが増加する敵の数
#define HUMAN_DIST_TIMEPLASS          (SCREEN_WIDTH / 5 * 2)   // タイムが増加する敵の位置

#//読み込むテクスチャファイル名
#define HUMAN_TWO_TEXTURENAME       "data/TEXTURE/GAME/HUMAN/Human01.png"   // NHUMAN_ONE
#define HUMAN_ONE_TEXTURENAME       "data/TEXTURE/GAME/HUMAN/Human02.png"   // NHUMAN_TWO

#define HUMAN_ANIM_TIME 15	// アニメーション間隔

#define HUMAN_TRANSPARENT 0.01f	//透明になる間隔

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureHuman[HUMAN_MAX] = {};//Humanの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferHuman = NULL;//ポインター!!&初期化

/*人構造体*/
HUMAN g_aHuman[MAX_HUMAN];
int g_nHumanTime; // 時間が戻る敵のカウント

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexHuman(LPDIRECT3DDEVICE9 pDevice);//頂点の作成

//============================================
//
//  名前  InitHuman関数
//  引数	void
//  戻り値  void
//  説明  Human関係の初期化
//
//============================================
HRESULT InitHuman(void)
{
	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//頂点作成
	if(FAILED(MakeVertexHuman(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//テクスチャ取得
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , HUMAN_ONE_TEXTURENAME , &g_pTextureHuman[0] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","HUMAN_ONE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , HUMAN_TWO_TEXTURENAME , &g_pTextureHuman[1] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","HUMAN_TWO",MB_OK | MB_DEFBUTTON1);
		}//EOif

	// 人構造体の初期化
	for(int nCntHuman = 0 ; nCntHuman < MAX_HUMAN ; nCntHuman++)
	{
		g_aHuman[nCntHuman].bUse = false;
		g_aHuman[nCntHuman].nMode = HUMAN_NONE;
		g_aHuman[nCntHuman].fHeight = 0.0f;
		g_aHuman[nCntHuman].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aHuman[nCntHuman].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aHuman[nCntHuman].fHeight = 0.0f;
		g_aHuman[nCntHuman].fWidth = 0.0f;
		g_aHuman[nCntHuman].fFlame = 0;
		g_aHuman[nCntHuman].nLife = 0;
		g_aHuman[nCntHuman].nCntAnim = 0;
		g_aHuman[nCntHuman].nNumWarning = 0;
		g_aHuman[nCntHuman].nCntDamegeTime = 0;
		g_aHuman[nCntHuman].bMoveFlag = true;

		g_aHuman[nCntHuman].bAlpha = false;
		g_aHuman[nCntHuman].fAlpha = 1.0f;
	} // EO for

	// タイム増加の敵破壊数のリセット
	g_nHumanTime = 0;
	return S_OK;
}//EOInitHuman

//============================================
//
//  名前  UninitHuman関数
//  引数	void
//  戻り値  void
//  説明  Human関係の終了処理
//
//============================================
void UninitHuman(void)
{
	for(int nCntHuman = 0 ; nCntHuman < HUMAN_MAX  ; nCntHuman++)
	{
		//テクスチャインターフェースの後片付け
		SAFE_RELEASE( g_pTextureHuman[nCntHuman] );
	} // EO for

	//頂点バッファの後片付け
	SAFE_RELEASE( g_pVtxBufferHuman );
}//EOUninitHuman

//============================================
//
//  名前  UpdateHuman関数
//  引数	void
//  戻り値  void
//  説明  Human関係の更新処理
//
//============================================
void UpdateHuman(void)
{
	// 人の発生→NotesUpdate

	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo

		//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferHuman -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

	// UVアニメーションで人
	for(int nCntHuman = 0 ; nCntHuman < MAX_HUMAN ; nCntHuman++)
	{
		// 使用チェック
		if(g_aHuman[nCntHuman].bUse == true)
		{

			//頂点座標の設定(2D座標 , 右回り )
			pVtx [ 0 + 4*nCntHuman] . pos = D3DXVECTOR3 (g_aHuman[nCntHuman].fPos.x , g_aHuman[nCntHuman].fPos.y , 0.0f);
			pVtx [ 1 + 4*nCntHuman] . pos = D3DXVECTOR3 (g_aHuman[nCntHuman].fPos.x + g_aHuman[nCntHuman].fWidth ,g_aHuman[nCntHuman].fPos.y , 0.0f);
			pVtx [ 2 + 4*nCntHuman] . pos = D3DXVECTOR3 (g_aHuman[nCntHuman].fPos.x , g_aHuman[nCntHuman].fPos.y + g_aHuman[nCntHuman].fHeight , 0.0f);
			pVtx [ 3 + 4*nCntHuman] . pos = D3DXVECTOR3 (g_aHuman[nCntHuman].fPos.x + g_aHuman[nCntHuman].fWidth , g_aHuman[nCntHuman].fPos.y + g_aHuman[nCntHuman].fHeight , 0.0f);

		    //各頂点のテクスチャ座標の設定
			pVtx [ 0 + 4*nCntHuman] . tex = D3DXVECTOR2 (g_aHuman[nCntHuman].fUV.x , g_aHuman[nCntHuman].fUV.y);
			pVtx [ 1 + 4*nCntHuman] . tex = D3DXVECTOR2 (g_aHuman[nCntHuman].fUV.x + HUMAN_U_WIDTH , g_aHuman[nCntHuman].fUV.y);
			pVtx [ 2 + 4*nCntHuman] . tex = D3DXVECTOR2 (g_aHuman[nCntHuman].fUV.x , g_aHuman[nCntHuman].fUV.y + HUMAN_V_HEIGHT);
			pVtx [ 3 + 4*nCntHuman] . tex = D3DXVECTOR2 (g_aHuman[nCntHuman].fUV.x + HUMAN_U_WIDTH , g_aHuman[nCntHuman].fUV.y+ HUMAN_V_HEIGHT);


			//////////////////////////////////////////////////
			//  もしUVアニメーションするならここ、爆発参照  //
			//////////////////////////////////////////////////
			g_aHuman[nCntHuman].nCntAnim++;
			if(g_aHuman[nCntHuman].nCntAnim >= HUMAN_ANIM_TIME)
			{
				g_aHuman[nCntHuman].nCntAnim = 0;
				g_aHuman[nCntHuman].fUV.x += 0.5f;
			}
			////////////////////////
			//  移動量の場合分け  //
			////////////////////////
			// 毎フレームの移動   //
			//////////////////////////////////////////////////
			// プレイヤーの位置把握
			PLAYER* pPlayer = GetPlayer();

			if(g_aHuman[nCntHuman].bUpdateFlag == true)
			{
				switch(g_aHuman[nCntHuman].nMode)
				{
				case HUMAN_ONE: // 直進
					g_aHuman[nCntHuman].fPos.x -= HUMAN_SPEED_SLOW;
					break;
				case HUMAN_TWO: // Yがプレイヤーに向かってくる
					g_aHuman[nCntHuman].fPos.x -= HUMAN_SPEED_SLOW;
					break;
				} // EO switch
			} // EO if
			//////////////////////////////////////////////////

			////////////////////
			// 壁来たら消える //
			//////////////////////////////////////////////////
			if(g_aHuman[nCntHuman].fPos.x + g_aHuman[nCntHuman].fWidth <= 0)
			{
				// ライフ0により消滅
				g_aHuman[nCntHuman].bUse = false;

				// 門or壊れていたら城についたら効果発揮

			} // EO if
			//////////////////////////////////////////////////

			////////////////////////
			// 門当たったら消える //
			//////////////////////////////////////////////////
			GATE* pGate = GetGate();
			int nCntGate = 0;
			for(nCntGate = 0 ; nCntGate < GATE_NUM ; nCntGate++)
			{
				if((pGate + nCntGate)->bUse == true && g_aHuman[nCntHuman].bAlpha == false)
				{
					if((pGate + nCntGate)->fPos.x >= g_aHuman[nCntHuman].fPos.x&&
						(pGate + nCntGate)->fPos.y <= g_aHuman[nCntHuman].fPos.y + g_aHuman[nCntHuman].fHeight / 2.0f&&
						(pGate + nCntGate)->fPos.y + (pGate + nCntGate)->fSize.y >= g_aHuman[nCntHuman].fPos.y + g_aHuman[nCntHuman].fHeight / 2.0f)
					{
						switch(g_aHuman[nCntHuman].nMode)
						{
						case HUMAN_ONE: // 回復
							AddLife(nCntGate , 20);
							g_aHuman[nCntHuman].bAlpha = true;
							break;
						case HUMAN_TWO: // 必殺技////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							addFcohEnergy(1);		//必殺技チャージ
							g_aHuman[nCntHuman].bAlpha = true;
							SetEffect((pGate + nCntGate)->fPos.x + (pGate + nCntGate)->fSize.x / 2 , (pGate + nCntGate)->fPos.y + (pGate + nCntGate)->fSize.y/2,
								(pGate + nCntGate)->fSize.x * 3 , LINE_HEIGHT , EFFECT_KILL);
							break;
						}
					}
				}
			}

			if(g_aHuman[nCntHuman].fPos.x + g_aHuman[nCntHuman].fWidth <= 0)
			{
				// 門or壊れていたら城についたら効果発揮

			} // EO if
			//////////////////////////////////////////////////

			//////////////////////////
			// 体力なくなったら爆発 //
			//////////////////////////////////////////////////
			if(g_aHuman[nCntHuman].nLife <= 0)
			{
				// ライフ0により消滅
				g_aHuman[nCntHuman].bAlpha = true;

			} // EO if
			//////////////////////////////////////////////////

			if(g_aHuman[nCntHuman].bUpdateFlag == false)
			{
				int i = 0;
			}

			// 通り過ぎたら
			if(g_aHuman[nCntHuman].bAlpha == true)
			{
				g_aHuman[nCntHuman].fAlpha -= HUMAN_TRANSPARENT;
				if(g_aHuman[nCntHuman].fAlpha <= 0.0f)
				{
					g_aHuman[nCntHuman].bUse = false;
				}
			}
			//頂点カラー(0～255の整数値)
			pVtx[0 + 4 * nCntHuman].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aHuman[nCntHuman].fAlpha);
			pVtx[1 + 4 * nCntHuman].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aHuman[nCntHuman].fAlpha);
			pVtx[2 + 4 * nCntHuman].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aHuman[nCntHuman].fAlpha);
			pVtx[3 + 4 * nCntHuman].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aHuman[nCntHuman].fAlpha);

		} // EO if
	} // EO for

	g_pVtxBufferHuman->Unlock ();												//ロック解除

}//EOUpdateHuman

//============================================
//
//  名前  DrawHuman関数
//  引数	void
//  戻り値  void
//  説明  Human関係の描画処理
//
//============================================
void DrawHuman(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//パイプラインの設定
	pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
						g_pVtxBufferHuman ,//データのある場所(先頭アドレス)
						0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
						sizeof(VERTEX2D) );//ストライド量(一個の単位の大きさ)

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// 最大数チェック
	for(int nCntHuman = 0 ; nCntHuman < MAX_HUMAN ; nCntHuman++)
	{
		if(g_aHuman[nCntHuman].bUse == true)
		{
			if(g_aHuman[nCntHuman].bDrawFlag == true)
			{
				// 種類で分ける
				switch(g_aHuman[nCntHuman].nMode)
				{
				case HUMAN_ONE:

					//Humanの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureHuman[0] );

					break;
				case HUMAN_TWO:

					//Humanの描画をする寸前
					pDevice -> SetTexture( 0 , g_pTextureHuman[1] );

					break;
				} // EO switch

				//プリミティブの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
					nCntHuman * 4 ,//オフセット(頂点数)何頂点目からとるか
					NUM_POLYGON );//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。
			} // EO if
			else
			{
				g_aHuman[nCntHuman].bDrawFlag = true;
			} // EO if
		} // EO if
	} // EO for
}//EODarwHuman

//============================================
//
//  名前  MakeVertexHuman関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexHuman(LPDIRECT3DDEVICE9 pDevice)
{

	//頂点バッファ作成
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_HUMAN,//作成したい頂点バッファのサイズ = 1つの頂点のサイズ * 頂点数
																	//どれくらいメモリほしいか、ここをめっちゃふやすんでーーー
			D3DUSAGE_WRITEONLY,									//頂点バッファの使用方法、書き込み専用なので、恐らく最速
			FVF_VERTEX_2D,										//NULLや0でも大丈夫、マナー的には書こうよ。このバッファの頂点フォーマットを問う
			D3DPOOL_MANAGED,									//メモリ管理どうする設定、この状態はデバイスにお任せ
			&g_pVtxBufferHuman,						//出来上がった頂点バッファを管理するアドレス
			NULL)												//謎だけれどNULL
	))
	{
		return E_FAIL;
	}


	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferHuman -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

		// 最大数回す
	for(int nCntHuman = 0 ; nCntHuman < MAX_HUMAN ; nCntHuman++)
	{
		//rhwの設定(必ず1.0fを入れる!!!!!!!!)
		pVtx[0 + 4 * nCntHuman].rhw = 1.0f;
		pVtx[1 + 4 * nCntHuman].rhw = 1.0f;
		pVtx[2 + 4 * nCntHuman].rhw = 1.0f;
		pVtx[3 + 4 * nCntHuman].rhw = 1.0f;

		//頂点カラー(0～255の整数値)
		pVtx[0 + 4 * nCntHuman].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntHuman].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntHuman].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntHuman].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//鍵をアンロック
	g_pVtxBufferHuman -> Unlock();

	return S_OK;

}//EOMakeVertexHuman

//============================================
//
//  名前  SetHuman関数
//  引数	void
//  戻り値  float fPosX ,float fPosY,float fWidth,float fHeught,Human_MODE nMode
//  説明  人をセット
//
//============================================
void    SetHuman    (float fPosX , // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	HUMAN_MODE nMode			   // 種類
	)
{
	for(int nCntHuman = 0 ; nCntHuman < MAX_HUMAN ; nCntHuman++)
	{
		if(g_aHuman[nCntHuman].bUse == false)
		{
			g_aHuman[nCntHuman].bUse = true;
			g_aHuman[nCntHuman].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aHuman[nCntHuman].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aHuman[nCntHuman].fHeight = fHeught;
			g_aHuman[nCntHuman].fFlame = 0;
			g_aHuman[nCntHuman].nMode = nMode;
			g_aHuman[nCntHuman].bMoveFlag = true;
			g_aHuman[nCntHuman].bUpdateFlag = true;
			g_aHuman[nCntHuman].nLife = 1;
			g_aHuman[nCntHuman].nPoint = 10;
			g_aHuman[nCntHuman].nCntAnim = 0;
			g_aHuman[nCntHuman].bAlpha = false;
			g_aHuman[nCntHuman].fAlpha = 1.0f;
			if(nMode == HUMAN_FIVE)
			{
				g_aHuman[nCntHuman].nLife = 2;
			}

			g_aHuman[nCntHuman].nNumWarning = -1;

			switch(nMode)
			{
			case HUMAN_ONE:

			g_aHuman[nCntHuman].fWidth = 100;
				g_aHuman[nCntHuman].nPoint = HUMAN_POINT_TYPE_ONE;

				break;
			case HUMAN_TWO:

			g_aHuman[nCntHuman].fWidth = 200;
				g_aHuman[nCntHuman].nPoint = HUMAN_POINT_TYPE_TWO;


				break;
			case HUMAN_THREE:

				g_aHuman[nCntHuman].nPoint = HUMAN_POINT_TYPE_THREE;


				break;
			case HUMAN_FOUR:

				g_aHuman[nCntHuman].nPoint = HUMAN_POINT_TYPE_FOUR;


				break;
			case HUMAN_FIVE:

				g_aHuman[nCntHuman].nPoint = HUMAN_POINT_TYPE_FIVE;


				break;
			case HUMAN_SIX:

				g_aHuman[nCntHuman].nPoint = HUMAN_POINT_TYPE_SIX;


				break;
			case HUMAN_SEVEN:
				g_aHuman[nCntHuman].nPoint = HUMAN_POINT_TYPE_SEVEN;

				break;
			} // EO switch
			break;
		} // EO if
	} // EO for
} // EO SetHuman

//============================================
//
//  名前  GetHuman関数
//  引数	void
//  戻り値  HUMAN *g_aHuman[0]
//  説明  g_aHumanの先頭アドレスを渡す
//
//============================================
HUMAN* GetHuman()
{
	return &g_aHuman[0];
} // EO GetHuman

//============================================
//
//  名前  CheckHumanTime関数
//  引数	void
//  戻り値  true or false
//  説明  敵破壊数が規定を満たしているかどうかを返す
//
//============================================
bool CheckHumanTime (void)
{
	// 敵破壊数が一定までいっていたら
	if(g_nHumanTime >= HUMAN_NUM_TIMEPLASS)
	{
		g_nHumanTime = 0;

		return true;
	} // EO if
	return false;
} // EO CheckHumanTime

void    AddDameageHuman(int nID , int nDamege)
{
	if(g_aHuman[nID].bUse == true)
	{
		g_aHuman[nID].nLife -= nDamege;
		if(g_aHuman[nID].nLife <= 0)
		{
			//PlaySound(SOUND_LABEL_SE002);
			g_aHuman[nID].bUse = false;
		} // EO if
	} // EO if
} // EO AddDameageHuman

D3DXVECTOR3    GetHumanPos(int n)
{
	if(g_aHuman[n].bUse == true)
		return D3DXVECTOR3(g_aHuman[n].fPos.x , g_aHuman[n].fPos.y , 0.0f);

	return D3DXVECTOR3(0.0f , 0.0f , 0.0f);
}
