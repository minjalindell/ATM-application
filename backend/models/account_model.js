const db = require('../database');

const account = {
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from account where AccountNumber=?', [id], callback);
  },
  add: function(account, callback) {
    return db.query(
      'insert into account (AccountNumber,Balance,Type,creditLimit, UserID) values(?,?,?,?,?)',
      [account.AccountNumber, account.Balance, account.Type, account.creditLimit, account.UserID],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where AccountNumber=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set Balance=?, Type=?, `Credit limit`=?, UserID=? where AccountNumber=?',
      [account.Balance, account.Type, account.creditLimit, account.UserID, id],
      callback
    );
  }
};
module.exports = account;