const express = require('express')
const app = express()

// noinspection JSUnresolvedFunction
app.get('/', (req, res) => {
  res.send('hello world')
})

let open = false

// noinspection JSUnresolvedFunction
app.get('/open', (req, res) => {
  if (open) {
    open = false
    res.send(true)
  } else {
    res.send(false)
  }
})

// noinspection JSUnresolvedFunction
app.get('/set-open', (req, res) => {
  open = true
  res.send('done')
})

const PORT = 8080
app.listen(PORT, () => {
  console.log('Example app listening on port ' + PORT)
})
