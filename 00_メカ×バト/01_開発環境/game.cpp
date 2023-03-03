//===================================================
//
// �Q�[���̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <time.h>
#include "game.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "debug_proc.h"
#include "sound.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "model.h"
#include "meshfield.h"
#include "fade.h"
#include "polygon.h"
#include "message.h"
#include "sky.h"
#include "hp.h"
#include "stage.h"
#include "item.h"
#include "time.h"
#include "bg.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
int CGame::nNum = 0;
bool CGame::m_bDeathEnemny = false;			//�G������ł��邩
bool CGame::m_bDeathPlayer = false;			//�v���C���[������ł��邩
bool CGame::m_bFinish = false;				//�I���t���O
bool CGame::m_bStart = false;				//�J�n�t���O

CCamera*	CGame::m_pCamera = nullptr;		//�J����
CPlayer*	CGame::m_pPlayer = nullptr;		//�v���C���[
CEnemy*		CGame::m_pEnemy = nullptr;		//�G�l�~�[
CMeshField*	CGame::m_pMeshField = nullptr;	//���b�V���t�B�[���h
CPolygon*	CGame::m_pPolygon = nullptr;	//2D�|���S��
CSky*		CGame::m_pSky = nullptr;		//�X�J�C
CStage*		CGame::m_pStage = nullptr;		//�X�e�[�W
CTime*		CGame::m_pTime = nullptr;		//�^�C�}�[

//===========================
// �R���X�g���N�^
//===========================
CGame::CGame()
{
	m_nCntFinish = 0;
	m_nCntItem = 0;
	m_nCntMessage = 0;		//���b�Z�[�W��\������܂ł̎���
	m_nNumMessage = 0;		//�\�����郁�b�Z�[�W�ԍ�
	nNum = 0;
	m_pItem = nullptr;		//�A�C�e��
	m_pMessage = nullptr;	//���b�Z�[�W
}

//===========================
// �f�X�g���N�^
//===========================
CGame::~CGame()
{

}

