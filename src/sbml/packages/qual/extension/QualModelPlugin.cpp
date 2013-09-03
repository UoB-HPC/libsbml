/**
 * @file    QualModelPlugin.cpp
 * @brief   Implementation of QualModelPlugin, the plugin class of
 *          qual package for the Model element.
 * @author  Akiya Jouraku
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2009-2011 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 */

#include <sbml/packages/qual/extension/QualModelPlugin.h>
#include <sbml/packages/qual/validator/QualSBMLError.h>

#include <iostream>
using namespace std;


#ifdef __cplusplus

LIBSBML_CPP_NAMESPACE_BEGIN

/*
 * Constructor
 */
QualModelPlugin::QualModelPlugin (const std::string &uri, 
                                      const std::string &prefix,
                                      QualPkgNamespaces *qualns)
  : SBasePlugin(uri,prefix, qualns)
   ,mQualitativeSpecies(qualns)
   ,mTransitions(qualns)
{
}


/*
 * Copy constructor. Creates a copy of this SBase object.
 */
QualModelPlugin::QualModelPlugin(const QualModelPlugin& orig)
  : SBasePlugin(orig)
  , mQualitativeSpecies(orig.mQualitativeSpecies)
  , mTransitions(orig.mTransitions)
{
}


/*
 * Destroy this object.
 */
QualModelPlugin::~QualModelPlugin () {}

/*
 * Assignment operator for QualModelPlugin.
 */
QualModelPlugin& 
QualModelPlugin::operator=(const QualModelPlugin& orig)
{
  if(&orig!=this)
  {
    this->SBasePlugin::operator =(orig);
    mQualitativeSpecies    = orig.mQualitativeSpecies;
    mTransitions    = orig.mTransitions;
  }    
  return *this;
}


/*
 * Creates and returns a deep copy of this QualModelPlugin object.
 * 
 * @return a (deep) copy of this SBase object
 */
QualModelPlugin* 
QualModelPlugin::clone () const
{
  return new QualModelPlugin(*this);  
}


/*
 *
 */
SBase*
QualModelPlugin::createObject(XMLInputStream& stream)
{
  SBase*        object = 0;

  const std::string&   name   = stream.peek().getName();
  const XMLNamespaces& xmlns  = stream.peek().getNamespaces();
  const std::string&   prefix = stream.peek().getPrefix();

  const std::string& targetPrefix = (xmlns.hasURI(mURI)) ? xmlns.getPrefix(mURI) : mPrefix;
  
  if (prefix == targetPrefix)
  {
    if ( name == "listOfQualitativeSpecies" ) 
    {
      if (mQualitativeSpecies.size() != 0)
      {
        getErrorLog()->logPackageError("qual", QualOneListOfTransOrQS, 
          getPackageVersion(), getLevel(), getVersion());
      }
      
      object = &mQualitativeSpecies;
    
      if (targetPrefix.empty())
      {
        //
        // (NOTE)
        //
        // A top-level element (listOfQualitativeSpecies) of the qual extension is located 
        // in a default namespace, and thus xmlns=".." attribute must be added to 
        // the element.
        // This is done by invoking SBMLDocument::enableDefaultNS() function with 
        // the two arguments (the uri of this package and true value).
        //
        mQualitativeSpecies.getSBMLDocument()->enableDefaultNS(mURI,true);
      }
    }          
    else if ( name == "listOfTransitions" ) 
    {
      if (mTransitions.size() != 0)
      {
        getErrorLog()->logPackageError("qual", QualOneListOfTransOrQS, 
          getPackageVersion(), getLevel(), getVersion());
      }
      
      object = &mTransitions;
    
      if (targetPrefix.empty())
      {
        //
        // (NOTE)
        //
        // A top-level element (listOfTransitions) of the qual extension is located 
        // in a default namespace, and thus xmlns=".." attribute must be added to 
        // the element.
        // This is done by invoking SBMLDocument::enableDefaultNS() function with 
        // the two arguments (the uri of this package and true value).
        //
        mTransitions.getSBMLDocument()->enableDefaultNS(mURI,true);
      }
    }          
  }    

  return object;
}


/** @cond doxygenLibsbmlInternal */


bool 
QualModelPlugin::accept(SBMLVisitor& v) const
{
  const Model * model = static_cast<const Model * >(this->getParentSBMLObject()); 
  
  v.visit(*model);
  v.leave(*model);

  for (unsigned int i = 0; i < getNumQualitativeSpecies(); i++)
  {
    getQualitativeSpecies(i)->accept(v);
  }
  for (unsigned int i = 0; i < getNumTransitions(); i++)
  {
    getTransition(i)->accept(v);
  }
  return true;
}


/** @endcond */



/*
 *
 */
