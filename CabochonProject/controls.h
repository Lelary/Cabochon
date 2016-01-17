#ifndef _CONTROLS_H
#define _CONTROLS_H

/*
	2016. 1. 5.
	��ü�� �̱���
	2016. 1. 9.
	�̱������� ����� ��ſ� �̱��� ��ü�� �� ��ü���� ����

*/
namespace controls
{
	//LifeCycleControl has Timer
	class LifeCycleControl;

	//Timer�� �������� ������ (1~2��)
	//����, �÷���Ÿ��
	class Timer;

	//MarbleControl has MarbleGenerator and a lot of Marble
	class MarbleControl;

	//SteeringGeerControl has a Marble or two Marbles
	/*
		2016. 1. 11
		���⼭ Marble�� ���� factory�� ������
	*/
	class SteeringWheelControl;

	//Generator�� ���� �ʿ� �ұ�?
	/*
		2016. 1. 13
		�ʿ����� ������? 
		�����ϴ� ���		
			1. �� ������
			2. SteeringWheelControl ����

		Generator ��� ���� Factory ��� ���� �����ؾ���
	*/
	class MarbleGenerator;
	


	// ���߿� ����
	// class LevelControl;
}
#endif