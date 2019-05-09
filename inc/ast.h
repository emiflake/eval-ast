/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 12:38:11 by nmartins       #+#    #+#                */
/*   Updated: 2019/05/09 12:44:40 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct	s_ast_binop
{
	struct s_ast_node	*lhs;
	char 				op;
	struct s_ast_node	*rhs;
}				t_ast_binop;

typedef int		t_num_lit;

typedef struct	s_ast_node
{
	enum
	{
		E_VALUE,
		E_BINOP
	}	type;
	union {
		t_num_lit num;
		t_ast_binop sub_node;
	}	value;
}				t_ast_node;

#endif