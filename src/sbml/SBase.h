/**
 * Filename    : SBase.h
 * Description : Base object of all SBML objects
 * Author(s)   : SBW Development Group <sysbio-team@caltech.edu>
 * Organization: Caltech ERATO Kitano Systems Biology Project
 * Created     : 2002-11-13
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


#ifndef SBase_h
#define SBase_h


#include "SBMLTypeCodes.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * As shown below, put SBASE_FIELDS as the *first* item of any struct
 * which "is a(n)" SBML object.
 */
#define SBASE_FIELDS       \
  SBMLTypeCode_t typecode; \
  char           *notes;   \
  char           *annotation


/**
 * Used primarily for example and internally by the functions below.
 */
typedef struct
{
  SBASE_FIELDS;
} SBase_t;


/**
 * SBase "objects" are abstract, i.e., they are not created.  Rather,
 * specific "subclasses" are created (e.g., Model) and their SBASE_FIELDS
 * are initialized with this function.  The type of the specific "subclass"
 * is indicated by the given SBMLTypeCode.
 */
void
SBase_init (SBase_t *sb, SBMLTypeCode_t tc);

/**
 * Clears (frees) only the SBASE_FIELDS of sb.
 */
void
SBase_clear (SBase_t *sb);

/**
 * Sets the notes field of the given SBML object to a copy of notes.  If
 * object already has notes, the existing string is freed before the new
 * one is copied.
 */
void
SBase_setNotes (SBase_t *sb, const char *notes);

/**
 * Sets the annotation field of the given SBML object to a copy of
 * annotations.  If object already has an annotation, the existing string
 * is freed before the new one is copied.
 */
void
SBase_setAnnotation (SBase_t *sb, const char *annotation);


#ifdef __cplusplus
}
#endif


#endif  /** SBase_h **/
