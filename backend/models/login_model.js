const db = require('../database');

const login={
  checkPassword: function(cardNumber, callback) {
      return db.query('SELECT pin FROM card WHERE cardNumber = ?',[cardNumber], callback); 
    }
};
          
module.exports = login;