///  @file    TestXMLOutputStream.cs
///  @brief   XMLOutputStream unit tests
///  @author  Frank Bergmann (Csharp conversion)
///  @author  Akiya Jouraku (Csharp conversion)
///  @author  Sarah Keating 
/// 
///  $Id$
///  $HeadURL$
/// 
///  ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
/// 
///  DO NOT EDIT THIS FILE.
/// 
///  This file was generated automatically by converting the file located at
///  src/xml/test/TestXMLOutputStream.c
///  using the conversion program dev/utilities/translateTests/translateTests.pl.
///  Any changes made here will be lost the next time the file is regenerated.
/// 
///  -----------------------------------------------------------------------------
///  This file is part of libSBML.  Please visit http://sbml.org for more
///  information about SBML, and the latest version of libSBML.
/// 
///  Copyright 2005-2010 California Institute of Technology.
///  Copyright 2002-2005 California Institute of Technology and
///                      Japan Science and Technology Corporation.
///  
///  This library is free software; you can redistribute it and/or modify it
///  under the terms of the GNU Lesser General Public License as published by
///  the Free Software Foundation.  A copy of the license agreement is provided
///  in the file named "LICENSE.txt" included with this software distribution
///  and also available online as http://sbml.org/software/libsbml/license.html
///  -----------------------------------------------------------------------------


namespace LibSBMLCSTest {

  using libsbml;

  using System;

  using System.IO;

  public class TestXMLOutputStream {
    public class AssertionError : System.Exception 
    {
      public AssertionError() : base()
      {
        
      }
    }


