from socket import socket

from ai.src.player.player import Player


class Pusher(Player):
    """
    Pusher class
    """

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        """
        Pusher class constructor
        """
        super().__init__(serv_info, cli_socket, debug_mode)
        self.you_should_not_pass = True
        self.is_in_position = False
        self.goto = None
        self.id = 0
        self.get_id('Quis est puer interfector?')

    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        if buf[-1] == '\n':
            buf = buf[:-1]
        if buf == 'ok':
            if self.actions[0] == 'Take food':
                self.life += self.FOOD
        elif buf == 'ko':
            if self.actions[0] == 'Take food':
                #TODO: communication('Need food')
                pass
        else:
            #TODO: understanding broadcast

            #TODO: set understanding in broadcast(there is food, let me pass, etc.)
            pass
        pass

    def make_action(self) -> None:
        """
        This method makes the action of the incantator.
        """
        if len(self.actions) > 1:
            return
        if self.life <= 300:
            print("life")
            self.queue.append('Take food')
        elif self.goto is None:
            self.message.buf_messages('Pusher')
            self.message.buf_messages('Quo ego vado')
            self.queue.append('Broadcast')
            print("after_broadcast")
            # self.goto = not None
        elif not self.is_in_position:
            #TODO: ask for a direction to go to
            pass
        elif self.you_should_not_pass:
            self.eject()
        self.apply_action()

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'sum socius senatus':
            # TODO: parler et dire 'Potes dominum facti' et ne pas pousser pendant X temps
            pass
        if message['msg'] == 'hic est prandium tuum':
            # TODO: prendre la bouffe sur la case
            pass
        if message['msg'] == 'movere ad':
            #TODO: GoTO
            pass
        if message['msg'] == 'Ego sum puer inteffector':
            # TODO - ADD parser id to replace missing id if collector died
            self.id += 1
        if message['msg'] == 'Quis est puer interfector?':
            self.message.buf_messages('Ego sum puer inteffector', infos=[self.id])
            self.queue.insert(0, 'Broadcast')
            self.apply_action()
        self.global_message()
