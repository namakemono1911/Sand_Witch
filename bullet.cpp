/*****************************************************************************
bullet.cpp
Aythor	: 上野　匠
Data	: 2017_04_13
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include <math.h>
#include "bullet.h"
#include "polygon.h"
#include "player.h"
#include "notes.h"
#include "boss.h"
#include "human.h"
#include "nucleusBoss.h"
#include "bulletBoss.h"
#include "gate.h"
#include "input.h"
#include "bulletUI.h"
#include "activate.h"
#include "bulletEffect.h"
#include "explo.h"
#include "sound.h"
#include "game.h"

#include "effect.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define	BULLET_MAX			(100)		//弾の最大数
#define BULLET_CONF			"data/conf/bulletConf"	//弾のコンフィグ

#define BULLET_COUNT		(30)		//次の弾発射までの時間
#define SPE_BULLET_COUNT	(300)		//特殊弾のクールタイム

#define BULLET_EXPLO		(600)		//爆発の有効範囲
#define BULLET_DIFF			(700)		//拡散範囲

#define BULLET_DMG			(1)			//通常弾の威力
#define SPE_BULLET_DMG		(3)			//特殊弾の威力

#define DIFF_BULLET_MIN		(3)			//拡散する弾の下限
#define DIFF_BULLET_MAX		(10)			//拡散する弾の上限

#define CHALLENGE			(100)			//チャレンジ回数
#define ANIME_FRAME			(15)		//30fpsで更新
#define ERO					(1)			//跳ね返り定数

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON		conf;	//画像の設定
	TEXTURE			tex;	//テクスチャの設定
	float			move;	//移動値
	BULLET_TYPE		type;	//弾の種類
	int				anime;	//テクスチャアニメーションのフレーム
	float			mass;	//質量
	int				effectID;//エフェクト配列番号
	bool			use;	//使用フラグ
	bool			active;	//魔法が発動してるか
}BULLET;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBullet ( LPDIRECT3DDEVICE9 pDevice );
bool	sandBullet	(int numBullet);
void	sortBullet	(float *sort, int numBullet, int upBullet);

void	addBullet	(int numBullet, int upBullet);
void	bomBullet(D3DXVECTOR3 pos);
void	diffBullet(UINT numBullet);
bool	checkOverlapBullet(D3DXVECTOR3 pos, BULLET_TYPE type);

bool	checkEnemy(float s, float l, int numBullet, int upBullet);
void	damageEnemy(NOTES *notes, int numEnemy, int numBullet, int upBullet);

bool	checkBoss(float s, float l, int numBullet, int upBullet);
void	damageBoss(int numBoss, int numBullet, int upBullet);

bool	checkHuman(float s, float l, int numBullet, int upBullet);
void	damageHuman(HUMAN *human, int numHuman, int numBullet, int upBullet);

bool	checkBossBullet(float s, float l, int numBullet, int upBullet);
void	damageBossBullet(BOSSBULLET *bosBlt, int numBoss, int numBullet, int upBullet);

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureBullet[BULLET_TYPE_MAX] = {};		//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBullet = NULL;	//頂点バッファ管理インターフェイス

BULLET	g_bullet[BULLET_MAX];			//弾の設定
char	*bulletTexName[]	=			//テクスチャの名前
{
	"data/TEXTURE/GAME/BULLET/magic0002-1.png",
	"data/TEXTURE/GAME/BULLET/magic0001-2.png",
	"data/TEXTURE/GAME/BULLET/bakuhatu3.png",
	"data/TEXTURE/GAME/BULLET/bullet05.png",
	"data/TEXTURE/GAME/BULLET/kakusan.png",
};

//////////////////////////////////////////////////////////////////////////////
//関数名	: initBullet
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initBullet ( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得
	int		i;		//loop

	//構造体初期化
	for(i = 0; i < BULLET_MAX; i++)
	{
		//テクスチャ初期化
		g_bullet[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
		g_bullet[i].tex.size = D3DXVECTOR2(1.f, 1.f);
		g_bullet[i].use = false;
		g_bullet[i].active = false;
	}

	//テクスチャの読み込み
	for(i = 0; i < BULLET_TYPE_MAX; i++)
	{
		if(FAILED(D3DXCreateTextureFromFile(pDevice, bulletTexName[i], &g_pTextureBullet[i])))
		{
			MessageBox(NULL, "bullet", "エラー", MB_OK);
		}
	}

	//デバイス取得
	makeVertexBullet(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitBullet
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitBullet ( void )
{
	//変数宣言
	int		i;		//loop

	//テクスチャインターフェイスの解放
	for(i = 0; i < BULLET_TYPE_MAX; i++)
	{
		if(g_pTextureBullet[i] != NULL)
		{
			g_pTextureBullet[i]->Release();
			g_pTextureBullet[i] = NULL;
		}
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferBullet != NULL)
	{
		g_pVtxBufferBullet->Release();
		g_pVtxBufferBullet = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateBullet
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateBullet ( void )
{
	//変数宣言
	VERTEX2D	*pVtx;

	//=============================
	//弾の情報更新
	//=============================
	for(int i = 0; i < BULLET_MAX; i++)
	{
		//弾が使われていたら更新
		if(g_bullet[i].use == true)
		{
			//弾移動
			g_bullet[i].conf.conf.pos.x += g_bullet[i].move;

			//テクスチャアニメ
			g_bullet[i].anime = (g_bullet[i].anime + 1) % 60;
			if(g_bullet[i].anime % (60 / ANIME_FRAME) == 0)
			{
				g_bullet[i].tex.pos.x += g_bullet[i].tex.size.x;
				g_bullet[i].tex.pos.x = fmod(g_bullet[i].tex.pos.x, 1);
			}

			//弾が画面外に出たら削除
			if (g_bullet[i].conf.conf.pos.x - g_bullet[i].conf.conf.size.x >= SCREEN_WIDTH ||
				g_bullet[i].conf.conf.pos.x + g_bullet[i].conf.conf.size.x <= 100)
			{
				g_bullet[i].use = false;
				resetCombo();
			}
		}
	}

	//=============================
	//当たり判定 
	//=============================
	for(int i = 0; i < BULLET_MAX; i++)
	{
		//弾が使われていれば判定
		if(g_bullet[i].use == true)
		{
			if(sandBullet(i) == false)
			{
				if(g_bullet[i].active == true)
				{
					releaseBulletEffect(g_bullet[i].effectID);
					g_bullet[i].active = false;
				}
			}
		}
	}

	//=============================
	//バッファ登録
	//=============================
	g_pVtxBufferBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < BULLET_MAX; i++)
	{
		if(g_bullet[i].use == true)
		{
			//座標更新
			setRotBuffer(pVtx, g_bullet[i].conf);

			//テクスチャ更新
			setTexture(pVtx, g_bullet[i].tex);
		}

		//ポインタ移動
		pVtx += 4;
	}

	g_pVtxBufferBullet->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawBullet
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawBullet ( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	int		i;		//loop

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferBullet, 0, sizeof(VERTEX2D));

	//ポリゴンの描画
	for(i = 0; i < BULLET_MAX; i++)
	{
		if(g_bullet[i].use == true)
		{
			//テクスチャ読み込み
			pDevice->SetTexture(0,g_pTextureBullet[g_bullet[i].type]);

			pDevice->DrawPrimitive
				(
				D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
				NUM_VERTEX * i,			//オフセット(頂点数)
				NUM_POLYGON				//ポリゴンの数
				);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexBullet
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBullet ( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ
	int		i;		//loop

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VERTEX * BULLET_MAX,		//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//メモリ管理方法
			&g_pVtxBufferBullet,				//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	g_pVtxBufferBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < BULLET_MAX * NUM_VERTEX; i++)
	{
		//rhwの設定(必ず1.0f)
		pVtx->rhw = 1.f;

		//頂点カラーの設定(0~155の整数値)
		pVtx->color = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx++;
	}

	g_pVtxBufferBullet->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBullet
//返り値	: 
//説明		: 弾設定
//////////////////////////////////////////////////////////////////////////////
void	setBullet	( D3DXVECTOR3 pos, BULLET_TYPE type )
{
	//変数宣言
	int		i;				//loop

	//カウントダウン中なら発射不可
	if ((getBulletCoolTime(0) > 0 && type <= BULLET001) || (getBulletCoolTime(1) > 0 && (type == BULLET002 || type == BULLET003)))
	{
		return;
	}
	//通常弾
	else if(type <= BULLET001)
	{
		setBulletUICoolTime(0, BULLET_COUNT);
	}
	//特殊弾
	else if(type >= BULLET002 &&  type <= BULLET003)
	{
		setBulletUICoolTime(1, SPE_BULLET_COUNT);
	}

	//未使用の弾探索
	for (i = 0; i < BULLET_MAX; i++)
	{
		//使われていなければ弾セット
		if (g_bullet[i].use == false && checkOverlapBullet(pos, type) == false)
		{
			initRotPolygon(&g_bullet[i].conf, pos, bulletSizeList[type]);
			g_bullet[i].move = bulletMoveList[type];
			g_bullet[i].type = type;
			g_bullet[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
			g_bullet[i].tex.size = D3DXVECTOR2(1.f / 10.0f, 1.f);
			g_bullet[i].anime = 0;
			g_bullet[i].mass = bulletMassList[type];
			g_bullet[i].effectID = -1;

			g_bullet[i].use = true;
			g_bullet[i].active = false;

			//発射音
			switch(type)
			{
			case	BULLET000:	// 通常
				PlaySound(SE_GAME_MAGIC_GO);
				break;
			case	BULLET001 :
				PlaySound(SE_GAME_MAGIC_GO);
				break;
			case	BULLET002 :	// 爆発
				PlaySound(SE_GAME_MAGIC_GO_BOMM);
				break;
			case	BULLET003 :	// 拡散
				PlaySound(SE_GAME_MAGIC_GO_DIFISION);
				break;
			case	BULLET004 :
				PlaySound(SE_GAME_MAGIC_GO);
				break;
			}

			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: sandBullet
//返り値	: 弾が重なっていれば true
//説明		: 敵との当たり判定
//////////////////////////////////////////////////////////////////////////////
bool	sandBullet	(int numBullet)
{
	//i番目の弾の一つ上のレーンの弾探索
	for(int j = 0; j < BULLET_MAX; j++)
	{
		//一つ上に弾があるか判定
		if( numBullet != j && g_bullet[j].use == true && g_bullet[numBullet].type != g_bullet[j].type &&
			g_bullet[numBullet].conf.conf.pos.y < g_bullet[j].conf.conf.pos.y &&
			g_bullet[numBullet].conf.conf.pos.y + SCREEN_HEIGHT / 5 > g_bullet[j].conf.conf.pos.y)
		{
			//重なってるか判定
			if( g_bullet[numBullet].conf.conf.pos.x + g_bullet[numBullet].conf.conf.size.x * 0.5f >= g_bullet[j].conf.conf.pos.x - g_bullet[j].conf.conf.size.x * 0.5f &&
				g_bullet[numBullet].conf.conf.pos.x - g_bullet[numBullet].conf.conf.size.x * 0.5f <= g_bullet[j].conf.conf.pos.x + g_bullet[j].conf.conf.size.x * 0.5f)
			{
				//座標をソートして当たり判定作成
				float sort[LINE_OBJ_MAX];
				sortBullet(sort, numBullet, j);

				//重なった部分にエフェクト設定
				if(g_bullet[numBullet].active == false)
				{
					//エフェクト設定
					g_bullet[numBullet].effectID = setBulletEffect(
						D3DXVECTOR3((sort[1] + sort[2]) * 0.5f, g_bullet[numBullet].conf.conf.pos.y + LINE_HEIGHT * 0.5f, 0.f),
						D3DXVECTOR3(sort[2] - sort[1], NOTES_HEIGHT, 0.f),
						BULLET_EFFECT_001);

					g_bullet[numBullet].active = true;
				}
				else
				{
					setBulletEffectPos(g_bullet[numBullet].effectID,
						D3DXVECTOR3((sort[1] + sort[2]) * 0.5f, g_bullet[numBullet].conf.conf.pos.y + LINE_HEIGHT * 0.5f, 0.f));

					setBulletEffectSize(g_bullet[numBullet].effectID,
						D3DXVECTOR3(sort[1] - sort[2], NOTES_HEIGHT, 0.f));
				}

				//敵との当たり判定
				if (true == checkEnemy(sort[2], sort[1], numBullet, j) ||		//敵との当たり判定
					true == checkBoss(sort[2], sort[1], numBullet, j) ||		//ボスとの当たり判定
					true == checkBossBullet(sort[2], sort[1], numBullet, j))	//ボス弾との当たり判定
				{
					if (true == g_bullet[j].active)
					{
						releaseBulletEffect(g_bullet[j].effectID);
						g_bullet[j].active = false;
					}

					addCombo();		//コンボ加算
					return true;
				}
				if (true == checkHuman(sort[2], sort[1], numBullet, j))		//市民との当たり判定
				{
					if (true == g_bullet[j].active)
					{
						releaseBulletEffect(g_bullet[j].effectID);
						g_bullet[j].active = false;
					}
					resetCombo();	//コンボリセット
					return true;
				}

				return true;
			}
		}

		addBullet(numBullet, j);
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: sortBullet
//返り値	: 
//説明		: 実質バブルソート
//////////////////////////////////////////////////////////////////////////////
void	sortBullet	(float *sort, int numBullet, int upBullet)
{
	float	work;					//待避所

	//重なってる範囲で更に当たり判定
	sort[0] = g_bullet[numBullet].conf.conf.pos.x + g_bullet[numBullet].conf.conf.size.x * 0.5f;
	sort[1] = g_bullet[numBullet].conf.conf.pos.x - g_bullet[numBullet].conf.conf.size.x * 0.5f;
	sort[2] = g_bullet[upBullet].conf.conf.pos.x + g_bullet[upBullet].conf.conf.size.x * 0.5f;
	sort[3] = g_bullet[upBullet].conf.conf.pos.x - g_bullet[upBullet].conf.conf.size.x * 0.5f;

	//ソートして配列2と3が範囲になる
	for(int k = 0; k < LINE_OBJ_MAX; k++)
	{
		for(int l = 0; l < LINE_OBJ_MAX; l++)
		{
			if(sort[l] < sort[l + 1])
			{
				work = sort[l];			//一旦退避
				sort[l] = sort[l + 1];	//交換こ
				sort[l + 1] = work;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: addBullet
//返り値	: 
//説明		: 同じレーンの弾が当たったら合成
//////////////////////////////////////////////////////////////////////////////
void	addBullet	(int numBullet, int upBullet)
{
	//同じレーンの弾か判定
	if( numBullet != upBullet && g_bullet[numBullet].use == true &&
		g_bullet[numBullet].conf.conf.pos.y + g_bullet[numBullet].conf.conf.size.y * 0.5f > g_bullet[upBullet].conf.conf.pos.y &&
		g_bullet[numBullet].conf.conf.pos.y - g_bullet[numBullet].conf.conf.size.y * 0.5f < g_bullet[upBullet].conf.conf.pos.y)
	{
		//右隣の弾と重なってるか判定
		if( g_bullet[numBullet].conf.conf.pos.x + g_bullet[numBullet].conf.conf.size.x * 0.5f >= g_bullet[upBullet].conf.conf.pos.x - g_bullet[upBullet].conf.conf.size.x * 0.5f &&
			g_bullet[numBullet].conf.conf.pos.x - g_bullet[numBullet].conf.conf.size.x * 0.5f <= g_bullet[upBullet].conf.conf.pos.x + g_bullet[upBullet].conf.conf.size.x * 0.5f)
		{
			if (g_bullet[numBullet].conf.conf.pos.x > g_bullet[upBullet].conf.conf.pos.x)
			{
				g_bullet[numBullet].conf.conf.pos.x +=
					(g_bullet[numBullet].conf.conf.size.x * 0.5f + g_bullet[upBullet].conf.conf.size.x * 0.5f) - 
					(g_bullet[numBullet].conf.conf.pos.x - g_bullet[upBullet].conf.conf.pos.x) + 0.01f;
			}
			else
			{
				g_bullet[upBullet].conf.conf.pos.x +=
					(g_bullet[numBullet].conf.conf.size.x * 0.5f + g_bullet[upBullet].conf.conf.size.x * 0.5f) -
					(g_bullet[upBullet].conf.conf.pos.x - g_bullet[numBullet].conf.conf.pos.x) + 0.01f;
			}

			float	move[2];	//退避用move

			move[0] = 
				((g_bullet[numBullet].mass - ERO * g_bullet[upBullet].mass) * g_bullet[numBullet].move + (1 + ERO) * g_bullet[upBullet].mass * g_bullet[upBullet].move) /
				(g_bullet[numBullet].mass + g_bullet[upBullet].mass);

			move[1] =
				((g_bullet[upBullet].mass - ERO * g_bullet[numBullet].mass) * g_bullet[upBullet].move + (1 + ERO) * g_bullet[numBullet].mass * g_bullet[numBullet].move) /
				(g_bullet[upBullet].mass + g_bullet[numBullet].mass);

			g_bullet[numBullet].move = move[0];
			g_bullet[upBullet].move = move[1];
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: bomBullet
//返り値	: 
//説明		: 爆発弾が炸裂した時の処理
//////////////////////////////////////////////////////////////////////////////
void	bomBullet	(D3DXVECTOR3 pos)
{
	//敵との判定
	for(int i = 0; i < MAX_NOTES; i++)
	{
		//同じレーンにいるか誤差を考慮して探索
		if(GetEnemyPos(i).y >= pos.y - 1 && GetEnemyPos(i).y <= pos.y + 1)
		{
			//爆発範囲内ならダメージ
			if (GetEnemyPos(i).x >= pos.x - BULLET_EXPLO * 0.5f &&
				GetEnemyPos(i).x <= pos.x + BULLET_EXPLO * 0.5f)
			{
//				AddDameage(i, SPE_BULLET_DMG);
				StopDamage(i , SPE_BULLET_DMG);

			}
		}
	}

	//ボスとの判定
	BOSSNUCLEUS	*nuc = GetNucleusBoss();
	if(nuc->bUse == true && nuc->fPos.y >= pos.y - 1 && nuc->fPos.y <= pos.y + 1)
	{
		//爆発範囲内ならダメージ
		if (nuc->fPos.x >= pos.x - BULLET_EXPLO * 0.5f &&
			nuc->fPos.x <= pos.x + BULLET_EXPLO * 0.5f)
		{
			AddDameageBoss(0, SPE_BULLET_DMG);
		}
	}

	//市民との判定
	HUMAN	*human = GetHuman();
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		if (human->bUse == true && human->fPos.y >= pos.y - 1 && human->fPos.y <= pos.y + 1)
		{
			//爆発範囲内ならダメージ
			if (human->fPos.x >= pos.x - BULLET_EXPLO * 0.5f &&
				human->fPos.x <= pos.x + BULLET_EXPLO * 0.5f)
			{
				AddDameageHuman(i, SPE_BULLET_DMG);
			}
		}

		human++;
	}
	
	//ボス弾との判定
	BOSSBULLET	*bosBlt = GetBulletBoss();
	for(int i = 0; i < MAX_BOSSBULLET; i++)
	{
		if (bosBlt->bUse == true && bosBlt->fPos.y - bosBlt->fHeight * 0.5f >= pos.y - 1 && bosBlt->fPos.y - bosBlt->fHeight * 0.5f <= pos.y + 1)
		{
			//爆発範囲内ならダメージ
			if (bosBlt->fPos.x >= pos.x - BULLET_EXPLO * 0.5f &&
				bosBlt->fPos.x <= pos.x + BULLET_EXPLO * 0.5f)
			{
				AddDmgBulletBoss(i, SPE_BULLET_DMG);
			}
		}

		bosBlt++;
	}

	PlaySound(SE_GAME_MAGIC_ON_BOMM);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: diffBullet
//返り値	: 
//説明		: 拡散弾が炸裂した時の処理
//////////////////////////////////////////////////////////////////////////////
void	diffBullet	( UINT numBullet )
{
	//変数宣言
	int			num;			//いくつ拡散されるか
	int			buf[5] = {0};	//バッファ
	float		work;			//ワーク
	int			j = 0;			//チャレンジカウント

	//拡散数設定1～5発
	num = (rand() % (DIFF_BULLET_MAX - DIFF_BULLET_MIN)) + DIFF_BULLET_MIN;

	for(int i = 0; i < num; )
	{
		work = abs((rand() * rand() * rand())) % (SCREEN_WIDTH - (int)POSX) + POSX;

		switch(rand() % 5)
		{
		case 0:
			//チャレンジ1年生
			if (checkOverlapBullet(D3DXVECTOR3(work, PLAYER_POS_1, 0.f), BULLET004) == true)
			{
				work = abs((rand() * rand() * rand())) % (SCREEN_WIDTH - (int)POSX) + POSX;
				j++;

				if(j > CHALLENGE)
				{
					i++;
					continue;
				}

				continue;
			}

			//弾生成
			setBullet(
				D3DXVECTOR3(work, PLAYER_POS_1, 0.f),
				BULLET004);

			buf[0]++;
			i++;
			j = 0;
			continue;

		case 1:
				//チャレンジ1年生
				if (checkOverlapBullet(D3DXVECTOR3(work, PLAYER_POS_2, 0.f), BULLET004) == true)
				{
					work = abs((rand() * rand() * rand())) % (SCREEN_WIDTH - (int)POSX) + POSX;
					j++;

					if (j > CHALLENGE)
					{
						i++;
						continue;
					}

					continue;
				}

				//弾生成
				setBullet(
					D3DXVECTOR3(work, PLAYER_POS_2, 0.f),
					BULLET004);

				buf[1]++;
				i++;
			continue;

		case 2:
				//チャレンジ1年生
				if (checkOverlapBullet(D3DXVECTOR3(work, PLAYER_POS_3, 0.f), BULLET004) == true)
				{
					work = abs((rand() * rand() * rand())) % (SCREEN_WIDTH - (int)POSX) + POSX;
					j++;

					if (j > CHALLENGE)
					{
						i++;
						continue;
					}

					continue;
				}

				//弾生成
				setBullet(
					D3DXVECTOR3(work, PLAYER_POS_2, 0.f),
					BULLET004);

				buf[1]++;
				i++;
				continue;

		case 3:
				//チャレンジ1年生
				if (checkOverlapBullet(D3DXVECTOR3(work, PLAYER_POS_4, 0.f), BULLET004) == true)
				{
					work = abs((rand() * rand() * rand())) % (SCREEN_WIDTH - (int)POSX) + POSX;
					j++;

					if (j > CHALLENGE)
					{
						i++;
						continue;
					}

					continue;
				}

				//弾生成
				setBullet(
					D3DXVECTOR3(work, PLAYER_POS_4, 0.f),
					BULLET004);

				buf[3]++;
				i++;
			continue;

		case 4:
				//チャレンジ1年生
				if (checkOverlapBullet(D3DXVECTOR3(work, PLAYER_POS_5, 0.f), BULLET004) == true)
				{
					work = abs((rand() * rand() * rand())) % (SCREEN_WIDTH - (int)POSX) + POSX;
					j++;

					if (j > CHALLENGE)
					{
						i++;
						continue;
					}

					continue;
				}

				//弾生成
				setBullet(
					D3DXVECTOR3(work, PLAYER_POS_5, 0.f),
					BULLET004);

				buf[4]++;
				i++;
			continue;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: checkOverlapBullet
//返り値	: 重なってたらtrue
//説明		: 生成された弾が重なっていないかチェック
//////////////////////////////////////////////////////////////////////////////
bool	checkOverlapBullet	(D3DXVECTOR3 pos, BULLET_TYPE type)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_bullet[i].use == true)
		{
			if (g_bullet[i].conf.conf.pos.x + g_bullet[i].conf.conf.size.x * 0.5f >= pos.x - bulletSizeList[type].x * 0.5f &&
				g_bullet[i].conf.conf.pos.x - g_bullet[i].conf.conf.size.x * 0.5f <= pos.x + bulletSizeList[type].x * 0.5f &&
				g_bullet[i].conf.conf.pos.y + g_bullet[i].conf.conf.size.y * 0.5f >= pos.y - bulletSizeList[type].y * 0.5f &&
				g_bullet[i].conf.conf.pos.y - g_bullet[i].conf.conf.size.y * 0.5f <= pos.y + bulletSizeList[type].y * 0.5f)
			{
				return true;
			}
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: checkEnemy
//返り値	: 敵と重なってたらtrue
//説明		: 敵と当たってるか判定
//////////////////////////////////////////////////////////////////////////////
bool	checkEnemy(float s, float l, int numBullet, int upBullet)
{
	//当たり判定の範囲に敵いないか探索
	NOTES	*notes;		//敵のポインタ
	notes = GetNotes();	//ポインタ取得
	for (int n = 0; n < MAX_NOTES; n++)
	{
		//いたらダメージ
		if (notes->bUse == true &&
			notes->fPos.x <= l && notes->fPos.x >= s &&
			notes->fPos.y <= g_bullet[upBullet].conf.conf.pos.y && notes->fPos.y >= g_bullet[numBullet].conf.conf.pos.y)
		{
			//敵にダメージ
			damageEnemy(notes, n, numBullet, upBullet);

			//配列解放
			releaseBulletEffect(g_bullet[numBullet].effectID);
			g_bullet[numBullet].use = false;
			g_bullet[upBullet].use = false;

			return true;
		}
		notes++;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: damageEnemy
//返り値	: 
//説明		: 敵に与えるダメージ決定
//////////////////////////////////////////////////////////////////////////////
void	damageEnemy(NOTES *notes, int numEnemy, int numBullet, int upBullet)
{
	//通常弾だった場合
	if ((g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type == BULLET004) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type == BULLET004))
	{
		//魔法発動エフェクト設定
		//setActivate(D3DXVECTOR3(
		//	notes->fPos.x + notes->fWidth * 0.5f,
		//	notes->fPos.y + notes->fHeight * 0.5f,
		//	0.f),
		//	ACTIVE_001);

		// エフェクト
		SetEffect(notes->fPos.x + notes->fWidth / 2, notes->fPos.y  + notes->fHeight / 2, 200 , LINE_HEIGHT , EFFECT_MAGIC_ON_NORMAL_1);

		//敵に1ダメージ
//		AddDameage(numEnemy, BULLET_DMG);
		StopDamage(numEnemy , BULLET_DMG);
		// 
		PlaySound(SE_GAME_MAGIC_ON);
	}
	//特殊弾だった場合
	else
	{
		//爆発弾
		if (g_bullet[numBullet].type == BULLET002 || g_bullet[upBullet].type == BULLET002)
		{
			//爆発エフェクト
			NOTES *notes = GetNotes();
			//setExplo(
			//	D3DXVECTOR3(
			//		notes[numEnemy].fPos.x + notes[numEnemy].fWidth * 0.5f,
			//		notes[numEnemy].fPos.y + notes[numEnemy].fHeight * 0.5f,
			//		0.f),
			//	BULLET_EXPLO);

			// エフェクト
			SetEffect(notes->fPos.x + notes->fWidth / 2, notes->fPos.y  + notes->fHeight / 2, BULLET_EXPLO , LINE_HEIGHT , EFFECT_MAGIC_ON_EXPLOSION_1);

			//魔法発動エフェクト設定
			//setActivate(D3DXVECTOR3(
			//	notes->fPos.x + notes->fWidth * 0.5f,
			//	notes->fPos.y + notes->fHeight * 0.5f,
			//	0.f),
			//	ACTIVE_001);

			//爆発処理
			bomBullet(GetEnemyPos(numEnemy));
		}

		//拡散弾
		if (g_bullet[numBullet].type == BULLET003)
		{
			diffBullet(numBullet);

			//魔法発動エフェクト設定
			setActivate(D3DXVECTOR3(
				notes->fPos.x + notes->fWidth * 0.5f,
				notes->fPos.y + notes->fHeight * 0.5f,
				0.f),
				ACTIVE_001);

			AddDameage(numEnemy, SPE_BULLET_DMG);
			PlaySound(SE_GAME_MAGIC_ON_DIFISION);
		}
		if (g_bullet[upBullet].type == BULLET003)
		{
			diffBullet(upBullet);

			//魔法発動エフェクト設定
			setActivate(D3DXVECTOR3(
				notes->fPos.x + notes->fWidth * 0.5f,
				notes->fPos.y + notes->fHeight * 0.5f,
				0.f),
				ACTIVE_001);

			AddDameage(numEnemy, SPE_BULLET_DMG);
			PlaySound(SE_GAME_MAGIC_ON_DIFISION);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: checkBoss
//返り値	: 
//説明		: ボスとの当たり判定
//////////////////////////////////////////////////////////////////////////////
bool	checkBoss(float s, float l, int numBullet, int upBullet)
{
	//当たり判定の範囲に核がないか探索
	BOSSNUCLEUS	*nuc;		//ボスの核のポインタ
	nuc = GetNucleusBoss();	//ポインタ取得
	
	for(int i = 0; i < BOSSNUCLEUS_MAX; i++)
	{
		//いたらダメージ
		if (nuc->bDraw == true && nuc->bUse == true &&
			nuc->fPos.x + nuc->fWidth * 0.5f <= l && nuc->fPos.x + nuc->fWidth + 0.5f >= s &&
			nuc->fPos.y <= g_bullet[upBullet].conf.conf.pos.y && nuc->fPos.y >= g_bullet[numBullet].conf.conf.pos.y)
		{
			//ダメージ
			damageBoss(i, numBullet, upBullet);

			//配列解放
			releaseBulletEffect(g_bullet[numBullet].effectID);
			g_bullet[numBullet].use = false;
			g_bullet[upBullet].use = false;

			return true;
		}

		nuc++;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: damageBoss
//返り値	: 
//説明		: ボスにダメージ
//////////////////////////////////////////////////////////////////////////////
void	damageBoss(int numBoss, int numBullet, int upBullet)
{
	//通常弾だった場合
	if ((g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type == BULLET004) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type == BULLET004))
	{
		//敵に1ダメージ
		AddDameageBoss(0, BULLET_DMG);
		PlaySound(SE_GAME_MAGIC_ON);
	}
	//特殊弾だった場合
	else
	{
		//爆発弾
		if (g_bullet[numBullet].type == BULLET002 || g_bullet[upBullet].type == BULLET002)
		{
			//爆発エフェクト
			BOSSNUCLEUS	*nuc = GetNucleusBoss();
			setExplo(D3DXVECTOR3(nuc->fPos.x, nuc->fPos.y, 0.f),BULLET_EXPLO);

			//爆発の処理
			bomBullet(D3DXVECTOR3(
				GetNucleusBoss()->fPos.x,
				GetNucleusBoss()->fPos.y,
				0.f));
			PlaySound(SE_GAME_MAGIC_ON_BOMM);
		}

		//拡散弾
		if (g_bullet[numBullet].type == BULLET003)
		{
			diffBullet(numBullet);
			PlaySound(SE_GAME_MAGIC_ON_DIFISION);
			AddDameageBoss(0, SPE_BULLET_DMG);
		}
		if (g_bullet[upBullet].type == BULLET003)
		{
			diffBullet(upBullet);
			PlaySound(SE_GAME_MAGIC_ON_DIFISION);
			AddDameageBoss(0, SPE_BULLET_DMG);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: checkHuman
//返り値	: 
//説明		: 市民との当たり判定
//////////////////////////////////////////////////////////////////////////////
bool	checkHuman(float s, float l, int numBullet, int upBullet)
{
	//市民の情報取得
	HUMAN	*human = GetHuman();

	for(int i = 0; i < MAX_HUMAN; i++)
	{
		//いたらダメージ
		if (human->bUse == true &&
			human->fPos.x <= l && human->fPos.x >= s &&
			human->fPos.y <= g_bullet[upBullet].conf.conf.pos.y && human->fPos.y >= g_bullet[numBullet].conf.conf.pos.y)
		{
			//敵にダメージ
			damageHuman(human, i, numBullet, upBullet);

			//配列解放
			releaseBulletEffect(g_bullet[numBullet].effectID);
			g_bullet[numBullet].use = false;
			g_bullet[upBullet].use = false;

			return true;
		}
		human++;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: damageHuman
//返り値	: 
//説明		: 市民にダメージ
//////////////////////////////////////////////////////////////////////////////
void	damageHuman(HUMAN *human, int numHuman, int numBullet, int upBullet)
{
	//通常弾だった場合
	if ((g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type == BULLET004) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type == BULLET004))
	{
		//魔法発動エフェクト設定
		setActivate(D3DXVECTOR3(
			human->fPos.x + human->fWidth * 0.5f,
			human->fPos.y + human->fHeight * 0.5f,
			0.f),
			ACTIVE_001);

		//敵に1ダメージ
		AddDameageHuman(numHuman, BULLET_DMG);
	}
	//特殊弾だった場合
	else
	{
		//爆発弾
		if (g_bullet[numBullet].type == BULLET002 || g_bullet[upBullet].type == BULLET002)
		{
			//爆発エフェクト
			HUMAN *human = GetHuman();
			setExplo(
				D3DXVECTOR3(
					human[numHuman].fPos.x + human[numHuman].fWidth * 0.5f,
					human[numHuman].fPos.y + human[numHuman].fHeight * 0.5f,
					0.f),
				BULLET_EXPLO);

			//魔法発動エフェクト設定
			setActivate(D3DXVECTOR3(
				human->fPos.x + human->fWidth * 0.5f,
				human->fPos.y + human->fHeight * 0.5f,
				0.f),
				ACTIVE_001);

			//爆発処理
			bomBullet(GetHumanPos(numHuman));
		}

		//拡散弾
		if (g_bullet[numBullet].type == BULLET003)
		{
			diffBullet(numBullet);

			//魔法発動エフェクト設定
			setActivate(D3DXVECTOR3(
				human->fPos.x + human->fWidth * 0.5f,
				human->fPos.y + human->fHeight * 0.5f,
				0.f),
				ACTIVE_001);

			AddDameageHuman(numHuman, SPE_BULLET_DMG);
		}
		if (g_bullet[upBullet].type == BULLET003)
		{
			diffBullet(upBullet);

			//魔法発動エフェクト設定
			setActivate(D3DXVECTOR3(
				human->fPos.x + human->fWidth * 0.5f,
				human->fPos.y + human->fHeight * 0.5f,
				0.f),
				ACTIVE_001);

			AddDameageHuman(numHuman, SPE_BULLET_DMG);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: checkBossBullet
//返り値	: 
//説明		: ボスの弾との判定
//////////////////////////////////////////////////////////////////////////////
bool	checkBossBullet(float s, float l, int numBullet, int upBullet)
{
	//ボス弾の情報取得
	BOSSBULLET	*bosBlt = GetBulletBoss();

	for (int i = 0; i < MAX_HUMAN; i++)
	{
		//いたらダメージ
		if (bosBlt->bUse == true &&
			bosBlt->fPos.x <= l && bosBlt->fPos.x >= s &&
			bosBlt->fPos.y <= g_bullet[upBullet].conf.conf.pos.y && bosBlt->fPos.y >= g_bullet[numBullet].conf.conf.pos.y)
		{
			//敵にダメージ
			damageBossBullet(bosBlt, i, numBullet, upBullet);

			//配列解放
			releaseBulletEffect(g_bullet[numBullet].effectID);
			g_bullet[numBullet].use = false;
			g_bullet[upBullet].use = false;

			return true;
		}
		bosBlt++;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: damageBossBullet
//返り値	: 
//説明		: 市民にダメージ
//////////////////////////////////////////////////////////////////////////////
void	damageBossBullet(BOSSBULLET *bosBlt, int numBoss, int numBullet, int upBullet)
{
	//通常弾だった場合
	if ((g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type == BULLET004) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type == BULLET004))
	{
		//魔法発動エフェクト設定
		setActivate(D3DXVECTOR3(
			bosBlt->fPos.x,
			bosBlt->fPos.y,
			0.f),
			ACTIVE_001);

		//敵に1ダメージ
		AddDmgBulletBoss(numBoss, SPE_BULLET_DMG);
	}
	//特殊弾だった場合
	else
	{
		//爆発弾
		if (g_bullet[numBullet].type == BULLET002 || g_bullet[upBullet].type == BULLET002)
		{
			//爆発エフェクト
			BOSSBULLET *bosBlt = GetBulletBoss();
			setExplo(
				D3DXVECTOR3(
					bosBlt[numBoss].fPos.x,
					bosBlt[numBoss].fPos.y,
					0.f),
				BULLET_EXPLO);

			//魔法発動エフェクト設定
			setActivate(D3DXVECTOR3(
				bosBlt->fPos.x,
				bosBlt->fPos.y,
				0.f),
				ACTIVE_001);

			//爆発処理 こいつだけ中心を原点にしやがって・・・殺す
			bomBullet(D3DXVECTOR3(
				bosBlt->fPos.x - bosBlt->fWidth * 0.5f,
				bosBlt->fPos.y - bosBlt->fHeight * 0.5f,
				0.f));
		}

		//拡散弾
		if (g_bullet[numBullet].type == BULLET003)
		{
			diffBullet(numBullet);

			//魔法発動エフェクト設定
			setActivate(D3DXVECTOR3(
				bosBlt->fPos.x,
				bosBlt->fPos.y,
				0.f),
				ACTIVE_001);

			AddDmgBulletBoss(numBoss, SPE_BULLET_DMG);
		}
		if (g_bullet[upBullet].type == BULLET003)
		{
			diffBullet(upBullet);

			//魔法発動エフェクト設定
			setActivate(D3DXVECTOR3(
				bosBlt->fPos.x,
				bosBlt->fPos.y,
				0.f),
				ACTIVE_001);

			AddDmgBulletBoss(numBoss, SPE_BULLET_DMG);
		}
	}
}