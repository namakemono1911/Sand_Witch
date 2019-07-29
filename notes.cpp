//============================================
//  Notes�֐�  (Notes.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
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
//  �萔�錾
//
//============================================
#define NOTES_UV_SPEED                (5)						// ���t���[����UV�A�j���[�V�������邩
#define NOTES_U_WIDTH                 (0.5f)					// U��
#define NOTES_V_HEIGHT                (1.0f)					// V����
#define NOTES_POINT_TYPE_ONE          (5)						// �U����1 �X���C��
#define NOTES_POINT_TYPE_FOUR         (5)						// �U����2 �S�[����
#define NOTES_POINT_TYPE_FIVE         (5)						// �U����3 �p���T�[
#define NOTES_ATTACK_TIME             (120)						// �U���Ԋu

#define NOTES_SPEED_SLOW              (1.0f)					// �x���X�s�[�h
#define NOTES_SPEED_NORMAL            (5.0f)					// ���ʃX�s�[�h
#define NOTES_SPEED_FAST              (3.0f)					// �����X�s�[�h
#define NOTES_NUM_TIMEPLASS           (10)						// �^�C������������G�̐�
#define NOTES_DIST_TIMEPLASS          (SCREEN_WIDTH / 5 * 2)	// �^�C������������G�̈ʒu
#define NOTES_POINT_TYPE_TWO          (5)						// �U����2
#define NOTES_POINT_TYPE_THREE        (5)						// �U����3
#define NOTES_POINT_TYPE_SIX          (5)						// �_��6
#define NOTES_POINT_TYPE_SEVEN        (5)						// �_��7

#define NOTES_ANIM_SPEED_1 30 // �A�j���[�V�����X�s�[�h �X���C��
#define NOTES_ANIM_SPEED_2 60 // �A�j���[�V�����X�s�[�h �S�[����
#define NOTES_ANIM_SPEED_3 90 // �A�j���[�V�����X�s�[�h

#define NOTES_STOP_TIME 30 // �~�܂鎞��

//�ǂݍ��ރe�N�X�`���t�@�C����
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
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureNotes[NOTES_MAX] = {};//Notes�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferNotes = NULL;//�|�C���^�[!!&������

/*�m�[�c�\����*/
NOTES g_aNotes[MAX_NOTES];
int g_nEnemyTime; // ���Ԃ��߂�G�̃J�E���g
int g_nTimeGame; // �Q�[�����Ԃ̃J�E���g

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexNotes(LPDIRECT3DDEVICE9 pDevice);//���_�̍쐬

//============================================
//
//  ���O  InitNotes�֐�
//  ����	void
//  �߂�l  void
//  ����  Notes�֌W�̏�����
//
//============================================
HRESULT InitNotes(void)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//���_�쐬
	if(FAILED(MakeVertexNotes(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//�e�N�X�`���擾
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_ONE_TEXTURENAME , &g_pTextureNotes[0] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","NOTES_ONE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_TWO_TEXTURENAME , &g_pTextureNotes[1] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","NOTES_TWO",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_THREE_TEXTURENAME , &g_pTextureNotes[2] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","NOTES_THREE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_FOUR_TEXTURENAME , &g_pTextureNotes[3] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","NOTES_FOUR",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_FIVE_TEXTURENAME , &g_pTextureNotes[4] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","NOTES_FIVE",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_SIX_TEXTURENAME , &g_pTextureNotes[5] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","NOTES_SIX",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_SEVEN_TEXTURENAME , &g_pTextureNotes[6] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","NOTES_SEVEN",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , NOTES_SEVEN_2_TEXTURENAME , &g_pTextureNotes[7] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","NOTES_SEVEN_2",MB_OK | MB_DEFBUTTON1);
		}//EOif
	// �m�[�c�\���̂̏�����
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

	// �^�C�������̓G�j�󐔂̃��Z�b�g
	g_nEnemyTime = 0;
	g_nTimeGame = 0;
	return S_OK;
}//EOInitNotes

