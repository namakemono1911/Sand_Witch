//============================================
//  Player�֐�  (Player.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N05��31��
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
#include "player.h"
#include "bullet.h"
#include "fcoh.h"
#include "input.h"
#include "inputX.h"
#include "notes.h"
#include "sound.h"

#include "effect.h"

//============================================
//
//  �萔�錾
//
//============================================
//�ǂݍ��ރe�N�X�`���t�@�C����
#define POLYGON_TEXTURENAME "data/TEXTURE/GAME/PLAYER/player.png"//�t�@�C���`���̓T�E���h���X�N���v�g������Ȃ���
                                                       //�ق��ɂ�jpg,png,tga,bmp,dds

#define POLYGON_POS_X  (50)//�|���S���̕\���ʒuX
#define POLYGON_POS_Y  (60)//�|���S���̕\���ʒuY
#define POLYGON_WIDTH  (100)//�|���S���̕�
#define POLYGON_HEIGHT (100)//�|���S���̍���
#define PLAYER_LIFE (100)
#define PLAYER_MOVE 10.0f // ���t���[���Ŏ��̏ꏊ�Ɉړ����邩

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
VERTEX2D g_aVertex[NUM_VERTEX];//���_�����i�[���邽�߂̔z��
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//�|���S���̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

// �v���C���[
PLAYER g_aPlayer;

