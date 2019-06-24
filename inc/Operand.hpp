/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:26:27 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/21 15:09:14 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <sstream>
#include <cmath>

template <typename T>
T mod(T val1, T val2)
{
	return val1 % val2;
}

template <>
float mod<float>(float val1, float val2)
{
	return std::fmod(val1, val2);
}

template <>
double mod<double>(double val1, double val2)
{
	return std::fmod(val1, val2);
}

template <typename T>
inline EOperandType getDataType()
{
	return EOperandType::MAX;
}

template <>
inline EOperandType getDataType<int8_t>()
{
	return EOperandType::INT8;
}

template <>
inline EOperandType getDataType<int16_t>()
{
	return EOperandType::INT16;
}

template <>
inline EOperandType getDataType<int32_t>()
{
	return EOperandType::INT32;
}

template <>
inline EOperandType getDataType<float>()
{
	return EOperandType::FLOAT;
}

template <>
inline EOperandType getDataType<double>()
{
	return EOperandType::DOUBLE;
}

#include "iostream"

template <typename T>
class Operand : public IOperand
{
public:
	Operand()
		: m_Value(0)
	{
	}

	virtual ~Operand() {}

	Operand(std::string value)
	{
		EOperandType type = getDataType<T>();
		if (type == EOperandType::INT8 || type == EOperandType::INT16 || type == EOperandType::INT32)
		{
			int32_t temp = std::stoi(value);
			m_Value = static_cast<T>(temp);
			if (static_cast<int32_t>(m_Value) != temp)
			{
				throw std::out_of_range(temp < m_Value ? "Underflow" : "Overflow");
			}
		}
		else if (type == EOperandType::FLOAT)
		{
			m_Value = std::stof(value);
		}
		else if (type == EOperandType::DOUBLE)
		{
			m_Value = std::stod(value);
		}
	}

	Operand(Operand const &rhs)
	{
		*this = rhs;
	}

	Operand &operator=(Operand const &rhs)
	{
		if (this != &rhs)
		{
			*this = rhs;
		}
		return *this;
	}

	virtual int getPrecision(void) const
	{
		return static_cast<int>(getType());
	}

	virtual EOperandType getType(void) const
	{
		return getDataType<T>();
	}

	virtual IOperand const *operator+(IOperand const &rhs) const
	{
		std::string valstr;
		EOperandType type = rhs.getType() > getType() ? rhs.getType() : getType();
		if (type == EOperandType::INT8 || type == EOperandType::INT16 || type == EOperandType::INT32)
		{
			valstr = std::to_string(m_Value + std::stoi(rhs.toString()));
		}
		else if (type == EOperandType::FLOAT)
		{
			valstr = std::to_string(m_Value + std::stof(rhs.toString()));
		}
		else if (type == EOperandType::DOUBLE)
		{
			valstr = std::to_string(m_Value + std::stod(rhs.toString()));
		}
		OperandFactory o;
		return o.createOperand(type, valstr);
	}

	virtual IOperand const *operator-(IOperand const &rhs) const
	{
		std::string valstr;
		EOperandType type = rhs.getType() > getType() ? rhs.getType() : getType();
		if (type == EOperandType::INT8 || type == EOperandType::INT16 || type == EOperandType::INT32)
		{
			valstr = std::to_string(m_Value - std::stoi(rhs.toString()));
		}
		else if (type == EOperandType::FLOAT)
		{
			valstr = std::to_string(m_Value - std::stof(rhs.toString()));
		}
		else if (type == EOperandType::DOUBLE)
		{
			valstr = std::to_string(m_Value - std::stod(rhs.toString()));
		}
		OperandFactory o;
		return o.createOperand(type, valstr);
	}

	virtual IOperand const *operator*(IOperand const &rhs) const
	{
		if (rhs.getPrecision() > getPrecision())
			return (rhs * *this);
		Operand<T> temp(rhs.toString());
		T val = temp.m_Value * m_Value;
		Operand<T> *ret = new Operand<T>;
		ret->m_Value = val;
		return ret;
	}

	virtual IOperand const *operator/(IOperand const &rhs) const
	{
		std::string valstr;
		EOperandType type = rhs.getType() > getType() ? rhs.getType() : getType();
		if (type == EOperandType::INT8 || type == EOperandType::INT16 || type == EOperandType::INT32)
		{
			int32_t operand = std::stoi(rhs.toString());
			if (operand == 0)
				throw DivZero();
			valstr = std::to_string(m_Value / operand);
		}
		else if (type == EOperandType::FLOAT)
		{
			float operand = std::stof(rhs.toString());
			if (operand == 0)
				throw DivZero();
			valstr = std::to_string(m_Value / operand);
		}
		else if (type == EOperandType::DOUBLE)
		{
			double operand = std::stod(rhs.toString());
			if (operand == 0)
				throw DivZero();
			valstr = std::to_string(m_Value / operand);
		}
		OperandFactory o;
		return o.createOperand(type, valstr);
	}

	virtual IOperand const *operator%(IOperand const &rhs) const
	{
		std::string valstr;
		EOperandType type = rhs.getType() > getType() ? rhs.getType() : getType();
		if (type == EOperandType::INT8 || type == EOperandType::INT16 || type == EOperandType::INT32)
		{
			int32_t operand = std::stoi(rhs.toString());
			if (operand == 0)
				throw DivZero();
			valstr = std::to_string(mod<T>(m_Value, operand));
		}
		else if (type == EOperandType::FLOAT)
		{
			float operand = std::stof(rhs.toString());
			if (operand == 0)
				throw DivZero();
			valstr = std::to_string(mod<T>(m_Value, operand));
		}
		else if (type == EOperandType::DOUBLE)
		{
			double operand = std::stod(rhs.toString());
			if (operand == 0)
				throw DivZero();
			valstr = std::to_string(mod<T>(m_Value, operand));
		}
		OperandFactory o;
		return o.createOperand(type, valstr);
	}

	virtual bool operator==(IOperand const &rhs) const
	{
		bool ret = false;
		EOperandType type = rhs.getType() > getType() ? rhs.getType() : getType();
		if (type == EOperandType::INT8 || type == EOperandType::INT16 || type == EOperandType::INT32)
		{
			ret = m_Value == std::stoi(rhs.toString());
		}
		else if (type == EOperandType::FLOAT)
		{
			ret = m_Value == std::stof(rhs.toString());
		}
		else if (type == EOperandType::DOUBLE)
		{
			ret = m_Value == std::stod(rhs.toString());
		}
		return ret;
	}

	virtual std::string toString(void) const
	{
		std::stringstream ss;
		if (getType() == EOperandType::INT8)
		{
			ss << static_cast<int>(m_Value);
		}
		else
		{
			ss << m_Value;
		}
		return ss.str();
	}

	struct DivZero : public std::exception {
		const char *what() const throw()
		{
			return "Cannot Divide by zero";
		}
	};

private:
	T m_Value;
};