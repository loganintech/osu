/*
 * Write your routing code in this file.  Make sure to add your name and
 * @oregonstate.edu email address below.
 *
 * Name: Logan Saso
 * Email: logan.saso2016@gmail.com
 */

var path = require('path');
var express = require('express');
var exphbs = require('express-handlebars');
var app = express();
var port = process.env.PORT || 3000;

const postData = require('./postData.json');

app.engine('handlebars', exphbs({
   defaultLayout: 'outline',
   partialsDir: [
     "views/partials/"
   ]
}));

app.use(express.static('views/other'));

app.set('view engine', 'handlebars');

app.get('/', (req, res) => {
  res.status(200).render("layouts/main", {
    posts: postData
  });
});

app.param(['num'], function(req, res, next, value) {
  next();
});

app.get('/posts/:num', (req, res, next) => {
  //req.params.num
  if (postData.length < parseInt(req.params.num)) {
    next();
  } else {
    res.status(200).render('layouts/posts', {
      post: postData[req.params.num]
    });
  }

});

app.get('*', (req, res) => {
  console.log(req.url);
  res.status(404).render('layouts/404');
});

app.listen(port, () => {
  console.log("== Server is listening on port", port);
});

