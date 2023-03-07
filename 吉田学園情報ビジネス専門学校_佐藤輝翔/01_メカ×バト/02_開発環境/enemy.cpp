//===================================================
//
// �G�l�~�[�̏���
// Author:Teruto Sato
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "enemy.h"
#include "object.h"
#include "application.h"
#include "renderer.h"
#include "model.h"
#include "line.h"
#include "game.h"
#include "player.h"
#include "fade.h"
#include "hp.h"
#include "message.h"
#include "utility.h"
#include "debug_proc.h"
#include "utility.h"
#include "camera.h"
#include "sound.h"
#include "combo.h"
#include "input_keyboard.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CEnemy::fDefGravity = 1.0f;	//��{�̏d��

//========================
// �R���X�g���N�^
//========================
CEnemy::CEnemy() : CObject(0)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O�̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�傫���̍ő�l
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�傫���̍ŏ��l
	m_worldMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���[���h��̍ő�l
	m_worldMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���[���h��̍ŏ��l
	m_nMoveTime = 0;		//�ړ��܂ł̎���
	m_nBreakTime = 0;		//�u���C�N��Ԃ̎���
	m_nCntFream = 0;		//�t���[�����̃J�E���g
	m_fLife = 0.0f;			//�̗�
	m_fRemLife = 0.0f;		//�c��̗�(%)
	m_fMaxLife = 0.0f;		//�ő�̗�
	m_fGravity = 0.0f;		//�d�͂̒l
	m_fBreak = 0.0f;
	m_fRemBreak = 0.0f;
	m_fMaxBreak = 0.0f;
	m_bNockBack = false;	//�m�b�N�o�b�N������
	m_pMessage = nullptr;	//���b�Z�[�W

	for (int i = 0; i < GAUGE_MAX; i++)
	{
		m_pHP[i] = nullptr;		//HP
	}

	/* �� ���f����� �� */
	for (int i = 0; i < MAX_ENEMY_PARTS; i++)
	{
		m_pModel[i] = nullptr;
	}

	for (int i = 0; i < nMaxLine; i++)
	{
		m_pLine[i] = nullptr;
	}

	/* �� ���[�V������� �� */
	m_nCurrentKey = 0;
	m_nCntMotion = 0;
	m_type = MOTION_IDOL;

	//-----------------------------------
	// �L�[�Z�b�g���̏�����
	//-----------------------------------
	for (int nCnt = 0; nCnt < MOTION_MAX; nCnt++)
	{
		for (int i = 0; i < MOTION_MAX; i++)
		{
			for (int j = 0; j < MAX_PARTS; j++)
			{
				m_aMotionSet[nCnt].aKeySet[i].aKey[j].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
				m_aMotionSet[nCnt].aKeySet[i].aKey[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
			}

			m_aMotionSet[nCnt].bLoop = false;			//���[�v���邩�ǂ���
			m_aMotionSet[nCnt].aKeySet[i].nFrame = 0;	//�t���[����
			m_aMotionSet[nCnt].nStartCollision = 0;		//�����蔻��̊J�n����
			m_aMotionSet[nCnt].nDamage = 0;				//�_���[�W��
			m_aMotionSet[nCnt].nNumHit = 0;				//�q�b�g��
			m_aMotionSet[nCnt].nHitInterval = 0;		//�q�b�g�Ԋu
		}

		m_aMotionSet[nCnt].nNumKey = 0;
		m_aMotionSet[nCnt].bLoop = false;
	}
}

//========================
// �f�X�g���N�^
//========================
CEnemy::~CEnemy()
{

}

//========================
// ������
//========================
HRESULT CEnemy::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;
	m_nCntMotion = 1;
	m_fLife = 7500.0f;			//�̗�
	m_fRemLife = 100.0f;		//�c��̗�(%)
	m_fMaxLife = m_fLife;		//�ő�̗�
	m_fGravity = fDefGravity;	//�d�͂̒l

	m_fBreak = 150.0f;
	m_fRemBreak = 100.0f;
	m_fMaxBreak = m_fBreak;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//--------------------
	// ���f���̐���
	//--------------------
	SetModel();

	//-----------------------
	// ���f���̑傫����ݒ�
	//-----------------------
	m_vtxMin = D3DXVECTOR3(-80.0f, 0.0f, -150.0f);
	m_vtxMax = D3DXVECTOR3(80.0f, 300.0f, 60.0f);

	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;

	//------------------------------
	// ���[�V�����̓ǂݍ���
	//------------------------------
	GetFileMotion();

	//-----------------------
	// �Q�[�W�̐���
	//-----------------------
	{
		//HP
		D3DXVECTOR3 hpPos(SCREEN_WIDTH / 2, 70.0f, 0.0f);
		m_pHP[GAUGE_HP] = CHP::Create(hpPos, 800.0f, 20.0f, CHP::GAUGETYPE_HP_ENEMY);
		m_pHP[GAUGE_HP]->SetLife(m_fLife, m_fRemLife);	//HP�̐ݒ�

														//�u���C�N�Q�[�W
		D3DXVECTOR3 breakpPos(SCREEN_WIDTH / 2, 110.0f, 0.0f);
		m_pHP[GAUGE_BREAK] = CHP::Create(breakpPos, 800.0f, 15.0f, CHP::GAUGETYPE_BREAK);
		m_pHP[GAUGE_BREAK]->SetLife(m_fBreak, m_fRemBreak);	//HP�̐ݒ�
	}

	return S_OK;
}

//========================
// �I��
//========================
void CEnemy::Uninit()
{
	//-------------------------
	// ���f���̏I��
	//-------------------------
	for (int i = 0; i < MAX_ENEMY_PARTS; i++)
	{//���f���p�[�c������
		if (m_pModel[i])
		{//���f����null����Ȃ��Ȃ�
			m_pModel[i]->Uninit();
			delete m_pModel[i];
			m_pModel[i] = nullptr;
		}
	}

	CObject::Release();
}

//========================
// �X�V
//========================
void CEnemy::Update()
{
	//�O�̈ʒu�̕ۑ�
	m_posOld = m_pos;

	//--------------------------------
	// ���[�V�����̃��Z�b�g
	//--------------------------------
	if (m_type != MOTION_ATTACK
		&& m_type != MOTION_SPIN)
	{//�U�����[�V��������Ȃ��Ȃ�
		//�ҋ@���[�V�����ɂ���
		ChangeMotion(MOTION_IDOL);
	}

	//-------------------------
	// ���f���̍X�V
	//-------------------------s
	for (int i = 0; i < MAX_ENEMY_PARTS; i++)
	{//���f���p�[�c������
		if (m_pModel[i])
		{//���f����null����Ȃ��Ȃ�
			m_pModel[i]->Update();
		}
	}

	if (CGame::GetStart())
	{//�J�n�t���O�������Ă���Ȃ�
		if (m_state == ENEMYSTATE_BREAK)
		{//�u���C�N��ԂȂ�
			//----------------------------
			// �m�b�N�o�b�N���鏈��
			//----------------------------
			NockBack();

			//------------------------
			// �u���C�N��Ԃ��畜�A
			//------------------------
			m_nBreakTime++;	//���Ԃ𐔂���

			if (m_nBreakTime >= 600)
			{//��莞�Ԍo��
				m_state = ENEMYSTATE_NONE;	//�u���C�N��Ԃ���
				m_nBreakTime = 0;			//���Ԃ̃��Z�b�g

				//�u���C�N�Q�[�W���ő�ɂ���
				m_fBreak = m_fMaxBreak;
				m_fRemBreak = m_fBreak * 100 / m_fMaxBreak;

				//�u���C�N�Q�[�W�̍Đ���
				{
					D3DXVECTOR3 breakpPos(SCREEN_WIDTH / 2, 100.0f, 0.0f);
					m_pHP[GAUGE_BREAK] = CHP::Create(breakpPos, 800.0f, 15.0f, CHP::GAUGETYPE_BREAK);
					m_pHP[GAUGE_BREAK]->SetLife(m_fBreak, m_fRemBreak);	//HP�̐ݒ�
				}
			}
		}
		else
		{//�G���u���C�N���Ă��Ȃ��Ȃ�
			//------------------------
			// �G�̍s��
			//------------------------
			EnemyAI();

			//�ړ����E�̊m�F
			m_pos = CUtility::LimitMove(m_pos);
		}

		//-------------------------
		// ���̍X�V
		//-------------------------
		//UpdateLine();

		//---------------------
		// �d�͂̉��Z
		//---------------------
		if (m_pos.y >= 0.0f)
		{//���ł���Ȃ�
			m_pos.y -= m_fGravity;
			m_fGravity += 3.0f;
		}
		else
		{//�n�ʂɒ�������
			//�d�͂̒l�����Z�b�g
			m_fGravity = fDefGravity;

			m_pos.y = 0.0f;		//������n�ʂɍ��킹��
		}
	}

	//--------------------------------
	// �v���C���[�Ƃ̓����蔻��
	//--------------------------------
	m_pos = CUtility::GetCollisionPos(m_pos, m_posOld, m_size, m_mtxWorld
			, CObject::OBJTYPE_PLAYER);

	//--------------------------------
	// ���[�V�����̐ݒ�
	//--------------------------------
	SetMotion(m_type, m_aMotionSet[m_type].bLoop, m_aMotionSet[m_type].nNumKey);

	//----------------------------
	// ���S������
	//----------------------------
	if (m_fLife <= 0)
	{//�̗͂��s������
		CGame::SetDeathEnemy();	//�G�����񂾏��

		//HP�o�[�̏���
		for (int i = 0; i < GAUGE_MAX; i++)
		{
			if (m_pHP[i] != nullptr)
			{//null����Ȃ��Ȃ�
				m_pHP[i]->Uninit();
			}
		}

		//����
		Uninit();
	}

#ifdef _DEBUG
	if (CInputKeyboard::Trigger(DIK_2))
	{
		//�̗͂̌���
		m_fLife = 100.0f;
		m_fRemLife = m_fLife * 100 / m_fMaxLife;
		m_pHP[GAUGE_HP]->SetLife(m_fLife, m_fRemLife);
	}
#endif // _DEBUG

}

//========================
// �`��
//========================
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���f���̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���f���̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//���f���̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//-------------------------
	// ���f���̕`��
	//-------------------------
	for (int i = 0; i < MAX_ENEMY_PARTS; i++)
	{//���f���p�[�c������
		if (!m_pModel[i])
		{//���f����null�Ȃ�
			return;
		}

		m_pModel[i]->Draw(&m_mtxWorld);
	}
}

