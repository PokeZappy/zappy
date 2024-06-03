from dataclasses import dataclass


@dataclass
class Latin(object):

    def __init__(self):
        self.verbum: dict[str, str] = {'point de ralliment': 'collectio militum : ',
                                       'point de dépot': 'collectio rerum : ',
                                       'évo de niveau:': 'nobilis incantatio',

                                       'inventaire des explorateur': 'quid habes ut nobis offerat',
                                       'etat ressources': 'ut inventarium rerum',

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
