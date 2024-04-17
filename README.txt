You are to implement a simple version of a spreadsheet.

This spreadsheet is a system for expressing functional dependencies between a collection of value "cells". Each cell
represents a numeric value and has an associated cell name that is "V" followed by a positive
integer ID suffix. Inter-cell dependencies are "dynamic" in a manner that is described more precisely below.

Cells can be defined in terms of numeric constants and other cells, via one of the following definitional forms (using
BNF-like notation):

    <cell name> := <number>
    <cell name> := <term> <operator> <term>

The first form indicates that a cell (identified by its name) is being set to a numeric constant:

    <number> := a floating-point literal

The second form defines a cell to be the result of computing a binary arithmetic expression over numbers and/or values
of other cells:

    <operator> := '+' | '-' | '*' | '/'
    <term>     := <number> | <cell name>

When first created, a spreadsheet starts out as an empty cell collection. It is subsequently manipulated via a sequence
of operations that are a mix of cell definitions and cell value queries. In the example
 ~~~~~~~~~
set V1 = 10.0
get V1
set V2 = 2 * V3
set V3 = 15.0
get V2
get V3
 ----------
we add a total of 3 cells (these are the lines starting with "set"): V1 is set to constant 10.0, V2 is defined
as twice the value of V3, and V3 is set to constant 15.0.

A cell can be queried (these are the lines starting with "get") at any point where its definition can be evaluated down
to a known numeric value. In the example above, V2 cannot be queried as soon as it is defined because its definition
references cell V3 which isn't yet entered into the spreadsheet at that point. However, following the subsequent
"set V3 = 15.0" definition both V2 and V3 can be queried successfully.

Like in a real spreadsheet, a cell can be re-defined and such a cell update will propagate to all other cells that may
be dependent on it. For example, the sequence above could be continued as
 ~~~~~~~~~
 ...
set V3 = 20.0
get V2
get V3
 ----------
and it will show V2 and V3 as now equal to 40.0 and 20.0, respectively.

You are provided with two files, a "main.cpp" driver and a skeleton of 'spreadsheet' class in the header "spreadsheet.h"
with the following API:

class spreadsheet
{
    public:

        spreadsheet();

        double get(const std::string & name) const;
        void set(const std::string & name, const std::string & definition);

    private:

    /* TODO */
};

The driver will read a sequence of get/set operations from stdin using syntax that should be obvious from the shown
examples and apply these operations to a spreadsheet instance. The result of each cell query ("get") will be traced
to stdout using a line formatted as "<cell name> <cell value>", one such output line per query. For instance, the example
above will result in stdout output
 ~~~~~~~~~
V1 10
V2 30
V3 15
V2 40
V3 20
 ----------
Your objective is to complete the class implementation in the header file so that it provides the intended spreadsheet
evaluation model.

 Notes:
~~~~~~~~~
 - you should not need to modify "main.cpp", only "spreadsheet.h"; if desired, you may add additional source and header files;
 - further input/output examples are shown at the end of this README;
 - you can assume that all input lines have single spaces as delimiters and have no leading/trailing whitespace; you can
 further assume that all input tokens (floating point literals and cell names) will be valid;
 - because we are working with floating point arithmetic, the exact values obtained by cell queries could vary slightly
 depending on the order of evaluation, roundoff errors, etc -- you can assume that output is validated using sufficient
 numerical tolerance;
 - you should handle any input and evaluation errors by throwing 'std::logic_error' or a subclass thereof, with a message
 string that starts with an "ERROR:" prefix followed by some human-friendly explanation of the error;

Example 1:
==========
input:
 ~~~~~~~~~
set V1 = 1
set V2 = V1 + V3
set V3 = 2
get V1
get V2
get V3
 ----------
output:
 ~~~~~~~~~
V1 1
V2 3
V3 2
 ----------

Example 2:
==========
input:
 ~~~~~~~~~
set V1 = 10.0
get V1
set V2 = V1 * V1
get V2
set V3 = V2 - 10.0
set V4 = V1 + V3
set V5 = V1 - V3
get V4
get V5
 ----------
output:
 ~~~~~~~~~
V1 10
V2 100
V4 100
V5 -80
 ----------

Example 3:
==========
input:
 ~~~~~~~~~
set V1 = 1
set V2 = V1 + V1
get V2
set V2 = V1 + V2
get V2
 ----------
output:
 ~~~~~~~~~
V2 2
ERROR: circular reference
 ----------

