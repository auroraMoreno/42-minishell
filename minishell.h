/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/31 18:48:52 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h> 
#include  <errno.h>
#include <stdbool.h>


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



/*executer*/
void ft_handle_exe(char *cmd, char *flags, t_built_in_type builtins[], char *env[]);

/*built in functions*/
void ft_init_builtins(t_built_in_type builtins[]);
int ft_echo();
int ft_cd();
int ft_pwd();
int ft_export();
int ft_unset();
int ft_env();
int ft_exit();

#endif

