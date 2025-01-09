const mysql = require('mysql2');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: 'lohielisabeth',
  database: 'bank_automat'
});

module.exports = connection;