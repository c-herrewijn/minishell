/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_exit.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:09 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/31 12:26:20 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exit with errno and strerror/perror?
void	b_exit(int exit_status)
{
	exit(exit_status);
}
