/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:23:31 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/23 12:06:54 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../includes/libft/libft.h"
# include "../includes/get_next_line/get_next_line.h"
# include <sys/types.h>
# include <sys/wait.h>

# define LL_MAX			9223372036854775807ULL
# define ERR_NUM_EXIT	"minishell: exit: numeric argument required\n"
# define ERR_ARG_EXIT	"minishell: exit: too many arguments\n"
# define SUCCESS 		0
# define FAIL 			1
# define CODE_FAIL 		1
# define CODE_SUCCESS	0
# define NO_QUOTE		0
# define S_QUOTE		1
# define D_QUOTE		2

typedef enum e_token_type
{
	WORD,				// word
	PIPE,				// when find a |
	REDIRECT_IN,		// when find <
	REDIRECT_OUT,		// >
	REDIRECT_APPEND,	// >>
	HEREDOC,			// <<
}							t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	struct s_token			*next;
}							t_token;

typedef struct s_redir
{
	t_token_type			type;
	char					*file;
	struct s_redir			*next;
}							t_redir;

/* structure pour l'exécution */
typedef struct s_cmd
{
	char					**args;
	t_redir					*infile;
	t_redir					*outfile;
	pid_t					pid;
	bool					builtin;
	struct s_cmd			*next;
}							t_cmd;

/* une fois que je suis dans les forks : d'abord les redirections → les $
	→ le split sur les espaces → gestion des guillemets*/
typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_shell
{
	t_env					**env;
	t_cmd					**cmd;
	int						exit_status;
}							t_shell;

typedef struct t_parse_space
{
	char					**line;
}							t_parse_space;

typedef struct s_parse_pipe
{
	char					**line;
}							t_parse_pipe;

typedef struct s_parse_redir_input
{
	char					**line;
}							t_parse_redir_input;

typedef struct s_parse_redir_output
{
	char					**line;
}							t_parse_redir_output;

typedef struct s_parse_redir_append
{
	char					**line;
}							t_parse_redir_append;

typedef struct s_parse_redir_heredoc
{
	char					**line;
}							t_parse_redir_heredoc;

typedef struct s_parse
{
	char					*line;
	t_parse_space			*space;
	t_parse_pipe			*pipe;
	t_parse_redir_input		*redir_input;
	t_parse_redir_output	*redir_output;
	t_parse_redir_append	*redir_append;
	t_parse_redir_heredoc	*redir_heredoc;
}							t_parse;

typedef struct s_quotes
{
	int						index;
	char					*line;
	struct s_quotes			*next;
}							t_quotes;

typedef struct s_info
{
	int						space;
	int						pipe;
	int						redir_input;
	int						redir_output;
	int						redir_append;
	int						redir_heredoc;
}							t_info;

typedef struct s_parse_redir
{
	char					**line;
	struct s_parse_redir	*next;
}							t_parse_redir;

/* parsing */
t_cmd						*init_cmd(void);
t_parse_redir				*init_redir(void);
void						parse(char *line);
void						parse_pipe(t_parse *cmd, char *line);
char						**ft_divide_char(char *line, char sep);
char						**ft_divide_str(char *line, char *sep);
int							ft_strcmp_minishell(char *s1, char *s2);
void						parse_redir_input(t_parse *cmd, char *line);
void						fill_t_cmd(t_parse_redir *redir, t_cmd *cmd);
void						parse_redir_output(t_parse *cmd, char *line);
void						parse_redir_append(t_parse *cmd, char *line);
void						parse_redir_heredoc(t_parse *cmd, char *line);
void						parse_redir(t_parse_redir *redir, char **pipe);
int							parse_v2(char *line, t_env *env, int last_status);

/* quotes */
char						*skip_quotes(char *line, char quote);
char						*remove_quotes(char *line, t_quotes *quotes);
void						replace_quotes(t_parse *cmd, t_quotes *quotes);
int							check_quote_closed(char *line, int index, char quote);

/* split */
void						free_tab(char **tab, int y);
char						**ft_minishell_split_str(const char *s, char *sep);
char						**ft_minishell_split_char(const char *s, char sep);

/* cleaning */
void						clean_env(void);
void						clean_pipe(char **pipe);
void						clean_cmd(t_parse *cmd);
void						clean_split(char **split);
void						clean_quotes(t_quotes *quotes);
void						clean_redir(t_parse_redir *redir);

/* utils */
char						**ft_strdup_split(char **split);

/* Handle here doc, return name file */
char	*get_here_doc(char *str);


/* Here are the declarations for the functions used to manage execution */

/* built-in */
int							ft_pwd(void);
int							ft_echo(t_cmd *cmd);
int							ft_cd(t_env **env, t_cmd *cmd);
int							ft_env(t_env *env, t_cmd *cmd);
int							ft_unset(t_cmd *cmd, t_env **env);
int							ft_export(t_env **env, t_cmd *cmd);
int							ft_exit(t_cmd *cmd, t_env *env, int exit_status);

/* utils built-in */
t_env 						*copy_export(t_env *env);
t_env						*new_node_env(char *key, char *value);
int							name_var_valid(char *str);
int							name_var_valid(char *str);
int							is_built_in(char *str);

/* handle environnement */
t_env						*cpy_env(char **env);
char						*get_before_egal(char *str);
char						*get_after_egal(char *str);
int	    					count_tab_char(char **tab);

/* Handle expand var and trim quotes */
void    					expand_and_trim_cmd(t_cmd *cmd, t_env *env, int last_status);
void						handling_dollars(t_cmd *cmd, t_env *env, int last_status);
void						expand_arg(char **arg, t_env *env, int last_status, int *index);
int							check_expand_quote(int *quote, char c);
void    					trim_quotes(t_cmd *cmd);
void    					find_and_trim_quote(char **arg);
void						print_cmd_debug(t_cmd *cmd);

/* error message during executing */
void						error_message(char *str);
void						is_a_directory(char *str);
void						command_not_found(char *cmd);
void						permission_denied(char *file);
void						no_such_file_or_directory(char *cmd);

/* executing */
int							ft_exec(t_cmd *cmd, t_env *env, int exit_code);
int							is_special_built_in(char *cmd);
int							exec_builtin(t_cmd *cmd, t_env *env);

/* build env for execution */
char						**env_tab_char(t_env *env);

/* process */
int							ft_process(t_cmd *cmd, t_env *env, int *pipe_fd, int prev_fd);
void						ft_exit_child(int code_status, char *path_cmd, char **envp);

/* find command */
char						*find_cmd_path(t_env *env, t_cmd *cmd);

/* management of redirection for infile or outfile */
int							last_outfile(t_cmd *cmd);
int							last_infile(t_cmd *cmd);
int							redirect_management(t_cmd *cmd, int *pipe_fd, int prev_fd);

/* handle free execution */
void						free_t_cmd(t_cmd *cmd);
void						free_tab_char(char **tab);
void						free_t_redir(t_redir *list);
int							wait_and_free(int status, t_cmd *cmd);
void						free_path(char *path_cmd);
int							wait_children(int status, t_cmd *cmd);
void						free_env(t_env *env);

#endif