#include <WiFi.h>
#include <PubSubClient.h>

// 接続先のSSIDとパスワード
const char ssid[] = "SSID";
const char password[] = "PASS";

// 自分で設定した CloudMQTT.com サイトの Instance info から取得
const char *mqttServer = "broker.shiftr.io";
const char *mqttDeviceId = "ESP32-KY";
const char *mqttUser = "819bcd7e";
const char *mqttPassword = "460f695cf094a8a5";
const int mqttPort = 1883;

// Subscribe する MQTT Topic 名
const char *mqttTopic_Signal = "esp/controll";
// PublishするMQTT Topic名
const char *mqttTopic_Query = "esp/sensor";

//Connect WiFi Client and MQTT(PubSub) Client
WiFiClient espClient;
PubSubClient g_mqtt_client(espClient);

// MQTTからのデータを受信する
void MQTT_callback(char *topic, byte *payload, unsigned int length)
{
	Serial.print("received MQTT topic:");
	Serial.println(topic);
	Serial.print("length = ");
	Serial.println(length);
	Serial.print("Payload : ");
	String tempMessage;
	for (int i = 0; i < length; i++)
	{
		tempMessage += (char)payload[i];
	}
	Serial.println(tempMessage);
	Serial.println();

	int switchNum = tempMessage.toInt();

	// 受信したメッセージによって処理
	// 0，1でオンオフの処理をして，それ以外は温度を直接渡す
	switch (switchNum)
	{
	case 0:
		// エアコンをオフにする
		Serial.println("エアコン オフ");
		break;
	case 1:
		// エアコンをオンにする
		break;
	case 25:
		// エアコンの温度設定
		break;
	default:
		break;
	}
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
void MQTT_publish_query(int temperture, int humid, int heart_rate, int co2)
{
	char payload[64];
	sprintf(payload,
			"{\"temperture\": %d, \"humid\": %d, \"heart_rate\": %d, \"co2\": %d}", temperture, humid, heart_rate, co2);

	// MQTT brokerへpublish
	g_mqtt_client.publish(mqttTopic_Query, payload);
}

void setup()
{
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
	if (!g_mqtt_client.connected())
	{
		MQTT_reconnect();
	}
	g_mqtt_client.loop();

	count++;
	if (count >= 10)
	{
		int temp_demo = 20 + (int)(rand() * (30 - 20 + 1.0) / (1.0 + RAND_MAX));
		int humid_demo = 40 + (int)(rand() * (80 - 40 + 1.0) / (1.0 + RAND_MAX));
		int beat_demo = 60 + (int)(rand() * (100 - 60 + 1.0) / (1.0 + RAND_MAX));
		int co2_demo = 17 + (int)(rand() * (19 - 17 + 1.0) / (1.0 + RAND_MAX));

		MQTT_publish_query(temp_demo, humid_demo, beat_demo, co2_demo);
		count = 0;
	}

	delay(200);
}
