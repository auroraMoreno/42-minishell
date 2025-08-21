/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:46:02 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/19 16:12:22 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *ft_init_cmd(char *cmd, t_built_in_type built_ins[]) // aqui pueden venir varios 
{
    t_cmd *cmd_data; 
    char **tokens; //modificar cuando lexer y parser
    int i;
    int j;
    if(!cmd)
    {
        cmd_data->cmd_name = NULL;
        return (cmd_data);
    }
    tokens = ft_split(cmd, ' ');
    
    cmd_data->cmd_name = ft_strdup(tokens[0]);

    i = 0;
    while(tokens[i])
        i++;
    if(i > 1)
    {
        cmd_data->args = (char **)malloc(sizeof(char *) * i);
        if(!cmd_data->args)
            return cmd_data;
        
        j = 1;
        while (j < i)
        {
            cmd_data->args[j - 1] = ft_strdup(tokens[j]);
            j++;
        }
        cmd_data->args[i - 1] = NULL;
    }    
    else
    {
        cmd_data->args = NULL;
    }
    
    cmd_data->flags = NULL;
    cmd_data->is_built_in = ft_check_built_in(cmd,built_ins);
    if(!cmd_data->is_built_in)
        cmd_data->cmd_path = find_route(cmd, getenv("PATH"));
    else 
        cmd_data->cmd_path = NULL;
    //check if built in:
    return (cmd_data);
}


// proabablemente lo quitaré cuando parser y lexer hechos 
t_list *ft_init_command_list(char *cmd_line, t_built_in_type built_ins[])
{
    // va a llegar un string de comandos:
    //ejemplo echo hola | cat fichero.txt
    // guardarlos en una lista para pasarselos al método ft_handle_exe 
    // y este metodo determine que flujo seguir 
    //cada t_list node es de tipo t_cmd y tiene que pasar por el método init_cmd 

    //esto habrá que repetirlo probablemente, porque puede haber n numero de comandos: 
    // primero hay que inicializar el t_cmd cmd
    t_list *cmd_list = NULL;
    t_list *new;
    t_cmd cmd; 
    //t_cmd cmd = ft_init_cmd(cmd, built_ins); // considerar modificar init_cmd para que reciba los parametros separados: cmd_name, flags y args
    char  **split_cmds;
    int i = 0;
    //una vez esto, crear un nuevo nodo t_list 
    split_cmds = ft_split(cmd_line, '|');
    if(!split_cmds)
        return (NULL);
    // añadirlo a t_list 
    while(split_cmds[i])
    {
        char *trm_cmd = ft_strtrim(split_cmds[i], "\t\n");
        if(!trm_cmd)
            return (NULL);
        cmd = ft_init_cmd(trm_cmd, built_ins);
        new = ft_lstnew((void *)ft_memdup(&cmd, sizeof(t_cmd)));
        if(!new)
            break;
        ft_lstadd_back(&cmd_list, new);

        free(trm_cmd);
        i++;
    }

    i = 0;
    while(split_cmds[i])
        free(split_cmds[i++]);
    free(split_cmds[i++]);
    
    return cmd_list;
    // return t_list
    
}