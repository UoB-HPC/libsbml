#
# @file    TestSBMLNamespaces.py
# @brief   SBMLNamespaces unit tests
#
# @author  Akiya Jouraku (Python conversion)
# @author  Sarah Keating 
#
# $Id$
# $HeadURL$
#
# This test file was converted from src/sbml/test/TestSBMLNamespaces.cpp
# with the help of conversion sciprt (ctest_converter.pl).
#
#<!---------------------------------------------------------------------------
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2009 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#--------------------------------------------------------------------------->*/
import sys
import unittest
import libsbml

class TestSBMLNamespaces(unittest.TestCase):


  def test_SBMLNamespaces_L1V1(self):
    sbml = libsbml.SBMLNamespaces(1,1)
    self.assert_( sbml.getLevel() == 1 )
    self.assert_( sbml.getVersion() == 1 )
    ns = sbml.getNamespaces()
    self.assert_( ns.getLength() == 1 )
    self.assert_( ns.getURI(0) ==  "http://www.sbml.org/sbml/level1" )
    self.assert_( ns.getPrefix(0) ==  "sbml" )
    sbml = None
    pass  

  def test_SBMLNamespaces_L1V2(self):
    sbml = libsbml.SBMLNamespaces(1,2)
    self.assert_( sbml.getLevel() == 1 )
    self.assert_( sbml.getVersion() == 2 )
    ns = sbml.getNamespaces()
    self.assert_( ns.getLength() == 1 )
    self.assert_( ns.getURI(0) ==  "http://www.sbml.org/sbml/level1" )
    self.assert_( ns.getPrefix(0) ==  "sbml" )
    sbml = None
    pass  

  def test_SBMLNamespaces_L2V1(self):
    sbml = libsbml.SBMLNamespaces(2,1)
    self.assert_( sbml.getLevel() == 2 )
    self.assert_( sbml.getVersion() == 1 )
    ns = sbml.getNamespaces()
    self.assert_( ns.getLength() == 1 )
    self.assert_( ns.getURI(0) ==  "http://www.sbml.org/sbml/level2" )
    self.assert_( ns.getPrefix(0) ==  "sbml" )
    sbml = None
    pass  

  def test_SBMLNamespaces_L2V2(self):
    sbml = libsbml.SBMLNamespaces(2,2)
    self.assert_( sbml.getLevel() == 2 )
    self.assert_( sbml.getVersion() == 2 )
    ns = sbml.getNamespaces()
    self.assert_( ns.getLength() == 1 )
    self.assert_( ns.getURI(0) ==  "http://www.sbml.org/sbml/level2/version2" )
    self.assert_( ns.getPrefix(0) ==  "sbml" )
    sbml = None
    pass  

  def test_SBMLNamespaces_L2V3(self):
    sbml = libsbml.SBMLNamespaces(2,3)
    self.assert_( sbml.getLevel() == 2 )
    self.assert_( sbml.getVersion() == 3 )
    ns = sbml.getNamespaces()
    self.assert_( ns.getLength() == 1 )
    self.assert_( ns.getURI(0) ==  "http://www.sbml.org/sbml/level2/version3" )
    self.assert_( ns.getPrefix(0) ==  "sbml" )
    sbml = None
    pass  

  def test_SBMLNamespaces_L2V4(self):
    sbml = libsbml.SBMLNamespaces(2,4)
    self.assert_( sbml.getLevel() == 2 )
    self.assert_( sbml.getVersion() == 4 )
    ns = sbml.getNamespaces()
    self.assert_( ns.getLength() == 1 )
    self.assert_( ns.getURI(0) ==  "http://www.sbml.org/sbml/level2/version4" )
    self.assert_( ns.getPrefix(0) ==  "sbml" )
    sbml = None
    pass  

  def test_SBMLNamespaces_getURI(self):
    self.assert_( libsbml.SBMLNamespaces.getSBMLNamespaceURI(1,1) ==                              "http://www.sbml.org/sbml/level1" )
    self.assert_( libsbml.SBMLNamespaces.getSBMLNamespaceURI(1,2) ==                              "http://www.sbml.org/sbml/level1" )
    self.assert_( libsbml.SBMLNamespaces.getSBMLNamespaceURI(2,1) ==                              "http://www.sbml.org/sbml/level2" )
    self.assert_( libsbml.SBMLNamespaces.getSBMLNamespaceURI(2,2) ==                              "http://www.sbml.org/sbml/level2/version2" )
    self.assert_( libsbml.SBMLNamespaces.getSBMLNamespaceURI(2,3) ==                              "http://www.sbml.org/sbml/level2/version3" )
    self.assert_( libsbml.SBMLNamespaces.getSBMLNamespaceURI(2,4) ==                              "http://www.sbml.org/sbml/level2/version4" )
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestSBMLNamespaces))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
