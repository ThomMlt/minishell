# Minishell
- [X] Afficher un prompt.

- [X] Avoir un historique de commandes fonctionnel.

- [X] Trouver et exécuter le bon exécutable (basé sur les variables du PATH ou en utilisant un chemin relatif ou absolu).

- [ ] Utiliser au maximum une seule variable globale pour indiquer un signal reçu.

- [ ] Ne pas interpréter les caractères spéciaux (comme `\` ou `;`) ni les guillemets (ou apostrophes) non fermés.

- [X] Gérer les apostrophes (`'`), qui empêchent le shell d’interpréter les métacaractères entre elles.

- [x] Gérer les guillemets (`"`), qui empêchent le shell d’interpréter les métacaractères entre elles, sauf pour le caractère `$`.

- [X] Implémenter les pipes (`|`) : la sortie de chaque commande dans le pipe doit être connectée à l'entrée de la commande suivante via un pipe.

- [X] Gérer les variables d’environnement (un `$` suivi d’une séquence de caractères) et les remplacer par leur valeur.

- [X] Gérer `$?`, qui doit être remplacé par le code de sortie du dernier pipeline exécuté au premier plan.

- [ ] Gérer `Ctrl-C`, `Ctrl-D` et `Ctrl-\` avec le même comportement que dans Bash.

- [ ] En mode interactif :
  * `Ctrl-C` affiche un nouveau prompt sur une nouvelle ligne.
  * `Ctrl-D` ferme le shell.
  * `Ctrl-\` ne fait rien.

- [ ] Implémenter ces redirections :
  * `<` doit rediriger l’entrée.
  * `>` doit rediriger la sortie.
  * `<<` doit recevoir un délimiteur, puis lire l’entrée jusqu’à ce qu’une ligne contenant ce délimiteur soit rencontrée. Ne dois pas mettre à jour l’historique.  
  * `>>` doit rediriger la sortie en mode ajout.
  
- [X] Le shell doit inclure ces commandes intégrées :
  * `echo` avec le paramètre `-n`.
  * `cd` avec uniquement un chemin absolu ou relatif.
  * `export` sans options.
  * `unset` sans options.
  * `env` sans options ni arguments.
  * `exit` sans options.

# Minishell

1. Boucle principale 
    1. Implémenter readline
    2. historique avec add_history (gestion seule des fleches)
2. Parsing des commandes 
    1. Tokeniser la ligne de commande reçue (le type de tokens : mots, opérateurs et guillemets, gérer également les variables d’environnement si $) :
        1. exemple : `echo "Hello world" | grep Hello > output.txt` 
            1. → echo : commande, “Hello World” argument, “|” pipe, “>” redirection, “output.txt : fichier”
    2. gérer les guillemets simples (’)
    3. les doubles (”)
    4. Gérer $? pour le statut de sortie
    5. copie de l’environnement, si modif de l’env doit être dans notre copie (attention les redirections et les pipes peuvent être collé !)
3. Execution des commandes 
    1. Rechercher l’exécutable dans le PATH
    2. gérer les chemins relatifs et absolus
    3. execution dans des FORK (pipex)
    4. gestion des erreurs d’exécution : les codes erreurs avec exit 
4. Implementation des built-ins
    1. Echo avec l’option -n (qui ne donne pas de retour à la ligne attention -n-n-n ou -n -n)
    2. cd : chemins relatifs et absolus
    3. pwd 
    4. export
    5. unset
    6. env
    7. exit : ici attention au code d’erreur
5. Gestion des redirections 
    1. < : entree
    2. << : here doc

6. gestion des pipes 

7. gestion des signaux
8. gestion des variables d’environnement 

Diagramme de PERT :

1. Boucle principale → 2. Parsing des commandes

2. Parsing des commandes → 3. Execution des commandes 

2. Parsing des commandes → 7. Gestion des signaux

2. Parsing des commandes → 8. Variables d’environnement 

3. Execution des commandes → 4. Built-ins

3. Execution des commandes → 5. Les redirections

3. Execution des commandes → 6. Les pipes

Structure pour la gestion des commandes : 

typedef enum e_token_type
{
	        WORD,            // word
	        PIPE,            // when find a |
	        REDIRECT_IN,     // when find <
	        REDIRECT_OUT,    // >
	        REDIRECT_APPEND, // >>
	        HEREDOC,         // <<
}							t_token_type;

typedef struct s_redir
{
	      t_token_type			  type;
	      char					        *file;
	      struct s_redir			*next;
}							t_redir;

typedef struct s_cmd
{
     char					      **args; // contient la commande et ses arguments entre les pipes
	    t_redir					   *infile; // representa les redirection d'entree (< file_name ou << OEF)
	    t_redir					   *outfile; // redirection de sortie ( > file, >> file)
	    bool					      builtin; 
	    struct s_cmd			*next;
}							t_cmd;

pourquoi faire des redirections d'entree ou de sorties en liste chaines : 
 - une commande peut avoir une ou plusieurs redirection ou aucune
     - entree simple: cat < file1 > file2 le node cmd a un node pour infile avec file1 et un node avec outfile avec file2
     - entree plus complexe : cat < file1 < file2 le node cmd avec la commande cat : infile va avoir deux nodes
     - sortie meme principe 

Pour stocker la variable d’environnement : 

typedef struct s_env_var {
char *key; // la valeur avant le =, exemple USER
char *value; // la valeur de l’environnement ici tmillot
struct s_env_var *next;
} t_env_var;

Pour stocker les deux : 

typedef struct s_shell {
    t_env_vat *env;            // Environnement complet
    t_command *commands;   // Liste chainée des commandes à exécuter
   d’autre ?
} t_shell;


