/*****************************************************************************
bullet.cpp
Aythor	: ���@��
Data	: 2017_04_13
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
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
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define	BULLET_MAX			(100)		//�e�̍ő吔
#define BULLET_CONF			"data/conf/bulletConf"	//�e�̃R���t�B�O

#define BULLET_COUNT		(30)		//���̒e���˂܂ł̎���
#define SPE_BULLET_COUNT	(300)		//����e�̃N�[���^�C��

#define BULLET_EXPLO		(600)		//�����̗L���͈�
#define BULLET_DIFF			(700)		//�g�U�͈�

#define BULLET_DMG			(1)			//�ʏ�e�̈З�
#define SPE_BULLET_DMG		(3)			//����e�̈З�

#define DIFF_BULLET_MIN		(3)			//�g�U����e�̉���
#define DIFF_BULLET_MAX		(10)			//�g�U����e�̏��

#define CHALLENGE			(100)			//�`�������W��
#define ANIME_FRAME			(15)		//30fps�ōX�V
#define ERO					(1)			//���˕Ԃ�萔

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON		conf;	//�摜�̐ݒ�
	TEXTURE			tex;	//�e�N�X�`���̐ݒ�
	float			move;	//�ړ��l
	BULLET_TYPE		type;	//�e�̎��
	int				anime;	//�e�N�X�`���A�j���[�V�����̃t���[��
	float			mass;	//����
	int				effectID;//�G�t�F�N�g�z��ԍ�
	bool			use;	//�g�p�t���O
	bool			active;	//���@���������Ă邩
}BULLET;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
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
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureBullet[BULLET_TYPE_MAX] = {};		//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBullet = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

BULLET	g_bullet[BULLET_MAX];			//�e�̐ݒ�
char	*bulletTexName[]	=			//�e�N�X�`���̖��O
{
	"data/TEXTURE/GAME/BULLET/magic0002-1.png",
	"data/TEXTURE/GAME/BULLET/magic0001-2.png",
	"data/TEXTURE/GAME/BULLET/bakuhatu3.png",
	"data/TEXTURE/GAME/BULLET/bullet05.png",
	"data/TEXTURE/GAME/BULLET/kakusan.png",
};

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initBullet
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initBullet ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾
	int		i;		//loop

	//�\���̏�����
	for(i = 0; i < BULLET_MAX; i++)
	{
		//�e�N�X�`��������
		g_bullet[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
		g_bullet[i].tex.size = D3DXVECTOR2(1.f, 1.f);
		g_bullet[i].use = false;
		g_bullet[i].active = false;
	}

	//�e�N�X�`���̓ǂݍ���
	for(i = 0; i < BULLET_TYPE_MAX; i++)
	{
		if(FAILED(D3DXCreateTextureFromFile(pDevice, bulletTexName[i], &g_pTextureBullet[i])))
		{
			MessageBox(NULL, "bullet", "�G���[", MB_OK);
		}
	}

	//�f�o�C�X�擾
	makeVertexBullet(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitBullet
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitBullet ( void )
{
	//�ϐ��錾
	int		i;		//loop

	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	for(i = 0; i < BULLET_TYPE_MAX; i++)
	{
		if(g_pTextureBullet[i] != NULL)
		{
			g_pTextureBullet[i]->Release();
			g_pTextureBullet[i] = NULL;
		}
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferBullet != NULL)
	{
		g_pVtxBufferBullet->Release();
		g_pVtxBufferBullet = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateBullet
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateBullet ( void )
{
	//�ϐ��錾
	VERTEX2D	*pVtx;

	//=============================
	//�e�̏��X�V
	//=============================
	for(int i = 0; i < BULLET_MAX; i++)
	{
		//�e���g���Ă�����X�V
		if(g_bullet[i].use == true)
		{
			//�e�ړ�
			g_bullet[i].conf.conf.pos.x += g_bullet[i].move;

			//�e�N�X�`���A�j��
			g_bullet[i].anime = (g_bullet[i].anime + 1) % 60;
			if(g_bullet[i].anime % (60 / ANIME_FRAME) == 0)
			{
				g_bullet[i].tex.pos.x += g_bullet[i].tex.size.x;
				g_bullet[i].tex.pos.x = fmod(g_bullet[i].tex.pos.x, 1);
			}

			//�e����ʊO�ɏo����폜
			if (g_bullet[i].conf.conf.pos.x - g_bullet[i].conf.conf.size.x >= SCREEN_WIDTH ||
				g_bullet[i].conf.conf.pos.x + g_bullet[i].conf.conf.size.x <= 100)
			{
				g_bullet[i].use = false;
				resetCombo();
			}
		}
	}

	//=============================
	//�����蔻�� 
	//=============================
	for(int i = 0; i < BULLET_MAX; i++)
	{
		//�e���g���Ă���Δ���
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
	//�o�b�t�@�o�^
	//=============================
	g_pVtxBufferBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < BULLET_MAX; i++)
	{
		if(g_bullet[i].use == true)
		{
			//���W�X�V
			setRotBuffer(pVtx, g_bullet[i].conf);

			//�e�N�X�`���X�V
			setTexture(pVtx, g_bullet[i].tex);
		}

		//�|�C���^�ړ�
		pVtx += 4;
	}

	g_pVtxBufferBullet->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawBullet
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawBullet ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	int		i;		//loop

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferBullet, 0, sizeof(VERTEX2D));

	//�|���S���̕`��
	for(i = 0; i < BULLET_MAX; i++)
	{
		if(g_bullet[i].use == true)
		{
			//�e�N�X�`���ǂݍ���
			pDevice->SetTexture(0,g_pTextureBullet[g_bullet[i].type]);

			pDevice->DrawPrimitive
				(
				D3DPT_TRIANGLESTRIP,	//�|���S���̎��
				NUM_VERTEX * i,			//�I�t�Z�b�g(���_��)
				NUM_POLYGON				//�|���S���̐�
				);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexBullet
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBullet ( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^
	int		i;		//loop

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VERTEX * BULLET_MAX,		//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//�������Ǘ����@
			&g_pVtxBufferBullet,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	g_pVtxBufferBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < BULLET_MAX * NUM_VERTEX; i++)
	{
		//rhw�̐ݒ�(�K��1.0f)
		pVtx->rhw = 1.f;

		//���_�J���[�̐ݒ�(0~155�̐����l)
		pVtx->color = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx++;
	}

	g_pVtxBufferBullet->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBullet
//�Ԃ�l	: 
//����		: �e�ݒ�
//////////////////////////////////////////////////////////////////////////////
void	setBullet	( D3DXVECTOR3 pos, BULLET_TYPE type )
{
	//�ϐ��錾
	int		i;				//loop

	//�J�E���g�_�E�����Ȃ甭�˕s��
	if ((getBulletCoolTime(0) > 0 && type <= BULLET001) || (getBulletCoolTime(1) > 0 && (type == BULLET002 || type == BULLET003)))
	{
		return;
	}
	//�ʏ�e
	else if(type <= BULLET001)
	{
		setBulletUICoolTime(0, BULLET_COUNT);
	}
	//����e
	else if(type >= BULLET002 &&  type <= BULLET003)
	{
		setBulletUICoolTime(1, SPE_BULLET_COUNT);
	}

	//���g�p�̒e�T��
	for (i = 0; i < BULLET_MAX; i++)
	{
		//�g���Ă��Ȃ���Βe�Z�b�g
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

			//���ˉ�
			switch(type)
			{
			case	BULLET000:	// �ʏ�
				PlaySound(SE_GAME_MAGIC_GO);
				break;
			case	BULLET001 :
				PlaySound(SE_GAME_MAGIC_GO);
				break;
			case	BULLET002 :	// ����
				PlaySound(SE_GAME_MAGIC_GO_BOMM);
				break;
			case	BULLET003 :	// �g�U
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
//�֐���	: sandBullet
//�Ԃ�l	: �e���d�Ȃ��Ă���� true
//����		: �G�Ƃ̓����蔻��
//////////////////////////////////////////////////////////////////////////////
bool	sandBullet	(int numBullet)
{
	//i�Ԗڂ̒e�̈��̃��[���̒e�T��
	for(int j = 0; j < BULLET_MAX; j++)
	{
		//���ɒe�����邩����
		if( numBullet != j && g_bullet[j].use == true && g_bullet[numBullet].type != g_bullet[j].type &&
			g_bullet[numBullet].conf.conf.pos.y < g_bullet[j].conf.conf.pos.y &&
			g_bullet[numBullet].conf.conf.pos.y + SCREEN_HEIGHT / 5 > g_bullet[j].conf.conf.pos.y)
		{
			//�d�Ȃ��Ă邩����
			if( g_bullet[numBullet].conf.conf.pos.x + g_bullet[numBullet].conf.conf.size.x * 0.5f >= g_bullet[j].conf.conf.pos.x - g_bullet[j].conf.conf.size.x * 0.5f &&
				g_bullet[numBullet].conf.conf.pos.x - g_bullet[numBullet].conf.conf.size.x * 0.5f <= g_bullet[j].conf.conf.pos.x + g_bullet[j].conf.conf.size.x * 0.5f)
			{
				//���W���\�[�g���ē����蔻��쐬
				float sort[LINE_OBJ_MAX];
				sortBullet(sort, numBullet, j);

				//�d�Ȃ��������ɃG�t�F�N�g�ݒ�
				if(g_bullet[numBullet].active == false)
				{
					//�G�t�F�N�g�ݒ�
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

				//�G�Ƃ̓����蔻��
				if (true == checkEnemy(sort[2], sort[1], numBullet, j) ||		//�G�Ƃ̓����蔻��
					true == checkBoss(sort[2], sort[1], numBullet, j) ||		//�{�X�Ƃ̓����蔻��
					true == checkBossBullet(sort[2], sort[1], numBullet, j))	//�{�X�e�Ƃ̓����蔻��
				{
					if (true == g_bullet[j].active)
					{
						releaseBulletEffect(g_bullet[j].effectID);
						g_bullet[j].active = false;
					}

					addCombo();		//�R���{���Z
					return true;
				}
				if (true == checkHuman(sort[2], sort[1], numBullet, j))		//�s���Ƃ̓����蔻��
				{
					if (true == g_bullet[j].active)
					{
						releaseBulletEffect(g_bullet[j].effectID);
						g_bullet[j].active = false;
					}
					resetCombo();	//�R���{���Z�b�g
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
//�֐���	: sortBullet
//�Ԃ�l	: 
//����		: �����o�u���\�[�g
//////////////////////////////////////////////////////////////////////////////
void	sortBullet	(float *sort, int numBullet, int upBullet)
{
	float	work;					//�Ҕ���

	//�d�Ȃ��Ă�͈͂ōX�ɓ����蔻��
	sort[0] = g_bullet[numBullet].conf.conf.pos.x + g_bullet[numBullet].conf.conf.size.x * 0.5f;
	sort[1] = g_bullet[numBullet].conf.conf.pos.x - g_bullet[numBullet].conf.conf.size.x * 0.5f;
	sort[2] = g_bullet[upBullet].conf.conf.pos.x + g_bullet[upBullet].conf.conf.size.x * 0.5f;
	sort[3] = g_bullet[upBullet].conf.conf.pos.x - g_bullet[upBullet].conf.conf.size.x * 0.5f;

	//�\�[�g���Ĕz��2��3���͈͂ɂȂ�
	for(int k = 0; k < LINE_OBJ_MAX; k++)
	{
		for(int l = 0; l < LINE_OBJ_MAX; l++)
		{
			if(sort[l] < sort[l + 1])
			{
				work = sort[l];			//��U�ޔ�
				sort[l] = sort[l + 1];	//������
				sort[l + 1] = work;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: addBullet
//�Ԃ�l	: 
//����		: �������[���̒e�����������獇��
//////////////////////////////////////////////////////////////////////////////
void	addBullet	(int numBullet, int upBullet)
{
	//�������[���̒e������
	if( numBullet != upBullet && g_bullet[numBullet].use == true &&
		g_bullet[numBullet].conf.conf.pos.y + g_bullet[numBullet].conf.conf.size.y * 0.5f > g_bullet[upBullet].conf.conf.pos.y &&
		g_bullet[numBullet].conf.conf.pos.y - g_bullet[numBullet].conf.conf.size.y * 0.5f < g_bullet[upBullet].conf.conf.pos.y)
	{
		//�E�ׂ̒e�Əd�Ȃ��Ă邩����
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

			float	move[2];	//�ޔ�pmove

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
//�֐���	: bomBullet
//�Ԃ�l	: 
//����		: �����e���y�􂵂����̏���
//////////////////////////////////////////////////////////////////////////////
void	bomBullet	(D3DXVECTOR3 pos)
{
	//�G�Ƃ̔���
	for(int i = 0; i < MAX_NOTES; i++)
	{
		//�������[���ɂ��邩�덷���l�����ĒT��
		if(GetEnemyPos(i).y >= pos.y - 1 && GetEnemyPos(i).y <= pos.y + 1)
		{
			//�����͈͓��Ȃ�_���[�W
			if (GetEnemyPos(i).x >= pos.x - BULLET_EXPLO * 0.5f &&
				GetEnemyPos(i).x <= pos.x + BULLET_EXPLO * 0.5f)
			{
//				AddDameage(i, SPE_BULLET_DMG);
				StopDamage(i , SPE_BULLET_DMG);

			}
		}
	}

	//�{�X�Ƃ̔���
	BOSSNUCLEUS	*nuc = GetNucleusBoss();
	if(nuc->bUse == true && nuc->fPos.y >= pos.y - 1 && nuc->fPos.y <= pos.y + 1)
	{
		//�����͈͓��Ȃ�_���[�W
		if (nuc->fPos.x >= pos.x - BULLET_EXPLO * 0.5f &&
			nuc->fPos.x <= pos.x + BULLET_EXPLO * 0.5f)
		{
			AddDameageBoss(0, SPE_BULLET_DMG);
		}
	}

	//�s���Ƃ̔���
	HUMAN	*human = GetHuman();
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		if (human->bUse == true && human->fPos.y >= pos.y - 1 && human->fPos.y <= pos.y + 1)
		{
			//�����͈͓��Ȃ�_���[�W
			if (human->fPos.x >= pos.x - BULLET_EXPLO * 0.5f &&
				human->fPos.x <= pos.x + BULLET_EXPLO * 0.5f)
			{
				AddDameageHuman(i, SPE_BULLET_DMG);
			}
		}

		human++;
	}
	
	//�{�X�e�Ƃ̔���
	BOSSBULLET	*bosBlt = GetBulletBoss();
	for(int i = 0; i < MAX_BOSSBULLET; i++)
	{
		if (bosBlt->bUse == true && bosBlt->fPos.y - bosBlt->fHeight * 0.5f >= pos.y - 1 && bosBlt->fPos.y - bosBlt->fHeight * 0.5f <= pos.y + 1)
		{
			//�����͈͓��Ȃ�_���[�W
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
//�֐���	: diffBullet
//�Ԃ�l	: 
//����		: �g�U�e���y�􂵂����̏���
//////////////////////////////////////////////////////////////////////////////
void	diffBullet	( UINT numBullet )
{
	//�ϐ��錾
	int			num;			//�����g�U����邩
	int			buf[5] = {0};	//�o�b�t�@
	float		work;			//���[�N
	int			j = 0;			//�`�������W�J�E���g

	//�g�U���ݒ�1�`5��
	num = (rand() % (DIFF_BULLET_MAX - DIFF_BULLET_MIN)) + DIFF_BULLET_MIN;

	for(int i = 0; i < num; )
	{
		work = abs((rand() * rand() * rand())) % (SCREEN_WIDTH - (int)POSX) + POSX;

		switch(rand() % 5)
		{
		case 0:
			//�`�������W1�N��
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

			//�e����
			setBullet(
				D3DXVECTOR3(work, PLAYER_POS_1, 0.f),
				BULLET004);

			buf[0]++;
			i++;
			j = 0;
			continue;

		case 1:
				//�`�������W1�N��
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

				//�e����
				setBullet(
					D3DXVECTOR3(work, PLAYER_POS_2, 0.f),
					BULLET004);

				buf[1]++;
				i++;
			continue;

		case 2:
				//�`�������W1�N��
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

				//�e����
				setBullet(
					D3DXVECTOR3(work, PLAYER_POS_2, 0.f),
					BULLET004);

				buf[1]++;
				i++;
				continue;

		case 3:
				//�`�������W1�N��
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

				//�e����
				setBullet(
					D3DXVECTOR3(work, PLAYER_POS_4, 0.f),
					BULLET004);

				buf[3]++;
				i++;
			continue;

		case 4:
				//�`�������W1�N��
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

				//�e����
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
//�֐���	: checkOverlapBullet
//�Ԃ�l	: �d�Ȃ��Ă���true
//����		: �������ꂽ�e���d�Ȃ��Ă��Ȃ����`�F�b�N
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
//�֐���	: checkEnemy
//�Ԃ�l	: �G�Əd�Ȃ��Ă���true
//����		: �G�Ɠ������Ă邩����
//////////////////////////////////////////////////////////////////////////////
bool	checkEnemy(float s, float l, int numBullet, int upBullet)
{
	//�����蔻��͈̔͂ɓG���Ȃ����T��
	NOTES	*notes;		//�G�̃|�C���^
	notes = GetNotes();	//�|�C���^�擾
	for (int n = 0; n < MAX_NOTES; n++)
	{
		//������_���[�W
		if (notes->bUse == true &&
			notes->fPos.x <= l && notes->fPos.x >= s &&
			notes->fPos.y <= g_bullet[upBullet].conf.conf.pos.y && notes->fPos.y >= g_bullet[numBullet].conf.conf.pos.y)
		{
			//�G�Ƀ_���[�W
			damageEnemy(notes, n, numBullet, upBullet);

			//�z����
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
//�֐���	: damageEnemy
//�Ԃ�l	: 
//����		: �G�ɗ^����_���[�W����
//////////////////////////////////////////////////////////////////////////////
void	damageEnemy(NOTES *notes, int numEnemy, int numBullet, int upBullet)
{
	//�ʏ�e�������ꍇ
	if ((g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type == BULLET004) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type == BULLET004))
	{
		//���@�����G�t�F�N�g�ݒ�
		//setActivate(D3DXVECTOR3(
		//	notes->fPos.x + notes->fWidth * 0.5f,
		//	notes->fPos.y + notes->fHeight * 0.5f,
		//	0.f),
		//	ACTIVE_001);

		// �G�t�F�N�g
		SetEffect(notes->fPos.x + notes->fWidth / 2, notes->fPos.y  + notes->fHeight / 2, 200 , LINE_HEIGHT , EFFECT_MAGIC_ON_NORMAL_1);

		//�G��1�_���[�W
//		AddDameage(numEnemy, BULLET_DMG);
		StopDamage(numEnemy , BULLET_DMG);
		// 
		PlaySound(SE_GAME_MAGIC_ON);
	}
	//����e�������ꍇ
	else
	{
		//�����e
		if (g_bullet[numBullet].type == BULLET002 || g_bullet[upBullet].type == BULLET002)
		{
			//�����G�t�F�N�g
			NOTES *notes = GetNotes();
			//setExplo(
			//	D3DXVECTOR3(
			//		notes[numEnemy].fPos.x + notes[numEnemy].fWidth * 0.5f,
			//		notes[numEnemy].fPos.y + notes[numEnemy].fHeight * 0.5f,
			//		0.f),
			//	BULLET_EXPLO);

			// �G�t�F�N�g
			SetEffect(notes->fPos.x + notes->fWidth / 2, notes->fPos.y  + notes->fHeight / 2, BULLET_EXPLO , LINE_HEIGHT , EFFECT_MAGIC_ON_EXPLOSION_1);

			//���@�����G�t�F�N�g�ݒ�
			//setActivate(D3DXVECTOR3(
			//	notes->fPos.x + notes->fWidth * 0.5f,
			//	notes->fPos.y + notes->fHeight * 0.5f,
			//	0.f),
			//	ACTIVE_001);

			//��������
			bomBullet(GetEnemyPos(numEnemy));
		}

		//�g�U�e
		if (g_bullet[numBullet].type == BULLET003)
		{
			diffBullet(numBullet);

			//���@�����G�t�F�N�g�ݒ�
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

			//���@�����G�t�F�N�g�ݒ�
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
//�֐���	: checkBoss
//�Ԃ�l	: 
//����		: �{�X�Ƃ̓����蔻��
//////////////////////////////////////////////////////////////////////////////
bool	checkBoss(float s, float l, int numBullet, int upBullet)
{
	//�����蔻��͈̔͂Ɋj���Ȃ����T��
	BOSSNUCLEUS	*nuc;		//�{�X�̊j�̃|�C���^
	nuc = GetNucleusBoss();	//�|�C���^�擾
	
	for(int i = 0; i < BOSSNUCLEUS_MAX; i++)
	{
		//������_���[�W
		if (nuc->bDraw == true && nuc->bUse == true &&
			nuc->fPos.x + nuc->fWidth * 0.5f <= l && nuc->fPos.x + nuc->fWidth + 0.5f >= s &&
			nuc->fPos.y <= g_bullet[upBullet].conf.conf.pos.y && nuc->fPos.y >= g_bullet[numBullet].conf.conf.pos.y)
		{
			//�_���[�W
			damageBoss(i, numBullet, upBullet);

			//�z����
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
//�֐���	: damageBoss
//�Ԃ�l	: 
//����		: �{�X�Ƀ_���[�W
//////////////////////////////////////////////////////////////////////////////
void	damageBoss(int numBoss, int numBullet, int upBullet)
{
	//�ʏ�e�������ꍇ
	if ((g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type == BULLET004) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type == BULLET004))
	{
		//�G��1�_���[�W
		AddDameageBoss(0, BULLET_DMG);
		PlaySound(SE_GAME_MAGIC_ON);
	}
	//����e�������ꍇ
	else
	{
		//�����e
		if (g_bullet[numBullet].type == BULLET002 || g_bullet[upBullet].type == BULLET002)
		{
			//�����G�t�F�N�g
			BOSSNUCLEUS	*nuc = GetNucleusBoss();
			setExplo(D3DXVECTOR3(nuc->fPos.x, nuc->fPos.y, 0.f),BULLET_EXPLO);

			//�����̏���
			bomBullet(D3DXVECTOR3(
				GetNucleusBoss()->fPos.x,
				GetNucleusBoss()->fPos.y,
				0.f));
			PlaySound(SE_GAME_MAGIC_ON_BOMM);
		}

		//�g�U�e
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
//�֐���	: checkHuman
//�Ԃ�l	: 
//����		: �s���Ƃ̓����蔻��
//////////////////////////////////////////////////////////////////////////////
bool	checkHuman(float s, float l, int numBullet, int upBullet)
{
	//�s���̏��擾
	HUMAN	*human = GetHuman();

	for(int i = 0; i < MAX_HUMAN; i++)
	{
		//������_���[�W
		if (human->bUse == true &&
			human->fPos.x <= l && human->fPos.x >= s &&
			human->fPos.y <= g_bullet[upBullet].conf.conf.pos.y && human->fPos.y >= g_bullet[numBullet].conf.conf.pos.y)
		{
			//�G�Ƀ_���[�W
			damageHuman(human, i, numBullet, upBullet);

			//�z����
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
//�֐���	: damageHuman
//�Ԃ�l	: 
//����		: �s���Ƀ_���[�W
//////////////////////////////////////////////////////////////////////////////
void	damageHuman(HUMAN *human, int numHuman, int numBullet, int upBullet)
{
	//�ʏ�e�������ꍇ
	if ((g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type == BULLET004) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type == BULLET004))
	{
		//���@�����G�t�F�N�g�ݒ�
		setActivate(D3DXVECTOR3(
			human->fPos.x + human->fWidth * 0.5f,
			human->fPos.y + human->fHeight * 0.5f,
			0.f),
			ACTIVE_001);

		//�G��1�_���[�W
		AddDameageHuman(numHuman, BULLET_DMG);
	}
	//����e�������ꍇ
	else
	{
		//�����e
		if (g_bullet[numBullet].type == BULLET002 || g_bullet[upBullet].type == BULLET002)
		{
			//�����G�t�F�N�g
			HUMAN *human = GetHuman();
			setExplo(
				D3DXVECTOR3(
					human[numHuman].fPos.x + human[numHuman].fWidth * 0.5f,
					human[numHuman].fPos.y + human[numHuman].fHeight * 0.5f,
					0.f),
				BULLET_EXPLO);

			//���@�����G�t�F�N�g�ݒ�
			setActivate(D3DXVECTOR3(
				human->fPos.x + human->fWidth * 0.5f,
				human->fPos.y + human->fHeight * 0.5f,
				0.f),
				ACTIVE_001);

			//��������
			bomBullet(GetHumanPos(numHuman));
		}

		//�g�U�e
		if (g_bullet[numBullet].type == BULLET003)
		{
			diffBullet(numBullet);

			//���@�����G�t�F�N�g�ݒ�
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

			//���@�����G�t�F�N�g�ݒ�
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
//�֐���	: checkBossBullet
//�Ԃ�l	: 
//����		: �{�X�̒e�Ƃ̔���
//////////////////////////////////////////////////////////////////////////////
bool	checkBossBullet(float s, float l, int numBullet, int upBullet)
{
	//�{�X�e�̏��擾
	BOSSBULLET	*bosBlt = GetBulletBoss();

	for (int i = 0; i < MAX_HUMAN; i++)
	{
		//������_���[�W
		if (bosBlt->bUse == true &&
			bosBlt->fPos.x <= l && bosBlt->fPos.x >= s &&
			bosBlt->fPos.y <= g_bullet[upBullet].conf.conf.pos.y && bosBlt->fPos.y >= g_bullet[numBullet].conf.conf.pos.y)
		{
			//�G�Ƀ_���[�W
			damageBossBullet(bosBlt, i, numBullet, upBullet);

			//�z����
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
//�֐���	: damageBossBullet
//�Ԃ�l	: 
//����		: �s���Ƀ_���[�W
//////////////////////////////////////////////////////////////////////////////
void	damageBossBullet(BOSSBULLET *bosBlt, int numBoss, int numBullet, int upBullet)
{
	//�ʏ�e�������ꍇ
	if ((g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type == BULLET004) ||
		(g_bullet[numBullet].type == BULLET004 && g_bullet[upBullet].type <= BULLET001) ||
		(g_bullet[numBullet].type <= BULLET001 && g_bullet[upBullet].type == BULLET004))
	{
		//���@�����G�t�F�N�g�ݒ�
		setActivate(D3DXVECTOR3(
			bosBlt->fPos.x,
			bosBlt->fPos.y,
			0.f),
			ACTIVE_001);

		//�G��1�_���[�W
		AddDmgBulletBoss(numBoss, SPE_BULLET_DMG);
	}
	//����e�������ꍇ
	else
	{
		//�����e
		if (g_bullet[numBullet].type == BULLET002 || g_bullet[upBullet].type == BULLET002)
		{
			//�����G�t�F�N�g
			BOSSBULLET *bosBlt = GetBulletBoss();
			setExplo(
				D3DXVECTOR3(
					bosBlt[numBoss].fPos.x,
					bosBlt[numBoss].fPos.y,
					0.f),
				BULLET_EXPLO);

			//���@�����G�t�F�N�g�ݒ�
			setActivate(D3DXVECTOR3(
				bosBlt->fPos.x,
				bosBlt->fPos.y,
				0.f),
				ACTIVE_001);

			//�������� �����������S�����_�ɂ��₪���āE�E�E�E��
			bomBullet(D3DXVECTOR3(
				bosBlt->fPos.x - bosBlt->fWidth * 0.5f,
				bosBlt->fPos.y - bosBlt->fHeight * 0.5f,
				0.f));
		}

		//�g�U�e
		if (g_bullet[numBullet].type == BULLET003)
		{
			diffBullet(numBullet);

			//���@�����G�t�F�N�g�ݒ�
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

			//���@�����G�t�F�N�g�ݒ�
			setActivate(D3DXVECTOR3(
				bosBlt->fPos.x,
				bosBlt->fPos.y,
				0.f),
				ACTIVE_001);

			AddDmgBulletBoss(numBoss, SPE_BULLET_DMG);
		}
	}
}