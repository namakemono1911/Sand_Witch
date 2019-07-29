//============================================
//  Human�֐�  (Human.cpp)
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
//  �萔�錾
//
//============================================
#define HUMAN_UV_SPEED                (5)                  // ���t���[����UV�A�j���[�V�������邩
#define HUMAN_U_WIDTH                 (0.5f)               // U��
#define HUMAN_V_HEIGHT                (1.0f)               // V����
#define HUMAN_POINT_TYPE_ONE          (10)                 // �_��1
#define HUMAN_POINT_TYPE_TWO          (30)                 // �_��2
#define HUMAN_POINT_TYPE_THREE        (50)                 // �_��3
#define HUMAN_POINT_TYPE_FOUR         (80)                 // �_��4
#define HUMAN_POINT_TYPE_FIVE         (100)                // �_��5
#define HUMAN_POINT_TYPE_SIX          (200)                // �_��6
#define HUMAN_POINT_TYPE_SEVEN        (130)                // �_��7
#define HUMAN_SPEED_SLOW              (1.0f)               // �x���X�s�[�h
#define HUMAN_SPEED_NORMAL            (5.0f)               // ���ʃX�s�[�h
#define HUMAN_SPEED_FAST              (20.0f)              // �����X�s�[�h
#define HUMAN_NUM_TIMEPLASS           (10)                 // �^�C������������G�̐�
#define HUMAN_DIST_TIMEPLASS          (SCREEN_WIDTH / 5 * 2)   // �^�C������������G�̈ʒu

#//�ǂݍ��ރe�N�X�`���t�@�C����
#define HUMAN_TWO_TEXTURENAME       "data/TEXTURE/GAME/HUMAN/Human01.png"   // NHUMAN_ONE
#define HUMAN_ONE_TEXTURENAME       "data/TEXTURE/GAME/HUMAN/Human02.png"   // NHUMAN_TWO

#define HUMAN_ANIM_TIME 15	// �A�j���[�V�����Ԋu

#define HUMAN_TRANSPARENT 0.01f	//�����ɂȂ�Ԋu

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureHuman[HUMAN_MAX] = {};//Human�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferHuman = NULL;//�|�C���^�[!!&������

/*�l�\����*/
HUMAN g_aHuman[MAX_HUMAN];
int g_nHumanTime; // ���Ԃ��߂�G�̃J�E���g

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexHuman(LPDIRECT3DDEVICE9 pDevice);//���_�̍쐬

