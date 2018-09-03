#
# sends random words to the demo app (words on macOS)
#

ID = "word spitter #{rand(10000000)}"

WORDS = [ "humble", "brave", "courageous", "serious", "resourceful",
          "stubborn", "loyal", "gullible", "selfish", "generous",
          "self-confident", "respectful", "considerate", "imaginative",
          "brilliant", "creative", "independent", "carefree", "studious",
          "intelligent", "honest", "mischievous", "adventurous", "hardworking",
          "daring", "charming", "lazy", "patriotic", "successful",
          "responsible", "helpful", "cautious", "polite", "conceited",
          "leader", "demanding", "bossy", "gentle", "loving", "proud",
          "mysterious", "eager", "hopeful", "lucky", "cooperative",
          "ambitious", "quiet", "curious", "mature", "witty", "determined",
          "energetic", "calm", "mannerly", "rude", "strict", "annoyed",
          "foolish", "grumpy", "miserable", "talented", "sly", "skillful",
          "rich", "thoughtful", "tolerant", "trustworthy", "weak", "wise",
          "jealous", "lonely", "faithful", "timid", "shy" ]

loop do
  word = WORDS.sample
  puts "#{ID} is sending '#{word}'"

  `curl --silent -XPOST -H"Content-Type:application/json" -d '{"board_id":"#{ID}","word":"#{word}"}' https://board-connection-check.glitch.me/word`

  sleep 30
end
