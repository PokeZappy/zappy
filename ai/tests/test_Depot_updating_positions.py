import socket
import pytest

from ai.src.player.depot import Depot


class TestUpdatingPositions:

    def test_updating_both_positions_successfully(self):
        depot = Depot(serv_info=[1, 2, 3], cli_socket=socket.socket(), debug_mode=True)
        depot.updating_positions(start=(1, 1), end=(2, 2))
        assert depot.pos == (1, 1)
        assert depot.the_place_to_be == (2, 2)

    def test_updating_only_start_position(self):
        depot = Depot(serv_info=[1, 2, 3], cli_socket=socket.socket(), debug_mode=True)
        depot.updating_positions(start=(1, 1))
        assert depot.pos == (1, 1)
        assert depot.the_place_to_be == (0, 0)

    def test_updating_only_end_position(self):
        depot = Depot(serv_info=[1, 2, 3], cli_socket=socket.socket(), debug_mode=True)
        depot.updating_positions(end=(2, 2))
        assert depot.pos == (0, 0)
        assert depot.the_place_to_be == (2, 2)

    def test_updating_positions_with_default_values(self):
        depot = Depot(serv_info=[1, 2, 3], cli_socket=socket.socket(), debug_mode=True)
        depot.updating_positions(start=(-1, -1), end=(-1, -1))
        assert depot.pos == (0, 0)
        assert depot.the_place_to_be == (0, 0)

    def test_updating_positions_with_large_values(self):
        depot = Depot(serv_info=[1, 2, 3], cli_socket=socket.socket(), debug_mode=True)
        large_value = 10**6
        depot.updating_positions(start=(large_value, large_value), end=(large_value + 1, large_value + 1))
        assert depot.pos == (large_value, large_value)
        assert depot.the_place_to_be == (large_value + 1, large_value + 1)
