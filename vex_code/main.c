#pragma config(Motor,  port2,           rightMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           clawServo,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           dispensingServo, tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main ()
{
	/*motors accessed with [] and range in speeds values from bits (-127 - 127)*/
	/*servos based on position in values of bits (-127 - 127) */
	// Current servo has 180 degrees of motion

	//default pos when starting
	int pos = -127;
	while(true)
	{

		// movement diff ft. surya | left joystick | Ch4 horizontal | Ch3 vertical | , right joystick | Ch1 horizontal | Ch2 vertical
		motor[leftMotor] = vexRT[Ch4] + vexRT[Ch3]; // maps values, might need to divide by 2 if too fast or slow
		motor[rightMotor] = vexRT[Ch3] - vexRT[Ch4];

		// Arm Movement
		motor[armMotor] = vexRT[Ch2]; // should work

		//claw

		/*if((up+down) == 2)
		{
			setServo(clawServo,pos);
		}*/
		if(vexRT[Btn6U] == 1)
		{
			//pos = pos + 2;
			//if(pos > 127)
				//pos = 127;
			setServo(clawServo, 0);
		}
		if(vexRT[Btn6D] == 1)
		{
			motor[clawServo] = 50;
			//pos = pos - 2;
			//if(pos < -127)
				//pos = -127;
			//setServo(clawServo,pos);
		}

		//Wheel Dispensing
		int out = vexRT[Btn5U]; // do not spam
		if(out != 0)
		{
			setServo(dispensingServo, 63);
			wait1Msec(2000);
			setServo(dispensingServo, -127);
		}
	}
}
