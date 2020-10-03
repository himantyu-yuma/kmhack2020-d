var mqtt;
const reconnectTimeout = 2000;
const mqttTimeout = 3;

// shiftr.ioの設定
const SHIFTR_HOST = "broker.shiftr.io"; // shiftr.ioの接続先 (変更しない)
const SHIFTR_PORT = 443; // Websocketのポート (TLSで接続する. 変更しない)
const SHIFTR_KEY = "819bcd7e"; // Key (Username)
const SHIFTR_SECRET = "460f695cf094a8a5"; // Secret (Password)
const TOPIC_NAME = "test/query";
// clientの設定
const CLIENT_NAME = "webapp";

// メッセージ
const MSG_SERVER_CONNECTION_LOST = "MQTT サーバーへのコネクションが切れました";
const MSG_SERVER_CONNECTION_RETRY = "MQTT サーバーへの接続をリトライしています";
const MSG_SERVER_CONNECTION_READY = "MQTT サーバーへの接続に成功しました (HOST:PORT)";

// ステータス
const STATUS_SERVER_DISCONNECTED = "Disconnected";
const STATUS_SERVER_FAILED = "Failed to connect";
const STATUS_SERVER_CONNECTED = "Connected";
const STATUS_SERVER_CONNECTING = "Connecting to HOST:PORT";

// ajax用
var xhr = new XMLHttpRequest();


// Hey button受け取り用変数
// 接続が切断された場合の処理
function onConnectionLost() {
    console.error(STATUS_SERVER_DISCONNECTED);
    connected_flag = 0;
}

// 接続に失敗した場合の処理
function onFailure(message) {
    console.error(STATUS_SERVER_FAILED);
    console.error(message);
    setTimeout(MQTTconnect, reconnectTimeout);
}


// mqttからメッセージを受信した場合の処理
function onMessageArrived(r_message) {

    // console.log('received');
    console.log(r_message.payloadString);
    // 受け取ったデータ
    const data = JSON.parse(r_message.payloadString);
    const temperture = data.temperture;
    const humid = data.humid;
    const heart_rate = data.heart_rate;

    // 各データを表示するDOM要素
    const temperture_element = document.getElementById('temperture');
    const humid_element = document.getElementById('humid');
    const heart_rate_element = document.getElementById('heart-rate');

    temperture_element.textContent = temperture;
    humid_element.textContent = humid;
    heart_rate_element.textContent = heart_rate;
}



// 接続完了した場合の処理
function onConnected(recon, url) {
    console.log(" in onConnected " + reconn);
}

// 接続中の処理
function onConnect() {
    console.log(STATUS_SERVER_CONNECTED);
    connected_flag = 1;
    console.log("on Connect " + connected_flag);
    mqtt.subscribe(TOPIC_NAME);
}

// 切断の処理
function disconnect() {
    if (connected_flag == 1)
        mqtt.disconnect();
}

// 接続開始の処理
function MQTTconnect() {
    console.log((STATUS_SERVER_CONNECTING).replace("HOST", SHIFTR_HOST).replace("PORT", SHIFTR_PORT));
    mqtt = new Paho.MQTT.Client(SHIFTR_HOST, SHIFTR_PORT, CLIENT_NAME);
    const options = {
        useSSL: true,
        timeout: mqttTimeout,
        userName: SHIFTR_KEY,
        password: SHIFTR_SECRET,
        onSuccess: onConnect,
        onFailure: onFailure,
    };
    mqtt.onConnectionLost = onConnectionLost;
    mqtt.onMessageArrived = onMessageArrived;
    mqtt.onConnected = onConnected;
    mqtt.connect(options); //connect
    return false
}

// ブローカーにメッセージを送信
const publish = (topic, msg) => {
    message = new Paho.MQTT.Message(msg);
    message.destinationName = topic;
    mqtt.send(message);
}

// 座り続けている時間に表示させるやる
const TimeDisplay = () => {
    const sit_time_element = document.getElementById('sit-time');

    let time = 0;
    let hour = 0;
    let minute = 0;
    let sec = 0;

    setInterval(() => {
        // 1秒ずつ増やす
        time++;
        hour = Math.floor(time / 60 / 60);
        minute = Math.floor(time / 60 - hour * 60);
        sec = time - hour * 60 * 60 - minute * 60;
        sit_time_element.textContent = `${( '00' + hour).slice( -2 )}:${( '00' + minute).slice( -2 )}:${( '00' + sec).slice( -2 )}`;
    }, 1000);
}
TimeDisplay();

const ControllAirCon = () => {
    const set_temperture_element = document.getElementById('set-temperture');
    let set_temperture = parseInt(set_temperture_element.textContent);

    const switchBtn = document.querySelector('.switch-icon');
    const upBtn = document.querySelector('.up-icon');
    const downBtn = document.querySelector('.down-icon');

    switchBtn.addEventListener('click', () => {
        publish('test/signal', '0');
    });

    upBtn.addEventListener('click', () => {
        set_temperture ++;
        set_temperture_element.textContent = set_temperture;
    });
    
    downBtn.addEventListener('click', () => {
        set_temperture --;
        set_temperture_element.textContent = set_temperture;
    });

}
ControllAirCon();