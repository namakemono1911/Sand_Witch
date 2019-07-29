//============================================
//  Boss�֐�  (Boss.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2017�N05��26��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

//============================================
//
//  �C���N���[�h�t�@�C��
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
//  �萔�錾
//
//============================================
#define BOSS_UV_SPEED                (10)                  // ���t���[����UV�A�j���[�V�������邩
#define BOSS_SPEED_SLOW              (0.5)               // �x���X�s�[�h
#define BOSS_BULLET_TIME 180
#define BOSS_MOVE 30 // �{�X�������Ȃ�����
#define BOSS_NUVLESUS_TIME 120 // �j�������鎞��
#define BOSS_ATTACK_TIME 120 // �{�X����ɓ������čU������Ԋu
#define BOSS_ATTACK 30 // �{�X����ɓ������čU����


// ������
#define BOSS_HEIGHT_1 (SCREEN_HEIGHT / 100.0f * 80)	// ��
#define BOSS_HEIGHT_2 (SCREEN_HEIGHT / 100.0f * 70)	// ��
#define BOSS_HEIGHT_3 (SCREEN_HEIGHT / 100.0f * 70)	// �h���S��

#define BOSS_WIDTH_1 (SCREEN_WIDTH / 100.0f * 30)
#define BOSS_WIDTH_2 (SCREEN_WIDTH / 100.0f * 30)
#define BOSS_WIDTH_3 (SCREEN_WIDTH / 100.0f * 30)

// �{�X�������ꏊ
#define BOSS_CAN_COME_1	(SCREEN_WIDTH / 100.0f * 85.0f)
#define BOSS_CAN_COME_2	(SCREEN_WIDTH / 100.0f * 90.0f)
#define BOSS_CAN_COME_3	(SCREEN_WIDTH / 100.0f * 90.0f)

#define BOSS_HP 20
#//�ǂݍ��ރe�N�X�`���t�@�C����
#define BOSS_ONE_TEXTURENAME       "data/TEXTURE/GAME/BOSS/boss1.png"   // NBOSS_ONE
#define BOSS_TWO_TEXTURENAME       "data/TEXTURE/GAME/BOSS/Boss02.png"   // NBOSS_TWO
#define BOSS_THREE_TEXTURENAME     "data/TEXTURE/GAME/BOSS/Boss03.png"   // NBOSS_THREE

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureBoss[BOSS_MAX] = {};//Boss�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBoss = NULL;//�|�C���^�[!!&������

/*�{�X�\����*/
BOSS g_aBoss[MAX_BOSS];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BOSS_MOTION_MAX 4	// ���[�V�����ő吔 1���[�V�����̒��̃L�[��

static float g_fBossUVSize[3][BOSS_MOTION_MAX][2] = 
{
	{{1.0f / 4.0f, 1.0f / 3.0f} , {1.0f / 2.0f, 1.0f / 3.0f} , {1.0f / 4.0f, 1.0f / 3.0f}, {1.0f / 2.0f, 1.0f / 3.0f}},			// �j���[�g����
	{{1.0f / 4.0f, 2.0f / 3.0f} , {1.0f / 2.0f, 2.0f / 3.0f} , {3.0f / 4.0f, 2.0f / 3.0f}, {1.0f , 2.0f / 3.0f}},				// �U��
	{{1.0f / 4.0f, 1.0f} , {1.0f / 4.0f, 1.0f} , {1.0f / 4.0f, 1.0f}, {1.0f / 4.0f, 1.0f}},										// ����
};

static float g_fBossUV[3][BOSS_MOTION_MAX][2] = 
{
	{{0.0f,0.0f} , {1.0f / 4.0f, 0.0f} , {0.0f, 0.0f}, {1.0f / 4.0f,0.0f}},										// �j���[�g����
	{{0.0f,1.0f / 3.0f} , {1.0f / 4.0f, 1.0f / 3.0f} , {1.0f / 2.0f, 1.0f / 3.0f}, {3.0f / 4.0f,1.0f / 3.0f}},			// �U��
	{{0.0f,2.0f / 3.0f} , {0.0f,2.0f / 3.0f} , {0.0f,2.0f / 3.0f}, {0.0f,2.0f / 3.0f}},							// ����
};

