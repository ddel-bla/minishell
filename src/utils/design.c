/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:10:52 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:10:53 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#define RE	"\033[0m"
#define YE	"\033[1;33m"
#define WH	"\033[1;37m"
#define CY	"\033[1;36m"
#define MA	"\033[1;35m"
#define PI	"\033[1;38;2;255;209;220m"
#define RED	"\033[1;31m"

/*
 * Prints a cute header.
 */
void	print_header(void)
{
	printf("\n");
	printf("%s\t\t      .--.    \n", WH);
	printf("\t\t     |o_o |%s                   _        _      _", YE);
	printf("          _  _\n");
	printf("\t\t    %s |%s:_/%s |%s           ", WH, YE, WH, YE);
	printf(" _ __  (_) _ _  (_) ___| |_   ___ | || | \n");
	printf("%s\t\t    //   \\ \\          %s| '  \\ |", WH, CY);
	printf(" || ' \\ | |(_-<| ' \\ / -_)| || |\n");
	printf("%s\t\t   (|     | )         %s|_|_|_||", WH, MA);
	printf("_||_||_||_|/__/|_||_|\\___||_||_|\n");
	printf("%s\t\t  /'\\_   _/`\\       \n", YE);
	printf("\t\t  \\___)%s=%s(___/\t \t   %s", RE, YE, WH);
	printf("   Welcome to our mini shell. \n");
	printf("\t\t                                %s@ddel-bla%s", CY, WH);
	printf(" & %s@claferna%s\n", PI, RE);
	printf("%s", RE);
}

/*
 * Prints a sad header.
 */
void	print_header_nc(void)
{
	printf("\n");
	printf("\t\t      .--.    \n");
	printf("\t\t     |o_o |                   _        _      _");
	printf("          _  _\n");
	printf("\t\t     |:_/ |           ");
	printf(" _ __  (_) _ _  (_) ___| |_   ___ | || | \n");
	printf("\t\t    //   \\ \\          | '  \\ |");
	printf(" || ' \\ | |(_-<| ' \\ / -_)| || |\n");
	printf("\t\t   (|     | )         |_|_|_||");
	printf("_||_||_||_|/__/|_||_|\\___||_||_|\n");
	printf("\t\t  /'\\_   _/`\\       \n");
	printf("\t\t  \\___)=(___/\t \t   ");
	printf("   Welcome to our mini shell. \n");
	printf("\t\t                                @ddel-bla");
	printf(" & @claferna\n");
}

/*
 * Selects the appropiatte prompt.
 */
char	*select_prompt(int is_colored)
{
	if (is_colored == 2)
		return (COLORED_PROMPT);
	return (PROMPT);
}

/*
 * Prints a format error message in stderr.
 */
void	print_error(char *str)
{
	ft_putendl_fd(str, 2);
}
