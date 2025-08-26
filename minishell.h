/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 18:33:20 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include  <errno.h>
#include <stdbool.h>

typedef enum e_redir_kind {
    R_IN,       // <
    R_OUT,      // >
    R_APPEND,   // >>
    R_HEREDOC   // <<
} t_redir_kind;

typedef struct s_redir {
    int           from_fd;          // fd origen que rediriges (por defecto 0 para < y <<, 1 para > y >>, o el IO_NUMBER si lo hubo)
    t_redir_kind  kind;             // tipo de redirección
    char         *target;           // filename (>, >>, <) o delimitador (<<)
    int           quoted_delim;     // 1 si delimitador estaba entre comillas -> no expandir heredoc
    char         *heredoc_tmpfile;  // si guardas el heredoc en un tmpfile
    struct s_redir *next;
} t_redir;

typedef struct s_cmd {
    char     **argv;        // argv[0] = ejecutable, resto args (ya con quote removal / expansiones)
    t_list   *assignments;  // lista de "NAME=VALUE" previas al ejecutable
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
t_list *ft_init_env(char *envp[]);
t_list *ft_process_env_values(char *key_val);
char *ft_find_equal_sign(char *str);


/*freeing memory methods*/
void ft_free_env(t_list **env_list);
void    ft_free_env_node(void *content);

/*error methods*/
void ft_error(char *str);

#endif

