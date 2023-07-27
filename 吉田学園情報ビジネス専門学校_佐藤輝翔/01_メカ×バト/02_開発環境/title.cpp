//===================================================
//
// �^�C�g���̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "title.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "application.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "bg.h"
#include "title_camera.h"
#include "stage.h"
#include "meshfield.h"
#include "sky.h"
#include "enemy.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CTitleCamera* CTitle::m_pCamera = nullptr;
CMeshField*	CTitle::m_pMeshField = nullptr;

//===========================
// �R���X�g���N�^
//===========================
CTitle::CTitle()
{
	m_pBg = nullptr;	//�w�i
	m_pStage = nullptr;	//�X�e�[�W
	m_pSky = nullptr;	//��
}

//===========================
// �f�X�g���N�^
//===========================
CTitle::~CTitle()
{

}

//===========================
// ������
//===========================
HRESULT CTitle::Init()
{
	m_pCamera = new CTitleCamera;
	m_pCamera->Init();

	m_pStage = CStage::Create("data\\MODEL\\Stage.x", D3DXVECTOR3(0.0f, -100.0f, 0.0f));

	m_pMeshField = CMeshField::Create();

	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//�w�i�̐���
	{
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0.0f);
		m_pBg = CBg::Create(pos, CBg::BGTYPE_TITLE);

		D3DXVECTOR3 pos2(SCREEN_WIDTH / 2,  550.0f, 0.0f);
		m_pBg = CBg::Create(pos2, CBg::BGTYPE_PRESS);
	}

	//BGM�̍Đ�
	CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// �I��
//===========================
void CTitle::Uninit()
{
	////BGM�̒�~
	//CSound::StopSound();

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
void CTitle::Update()
{
	//----------------------------
	// �J�����̍X�V
	//----------------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//��ʑJ��
	if (CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{
		//�Q�[����ʂɈڍs
		CMode::GetFade()->SetFade(CMode::MODE_TUTORIAL);

		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}
}