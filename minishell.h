/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 18:37:28 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <unistd.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include  <errno.h>
#include <stdbool.h>
# include <fcntl.h>

#define SUCCESS 0
#define ERROR -1
#define FORK_ERROR -2

extern int g_signal; 

typedef enum e_quote_type {
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef enum e_redir_type {
	R_IN,		// <
	R_OUT,		// >
	R_APPEND,	// >>
	R_HEREDOC// <<
}	t_redir_type;

typedef struct s_assign {
	char			*key;
	char			*value;
	struct s_assign	*next;
}	t_assign;

typedef struct s_redir {
	int				from_fd;          // fd origen que rediriges (por defecto 0 para < y <<, 1 para > y >>, o el IO_NUMBER si lo hubo)
	t_redir_type	redir_type;             // tipo de redirección
	char			*target;           // filename (>, >>, <) o delimitador (<<)
	bool			heredoc_quoted_delim;     // 1 si delimitador estaba entre comillas -> no expandir heredoc
	char			*heredoc_tmpfile;  // si guardas el heredoc en un tmpfile
	struct s_redir	*next;
} t_redir;

typedef struct s_cmd {
    char     **argv;        // argv[0] = ejecutable, resto args (ya con quote removal / expansiones)
    t_assign   *assignments;  // lista de "NAME=VALUE" previas al ejecutable
    t_redir  *redirs;       // lista de redirecciones (0..N)
    bool       is_builtin;   // opcional
	char			*infile; 
	char			*outfile; 
	int				fd_in;
	int				fd_out;
	pid_t			id_process;
    struct s_cmd *next;     // siguiente en el pipeline
} t_cmd;

typedef struct s_data
{
	char *prompt;
	char *cmd_line;
	int exit_status; 
	char *pwd;
	t_list **env; // TO-DO deberia ser ** ? 
	char *built_ins[7];
    char **env_cpy;
	t_cmd *cmd_list;
	int shell_lvl;
	int cmd_nbr;
	char **heredoc_content; //TO-DO: moverlo a la struct redir 
	int 	heredoc_fds[2];
}
t_data;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	IO_NUMBER,
	ASSIGNMENT_WORD,
}	t_token_type;


typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/*typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
	int				io_number;	// fd target por defecto (si se aplica)
	t_list			*assignments;	// lista de char* "NAME=VALUE" para este cmd
	int				infile_fd;	// -1 si sin open (si quieres)
	int				outfile_fd;	// -1 si sin open
	char			*heredoc_tmpfile;	// si guardas heredoc
	struct s_cmd *next;     // siguiente en el pipeline
}	t_cmd;*/

typedef struct s_builtin_type
{
    char *built_in_name;
    int (*foo)(); //considerar un union para distintos prototypes

}t_built_in_type;


typedef struct s_env
{
    char *key;
    char *value;

}t_env;


/*init functions*/
void			ft_init_data(t_data *data, char **env);
t_cmd 			*ft_init_cmd(char *cmd, t_built_in_type built_ins[]);
t_list			*ft_init_env(char *envp[]);
void 			ft_init_builtins(t_data *data);
char 			**ft_cpy_env(char **env);
int				ft_get_env_size(char **env);
void			ft_run_shell(t_data *data);


//LEXER

t_cmd			*parse_input(char *cmd);
void			print_tokens(t_token *token_list);

char			**input_to_tokens(char *cmd);
int				count_tokens(char *cmd);
char			**just_one_token(char *cmd_trimmed);
char			**tokens_split(char *cmd, int token_nbr, int *delimiters_pos);
char			*push_token(char *cmd, int start, int end);

int				find_delimiters(char *cmd, int token_nbr, int *delimiters_pos);
int				get_delimiter(int *i, int *start, char *cmd, int *nbr);
int				check_delimiter(int i, int start, char *cmd, int nbr);
int				check_array(int *delimiters_pos, int token_number);

int				is_space(char c);
int				is_quote(char c);
int				is_operator(char c);

void			check_quote(bool *in_quote, char *quote_chr, char to_check);
void			check_space(int *i, int *start, char *cmd, int *nbr);
void			check_operator(int *i, int *start, char *cmd, int *nbr);
void			check_no_quote(int *i, int *start, char *cmd, int *nbr);

t_token			*tokens_in_list(char	**tokens);
t_token_type	get_token_type(char	*token);
t_token			*new_token(char	*token, t_token_type token_type);
void			add_token(t_token **head, t_token *new);

//GRAMMAR

int	new_cmd(t_cmd **current_cmd);
int	craft_cmd(t_cmd *current_cmd, t_token **token_list);
int	content_in_cmd(t_cmd *current_cmd);
void	add_cmd(t_cmd **cmd_lst_start, t_cmd **cmd_lst_end, t_cmd *current_cmd);
t_cmd	*tokens_to_cmds(t_token *token_list);

