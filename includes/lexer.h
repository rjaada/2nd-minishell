/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:39:48 by rjaada            #+#    #+#             */
/*   Updated: 2025/01/28 12:33:09 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	char			*input;
	int				pos;
	int				len;
	t_token			*curr_token;
}					t_lexer;

/* Core lexer functions */
t_lexer				*lexer_init(char *input);
void				lexer_free(t_lexer *lexer);
t_token				*lexer_get_next_token(t_lexer *lexer);
void				lexer_skip_spaces(t_lexer *lexer);

/* Token handling */
t_token				*token_create(t_token_type type, char *value);
void				token_free(t_token *token);
t_token				*handle_word(t_lexer *lexer);
t_token				*handle_operator(t_lexer *lexer);
t_token				*handle_quote(t_lexer *lexer, char quote_type);

/* Utils */
int					is_operator(char c);
int					is_word_char(char c);
char				*expand_env_vars(char *str);

#endif