#
# @file    TestCompartmentType.rb
# @brief   CompartmentTypeType unit tests
#
# @author  Akiya Jouraku (Ruby conversion)
# @author  Sarah Keating 
#
# $Id:$
# $HeadURL:$
#
# This test file was converted from src/sbml/test/TestCompartmentType.c
# with the help of conversion sciprt (ctest_converter.pl).
#
#<!---------------------------------------------------------------------------
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2008 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#--------------------------------------------------------------------------->*/
require 'test/unit'
require 'libSBML'

class TestCompartmentType < Test::Unit::TestCase

  def setup
    @@ct = LibSBML::CompartmentType.new()
    if (@@ct == nil)
    end
  end

  def teardown
    @@ct = nil
  end

  def test_CompartmentType_create
    assert( @@ct.getTypeCode() == LibSBML::SBML_COMPARTMENT_TYPE )
    assert( @@ct.getMetaId() == "" )
    assert( @@ct.getNotes() == nil )
    assert( @@ct.getAnnotation() == nil )
    assert( @@ct.getId() == "" )
    assert( @@ct.getName() == "" )
    assert_equal false, @@ct.isSetId()
    assert_equal false, @@ct.isSetName()
  end

  def test_CompartmentType_createWith
    c = LibSBML::CompartmentType.new("A", "")
    assert( c.getTypeCode() == LibSBML::SBML_COMPARTMENT_TYPE )
    assert( c.getMetaId() == "" )
    assert( c.getNotes() == nil )
    assert( c.getAnnotation() == nil )
    assert( c.getName() == "" )
    assert ((  "A"      == c.getId() ))
    assert_equal true, c.isSetId()
    assert_equal false, c.isSetName()
    c = nil
  end

  def test_CompartmentType_createWithLevelVersionAndNamespace
    xmlns = LibSBML::XMLNamespaces.new()
    xmlns.add( "http://www.sbml.org", "sbml")
    object = LibSBML::CompartmentType.new(1,1,xmlns)
    assert( object.getTypeCode() == LibSBML::SBML_COMPARTMENT_TYPE )
    assert( object.getMetaId() == "" )
    assert( object.getNotes() == nil )
    assert( object.getAnnotation() == nil )
    assert( object.getLevel() == 1 )
    assert( object.getVersion() == 1 )
    assert( object.getNamespaces() != "" )
    assert( object.getNamespaces().getLength() == 1 )
    object = nil
  end

  def test_CompartmentType_free_NULL
  end

  def test_CompartmentType_setId
    id =  "mitochondria";
    @@ct.setId(id)
    assert (( id == @@ct.getId() ))
    assert_equal true, @@ct.isSetId()
    if (@@ct.getId() == id)
    end
    @@ct.setId(@@ct.getId())
    assert (( id == @@ct.getId() ))
    @@ct.setId("")
    assert_equal false, @@ct.isSetId()
    if (@@ct.getId() != nil)
    end
  end

  def test_CompartmentType_setName
    name =  "My Favorite Factory";
    @@ct.setName(name)
    assert (( name == @@ct.getName() ))
    assert_equal true, @@ct.isSetName()
    if (@@ct.getName() == name)
    end
    @@ct.setName(@@ct.getName())
    assert (( name == @@ct.getName() ))
    @@ct.setName("")
    assert_equal false, @@ct.isSetName()
    if (@@ct.getName() != nil)
    end
  end

  def test_CompartmentType_unsetName
    @@ct.setName( "name")
    assert ((  "name"      == @@ct.getName() ))
    assert_equal true, @@ct.isSetName()
    @@ct.unsetName()
    assert_equal false, @@ct.isSetName()
  end

end