static float g_fPosPlayer[5][3] = {
	{POLYGON_POS_X,PLAYER_POS_1,0.0f},
	{POLYGON_POS_X,PLAYER_POS_2,0.0f},
	{POLYGON_POS_X,PLAYER_POS_3,0.0f},
	{POLYGON_POS_X,PLAYER_POS_4,0.0f},
	{POLYGON_POS_X,PLAYER_POS_5,0.0f}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PLAYER_MOTION_MAX 3	// ���[�V�����ő吔

static float g_fPlayerUVSize[6][3][2] = 
{
	{{1.0f / 3.0f, 1.0f / 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f}},								// �j���[�g����
	{{1.0f / 3.0f, 1.0f / 6.0f * 2.0f} , {1.0f / 3.0f * 2.0f, 1.0f / 6.0f * 2.0f} , {1.0f, 1.0f / 6.0f * 2.0f}},		// �U��
	{{1.0f / 3.0f, 1.0f / 6.0f * 3.0f} , {1.0f / 3.0f * 2.0f, 1.0f / 6.0f * 3.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 3.0f}},	// �O����
	{{1.0f / 3.0f, 1.0f / 6.0f * 4.0f} , {1.0f / 3.0f * 2.0f, 1.0f / 6.0f * 4.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 4.0f}},	// ������
	{{1.0f / 3.0f, 1.0f / 6.0f * 5.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 5.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 5.0f}},		// ����
	{{1.0f / 3.0f, 1.0f / 6.0f * 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 6.0f}}			// ����
};

static float g_fPlayerUV[6][3][2] = 
{
	{{0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f}},														// �j���[�g����
	{{0.0f , 1.0f / 6.0f} , {1.0f / 3.0f, 1.0f / 6.0f} , {1.0f / 3.0f * 2.0f, 1.0f / 6.0f}},				// �U��
	{{0.0f , 1.0f / 6.0f * 2.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 2.0f} , {0.0f, 1.0f / 6.0f * 2.0f}},	// �O����
	{{0.0f , 1.0f / 6.0f * 3.0f} , {1.0f / 3.0f, 1.0f / 6.0f * 3.0f} , {0.0f, 1.0f / 6.0f * 3.0f}},	// ������
	{{0.0f , 1.0f / 6.0f * 4.0f} , {0.0f , 1.0f / 6.0f * 4.0f} , {0.0f , 1.0f / 6.0f * 4.0f}},				// ����
	{{0.0f , 1.0f / 6.0f * 5.0f} , {0.0f , 1.0f / 6.0f * 5.0f} , {0.0f , 1.0f / 6.0f * 5.0f}}				// ����
};

static int g_nPlayerMode = 0;			// 0:�j���[�g���� , 1:�U�� , 2�O���� : ,3:������ , 4:���� , 5:����
static int g_nPlayerModeCount = 0;		// ���̃��[�V�����܂ł̃J�E���g
static int g_nPlayerMotionCount = 0;	// ���ݍĐ����Ă���L�[

static int g_nPlayerModeTime[6][3] = 
{
	{30,30,30},	// �j���[�g����
	{10,5,30},	// �U��
	{5,5,5},	// �O����
	{5,5,5},	// ������
	{30,30,30},	// ����
	{30,30,30}	// ����
};

void SetPlayerMode(int nPlayerMode)
{
	g_nPlayerMode = nPlayerMode;
	g_nPlayerModeCount = 0;
	g_nPlayerMotionCount = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
void MakeVertexPlayer(LPDIRECT3DDEVICE9 pDevice);//���_�̍쐬

//============================================
//
//  ���O  InitPlayer�֐�
//  ����	void
//  �߂�l  void
//  ����  �|���S���֌W�̏�����
//
//============================================
void InitPlayer(void)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	//���_�쐬
	MakeVertexPlayer(pDevice);
	
	//�e�N�X�`���擾
	//�G���[�`�F�b�N�K�{
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , POLYGON_TEXTURENAME , &g_pTexturePlayer )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","�Ђ���ف`��",MB_OK | MB_DEFBUTTON1);
		}//EOif

	// �\���̏�����
	g_aPlayer.bUse = false;
	g_aPlayer.fMove = D3DXVECTOR3(0.0f , (g_fPosPlayer[0][1] - g_fPosPlayer[1][1]) / PLAYER_MOVE, 0.0f);
	g_aPlayer.nPos = 0;
	g_aPlayer.fPos = D3DXVECTOR3(g_fPosPlayer[g_aPlayer.nPos][0] , g_fPosPlayer[g_aPlayer.nPos][1] , 0.0f);
	g_aPlayer.fSize = D3DXVECTOR2(POLYGON_WIDTH , POLYGON_HEIGHT);
	g_aPlayer.nMovePos = 0;
	g_aPlayer.nZanki = 5;


	g_nPlayerMode = 0;			// 0:�j���[�g���� , 1:�U�� , 2�O���� : ,3:������ , 4:���� , 5:����
	g_nPlayerModeCount = 0;		// ���̃��[�V�����܂ł̃J�E���g
	g_nPlayerMotionCount = 0;	// ���ݍĐ����Ă���L�[

}//EOInitPolygin

//============================================
//
//  ���O  UninitPlayer�֐�
//  ����	void
//  �߂�l  void
//  ����  �|���S���֌W�̏I������
//
//============================================
void UninitPlayer(void)
{
	//�e�N�X�`���C���^�[�t�F�[�X�̌�Еt��
	SAFE_RELEASE( g_pTexturePlayer );
}//EOUninitPlayer

//============================================
//
//  ���O  UpdatePlayer�֐�
//  ����	void
//  �߂�l  void
//  ����  �|���S���֌W�̍X�V����
//
//============================================
void UpdatePlayer(void)
{
	// �X�V
	int nNow = g_aPlayer.nPos; // ���݂̈ʒu�̊m��

	// �㉺
	if(GetKeyboardTrigger(DIK_UP) || GetKeyXInputTrigger(XINPUT_DPAD_UP))
	{
		if(g_aPlayer.nPos > 0)
		{
			g_aPlayer.nPos--;
			g_aPlayer.fPos.x = g_fPosPlayer[g_aPlayer.nPos][0];
			SetPlayerMode(3);
			PlaySound(SE_GAME_PLAEYR_FOOT_VILLEGE);

		} // EO if
	} // EO if

	if(GetKeyboardTrigger(DIK_DOWN) || GetKeyXInputTrigger(XINPUT_DPAD_DOWN))
	{
		if(g_aPlayer.nPos < 4)
		{
			g_aPlayer.nPos++;
			g_aPlayer.fPos.x = g_fPosPlayer[g_aPlayer.nPos][0];
			SetPlayerMode(2);
			PlaySound(SE_GAME_PLAEYR_FOOT_VILLEGE);
		} // EO if
	} // EO if


	// �����ړ��ꏊ���ς������
	if(nNow != g_aPlayer.nPos)
	{
		g_aPlayer.fMove.y = (g_fPosPlayer[g_aPlayer.nPos][1] - g_aPlayer.fPos.y) / PLAYER_MOVE;
	}
	
	if(g_aPlayer.fPos.y >= g_fPosPlayer[g_aPlayer.nPos][1] - 0.01f && g_aPlayer.fPos.y <= g_fPosPlayer[g_aPlayer.nPos][1] + 0.01f)
	{
		g_aPlayer.fPos.y = g_fPosPlayer[g_aPlayer.nPos][1];
	}

	if(g_aPlayer.fPos.y != g_fPosPlayer[g_aPlayer.nPos][1])
	{
			g_aPlayer.fPos.y += g_aPlayer.fMove.y;
	//	if(g_aPlayer.fPos.y >= g_fPosPlayer[g_aPlayer.nPos][1])
	//	{
	//		g_aPlayer.fPos.y += g_aPlayer.fMove.y;
	//	} // EO if
	//	else
	//	{
	//		g_aPlayer.fPos.y -= g_aPlayer.fMove.y;
	//	}
	//}
	}
	//�e����
	if(GetKeyboardTrigger(DIK_Z) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A))
	{
		setBullet(D3DXVECTOR3(
			g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
			g_fPosPlayer[g_aPlayer.nPos][1],
			0.f),
			BULLET000);
			SetPlayerMode(1);
			PlaySound(SE_GAME_MAGIC_GO);
	}
	if(GetKeyboardTrigger(DIK_X) || GetKeyXInputTrigger(XINPUT_GAMEPAD_B))
	{
		setBullet(D3DXVECTOR3(
			g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
			g_fPosPlayer[g_aPlayer.nPos][1],
			0.f), BULLET001);
			SetPlayerMode(1);
			PlaySound(SE_GAME_MAGIC_GO);
	}
	if(GetKeyboardTrigger(DIK_C) || GetKeyXInputTrigger(XINPUT_GAMEPAD_X))
	{
		setBullet(D3DXVECTOR3(
			g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
			g_fPosPlayer[g_aPlayer.nPos][1],
			0.f), BULLET002);
			SetPlayerMode(1);
			PlaySound(SE_GAME_MAGIC_GO_BOMM);
	}
	//if (GetKeyboardTrigger(DIK_V) || GetKeyXInputTrigger(XINPUT_GAMEPAD_X))
	//{
	//	setBullet(D3DXVECTOR3(
	//		g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
	//		g_fPosPlayer[g_aPlayer.nPos][1],
	//		0.f), BULLET003);
	//		SetPlayerMode(1);
	//		PlaySound(SE_GAME_MAGIC_GO_DIFISION);
	//}
	if (GetKeyboardTrigger(DIK_SPACE)  || GetKeyXInputTrigger(XINPUT_RIGHT_SHOULDER))
	{
		setFcoh();
		SetPlayerMode(1);
		PlaySound(SE_GAME_MAGIC_ON_KILL);
	}

	//if(GetKeyXInputTrigger(XINPUT_GAMEPAD_A))
	//{
	//	setBullet(D3DXVECTOR3(
	//		g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
	//		g_fPosPlayer[g_aPlayer.nPos][1],
	//		0.f), BULLET000);
	//		SetPlayerMode(1);
	//}
	//if(GetKeyXInputTrigger(XINPUT_GAMEPAD_B))
	//{
	//	setBullet(D3DXVECTOR3(
	//		g_aPlayer.fPos.x + g_aPlayer.fSize.x * 0.5f,
	//		g_fPosPlayer[g_aPlayer.nPos][1],
	//		0.f), BULLET001);
	//		SetPlayerMode(1);
	//}
	// END�X�V

	// ���[�V����
	g_nPlayerModeCount++;
	if(g_nPlayerModeCount >= g_nPlayerModeTime[g_nPlayerMode][g_nPlayerMotionCount])
	{
		g_nPlayerModeCount = 0;
		g_nPlayerMotionCount++;
		if(g_nPlayerMotionCount >= PLAYER_MOTION_MAX)
		{
			// ���[�V�������I�������A�j���[�g�����ɂȂ���
			SetPlayerMode(0);
		}
	}

	//���_���W�̐ݒ�(2D���W�E�E���)
	g_aVertex[0].pos = D3DXVECTOR3(g_aPlayer.fPos.x - g_aPlayer.fSize.x / 2.0f,//X
		g_aPlayer.fPos.y - g_aPlayer.fSize.y / 2.0f,//Y
		0.0f);//Z,�����1�̒��_
	g_aVertex[1].pos = D3DXVECTOR3(g_aPlayer.fPos.x + g_aPlayer.fSize.x / 2.0f ,//X
		g_aPlayer.fPos.y - g_aPlayer.fSize.y / 2.0f,//Y
		0.0f);//Z,�����1�̒��_
	g_aVertex[2].pos = D3DXVECTOR3(g_aPlayer.fPos.x - g_aPlayer.fSize.x / 2.0f ,//X
		g_aPlayer.fPos.y + g_aPlayer.fSize.y / 2.0f,//Y
		0.0f);//Z,�����1�̒��_
	g_aVertex[3].pos = D3DXVECTOR3(g_aPlayer.fPos.x + g_aPlayer.fSize.x / 2.0f,//X
		g_aPlayer.fPos.y + g_aPlayer.fSize.y / 2.0f,//Y
		0.0f);//Z,�����1�̒��_

	//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
	g_aVertex[0].rhw = 1.0f;
	g_aVertex[1].rhw = 1.0f;
	g_aVertex[2].rhw = 1.0f;
	g_aVertex[3].rhw = 1.0f;

	//���_�J���[(0�`255�̐����l)
	g_aVertex[0].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[1].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[2].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[3].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	//���_UV�l�̐ݒ�
	g_aVertex[0].tex = D3DXVECTOR2( g_fPlayerUV[g_nPlayerMode][g_nPlayerMotionCount][0] ,
		g_fPlayerUV[g_nPlayerMode][g_nPlayerMotionCount][1] );
	g_aVertex[1].tex = D3DXVECTOR2(  g_fPlayerUVSize[g_nPlayerMode][g_nPlayerMotionCount][0] ,
		g_fPlayerUV[g_nPlayerMode][g_nPlayerMotionCount][1]  );
	g_aVertex[2].tex = D3DXVECTOR2( g_fPlayerUV[g_nPlayerMode][g_nPlayerMotionCount][0] ,
		 g_fPlayerUVSize[g_nPlayerMode][g_nPlayerMotionCount][1] );
	g_aVertex[3].tex = D3DXVECTOR2( g_fPlayerUVSize[g_nPlayerMode][g_nPlayerMotionCount][0],
		 g_fPlayerUVSize[g_nPlayerMode][g_nPlayerMotionCount][1]  );

}//EOUpdatePlayer

//============================================
//
//  ���O  DrawPlayer�֐�
//  ����	void
//  �߂�l  void
//  ����  �|���S���֌W�̕`�揈��
//
//============================================
void DrawPlayer(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	//�|���S���̕`������鐡�O
	pDevice -> SetTexture( 0 , g_pTexturePlayer );
	//�v���~�e�B�u�̕`��
	pDevice -> DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		NUM_POLYGON,//�v���~�e�B�u�̐��A�|���S���̑��₵�Y��ɒ���
		&g_aVertex[0],//���_�f�[�^�̐擪�A�h���X
		sizeof(VERTEX2D)//���_�f�[�^����̃T�C�Y(�P�ʂ̓o�C�g)
		);
}//EODarwPlayer

