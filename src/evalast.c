/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   evalast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 12:34:12 by nmartins       #+#    #+#                */
/*   Updated: 2019/05/09 12:59:00 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

t_ast_node	*mk_binop_node(t_ast_node *lhs, char op, t_ast_node *rhs)
{
	t_ast_node *node;

	node = (t_ast_node*)malloc(sizeof(t_ast_node));
	node->type = E_BINOP;
	node->value.sub_node.lhs = lhs;
	node->value.sub_node.op = op;
	node->value.sub_node.rhs = rhs;
	return (node);
}

t_ast_node	*mk_num_node(int num)
{
	t_ast_node *node;

	node = (t_ast_node*)malloc(sizeof(t_ast_node));
	node->type = E_VALUE;
	node->value.num = num;
	return (node);
}

void	print_node(t_ast_node *node)
{
	if (node == NULL)
	{
		printf("<null>");
		return ;
	}
	if (node->type == E_BINOP)
	{
		printf("(");
		printf("%c ", node->value.sub_node.op);
		print_node(node->value.sub_node.lhs);
		printf(" ");
		print_node(node->value.sub_node.rhs);
		printf(")");
	}
	else if (node->type == E_VALUE)
	{
		printf("%d", node->value.num);
	}
}

t_ast_node *parse_expr(char *str)
{
	(void)str;
	return (NULL);
}

int			main(void)
{
	t_ast_node *node = parse_expr("2 + 3");
	print_node(node);
	printf("\n");
	return (0);
}