/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/03 20:16:13 by aumoreno         ###   ########.fr       */
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


int g_signal; 


typedef struct s_data // usar struct pipex de cesar 
{
	char *prompt;
	char *cmd_line;
	int exit_status; 
	char *pwd;
	t_list *env; // deberia ser ** ? 
	char built_ins[7];
    char **env_cpy;
	t_list *cmds;
	int shell_lvl;
	int cmd_nbr;
	//DE MOMENTO
	char **heredoc_content;
	int 	heredoc_fds[2];
}
t_data;

//add propiedad para redirecciones 
typedef struct s_cmd
{
	char			*cmd_name; // el nombre del comando 
    char			*cmd_path; //método build path 
    char			**args; // valores rollo nombre de variables
    char			*flags;
    int				is_built_in;
	char			**argv;
	char			*infile; 
	char			*outfile; 
	int				append; 
	int				heredoc;
	int				fd_in;
	int				fd_out;
	pid_t			id_process;
	int				redir_type; //REMOVE POR LA BUENA PROPIEDAD
	struct s_cmd	*next;
	
}	t_cmd;
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
    struct s_cmd *next;     // siguiente en el pipeline
} t_cmd;

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



//LEXER

void			parse_input(char *cmd);
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


typedef struct s_env
{
    char *key;
    char *value;

}t_env;

typedef struct s_data // usar struct pipex de cesar
{
    t_list *env;
    char **env_parsed;
}
t_data;

/*typedef struct s_cmd
{
    char *cmd_name; // el nombre del comando
    char **args; // valores rollo nombre de variables
    char **flags; //aqui serian rollo -n para echo y demas +
    int is_built_in;
}t_cmd;*/


/*executer*/
void ft_handle_exe(char *cmd, char *flags, t_built_in_type builtins[], t_data data);

/*built in functions*/
void ft_init_builtins(t_built_in_type builtins[]);
int ft_echo();
int ft_cd();
int ft_pwd();
int ft_export();
int ft_unset();
int ft_env();
int ft_exit();

/*utils*/
t_list 			*ft_process_env_values(char *key_val);
char 			*ft_find_equal_sign(char *str);
int 			ft_strcmp(const char *s1, const char *s2);
char			*find_route(char *instruction, char *path);
char			*get_route(char *cmd, char **envp);

/*freeing memory methods*/
void 			ft_free_env(t_list **env_list);
void			ft_free_env_node(void *content);
void 			ft_free_all(t_data *data);
void			ft_free_matrix(char **matrix);

/*error methods*/
void			ft_error_and_free(int error_code ,t_data *data);
int				ft_formatted_error(char *msg, char *cmd, t_data *data);

#endif
