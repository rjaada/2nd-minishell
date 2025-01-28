/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:22 by rjaada            #+#    #+#             */
/*   Updated: 2025/01/28 12:26:26 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*get_quoted_content(t_lexer *lexer, char quote_type, int *pos)
{
	int		start;
	int		len;
	char	*content;
	int		escaped;

	start = *pos;
	len = 0;
	escaped = 0;
	while (*pos < lexer->len)
	{
		if (!escaped && lexer->input[*pos] == '\\' && *pos + 1 < lexer->len)
		{
			escaped = 1;
			(*pos)++;
			continue ;
		}
		if (!escaped && lexer->input[*pos] == quote_type)
			break ;
		escaped = 0;
		len++;
		(*pos)++;
	}
	if (*pos >= lexer->len)
		return (NULL);
	content = malloc(sizeof(char) * (len + 1));
	if (!content)
		return (NULL);
	escaped = 0;
	len = 0;
	while (start < *pos)
	{
		if (!escaped && lexer->input[start] == '\\')
		{
			escaped = 1;
			start++;
			continue ;
		}
		content[len++] = lexer->input[start++];
		escaped = 0;
	}
	content[len] = '\0';
	return (content);
}

t_token	*handle_quote(t_lexer *lexer, char quote_type)
{
	char	*word;
	char	*expanded;
	int		pos;

	lexer->pos++;
	pos = lexer->pos;
	word = get_quoted_content(lexer, quote_type, &pos);
	if (!word)
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		return (NULL);
	}
	lexer->pos = pos + 1;
	if (quote_type == '"')
	{
		expanded = expand_env_vars(word);
		free(word);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, word));
}

t_token	*handle_word(t_lexer *lexer)
{
	int		start;
	char	*word;
	int		len;
	char	*expanded;

	start = lexer->pos;
	while (lexer->pos < lexer->len && is_word_char(lexer->input[lexer->pos]))
		lexer->pos++;
	len = lexer->pos - start;
	word = ft_substr(lexer->input, start, len);
	if (!word)
		return (NULL);
	if (ft_strchr(word, '$'))
	{
		expanded = expand_env_vars(word);
		free(word);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, word));
}
