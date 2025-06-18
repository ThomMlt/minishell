Minishell

Minishell est un projet de l'école 42 consistant à recréer un shell UNIX minimaliste, capable de lancer des commandes, gérer les redirections, les pipes, et quelques built-ins. Ce projet permet d'approfondir ses connaissances sur les processus, les signaux, la gestion de la mémoire, et les appels systèmes.
🛠️ Fonctionnalités implémentées
Built-ins pris en charge :

    cd

    echo (avec ou sans -n)

    env

    exit

    export

    pwd

    unset

Comportements du shell :

    Exécution de commandes avec ou sans chemin absolu.

    Support des pipes (|) entre plusieurs commandes.

    Gestion des redirections :

        Entrée : <

        Sortie : >

        Append : >>

        Here-document : << (avec gestion des signaux dans ce contexte).

    Expansions des variables d'environnement ($USER, $PATH, etc).

    Gestion des signaux :

        Ctrl + C : interrompt la commande en cours.

        Ctrl + \ : ignoré.

        Ctrl + D : gère la fermeture propre du shell.

    Gestion des erreurs pour :

        Redirections invalides

        Commandes introuvables

        Quotes non fermées (affichage d'une erreur sans provoquer de crash)

🧠 Structure du projet

Le cœur de l'implémentation repose sur une liste chaînée de commandes (t_cmd). Chaque nœud de cette liste représente une commande séparée par un pipe.

Chaque t_cmd contient :

    Une liste de redirections d'entrée (t_redir_in)

    Une liste de redirections de sortie (t_redir_out)

Cette structure permet de gérer un nombre illimité de redirections par commande, tout en gardant une architecture claire et modulaire.
🚀 Détails supplémentaires

Bien que certaines fonctionnalités ne soient pas obligatoires, j'ai choisi d'en intégrer quelques-unes supplémentaires pour améliorer la robustesse du shell, comme :

    La gestion des signaux dans les here_doc

    La gestion d’erreurs dans certains cas non spécifiés (ex : quotes non fermées)

⚠️ Attention cependant : il est crucial de ne pas ajouter de comportements non demandés qui pourraient entraîner des divergences avec les attentes du sujet. Il faut avant tout éviter les segfaults, les fuites mémoire, et rester conforme à la norme POSIX dans la mesure du possible.
🧪 Tests et vérifications

    Utilisation de Valgrind pour s'assurer de l'absence de fuites mémoire.

    Tests avec bash et sh pour comparer les comportements standards.

    Vérification de la gestion des redirections combinées et des expansions dans différents contextes.
