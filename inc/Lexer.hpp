/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 08:36:10 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/24 11:06:42 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IOperand.hpp"
#include <string>
#include <vector>

enum class ECommand {
	NONE = 0,
	PUSH,
	POP,
	DUMP,
	ASSERT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	PRINT,
	EXIT,
	RUN,
	UNKNOWN
};

class Lexer {
	public:
		Lexer(std::string const &s, size_t line);
		~Lexer();
		Lexer(Lexer const &rhs);
		Lexer &operator=(Lexer const &rhs);
		ECommand getCommand() const;
		IOperand const *getValue() const;
		size_t getLine() const;
		struct NoMoreTokens : public std::exception {
			const char *what() const throw();
		};

		struct UnknownDataType : public std::exception {
			const char *what() const throw();
		};

		struct UnknownCommand : public std::exception {
			const char *what() const throw();
		};
		
	private:
		Lexer();

		ECommand m_Command;
		mutable size_t m_Index;
		size_t m_Line;
		IOperand const *m_Value;
};