//========================
// ����
//========================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pEnemy = new CEnemy;	//����

	if (pEnemy != nullptr)
	{//NULL�`�F�b�N
		//�ϐ��ɑ��
		pEnemy->m_rot = rot;

		//������
		pEnemy->Init(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}

//========================
// ���f���̐���
//========================
void CEnemy::SetModel()
{
	//��
	m_pModel[0] = CModel::Create("data\\MODEL\\Enemy\\body.x", nullptr,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�E�n���}�[
	m_pModel[1] = CModel::Create("data\\MODEL\\Enemy\\armR.x", m_pModel[0],
		D3DXVECTOR3(-200.0f, 80.0f, -80.0f), D3DXVECTOR3(0.0f, 0.0f, 0.5f));

	//���n���}�[
	m_pModel[2] = CModel::Create("data\\MODEL\\Enemy\\armL.x", m_pModel[0],
		D3DXVECTOR3(200.0f, 80.0f, -80.0f), D3DXVECTOR3(0.0f, 0.0f, -0.5f));
}

//========================
// ���̐ݒu
//========================
void CEnemy::SetLine()
{
	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�ϊ��s����g����Min,Max�����߂�
	D3DXVec3TransformCoord(&m_worldMin, &m_vtxMin, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_worldMax, &m_vtxMax, &m_mtxWorld);

	//�������l���܂Ƃ߂�
	D3DXVECTOR3 min = m_worldMin;
	D3DXVECTOR3 max = m_worldMax;

	for (int i = 0; i < nMaxLine; i++)
	{
		m_pLine[i] = CLine::CreateAll(m_pLine[i], i, m_pos, min, max);
	}
}

//========================
// ���̏��̍X�V
//========================
void CEnemy::UpdateLine()
{
	//���[���h�ϊ��s����g����Min,Max�����߂�
	D3DXVec3TransformCoord(&m_worldMin, &m_vtxMin, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_worldMax, &m_vtxMax, &m_mtxWorld);

	//�������l���܂Ƃ߂�
	D3DXVECTOR3 min = m_worldMin;
	D3DXVECTOR3 max = m_worldMax;

	for (int i = 0; i < nMaxLine; i++)
	{
		if (m_pLine[i])
		{
			m_pLine[i]->SetLinePos(i, min, max);
		}
	}
}

//========================
// HP�������̏���
//========================
void CEnemy::SubGauge(float fDamage, GAUGE type)
{
	switch (type)
	{
		//-----------------------
		// HP�����炷����
		//-----------------------
	case GAUGE_HP:
		if (!m_pHP[GAUGE_HP])
		{//null�Ȃ�
			return;
		}

		m_fLife -= round(fDamage);	//�̗͂̌���

		//�c��̗͂��v�Z
		m_fRemLife = m_fLife * 100 / m_fMaxLife;

		if (m_fRemLife < 1 && m_fRemLife > 0)
		{//�c��̗͂�1%���� ���� 0����Ȃ�
			m_fRemLife = 1;
		}

		//HP�̐ݒ�
		m_pHP[GAUGE_HP]->SetLife(m_fLife, m_fRemLife);

		if (m_fLife < 0 && m_fRemLife < 0)
		{//HP�Q�[�W���s������
			if (m_pHP[GAUGE_HP])
			{//null�`�F�b�N
				m_pHP[GAUGE_HP] = nullptr;
			}

			//���b�Z�[�W�̕\��
			{
				D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
				m_pMessage = CMessage::Create(pos, 600.0f, 200.0f, CMessage::MESSAGE_CLEAR);
			}

			//�u���C�N�Q�[�W������
			m_fBreak = 0;
			m_fRemBreak = m_fBreak * 100 / m_fMaxBreak;
			return;
		}
		break;

		//--------------------------------
		// �u���C�N�Q�[�W�����炷����
		//--------------------------------
	case GAUGE_BREAK:
		if (!m_pHP[GAUGE_BREAK])
		{//null�Ȃ�
			return;
		}

		m_fBreak -= round(fDamage);
		m_fRemBreak = m_fBreak * 100 / m_fMaxBreak;

		if (m_fRemBreak < 1 && m_fRemBreak > 0)
		{//�c��u���C�N�Q�[�W��1%���� ���� 0����Ȃ�
			m_fRemBreak = 1;
		}

		m_pHP[GAUGE_BREAK]->SetLife(m_fBreak, m_fRemBreak);

		if (m_fBreak < 0 || m_fRemBreak < 0)
		{//�u���C�N�Q�[�W���s������
			if (m_pHP[GAUGE_BREAK])
			{
				m_pHP[GAUGE_BREAK] = nullptr;
			}

			//�u���C�N��Ԃɂ���
			m_state = ENEMYSTATE_BREAK;

			//�����̕\��
			{
				D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
				m_pMessage = CMessage::Create(pos, 600.0f, 200.0f, CMessage::MESSAGE_BREAK);
			}

			//�ҋ@���[�V�����ɂ���
			ChangeMotion(MOTION_IDOL);

			CSound::PlaySound(CSound::SOUND_LABEL_SE_BREAK);
		}
		break;

	default:
		break;
	}
}

//========================
// �U������
//========================
void CEnemy::EnemyAI()
{
	//�ϐ��錾
	int nMaxAttackTime = 200;		//�U������
	float fAttackArea = 300.0f;		//�G�̍U���͈�
	float fMoveArea = 200.0f;

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPosition();

	//�G�ƃv���C���[�Ԃ̋������v�Z
	D3DXVECTOR3 vec = playerPos - m_pos;

	//�����̐�Βl���v�Z
	float fDistance = fabs((vec.x + vec.z) / 2);

	//-------------------------
	// �v���C���[�܂ňړ�
	//-------------------------
	if (m_type != MOTION_ATTACK && m_type != MOTION_SPIN
		&& fDistance >= fMoveArea)
	{//�U��������Ȃ� & �v���C���[���͈͓��ɂ��Ȃ��Ȃ�
		Rotation(playerPos);	//��]
		Move(playerPos);		//�ړ�
	}

	//-------------------------
	// �v���C���[�̕�������
	//-------------------------
	if (m_type == MOTION_ATTACK
		&& m_nCntFream <= m_aMotionSet[m_type].aKeySet[0].nFrame)
	{//�U�����[�V������ & �n���}�[��U��グ�Ă���ԂȂ�
		Rotation(playerPos);	//��]
	}
	
	//-------------------------
	// �U������
	//-------------------------
	if (m_type != MOTION_MOVE && m_type != MOTION_ATTACK && m_type != MOTION_SPIN
		&& fDistance <= fAttackArea)
	{//�U�����[�V����������Ȃ� & �v���C���[���͈͓��ɂ���Ȃ�
		//�U���܂ł̎��Ԃ����Z
		m_nAttackTime++;

		if (m_nAttackTime >= nMaxAttackTime)
		{//�U�����Ԃ��l�ɒB������
			//--------------------------
			// �U�����[�V�����ɂ���
			//--------------------------
			int nRand = rand() % 2;
			if (nRand == 0)
			{
				ChangeMotion(MOTION_ATTACK);
			}
			else if (nRand == 1)
			{
				ChangeMotion(MOTION_SPIN);
			}

			//�U�����Ԃ̃��Z�b�g
			m_nAttackTime = 0;
		}
	}

	//�U������
	Attack();
}

//==========================================
// �U������
//==========================================
void CEnemy::Attack()
{
	if (m_type != MOTION_ATTACK && m_type != MOTION_SPIN)
	{
		return;
	}

	//------------------------------------------
	// ���[�V�����ƍU�����Ԃ����킹��
	//------------------------------------------
	int nAttackFream = 0;
	int nOutRigor = 0;
	for (int i = 0; i < m_aMotionSet[m_type].nNumKey; i++)
	{//�L�[��-1�񕪉�
		//�U�����[�V�����̃t���[���������v����
		nAttackFream += m_aMotionSet[m_type].aKeySet[i].nFrame;

		if (i != m_aMotionSet[m_type].nNumKey - 1)
		{//�d���L�[����Ȃ��Ȃ�
			//���[�V�����̃t���[���������Z
			nOutRigor += m_aMotionSet[m_type].aKeySet[i].nFrame;
		}
	}

	//------------------------------------------
	// �U���̏I��
	//------------------------------------------
	if (m_nCntFream >= nAttackFream)
	{//�t���[�������U�����[�V�����̃t���[�����̍��v�𒴂�����
		//�ҋ@���[�V�����ɂ���
		ChangeMotion(MOTION_IDOL);
	}
	else
	{
		//�t���[�����̃J�E���g
		m_nCntFream++;
	}

	//------------------------------------------
	// �n���}�[�̓����蔻��
	//------------------------------------------
	if (!CGame::GetPlayer()->GetAvoidance())
	{//�v���C���[�̉����Ԃ���Ȃ��Ȃ�
		HitHummer();
	}
}

//==========================================
// �n���}�[�̓����蔻��
//==========================================
void CEnemy::HitHummer()
{
	//----------------------------------
	// �ϐ��錾
	//----------------------------------
	D3DXVECTOR3 offset(0.0f, 280.0f, 0.0f);				//����̐�ւ̃I�t�Z�b�g���W
	D3DXMATRIX mtxR = m_pModel[1]->GetmtxWorld();		//�E�n���}�[�̃}�g���b�N�X
	D3DXMATRIX mtxL = m_pModel[2]->GetmtxWorld();		//���n���}�[�̃}�g���b�N�X
	CObject::EObjType player = CObject::OBJTYPE_PLAYER;	//�@�����肪�v���C���[
	float fSphereSize = 280.0f;	//���̒��a

	//----------------------------------
	// �����蔻��
	//----------------------------------
	if (CUtility::ColliaionWeapon(offset, fSphereSize, mtxR, player)
		|| CUtility::ColliaionWeapon(offset, fSphereSize, mtxL, player))
	{//�n���}�[���v���C���[�ɓ�������
		if (m_nCntFream >= m_aMotionSet[m_type].nStartCollision
			&& !m_bHitAtk
			&& m_aMotionSet[m_type].nNumHit > m_nCntHit)
		{//�U�����Ԃ������蔻��̊J�n���Ԃ𒴂��� & �U�����������Ă��Ȃ�
		 //�q�b�g�����������Ȃ��Ȃ�

			//�v���C���[�Ƀ_���[�W
			CGame::GetPlayer()->AddLife((float)-m_aMotionSet[m_type].nDamage);
			m_bHitAtk = true;					//�������Ă����Ԃɂ���
			m_nCntHit++;

			//�v���C���[�̃R���{����0�ɂ���
			CGame::GetPlayer()->GetCombo()->ResetCombo();

			//--------------------------------
			// �v���C���[�̃m�b�N�o�b�N
			//--------------------------------
			if (m_type == MOTION_ATTACK)
			{//�@�����U���Ȃ�
				//�m�b�N�o�b�N������
				CGame::GetPlayer()->NockBack(150.0f);
			}
			else if (m_type == MOTION_SPIN)
			{//��]�U���Ȃ�
				CGame::GetPlayer()->NockBack(100.0f);
			}

			//SE�̍Đ�
			CSound::PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		}

		if (m_type == MOTION_ATTACK)
		{
			//�J�����̐U��(�c�h��)
			CGame::GetCamera()->ShakeCamera(10, 0.2f, D3DXVECTOR3(40.0f, 180.0f, 40.0f));
		}
		else
		{
			//�J�����̐U��(����)
			//CGame::GetCamera()->ShakeCamera(10, 0.2f, D3DXVECTOR3(100.0f, 100.0f, 100.0f));
			CGame::GetCamera()->ShakeCamera(10, 0.2f, D3DXVECTOR3(180.0f, 40.0f, 40.0f));
		}
	}

	//----------------------------------
	// ���i�q�b�g���鏈��
	//----------------------------------
	if (m_bHitAtk)
	{//�������Ă�����
		m_nHitTime++;

		if (m_nHitTime >= m_aMotionSet[m_type].nHitInterval)
		{//�q�b�g�܂ł̎��Ԃ��q�b�g�Ԋu�𒴂�����
			m_bHitAtk = false;
		}
	}
}

//==========================================
// �m�b�N�o�b�N���鏈��
//==========================================
void CEnemy::NockBack()
{
	if (CGame::GetPlayer()->GetHitAttack())
	{//�v���C���[���U���𓖂Ă���ԂȂ�
		//���Z�b�g
		m_nAttackTime = 0;			//�U���܂ł̎���
		m_fGravity = fDefGravity;	//�d�͂̒l

		//--------------------------------
		// �m�b�N�o�b�N���鏈��
		//--------------------------------
		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPosition();

		//�G�ƃv���C���[�Ԃ̃x�N�g�����v�Z
		D3DXVECTOR3 vec = playerPos - m_pos;

		D3DXVec3Normalize(&vec, &vec);	//�x�N�g���̐��K��

		if (!m_bNockBack)
		{//�m�b�N�o�b�N���Ă��Ȃ��Ȃ�
			m_pos += -vec * 2.0f;	//�t�x�N�g�������Ɉړ�
			m_pos.y += 100.0f;		//�㏸
			m_bNockBack = true;
		}
	}
	else
	{
		m_bNockBack = false;
	}
}

//==========================================
// �ړ�����
//==========================================
void CEnemy::Move(D3DXVECTOR3 targetPos)
{
	//------------------------------
	// �v���C���[�Ɍ������Ĉړ�
	//------------------------------
	//�v���C���[�ƓG�̃x�N�g�������߂�
	D3DXVECTOR3 vec(targetPos - m_pos);

	//�x�N�g���̐��K��
	D3DXVec3Normalize(&vec, &vec);

	//�v���C���[�Ɍ������Ĉړ�
	m_move = vec * 4.5f;
	m_pos += m_move;

	//�ړ����[�V�����ɂ���
	ChangeMotion(MOTION_MOVE);
}

//==========================================
// ��]����
//==========================================
void CEnemy::Rotation(D3DXVECTOR3 targetPos)
{
	//------------------------------
	// �ړI�̕���������
	//------------------------------
	//2�_�Ԃ̋��������߂�
	float X = m_pos.x - targetPos.x;
	float Z = m_pos.z - targetPos.z;

	//�p�x�̐ݒ�
	float angle = atan2f(X, Z);

	//�����̐ݒ�
	m_rotDest = D3DXVECTOR3(0.0f, angle, 0.0f);

	//-------------------------------
	// �ړI�̊p�x�̐��K��
	//-------------------------------
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{//��]�������p�x��180�ȏ�Ȃ�
		m_rotDest.y -= D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{//��]�������p�x��-180�ȉ��Ȃ�
		m_rotDest.y += D3DX_PI * 2;
	}

	//-------------------------------
	// �ړI�̊p�x�܂ŉ�]����
	//-------------------------------
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;	//��������

	//-------------------------------
	// �p�x�̐��K��
	//-------------------------------
	m_rot.y = CUtility::GetNorRot(m_rot.y);
}

//==========================================
// �t�@�C�����烂�[�V���������擾
//==========================================
void CEnemy::GetFileMotion()
{
	const int nMaxText = 256;	//�����̍ő吔

	FILE *pFile;				//�t�@�C���|�C���^��錾����
	char cText[nMaxText];		//1�s���̕����ǂݎ��p�ϐ�
	char cTextHead[nMaxText];	//�����������悤�̕ϐ�
	int nNumMotion = 0;			//�ǂݍ��ݒ��̃��[�V�����ԍ�
	int nNumKey = 0;			//�ǂݍ��ݒ��̃L�[�ԍ�
	int nNumParts = 0;			//�ǂݍ��ݒ��̃p�[�c�ԍ�

	//--------------------------------
	// �t�@�C���̓ǂݍ���
	//--------------------------------
	//�t�@�C�����J��
	pFile = fopen("data/MOTION/enemy.txt", "r");

	if (pFile == nullptr)
	{//�J���Ȃ�������
		assert(false);
	}

	//�����̓ǂݎ�菈��
	while (fgets(cText, nMaxText, pFile) != nullptr)
	{
		//������̕���
		sscanf(cText, "%s", &cTextHead);

		//========================================
		// ���[�V�������
		//========================================
		if (strcmp(&cTextHead[0], "MOTIONSET") == 0)
		{//��������MOTIONSET�Ȃ�
		 //�����̓ǂݎ�菈��
			while (fgets(cText, nMaxText, pFile) != nullptr)
			{
				//������̕���
				sscanf(cText, "%s", &cTextHead);

				//-------------------------------
				// ���[�v���邩�ǂ���
				//-------------------------------
				if (strcmp(&cTextHead[0], "LOOP") == 0)
				{//��������LOOP�Ȃ�
					int nLoop = 0;

					//�����񂩂烋�[�v�̒l��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &nLoop);

					if (nLoop == 0)
					{//�ǂݎ�����l��0�Ȃ�
						m_aMotionSet[nNumMotion].bLoop = false;
					}
					else if (nLoop == 1)
					{//�ǂݎ�����l��1�Ȃ�
						m_aMotionSet[nNumMotion].bLoop = true;
					}
				}
				//-------------------------------
				// �L�[�̍ő吔
				//-------------------------------
				else if (strcmp(&cTextHead[0], "NUM_KEY") == 0)
				{//��������NUM_KEY�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nNumKey);
				}
				//-------------------------------
				// �����蔻��̊J�n����
				//-------------------------------
				else if (strcmp(&cTextHead[0], "COLLISION") == 0)
				{//��������COLLISION�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nStartCollision);
				}
				//-------------------------------
				// �_���[�W��
				//-------------------------------
				else if (strcmp(&cTextHead[0], "NUM_DAMAGE") == 0)
				{//��������DAMAGE�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nDamage);
				}
				//-------------------------------
				// �q�b�g��
				//-------------------------------
				else if (strcmp(&cTextHead[0], "NUM_HIT") == 0)
				{//��������NUM_HIT�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nNumHit);
				}
				//-------------------------------
				// �q�b�g�Ԋu
				//-------------------------------
				else if (strcmp(&cTextHead[0], "HIT_INTERVAL") == 0)
				{//��������HIT_INTERVAL�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nHitInterval);
				}
				//========================================
				// �L�[�Z�b�g���
				//========================================
				else if (strcmp(&cTextHead[0], "KEYSET") == 0)
				{//��������KEYSET�Ȃ�
					//�����̓ǂݎ�菈��
					while (fgets(cText, nMaxText, pFile) != nullptr)
					{
						//������̕���
						sscanf(cText, "%s", &cTextHead);

						//-------------------------------
						// �t���[����
						//-------------------------------
						if (strcmp(&cTextHead[0], "FRAME") == 0)
						{//��������FRAME�Ȃ�
							//�����񂩂�L�[�̍ő吔��ǂݎ��
							sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].aKeySet[nNumKey].nFrame);
						}
						//========================================
						// �L�[���
						//========================================
						else if (strcmp(&cTextHead[0], "KEY") == 0)
						{//��������KEY�Ȃ�
							//�����̓ǂݎ�菈��
							while (fgets(cText, nMaxText, pFile) != nullptr)
							{
								//������̕���
								sscanf(cText, "%s", &cTextHead);

								//-------------------------------
								// �ʒu
								//-------------------------------
								if (strcmp(&cTextHead[0], "POS") == 0)
								{//��������POS�Ȃ�
									//�����񂩂�ʒu��ǂݎ��
									sscanf(cText, "%s = %f %f %f", &cTextHead,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].pos.x,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].pos.y,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].pos.z);
								}
								//-------------------------------
								// ����
								//-------------------------------
								else if (strcmp(&cTextHead[0], "ROT") == 0)
								{//��������ROT�Ȃ�
									//�����񂩂������ǂݎ��
									sscanf(cText, "%s = %f %f %f", &cTextHead,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].rot.x,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].rot.y,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].rot.z);
								}
								else if (strcmp(&cTextHead[0], "END_KEY") == 0)
								{//�L�[�̓ǂݎ�肪�I��������
									if (nNumParts + 1 < MAX_ENEMY_PARTS)
									{//�p�[�c���𒴂��Ȃ��Ȃ�
										//�p�[�c�ԍ��̉��Z
										nNumParts++;
									}
									else
									{//�p�[�c�����ǂݍ��񂾂�
										//�p�[�c�ԍ������Z�b�g
										nNumParts = 0;
									}
									break;
								}
							}
						}
						else if (strcmp(&cTextHead[0], "END_KEYSET") == 0)
						{//�L�[�Z�b�g�̓ǂݎ�肪�I��������
							if (nNumKey < m_aMotionSet[nNumMotion].nNumKey)
							{//�L�[�����ő傶��Ȃ��Ȃ�
								//�L�[�ԍ��̉��Z
								nNumKey++;
							}
							break;
						}
					}
				}
				else if (strcmp(&cTextHead[0], "END_MOTIONSET") == 0)
				{//���[�V�����̓ǂݎ�肪�I��������
					//�L�[�ԍ������Z�b�g
					nNumKey = 0;
					//���[�V�����ԍ��̉��Z
					nNumMotion++;
					break;
				}
			}
		}

		//----------------------------------
		// �ۑ����̕�����̏�����
		//----------------------------------
		ZeroMemory(&cText, sizeof(cText));
		ZeroMemory(&cTextHead, sizeof(cTextHead));
	}

	//�t�@�C�������
	fclose(pFile);
}

