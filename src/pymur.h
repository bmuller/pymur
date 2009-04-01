#include "config.h"

#include <indri/QueryEnvironment.hpp>
#include <indri/IndexEnvironment.hpp>
#include <indri/ConflationPattern.hpp>
#include <indri/FileClassEnvironmentFactory.hpp>
#include <indri/ScoredExtentResult.hpp>
#include <Index.hpp>
#include <IndexManager.hpp>
#include <RetMethodManager.hpp>
#include <IndexedReal.hpp>

#include <Python.h>

#include <cstdlib>
#include <iostream>

#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

#include "argchecker.h"
#include "utils.h"
#include "index.h"
#include "index_environment.h"
#include "scored_extent_result.h"
#include "query_environment.h"
