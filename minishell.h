/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/19 17:48:56 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <linux/limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> 
#include  <errno.h>
#include <stdbool.h>
# include <fcntl.h>

#define ERROR 0
#define SUCCESS 1

// variable global
t_data *g_data; //malloc?

//define un typedef status 

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	ENV_VAR,
	ASSIGNMENT_WORD,
	DELIMETER
}	t_token_type;


typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token token; 
	char *file;
	struct s_redir *next;
	
}t_redir;

//add propiedad para redirecciones 
typedef struct s_cmd
{
	char			*cmd_name; // el nombre del comando 
    char			*cmd_path; //método build path 
    char			**args; // valores rollo nombre de variables
    char			*flags;
    int				is_built_in;
	char			**argv; // remove 
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	t_redir			*redir;
	struct s_cmd	*next;
	
}	t_cmd;


typedef struct s_env
{
    char *key;
    char *value;

}t_env;

// global
typedef struct s_data // usar struct pipex de cesar 
{
	char *prompt;
	char *cmd_line;
	int exit_status; 
	char pwd[PATH_MAX];
	t_list *env;
	char built_ins[7];
    char **env_parsed;
	t_cmd *cmds;
	//TO-DO: add shell-level
	//int cmd_num_args;
}
t_data;

typedef struct s_pipe
{
	int		here_doc;
	char	*delimiter;
	int		heredoc_pipe_fds[2]; // de momento no
    
	int		cmd_nbr; //init man
	char	**cmds; // son los comandos sueltos, ls y tal EXECVE init man 
	char	**cmd_routes; //las rutas EXECVE init man
	char	*filein; // create method init man (a lo mejor no hace falta init man)
	char	*fileout; //create method init man
	char	**env; // usar la de dataa  init man
	int		current_pipe_fds[2]; //para el metodo pipe (init sol)
	int		previous_pipe_fd; // init solo
	pid_t	cmd_id; // init auto 
}	t_pipe;


//#include "./pipex/pipex_bonus.h"

// to remove 
typedef struct s_builtin_type
{
    char *built_in_name;
    int (*foo)(); //considerar un union para distintos prototypes 
    
}t_built_in_type;


//PARSER

void			parse_input(char *cmd);

char			**input_to_tokens(char *cmd);
int				count_tokens(char *cmd);
char			**just_one_token(char *cmd_trimmed);
char			**tokens_split(char *cmd, int token_nbr, int *delimiters_pos);
char			*push_token(char *cmd, int start, int end);

int				find_delimiters(char *cmd, int token_nbr, int *delimiters_pos);
int				get_delimiter(int *i, int *start, char *cmd, int *nbr);
int				check_delimiter(int *i, int *start, char *cmd, int *nbr);
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
void			print_list(t_token *token_list);


//UTILS
void	free_matrix(char **matrix);



//PARSER

void			parse_input(char *cmd);

char			**input_to_tokens(char *cmd);
int				count_tokens(char *cmd);
char			**just_one_token(char *cmd_trimmed);
char			**tokens_split(char *cmd, int token_nbr, int *delimiters_pos);
char			*push_token(char *cmd, int start, int end);

int				find_delimiters(char *cmd, int token_nbr, int *delimiters_pos);
int				get_delimiter(int *i, int *start, char *cmd, int *nbr);
int				check_delimiter(int *i, int *start, char *cmd, int *nbr);
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
void			print_list(t_token *token_list);


//UTILS
void			free_matrix(char **matrix);

/*EXECUTER*/
void 			ft_executer(t_cmd *cmd);
void 			ft_execute_cmds(t_cmd *cmd, int fd_input, t_list *env);
void 			ft_single_cmd(t_cmd *cmd, int fd, t_list *env);
void 			ft_child_process(t_cmd *cmd, int fd_input, int fd_output);


/*built in functions*/
void			ft_built_ins(t_cmd *cmd, t_env *env);
int 			ft_echo(char *str, char *flags);
int 			ft_cd(char *path, t_list *env);
int				ft_pwd();
int				ft_export(char *var_name[], t_data data);
int				ft_unset(char *var_names[], t_data data);
int				ft_env(t_data data);
int				ft_exit(int status);

/*init functions*/
void 			ft_init_data(char **env);
t_cmd 			*ft_init_cmd(char *cmd, t_built_in_type built_ins[]);
t_list			*ft_init_env(char *envp[]);

/*pipe functions*/
void			ft_init_pipe(t_pipe *piped, t_cmd cmd_data, t_data data);
void			pipex(t_pipe *piped);


/*utils*/
t_list 			*ft_process_env_values(char *key_val);
char 			*ft_find_equal_sign(char *str);
int 			ft_strcmp(const char *s1, const char *s2);
char			*find_route(char *instruction, char *path);
void			free_matrix(char **matrix);


/*freeing memory methods*/
void 			ft_free_env(t_list **env_list);
void			ft_free_env_node(void *content);

/*error methods*/
void 			ft_error(char *str);

#endif

