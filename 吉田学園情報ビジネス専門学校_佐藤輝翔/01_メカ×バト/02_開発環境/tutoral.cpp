//===================================================
//
// �`���[�g���A���̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "tutorial.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "application.h"
#include "sound.h"
#include "bg.h"
#include "fade.h"
#include "ranking.h"

//===========================
// �R���X�g���N�^
//===========================
CTutorial::CTutorial()
{
	m_nNumber = 0;	//�ԍ�

	for (int i = 0; i < nMaxBg; i++)
	{
		m_pBg[i] = nullptr;	//�w�i
	}
}

//===========================
// �f�X�g���N�^
//===========================
CTutorial::~CTutorial()
{

}

//===========================
// ������
//===========================
HRESULT CTutorial::Init()
{
	m_nNumber = TYPE_MANUAL;;

	{
		//�w�i�̐���
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		m_pBg[m_nNumber] = CBg::Create(pos, CBg::BGTYPE_MANUAL);
	}

	////BGM�̍Đ�
	//CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// �I��
//===========================
void CTutorial::Uninit()
{
	//BGM�̒�~
	CSound::StopSound();
}

//===========================
// �X�V
//===========================
void CTutorial::Update()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//�����ʒu
	D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	//��ʑJ��
	if (CInputKeyboard::AllTrigger()
		|| joypad->AllTrigger())
	{
		if (m_nNumber < TYPE_GAME && m_pBg[m_nNumber])
		{
			m_pBg[m_nNumber] = nullptr;

			m_nNumber++;
		}

		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}
	//else if (CInputKeyboard::Trigger(DIK_BACK) || joypad->Trigger(CInputJoypad::JOYKEY_A))
	//{
	//	if (m_nNumber > 0 && m_pBg[m_nNumber])
	//	{
	//		m_pBg[m_nNumber] = nullptr;

	//		m_nNumber--;
	//	}

	//	//SE�̍Đ�
	//	CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	//}

	//-------------------------------
	// ��ʐ؂�ւ�
	//-------------------------------
	if (m_nNumber == TYPE_MANUAL)
	{//0�ԂȂ�
		if (!m_pBg[0])
		{//null�Ȃ�
			m_pBg[0] = CBg::Create(pos, CBg::BGTYPE_MANUAL);
		}
	}
	else if (m_nNumber == TYPE_TUTORIAL1)
	{//1�ԂȂ�
		if (!m_pBg[1])
		{//null�Ȃ�
			m_pBg[1] = CBg::Create(pos, CBg::BGTYPE_TUTORIAL1);
		}
	}
	else if (m_nNumber == TYPE_TUTORIAL2)
	{//2�ԂȂ�
		if (!m_pBg[2])
		{//null�Ȃ�
			m_pBg[2] = CBg::Create(pos, CBg::BGTYPE_TUTORIAL2);
		}
	}
	else
	{
		//�Q�[����ʂɈڍs
		CApplication::GetFade()->SetFade(CApplication::MODE_GAME);
	}
}