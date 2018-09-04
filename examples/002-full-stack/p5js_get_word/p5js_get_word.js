function setup() {
  createCanvas(windowWidth, windowHeight)
  background(100, 100, 200)
  textSize(48)
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight)
  background(100, 100, 200)
}

var isClicked = false

function draw() {
  if (isClicked) {
    fill(0)
    ellipse(mouseX, mouseY, 30, 30)
  }
}

function mousePressed() {
  isClicked = true
}

function mouseReleased() {
  isClicked = false
}

var requester = setInterval(function () {
  fetch('http://board-connection-check.glitch.me/word').then(function (response) {
    return response.json();
  }).then(function (json) {
    console.log("got a word", json)
    fill(255)
    text(json.word, random(width), random(height))
  }).catch(function (err) {
    // there was an error making requests, kill requester
    console.error("request failure!", err)
    clearInterval(requester)
  })
}, 5000)
