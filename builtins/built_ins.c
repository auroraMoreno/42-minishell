/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:09:08 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/19 09:35:09 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_init_builtins(t_built_in_type builtins[])
{
    //echo
    builtins[0].built_in_name = "echo";
    builtins[0].foo = ft_echo; 
    
    //cd
    builtins[1].built_in_name = "cd";
    builtins[1].foo = ft_cd;
    
    //pwd
    builtins[2].built_in_name = "pwd";
    builtins[2].foo = ft_pwd;
    
    //export
    builtins[3].built_in_name = "export";
    builtins[3].foo = ft_export;
    
    //unset
    builtins[4].built_in_name = "unset";
    builtins[4].foo = ft_unset;

    //env
    builtins[5].built_in_name = "env";
    builtins[5].foo = ft_env;
    
    //exit
    builtins[6].built_in_name = "exit";
    builtins[6].foo = ft_exit; 
    
}