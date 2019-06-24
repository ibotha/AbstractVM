/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:39:52 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/24 11:06:37 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <iostream>

operation_t Parser::sOperations[] = {
	&Parser::None,
	&Parser::Push,
	&Parser::Pop,
	&Parser::Dump,
	&Parser::Assert,
	&Parser::Add,
	&Parser::Sub,
	&Parser::Mul,
	&Parser::Div,
	&Parser::Mod,
	&Parser::Print,
	&Parser::Exit,
	&Parser::Execute
};
Parser::Parser()
	: m_Stream(std::cin)
{
}

Parser::Parser(std::istream &stream)
	: m_Stream(stream)
{
}

Parser::~Parser()
{
	for (auto a : m_Stack)
	{
		delete a;
	}
}

Parser::Parser(Parser const &rhs)
	: m_Stream(rhs.m_Stream)
{
}

Parser &Parser::operator=(Parser const &rhs)
{
	if (this != &rhs)
	{
		*this = rhs;
	}
	return (*this);
}

void Parser::Push(Lexer &l)
{
	m_Stack.push_back(l.getValue());
}

void Parser::Pop(Lexer &l)
{
	(void)l;
	if (m_Stack.size() < 1)
		throw EmptyStack();
	delete m_Stack.back();
	m_Stack.pop_back();
}

void Parser::Print(Lexer &l)
{
	(void)l;
	if (m_Stack.size() < 1)
		throw EmptyStack();
	std::cout << m_Stack.back()->toString() << std::endl;
}

void Parser::Dump(Lexer &l)
{
	(void)l;
	for (int i = m_Stack.size() - 1; i >= 0; i--)
	{
		std::cout << m_Stack[i]->toString() << std::endl;
	}
}

void Parser::Add(Lexer &l)
{
	(void)l;
	IOperand const *v1;
	IOperand const *v2;

	if (m_Stack.size() < 2)
		throw OperatorStackSize();
	v1 = m_Stack.back();
	m_Stack.pop_back();
	v2 = m_Stack.back();
	m_Stack.pop_back();
	m_Stack.push_back(*v1 + *v2);
	delete v1;
	delete v2;
}

void Parser::Sub(Lexer &l)
{
	(void)l;
	IOperand const *v1;
	IOperand const *v2;

	if (m_Stack.size() < 2)
		throw OperatorStackSize();
	v1 = m_Stack.back();
	m_Stack.pop_back();
	v2 = m_Stack.back();
	m_Stack.pop_back();
	m_Stack.push_back(*v1 - *v2);
	delete v1;
	delete v2;
}

void Parser::Div(Lexer &l)
{
	(void)l;
	IOperand const *v1;
	IOperand const *v2;

	if (m_Stack.size() < 2)
		throw OperatorStackSize();
	v1 = m_Stack.back();
	m_Stack.pop_back();
	v2 = m_Stack.back();
	m_Stack.pop_back();
	m_Stack.push_back(*v1 / *v2);
	delete v1;
	delete v2;
}

void Parser::Mul(Lexer &l)
{
	(void)l;
	IOperand const *v1;
	IOperand const *v2;

	if (m_Stack.size() < 2)
		throw OperatorStackSize();
	v1 = m_Stack.back();
	m_Stack.pop_back();
	v2 = m_Stack.back();
	m_Stack.pop_back();
	m_Stack.push_back(*v1 * *v2);
	delete v1;
	delete v2;
}

void Parser::Assert(Lexer &l)
{
	(void)l;
	if (m_Stack.size() < 1)
		throw EmptyStack();
	IOperand const * val = l.getValue();
	bool out = *val == *m_Stack.back();
	delete val;
	if (!out)
		throw Assertion();
}

void Parser::Exit(Lexer &l)
{
	(void)l;
}

void Parser::None(Lexer &l)
{
	(void)l;
}

void Parser::Mod(Lexer &l)
{
	(void)l;
	IOperand const *v1;
	IOperand const *v2;

	if (m_Stack.size() < 2)
		throw OperatorStackSize();
	v1 = m_Stack.back();
	m_Stack.pop_back();
	v2 = m_Stack.back();
	m_Stack.pop_back();
	m_Stack.push_back(*v1 % *v2);
	delete v1;
	delete v2;
}

void Parser::Execute(Lexer &l)
{
	(void)l;
}

void Parser::Execute()
{
	size_t line = 0;
	try
	{
		for (auto a : m_Instructions)
		{
			line = a.getLine();
			operation_t fun = sOperations[static_cast<size_t>(a.getCommand())];
			((*this).*(fun))(a);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "line " << line << ": \033[0;35m" << e.what() << "\033[0m\n";
	}
	m_Instructions.clear();
}

void Parser::Run()
{
	size_t line = 1;
	m_Error = false;
	while (!m_Stream.eof())
	{
		try
		{
			std::string read;
			std::cout << read;
			getline(m_Stream, read);
			Lexer l(read, line);
			m_Instructions.push_back(l);
			if (m_Instructions.back().getCommand() == ECommand::EXIT)
			{
				if (!m_Error)
					Execute();
				return;
			}
			if (m_Instructions.back().getCommand() == ECommand::RUN)
			{
				Execute();
			}
		}
		catch(const std::exception& e)
		{
			m_Error = true;
			std::cerr << "line " << line << ": \033[0;31m" << e.what() << "\033[0m\n";
			m_Instructions.clear();
		}
		line++;
	}
	std::cerr << "line " << line << ": \033[0;31m" << "No exit command" << "\033[0m\n";
}

const char *Parser::EmptyStack::what() const throw()
{
	return "Empty Stack";
}

const char *Parser::OperatorStackSize::what() const throw()
{
	return "Cannot operate On Stack With Less Than 2 Values";
}

const char *Parser::Assertion::what() const throw()
{
	return "Assertion Failed";
}