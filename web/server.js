var express = require('express')
var app = express()
var exphbs  = require('express-handlebars')

// Serve static files
app.use(express.static('public'))

// Use handlebars teplating engine
app.engine('handlebars', exphbs({defaultLayout: 'main'}))
app.set('view engine', 'handlebars')

app.get('/', function (req, res) {
  res.render('home')
})

app.listen(3000, function () {
  console.log('Example app listening on port 3000!')
})
