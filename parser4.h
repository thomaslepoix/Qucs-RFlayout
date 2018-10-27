#ifndef PARSER4_H
#define PARSER4_H

#include <iostream>
#include <fstream>
#include <regex>

#include "eqn.h"
#include "pac.h"
#include "mcorn.h"
#include "mcross.h"
#include "mcoupled.h"
#include "mgap.h"
#include "mmbend.h"
#include "mlin.h"
#include "mopen.h"
#include "mrstub.h"
#include "mstep.h"
#include "mtee.h"
#include "mvia.h"

int parser4(Element**& tab_all, std::string const& n_sch, int& nelem);
long double suffix(std::string const s_sci, std::string const s_eng);

#endif
