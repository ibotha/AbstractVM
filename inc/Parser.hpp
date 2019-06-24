/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:25:45 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/21 17:55:43 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "OperandFactory.hpp"
#include "sstream"
#include "vector"
#include "Lexer.hpp"

class Parser;
typedef void (Parser::* operation_t)(Lexer &);

class Parser
{
private:
	static operation_t sOperations[];
	std::istream &m_Stream;
	std::stringstream m_SS;
	std::vector<IOperand const *> m_Stack;
	std::vector<Lexer> m_Instructions;
	bool m_Error;

public:
	Parser();
	Parser(std::istream &stream);
	~Parser();
	Parser(Parser const &rhs);
	Parser &operator=(Parser const &rhs);

	void Push(Lexer &l);
	void Pop(Lexer &l);
	void Print(Lexer &l);
	void Dump(Lexer &l);
	void Add(Lexer &l);
	void Sub(Lexer &l);
	void Div(Lexer &l);
	void Mul(Lexer &l);
	void Assert(Lexer &l);
	void Exit(Lexer &l);
	void None(Lexer &l);
	void Mod(Lexer &l);
	void Execute(Lexer &l);

	struct EmptyStack : public std::exception {
		const char *what() const throw();
	};

	struct OperatorStackSize : public std::exception {
		const char *what() const throw();
	};

	struct Assertion : public std::exception {
		const char *what() const throw();
	};

	void Run();
	void Execute();
};