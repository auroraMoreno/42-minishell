/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:01:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/05 12:11:15 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    recibe lo que hay que escribir 
        // si !str => \n 
    si tiene flags => 
        //comprobar que la flag es -n 
            si no es -n => print lo que viene 
            si es -n => printf sin \n 
                si viene con -n pero !str , no pinta,¡mos nada
            si no hay flags => printf con \n 
        
*/
/*
PROBLEMA CON ECHO si le viene NULL si coge que no -n pero si viene "" entonces no lo coge 

*/
int ft_echo(char *str, char *flags)
{
    if(flags) // comprobar que -n? si no es un flag que echo admite, bash lo pinta igual 
    {
        // con -n
        if(str)
            // TO-DO: ver como gestiona esto los numeros, habrá que hacer itoa y decimales y con /
            printf("%s", str);
    }
    else 
    {
        // sin -n
        if(!str)
            printf("\n");
        else
            printf("%s\n",str);
    }
    
    return (0); // no returning values
}
