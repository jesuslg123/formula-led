$(document).ready(function(){
  //connect to the socket server.
  var socket = io.connect('http://' + document.domain + ':' + location.port);

  // handle messages with 'track' topic
  socket.on('track', function(msg) {
    var message = msg.data.command_value;

    if (message == "start") {
      $('#end').html("");
      $('#elapsed').html("");
      $('#player_one_loop').html("");
      $('#player_two_loop').html("");
      $('#player_one_speed').html("");
      $('#player_two_speed').html("");
      $('#winner').html("");
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
    var loop_time = msg.data.loop_time;
    var speed = msg.data.speed_value;

    if (player === "1") {
      if (loop !== undefined || "") {
        $('#player_one_loop').html("Player " + player + " just completed loop " + loop + " in " + loop_time + " seconds!");
      } else {
        $('#player_one_speed').html(speed)
      }
    }

    if (player === "2") {
      if (loop !== undefined || "") {
        $('#player_two_loop').html("Player " + player + " just completed loop " + loop + " in " + loop_time + " seconds!");
      } else {
        $('#player_two_speed').html(speed)
      }
    }
  });
});