void
QualModelPlugin::writeElements (XMLOutputStream& stream) const
{
  if (getNumQualitativeSpecies() > 0)
  {
    mQualitativeSpecies.write(stream);
  }    
  if (getNumTransitions() > 0)
  {
    mTransitions.write(stream);
  }    
}


/* default for components that have no required elements */
bool
QualModelPlugin::hasRequiredElements() const
{
  bool allPresent = true;

  if (mQualitativeSpecies.size() < 0)
  {
    allPresent = false;    
  }
  if (mTransitions.size() < 0)
  {
    allPresent = false;    
  }
  return allPresent;
}



/*
 *
 *  (EXTENSION) Additional public functions
 *
 */  


/*
 * Returns the ListOf Qual for this Model.
 */
const ListOfQualitativeSpecies*
QualModelPlugin::getListOfQualitativeSpecies () const
{
  return &this->mQualitativeSpecies;
}


/*
 * Returns the ListOf Qual for this Model.
 */
ListOfQualitativeSpecies*
QualModelPlugin::getListOfQualitativeSpecies ()
{
  return &this->mQualitativeSpecies;
}


/*
 * Returns the qual object that belongs to the given index. If the index
 * is invalid, NULL is returned.
 */
const QualitativeSpecies*
QualModelPlugin::getQualitativeSpecies (unsigned int index) const
{
  return static_cast<const QualitativeSpecies*>( mQualitativeSpecies.get(index) );
}


/*
 * Returns the qual object that belongs to the given index. If the index
 * is invalid, NULL is returned.
 */
QualitativeSpecies*
QualModelPlugin::getQualitativeSpecies (unsigned int index)
{
  return static_cast<QualitativeSpecies*>( mQualitativeSpecies.get(index) );
}


/*
 * Returns the qualitativeSpecies object based on its identifier.
 */
QualitativeSpecies*
QualModelPlugin::getQualitativeSpecies (const std::string& sid)
{
  return static_cast<QualitativeSpecies*>( mQualitativeSpecies.get(sid) );
}


/*
 * Returns the qualitativeSpecies object based on its identifier.
 */
const QualitativeSpecies* 
QualModelPlugin::getQualitativeSpecies (const std::string& sid) const
{
  return static_cast<const QualitativeSpecies*>( mQualitativeSpecies.get(sid) );
}


/*
 * Returns the number of QualitativeSpecies objects.
 */
unsigned int 
QualModelPlugin::getNumQualitativeSpecies() const
{
  return mQualitativeSpecies.size();
}



/*
 * Adds a copy of the qual object to the list of quals.
 */ 
int
QualModelPlugin::addQualitativeSpecies (const QualitativeSpecies* qual)
{
  if (!qual)
  {
    return LIBSBML_OPERATION_FAILED;
  }    
  else if (!qual->hasRequiredElements())
  {
    return LIBSBML_INVALID_OBJECT;
  }
  else if (getLevel() != qual->getLevel())
  {
    return LIBSBML_LEVEL_MISMATCH;
  }
  else if (getVersion() != qual->getVersion())
  {
    return LIBSBML_VERSION_MISMATCH;
  }
  else if (getPackageVersion() != qual->getPackageVersion())
  {
    return LIBSBML_PKG_VERSION_MISMATCH;
  }
  else
  {
    mQualitativeSpecies.append(qual);
  }

  return LIBSBML_OPERATION_SUCCESS;

}


/*
 * Creates a new qual object and adds it to the list of qual objects.
 * A reference to the newly created object is returned.
 */
QualitativeSpecies*
QualModelPlugin::createQualitativeSpecies ()
{
  QualitativeSpecies* g = 0;

  try
  {  
    QUAL_CREATE_NS(qualns, getSBMLNamespaces());
    g = new QualitativeSpecies(qualns);
  }
  catch(...)
  {
    /* 
     * NULL will be returned if the mSBMLNS is invalid (basically this
     * should not happen) or some exception is thrown (e.g. std::bad_alloc)
     *
     * (Maybe this should be changed so that caller can detect what kind 
     *  of error happened in this function.)
     */
  }

  if (g) mQualitativeSpecies.appendAndOwn(g);

  return g;
}


/*
 * Removes the nth QualitativeSpecies object from this Model object and
 * returns a pointer to it.
 */
QualitativeSpecies* 
QualModelPlugin::removeQualitativeSpecies (unsigned int n)
{
  return static_cast<QualitativeSpecies*>(mQualitativeSpecies.remove(n));
}


/*
 * Removes the QualitativeSpecies object with the given id attribute from 
 * this plugin object and returns a pointer to it.
 */
QualitativeSpecies* 
QualModelPlugin::removeQualitativeSpecies (const std::string& sid)
{
  return static_cast<QualitativeSpecies*>(mQualitativeSpecies.remove(sid));
}


