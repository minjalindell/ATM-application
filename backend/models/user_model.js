const db = require('../database');

const user = {
  getAll: function(callback) {
    return db.query('select * from user', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from user where userID=?', [id], callback);
  },
  add: function(user, callback) {
    return db.query(
      'insert into user (userID,fname,lname,Address,BDate) values(?,?,?,?,?)',
      [user.userID,user.fname, user.lname, user.Address, user.BDate],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from user where userID=?', [id], callback);
  },
  update: function(id, user, callback) {
    return db.query(
      'update user set fname=?,lname=?, Address=?, BDate=? where userID=?',
      [user.fname, user.lname, user.Address, user.BDate, id],
      callback
    );
  }
};
module.exports = user;