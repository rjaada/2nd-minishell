/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:29:05 by rjaada            #+#    #+#             */
/*   Updated: 2025/01/28 12:31:52 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int			g_exit_status;

static void	token_print_wrapper(t_token *token)
{
	ft_putstr_fd("Token: ", 1);
	if (token->type == TOKEN_WORD)
		ft_putstr_fd("WORD", 1);
	else if (token->type == TOKEN_PIPE)
		ft_putstr_fd("PIPE", 1);
	else if (token->type == TOKEN_REDIR_IN)
		ft_putstr_fd("REDIR_IN", 1);
	else if (token->type == TOKEN_REDIR_OUT)
		ft_putstr_fd("REDIR_OUT", 1);
	else if (token->type == TOKEN_HEREDOC)
		ft_putstr_fd("HEREDOC", 1);
	else if (token->type == TOKEN_APPEND)
		ft_putstr_fd("APPEND", 1);
	else if (token->type == TOKEN_EOF)
		ft_putstr_fd("EOF", 1);
	if (token->value)
	{
		ft_putstr_fd(" -> [", 1);
		ft_putstr_fd(token->value, 1);
		ft_putstr_fd("]", 1);
	}
	ft_putstr_fd("\n", 1);
}

static int	process_input(char *input)
{
	t_lexer	*lexer;
	t_token	*token;

	if (ft_strcmp(input, "exit") == 0)
		return (1);
	lexer = lexer_init(input);
	if (!lexer)
		return (0);
	while (1)
	{
		token = lexer_get_next_token(lexer);
		if (!token)
			break ;
		token_print_wrapper(token);
		if (token->type == TOKEN_EOF)
		{
			token_free(token);
			break ;
		}
		token_free(token);
	}
	lexer_free(lexer);
	return (0);
}

int	main(void)
{
	char	*input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	g_exit_status = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input && *input)
			add_history(input);
		if (process_input(input))
		{
			free(input);
			break ;
		}
		free(input);
	}
	return (g_exit_status);
}
