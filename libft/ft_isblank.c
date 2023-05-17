/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isblank.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:31:08 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/17 15:25:20 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// check if a char is blank according to the definition of bash
// https://www.man7.org/linux/man-pages/man1/bash.1.html
int	ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}
