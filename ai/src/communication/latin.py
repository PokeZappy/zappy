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
                                        # MM to Collector
                                        'focalisation sur ces ressources': 'focus in his opibus : ',
                                        'point de dépot': 'collectio rerum : ',
                                       'inventaire des explorateur': 'quid habes ut nobis offerat',
                                        'demande de ressources': 'vade ad me aliquid : ',

                                        #  Push to coll
                                        'Vous pouvez passez maître': 'Potes dominum facti',

                                        # Coock to ALL
                                        # TODO - ajouter le nombre pour chaque avec l'id
                                        'Vous êtes servi maître': 'dominus servivit : ',

                                        # MM to Incant
                                       'ressources placés pour l\'incantation': 'facultates positas carmina',

                                        # Coll to MM
                                        'ressources déposées': 'opes deposita',
                                        # TODO - parse l'inventaire


                                        # Incant to MM
                                        'incantation raté': 'defecit carmen',

                                        # All to push
                                        'confirmation id': 'sum socius senatus',

                                        # COOCK to push
                                        'voici votre repas': 'hic est prandium tuum',

                                        # MM to push
                                        'deplace-toi vers : ': 'movere ad',
                                        'changement de rôle': 'factus es : ',

                                        # North_guard to ALL
                                        'voici le nord': 'est dominus aquilonis',
                                        'évo de niveau': 'nobilis incantatio',
                                        'Collector': 'Collector',
                                        'Pusher': 'Pusher',
                                        'Incantator': 'Incantator',
                                        'Progenitor': 'Progenitor',

                                        'Où vais-je': 'Quo ego vado',
                                        'point de ralliment': 'collectio militum : ',


                                       'etat ressources': 'ut inventarium rerum',

                                        'assignation rôles': 'assignationem partium : ',
                                        'nouvelle tâche': 'habes novum negotium : ',

                                        'reconfiguration des rôles': 'omnis fit : ',

                                        'presence ennemis': 'inimicos recta praemisit',

                                        'temps restant incantation': 'quantum temporis reliquum est carminibus',

                                        'besoin aide': 'auxilium postulo',

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
