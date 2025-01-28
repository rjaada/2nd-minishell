/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:25:56 by rjaada            #+#    #+#             */
/*   Updated: 2025/01/28 13:17:37 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_create(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	token_free(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

t_token	*handle_operator(t_lexer *lexer)
{
	char	curr;
	char	next;

	curr = lexer->input[lexer->pos];
	if (lexer->pos + 1 < lexer->len)
		next = lexer->input[lexer->pos + 1];
	else
		next = 0;
	lexer->pos++;
	if (curr == '|')
		return (token_create(TOKEN_PIPE, ft_strdup("|")));
	if (curr == '<')
	{
		if (next == '<')
		{
			lexer->pos++;
			return (token_create(TOKEN_HEREDOC, ft_strdup("<<")));
		}
		return (token_create(TOKEN_REDIR_IN, ft_strdup("<")));
	}
	if (curr == '>')
	{
		if (next == '>')
		{
			lexer->pos++;
			return (token_create(TOKEN_APPEND, ft_strdup(">>")));
		}
		return (token_create(TOKEN_REDIR_OUT, ft_strdup(">")));
	}
	return (NULL);
}