//============================================
//
//  ���O  InitHuman�֐�
//  ����	void
//  �߂�l  void
//  ����  Human�֌W�̏�����
//
//============================================
HRESULT InitHuman(void)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//���_�쐬
	if(FAILED(MakeVertexHuman(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//�e�N�X�`���擾
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , HUMAN_ONE_TEXTURENAME , &g_pTextureHuman[0] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","HUMAN_ONE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , HUMAN_TWO_TEXTURENAME , &g_pTextureHuman[1] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","HUMAN_TWO",MB_OK | MB_DEFBUTTON1);
		}//EOif

	// �l�\���̂̏�����
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

	// �^�C�������̓G�j�󐔂̃��Z�b�g
	g_nHumanTime = 0;
	return S_OK;
}//EOInitHuman

//============================================
//
//  ���O  UninitHuman�֐�
//  ����	void
//  �߂�l  void
//  ����  Human�֌W�̏I������
//
//============================================
void UninitHuman(void)
{
	for(int nCntHuman = 0 ; nCntHuman < HUMAN_MAX  ; nCntHuman++)
	{
		//�e�N�X�`���C���^�[�t�F�[�X�̌�Еt��
		SAFE_RELEASE( g_pTextureHuman[nCntHuman] );
	} // EO for

	//���_�o�b�t�@�̌�Еt��
	SAFE_RELEASE( g_pVtxBufferHuman );
}//EOUninitHuman

//============================================
//
//  ���O  UpdateHuman�֐�
//  ����	void
//  �߂�l  void
//  ����  Human�֌W�̍X�V����
//
//============================================
void UpdateHuman(void)
{
	// �l�̔�����NotesUpdate

	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo

		//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferHuman -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

	// UV�A�j���[�V�����Ől
	for(int nCntHuman = 0 ; nCntHuman < MAX_HUMAN ; nCntHuman++)
	{
		// �g�p�`�F�b�N
		if(g_aHuman[nCntHuman].bUse == true)
		{

			//���_���W�̐ݒ�(2D���W , �E��� )
			pVtx [ 0 + 4*nCntHuman] . pos = D3DXVECTOR3 (g_aHuman[nCntHuman].fPos.x , g_aHuman[nCntHuman].fPos.y , 0.0f);
			pVtx [ 1 + 4*nCntHuman] . pos = D3DXVECTOR3 (g_aHuman[nCntHuman].fPos.x + g_aHuman[nCntHuman].fWidth ,g_aHuman[nCntHuman].fPos.y , 0.0f);
			pVtx [ 2 + 4*nCntHuman] . pos = D3DXVECTOR3 (g_aHuman[nCntHuman].fPos.x , g_aHuman[nCntHuman].fPos.y + g_aHuman[nCntHuman].fHeight , 0.0f);
			pVtx [ 3 + 4*nCntHuman] . pos = D3DXVECTOR3 (g_aHuman[nCntHuman].fPos.x + g_aHuman[nCntHuman].fWidth , g_aHuman[nCntHuman].fPos.y + g_aHuman[nCntHuman].fHeight , 0.0f);

		    //�e���_�̃e�N�X�`�����W�̐ݒ�
			pVtx [ 0 + 4*nCntHuman] . tex = D3DXVECTOR2 (g_aHuman[nCntHuman].fUV.x , g_aHuman[nCntHuman].fUV.y);
			pVtx [ 1 + 4*nCntHuman] . tex = D3DXVECTOR2 (g_aHuman[nCntHuman].fUV.x + HUMAN_U_WIDTH , g_aHuman[nCntHuman].fUV.y);
			pVtx [ 2 + 4*nCntHuman] . tex = D3DXVECTOR2 (g_aHuman[nCntHuman].fUV.x , g_aHuman[nCntHuman].fUV.y + HUMAN_V_HEIGHT);
			pVtx [ 3 + 4*nCntHuman] . tex = D3DXVECTOR2 (g_aHuman[nCntHuman].fUV.x + HUMAN_U_WIDTH , g_aHuman[nCntHuman].fUV.y+ HUMAN_V_HEIGHT);


			//////////////////////////////////////////////////
			//  ����UV�A�j���[�V��������Ȃ炱���A�����Q��  //
			//////////////////////////////////////////////////
			g_aHuman[nCntHuman].nCntAnim++;
			if(g_aHuman[nCntHuman].nCntAnim >= HUMAN_ANIM_TIME)
			{
				g_aHuman[nCntHuman].nCntAnim = 0;
				g_aHuman[nCntHuman].fUV.x += 0.5f;
			}
			////////////////////////
			//  �ړ��ʂ̏ꍇ����  //
			////////////////////////
			// ���t���[���̈ړ�   //
			//////////////////////////////////////////////////
			// �v���C���[�̈ʒu�c��
			PLAYER* pPlayer = GetPlayer();

			if(g_aHuman[nCntHuman].bUpdateFlag == true)
			{
				switch(g_aHuman[nCntHuman].nMode)
				{
				case HUMAN_ONE: // ���i
					g_aHuman[nCntHuman].fPos.x -= HUMAN_SPEED_SLOW;
					break;
				case HUMAN_TWO: // Y���v���C���[�Ɍ������Ă���
					g_aHuman[nCntHuman].fPos.x -= HUMAN_SPEED_SLOW;
					break;
				} // EO switch
			} // EO if
			//////////////////////////////////////////////////

			////////////////////
			// �Ǘ���������� //
			//////////////////////////////////////////////////
			if(g_aHuman[nCntHuman].fPos.x + g_aHuman[nCntHuman].fWidth <= 0)
			{
				// ���C�t0�ɂ�����
				g_aHuman[nCntHuman].bUse = false;

				// ��or���Ă������ɂ�������ʔ���

			} // EO if
			//////////////////////////////////////////////////

			////////////////////////
			// �哖������������� //
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
						case HUMAN_ONE: // ��
							AddLife(nCntGate , 20);
							g_aHuman[nCntHuman].bAlpha = true;
							break;
						case HUMAN_TWO: // �K�E�Z////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							addFcohEnergy(1);		//�K�E�Z�`���[�W
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
				// ��or���Ă������ɂ�������ʔ���

			} // EO if
			//////////////////////////////////////////////////

			//////////////////////////
			// �̗͂Ȃ��Ȃ����甚�� //
			//////////////////////////////////////////////////
			if(g_aHuman[nCntHuman].nLife <= 0)
			{
				// ���C�t0�ɂ�����
				g_aHuman[nCntHuman].bAlpha = true;

			} // EO if
			//////////////////////////////////////////////////

			if(g_aHuman[nCntHuman].bUpdateFlag == false)
			{
				int i = 0;
			}

			// �ʂ�߂�����
			if(g_aHuman[nCntHuman].bAlpha == true)
			{
				g_aHuman[nCntHuman].fAlpha -= HUMAN_TRANSPARENT;
				if(g_aHuman[nCntHuman].fAlpha <= 0.0f)
				{
					g_aHuman[nCntHuman].bUse = false;
				}
			}
			//���_�J���[(0�`255�̐����l)
			pVtx[0 + 4 * nCntHuman].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aHuman[nCntHuman].fAlpha);
			pVtx[1 + 4 * nCntHuman].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aHuman[nCntHuman].fAlpha);
			pVtx[2 + 4 * nCntHuman].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aHuman[nCntHuman].fAlpha);
			pVtx[3 + 4 * nCntHuman].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aHuman[nCntHuman].fAlpha);

		} // EO if
	} // EO for

	g_pVtxBufferHuman->Unlock ();												//���b�N����

}//EOUpdateHuman

