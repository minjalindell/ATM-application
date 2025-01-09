var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');


var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
const jwt = require('jsonwebtoken');
require('dotenv').config();

const loginRouter = require('./routes/login.js');


app.use('/login', loginRouter);

app.use(authenticateToken);

var usersRouter = require('./routes/user');
app.use('/users', usersRouter);

var cardRouter = require('./routes/card');
app.use('/card', cardRouter);

const transactionsRouter = require('./routes/transactions');
app.use('/transactions', transactionsRouter);

const accountRouter = require('./routes/account');
app.use('/account', accountRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
  
      if (err) return res.sendStatus(403)
      //console.log("MY_TOKEN = "+MY_TOKEN);

      req.user = user
  
      next()
    })
}

module.exports = app;
