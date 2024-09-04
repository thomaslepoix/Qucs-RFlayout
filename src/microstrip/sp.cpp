///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "sp.hpp"
using namespace std;

//******************************************************************************
string const Sp::m_descriptor("s_parameter_simulation");

//******************************************************************************
Sp::Sp(string const _label,
			string const _type,
			bool const _mirrorx,
			short const _r,
			std::string const _simtype,
			long double const _fstart,
			long double const _fstop,
			unsigned long const _n) :
	Element(_label, _type, true, _mirrorx, _r, 0, ""),
	m_simtype(_simtype),
	m_fstart(_fstart),
	m_fstop(_fstop),
	m_n(_n)
	{}

//******************************************************************************
string Sp::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Sp::getFstart() const {
	return(m_fstart);
	}

//******************************************************************************
long double Sp::getFstop() const {
	return(m_fstop);
	}

//******************************************************************************
string Sp::getSimtype() const {
	return(m_simtype);
	}

//******************************************************************************
unsigned long Sp::getN() const {
	return(m_n);
	}
