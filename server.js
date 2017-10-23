const express = require('express')
const app = express()

// noinspection JSUnresolvedFunction
app.get('/', function (req, res) {
  res.send('hello world')
})

const PORT = 8001
app.listen(PORT, function () {
  console.log('Example app listening on port ' + PORT)
})
