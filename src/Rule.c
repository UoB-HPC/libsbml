/**
 * Filename    : Rule.c
 * Description : SBML Rule
 * Author(s)   : SBW Development Group <sysbio-team@caltech.edu>
 * Organization: Caltech ERATO Kitano Systems Biology Project
 * Created     : 2002-11-26
 * Revision    : $Id$
 * Source      : $Source$
 *
 * Copyright 2002 California Institute of Technology and
 * Japan Science and Technology Corporation.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  The software and
 * documentation provided hereunder is on an "as is" basis, and the
 * California Institute of Technology and Japan Science and Technology
 * Corporation have no obligations to provide maintenance, support,
 * updates, enhancements or modifications.  In no event shall the
 * California Institute of Technology or the Japan Science and Technology
 * Corporation be liable to any party for direct, indirect, special,
 * incidental or consequential damages, including lost profits, arising
 * out of the use of this software and its documentation, even if the
 * California Institute of Technology and/or Japan Science and Technology
 * Corporation have been advised of the possibility of such damage.  See
 * the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * The original code contained here was initially developed by:
 *
 *     Ben Bornstein
 *     The Systems Biology Workbench Development Group
 *     ERATO Kitano Systems Biology Project
 *     Control and Dynamical Systems, MC 107-81
 *     California Institute of Technology
 *     Pasadena, CA, 91125, USA
 *
 *     http://www.cds.caltech.edu/erato
 *     mailto:sysbio-team@caltech.edu
 *
 * Contributor(s):
 */


#include "sbml/common.h"
#include "sbml/Rule.h"


/**
 * Rule "objects" are abstract, i.e. they are not created.  Rather,
 * specific "subclasses" are created (e.g. AlgebraicRule) and their
 * RULE_FIELDS are initialized with this function.  The type of the
 * specific "subclass" is indicated by the given SBMLTypeCode.
 *
 * This function also calls its "parent", SBase_init().
 */
void
Rule_init (Rule_t *r, SBMLTypeCode_t tc)
{
  SBase_init((SBase_t *) r, tc);
  r->formula = NULL;
}


/**
 * Clears (frees) RULE_FIELDS of this Rule "subclass".  This function also
 * calls its "parent", SBase_clear().
 */
void
Rule_clear (Rule_t *r)
{
  if (r == NULL) return;

  SBase_clear((SBase_t *) r);
  safe_free(r->formula);
}


/**
 * Sets the formula field of this Rule to a copy of string.
 */
void
Rule_setFormula (Rule_t *r, const char *string)
{
  if (r->formula != NULL)
  {
    safe_free(r->formula);
  }

  r->formula = (string == NULL) ? NULL : safe_strdup(string);
}
