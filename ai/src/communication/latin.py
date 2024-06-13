from dataclasses import dataclass


@dataclass
class Latin(object):
    """
    The Latin class initializes a dictionary named verbum that maps French phrases to their Latin translations. This
    dictionary is used to store and retrieve Latin translations for specific French terms.
    """

    def __init__(self) -> None:
        """
        Initialize the Latin class with a dictionary of Latin phrases and their translations.
        """
        self.verbum: dict[str, str] = {
                                        'Collector': 'Collector',
                                        'Pusher': 'Pusher',
                                        'Incantator': 'Incantator',
                                        'Progenitor': 'Progenitor',

                                        'Où vais-je': 'Quo ego vado',
                                        'point de ralliment': 'collectio militum : ',

                                        'identification': 'Quis es', # TODO - Collector - Pusher
                                        'la voie est libre': 'patet via', # TODO - Pusher - Collector

                                        'point de dépot': 'collectio rerum : ',
                                        'évo de niveau': 'nobilis incantatio',

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
                                        'demande de ressources': 'vade ad me aliquid : ',

                                        'confirmation id': 'sum socius senatus',
                                        'confirmation action': 'hic servio tibi domino',

                                        'plan de bataille': 'pugnae consilia',
                                        'strat ressources': 'omnis venite ut',

                                        'divertis-moi (peroquet)': 'oblectas',
                                        'pousse les autres': 'officium tuum est ad ventilabis inimicos',

                                        'qui est le mastermind ?': 'quis est dominus mentis',
                                        'c\'est moi': 'ego sum',

                                        'zero': 'nulla',
                                        'un': 'unum',
                                        'deux': 'duo',
                                        'trois': 'tres',
                                        'quatre': 'quattuor',
                                        'cinq': 'quinque',
                                        'six': 'sex',
                                        'sept': 'septem',
                                        'huit': 'octo',
                                        'neuf': 'novem',
                                       }
