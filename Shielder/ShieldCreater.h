#pragma once

class Shield;

class ShieldCreater final
{
public:
	ShieldCreater();
	~ShieldCreater();

	Shield* Create();

private:
	//ShieldCreater();
	ShieldCreater(const ShieldCreater&);	//コピーコンストラクタ
	void operator=(const ShieldCreater&);	//コピー代入演算子


};

