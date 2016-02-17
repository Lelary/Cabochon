#ifndef _CONTROLS_H
#define _CONTROLS_H

/*
	2016. 1. 5.
	��ü�� �̱���
	2016. 1. 9.
	�̱������� ����� ��ſ� �̱��� ��ü�� �� ��ü���� ����
	2016. 2. 2.
	Base Ŭ������ Control ��ü �ۼ�. ���� Ŭ�������� Control�� ��ӹ���.
*/
namespace controls
{
	class Control;

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
	struct MarbleColorBitField;
	union MarbleColorOn;
	class MarbleBoard;
	class MarbleGenerator;

	/*
	2016. 1. 10
	controls ? components ?
	Grid - Quadrant - Object
	��ü�� �ʿ�ġ �ʰ�(�޸𸮸� �Ҵ��ϰ� ����� ������ ����)
	������� ���� ���� �� �ִ�.
	*/
	//Marble�� ��ġ�κ��� ����ġ�� ���ĭ���� �˷���
	class Grid;


	// ���߿� ����
	// class LevelControl;
}
#endif