require 'socket'
require 'thread'

threads = []

10.times do
  threads << Thread.new do
    s = TCPSocket.new 'localhost', 12345

    puts "start #{Process.pid}"

    20.times do
      random_size = (10 + (rand() * 200)).to_s

      # send data to the server using the protocol of NUMBER + NEW_LINE_CHARACTER
      s.print(random_size + "\n")

      # sleep a random amount of time around 0.1 seconds
      sleep(rand() * 0.4)
    end

    puts "exit #{Process.pid}"
  end

  sleep 0.7
end

threads.map(&:join)