//============================================
//
//  ���O  DrawHuman�֐�
//  ����	void
//  �߂�l  void
//  ����  Human�֌W�̕`�揈��
//
//============================================
void DrawHuman(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�p�C�v���C���̐ݒ�
	pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
						g_pVtxBufferHuman ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
						0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
						sizeof(VERTEX2D) );//�X�g���C�h��(��̒P�ʂ̑傫��)

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// �ő吔�`�F�b�N
	for(int nCntHuman = 0 ; nCntHuman < MAX_HUMAN ; nCntHuman++)
	{
		if(g_aHuman[nCntHuman].bUse == true)
		{
			if(g_aHuman[nCntHuman].bDrawFlag == true)
			{
				// ��ނŕ�����
				switch(g_aHuman[nCntHuman].nMode)
				{
				case HUMAN_ONE:

					//Human�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureHuman[0] );

					break;
				case HUMAN_TWO:

					//Human�̕`������鐡�O
					pDevice -> SetTexture( 0 , g_pTextureHuman[1] );

					break;
				} // EO switch

				//�v���~�e�B�u�̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
					nCntHuman * 4 ,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
					NUM_POLYGON );//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B
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
//  ���O  MakeVertexHuman�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexHuman(LPDIRECT3DDEVICE9 pDevice)
{

	//���_�o�b�t�@�쐬
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_HUMAN,//�쐬���������_�o�b�t�@�̃T�C�Y = 1�̒��_�̃T�C�Y * ���_��
																	//�ǂꂭ�炢�������ق������A�������߂�����ӂ₷��Ł[�[�[
			D3DUSAGE_WRITEONLY,									//���_�o�b�t�@�̎g�p���@�A�������ݐ�p�Ȃ̂ŁA���炭�ő�
			FVF_VERTEX_2D,										//NULL��0�ł����v�A�}�i�[�I�ɂ͏�������B���̃o�b�t�@�̒��_�t�H�[�}�b�g��₤
			D3DPOOL_MANAGED,									//�������Ǘ��ǂ�����ݒ�A���̏�Ԃ̓f�o�C�X�ɂ��C��
			&g_pVtxBufferHuman,						//�o���オ�������_�o�b�t�@���Ǘ�����A�h���X
			NULL)												//�䂾�����NULL
	))
	{
		return E_FAIL;
	}


	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferHuman -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

		// �ő吔��
	for(int nCntHuman = 0 ; nCntHuman < MAX_HUMAN ; nCntHuman++)
	{
		//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
		pVtx[0 + 4 * nCntHuman].rhw = 1.0f;
		pVtx[1 + 4 * nCntHuman].rhw = 1.0f;
		pVtx[2 + 4 * nCntHuman].rhw = 1.0f;
		pVtx[3 + 4 * nCntHuman].rhw = 1.0f;

		//���_�J���[(0�`255�̐����l)
		pVtx[0 + 4 * nCntHuman].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntHuman].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntHuman].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntHuman].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//�����A�����b�N
	g_pVtxBufferHuman -> Unlock();

	return S_OK;

}//EOMakeVertexHuman

//============================================
//
//  ���O  SetHuman�֐�
//  ����	void
//  �߂�l  float fPosX ,float fPosY,float fWidth,float fHeught,Human_MODE nMode
//  ����  �l���Z�b�g
//
//============================================
void    SetHuman    (float fPosX , // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	HUMAN_MODE nMode			   // ���
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
//  ���O  GetHuman�֐�
//  ����	void
//  �߂�l  HUMAN *g_aHuman[0]
//  ����  g_aHuman�̐擪�A�h���X��n��
//
//============================================
HUMAN* GetHuman()
{
	return &g_aHuman[0];
} // EO GetHuman

//============================================
//
//  ���O  CheckHumanTime�֐�
//  ����	void
//  �߂�l  true or false
//  ����  �G�j�󐔂��K��𖞂����Ă��邩�ǂ�����Ԃ�
//
//============================================
bool CheckHumanTime (void)
{
	// �G�j�󐔂����܂ł����Ă�����
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
