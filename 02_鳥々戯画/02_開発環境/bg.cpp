//===================================
//
// 弾の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "bg.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"

//===========================
// コンストラクタ
//===========================
CBg::CBg() : CObject(0)
{
	m_pObject2D = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntClear = 0;
	m_fTexLeft = 0.0f;
	m_fTexRight = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}

//===========================
// デストラクタ
//===========================
CBg::~CBg()
{

}

//===========================
// 初期化
//===========================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_nCntAnim = 0;
	m_fTexLeft = 0.0f;

	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Init(m_pos);
		m_fWidth = SCREEN_WIDTH;
		m_fHeight = SCREEN_HEIGHT;

		//テクスチャ座標の設定
		m_pObject2D->SetTexCIE(0.0f, 1.0f);

		switch (m_type)
		{
		case BGTYPE_GAME:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_GAME);	//テクスチャの設定
			m_fTexRight = 0.5f;
			m_pObject2D->SetTexCIE(m_fTexLeft, m_fTexRight);
			break;

		case BGTYPE_GAME_TIME:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_GAME_TIME);
			m_fWidth = 200.0f;
			m_fHeight = 100.0f;
			break;

		case BGTYPE_GAME_SCORE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_GAME_SCORE);
			m_fWidth = 200.0f;
			m_fHeight = 100.0f;
			break;

		case BGTYPE_TITLE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE);
			m_fTexRight = 0.5f;
			m_pObject2D->SetTexCIE(m_fTexLeft, m_fTexRight);
			break;

		case BGTYPE_TITLE_LOGO:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_LOGO);
			m_fWidth = 700.0f;
			m_fHeight = 300.0f;
			break;

		case BGTYPE_TITLE_ENTER:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_PRESSENTER);
			m_fWidth = 600.0f;
			m_fHeight = 100.0f;
			break;

		case BGTYPE_RESULT:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_RESULT);
			m_fTexRight = 0.5f;
			m_pObject2D->SetTexCIE(m_fTexLeft, m_fTexRight);
			break;

		case BGTYPE_RESULTTEXT:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_RESULTTEXT);
			break;

		case BGTYPE_SELECTMODE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_NONE);
			m_fWidth = 600.0f;
			m_fHeight = 500.0f;
			m_pObject2D->SetColor(D3DXCOLOR(0.8f, 0.4f, 0.4f, 0.5f));
			break;

		case BGTYPE_TUTORIAL1:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TUTORIAL1);
			break;

		case BGTYPE_TUTORIAL2:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TUTORIAL2);
			break;

		default:
			break;
		}

		m_pObject2D->SetSize(m_fWidth, m_fHeight);
	}

	return S_OK;
}

//===========================
// 終了
//===========================
void CBg::Uninit()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}
}

//===========================
// 更新
//===========================
void CBg::Update()
{
	if (m_pObject2D != nullptr)
	{
		//カウントの加算
		m_nCntAnim++;
		m_nCntAnim %= 10;

		m_nCntClear++;
		m_nCntClear %= 80;

		//-----------------
		// 背景の移動
		//-----------------
		if (m_type == BGTYPE_GAME || m_type == BGTYPE_TITLE || m_type == BGTYPE_RESULT
			&& m_nCntAnim == 0)
		{//ゲーム画面 or タイトル画面 or リザルト画面なら
			//テクスチャ座標の加算
			m_fTexLeft += 0.0005f;
			m_fTexRight += 0.0005f;

			//テクスチャ座標の設定
			m_pObject2D->SetTexCIE(m_fTexLeft, m_fTexRight);
		}

		//-----------------------------
		// プレスエンターを点滅させる
		//-----------------------------
		if (m_type == BGTYPE_TITLE_ENTER)
		{
			if (m_nCntClear < 40)
			{
				m_pObject2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_pObject2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
			}
		}
	}
}

//===========================
// 描画
//===========================
void CBg::Draw()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Draw();
	}
}

//===========================
// 生成
//===========================
CBg *CBg::Create(D3DXVECTOR3 pos, BGTYPE type)
{
	CBg *pBG = nullptr;

	//----------------------------------
	// 背景の生成と初期化
	//----------------------------------
	pBG = new CBg;	//生成
	pBG->m_pObject2D = new CObject2D(0);

	if (pBG != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pBG->m_type = type;

		//初期化
		pBG->Init(pos);
		pBG->SetObjType(OBJTYPE_BG);
	}

	return pBG;
}

//===========================
// 位置の取得
//===========================
D3DXVECTOR3 CBg::GetPosition()
{
	return m_pos;
}

//===========================
// 幅の取得
//===========================
float CBg::GetWidth()
{
	return m_fWidth;
}

//===========================
// 高さの取得
//===========================
float CBg::GetHeight()
{
	return m_fHeight;
}