static int g_nBossModeTime[6][BOSS_MOTION_MAX] = 
{
	{30,30,30 , 30},	// �j���[�g����
	{30,30,30,30},	// �U��
	{30,30,30,5}	// ����
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
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexBoss(LPDIRECT3DDEVICE9 pDevice);//���_�̍쐬

//============================================
//
//  ���O  InitBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  Boss�֌W�̏�����
//
//============================================
HRESULT InitBoss(void)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//���_�쐬
	if(FAILED(MakeVertexBoss(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//�e�N�X�`���擾
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , BOSS_ONE_TEXTURENAME , &g_pTextureBoss[0] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSS_ONE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , BOSS_TWO_TEXTURENAME , &g_pTextureBoss[1] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSS_TWO",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , BOSS_THREE_TEXTURENAME , &g_pTextureBoss[2] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSS_THREE",MB_OK | MB_DEFBUTTON1);
		}//EOif


	// �{�X�\���̂̏�����
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
//  ���O  UninitBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  Boss�֌W�̏I������
//
//============================================
void UninitBoss(void)
{
	for(int nCntBoss = 0 ; nCntBoss < BOSS_MAX  ; nCntBoss++)
	{
		//�e�N�X�`���C���^�[�t�F�[�X�̌�Еt��
		SAFE_RELEASE( g_pTextureBoss[nCntBoss] );
	} // EO for

	//���_�o�b�t�@�̌�Еt��
	SAFE_RELEASE( g_pVtxBufferBoss );
}//EOUninitBoss

//============================================
//
//  ���O  UpdateBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  Boss�֌W�̍X�V����
//
//============================================
void UpdateBoss(void)
{
	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo

		//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferBoss -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

	GATE* pGate = GetGate();

	bool bAttack = false;

	// UV�A�j���[�V�����Ń{�X
	for(int nCntBoss = 0 ; nCntBoss < MAX_BOSS ; nCntBoss++)
	{
		// �g�p�`�F�b�N
		if(g_aBoss[nCntBoss].bUse == true)
		{
			g_aBoss[nCntBoss].bMoveFlag = true;

			//���_���W�̐ݒ�(2D���W , �E��� )
			pVtx [ 0 + 4*nCntBoss] . pos = D3DXVECTOR3 (g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f ,
				g_aBoss[nCntBoss].fPos.y  - g_aBoss[nCntBoss].fHeight / 2.0f, 0.0f);
			pVtx [ 1 + 4*nCntBoss] . pos = D3DXVECTOR3 (g_aBoss[nCntBoss].fPos.x + g_aBoss[nCntBoss].fWidth / 2.0f ,
				g_aBoss[nCntBoss].fPos.y - g_aBoss[nCntBoss].fHeight / 2.0f , 0.0f);
			pVtx [ 2 + 4*nCntBoss] . pos = D3DXVECTOR3 (g_aBoss[nCntBoss].fPos.x - g_aBoss[nCntBoss].fWidth / 2.0f ,
				g_aBoss[nCntBoss].fPos.y + g_aBoss[nCntBoss].fHeight / 2.0f, 0.0f);
			pVtx [ 3 + 4*nCntBoss] . pos = D3DXVECTOR3 (g_aBoss[nCntBoss].fPos.x + g_aBoss[nCntBoss].fWidth / 2.0f ,
				g_aBoss[nCntBoss].fPos.y + g_aBoss[nCntBoss].fHeight / 2.0f, 0.0f);

		    //�e���_�̃e�N�X�`�����W�̐ݒ�
			pVtx [ 0 + 4*nCntBoss] . tex = D3DXVECTOR2 (g_fBossUV[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][0] ,
				g_fBossUV[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][1]);

			pVtx [ 1 + 4*nCntBoss] . tex = D3DXVECTOR2 (g_fBossUVSize[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][0]  ,
				g_fBossUV[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][1]);

			pVtx [ 2 + 4*nCntBoss] . tex = D3DXVECTOR2 (g_fBossUV[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][0] ,
				g_fBossUVSize[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][1]);

			pVtx [ 3 + 4*nCntBoss] . tex = D3DXVECTOR2 (g_fBossUVSize[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][0] ,
				g_fBossUVSize[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount][1]);

			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// ���[�V����
			g_aBoss[nCntBoss].nBossModeCount++;


			if(g_aBoss[nCntBoss].nBossModeCount >= g_nBossModeTime[g_aBoss[nCntBoss].nBossMode][g_aBoss[nCntBoss].nBossMotionCount])
			{
				g_aBoss[nCntBoss].nBossModeCount = 0;
				g_aBoss[nCntBoss].nBossMotionCount++;
				if(g_aBoss[nCntBoss].nBossMotionCount >= BOSS_MOTION_MAX)
				{
					// ���[�V�������I�������A�j���[�g�����ɂȂ���
					SetBossMode(nCntBoss , 0);
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// ��̓����蔻��
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
			//  ����UV�A�j���[�V��������Ȃ炱���A�����Q��  //
			//////////////////////////////////////////////////


			// �j�̕\��
		OnDrawNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[0] , 2);
		OnDrawNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[1] , 2);
		OnDrawNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[2] , 2);
		OnDrawNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[3] , 2);

		////////////////////////
			//  �ړ��ʂ̏ꍇ����  //
			////////////////////////
			// ���t���[���̈ړ�   //
			//////////////////////////////////////////////////
			float fWidth = 100.0f;	// �e�̑傫��
			float fHeight = 200.0f;	// �e�̑傫��

			switch(g_aBoss[nCntBoss].nMode)
			{
			case BOSS_ONE:
				// �Ē[�����s���[�V�����Ȃ�����Ȃ�
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

				// �j�̍��W�Z�b�g
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[0] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 60.0f , LINE_ONE + LINE_HEIGHT * 0.45f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[1] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 40.0f , LINE_TWO + LINE_HEIGHT * 0.45f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[2] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x + 30.0f , LINE_ONE + LINE_HEIGHT * 0.45f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[3] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x + 80.0f , LINE_TWO + LINE_HEIGHT * 0.45f));

				// �{�X������ȏ�s�����Ȃ�
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

				// �j�̍��W�Z�b�g
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[0] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_ONE + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[1] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_TWO + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[2] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_THREE + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[3] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_FOUR + LINE_HEIGHT * 0.5f));

				// �{�X������ȏ�s�����Ȃ�
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

				// �j�̍��W�Z�b�g
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[0] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_ONE + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[1] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_TWO + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[2] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_THREE + LINE_HEIGHT * 0.5f));
				SetPosNucleusBoss(g_aBoss[nCntBoss].nNumNucleus[3] , D3DXVECTOR2( g_aBoss[nCntBoss].fPos.x - 130.0f , LINE_FOUR + LINE_HEIGHT * 0.5f));

				// �{�X������ȏ�s�����Ȃ�
				if(g_aBoss[nCntBoss].fPos.x <= BOSS_CAN_COME_3)
				{
					g_aBoss[nCntBoss].fPos.x = BOSS_CAN_COME_3;
				}
				break;
			} // EO switch
			//////////////////////////////////////////////////

			////////////////////
			// �Ǘ���������� //
			//////////////////////////////////////////////////
			if(g_aBoss[nCntBoss].fPos.x + g_aBoss[nCntBoss].fWidth <= 0)
			{
				// ���C�t0�ɂ�����
				g_aBoss[nCntBoss].bUse = false;

				AddDamegeCastle(300);

			} // EO if
			//////////////////////////////////////////////////

			////////////////////////
			// ��U���^�C���̏��� //
			//////////////////////////////////////////////////
			if(g_aBoss[nCntBoss].bAttack == true)
			{
				// ���C�t0�ɂ�����
				g_aBoss[nCntBoss].nCntDamegeTime++;

				if(g_aBoss[nCntBoss].nCntDamegeTime >= 120 )
				{
					g_aBoss[nCntBoss].bAttack = false;
					g_aBoss[nCntBoss].nCntDamegeTime = 0;
				} // EO if
			} // EO if
			//////////////////////////////////////////////////

			//////////////////////////
			// �̗͂Ȃ��Ȃ����甚�� //
			//////////////////////////////////////////////////
			if(g_aBoss[nCntBoss].nLife <= 0)
			{
				// ���C�t0�ɂ�����
				g_aBoss[nCntBoss].bUse = false;

			} // EO if
			//////////////////////////////////////////////////

			// �̗�
			SetPosHeart(g_aBoss[nCntBoss].nNumHeart , D3DXVECTOR2(g_aBoss[nCntBoss].fPos.x - 100 , g_aBoss[nCntBoss].fPos.y));
			SetUVSizeHeart(g_aBoss[nCntBoss].nNumHeart , g_aBoss[nCntBoss].nLife);

			// �̗͂ɂ���ĐԂ��Ȃ�
			float x = (float)g_aBoss[nCntBoss].nLife / (float)BOSS_HP;
			pVtx[0 + 4 * nCntBoss].color = D3DXCOLOR(1.0f , 1.0f * x , 1.0f * x , 1.0f);
			pVtx[1 + 4 * nCntBoss].color = D3DXCOLOR(1.0f , 1.0f * x , 1.0f * x , 1.0f);
			pVtx[2 + 4 * nCntBoss].color = D3DXCOLOR(1.0f , 1.0f * x , 1.0f * x , 1.0f);
			pVtx[3 + 4 * nCntBoss].color = D3DXCOLOR(1.0f , 1.0f * x , 1.0f * x , 1.0f);

		} // EO if
	} // EO for

	g_pVtxBufferBoss->Unlock ();												//���b�N����

}//EOUpdateBoss

