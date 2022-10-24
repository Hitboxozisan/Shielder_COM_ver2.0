#include "Pch.h"

#include "BillboardBase.h"

BillboardBase::BillboardBase()
	:position()
	,graphicPointer()
	,size()
	,exist(false)
	,existFrame(0)
{
}

BillboardBase::~BillboardBase()
{
}

void BillboardBase::Initialize(const int* inGraphicPointer)
{
	graphicPointer = inGraphicPointer;
}

void BillboardBase::Finalize()
{
}

void BillboardBase::Deactivate()
{
	exist = false;
}

void BillboardBase::Update()
{
	if (exist == false)
	{
		return;
	}

	--existFrame;
	//���݂ł���t���[�������o�߂�����
	if (existFrame < 0)
	{
		Deactivate();
		return;
	}

	UpdateEach();		//�q�N���X�ʂ̍X�V����
}

void BillboardBase::Draw(const VECTOR& inPosition)
{
}

bool BillboardBase::GetExist() const
{
	return exist;
}
