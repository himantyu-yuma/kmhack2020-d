#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

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
const char *mqttTopic_Signal = "test/signal";
const char *mqttTopic_Query = "test/query";

//Connect WiFi Client and MQTT(PubSub) Client
WiFiClient espClient;
PubSubClient g_mqtt_client(espClient);

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
			"{temperture: %.1f, humid: %d, heart_rate: %d, co2: %d}", temperture, humid, heart_rate, co2);

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
		MQTT_publish_query(10.1f, 20, 30, 17);
		count = 0;
	}

	delay(200);
}
