import pytest

from src.player.depot import Depot


class TestRaidsResources:

    def test_collects_all_resources_in_focus(self, mocker):
        mock_socket = mocker.Mock()
        depot = Depot([1, 5, 5], mock_socket, debug_mode=True)
        depot.take_obj = mocker.Mock()
        depot.recv_action = mocker.Mock(return_value='ok')
    
        tile = ['food', 'linemate', 'sibur']
        depot.raids_resources(tile)
    
        assert depot.take_obj.call_count == 3
        assert depot.inventory['food'] == 11
        assert depot.inventory['linemate'] == 1
        assert depot.inventory['sibur'] == 1

    def test_updates_inventory_on_successful_collection(self, mocker):
        mock_socket = mocker.Mock()
        depot = Depot([1, 5, 5], mock_socket, debug_mode=True)
        depot.take_obj = mocker.Mock()
        depot.recv_action = mocker.Mock(return_value='ok')
    
        tile = ['food', 'linemate']
        depot.raids_resources(tile)
    
        assert depot.inventory['food'] == 11
        assert depot.inventory['linemate'] == 1

    def test_calls_take_obj_for_each_resource_in_focus(self, mocker):
        mock_socket = mocker.Mock()
        depot = Depot([1, 5, 5], mock_socket, debug_mode=True)
        depot.take_obj = mocker.Mock()
        depot.recv_action = mocker.Mock(return_value='ok')
    
        tile = ['food', 'linemate', 'sibur']
        depot.raids_resources(tile)
    
        depot.take_obj.assert_any_call('food')
        depot.take_obj.assert_any_call('linemate')
        depot.take_obj.assert_any_call('sibur')

    def test_no_resources_to_collect_from_empty_tile(self, mocker):
        mock_socket = mocker.Mock()
        depot = Depot([1, 5, 5], mock_socket, debug_mode=True)
        depot.take_obj = mocker.Mock()
        depot.recv_action = mocker.Mock(return_value='ok')
    
        tile = []
        depot.raids_resources(tile)
    
        assert depot.take_obj.call_count == 0

    def test_ignores_resources_not_in_focus(self, mocker):
        mock_socket = mocker.Mock()
        depot = Depot([1, 5, 5], mock_socket, debug_mode=True)
        depot.take_obj = mocker.Mock()
        depot.recv_action = mocker.Mock(return_value='ok')
    
        tile = ['stone', 'wood']
        depot.raids_resources(tile)
    
        assert depot.take_obj.call_count == 0

    def test_handles_non_ok_response(self, mocker):
        mock_socket = mocker.Mock()
        depot = Depot([1, 5, 5], mock_socket, debug_mode=True)
        depot.take_obj = mocker.Mock()
        depot.recv_action = mocker.Mock(return_value='ko')
    
        tile = ['food']
        depot.raids_resources(tile)
    
        assert depot.inventory['food'] == 10
