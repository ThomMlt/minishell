/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:23:31 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/11 11:52:54 by tmillot          ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>

# define LL_MAX			9223372036854775807ULL
# define ERR_NUM_EXIT	"minishell: exit: numeric argument required\n"
# define ERR_ARG_EXIT	"minishell: exit: too many arguments\n"
# define ERR_NO_ARG		"error, don't entry argument"
# define ERR_PIPE		"minishell: syntax error near unexpected token '|'\n"
# define ERR_QUOTE		"minishell: syntax error: unexpected end of quote\n"
# define ERR_REDIR		"minishell: syntax error near unexpected token '>'\n"
# define ERR_NO_FILE	"minishell: syntax error near unexpected token 'newline'\n"
# define SUCCESS 		0
# define FAIL 			1
# define CODE_FAIL 		1
# define CODE_SUCCESS	0
# define NO_QUOTE		0
# define S_QUOTE		1
# define D_QUOTE		2

extern volatile bool	g_signal;

typedef enum e_token_type
{
	WORD,				// word
	PIPE,				// when find a |
	REDIRECT_IN,		// when find <
	REDIRECT_OUT,		// >
	REDIRECT_APPEND,	// >>
	HEREDOC,			// <<
}							t_token_type;

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
	struct s_cmd			*prev;
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

typedef struct s_parse_redir
{
	char					**line;
	struct s_parse_redir	*next;
}							t_parse_redir;

/* parsing */
int							ft_split_len(char **split);
int							parse(char *line, t_cmd	*cmd);
int							len_list(t_parse_redir *redir);
char						**ft_divide_char(char *line, char sep);
char						**ft_divide_str(char *line, char *sep);
int							ft_strcmp_minishell(char *s1, char *s2);
void						add_split(t_cmd *current_cmd, char **split);
int							fill_t_cmd(t_parse_redir *redir, t_cmd *cmd);
void						parse_redir(t_parse_redir *redir, char **pipe);
int							add_redir(t_cmd *current_cmd, char *file,
								t_token_type type);
void						tab_to_redir_char(t_parse_redir *redir,
								char **pipe, char sep);
void						tab_to_redir_str(t_parse_redir *redir,
								char **pipe, char *sep);

/* checking */
int							check_quotes(char *line);
int							is_only_spaces(char *str);
int							check_if_valid_redir(char *line);
int							check_if_valid_pipe(char *line, char sep);
int							check_quote_closed(char *line,
								int index, char quote);

/* list init */
t_cmd						*init_cmd(void);
t_parse_redir				*init_redir(void);
t_redir						*init_cmd_redir(void);

/* quotes */
char						*skip_quotes(char *line, char quote);

/* cleaning */
void						clean_t_cmd(t_cmd *cmd);
void						clean_pipe(char **pipe);
void						clean_split(char **split);
void						clean_redir(t_parse_redir *redir);

/* utils */
char						**ft_strdup_split(char **tab);
char						**ft_strndup_split(char **tab, int i);

/* Handle here doc, return name file */
char						*get_here_doc(char *str);

/* Here are the declarations for the functions used to manage execution */

/* built-in */
int							ft_pwd(void);
int							ft_echo(t_cmd *cmd);
int							ft_cd(t_env **env, t_cmd *cmd);
int							ft_env(t_env **env, t_cmd *cmd);
int							ft_unset(t_cmd *cmd, t_env **env);
int							ft_export(t_env **env, t_cmd *cmd);
int							ft_exit(t_cmd *cmd, t_env **env, int exit_status);

/* utils built-in */
int							is_built_in(char *str);
t_env						*copy_export(t_env *env);
int							name_var_valid(char *str);
int							name_var_valid(char *str);
t_env						*new_node_env(char *key, char *value);

/* handle environnement */
t_env						*cpy_env(char **env);
char						*get_after_egal(char *str);
int							count_tab_char(char **tab);
char						*get_before_egal(char *str);

/* Handle expand var and trim quotes */
void						trim_quotes(t_cmd *cmd);
void						print_cmd_debug(t_cmd *cmd);
void						find_and_trim_quote(char **arg);
int							check_expand_quote(int *quote, char c);
void						handling_dollars(t_cmd *cmd, t_env **env,
								int last_status);
int							expand_and_trim_cmd(t_cmd *cmd, t_env **env,
								int last_status);
void						expand_arg(char **arg, t_env **env,
								int last_status, int *index);
int							sep_var_name(char c);
void						split_first_args(t_cmd *cmd);

/* error message during executing */
void						error_message(char *str);
void						is_a_directory(char *str);
void						command_not_found(char *cmd);
void						permission_denied(char *file);
void						no_such_file_or_directory(char *cmd);

/* executing */
int							is_special_built_in(char *cmd);
int							exec_builtin(t_cmd *cmd, t_env **env);
int							ft_exec(t_cmd *cmd, t_env **env, int exit_code);

/* build env for execution */
char						**env_tab_char(t_env **env);

/* process */
void						ft_exit_child(int code_status, char *path_cmd,
								char **envp);
int							ft_process(t_cmd *cmd, t_env **env, int *pipe_fd,
								int prev_fd);

/* find command */
char						*find_cmd_path(t_env **env, t_cmd *cmd);

/* management of redirection for infile or outfile */
int							last_infile(t_cmd *cmd);
int							last_outfile(t_cmd *cmd);
int							redirect_management(t_cmd *cmd, int *pipe_fd,
								int prev_fd);

/* handle free execution */
void						free_env(t_env **env);
void						setup_signal(int sig);
void						free_t_cmd(t_cmd *cmd);
void						free_path(char *path_cmd);
void						free_tab_char(char **tab);
void						setup_signal_heredoc(void);
void						free_t_redir(t_redir *list);
void						free_t_cmd_nowhere(t_cmd *cmd);
int							wait_and_free(int status, t_cmd *cmd);
int							wait_children(int status, t_cmd *cmd);
void						safe_free_exec(t_cmd *cmd, char **envp, char *path);
void						print_cmd_list(t_cmd *cmd);

#endif