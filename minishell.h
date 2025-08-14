/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/14 10:06:57 by aumoreno         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
	
}	t_cmd;

//#include "./pipex/pipex_bonus.h"


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
void	free_matrix(char **matrix);

typedef struct s_env
{
    char *key;
    char *value;

}t_env;

typedef struct s_data // usar struct pipex de cesar 
{
    t_list *env;
    int cmd_num_args;
    char **env_parsed;
}
t_data;

typedef struct s_cmd
{
    char *cmd_name; // el nombre del comando 
    char *cmd_path; //método build path 
    char **args; // valores rollo nombre de variables
    char **flags; //aqui serian rollo -n para echo y demas +
    int is_built_in;
}t_cmd;

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

/*executer*/
void ft_handle_exe(t_cmd cmd_data, t_built_in_type builtins[], t_data data);

/*built in functions*/
void ft_init_builtins(t_built_in_type builtins[]);
int ft_echo();
int ft_cd();
int ft_pwd();
int ft_export();
int ft_unset();
int ft_env();
int ft_exit();

/*init functions*/
t_cmd ft_init_cmd(char *cmd, t_built_in_type built_ins[]);

/*pipe functions*/
void ft_init_pipe(t_pipe *piped, t_cmd cmd_data, t_data data);
void	pipex(t_pipe *piped);


/*utils*/
t_list *ft_init_env(char *envp[]);
t_list *ft_process_env_values(char *key_val);
char *ft_find_equal_sign(char *str);
int ft_strcmp(const char *s1, const char *s2);
char	*find_route(char *instruction, char *path);
void	free_matrix(char **matrix);


/*freeing memory methods*/
void ft_free_env(t_list **env_list);
void    ft_free_env_node(void *content);

/*error methods*/
void ft_error(char *str);

#endif

