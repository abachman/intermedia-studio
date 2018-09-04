We can generate and send requests to the web app directly from the command line. curl is built in if you're on a MAC, Windows may take a bit more work.


Publish fake board checks to /ping

    curl -XPOST -H"Content-Type:application/json" \
        -d '{"board_id":"testing","mac":"AA:BB:CC:DD:EE"}' \
        https://board-connection-check.glitch.me/ping


Publish a new word to add to the story

    curl -XPOST -H"Content-Type:application/json" \
        -d '{"board_id":"testing","word":"yessssssssss"}' https://board-connection-check.glitch.me/word


Get a random word

    curl https://board-connection-check.glitch.me/word.txt

Get all the words

    curl https://board-connection-check.glitch.me/words

Reset the database

    curl -XPOST -H"Content-Type:application/json" \
        -d '{"password":"ha ha nope"}' https://board-connection-check.glitch.me/reset
