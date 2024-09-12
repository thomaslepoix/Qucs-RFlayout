///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include "element.hpp"

//******************************************************************************
class Sp final : public Element {
private :
	static std::string const m_descriptor;
	std::string const m_simtype;
	long double const m_fstart;
	long double const m_fstop;
	unsigned long const m_n;
public :
	Sp(std::string _label,
			std::string _type,
			bool const _mirrorx,
			short const _r,
			std::string _simtype,
			long double const _fstart,
			long double const _fstop,
			unsigned long const _n);
	~Sp()=default;
	std::string getDescriptor() const override;
	long double getFstart() const override;
	long double getFstop() const override;
	std::string getSimtype() const override;
	unsigned long getN() const override;
};
