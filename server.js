const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const usergroup = require('./build/Release/usergroup.node');

/*
var func = usergroup.usergroup_init('Пользователи');
console.log(func);
*/

app.use(express.static(__dirname + '/public'));
app.use(bodyParser.urlencoded( {extended: false} ));
app.use(bodyParser.json());

app.get('/', (req, res) => {
	res.sendFile("index.html");
	res.end();
});

app.post('/', (req,res) => {
	func = usergroup.usergroup_init(req.body.gName);
	res.send(func);
});

const listener = app.listen(20000, '127.0.0.1', () => console.log('Сервер запущен. Адрес: '+listener.address().address+':'+listener.address().port));