from socket import socket

from ai.src.player.player import Player
from ai.src.gameplay.enum_gameplay import TESTUDO
from ai.src.utils.messages import get_id_testudo


class Pusher(Player):
    """
    Pusher class
    """

    def __init__(self,
                 serv_info: list[int] | None = None,
                 cli_socket: socket | None = None,
                 debug_mode: bool = False):
        """
        Pusher class constructor
        """
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.id: int = 0
        self.first: bool = True
        self.start: bool = False
        self.hard_push: bool = False
        self.you_should_not_pass: bool = True
        self.dead_end: bool = False
        self.timing: bool = True
        self.vice: bool = False
        self.spartiate: bool = False
        self.said: bool = False
        self.count: int = 0
        print('je suis sasa')

    def go_to_start(self) -> None:
        if self.id == 1:
            self.queue.append('Right')
            self.life -= self.ACTION
        if self.id == 3:
            self.queue.append('Left')
            self.life -= self.ACTION
        if self.id == 2:
            self.queue.append('Right')
            self.queue.append('Right')
            self.life -= self.ACTION * 2
        self.queue.append('Forward')
        self.life -= self.ACTION
        self.start = True

    def make_action(self) -> None:
        """
        Perform the next action based on the current state of the player.
        This method checks if there are pending actions,
        looks around if needed, and applies the next action in the queue.

        :return: None
        """
        if self.first is True and self.dead_end is False:
            self.get_id('Quis est puer interfector?')
            self.dead_end = True
        if 0 < len(self.queue) and len(self.actions) < 1:
            self.apply_action()
            self.count += 1
            # if self.count % 1_000 == 0:
            # if self.id == 0:
            # print(f'Mat id: {self.id}\nqueue: {self.queue}\naction: {self.actions}\nlife: {self.life}\nstart: {self.start}')
        if self.life < 300 and self.said is False and self.spartiate is False and self.start is True:
            # TODO -enelever print débug et l'utilisation du timing si pas utilisé
            print(f'je vais mdr: {self.id}')
            if self.id == 0:
                print(f'0 va vers la mort')
                self.message.buf_messages('Dimissus a Legione Honoris')
            if self.id == 1:
                print(f'1 va vers la mort')
                self.message.buf_messages('Dimissus a legione prima')
            if self.id == 2:
                print(f'2 va vers la mort')
                self.message.buf_messages('Dimissus a legione secunda')
            if self.id == 3:
                print(f'3 va vers la mort')
                self.message.buf_messages('Dimissus a legione tertia')
            self.queue.insert(0, 'Broadcast')
            self.said = True
        if len(self.actions) > 0:
            return
        if self.you_should_not_pass is True and self.start is True and self.said is False:
            self.queue.append('Eject')
            self.life -= self.ACTION
            if self.count % 18 == 0:
                self.queue.append('Inventory')
                self.life += 1
            self.count += 1
        elif self.start is True:
            self.queue.append('Inventory')
            self.life -= self.INVENTORY

    def broadcast_traitement(self, message: tuple | str | dict) -> None:
        if message['msg'] == 'est dominus aquilonis' and self.start is False:
            if self.path.facing is None:
                self.path.get_north(message['direction'])
                self.turn_to_the_north()
                if self.id >= 4 and self.hard_push is True and self.spartiate is True:
                    self.go_testudo()
                    return
            if self.got_id > 2 and (self.first is True or self.vice is True):
                print(f"fox : {self.id}")
                if self.id >= 4:
                    self.kill_me()
                    return
                self.go_to_start()
            else:
                print(f'kiwi got_id: {self.got_id}\nfirst: {self.first}\nvice: {self.vice}')
        elif message['msg'] == 'Ego sum puer inteffector' and self.got_id < 3 and self.first is True:
            self.id += 1
            print(f'identifiant inc : {self.id}')
        elif message['msg'] == 'Quis est puer interfector?' and self.first is True:
            self.message.buf_messages('Ego sum puer inteffector', my_id=[self.id])
            self.queue.insert(0, 'Broadcast')
            self.life -= self.ACTION
        elif message['msg'] == 'situm intrare' and self.hard_push is False and self.spartiate is False:
            if self.you_should_not_pass is True:
                self.you_should_not_pass = False
        elif message['msg'] == 'Non Potes dominum facti':
            self.you_should_not_pass = True
            self.queue.append('Inventory')
        elif message['msg'] == 'satus testudo : ' and (self.spartiate is True):
            if self.id == 0 and self.start is True:
                self.you_should_not_pass = False
            if self.start is False and self.id == 0 and self.first is False:
                self.id = get_id_testudo(message['infos'])
                if self.path.facing is None:
                    return
                for move in TESTUDO[self.id]['path']:
                    self.queue.append(move)
                self.hard_push = True
                self.start = True
        elif message['msg'] == 'occupat exercitum : ' and self.vice is True and self.start is False:
            self.got_id = 3
            print(f'U R WRITE')
            print(f'id {message['id']}')
            print(f'infos {message["infos"]}')
            self.id = get_id_testudo(message['infos'])
            print(f'Coucou chui {self.id}')
        elif message['msg'] == 'occupat exercitum : ':
            print(f"just chialling: {self.id}\nstart: {self.start}\ngta vice: {self.vice}")
        self.global_message(message)

    def go_testudo(self):
        for move in TESTUDO[self.id]['path']:
            self.queue.append(move)
        self.start = True

    def kill_me(self):
        for _ in range(self.inventory['food'] - 1):
            self.queue.append(('Set', 'food'))


class VicePusher(Pusher):
    def __init__(self,
                 serv_info: list[int] | None = None,
                 cli_socket: socket | None = None,
                 debug_mode: bool = False):
        """
        Pusher class constructor
        """
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.id: int = 0
        self.got_id: int = 1
        self.first: bool = False
        self.start: bool = False
        self.hard_push: bool = False
        self.you_should_not_pass: bool = True
        self.dead_end: bool = True
        self.vice: bool = True
        self.spartiate: bool = False
        print(f'je spawn bg')


class Spartiate(Pusher):
    def __init__(self,
                 serv_info: list[int] | None = None,
                 cli_socket: socket | None = None,
                 debug_mode: bool = False):
        """
        Pusher class constructor
        """
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.id: int = 0
        self.got_id: int = 3
        self.first: bool = False
        self.start: bool = False
        self.hard_push: bool = False
        self.you_should_not_pass: bool = True
        self.dead_end: bool = True
        self.vice: bool = False
        self.spartiate: bool = True
