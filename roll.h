#pragma once

class Roll
{

public:

	//������
	void Initialize();

	//����
	void Updare();

	//�`��
	void Draw();

	//�V���O���g��
	static Roll* GetInstance()
	{
		static Roll roll;
		return &roll;
	}

private:

	//���s
	void Act();

	//���l����
	void Number();

	//���ʕۑ�
	size_t ans[10];

	//�����_����
	size_t size = 5;
	size_t maxsize = 10;
	size_t forcas = 0;

};