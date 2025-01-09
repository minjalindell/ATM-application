const db = require('../database');
const bcrypt = require('bcryptjs');

const card = {
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  getById: function(card, callback) {
    return db.query('select * from card where cardNumber=?', [card.cardNumber], callback);
  },
  add: function(card, callback) {
    bcrypt.hash(card.pin, 10, function(err, hashedPassword){
      return db.query(
        'insert into card (cardNumber,pin,type,userId) values(?,?,?,?)',
        [card.cardNumber, hashedPassword, card.type, card.userId],
        callback
      )
    })
  },
  delete: function(id, callback) {
    return db.query('delete from card where cardNumber=?', [id], callback);
  },
  update: function(id, card, callback) {
    bcrypt.hash(card.pin, 10, function(err, hashedPassword){
      return db.query(
        'update card set pin=?,type=?, userId=? where cardNumber=?',
        [hashedPassword, card.type, card.userId, id],
        callback
      );
    });

  }
};
module.exports = card;