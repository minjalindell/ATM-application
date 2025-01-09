const db = require('../database');

const transactions = {
  getAll: function(callback) {
    return db.query('select * from transactions', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from transactions where AccountNumber=? order by date_time desc', [id], callback);
    console.log("Moi");
  },
  add: function(transactions, callback) {
    return db.query(
      'insert into transactions (id_receiver, type, transaction, amount, date_time, AccountNumber) values(?,?,?,?,?,?)',
      [transactions.id_receiver, transactions.type, transactions.transaction, transactions.amount, transactions.date_time, transactions.AccountNumber],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from transactions where idTransaction=?', [id], callback);
  },
  update: function(id, transactions, callback) {
    return db.query(
      'update transactions set id_receiver=?,type=?, transaction=?, amount=?, date_time=?, AccountNumber=? where idTransaction=?',
      [transactions.id_receiver, transactions.type, transactions.transaction, transactions.amount, transactions.date_time, transactions.AccountNumber, id],
      callback
    );
  }
};
module.exports = transactions;