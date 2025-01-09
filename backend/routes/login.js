const express = require('express');
const router = express.Router();
const login = require('../models/login_model');
const bcrypt=require('bcryptjs');
const jwt=require('jsonwebtoken');

router.post('/', function(request, response) {
    console.log("login test");
    if (request.body.cardNumber && request.body.pin) {
        const username = request.body.cardNumber;
        const pin = request.body.pin;
        console.log("Input cardNumber:", username);

        login.checkPassword(username, function(dbError, dbResult) {
            
            if (dbError) {
                response.status(500).json({ error: 'Database error' });
                return;
            }

            if (dbResult.length > 0) {
                
                const storedpin = dbResult[0].pin;
                console.log("Stored pin:", storedpin);
                console.log("Provided pin:", pin);
                
                bcrypt.compare(request.body.pin, dbResult[0].pin, function(err, compareResult){
                    if (compareResult) {
                        console.log("Login successful");
                        const token=genToken({username: request.body.username});
                        response.send(token);
                    } else {
                        console.log("Incorrect pin");
                        response.send(false);
                    }
                })
            } else {
                console.log("User not found");
                response.send(false);
            }
        });
    } else {
        console.log("cardNumber or pin missing");
        response.status(400).json({ error: 'cardNumber or pin missing' });
    }
});

function genToken(value){
    return jwt.sign(value, process.env.MY_TOKEN, {expiresIn: '200s'});
}

module.exports = router;

