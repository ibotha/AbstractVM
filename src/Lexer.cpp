/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 08:44:11 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/24 11:06:41 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include "OperandFactory.hpp"
#include "iostream"

Lexer::Lexer(std::string const &s, size_t line)
	:m_Command(ECommand::NONE), m_Index(1), m_Line(line), m_Value(nullptr)
{
	std::string cmdSeparators = " \t\v\n";
	size_t comment = s.find_first_of(";");
	std::vector<std::string> tokens;
		
	if (comment == 0 && s[1] == ';')
		tokens.push_back(";;");
	for (size_t i = 0; i < s.length() && s[i] != ';' && i < comment; i++)
	{
		i = s.find_first_not_of(cmdSeparators, i);
		size_t end = s.find_first_of(cmdSeparators, i);
		if (i >= comment)
			break;
		tokens.push_back(s.substr(i, end - i));
		i = end;
		if (i >= comment)
			break;
	}
	if (tokens.size() == 0)
		return;
	std::string command = tokens[0];
	if (command == "add")
	{
		m_Command = ECommand::ADD;
	}
	else if (command == "sub")
	{
		m_Command = ECommand::SUB;
	}
	else if (command == "assert")
	{
		m_Command = ECommand::ASSERT;
	}
	else if (command == "div")
	{
		m_Command = ECommand::DIV;
	}
	else if (command == "dump")
	{
		m_Command = ECommand::DUMP;
	}
	else if (command == "exit")
	{
		m_Command = ECommand::EXIT;
	}
	else if (command == "mod")
	{
		m_Command = ECommand::MOD;
	}
	else if (command == "mul")
	{
		m_Command = ECommand::MUL;
	}
	else if (command == "pop")
	{
		m_Command = ECommand::POP;
	}
	else if (command == "print")
	{
		m_Command = ECommand::PRINT;
	}
	else if (command == "push")
	{
		m_Command = ECommand::PUSH;
	}
	else if (command == ";;")
	{
		m_Command = ECommand::RUN;
	}
	else
	{
		throw UnknownCommand();
	}
	tokens.erase(tokens.begin());
	if (m_Command == ECommand::PUSH || m_Command == ECommand::ASSERT)
	{
		if (tokens.size() == 0)
			throw NoMoreTokens();
		OperandFactory o;
		size_t open, close;
		open = tokens[0].find_first_of('(');
		close = tokens[0].find_first_of(')');
		if ((tokens[0].find(')', open)) == std::string::npos)
			throw NoMoreTokens();
		std::string const stype = tokens[0].substr(0, open);
		std::string const data = tokens[0].substr(open + 1, close - open - 1);
		EOperandType type;
		type = EOperandType::MAX;
		if (stype == "int8") type = EOperandType::INT8;
		else if (stype == "int16") type = EOperandType::INT16;
		else if (stype == "int32") type = EOperandType::INT32;
		else if (stype == "float") type = EOperandType::FLOAT;
		else if (stype == "double") type = EOperandType::DOUBLE;
		else throw UnknownDataType();
		m_Value = o.createOperand(type, data);
	}
}

Lexer::~Lexer()
{
	if (m_Value)
		delete m_Value;
}

size_t Lexer::getLine() const
{
	return m_Line;
}

Lexer::Lexer(Lexer const &rhs)
{
	m_Value = rhs.getValue();
	m_Command = rhs.m_Command;
	m_Index = rhs.m_Index;
	m_Line = rhs.m_Line;
}

Lexer &Lexer::operator=(Lexer const &rhs)
{
	if (this != &rhs)
	{
		*this = rhs;
	}
	return (*this);
}

Lexer::Lexer() {};

ECommand Lexer::getCommand() const
{
	return m_Command;
}

IOperand const *Lexer::getValue() const
{
	if (!m_Value)
		return nullptr;
	OperandFactory o;
	return o.createOperand(m_Value->getType(), m_Value->toString());
}

const char *Lexer::NoMoreTokens::what() const throw()
{
	return "Lexical Error";
}

const char *Lexer::UnknownDataType::what() const throw()
{
	return "Unknown Type";
}

const char *Lexer::UnknownCommand::what() const throw()
{
	return "Unknown Command";
}