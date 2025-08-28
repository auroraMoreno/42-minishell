/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/28 18:59:40 by aumoreno         ###   ########.fr       */
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
	//TO-DO: add shell-level
	int cmd_nbr;
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
	struct s_cmd	*next;
	
}	t_cmd;

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


typedef struct s_env
{
    char *key;
    char *value;

}t_env;

// to remove 
typedef struct s_builtin_type
{
    char *built_in_name;
    int (*foo)(); //considerar un union para distintos prototypes 
    
}t_built_in_type;

/*init functions*/
void			ft_init_data(t_data *data, char **env);
t_cmd 			*ft_init_cmd(char *cmd, t_built_in_type built_ins[]);
t_list			*ft_init_env(char *envp[]);
void 			ft_init_builtins(t_data *data);
char 			**ft_cpy_env(char **env);
int				ft_get_env_size(char **env);
void			ft_run_shell(t_data *data);


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

void			print_list(t_token *token_list);


/*REDIRECTS/HEREDOC*/


//UTILS
void			free_matrix(char **matrix);

/*EXECUTER*/
void ft_prepare_executer(t_list *cmd_data, t_data *data);
void ft_executer(t_list *cmd_list, t_data *data);
int ft_single_cmd(t_cmd *cmd, int fd, t_data *data);
int ft_multiple_commands(t_list *cmd_list, t_data *data);

/*executer utils*/
void ft_child_process(t_cmd *cmd, int fd_input, int fd_output, t_data *data);
pid_t ft_create_fork(t_cmd *cmd, int fd_in, int fd_out, t_data *data);
void ft_exec_cmd(t_cmd *cmd, t_data *data);
int ft_return_status(t_data *data, int status);
int ft_wait_children_process(t_list *cmd, t_data *data);


/*BUILT IN functions*/
int ft_built_ins(t_cmd *cmd, t_data *data);
int ft_check_built_in(char *cmd, char built_ins[]);
int ft_echo(t_cmd *cmd, t_data *data);
int ft_cd(t_cmd *cmd, t_data *data);
int ft_pwd(t_cmd *cmd, t_data *data);
int ft_unset(t_cmd *cmd, t_data *data);
int ft_env(t_cmd *cmd, t_data *data);
int ft_exit(t_cmd *cmd, t_data *data);
int ft_export(t_cmd *cmd, t_data *data);


/*export utils*/
int ft_find_in_env_cpy(char **env, char *key);
int ft_check_variables(char *var);
char **ft_add_env_cpy(char **env_cpy, char *key, char *value);
void ft_process_values(char *key_val, char **key,  char **val);
char *ft_get_key(char *str);
char **ft_sort_alpha(char **env);
void ft_print_export(char **env, t_cmd *cmd);


/*signals*/
void ft_handle_sigint(int sig);


/*redirection functions*/
void ft_handle_redir(t_cmd *cmd);


/*utils*/
t_list 			*ft_process_env_values(char *key_val);
char 			*ft_find_equal_sign(char *str);
int 			ft_strcmp(const char *s1, const char *s2);
char			*find_route(char *instruction, char *path);
char			*get_route(char *cmd, char **envp);
void			free_matrix(char **matrix);


/*freeing memory methods*/
void 			ft_free_env(t_list **env_list);
void			ft_free_env_node(void *content);

/*error methods*/
void 			ft_error(char *str);
int				ft_formatted_error(char *msg, char *cmd, t_data *data);

#endif

