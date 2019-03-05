/************************************************************
* ��֯���ƣ�
* �ļ�����: K:\��Ƭ�����\���Ӵ���������\HARDWARE\DEVICES\MOTOR\STEP_MOTOR\STEP_MOTOR.C
* ����:  �ܳ���
* �汾:  1.0
* ����:  2017/07/11
* ����: �����������������
* ��ʷ�޸ļ�¼:
* <����> <ʱ��> <�汾 > <����>
*
***********************************************************/

#include "STEP_MOTOR.H"
#include "../../../COMMON_HARDWARE/fixedPulser.h"
#define STEP_MOTOR_NUM 2 
typedef struct
{
	u16 angle;//��ת�Ƕ�
	u8 state;//���״̬��ͣת����ס����ͣת������̬������ת
	u16 round;//��תȦ��
	u8 speed;//��ת�ٶ�
	float DIV;//������������Ƕ�ֵ ����1.8��
	u8 driverDiv;//�����������������ѡ�ĽǶ�ϸ��ֵ 2��4��8��16
	u16 maxPeriod; 	//����������ܳ��ܵ����Ƶ��
	u8 diversion;//���ת��


}StepMotor;
static  StepMotor g_stepMotor[STEP_MOTOR_NUM];
//enum {
//	 RUNNING,FREE,LOCKED
//}g_stepMotor[0]=LOCKED;

//************************************
// Method:    setStepMotorWithAngle
// FullName:  setStepMotorWithAngle
// Access:    public 
// Returns:   bit
// Qualifier: ���ò����������ת�Ƕ�
// Parameter: u8 motor����һ�����
// Parameter: u16 angle ��ת�Ƕȣ�������360�㣬���Գ���360��
// Parameter: u8 speed����ת�ٶȣ�1-100
//************************************
bit setStepMotorWithAngle(u8 motor, float angle, u8 speed)
{
	setPulse(motor, (u16)((1 + g_stepMotor[motor].maxPeriod / 99)*speed - (g_stepMotor[motor].maxPeriod / 99)), \
		(u16)((angle*g_stepMotor[STEP_MOTOR_1].driverDiv) / g_stepMotor[STEP_MOTOR_1].DIV));
	return 1;
}
//************************************
// Method:    setStepMotorWithRound
// FullName:  setStepMotorWithRound
// Access:    public 
// Returns:   bit
// Qualifier: ���ò����������תȦ��
// Parameter: u8 motor
// Parameter: u16 round
// Parameter: u8 speed
//************************************
bit setStepMotorWithRound(u8 motor, u16 round, u8 speed)
{
	setStepMotorWithAngle(motor, 360 * round, speed);
	return 1;
}
//************************************
// Method:    getStepMotorState
// FullName:  getStepMotorState
// Access:    public 
// Returns:   bit
// Qualifier: ��ȡ���������ǰ��״̬
// Parameter: u8 motor
//************************************
u8 getStepMotorState(u8 motor)
{
	return g_stepMotor[motor].state;
}
bit setStepMotorDiversion(u8 motor)
{

	return 1;
}
//************************************
// Method:    close_StepMotor
// FullName:  close_StepMotor
// Access:    public 
// Returns:   void
// Qualifier: �رղ������
// Parameter: u8 motor
//************************************
void close_StepMotor(u8 motor)
{
	closePulser(motor);
	g_stepMotor[motor].state = OFF;

}
//************************************
// Method:    open_StepMotor
// FullName:  open_StepMotor
// Access:    public 
// Returns:   void
// Qualifier: �򿪲������
// Parameter: u8 motor
//************************************
void open_StepMotor(u8 motor)
{
	openPulser(motor);
	g_stepMotor[motor].state = ON;
}
bit freeStepMotor(u8 motor)
{

	return 1;
}
bit lockStepMotor(u8 motor)
{

	return 1;
}
//************************************
// Method:    stepMotor_Init
// FullName:  stepMotor_Init
// Access:    public 
// Returns:   void
// Qualifier: ����
// div:�������������
// driverDiv��������ϸ��ֵ
// maxPeriod��������ܳ��ܵ��������Ƶ��
//************************************
void stepMotor_Init(u8 motor,float div,u8 driverDiv,u16 maxPeriod)
{
	g_stepMotor[motor].DIV = div;//1.8��Ĳ�����
	g_stepMotor[motor].driverDiv = driverDiv; //��������ʹ��8��ϸ��
	g_stepMotor[motor].maxPeriod = maxPeriod;
	PulserInit();
}