//============================================
//
//  ���O  UninitNotes�֐�
//  ����	void
//  �߂�l  void
//  ����  Notes�֌W�̏I������
//
//============================================
void UninitNotes(void)
{
	for(int nCntNotes = 0 ; nCntNotes < NOTES_MAX  ; nCntNotes++)
	{
		//�e�N�X�`���C���^�[�t�F�[�X�̌�Еt��
		SAFE_RELEASE( g_pTextureNotes[nCntNotes] );
	} // EO for

	//���_�o�b�t�@�̌�Еt��
	SAFE_RELEASE( g_pVtxBufferNotes );
}//EOUninitNotes

//============================================
//
//  ���O  UpdateNotes�֐�
//  ����	void
//  �߂�l  void
//  ����  Notes�֌W�̍X�V����
//
//============================================
void UpdateNotes(void)
{
	// �G�̔���
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

	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo

		//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferNotes -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

	// UV�A�j���[�V�����Ńm�[�c
	for(int nCntNotes = 0 ; nCntNotes < MAX_NOTES ; nCntNotes++)
	{
		// �g�p�`�F�b�N
		if(g_aNotes[nCntNotes].bUse == true)
		{
			//���_���W�̐ݒ�(2D���W , �E��� )
			pVtx [ 0 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aNotes[nCntNotes].fPos.x , g_aNotes[nCntNotes].fPos.y , 0.0f);
			pVtx [ 1 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aNotes[nCntNotes].fPos.x + g_aNotes[nCntNotes].fWidth ,g_aNotes[nCntNotes].fPos.y , 0.0f);
			pVtx [ 2 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aNotes[nCntNotes].fPos.x , g_aNotes[nCntNotes].fPos.y + g_aNotes[nCntNotes].fHeight , 0.0f);
			pVtx [ 3 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aNotes[nCntNotes].fPos.x + g_aNotes[nCntNotes].fWidth , g_aNotes[nCntNotes].fPos.y + g_aNotes[nCntNotes].fHeight , 0.0f);

		    //�e���_�̃e�N�X�`�����W�̐ݒ�
			pVtx [ 0 + 4*nCntNotes] . tex = D3DXVECTOR2 (g_aNotes[nCntNotes].fUV.x , g_aNotes[nCntNotes].fUV.y);
			pVtx [ 1 + 4*nCntNotes] . tex = D3DXVECTOR2 (g_aNotes[nCntNotes].fUV.x + NOTES_U_WIDTH , g_aNotes[nCntNotes].fUV.y);
			pVtx [ 2 + 4*nCntNotes] . tex = D3DXVECTOR2 (g_aNotes[nCntNotes].fUV.x , g_aNotes[nCntNotes].fUV.y + NOTES_V_HEIGHT);
			pVtx [ 3 + 4*nCntNotes] . tex = D3DXVECTOR2 (g_aNotes[nCntNotes].fUV.x + NOTES_U_WIDTH , g_aNotes[nCntNotes].fUV.y+ NOTES_V_HEIGHT);


			// �̗͂ɂ���ĐԂ��Ȃ�
			float par = (float)g_aNotes[nCntNotes].nLife / (float)g_aNotes[nCntNotes].nNumLife;
			//���_�J���[(0�`255�̐����l)
			pVtx[0 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f * par, 1.0f * par , 1.0f);
			pVtx[1 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f * par, 1.0f * par , 1.0f);
			pVtx[2 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f * par, 1.0f * par , 1.0f);
			pVtx[3 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f * par, 1.0f * par , 1.0f);

		//////////////////////////////////////////////////
			//  ����UV�A�j���[�V��������Ȃ炱���A�����Q��  //
			//////////////////////////////////////////////////

			// ��̓����蔻��
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
			//  �ړ��ʂ̏ꍇ����  //
			////////////////////////
			// ���t���[���̈ړ�   //
			//////////////////////////////////////////////////
			// �v���C���[�̈ʒu�c��
			PLAYER* pPlayer = GetPlayer();


			if(g_aNotes[nCntNotes].bStop == false)
			{
				switch(g_aNotes[nCntNotes].nMode)
				{
				case NOTES_ONE: // ���i
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
				case NOTES_TWO: // Y���v���C���[�Ɍ������Ă���
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
				case NOTES_THREE: // cos�J�[�u
					g_aNotes[nCntNotes].fFlame += 0.05f;
					g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_NORMAL;
					g_aNotes[nCntNotes].fPos.y -= cosf(g_aNotes[nCntNotes].fFlame) * 10;
					if(g_aNotes[nCntNotes].fFlame >= D3DX_PI)
					{
						g_aNotes[nCntNotes].fFlame = 0.0f;
					} // EO if
					break;
				case NOTES_FOUR: // ���i���āA�ꎞ��~
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
				case NOTES_FIVE: // ������蒼�i
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
				case NOTES_SIX: // �������i(�|����Ȃ�)
					g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_FAST;


					break;
				case NOTES_SEVEN:
					if(g_aNotes[nCntNotes].fFlame <= 1)
					{
						g_aNotes[nCntNotes].fPos.x -= NOTES_SPEED_NORMAL;

						// ���܂ŗ�����
						if(g_aNotes[nCntNotes].fPos.x <= 0)
						{
							g_aNotes[nCntNotes].fFlame = 3;
							g_aNotes[nCntNotes].fPos.x = 0;
						} // EO if
					} // EO if

					// ���˕Ԃ�
					if(g_aNotes[nCntNotes].fFlame > 1)
					{
						g_aNotes[nCntNotes].fPos.x += NOTES_SPEED_NORMAL;

						// �ǂ܂ŗ�����
						if(g_aNotes[nCntNotes].fPos.x > SCREEN_WIDTH)
						{
							g_aNotes[nCntNotes].bUse = false;
						} // EO if
					} // EO if

					// Y���v���C���[��ǂ�
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
			// �Ǘ���������� //
			//////////////////////////////////////////////////
			if(g_aNotes[nCntNotes].fPos.x + g_aNotes[nCntNotes].fWidth <= 0)
			{
				// ���C�t0�ɂ�����
				g_aNotes[nCntNotes].bUse = false;

				// ��Ƀ_���[�W
				AddDamegeCastle(g_aNotes[nCntNotes].nPoint);

				PlaySound(SE_GAME_CASTLE_BREAK);

			} // EO if
			//////////////////////////////////////////////////

			//////////////////////////
			// �̗͂Ȃ��Ȃ����甚�� //
			//////////////////////////////////////////////////
			if(g_aNotes[nCntNotes].nLife <= 0)
			{
				// ���C�t0�ɂ�����
				//PlaySound(SOUND_LABEL_SE002);
				g_aNotes[nCntNotes].bUse = false;
				switch(g_aNotes[nCntNotes].nMode)
				{
				case NOTES_ONE:	// �X���C��
					PlaySound(SE_GAME_ENEMY_KILL_SURAIMU);
					break;
				case NOTES_FIVE:	// �S�[����
					PlaySound(SE_GAME_ENEMY_KILL_GOREMU);
					break;
				case NOTES_SEVEN:	// �p���T�[
					PlaySound(SE_GAME_ENEMY_KILL_PANSER);
					break;
				}

			} // EO if
			//////////////////////////////////////////////////

			// �̗͍X�V
			SetUVSizeHeart(g_aNotes[nCntNotes].nNumHp , g_aNotes[nCntNotes].nLife);
			SetPosHeart(g_aNotes[nCntNotes].nNumHp , g_aNotes[nCntNotes].fPos);

			if(g_aNotes[nCntNotes].bUpdateFlag == false)
			{
				int i = 0;
			}
		} // EO if
	} // EO for

	g_pVtxBufferNotes->Unlock ();												//���b�N����

}//EOUpdateNotes

//============================================
//
//  ���O  DrawNotes�֐�
//  ����	void
//  �߂�l  void
//  ����  Notes�֌W�̕`�揈��
//
//============================================
void DrawNotes(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�p�C�v���C���̐ݒ�
	pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
						g_pVtxBufferNotes ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
						0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
						sizeof(VERTEX2D) );//�X�g���C�h��(��̒P�ʂ̑傫��)

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// �ő吔�`�F�b�N
	for(int nCntNotes = 0 ; nCntNotes < MAX_NOTES ; nCntNotes++)
	{
		if(g_aNotes[nCntNotes].bUse == true)
		{
			if(g_aNotes[nCntNotes].bDrawFlag == true)
			{
				// ��ނŕ�����
				switch(g_aNotes[nCntNotes].nMode)
				{
				case NOTES_ONE:

					//Notes�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureNotes[0] );

					break;
				case NOTES_TWO:

					//Notes�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureNotes[1] );

					break;
				case NOTES_THREE:

					//Notes�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureNotes[2] );

					break;
				case NOTES_FOUR:

					//Notes�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureNotes[3] );

					break;
				case NOTES_FIVE:

					//Notes�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureNotes[4] );

					break;
				case NOTES_SIX:

					//Notes�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureNotes[5] );

					break;
				case NOTES_SEVEN:

					//Notes�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureNotes[6] );
					if(g_aNotes[nCntNotes].fFlame > 1)
					{
						pDevice -> SetTexture( 0 , g_pTextureNotes[7] );
					} // EO if

					break;
				} // EO switch

				//�v���~�e�B�u�̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
					nCntNotes * 4 ,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
					NUM_POLYGON );//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B
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
//  ���O  MakeVertexNotes�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexNotes(LPDIRECT3DDEVICE9 pDevice)
{

	//���_�o�b�t�@�쐬
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_NOTES,//�쐬���������_�o�b�t�@�̃T�C�Y = 1�̒��_�̃T�C�Y * ���_��
																	//�ǂꂭ�炢�������ق������A�������߂�����ӂ₷��Ł[�[�[
			D3DUSAGE_WRITEONLY,									//���_�o�b�t�@�̎g�p���@�A�������ݐ�p�Ȃ̂ŁA���炭�ő�
			FVF_VERTEX_2D,										//NULL��0�ł����v�A�}�i�[�I�ɂ͏�������B���̃o�b�t�@�̒��_�t�H�[�}�b�g��₤
			D3DPOOL_MANAGED,									//�������Ǘ��ǂ�����ݒ�A���̏�Ԃ̓f�o�C�X�ɂ��C��
			&g_pVtxBufferNotes,						//�o���オ�������_�o�b�t�@���Ǘ�����A�h���X
			NULL)												//�䂾�����NULL
	))
	{
		return E_FAIL;
	}


	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferNotes -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

		// �ő吔��
	for(int nCntNotes = 0 ; nCntNotes < MAX_NOTES ; nCntNotes++)
	{
		//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
		pVtx[0 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[1 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[2 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[3 + 4 * nCntNotes].rhw = 1.0f;

		//���_�J���[(0�`255�̐����l)
		pVtx[0 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//�����A�����b�N
	g_pVtxBufferNotes -> Unlock();

	return S_OK;

}//EOMakeVertexNotes

//============================================
//
//  ���O  SetNotes�֐�
//  ����	void
//  �߂�l  float fPosX ,float fPosY,float fWidth,float fHeught,Notes_MODE nMode
//  ����  �m�[�c���Z�b�g
//
//============================================
void    SetNotes    (float fPosX , // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	NOTES_MODE nMode			   // ���
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
//  ���O  GetNotes�֐�
//  ����	void
//  �߂�l  NOTES *g_aNotes[0]
//  ����  g_aNotes�̐擪�A�h���X��n��
//
//============================================
NOTES* GetNotes()
{
	return &g_aNotes[0];
} // EO GetNotes

//============================================
//
//  ���O  CheckEnemyTime�֐�
//  ����	void
//  �߂�l  true or false
//  ����  �G�j�󐔂��K��𖞂����Ă��邩�ǂ�����Ԃ�
//
//============================================
bool CheckEnemyTime (void)
{
	// �G�j�󐔂����܂ł����Ă�����
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
				case NOTES_ONE:	// �X���C��
					PlaySound(SE_GAME_ENEMY_KILL_SURAIMU);
					break;
				case NOTES_FIVE:	// �S�[����
					PlaySound(SE_GAME_ENEMY_KILL_GOREMU);
					break;
				case NOTES_SEVEN:	// �p���T�[
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

bool GetZeroNotes(void)	// �G�����ׂ�false�Ȃ�true,�����łȂ��Ȃ�false��Ԃ�
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
