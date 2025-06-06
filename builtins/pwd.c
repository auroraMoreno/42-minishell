/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/06 15:28:22 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_pwd()
{
    char cwd[PATH_MAX];

    if(!getcwd(cwd, sizeof(cwd)))
        ft_error("Unable to get current working directory");

    printf("%s\n", cwd);
    
    return (0);
}