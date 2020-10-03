var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://819bcd7e:460f695cf094a8a5@broker.shiftr.io');
const http = require('http');
const express = require('express')
const app = express()
// body-parserのおまじない
// 参照:https://expressjs.com/ja/4x/api.html#req.body
const bodyParser = require('body-parser');

client.on('connect', function () {
    console.log('publisher.connected.');
});


app.use(bodyParser.urlencoded({ extended: true }))

app.listen(3000)
app.get('/v1', function (req, res) {
    // GETリクエスト処理
    res.send('Receive Get request');
    console.log(req.query.trigger);

    // トリガーを横流し
    const trigger = req.query.trigger;
    client.publish('pose/trigger', trigger);

    // client.publish('test/query', message);
    // const message = Date.now().toString();
    // console.log('publisher.publish:', message);
})