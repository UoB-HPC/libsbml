/**
 * @file DistribCategoricalUnivariateDistribution.h
 * @brief Definition of the DistribCategoricalUnivariateDistribution class.
 * @author SBMLTeam
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML. Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2013-2018 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 * 3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 * Pasadena, CA, USA
 *
 * Copyright (C) 2002-2005 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. Japan Science and Technology Agency, Japan
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation. A copy of the license agreement is provided in the
 * file named "LICENSE.txt" included with this software distribution and also
 * available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 *
 * @class DistribCategoricalUnivariateDistribution
 * @sbmlbrief{distrib} TODO:Definition of the
 * DistribCategoricalUnivariateDistribution class.
 */


#ifndef DistribCategoricalUnivariateDistribution_H__
#define DistribCategoricalUnivariateDistribution_H__


#include <sbml/common/extern.h>
#include <sbml/common/sbmlfwd.h>
#include <sbml/packages/distrib/common/distribfwd.h>


#ifdef __cplusplus


#include <string>


#include <sbml/packages/distrib/sbml/DistribUnivariateDistribution.h>
#include <sbml/packages/distrib/extension/DistribExtension.h>


LIBSBML_CPP_NAMESPACE_BEGIN


class DistribBernoulliDistribution;
class DistribCategoricalDistribution;

