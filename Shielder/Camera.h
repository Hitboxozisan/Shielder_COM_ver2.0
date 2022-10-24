#pragma once

class Character;

class Camera final
{
public:
	Camera();
	~Camera();

	void Initialize();
	void SetPosition(Character** character);
	void Update(Character** character);
	void Finalize();

	//�Q�[���J�n���ɃJ����������̈ʒu�܂ňړ�������


	//���݈ʒu���擾
	const VECTOR& GetCameraPosition() const { return position; }

private:

	static const VECTOR CAMERA_INITIAL_POSITION;	//�J���������ʒu
	static const float  CAMERA_LOOK_AT_HEIGHT;
	static const float  CAMERA_LOOK_AT_DISTANCE;
	static const float  CAMERA_FOV;					//����p
	static const float  CAMERA_NEAR;				//�J�����̕`��͈́i��O�j
	static const float  CAMERA_FAR;					//�J�����̕`��͈́i���j
	static const float  CAMERA_OUTSIDE_RANGE;		//�J����������鋗��

	VECTOR position;
	VECTOR targetPosition;
	VECTOR twoPositionDistance;		//�v���C���[�ƃG�l�~�[�̋���

	//�J�����̌���
	float hAngle;
	float vAngle;

	float sinParam;
	float cosParam;
};

