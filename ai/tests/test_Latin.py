import os
import sys

import pytest

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from ai.src.communication.latin import Latin


class TestLatin:

    #  initialization of Latin class creates a dictionary with correct keys and values
    def test_initialization_creates_correct_dict(self):
        latin = Latin()
        expected_dict = {
            'point de ralliment': 'collectio militum : ',
            'point de dépot': 'collectio rerum : ',
            'évo de niveau:': 'nobilis incantatio',

            'inventaire des explorateur': 'quid habes ut nobis offerat',
            'etat ressources': 'ut inventarium rerum',
            'ressources placés pour l\'incantation': 'facultates positas carmina',

            'assignation rôles': 'assignationem partium : ',
            'nouvelle tâche': 'habes novum negotium : ',

            'changement de rôle': 'factus es : ',
            'reconfiguration des rôles': 'omnis fit : ',

            'presence ennemis': 'inimicos recta praemisit',

            'temps restant incantation': 'quantum temporis reliquum est carminibus',

            'besoin aide': 'auxilium postulo',
            'identification': 'Quis es',
            'demande de ressources': 'vade ad me aliquid : ',

            'confirmation id': 'sum socius senatus',
            'confirmation action': 'hic servio tibi domino',

            'plan de bataille': 'pugnae consilia',
            'strat ressources': 'omnis venite ut',

            'divertis-moi (peroquet)': 'oblectas',
            'pousse les autres': 'officium tuum est ad ventilabis inimicos'
        }
        assert latin.verbum == expected_dict

    #  accessing a valid key in the verbum dictionary returns the correct Latin translation
    def test_access_valid_key_returns_correct_translation(self):
        latin = Latin()
        assert latin.verbum['point de ralliment'] == 'collectio militum : '

    #  adding a new key-value pair to the verbum dictionary works as expected
    def test_adding_new_key_value_pair(self):
        latin = Latin()
        latin.verbum['nouveau mot'] = 'novum verbum'
        assert latin.verbum['nouveau mot'] == 'novum verbum'