int	argv_len(char **argv);
char	**push_to_argv(char **argv, char *arg);
int	add_word(t_cmd *current_cmd, t_token **token_list, bool *exec_seen);
int	set_assign(t_assign *asgn_wrd, char	*wrd);
int	add_asgn_wrd(t_cmd *current_cmd, t_token **token_list, bool *exec_seen);

int	is_redir(t_token *token_list);
int	add_io_num(t_cmd *current_cmd, t_token **token_list, int *pending_fd, bool *exec_seen);
int catalogue_redir(t_redir_type *redir_type, t_token_type token_type);
int	set_redir(t_redir *redir, t_token **token_list, int *pending_fd);
int	add_redir(t_cmd *current_cmd, t_token **token_list, int *pending_fd);

bool	token_is_quoted(char *token_value);
// t_quote_type type_of_quote(char *token_value);
char	*remove_quotes(char *str);
char	*copy_str(char *str);

void	print_argv(char **argv);
void	print_assgn(t_assign *assign);
void	print_redir_type(t_redir_type redir_type);
void	print_redir(t_redir *redirs);
void	print_cmds(t_cmd *cmds);


//UTILS
void	free_matrix(char **matrix);
void	free_token_list(t_token *token_list);
t_cmd	*free_cmds(t_cmd *cmd_list_start, t_cmd *current_cmd);
void	free_redirs(t_redir *redirs);
void	free_assignments(t_assign *assignments);



/*EXECUTER*/
void			ft_prepare_executer(t_cmd *cmd_list, t_data *data);
void			ft_executer(t_cmd *cmd_list, t_data *data);
int				ft_single_cmd(t_cmd *cmd, t_data *data);
int				ft_multiple_commands(t_cmd *cmd_list, t_data *data);

/*executer utils*/
void			ft_child_process(t_cmd *cmd, int fd_input, int fd_output, t_data *data);
pid_t			ft_create_fork(t_cmd *cmd, int fd_in, int fd_out, t_data *data);
void			ft_exec_cmd(t_cmd *cmd, t_data *data);
int				ft_return_status(int status);
int				ft_wait_children_process(t_cmd *cmd_list);


/*BUILT IN functions*/
int				ft_built_ins(t_cmd *cmd, t_data *data);
int				ft_check_built_in(char *cmd, char *built_ins[]);
int				ft_echo(t_cmd *cmd);
int				ft_cd(t_cmd *cmd, t_data *data);
int				ft_pwd(t_cmd *cmd, t_data *data);
int				ft_unset(t_cmd *cmd, t_data *data);
int 			ft_env(t_cmd *cmd, t_data *data);
int 			ft_exit(t_cmd *cmd, t_data *data);
int				ft_export(t_cmd *cmd, t_data *data);

/*export & other built ins' utils*/
int				ft_find_in_env_cpy(char **env, char *key);
int				ft_check_variables(char *var);
char			**ft_add_env_cpy(char **env_cpy, char *key, char *value);
void			ft_process_values(char *key_val, char **key,  char **val);
char			*ft_get_key(char *str);
char			**ft_sort_alpha(char **env);
void			ft_print_export(char **env, t_cmd *cmd);
char			*ft_cd_go_home(char **env_cpy, char *path);
int				ft_cd_errors(int err_number, t_data *data); //TO-DO formatear el mensaje de error que sea mas parecido a bash
int				ft_check_n_flag(char *flags);
long			ft_atoi_exit_code(char *str_code);
int				ft_remove_element(char **env_cpy, char *var_name);

/*signals*/
void			ft_handle_sigint(int sig);

/*REDIRECTS/HEREDOC*/
int				ft_heredoc(int from_token, char *delimitter, t_data *data);
int				ft_heredoc_write_content(int from_token, char *delimitter, t_data *data);
int				ft_heredoc_read_more_content(t_data *data);

/*heredoc utils*/
char			*ft_read_content_heredoc(int fd);
ssize_t			ft_read_bytes(int fd, char **buffer, char **content, int buffer_size);
int				ft_update_content(char *content, t_data *data);
void			ft_remove_heredoc_lines(int from, t_data *data);

/*utils*/
t_list 			*ft_process_env_values(char *key_val);
char 			*ft_find_equal_sign(char *str);
int 			ft_strcmp(const char *s1, const char *s2);
char			*find_route(char *instruction, char *path);
char			*get_route(char *cmd, char **envp, t_data *data);



/*freeing memory methods*/
void 			ft_free_env(t_list **env_list);
void			ft_free_env_node(void *content);
void			ft_free_all(t_data *data);
void			ft_free_matrix(char **matrix);

/*error methods*/
void 			ft_error_and_free(char *msg, int error_code, t_data *data);
int				ft_formatted_error(char *msg, char *cmd, t_data *data);

#endif
