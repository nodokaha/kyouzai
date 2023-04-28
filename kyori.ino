#include <Servo.h>

int val = 0, theta = 0; // 受信するシリアルデータのために準備
float dis = 0; // 距離の計算値
float l_t = 0.7; // センサのフィルタ定数
const int SERVO_PIN = 9; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD = 50; // centimeters

Servo servo;

void setup() {
	Serial.begin(9600); // シリアルポートを開き，データレートを9600 bpsにセットする
	servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(0);
}
void loop() {
	servo.write(0);
	Serial.print('q');
	delay(1000);
	for(int data=Serial.read(); data == 's'; Serial.flush(),data=Serial.read()){
		theta=0;
		while(theta+20<=180){
			servo.write(theta);
			theta+=20;
			delay(1000);
			val = analogRead(A0);
			if(val < 82){
				// AD値が小さい場合に近似式で距離が無限になってしまうので、AD値が82未満は82とする
				val = 82; }
			dis = l_t * dis + (1 - l_t) * 25391 * pow(val, -1.136); // 距離算出。指数移動平均で平滑化。
			Serial.print("AD: ");
			Serial.print(val);
			Serial.print("/ distance: ");
			Serial.print(dis);
			Serial.print(" cm / ");
			Serial.print("degree: ");
			Serial.print(theta);
			Serial.print("/ order: ");
			Serial.print(data);
			delay(1000);//1000msec待機(1秒待機)
			if(theta==180)
				while(Serial.read() == 's');
		}
	}
}