/*
 * Returns the ListOf Qual for this Model.
 */
const ListOfTransitions*
QualModelPlugin::getListOfTransitions () const
{
  return &this->mTransitions;
}


/*
 * Returns the ListOfTransitions for this Model.
 */
ListOfTransitions*
QualModelPlugin::getListOfTransitions ()
{
  return &this->mTransitions;
}


/*
 * Returns the qual object that belongs to the given index. If the index
 * is invalid, NULL is returned.
 */
const Transition*
QualModelPlugin::getTransition (unsigned int index) const
{
  return static_cast<const Transition*>( mTransitions.get(index) );
}


/*
 * Returns the qual object that belongs to the given index. If the index
 * is invalid, NULL is returned.
 */
Transition*
QualModelPlugin::getTransition (unsigned int index)
{
  return static_cast<Transition*>( mTransitions.get(index) );
}


/*
 * Returns the group object based on its identifier.
 */
Transition*
QualModelPlugin::getTransition (const std::string& sid)
{
  return static_cast<Transition*>( mTransitions.get(sid) );
}


/*
 * Returns the group object based on its identifier.
 */
const Transition* 
QualModelPlugin::getTransition (const std::string& sid) const
{
  return static_cast<const Transition*>( mTransitions.get(sid) );
}


/*
 * Returns the number of Transition objects.
 */
unsigned int 
QualModelPlugin::getNumTransitions() const
{
  return mTransitions.size();
}



/*
 * Adds a copy of the qual object to the list of quals.
 */ 
int
QualModelPlugin::addTransition (const Transition* qual)
{
  if (!qual)
  {
    return LIBSBML_OPERATION_FAILED;
  }    
  else if (!qual->hasRequiredElements())
  {
    return LIBSBML_INVALID_OBJECT;
  }
  else if (getLevel() != qual->getLevel())
  {
    return LIBSBML_LEVEL_MISMATCH;
  }
  else if (getVersion() != qual->getVersion())
  {
    return LIBSBML_VERSION_MISMATCH;
  }
  else if (getPackageVersion() != qual->getPackageVersion())
  {
    return LIBSBML_PKG_VERSION_MISMATCH;
  }
  else
  {
    mTransitions.append(qual);
  }

  return LIBSBML_OPERATION_SUCCESS;

}


/*
 * Creates a new qual object and adds it to the list of qual objects.
 * A reference to the newly created object is returned.
 */
Transition*
QualModelPlugin::createTransition ()
{
  Transition* g = 0;

  try
  {  
    QUAL_CREATE_NS(qualns, getSBMLNamespaces());
    g = new Transition(qualns);
  }
  catch(...)
  {
    /* 
     * NULL will be returned if the mSBMLNS is invalid (basically this
     * should not happen) or some exception is thrown (e.g. std::bad_alloc)
     *
     * (Maybe this should be changed so that caller can detect what kind 
     *  of error happened in this function.)
     */
  }

  if (g) mTransitions.appendAndOwn(g);

  return g;
}


/*
 * Removes the nth Transition object from this Model object and
 * returns a pointer to it.
 */
Transition* 
QualModelPlugin::removeTransition (unsigned int n)
{
  return static_cast<Transition*>(mTransitions.remove(n));
}


/*
 * Removes the Transition object with the given id attribute from 
 * this plugin object and returns a pointer to it.
 */
Transition* 
QualModelPlugin::removeTransition (const std::string& sid)
{
  return static_cast<Transition*>(mTransitions.remove(sid));
}


/*
 * Sets the parent SBMLDocument of this SBML object.
 *
 * @param d the SBMLDocument object to use
 */
void 
QualModelPlugin::setSBMLDocument (SBMLDocument* d)
{
  SBasePlugin::setSBMLDocument(d);

  mQualitativeSpecies.setSBMLDocument(d);  
  mTransitions.setSBMLDocument(d);  
}


/*
 * Sets the parent SBML object of this plugin object to
 * this object and child elements (if any).
 * (Creates a child-parent relationship by this plugin object)
 */
void
QualModelPlugin::connectToParent (SBase* sbase)
{
  SBasePlugin::connectToParent(sbase);

  mQualitativeSpecies.connectToParent(sbase);
  mTransitions.connectToParent(sbase);
}


/*
 * Enables/Disables the given package with child elements in this plugin
 * object (if any).
 */
void
QualModelPlugin::enablePackageInternal(const std::string& pkgURI,
                                        const std::string& pkgPrefix, bool flag)
{
  mQualitativeSpecies.enablePackageInternal(pkgURI,pkgPrefix,flag);
  mTransitions.enablePackageInternal(pkgURI,pkgPrefix,flag);
}

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
