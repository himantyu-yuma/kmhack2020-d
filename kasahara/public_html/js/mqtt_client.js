var mqtt;
const reconnectTimeout  = 2000;
const mqttTimeout       = 3;

// shiftr.ioの設定
const SHIFTR_HOST       = "broker.shiftr.io"; // shiftr.ioの接続先 (変更しない)
const SHIFTR_PORT       = 443; // Websocketのポート (TLSで接続する. 変更しない)
const SHIFTR_KEY        = "819bcd7e"; // Key (Username)
const SHIFTR_SECRET     = "460f695cf094a8a5"; // Secret (Password)
const TOPIC_NAME        = "test/query";
// clientの設定
const CLIENT_NAME       = "webapp";

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
    document.getElementById("status").innerHTML = STATUS_SERVER_DISCONNECTED;
    document.getElementById("messages").innerHTML = MSG_SERVER_CONNECTION_LOST;
    connected_flag = 0;
}

// 接続に失敗した場合の処理
function onFailure(message) {
    console.error(STATUS_SERVER_FAILED);
    console.error(message);
    document.getElementById("messages").innerHTML = MSG_SERVER_CONNECTION_RETRY;
    setTimeout(MQTTconnect, reconnectTimeout);
}


// メッセージを受信した場合の処理
function onMessageArrived(r_message) {

    console.log(r_message.payloadString);

}



// 接続完了した場合の処理
function onConnected(recon, url) {
    console.log(" in onConnected " + reconn);
}

// 接続中の処理
function onConnect() {
    console.log(STATUS_SERVER_CONNECTED);
    document.getElementById("messages").innerHTML = MSG_SERVER_CONNECTION_READY.replace("HOST", SHIFTR_HOST).replace("PORT", SHIFTR_PORT);
    connected_flag = 1;
    document.getElementById("status").innerHTML = STATUS_SERVER_CONNECTED;
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





