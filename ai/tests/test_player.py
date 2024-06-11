# import sys
# import os
# from src.gameplay.enum_gameplay import Directions as dir
# import pytest
#
# sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
#
# from src.player.player import Player
#
# class TestPlayer:
#
#     def test_player_init(self):
#         player = Player([1, 5, 5], 1)
#
#         try:
#             assert player.pos_view('y', 0, dir.NORTH) == 0
#             assert player.pos_view('y', 1, dir.NORTH) == 1
#             assert player.pos_view('y', 3, dir.NORTH) == -1
#             assert player.pos_view('y', 4, dir.NORTH) == 2
#             assert player.pos_view('y', 8, dir.NORTH) == -2
#             assert player.pos_view('y', 9, dir.NORTH) == 3
#             assert player.pos_view('y', 15, dir.NORTH) == -3
#             assert player.pos_view('y', 16, dir.NORTH) == 4
#             assert player.pos_view('y', 24, dir.NORTH) == -4
#             assert player.pos_view('y', 25, dir.NORTH) == 5
#         except AssertionError as e:
#             pytest.fail(f"{e} pos_view('x', i, dir.NORTH) failed")
#
#         try:
#             assert player.pos_view('x', 0, dir.NORTH) == 0
#             assert player.pos_view('x', 1, dir.NORTH) == -1
#             assert player.pos_view('x', 3, dir.NORTH) == -1
#             assert player.pos_view('x', 4, dir.NORTH) == -2
#             assert player.pos_view('x', 8, dir.NORTH) == -2
#             assert player.pos_view('x', 9, dir.NORTH) == -3
#             assert player.pos_view('x', 15, dir.NORTH) == -3
#             assert player.pos_view('x', 16, dir.NORTH) == -4
#             assert player.pos_view('x', 24, dir.NORTH) == -4
#             assert player.pos_view('x', 25, dir.NORTH) == -5
#         except AssertionError as e:
#             pytest.fail(f"{e} pos_view('x', i, dir.NORTH) failed")
#
