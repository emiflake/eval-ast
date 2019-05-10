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
#include <string.h>
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
		printf("???");
		return ;
	}
	if (node->type == E_BINOP)
	{
		printf("(");
		print_node(node->value.sub_node.lhs);
		printf(" ");
		printf("%c ", node->value.sub_node.op);
		print_node(node->value.sub_node.rhs);
		printf(")");
	}
	else if (node->type == E_VALUE)
	{
		printf("%d", node->value.num);
	}
}

t_ast_node *parse_stage_num(char **str, int *success);

t_ast_node *parse_stage_1(char **str, int *success)
{
	t_ast_node	*lhs;
	t_ast_node	*rhs;
	char		op;

	lhs = parse_stage_num(str, success);
	if (lhs == NULL)
	{
		*success = 0;
		return (NULL);
	}
	if (**str == '*' || **str == '/')
	{
		op = **str;
		(*str)++;
		rhs = parse_stage_1(str, success);
		return (mk_binop_node(lhs, op, rhs));
	}
	else
	{
		return (lhs);
	}
	*success = 0;
	return (NULL);
}

t_ast_node *parse_stage_0(char **str, int *success)
{
	t_ast_node	*lhs;
	t_ast_node	*rhs;
	char		op;

	lhs = parse_stage_1(str, success);
	if (lhs == NULL)
	{
		*success = 0;
		return (NULL);
	}
	if (**str == '+' || **str == '-')
	{
		op = **str;
		(*str)++;
		rhs = parse_stage_0(str, success);
		return (mk_binop_node(lhs, op, rhs));
	}
	else
	{
		return (lhs);
	}
	*success = 0;
	return (NULL);
}

t_ast_node *parse_stage_num(char **str, int *success)
{
	int			result;
	t_ast_node	*res;

	if (**str == '(')
	{
		(*str)++;
		res = parse_stage_0(str, success);
		(*str)++;
		return (res);
	}
	else if (strchr("0123456789", **str) != NULL && **str != '\0')
	{
		result = 0;
		while (strchr("0123456789", **str) != NULL && **str != '\0')
		{
			result = (result * 10) + (**str - '0');
			(*str)++;
		}
		res = mk_num_node(result);
		return (res);
	}
	else
	{
		*success = 0;
		return NULL;
	}
}

t_ast_node *parse_expr(char **str, /*out*/ int *success)
{
	t_ast_node *res;
	
	*success = 1;
	res = parse_stage_0(str, success);
	return (res);
}

int			do_op(int a, char op, int b)
{
	switch (op)
	{
		case '+': return (a + b);
		case '-': return (a - b);
		case '*': return (a * b);
		case '/': return (a / b);
		default: return (0);
	}
}

int			evaluate(t_ast_node *node)
{
	if (node->type == E_VALUE)
	{
		return (node->value.num);
	}
	else
	{
		t_ast_binop *b;
		b = &node->value.sub_node;
		return (do_op(evaluate(b->lhs), b->op, evaluate(b->rhs)));
	}
}

int			main(int argc, char **argv)
{
	int success;
	if (argc == 2)
	{
		t_ast_node *node = parse_expr(&argv[1], &success);
		print_node(node);
		if (success == 1)
		{
			printf("\nWill evaluate to: %d", evaluate(node));
		}
		else
		{
			printf("\nFailed to parse.");
		}
		
	}
	printf("\n");
	return (0);
}