//============================================
//
//  ���O  MakeVertexPlayer�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
void MakeVertexPlayer(LPDIRECT3DDEVICE9 pDevice)
{
	//���_���W�̐ݒ�(2D���W�E�E���)
	g_aVertex[0].pos = D3DXVECTOR3(g_aPlayer.fPos.x ,//X
		g_aPlayer.fPos.y ,//Y
		0.0f);//Z,�����1�̒��_
	g_aVertex[1].pos = D3DXVECTOR3(g_aPlayer.fPos.x + g_aPlayer.fSize.x ,//X
		g_aPlayer.fPos.y ,//Y
		0.0f);//Z,�����1�̒��_
	g_aVertex[2].pos = D3DXVECTOR3(g_aPlayer.fPos.x ,//X
		g_aPlayer.fPos.y + g_aPlayer.fSize.y ,//Y
		0.0f);//Z,�����1�̒��_
	g_aVertex[3].pos = D3DXVECTOR3(g_aPlayer.fPos.x + g_aPlayer.fSize.x ,//X
		g_aPlayer.fPos.y + g_aPlayer.fSize.y ,//Y
		0.0f);//Z,�����1�̒��_

	//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
	g_aVertex[0].rhw = 1.0f;
	g_aVertex[1].rhw = 1.0f;
	g_aVertex[2].rhw = 1.0f;
	g_aVertex[3].rhw = 1.0f;

	//���_�J���[(0�`255�̐����l)
	g_aVertex[0].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[1].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[2].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	g_aVertex[3].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	//���_UV�l�̐ݒ�
	g_aVertex[0].tex = D3DXVECTOR2( 0.0f , 0.0f );
	g_aVertex[1].tex = D3DXVECTOR2( 1.0f , 0.0f );
	g_aVertex[2].tex = D3DXVECTOR2( 0.0f , 1.0f );
	g_aVertex[3].tex = D3DXVECTOR2( 1.0f , 1.0f );
}//EOMakeVertexPlayer

PLAYER* GetPlayer(void)
{
	return &g_aPlayer;
}
