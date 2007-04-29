/**
 * @file    XMLNode.h
 * @brief   A node in an XML document tree
 * @author  Ben Bornstein
 *
 * $Id$
 * $Source$
 *
 *<!---------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright 2005-2007 California Institute of Technology.
 * Copyright 2002-2005 California Institute of Technology and
 *                     Japan Science and Technology Corporation.
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 *------------------------------------------------------------------------- -->
 * @class XMLNode.
 * @brief Implementation of %XMLNode construct.
 */


#ifndef XMLNode_h
#define XMLNode_h

#include <sbml/xml/XMLExtern.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/common/sbmlfwd.h>


#ifdef __cplusplus

#include <vector>


class XMLInputStream;
class XMLOutputStream;


class LIBLAX_EXTERN XMLNode : public XMLToken
{
public:

  /**
   * Creates a new empty XMLNode with no children.
   */
  XMLNode ();

  /**
   * Creates a new XMLNode by copying token.
   *
   * @param token XMLToken to be copied to XMLNode
   */
  XMLNode (const XMLToken& token);

  /**
   * Creates a new XMLNode by reading XMLTokens from stream.  
   *
   * The stream must
   * be positioned on a start element (stream.peek().isStart() == true) and
   * will be read until the matching end element is found.
   *
   * @param stream XMLInputStream from which XMLNode is to be created.
   */
  XMLNode (XMLInputStream& stream);

  /**
   * Destroys this XMLNode.
   */
  virtual ~XMLNode ();
  
  /**
   * Copy constructor; creates a copy of this XMLNode.
   */
  XMLNode(const XMLNode& orig);


  /**
   * Assignment operator for XMLNode.
   */
  XMLNode& operator=(const XMLNode& orig);

  /**
   * Creates and returns a deep copy of this XMLNode.
   * 
   * @return a (deep) copy of this XMLNode.
   */
  XMLNode* clone () const;


  /**
   * Adds a copy of child node to this XMLNode.
   *
   * @param node XMLNode to be added as child.
   */
  void addChild (const XMLNode& node);

  /**
   * Returns the nth child of this XMLNode.
   *
   * @return the nth child of this XMLNode.
   */
  const XMLNode& getChild (unsigned int n) const;

  /**
   * Returns the number of children for this XMLNode.
   *
   * @return the number of children for this XMLNode.
   */
  unsigned int getNumChildren () const;

  /**
   * Writes this XMLNode and its children to stream.
   *
   * @param stream XMLOutputStream, stream to which this XMLNode
   * is to be written.
   */
  void write (XMLOutputStream& stream) const;


#ifndef SWIG

  /**
   * Inserts this XMLNode and its children into stream.
   *
   * @param stream XMLOutputStream, stream to which the XMLNode
   * is to be written.
   * @param node XMLNode, node to be written to stream.
   *
   * @return the stream with the node inserted.
   */
  LIBLAX_EXTERN
  friend
  XMLOutputStream& operator<< (XMLOutputStream& stream, const XMLNode& node);

#endif  /* !SWIG */


protected:
  /** @cond doxygen-libsbml-internal */

  std::vector<XMLNode> mChildren;
  /** @endcond doxygen-libsbml-internal */
};

#endif  /* __cplusplus */


#ifndef SWIG

BEGIN_C_DECLS
/*-----------------------------------------------------------------------------
 * See the .cpp file for the documentation of the following functions.
 *---------------------------------------------------------------------------*/


/**
 * 
 **/
LIBLAX_EXTERN
XMLNode_t *
XMLNode_create (void);


/**
 * 
 **/
LIBLAX_EXTERN
XMLNode_t *
XMLNode_createFromToken (const XMLToken_t *token);


/**
 * 
 **/
LIBLAX_EXTERN
void
XMLNode_free (XMLNode_t *node);


/**
 * 
 **/
LIBLAX_EXTERN
void
XMLNode_addChild (XMLNode_t *node, const XMLNode_t *child);


/**
 * 
 **/
LIBLAX_EXTERN
const char *
XMLNode_getName (const XMLNode_t *node);


/**
 * 
 **/
LIBLAX_EXTERN
const char *
XMLNode_getPrefix (const XMLNode_t *node);


/**
 * 
 **/
LIBLAX_EXTERN
const char *
XMLNode_getURI (const XMLNode_t *node);


/**
 * 
 **/
LIBLAX_EXTERN
const XMLNode_t *
XMLNode_getChild (const XMLNode_t *node, const int n);


/**
 * 
 **/
LIBLAX_EXTERN
unsigned int
XMLNode_getNumChildren (const XMLNode_t *node);



END_C_DECLS

#endif  /* !SWIG */
#endif  /* XMLNode_h */
