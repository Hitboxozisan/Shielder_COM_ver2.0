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
	ShieldCreater(const ShieldCreater&);	//�R�s�[�R���X�g���N�^
	void operator=(const ShieldCreater&);	//�R�s�[������Z�q


};