class LIBSBML_EXTERN DistribCategoricalUnivariateDistribution : public
  DistribUnivariateDistribution
{

public:

  /**
   * Creates a new DistribCategoricalUnivariateDistribution using the given
   * SBML Level, Version and &ldquo;distrib&rdquo; package version.
   *
   * @param level an unsigned int, the SBML Level to assign to this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param version an unsigned int, the SBML Version to assign to this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param pkgVersion an unsigned int, the SBML Distrib Version to assign to
   * this DistribCategoricalUnivariateDistribution.
   *
   * @copydetails doc_note_setting_lv_pkg
   */
  DistribCategoricalUnivariateDistribution(
                                           unsigned int level =
                                             DistribExtension::getDefaultLevel(),
                                           unsigned int version =
                                             DistribExtension::getDefaultVersion(),
                                           unsigned int pkgVersion =
                                             DistribExtension::getDefaultPackageVersion());


  /**
   * Creates a new DistribCategoricalUnivariateDistribution using the given
   * DistribPkgNamespaces object.
   *
   * @copydetails doc_what_are_sbml_package_namespaces
   *
   * @param distribns the DistribPkgNamespaces object.
   *
   * @copydetails doc_note_setting_lv_pkg
   */
  DistribCategoricalUnivariateDistribution(DistribPkgNamespaces *distribns);


  /**
   * Copy constructor for DistribCategoricalUnivariateDistribution.
   *
   * @param orig the DistribCategoricalUnivariateDistribution instance to copy.
   */
  DistribCategoricalUnivariateDistribution(const
    DistribCategoricalUnivariateDistribution& orig);


  /**
   * Assignment operator for DistribCategoricalUnivariateDistribution.
   *
   * @param rhs the DistribCategoricalUnivariateDistribution object whose
   * values are to be used as the basis of the assignment.
   */
  DistribCategoricalUnivariateDistribution& operator=(const
    DistribCategoricalUnivariateDistribution& rhs);


  /**
   * Creates and returns a deep copy of this
   * DistribCategoricalUnivariateDistribution object.
   *
   * @return a (deep) copy of this DistribCategoricalUnivariateDistribution
   * object.
   */
  virtual DistribCategoricalUnivariateDistribution* clone() const;


  /**
   * Destructor for DistribCategoricalUnivariateDistribution.
   */
  virtual ~DistribCategoricalUnivariateDistribution();


  /**
   * Predicate returning @c true if this abstract
   * "DistribCategoricalUnivariateDistribution" is of type
   * DistribBernoulliDistribution
   *
   * @return @c true if this abstract
   * "DistribCategoricalUnivariateDistribution" is of type
   * DistribBernoulliDistribution, @c false otherwise
   */
  virtual bool isDistribBernoulliDistribution() const;


  /**
   * Predicate returning @c true if this abstract
   * "DistribCategoricalUnivariateDistribution" is of type
   * DistribCategoricalDistribution
   *
   * @return @c true if this abstract
   * "DistribCategoricalUnivariateDistribution" is of type
   * DistribCategoricalDistribution, @c false otherwise
   */
  virtual bool isDistribCategoricalDistribution() const;


  /**
   * Returns the XML element name of this
   * DistribCategoricalUnivariateDistribution object.
   *
   * For DistribCategoricalUnivariateDistribution, the XML element name is
   * always @c "categoricalUnivariateDistribution".
   *
   * @return the name of this element, i.e.
   * @c "categoricalUnivariateDistribution".
   */
  virtual const std::string& getElementName() const;


  /**
   * Returns the libSBML type code for this
   * DistribCategoricalUnivariateDistribution object.
   *
   * @copydetails doc_what_are_typecodes
   *
   * @return the SBML type code for this object:
   * @sbmlconstant{SBML_DISTRIB_CATEGORICALUNIVARIATEDISTRIBUTION,
   * SBMLDistribTypeCode_t}.
   *
   * @copydetails doc_warning_typecodes_not_unique
   *
   * @see getElementName()
   * @see getPackageName()
   */
  virtual int getTypeCode() const;


  /**
   * Predicate returning @c true if all the required attributes for this
   * DistribCategoricalUnivariateDistribution object have been set.
   *
   * @return @c true to indicate that all the required attributes of this
   * DistribCategoricalUnivariateDistribution have been set, otherwise @c false
   * is returned.
   */
  virtual bool hasRequiredAttributes() const;



  /** @cond doxygenLibsbmlInternal */

  /**
   * Write any contained elements
   */
  virtual void writeElements(XMLOutputStream& stream) const;

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Accepts the given SBMLVisitor
   */
  virtual bool accept(SBMLVisitor& v) const;

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Sets the parent SBMLDocument
   */
  virtual void setSBMLDocument(SBMLDocument* d);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Enables/disables the given package with this element
   */
  virtual void enablePackageInternal(const std::string& pkgURI,
                                     const std::string& pkgPrefix,
                                     bool flag);

  /** @endcond */




  #ifndef SWIG



  /** @cond doxygenLibsbmlInternal */

  /**
   * Gets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName, bool& value)
    const;

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Gets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName, int& value) const;

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Gets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName,
                           double& value) const;

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Gets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName,
                           unsigned int& value) const;

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Gets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName,
                           std::string& value) const;

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Predicate returning @c true if this
   * DistribCategoricalUnivariateDistribution's attribute "attributeName" is
   * set.
   *
   * @param attributeName, the name of the attribute to query.
   *
   * @return @c true if this DistribCategoricalUnivariateDistribution's
   * attribute "attributeName" has been set, otherwise @c false is returned.
   */
  virtual bool isSetAttribute(const std::string& attributeName) const;

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Sets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName, bool value);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Sets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName, int value);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Sets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName, double value);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Sets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName,
                           unsigned int value);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Sets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName,
                           const std::string& value);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Unsets the value of the "attributeName" attribute of this
   * DistribCategoricalUnivariateDistribution.
   *
   * @param attributeName, the name of the attribute to query.
   *
   * @copydetails doc_returns_success_code
   * @li @sbmlconstant{LIBSBML_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @sbmlconstant{LIBSBML_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int unsetAttribute(const std::string& attributeName);

  /** @endcond */




  #endif /* !SWIG */


protected:


  /** @cond doxygenLibsbmlInternal */

  /**
   * Creates a new object from the next XMLToken on the XMLInputStream
   */
  virtual SBase* createObject(XMLInputStream& stream);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Adds the expected attributes for this element
   */
  virtual void addExpectedAttributes(ExpectedAttributes& attributes);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Reads the expected attributes into the member data variables
   */
  virtual void readAttributes(const XMLAttributes& attributes,
                              const ExpectedAttributes& expectedAttributes);

  /** @endcond */



  /** @cond doxygenLibsbmlInternal */

  /**
   * Writes the attributes to the stream
   */
  virtual void writeAttributes(XMLOutputStream& stream) const;

  /** @endcond */


};



LIBSBML_CPP_NAMESPACE_END




#endif /* __cplusplus */




#ifndef SWIG




LIBSBML_CPP_NAMESPACE_BEGIN




BEGIN_C_DECLS


/**
 * Creates a new DistribCategoricalUnivariateDistribution_t using the given
 * SBML Level, Version and &ldquo;distrib&rdquo; package version.
 *
 * @param level an unsigned int, the SBML Level to assign to this
 * DistribCategoricalUnivariateDistribution_t.
 *
 * @param version an unsigned int, the SBML Version to assign to this
 * DistribCategoricalUnivariateDistribution_t.
 *
 * @param pkgVersion an unsigned int, the SBML Distrib Version to assign to
 * this DistribCategoricalUnivariateDistribution_t.
 *
 * @copydetails doc_note_setting_lv_pkg
 *
 * @copydetails doc_returned_owned_pointer
 *
 * @memberof DistribCategoricalUnivariateDistribution_t
 */
LIBSBML_EXTERN
DistribCategoricalUnivariateDistribution_t *
DistribCategoricalUnivariateDistribution_create(unsigned int level,
                                                unsigned int version,
                                                unsigned int pkgVersion);


/**
 * Creates and returns a deep copy of this
 * DistribCategoricalUnivariateDistribution_t object.
 *
 * @param dcud the DistribCategoricalUnivariateDistribution_t structure.
 *
 * @return a (deep) copy of this DistribCategoricalUnivariateDistribution_t
 * object.
 *
 * @copydetails doc_returned_owned_pointer
 *
 * @memberof DistribCategoricalUnivariateDistribution_t
 */
LIBSBML_EXTERN
DistribCategoricalUnivariateDistribution_t*
DistribCategoricalUnivariateDistribution_clone(const
  DistribCategoricalUnivariateDistribution_t* dcud);


/**
 * Frees this DistribCategoricalUnivariateDistribution_t object.
 *
 * @param dcud the DistribCategoricalUnivariateDistribution_t structure.
 *
 * @memberof DistribCategoricalUnivariateDistribution_t
 */
LIBSBML_EXTERN
void
DistribCategoricalUnivariateDistribution_free(DistribCategoricalUnivariateDistribution_t*
  dcud);


/**
 * Predicate returning @c 1 if this DistribCategoricalUnivariateDistribution_t
 * is of type DistribBernoulliDistribution_t
 *
 * @param dcud the DistribCategoricalUnivariateDistribution_t structure.
 *
 * @return @c 1 if this DistribCategoricalUnivariateDistribution_t is of type
 * DistribBernoulliDistribution_t, @c 0 otherwise
 *
 * @memberof DistribCategoricalUnivariateDistribution_t
 */
LIBSBML_EXTERN
int
DistribCategoricalUnivariateDistribution_isDistribBernoulliDistribution(const
  DistribCategoricalUnivariateDistribution_t * dcud);


/**
 * Predicate returning @c 1 if this DistribCategoricalUnivariateDistribution_t
 * is of type DistribCategoricalDistribution_t
 *
 * @param dcud the DistribCategoricalUnivariateDistribution_t structure.
 *
 * @return @c 1 if this DistribCategoricalUnivariateDistribution_t is of type
 * DistribCategoricalDistribution_t, @c 0 otherwise
 *
 * @memberof DistribCategoricalUnivariateDistribution_t
 */
LIBSBML_EXTERN
int
DistribCategoricalUnivariateDistribution_isDistribCategoricalDistribution(const
  DistribCategoricalUnivariateDistribution_t * dcud);


/**
 * Predicate returning @c 1 (true) if all the required attributes for this
 * DistribCategoricalUnivariateDistribution_t object have been set.
 *
 * @param dcud the DistribCategoricalUnivariateDistribution_t structure.
 *
 * @return @c 1 (true) to indicate that all the required attributes of this
 * DistribCategoricalUnivariateDistribution_t have been set, otherwise @c 0
 * (false) is returned.
 *
 * @memberof DistribCategoricalUnivariateDistribution_t
 */
LIBSBML_EXTERN
int
DistribCategoricalUnivariateDistribution_hasRequiredAttributes(const
  DistribCategoricalUnivariateDistribution_t * dcud);




END_C_DECLS




LIBSBML_CPP_NAMESPACE_END




#endif /* !SWIG */




#endif /* !DistribCategoricalUnivariateDistribution_H__ */


