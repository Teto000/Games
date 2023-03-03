//=====================================
//
// 経験値ヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _EXP_H_
#define _EXP_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// 経験値クラス
//--------------------------
class CExp : public CObject2D
{
public:
	CExp();				//コンストラクタ
	~CExp() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// 静的メンバ関数
	//------------------
	static CExp *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float m_fLength);

private:
	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//回転
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
};

#endif // !_EXP_H_