//============================================
//
//  ���O  DrawBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  Boss�֌W�̕`�揈��
//
//============================================
void DrawBoss(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�p�C�v���C���̐ݒ�
	pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
						g_pVtxBufferBoss ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
						0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
						sizeof(VERTEX2D) );//�X�g���C�h��(��̒P�ʂ̑傫��)

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// �ő吔�`�F�b�N
	for(int nCntBoss = 0 ; nCntBoss < MAX_BOSS ; nCntBoss++)
	{
		if(g_aBoss[nCntBoss].bUse == true)
		{
			if(g_aBoss[nCntBoss].bDrawFlag == true)
			{
				// ��ނŕ�����
				switch(g_aBoss[nCntBoss].nMode)
				{
				case BOSS_ONE:

					//Boss�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureBoss[0] );

					break;
				case BOSS_TWO:

					//Boss�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureBoss[1] );

					break;
				case BOSS_THREE:

					//Boss�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureBoss[2] );

					break;
				} // EO switch

				//�v���~�e�B�u�̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
					nCntBoss * 4 ,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
					NUM_POLYGON );//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B
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
//  ���O  MakeVertexBoss�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexBoss(LPDIRECT3DDEVICE9 pDevice)
{

	//���_�o�b�t�@�쐬
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_BOSS,//�쐬���������_�o�b�t�@�̃T�C�Y = 1�̒��_�̃T�C�Y * ���_��
																	//�ǂꂭ�炢�������ق������A�������߂�����ӂ₷��Ł[�[�[
			D3DUSAGE_WRITEONLY,									//���_�o�b�t�@�̎g�p���@�A�������ݐ�p�Ȃ̂ŁA���炭�ő�
			FVF_VERTEX_2D,										//NULL��0�ł����v�A�}�i�[�I�ɂ͏�������B���̃o�b�t�@�̒��_�t�H�[�}�b�g��₤
			D3DPOOL_MANAGED,									//�������Ǘ��ǂ�����ݒ�A���̏�Ԃ̓f�o�C�X�ɂ��C��
			&g_pVtxBufferBoss,						//�o���オ�������_�o�b�t�@���Ǘ�����A�h���X
			NULL)												//�䂾�����NULL
	))
	{
		return E_FAIL;
	}


	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferBoss -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

		// �ő吔��
	for(int nCntBoss = 0 ; nCntBoss < MAX_BOSS ; nCntBoss++)
	{
		//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
		pVtx[0 + 4 * nCntBoss].rhw = 1.0f;
		pVtx[1 + 4 * nCntBoss].rhw = 1.0f;
		pVtx[2 + 4 * nCntBoss].rhw = 1.0f;
		pVtx[3 + 4 * nCntBoss].rhw = 1.0f;

		//���_�J���[(0�`255�̐����l)
		pVtx[0 + 4 * nCntBoss].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntBoss].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntBoss].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntBoss].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//�����A�����b�N
	g_pVtxBufferBoss -> Unlock();

	return S_OK;

}//EOMakeVertexBoss

//============================================
//
//  ���O  SetBoss�֐�
//  ����	void
//  �߂�l  float fPosX ,float fPosY,float fWidth,float fHeught,Boss_MODE nMode
//  ����  �{�X���Z�b�g
//
//============================================
void    SetBoss    (float fPosX , // ���S���WX
float fPosY ,
BOSS_MODE nMode			   // ���
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

				// ������
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
//  ���O  GetBoss�֐�
//  ����	void
//  �߂�l  BOSS *g_aBoss[0]
//  ����  g_aBoss�̐擪�A�h���X��n��
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

