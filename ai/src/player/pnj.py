from socket import socket
from re import match

from ai.src.player.player import Player
from ai.src.utils.messages import extract_inventory


class Pnj(Player):
    """
    Pnj class
    """

    def __init__(self, serv_info: list[int] | None = None, cli_socket: socket | None = None, debug_mode: bool = False):
        """
        Pnj class constructor
        """
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.goto = None
        self.dir = None
        self.first_round = True
    
    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        if len(self.actions) == 0:
            recv_list = self.message.receive(buf)
        else:
            recv_list = self.message.receive(buf, self.actions[0])
        for recv_type, msgs in recv_list:
            if recv_type == 'elevation':
                matches = match(r'Current level: (\d+)', msgs)
                if matches:
                    self.queue = []
                    if int(msgs[-1]) == 2:
                        # print('I am level 2, here')
                        self.queue.append('Right')
                        self.queue.append('Right')
                        self.queue.append('Forward')
                    self.queue.append(('Take', 'food'))
                    self.queue.append(('Take', 'food'))
                    self.queue.append(('Take', 'food'))
                    # if int(match.group(1)) == 2:
                    #     self.message.buf_messages('motus sum')
                    #     self.queue.append('Broadcast')
                continue
            elif recv_type == 'eject':
                continue
            elif recv_type == 'inventory':
                self.inventory = extract_inventory(msgs)
                self.life = self.inventory['food'] * self.FOOD
            elif recv_type == 'ok':
                if isinstance(msgs, str) and msgs[0] == 'Take' and msgs[1] == 'food':
                    self.life += self.FOOD
            elif recv_type == 'broadcast':
                if msgs == 'ko':
                    continue
                for msg in msgs:
                    self.broadcast_traitement(msg)
                continue
            try:
                self.actions.pop(0)
            except Exception as e:
                print(f"Error: {e}")
                print(f"Unknown message type for Pnj: {recv_type}, msg {msgs}, buf {buf}")

            
        

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'movere ad : ':
            self.goto = message['info']
        if message['msg'] == 'est dominus aquilonis':
            if self.path.facing is None:
                self.path.get_north(message['direction'])
                if self.path.facing == 0:
                    self.queue.append('Left')
                    self.queue.append('Forward')
                elif self.path.facing == 3:
                    self.queue.append('Forward')
                elif self.path.facing == 2:
                    self.queue.append('Right')
                    self.queue.append('Forward')
                else:
                    self.queue.append('Right')
                    self.queue.append('Right')
                    self.queue.append('Forward')
                self.message.buf_messages('motus sum')
                self.queue.append('Broadcast')
                # self.queue.append(('Take', 'food'))
                # self.queue.append(('Take', 'food'))
                # self.queue.append(('Take', 'food'))

    def make_action(self) -> None:
        """
        This method makes the action.
        """
        if self.first_round:
            # self.queue.append(('Set', 'food'))
            self.first_round = False
        if len(self.queue) > 0 and len(self.actions) < 1:
            # print(f"témort {self.queue}")
            # print(f"tamer : {self.actions}")
            # print(f"tégrenmort {self.life}")
            self.apply_action()
        if len(self.actions) > 0:
             return
        if self.life <= 500:
            # print('I am hungry')
            self.queue.append(('Take', 'food'))
            self.queue.append(('Take', 'food'))
            self.queue.append(('Take', 'food'))
        if self.level >= 1:
            # print('I , here')
            self.queue.append('Inventory')

