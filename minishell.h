/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/19 16:58:12 by aumoreno         ###   ########.fr       */
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

//#include "./pipex/pipex_bonus.h"


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

typedef struct s_data // usar struct pipex de cesar 
{
    t_list *env;
    
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

