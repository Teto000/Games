//===================================
//
// タイマー処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "timer.h"
#include "texture.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
int CTimer::m_nTime = 0;
int CTimer::m_aPosTexU[nMaxScore] = {};
int CTimer::nNum = 0;

//===========================
// コンストラクタ
//===========================
CTimer::CTimer() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntTime = 0;
	m_fWidth = 0.0f;
	m_fHeight = 0.0;
	m_mode = MODE_MAX;
}

//===========================
// デストラクタ
//===========================
CTimer::~CTimer()
{

}

//===========================
// 初期化
//===========================
HRESULT CTimer::Init(D3DXVECTOR3 pos)
{
	//構造体の初期化
	m_pos = pos;
	m_nTime = 0;

	if (m_mode == MODE_GAME)
	{
		m_fWidth = 30.0f;
		m_fHeight = 50.0f;
	}
	else if (m_mode == MODE_RESULT)
	{
		m_fWidth = 60.0f;
		m_fHeight = 100.0f;
	}

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CTimer::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CTimer::Update()
{
	CObject2D::Update();

	if (m_mode == MODE_GAME)
	{
		m_nCntTime++;
		m_nCntTime %= 60;

		if (m_nCntTime == 0)
		{
			m_nTime++;
		}
	}
	
	if (m_nTime % 3 == 0)
	{
		//桁ごとの値を求める
		m_aPosTexU[nNum] = (m_nTime / 3) % (1000 / (int)pow(10, nNum)) / (100 / (int)pow(10, nNum));
	}

	//テクスチャ座標の設定
	CObject2D::SetTexCIE(0.0f + m_aPosTexU[nNum] * 0.1f, 0.1f + m_aPosTexU[nNum] * 0.1f);

	//配列を進める
	if (nNum >= nMaxScore - 1)
	{
		nNum = 0;
	}
	else
	{
		nNum++;
	}
}
//===========================
// 描画
//===========================
void CTimer::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CTimer *CTimer::Create(MODE mode)
{
	CTimer *pTimer = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	for (int i = 0; i < nMaxScore; i++)
	{
		pTimer = new CTimer;	//生成

		if (pTimer != nullptr)
		{//NULLチェック
			//メンバ変数に代入
			pTimer->m_mode = mode;

			//初期化
			if (pTimer->m_mode == MODE_GAME)
			{
				pTimer->Init(D3DXVECTOR3(920.0f + (i * 30.0f), 90.0f, 0.0f));
			}
			else if (pTimer->m_mode == MODE_RESULT)
			{
				pTimer->Init(D3DXVECTOR3(550.0f + (i * 70.0f), 320.0f, 0.0f));
			}

			pTimer->SetObjType(OBJTYPE_SCORE);
		}
	}

	return pTimer;
}

//===========================
// 時間の設定
//===========================
void CTimer::SetTime(int nTime)
{
	m_nTime = nTime;
}

//===========================
// 時間の取得
//===========================
int CTimer::GetTime()
{
	return m_nTime;
}