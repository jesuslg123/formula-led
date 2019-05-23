$(document).ready(function(){
  //connect to the socket server.
  var socket = io.connect('http://' + document.domain + ':' + location.port);

  // handle messages with 'track' topic
  socket.on('track', function(msg) {
    var message = msg.data.command_value;

    if (message == "start") {
      $('#start').html(message);
    }

    if (message == "end") {
      $('#end').html(message);
      $('#winner').html("Player " + msg.data.winner);
      $('#elapsed').html(msg.data.elapsed + " seconds");
    }

  });

  // handle messages with the 'player' topic
  socket.on('player', function(msg) {

    var player = msg.data.player_value;
    var loop = msg.data.loop_value;
    var loop_time = msg.data.loop_time

    if (player == "1") {
      $('#player_one_loop ').html("Player " + player + " just completed loop " + loop + " in " + loop_time + " seconds!");
    }

    if (player == "2") {
      $('#player_two_loop ').html("Player " + player + " just completed loop " + loop + " in " + loop_time + " seconds!");
    }
  });
});
