import sys
import os

import pytest
import socket

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from src.player.depot import Depot


class TestDepot:

    def test_updating_positions_correctly_updates_start_and_end_positions(self):
        depot = Depot([1, 5, 5], socket.socket(), debug_mode=True)
        depot.updating_positions((2, 3), (4, 4))
        assert depot.pos == (2, 3)
        assert depot.the_place_to_be == (4, 4)

    def test_delivery_method_calculates_path_correctly(self, mocker):
        mocker.patch('src.mvt.path.Path.get_path', return_value=[(1, 0), (1, 1)])
        depot = Depot([1, 5, 5], socket.socket(), debug_mode=True)
        depot.delivery()
        assert depot.path.get_path.called

    def test_updating_positions_with_default_values_does_not_change_positions(self):
        depot = Depot([1, 5, 5], socket.socket(), debug_mode=True)
        initial_pos = depot.pos
        initial_the_place_to_be = depot.the_place_to_be
        depot.updating_positions()
        assert depot.pos == initial_pos
        assert depot.the_place_to_be == initial_the_place_to_be

    def test_delivery_handles_empty_path_gracefully(self, mocker):
        mocker.patch('src.mvt.path.Path.get_path', return_value=[])
        depot = Depot([1, 5, 5], socket.socket(), debug_mode=True)
        depot.delivery()
        assert depot.path.get_path.called
