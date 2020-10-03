#include <WiFi.h>
#include <PubSubClient.h>
#include <string>


//Heart rate

// Function: This program can be used to measure heart rate, the lowest pulse in the program be set to 30.
//         Use an external interrupt to measure it.
// Hardware: Grove - Ear-clip Heart Rate Sensor, Grove - Base Shield, Grove - LED
// Arduino IDE: Arduino-1.0
// Author: FrankieChu       
// Date: Jan 22, 2013
// Version: v1.0
// by www.seeedstudio.com
#define LED 26//indicator, Grove - LED is connected with D4 of Arduino
boolean led_state = LOW;//state of LED, each time an external interrupt 
                                //will change the state of LED
unsigned char counter;
unsigned long temp[21];
unsigned long sub;
bool data_effect=true;
unsigned int heart_rate;//the measurement result of heart rate

const int max_heartpluse_duty = 2000;//you can change it follow your system's request.
                        //2000 meams 2 seconds. System return error 
                        //if the duty overtrip 2 second.

//int tones[5] = {196, 262, 330, 466, 622};    //音階


// 接続先のSSIDとパスワード
const char ssid[] = "FG4023B-0C58-bg";
const char password[] = "8207145431";

// 自分で設定した CloudMQTT.com サイトの Instance info から取得
const char *mqttServer = "broker.shiftr.io";
const char *mqttDeviceId = "ESP32-KY";
const char *mqttUser = "819bcd7e";
const char *mqttPassword = "460f695cf094a8a5";
const int mqttPort = 1883;

// Subscribe する MQTT Topic 名
const char *mqttTopic_Signal = "test/signal";
const char *mqttTopic_Query = "test/query";

//Connect WiFi Client and MQTT(PubSub) Client
WiFiClient espClient;
PubSubClient g_mqtt_client(espClient);

void setup()
{
    //heart rate
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    Serial.println("Please ready your chest belt.");
    delay(5000);
    arrayInit();
    Serial.println("Heart rate test begin.");
    attachInterrupt(14, interrupt, RISING);//set interrupt 0,digital port 2
    attachInterrupt(0, interrupt, RISING);//set interrupt 0,"FLASH"ボタン


  //MQTT
  Serial.begin(9600);

  // Connect WiFi
  WiFi.begin(ssid, password);

  int cnt = 0;
  int is_success = true;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("WiFi connecting to ");
    Serial.println(ssid);
    cnt++;
    if (cnt > 30)
    {
      is_success = false;
      break;
    }
  }
  if (is_success)
  {
    // WiFi アクセスポイントから付与されたIPアドレスを表示
    Serial.print("Connected to the WiFi network. IP address: ");
    Serial.println(WiFi.localIP());
    // MQTT Serverの設定
    g_mqtt_client.setServer(mqttServer, mqttPort);
    // topicをsubscribeしたときのコールバック関数を登録
    g_mqtt_client.setCallback(MQTT_callback);
    // MQTT brokerとの接続
    MQTT_reconnect();
  }
  else
  {
    Serial.println("[Errol] Cannot connected to the WiFi network");
  }
}

int count = 0;
void loop()
{
    digitalWrite(LED, led_state);//Update the state of the indicator

    //MQTT
    if (!g_mqtt_client.connected())
  {
    MQTT_reconnect();
  }
  g_mqtt_client.loop();

  count++;
  if (count >= 10)
  {
    MQTT_publish_query(10.1f, 20, heart_rate, 17);
    count = 0;
  }

  delay(200);
}
/*Function: calculate the heart rate*/
void sum()
{
 if(data_effect)
    {
      heart_rate=1200000/(temp[20]-temp[0]);//60*20*1000/20_total_time 
      Serial.println();
      Serial.print("Heart_rate_is:\t");
      Serial.println(heart_rate);
      Serial.println();
    }
   data_effect=1;//sign bit
}
/*Function: Interrupt service routine.Get the sigal from the external interrupt*/
void interrupt()
{
    temp[counter]=millis();
    //Serial.println(counter,DEC);
    //Serial.println(temp[counter]);
    Serial.print("loading...[");
    Serial.print(counter,DEC);
    Serial.println("/20]");
    switch(counter)
    {
        case 0:
            sub=temp[counter]-temp[20];
            //Serial.println(sub);
            break;
        default:
            sub=temp[counter]-temp[counter-1];
            //Serial.println(sub);
            break;
    }
    if(sub>max_heartpluse_duty)//set 2 seconds as max heart pluse duty
    {
        data_effect=0;//sign bit
        counter=0;
        Serial.println("Heart rate measure error,test will restart!" );
        arrayInit();
    }
    if (counter==20&&data_effect)
    {
        counter=0;
        sum();
    }
    else if(counter!=20&&data_effect)
    counter++;
    else 
    {
        counter=0;
        data_effect=1;
    }
}
/*Function: Initialization for the array(temp)*/
void arrayInit()
{
    for(unsigned char i=0;i < 20;i ++)
    {
        temp[i]=0;
    }
    temp[20]=millis();
}

    



void MQTT_callback(char *topic, byte *payload, unsigned int length)
{
	Serial.print("received MQTT topic:");
	Serial.println(topic);
	Serial.print("length = ");
	Serial.println(length);
	Serial.print("Payload : ");
	Serial.println((char *)payload);

	Serial.println();
}

// MQTT Client が接続できなかったら接続できるまで再接続を試みるための MQTT_reconnect 関数
void MQTT_reconnect()
{
	// Loop until we're reconnected
	while (!g_mqtt_client.connected())
	{
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (g_mqtt_client.connect(mqttDeviceId, mqttUser, mqttPassword))
		{
			Serial.println("connected");
			g_mqtt_client.subscribe(mqttTopic_Signal);
		}
		else
		{
			Serial.print("failed, rc=");
			Serial.print(g_mqtt_client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5sec before retrying
			delay(1000);
		}
	}
}

// MQTTサーバーにデータを送信する関数
// 温度，湿度，心拍数，CO2濃度の順です
// 124行目で試しに呼び出しています
void MQTT_publish_query(float temperture, int humid, int heart_rate, int co2)
{
  char payload[64];
  sprintf(payload,
      "{\"temperture\": %.1f, \"humid\": %d, \"heart_rate\": %d, \"co2\": %d}", temperture, humid, heart_rate, co2);
  // MQTT brokerへpublish
  g_mqtt_client.publish(mqttTopic_Query, payload);
}