    static void assertTrue(bool condition)
    {
      if (condition == true)
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertEquals(object a, object b)
    {
      if ( (a == null) && (b == null) )
      {
        return;
      }
      else if ( (a == null) || (b == null) )
      {
        throw new AssertionError();
      }
      else if (a.Equals(b))
      {
        return;
      }
  
      throw new AssertionError();
    }

    static void assertNotEquals(object a, object b)
    {
      if ( (a == null) && (b == null) )
      {
        throw new AssertionError();
      }
      else if ( (a == null) || (b == null) )
      {
        return;
      }
      else if (a.Equals(b))
      {
        throw new AssertionError();
      }
    }

    static void assertEquals(bool a, bool b)
    {
      if ( a == b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertNotEquals(bool a, bool b)
    {
      if ( a != b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertEquals(int a, int b)
    {
      if ( a == b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertNotEquals(int a, int b)
    {
      if ( a != b )
      {
        return;
      }
      throw new AssertionError();
    }


    public void test_XMLOutputStream_CharacterReference()
    {
      OStringStream oss = new OStringStream();
      XMLOutputStream stream = new  XMLOutputStream(oss,"",false);
      stream.startElement( "testcr");
      stream.writeAttribute( "chars",    "one"     );
      stream.writeAttribute( "amp",      "&"       );
      stream.writeAttribute( "deccr",    "&#0168;"  );
      stream.writeAttribute( "hexcr",    "&#x00a8;");
      stream.writeAttribute( "lhexcr",   "&#x00A8;");
      stream.writeAttribute( "nodeccr1", "&#01688"  );
      stream.writeAttribute( "nodeccr2", "&#;"     );
      stream.writeAttribute( "nodeccr3", "&#00a8;" );
      stream.writeAttribute( "nodeccr4", "&#00A8;" );
      stream.writeAttribute( "nohexcr1", "&#x;"    );
      stream.writeAttribute( "nohexcr2", "&#xABCD" );
      stream.endElement( "testcr");
      string expected =  "<testcr chars=\"one\" amp=\"&amp;\" deccr=\"&#0168;\" hexcr=\"&#x00a8;\" lhexcr=\"&#x00A8;\" nodeccr1=\"&amp;#01688\" nodeccr2=\"&amp;#;\" nodeccr3=\"&amp;#00a8;\" nodeccr4=\"&amp;#00A8;\" nohexcr1=\"&amp;#x;\" nohexcr2=\"&amp;#xABCD\"/>";
      string s = oss.str();
      assertTrue(( expected == s ));
      stream = null;
    }

    public void test_XMLOutputStream_Elements()
    {
      double d = 2.4;
      long l = 123456789;
      long ui = 5;
      int i = -3;
      OStringStream oss = new OStringStream();
      XMLOutputStream stream = new  XMLOutputStream(oss,"",false);
      stream.startElement( "fred");
      stream.writeAttribute( "chars", "two");
      stream.writeAttribute( "bool",true);
      stream.writeAttribute( "double",d);
      stream.writeAttribute( "long",l);
      stream.writeAttribute( "uint",ui);
      stream.writeAttribute( "int",i);
      stream.endElement( "fred");
      string expected =  "<fred chars=\"two\" bool=\"true\" double=\"2.4\" long=\"123456789\" uint=\"5\" int=\"-3\"/>";
      string s = oss.str();
      assertTrue(( expected == s ));
      stream = null;
    }

    public void test_XMLOutputStream_PredefinedEntity()
    {
      OStringStream oss = new OStringStream();
      XMLOutputStream stream = new  XMLOutputStream(oss,"",false);
      stream.startElement( "testpde");
      stream.writeAttribute( "amp",     "&"     );
      stream.writeAttribute( "apos",    "'"     );
      stream.writeAttribute( "gt",      ">"     );
      stream.writeAttribute( "lt",      "<"     );
      stream.writeAttribute( "quot",    "\""    );
      stream.writeAttribute( "pdeamp",  "&amp;" );
      stream.writeAttribute( "pdeapos", "&apos;");
      stream.writeAttribute( "pdegt",   "&gt;"  );
      stream.writeAttribute( "pdelt",   "&lt;"  );
      stream.writeAttribute( "pdequot", "&quot;");
      stream.endElement( "testpde");
      string expected =  "<testpde amp=\"&amp;\" apos=\"&apos;\" gt=\"&gt;\" lt=\"&lt;\" quot=\"&quot;\" pdeamp=\"&amp;\" pdeapos=\"&apos;\" pdegt=\"&gt;\" pdelt=\"&lt;\" pdequot=\"&quot;\"/>";
      string s = oss.str();
      assertTrue(( expected == s ));
      stream = null;
    }

    public void test_XMLOutputStream_createStdout()
    {
      XMLOutputStream stream = new  XMLOutputStream(libsbml.cout,"UTF-8",false);
      assertTrue( stream != null );
      stream = null;
    }

    public void test_XMLOutputStream_createStdoutWithProgramInfo()
    {
      XMLOutputStream stream = new  XMLOutputStream(libsbml.cout,"UTF-8",false, "foo", "bar");
      assertTrue( stream != null );
      stream = null;
    }

    public void test_XMLOutputStream_createString()
    {
      string expected =  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
      OStringStream oss = new OStringStream();
      XMLOutputStream stream = new  XMLOutputStream(oss,"UTF-8",true);
      assertTrue( stream != null );
      string str = oss.str();
      assertTrue(( expected == str ));
      stream = null;
    }

    public void test_XMLOutputStream_createStringWithProgramInfo()
    {
      string expected =  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
      OStringStream oss = new OStringStream();
      XMLOutputStream stream = new  XMLOutputStream(oss,"UTF-8",true, "", "");
      assertTrue( stream != null );
      string str = oss.str();
      assertTrue(( expected == str ));
      stream = null;
    }

    public void test_XMLOutputStream_startEnd()
    {
      OStringStream oss = new OStringStream();
      XMLOutputStream stream = new  XMLOutputStream(oss,"",false);
      assertTrue( stream != null );
      stream.startEndElement( "id");
      string str = oss.str();
      assertTrue((  "<id/>" == str ));
      stream = null;
    }

  }
}