//==========================================
// ���[�V�����̐ݒ�
// �����F��ށA���[�v��ԁA�L�[��
//==========================================
void CEnemy::SetMotion(MOTION_TYPE type, bool bLoop, int nNumKey)
{
	if (m_nCurrentKey + 1 >= nNumKey)
	{//�L�[���ő吔�ɒB������
		if (bLoop)
		{//���[�v����Ȃ�
			m_nCurrentKey = 0;	//�L�[�ԍ��̏�����
		}
		else
		{
			return;
		}
	}

	for (int i = 0; i < MAX_ENEMY_PARTS; i++)
	{//���f���p�[�c������
		//-------------------------------------------------------
		// NULL�`�F�b�N
		//-------------------------------------------------------
		if (!m_pModel[i])
		{//���f���p�[�c��null�Ȃ�
			return;
		}

		//�L�[�����������ϐ�
		KEY key = m_aMotionSet[type].aKeySet[m_nCurrentKey].aKey[i];
		KEY keyNext = m_aMotionSet[type].aKeySet[m_nCurrentKey + 1].aKey[i];

		//-------------------------------------------------------
		// ���ݒl���擾
		//-------------------------------------------------------
		//�ʒu���擾
		float fPosX = m_pModel[i]->GetPos().x;
		float fPosY = m_pModel[i]->GetPos().y;
		float fPosZ = m_pModel[i]->GetPos().z;

		//�������擾
		float fRotX = m_pModel[i]->GetRot().x;
		float fRotY = m_pModel[i]->GetRot().y;
		float fRotZ = m_pModel[i]->GetRot().z;

		//-------------------------------------------------------
		// �����̌v�Z
		// (�I���l - �J�n�l)
		//-------------------------------------------------------
		//�ʒu
		float fDifPosX = keyNext.pos.x - key.pos.x;
		float fDifPosY = keyNext.pos.y - key.pos.y;
		float fDifPosZ = keyNext.pos.z - key.pos.z;

		//����
		float fDifRotX = keyNext.rot.x - key.rot.x;
		float fDifRotY = keyNext.rot.y - key.rot.y;
		float fDifRotZ = keyNext.rot.z - key.rot.z;

		//-------------------------------------------------------
		// �����̊p�x�̐��K��
		//-------------------------------------------------------
		fDifRotX = CUtility::GetNorRot(fDifRotX);	//X�̒l
		fDifRotY = CUtility::GetNorRot(fDifRotY);	//Y�̒l
		fDifRotZ = CUtility::GetNorRot(fDifRotZ);	//Z�̒l

		//-------------------------------------------------------
		// ���Βl�̌v�Z
		// (���[�V�����J�E���^�[ / �t���[����)
		//-------------------------------------------------------
		float fNumRelative = m_nCntMotion / (float)m_aMotionSet[type].aKeySet[m_nCurrentKey].nFrame;

		//-------------------------------------------------------
		// ���ݒl�̌v�Z
		// (�J�n�l + (���� * ���Βl))
		//-------------------------------------------------------
		//�����l�̎擾
		D3DXVECTOR3 initPos = m_pModel[i]->GetInitPos();
		D3DXVECTOR3 initRot = m_pModel[i]->GetInitRot();

		//�ʒu
		fPosX = initPos.x + key.pos.x + (fDifPosX * fNumRelative);
		fPosY = initPos.y + key.pos.y + (fDifPosY * fNumRelative);
		fPosZ = initPos.z + key.pos.z + (fDifPosZ * fNumRelative);

		//����
		fRotX = initRot.x + key.rot.x + (fDifRotX * fNumRelative);
		fRotY = initRot.y + key.rot.y + (fDifRotY * fNumRelative);
		fRotZ = initRot.z + key.rot.z + (fDifRotZ * fNumRelative);

		//-------------------------------------------------------
		// ���f�����̐ݒ�
		//-------------------------------------------------------
		//�ʒu�̐ݒ�
		m_pModel[i]->SetPos(D3DXVECTOR3(fPosX, fPosY, fPosZ));

		//�����̐ݒ�
		m_pModel[i]->SetRot(D3DXVECTOR3(fRotX, fRotY, fRotZ));
	}

	//���[�V�����J�E���^�[��i�߂�
	m_nCntMotion++;

	//--------------------------------
	// ������
	//--------------------------------
	if (m_nCntMotion >= m_aMotionSet[type].aKeySet[m_nCurrentKey].nFrame)
	{//���[�V�����J�E���^�[���Đ��t���[���ɒB������
		m_nCurrentKey++;	//�L�[�ԍ������Z
		m_nCntMotion = 0;	//���[�V�����J�E���^�[��������
	}
}

//==========================================
// ���[�V�����̕ύX
// �����F�ύX���������[�V�����̗�
//==========================================
void CEnemy::ChangeMotion(MOTION_TYPE type)
{
	//���[�V�����̕ύX
	m_type = type;

	//--------------------------
	// ���̏�����
	//--------------------------
	if (m_type == MOTION_ATTACK
		|| m_type == MOTION_SPIN)
	{//�U�������Ȃ�
		//���[�V�����̏�����
		m_nCurrentKey = 0;
		m_nCntMotion = 0;

		//�U���֘A�̏�����
		m_bHitAtk = false;	//�U���𓖂ĂĂȂ����
		m_nCntFream = 0;	//�U���t���[����������
		m_nCntHit = 0;		//�q�b�g�J�E���g��������
		m_nHitTime = 0;		//�q�b�g���Ԃ�������
	}
}