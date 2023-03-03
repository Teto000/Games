//===================================================
//
// ���C���̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "line.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "object3d.h"
#include "game.h"
#include "player.h"
#include "model.h"

//===========================
// �R���X�g���N�^
//===========================
CLine::CLine() : CObject(0)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�n�_
	m_end = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�I�_
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^
	m_pObject3D = nullptr;
}

//===========================
// �f�X�g���N�^
//===========================
CLine::~CLine()
{
	assert(m_pVtxBuff == nullptr);
}

//===========================
// ������
//===========================
HRESULT CLine::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;

	if (m_pObject3D != nullptr)
	{
		m_pObject3D->Init(m_pos);
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * nMaxLine,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								nullptr);

	//-------------------------------
	//	���_���̐ݒ�
	//-------------------------------
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nMaxLine; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = m_start;
		pVtx[1].pos = m_end;

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;

		pVtx += 2;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
// �I��
//===========================
void CLine::Uninit()
{
	if (m_pObject3D != nullptr)
	{
		m_pObject3D->Uninit();
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject::Release();
}

//===========================
// �X�V
//===========================
void CLine::Update()
{
	//-------------------------------
	//	���_���̐ݒ�
	//-------------------------------
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nMaxLine; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = m_start;
		pVtx[1].pos = m_end;

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;

		pVtx += 2;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �`��
//===========================
void CLine::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_LINELIST,	//�v���~�e�B�u�̎��
						   2,				//�`�悷��ŏ��̒��_�C���f�b�N�X
						   1);				//�`�悷��v���~�e�B�u��

	//���C�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===========================
// ���̐ݒ�
// �����F�ʒu�A�n�_�A�I�_�A�F
//===========================
CLine* CLine::Create(
	D3DXVECTOR3 pos, D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col)
{
	CLine* pLine = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pLine = new CLine;	//����
	pLine->m_pObject3D = new CObject3D(0);

	if (pLine != nullptr)
	{//NULL�`�F�b�N
		//�ϐ��ɑ��
		pLine->m_start = start;	//�n�_
		pLine->m_end = end;		//�I�_
		pLine->m_col = col;		//�F

		//������
		pLine->Init(pos);
	}

	return pLine;
}

//===========================
// �S�Ă̐��̐���
//===========================
CLine* CLine::CreateAll(CLine* line, int nNumber,
					D3DXVECTOR3 pos, D3DXVECTOR3 min, D3DXVECTOR3 max)
{
	//�ϐ�
	D3DXVECTOR3 start(0.0f, 0.0f, 0.0f);		//�J�n�ʒu
	D3DXVECTOR3 end(0.0f, 0.0f, 0.0f);			//�I���ʒu
	D3DXCOLOR lineCol(1.0f, 0.0f, 0.0f, 1.0f);	//���̐F

	//-----------------------------------
	// ����
	//-----------------------------------
	switch (nNumber)
	{
	case 0:
		start = D3DXVECTOR3(min.x, min.y, min.z);
		end = D3DXVECTOR3(max.x, min.y, min.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 1:
		start = D3DXVECTOR3(min.x, min.y, min.z);
		end = D3DXVECTOR3(min.x, min.y, max.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 2:
		start = D3DXVECTOR3(max.x, min.y, min.z);
		end = D3DXVECTOR3(max.x, min.y, max.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 3:
		start = D3DXVECTOR3(min.x, min.y, max.z);
		end = D3DXVECTOR3(max.x, min.y, max.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	//-----------------------------------
	// ���
	//-----------------------------------
	case 4:
		start = D3DXVECTOR3(min.x, max.y, min.z);
		end = D3DXVECTOR3(max.x, max.y, min.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 5:
		start = D3DXVECTOR3(min.x, max.y, min.z);
		end = D3DXVECTOR3(min.x, max.y, max.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 6:
		start = D3DXVECTOR3(max.x, max.y, min.z);
		end = D3DXVECTOR3(max.x, max.y, max.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 7:
		start = D3DXVECTOR3(min.x, max.y, max.z);
		end = D3DXVECTOR3(max.x, max.y, max.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	//-----------------------------------
	// �c��
	//-----------------------------------
	case 8:
		start = D3DXVECTOR3(min.x, min.y, min.z);
		end = D3DXVECTOR3(min.x, max.y, min.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 9:
		start = D3DXVECTOR3(min.x, min.y, max.z);
		end = D3DXVECTOR3(min.x, max.y, max.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 10:
		start = D3DXVECTOR3(max.x, min.y, min.z);
		end = D3DXVECTOR3(max.x, max.y, min.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;

	case 11:
		start = D3DXVECTOR3(max.x, min.y, max.z);
		end = D3DXVECTOR3(max.x, max.y, max.z);
		line = CLine::Create(pos, start, end, lineCol);
		break;
	}

	return line;
}

//===========================
// ���̊J�n�I���ʒu��ݒ�
//===========================
void CLine::SetLinePos(int nNumber, D3DXVECTOR3 min, D3DXVECTOR3 max)
{
	//-----------------------------------
	// ����
	//-----------------------------------
	switch (nNumber)
	{
	case 0:
		m_start = D3DXVECTOR3(min.x, min.y, min.z);
		m_end = D3DXVECTOR3(max.x, min.y, min.z);
		break;

	case 1:
		m_start = D3DXVECTOR3(min.x, min.y, min.z);
		m_end = D3DXVECTOR3(min.x, min.y, max.z);
		break;

	case 2:
		m_start = D3DXVECTOR3(max.x, min.y, min.z);
		m_end = D3DXVECTOR3(max.x, min.y, max.z);
		break;

	case 3:
		m_start = D3DXVECTOR3(min.x, min.y, max.z);
		m_end = D3DXVECTOR3(max.x, min.y, max.z);
		break;

		//-----------------------------------
		// ���
		//-----------------------------------
	case 4:
		m_start = D3DXVECTOR3(min.x, max.y, min.z);
		m_end = D3DXVECTOR3(max.x, max.y, min.z);
		break;

	case 5:
		m_start = D3DXVECTOR3(min.x, max.y, min.z);
		m_end = D3DXVECTOR3(min.x, max.y, max.z);
		break;

	case 6:
		m_start = D3DXVECTOR3(max.x, max.y, min.z);
		m_end = D3DXVECTOR3(max.x, max.y, max.z);
		break;

	case 7:
		m_start = D3DXVECTOR3(min.x, max.y, max.z);
		m_end = D3DXVECTOR3(max.x, max.y, max.z);
		break;

		//-----------------------------------
		// �c��
		//-----------------------------------
	case 8:
		m_start = D3DXVECTOR3(min.x, min.y, min.z);
		m_end = D3DXVECTOR3(min.x, max.y, min.z);
		break;

	case 9:
		m_start = D3DXVECTOR3(min.x, min.y, max.z);
		m_end = D3DXVECTOR3(min.x, max.y, max.z);
		break;

	case 10:
		m_start = D3DXVECTOR3(max.x, min.y, min.z);
		m_end = D3DXVECTOR3(max.x, max.y, min.z);
		break;

	case 11:
		m_start = D3DXVECTOR3(max.x, min.y, max.z);
		m_end = D3DXVECTOR3(max.x, max.y, max.z);
		break;
	}
}