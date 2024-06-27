from socket import socket

from ai.src.player.player import Player


class Elder(Player):
    """
    The Elder class represents a player with advanced capabilities and functionalities in the game environment.
    It extends the Player class and provides additional features for higher-level gameplay.
    """
    def __init__(self, serv_info: list[int] | None = None, cli_socket: socket | None = None, debug_mode: bool = False):
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)

    def explain_the_history(self) -> None:
        """
        Explain the history of the game environment and decrease player's life.

        This method sends a broadcast message with the history of the game empire to other players.

        :return: None
        """
        if self.message.uuid_used:
            self.message.buf_messages(message='haec est historia imperii ACCMST',
                                      infos=[(uuid, '0') for uuid in self.message.uuid_used])
            self.queue.append('Broadcast')
            self.life -= self.ACTION

    def make_action(self) -> None:
        if len(self.actions) >= 1:
            return
        if 0 < len(self.queue) and len(self.actions) < 1:
            self.apply_action()
        # if self.life <= 300:
        #     self.queue.append(('Take', 'food'))
        # else:
        self.explain_the_history()
