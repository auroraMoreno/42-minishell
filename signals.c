/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:17:00 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 19:44:36 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0; //TO DO: cambiar l

void ft_handle_sigint(int sig)
{
	if(sig == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        g_signal = SIGINT + 128; 
    }
}
