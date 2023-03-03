//===================================================
//
// ���b�Z�[�W�̏���
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "message.h"
#include "renderer.h"
#include "game.h"
#include "enemy.h"

//=======================
// �R���X�g���N�^
//=======================
CMessage::CMessage() : CObject2D(2)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
	m_nCntTime = 0;		//���ԃJ�E���g
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
	m_message = MESSAGE_NONE;
}

//=======================
// �f�X�g���N�^
//=======================
CMessage::~CMessage()
{

}

//=======================
// ������
//=======================
HRESULT CMessage::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCntTime = 0;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	switch (m_message)
	{
	//�N���A
	case MESSAGE_CLEAR:
		CObject2D::SetTexture(CTexture::TEXTURE_CLEAR);
		break;

	//�Q�[���I�[�o�[
	case MESSAGE_GAMEOVER:
		CObject2D::SetTexture(CTexture::TEXTURE_GAMEOVER);
		break;

	//�u���C�N
	case MESSAGE_BREAK:
		CObject2D::SetTexture(CTexture::TEXTURE_BREAK);
		break;

	//�X�^�[�g
	case MESSAGE_START:
		CObject2D::SetTexture(CTexture::TEXTURE_START);
		break;

	//�J�E���g1
	case MESSAGE_1:
		CObject2D::SetTexture(CTexture::TEXTURE_1);
		break;

	//�J�E���g2
	case MESSAGE_2:
		CObject2D::SetTexture(CTexture::TEXTURE_2);
		break;

	//�J�E���g3
	case MESSAGE_3:
		CObject2D::SetTexture(CTexture::TEXTURE_3);
		break;

	default:
		break;
	}

	return S_OK;
}

//=======================
// �I��
//=======================
void CMessage::Uninit()
{
	CObject2D::Uninit();
}

//=======================
// �X�V
//=======================
void CMessage::Update()
{
	CObject2D::Update();

	if (m_message != MESSAGE_GAMEOVER)
	{
		//���ԃJ�E���g
		m_nCntTime++;
	}

	//-------------------------
	// �����ɂ���
	//-------------------------
	if (m_nCntTime >= 60)
	{//�J�E���g��60�ȏ�Ȃ�
		m_col.a -= 0.02f;	//�����x�̌���
	}

	if (m_col.a < 0.0f)
	{//���S�ɓ����Ȃ�
		m_nCntTime = 0;
	}

	//�F�̐ݒ�
	CObject2D::SetColor(m_col);
}

//=======================
// �`��
//=======================
void CMessage::Draw()
{
	switch (m_message)
	{
	case MESSAGE_BREAK:
		if (CGame::GetEnemy() != nullptr 
			&& CGame::GetEnemy()->GetState() == CEnemy::ENEMYSTATE_BREAK)
		{//�G���u���C�N��ԂȂ�
			CObject2D::Draw();
		}
		else
		{//�G���u���C�N��Ԃ���Ȃ��Ȃ�����
			m_col.a = 1.0f;	//�����x���ő�ɂ���
			CObject2D::SetColor(m_col);	//�F�̐ݒ�
		}
		break;

	default:
		CObject2D::Draw();
		break;
	}
}

//=======================
// ����
// �����F�ʒu�A���
//=======================
CMessage *CMessage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, MESSAGE message)
{
	CMessage *pMessage = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pMessage = new CMessage;	//����

	if (pMessage != nullptr)
	{//NULL�`�F�b�N
		//�����̑��
		pMessage->m_fWidth = fWidth;	//��
		pMessage->m_fHeight = fHeight;	//����
		pMessage->m_message = message;	//�񋓌^

		//������
		pMessage->Init(D3DXVECTOR3(pos));
		pMessage->SetObjType(OBJTYPE_MESSAGE);
	}

	return pMessage;
}