//===========================
// ������
//===========================
HRESULT CGame::Init()
{
	//�����l�̐ݒ�
	m_bDeathEnemny = false;
	m_bDeathPlayer = false;
	m_bFinish = false;
	m_bStart = false;
	m_nNumMessage = 3;
	m_nCntMessage = 60;

	//�J�����̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	//----------------------------
	// �G�l�~�[�̐���
	//----------------------------
	{
		D3DXVECTOR3 pos(0.0f, 0.0f, 300.0f);
		D3DXVECTOR3 rot(0.0f, 0.0f, 0.0f);
		m_pEnemy = CEnemy::Create(pos, rot);
	}

	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create();

	//�X�e�[�W�̐���
	m_pStage = CStage::Create("data\\MODEL\\Stage.x", D3DXVECTOR3(0.0f, -100.0f, 0.0f));

	//��̐���
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//2D�|���S���̐���
	m_pPolygon = CPolygon::Create(CPolygon::POLYGONTYPE_AIM);

	//�^�C�}�[�̐���
	m_pTime = CTime::Create(D3DXVECTOR3(1088.0f, 592.0f, 0.0f));

	//�w�i�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(1140.0f, 350.0f, 0.0f), CBg::BGTYPE_COMBO);		//�R���{�w�i
	m_pBg = CBg::Create(D3DXVECTOR3(1140.0f, 580.0f, 0.0f), CBg::BGTYPE_TIMER);		//�^�C�}�[�w�i
	m_pBg = CBg::Create(D3DXVECTOR3(210.0f, 590.0f, 0.0f), CBg::BGTYPE_PLAYER_HP);	//�v���C���[HP�w�i
	m_pBg = CBg::Create(D3DXVECTOR3(400.0f, 35.0f, 0.0f), CBg::BGTYPE_ENEMY_HP);	//�G�l�~�[HP�w�i

	//BGM�̍Đ�
	CSound::PlaySound(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//===========================
// �I��
//===========================
void CGame::Uninit()
{
	//BGM�̒�~
	CSound::StopSound();

	//�J�����̏I��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//===========================
// �X�V
//===========================
void CGame::Update()
{
	if (m_bDeathEnemny)
	{//�G������ł���Ȃ�
		m_pEnemy = nullptr;
		m_bFinish = true;	//�I���t���O�𗧂Ă�
	}
	else if (m_bDeathPlayer)
	{//�v���C���[������ł���Ȃ�
		m_bFinish = true;
	}

	//----------------------------
	// �I������
	//----------------------------
	Finish();

	//----------------------------
	// �J�����̍X�V
	//----------------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//----------------------------
	// �J�n���Ă��邩�ǂ���
	//----------------------------
	if (m_bStart == false)
	{//�J�n�t���O�������Ă��Ȃ��Ȃ�
		//----------------------------
		// ���b�Z�[�W�̕\��
		//----------------------------
		SetMessage();
	}
	else
	{//�J�n���Ă���Ȃ�
		if (nNum <= 20)
		{
			//----------------------------
			// �A�C�e���̐���
			//----------------------------
			SetItem();
		}
	}

#ifdef _DEBUG
	if (CInputKeyboard::Trigger(DIK_1))
	{
		m_bFinish = true;	//�I���t���O�𗧂Ă�

		//�Q�[����ʂɈڍs
		CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);
	}
#endif // !_DEBUG
}

//===========================
// �Q�[���I������
//===========================
void CGame::Finish()
{
	if (m_bFinish)
	{//�I���t���O�������Ă���Ȃ�
		m_nCntFinish++;	//�J�E���g�����Z

		//---------------------------
		// ���Ԍo�߂őJ��
		//---------------------------
		if (m_nCntFinish >= 300)
		{//�J�E���g��5�b�ȏ�Ȃ�
			//���U���g��ʂɈڍs
			CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);
		}
		//---------------------------
		// �L�[�������đJ��
		//---------------------------
		else if (m_nCntFinish >= 120)
		{//�J�E���g��2�b�ȏ�(�N���A�̕�������������)
			if (CInputKeyboard::Trigger(DIK_RETURN))
			{//ENTER�L�[�������ꂽ��
				//���U���g��ʂɈڍs
				CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);
			}
		}
	}
}

//===========================
// �J�E���g�_�E���̕\��
//===========================
void CGame::SetMessage()
{
	D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	//���Ԃ𐔂���
	m_nCntMessage++;

	if (m_nCntMessage >= 60)
	{
		if (m_nNumMessage == 3)
		{//�J�E���g3
			m_pMessage = CMessage::Create(pos, 600.0f, 300.0f, CMessage::MESSAGE_3);
		}
		else if (m_nNumMessage == 2)
		{//�J�E���g2
			m_pMessage = CMessage::Create(pos, 600.0f, 300.0f, CMessage::MESSAGE_2);
		}
		else if (m_nNumMessage == 1)
		{//�J�E���g1
			m_pMessage = CMessage::Create(pos, 600.0f, 300.0f, CMessage::MESSAGE_1);
		}
		else if (m_nNumMessage == 0)
		{//�X�^�[�g
			m_pMessage = CMessage::Create(pos, 800.0f, 400.0f, CMessage::MESSAGE_START);
		}
		else
		{
			//�J�n�t���O�𗧂Ă�
			m_bStart = true;
		}

		//�\�����镶����ύX
		m_nNumMessage--;

		m_nCntMessage = 0;
	}
}

//===========================
// �A�C�e���̐���
//===========================
void CGame::SetItem()
{
	m_nCntItem++;	//�J�E���g�̉��Z

	if (m_nCntItem >= 300)
	{
		int nWidth = 1500;

		int X = rand() % (nWidth * 2) - nWidth;
		int Z = rand() % (nWidth * 2) - nWidth;

		D3DXVECTOR3 pos((float)X, 100.0f, (float)Z);
		m_pItem = CItem::Create(pos, CItem::ITEMTYPE_HEAL);
		nNum++;
		m_nCntItem = 0;	//���Z�b�g
	}
}