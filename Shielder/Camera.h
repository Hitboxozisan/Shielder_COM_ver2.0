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
	void StartCamera(Character** character);

	//�v���C���[�ɃY�[������
	void PlayerZoom(Character** character);

	//�Y�[���A�E�g
	void ZoomOut();
	//�J���������̈ʒu�ɖ߂�
	void RestoreCamera();

	//���݈ʒu���擾
	const VECTOR& GetCameraPosition() const { return position; }

private:

	static const VECTOR CAMERA_INITIAL_POSITION;	//�J���������ʒu
	static const float  CAMERA_CHANGE_SPEED;		//�J�����̈ʒu��ύX����X�s�[�h
	static const float  CAMERA_ZOOM_RANGE;			//�Y�[���������̃J�����Ƃ̋���
	static const float  CAMERA_LOOK_AT_HEIGHT;
	static const float  CAMERA_LOOK_AT_DISTANCE;
	static const float  CAMERA_FOV;					//����p
	static const float  CAMERA_NEAR;				//�J�����̕`��͈́i��O�j
	static const float  CAMERA_FAR;					//�J�����̕`��͈́i���j
	static const float  CAMERA_OUTSIDE_RANGE;		//�J����������鋗��

	VECTOR mainCameraPosition;		//�Q�[����ʂ̃J�����̍ŏI�ʒu
	VECTOR position;
	VECTOR velocity;				//���x�A�����x�A����
	VECTOR targetPosition;
	VECTOR twoPositionDistance;		//�v���C���[�ƃG�l�~�[�̋���
	float changeSpeed;				//�J�����̈ʒu��ύX����X�s�[�h
	float rangeOfCameraAndObject;	//�J�����ƃI�u�W�F�N�g�̋���


	//�J�����̌���
	float hAngle;
	float vAngle;

	float sinParam;
	float cosParam;
};

