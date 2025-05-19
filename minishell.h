/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:37 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/19 20:10:43 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <linux/limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h> 
#include  <errno.h>

typedef struct s_builtin_type
{
    char *built_in_name;
    int (*foo)(); //considerar un union para distintos prototypes 
    
}t_built_in_type;

/*executer*/
void ft_handle_exe(char *cmd, char *flags, t_built_in_type builtins[]);

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

