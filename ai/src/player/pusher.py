from socket import socket

from ai.src.player.player import Player


class Pusher(Player):
    """
    Pusher class
    """

    def __init__(self, serv_info: list[int] | None = None, cli_socket: socket | None = None, debug_mode: bool = False):
        """
        Pusher class constructor
        """
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.you_should_not_pass = True
        self.id = 0
        self.get_id('Quis est puer interfector?')
        self.start: bool = False

    def go_to_start(self) -> None:
        if self.id == 1:
            self.queue.append('Right')
            self.life -= self.ACTION
        if self.id == 2:
            self.queue.append('Left')
            self.life -= self.ACTION
        if self.id == 3:
            self.queue.append('Right')
            self.queue.append('Right')
            self.life -= self.ACTION * 2
        self.queue.append('Forward')
        self.life -= self.ACTION


    def make_action(self) -> None:
        """
        Perform the next action based on the current state of the player.
        This method checks if there are pending actions,
        looks around if needed, and applies the next action in the queue.

        :return: None
        """
        if 0 < len(self.queue) and len(self.actions) < 1:
            self.apply_action()
        if len(self.actions) > 0:
            return
        if self.you_should_not_pass:
            self.queue.append('Eject')
            self.life -= self.ACTION

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'est dominus aquilonis':
            if self.path.facing is None:
                self.path.get_north(message['direction'])
                self.turn_to_the_north()
            if self.got_id > 2 and self.start is False:
                self.go_to_start()
        if message['msg'] == 'Ego sum puer inteffector' and self.got_id < 3:
            # TODO - ADD parser id to replace missing id if collector died in :message['nbr'][0]
            self.id += 1
        if message['msg'] == 'Quis est puer interfector?':
            self.message.buf_messages('Ego sum puer inteffector', my_id=[self.id])
            self.queue.insert(0, 'Broadcast')
            self.life -= self.ACTION
        if message['msg'] == 'situm intrare':
            if self.you_should_not_pass is True:
                self.you_should_not_pass = False
        if message['msg'] == 'Non Potes dominum facti':
            self.you_should_not_pass = True
        self.global_message(message)
