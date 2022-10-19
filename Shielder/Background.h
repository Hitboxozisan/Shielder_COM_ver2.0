#pragma once

class Background final
{
public:
	Background();
	~Background();

	void Initialize();
	void Finalize();
	void Activate();
	void Deactivate();
	void Update();
	void Draw();

private:
	static const float SIZE;
	static const VECTOR INITIAL_POSITION;

	int img;
	VECTOR position;
	int modelHandle;
};

