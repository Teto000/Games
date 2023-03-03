//=====================================
//
// HPフレームヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _HPFREAM_H_
#define _HPFREAM_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// HPフレームクラス
//--------------------------
class CHpFream : public CObject2D
{
public:
	CHpFream();				//コンストラクタ
	~CHpFream() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//セッター
	void SetMove(D3DXVECTOR3 move);

	//------------------
	// 静的メンバ関数
	//------------------
	static CHpFream *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
};

#endif