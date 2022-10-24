#pragma once
class BillboardBase
{
public:
	BillboardBase();
	virtual ~BillboardBase();

    void Initialize(const int* inGraphicPointer);
    void Finalize();
    virtual void Activate(const VECTOR& creatorPosition, float creatorSize) = 0;
    void Deactivate();
    void Update();
    virtual void Draw(const VECTOR& inPosition);

    bool GetExist() const;    // ���݂��Ă��邩�ǂ�����Ԃ�

protected:
    static const float DEFAULT_GRAPHIC_CENTER; // �f�t�H���g�̉摜�̒��S(0.0f�`1.0f�A�ʏ��0.5f)

    VECTOR     position;       // ���݂̍��W
    const int* graphicPointer; // �摜�̃|�C���^
    float      size;           // ���݂̑傫��(�摜)
    bool       exist;          // ���݂��Ă��邩
    int        existFrame; // ���݂ł���c��t���[��

private:
    // �g�p���֎~����
    BillboardBase(const BillboardBase&);  // �R�s�[�R���X�g���N�^
    void operator=(const BillboardBase&); // �R�s�[������Z�q

    virtual void UpdateEach() = 0; // �q�N���X���ꂼ��̍X�V����

};

