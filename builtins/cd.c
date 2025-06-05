/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:02:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/04 13:55:22 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(char *path)
{
    (void)path;
    //printf("Este es el built in cd\n");

    if(chdir("kjdfhgjkjfd") < 0)
        ft_cd_errors(); //return -1 on error
        
    return (0);
}