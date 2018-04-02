#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

int sensor=A0;
int speaker=7;
int gas_value,Gas_alert_val, Gas_shut_val, call_Count=0;
int Gas_Leak_Status;

int trigger=55;


void setup()
{

	pinMode(sensor,INPUT);
	pinMode(speaker,OUTPUT);
	
	mySerial.begin(9600);
	delay(500);
	Serial.begin(9600);
	delay(500);
}

void loop()
{
	CheckGas();
	CheckShutDown();
}

void CheckGas()
{

	Gas_alert_val=ScanGasLevel();

	if(Gas_alert_val>=trigger)
	{
		if(call_Count==0)
		{
		SetAlert1(); // Function to send call Alerts
		}
		SetAlert2(); // Function to send buzz Alerts
	}
}

int ScanGasLevel()
{
	gas_value=analogRead(sensor); // reads the sensor output
    Serial.println(gas_value);
	return gas_value; //
}

void SetAlert1()
 {

	//digitalWrite(speaker,HIGH);
	callAlert();
	call_Count=1;
	Gas_Leak_Status=1;
	
}
void SetAlert2()
{
	digitalWrite(speaker,HIGH);
	Serial.println("buzzH");
}

void CheckShutDown()
{
	if(Gas_Leak_Status==1)
	{
		Gas_shut_val=ScanGasLevel();
		if(Gas_shut_val<=trigger)
		{
			digitalWrite(speaker,LOW);
			Gas_Leak_Status=0;
			call_Count=0;
		}
		/*
		else
		{
			call_Count=0;
		}
		*/
	}
}

void callAlert()
{   	Serial.println("shadab");
	mySerial.println("ATD8375017991;");
	delay(20000);
	mySerial.println("ATH");
	delay(10000);
	Serial.println("rahul");
	mySerial.println("ATD8178063117;");
	delay(20000);
	mySerial.println("ATH");
	delay(10000);
// 	mySerial.println("ATD7042682108;");
// 	delay(20000);
// 	mySerial.println("ATH");
// 	delay(10000);
	
}
