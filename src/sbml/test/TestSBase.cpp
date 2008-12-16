/**
 * \file    TestSBase.cpp
 * \brief   SBase unit tests
 * \author  Ben Bornstein
 *
 * $Id$
 * $HeadURL$
 */
/* Copyright 2002 California Institute of Technology and
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
 *     The Systems Biology Markup Language Development Group
 *     ERATO Kitano Symbiotic Systems Project
 *     Control and Dynamical Systems, MC 107-81
 *     California Institute of Technology
 *     Pasadena, CA, 91125, USA
 *
 *     http://www.cds.caltech.edu/erato
 *     mailto:sbml-team@caltech.edu
 *
 * Contributor(s):
 */


#include <sbml/common/common.h>
#include <sbml/common/extern.h>

#include <sbml/SBase.h>
#include <sbml/Model.h>
#include <sbml/annotation/CVTerm.h>

#include <check.h>


static SBase *S;


BEGIN_C_DECLS


void
SBaseTest_setup (void)
{
  S = new(std::nothrow) Model;

  if (S == NULL)
  {
    fail("'new(std::nothrow) SBase;' returned a NULL pointer.");
  }

}


void
SBaseTest_teardown (void)
{
  delete S;
}


START_TEST (test_SBase_setMetaId)
{
  char *metaid = "x12345";


  SBase_setMetaId(S, metaid);

  fail_unless( !strcmp(SBase_getMetaId(S), metaid), NULL );
  fail_unless( SBase_isSetMetaId(S)      , NULL );

  if (SBase_getMetaId(S) == metaid)
  {
    fail("SBase_setMetaId(...) did not make a copy of string.");
  }

  /* Reflexive case (pathological) */
  SBase_setMetaId(S, SBase_getMetaId(S));
  fail_unless( !strcmp(SBase_getMetaId(S), metaid), NULL );

  SBase_setMetaId(S, NULL);
  fail_unless( !SBase_isSetMetaId(S), NULL );

  if (SBase_getMetaId(S) != NULL)
  {
    fail("SBase_setMetaId(S, NULL) did not clear string.");
  }
}
END_TEST


START_TEST (test_SBase_setNotes)
{
  XMLToken_t *token;
  XMLNode_t *node;

  token = XMLToken_createWithText("This is a test note");
  node = XMLNode_createFromToken(token);


  SBase_setNotes(S, node);

  fail_unless(SBase_isSetNotes(S) == 1);

  if (SBase_getNotes(S) == node)
  {
    fail("SBase_setNotes(...) did not make a copy of node.");
  }
  XMLNode_t *t1 = SBase_getNotes(S);

  fail_unless(XMLNode_getNumChildren(t1) == 1);
  fail_unless(!strcmp(XMLNode_getCharacters(XMLNode_getChild(t1,0)), "This is a test note"));


  /* Reflexive case (pathological)  */
  SBase_setNotes(S, SBase_getNotes(S));
  t1 = SBase_getNotes(S);
  fail_unless(XMLNode_getNumChildren(t1) == 1);
  const char * chars = XMLNode_getCharacters(XMLNode_getChild(t1,0));
  fail_unless(!strcmp(chars, "This is a test note"));

  SBase_setNotes(S, NULL);
  fail_unless(SBase_isSetNotes(S) == 0 );

  if (SBase_getNotes(S) != NULL)
  {
    fail("SBase_setNotes(S, NULL) did not clear string.");
  }

  SBase_setNotes(S, node);

  fail_unless(SBase_isSetNotes(S) == 1);

  XMLNode_free(node);
}
END_TEST


START_TEST (test_SBase_setAnnotation)
{
  XMLToken_t *token;
  XMLNode_t *node;

  token = XMLToken_createWithText("This is a test note");
  node = XMLNode_createFromToken(token);


  SBase_setAnnotation(S, node);

  fail_unless(SBase_isSetAnnotation(S) == 1);

  XMLNode_t *t1 = SBase_getAnnotation(S);

  fail_unless(XMLNode_getNumChildren(t1) == 1);
  fail_unless(!strcmp(XMLNode_getCharacters(XMLNode_getChild(t1,0)), "This is a test note"));

  if (SBase_getAnnotation(S) == node)
  {
    fail("SBase_setAnnotation(...) did not make a copy of node.");
  }

  /* Reflexive case (pathological) */
  SBase_setAnnotation(S, SBase_getAnnotation(S));
  fail_unless(!strcmp(XMLNode_getCharacters(XMLNode_getChild(SBase_getAnnotation(S),0)), "This is a test note"));

  SBase_setAnnotation(S, NULL);
  fail_unless(SBase_isSetAnnotation(S) == 0 );

  if (SBase_getAnnotation(S) != NULL)
  {
    fail("SBase_setAnnotation(S, NULL) did not clear string.");
  }

  SBase_setAnnotation(S, node);

  fail_unless(SBase_isSetAnnotation(S) == 1);

  SBase_unsetAnnotation(S);

  fail_unless(SBase_isSetAnnotation(S) == 0);
}
END_TEST

START_TEST (test_SBase_setNotesString)
{
  char * notes = "This is a test note";
  char * taggednotes = "<notes>This is a test note</notes>";

  SBase_setNotesString(S, notes);

  fail_unless(SBase_isSetNotes(S) == 1);

  if (strcmp(SBase_getNotesString(S), taggednotes))
  {
    fail("SBase_setNotesString(...) did not make a copy of node.");
  }
  XMLNode_t *t1 = SBase_getNotes(S);
  fail_unless(XMLNode_getNumChildren(t1) == 1);

  const XMLNode_t *t2 = XMLNode_getChild(t1,0);
  fail_unless(!strcmp(XMLNode_getCharacters(XMLNode_getChild(t2,0)), "This is a test note"));


  /* Reflexive case (pathological)  */
  SBase_setNotesString(S, SBase_getNotesString(S));
  t1 = SBase_getNotes(S);
  fail_unless(XMLNode_getNumChildren(t1) == 1);
  const char * chars = SBase_getNotesString(S);
  fail_unless(!strcmp(chars, taggednotes));

  SBase_setNotesString(S, "");
  fail_unless(SBase_isSetNotes(S) == 0 );

  if (SBase_getNotesString(S) != NULL)
  {
    fail("SBase_getNotesString(S, "") did not clear string.");
  }

  SBase_setNotesString(S, taggednotes);

  fail_unless(SBase_isSetNotes(S) == 1);

  if (strcmp(SBase_getNotesString(S), taggednotes))
  {
    fail("SBase_setNotesString(...) did not make a copy of node.");
  }
  t1 = SBase_getNotes(S);
  fail_unless(XMLNode_getNumChildren(t1) == 1);

  t2 = XMLNode_getChild(t1,0);
  fail_unless(!strcmp(XMLNode_getCharacters(t2), "This is a test note"));

}
END_TEST


START_TEST (test_SBase_setAnnotationString)
{
  char * annotation = "This is a test note";
  char * taggedannotation = "<annotation>This is a test note</annotation>";

  SBase_setAnnotationString(S, annotation);

  fail_unless(SBase_isSetAnnotation(S) == 1);

  if (strcmp(SBase_getAnnotationString(S), taggedannotation))
  {
    fail("SBase_setAnnotationString(...) did not make a copy of node.");
  }
  XMLNode_t *t1 = SBase_getAnnotation(S);
  fail_unless(XMLNode_getNumChildren(t1) == 1);

  const XMLNode_t *t2 = XMLNode_getChild(t1,0);
  fail_unless(!strcmp(XMLNode_getCharacters(XMLNode_getChild(t2,0)), "This is a test note"));


  /* Reflexive case (pathological)  */
  SBase_setAnnotationString(S, SBase_getAnnotationString(S));
  t1 = SBase_getAnnotation(S);
  fail_unless(XMLNode_getNumChildren(t1) == 1);
  const char * chars = SBase_getAnnotationString(S);
  fail_unless(!strcmp(chars, taggedannotation));

  SBase_setAnnotationString(S, "");
  fail_unless(SBase_isSetAnnotation(S) == 0 );

  if (SBase_getAnnotationString(S) != NULL)
  {
    fail("SBase_getAnnotationString(S, "") did not clear string.");
  }

  SBase_setAnnotationString(S, taggedannotation);

  fail_unless(SBase_isSetAnnotation(S) == 1);

  if (strcmp(SBase_getAnnotationString(S), taggedannotation))
  {
    fail("SBase_setAnnotationString(...) did not make a copy of node.");
  }
  t1 = SBase_getAnnotation(S);
  fail_unless(XMLNode_getNumChildren(t1) == 1);

  t2 = XMLNode_getChild(t1,0);
  fail_unless(!strcmp(XMLNode_getCharacters(t2), "This is a test note"));
}
END_TEST


START_TEST (test_SBase_appendNotes)
{ // add a p tag to a p tag
  XMLToken_t *token;
  XMLNode_t *node;
  XMLToken_t *token1;
  XMLNode_t *node1;
  XMLNode_t * node2;
  XMLTriple_t *triple = XMLTriple_createWith("p", "", "");
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLToken_t *token4 = XMLToken_createWithText("This is my text");
  XMLNode_t *node4 = XMLNode_createFromToken(token4);
  XMLToken_t *token5 = XMLToken_createWithText("This is additional text");
  XMLNode_t *node5 = XMLNode_createFromToken(token5);

  token = XMLToken_createWithTripleAttrNS(triple, att, ns);
  node = XMLNode_createFromToken(token);
  XMLNode_addChild(node, node4);

  SBase_setNotes(S, node);

  fail_unless(SBase_isSetNotes(S) == 1);

  token1 = XMLToken_createWithTripleAttrNS(triple, att, ns);
  node1 = XMLNode_createFromToken(token1);
  XMLNode_addChild(node1, node5);
  
  SBase_appendNotes(S, node1);

  fail_unless(SBase_isSetNotes(S) == 1);

  node2 = SBase_getNotes(S);

  fail_unless(XMLNode_getNumChildren(node2) == 2);
  fail_unless(!strcmp(XMLNode_getName(XMLNode_getChild(node2, 0)), "p"));
  fail_unless(XMLNode_getNumChildren(XMLNode_getChild(node2, 0)) == 1);
  fail_unless(!strcmp(XMLNode_getName(XMLNode_getChild(node2, 1)), "p"));
  fail_unless(XMLNode_getNumChildren(XMLNode_getChild(node2, 1)) == 1);

  const char * chars1 = XMLNode_getCharacters(XMLNode_getChild(
    XMLNode_getChild(node2, 0), 0));
  const char * chars2 = XMLNode_getCharacters(XMLNode_getChild(
    XMLNode_getChild(node2, 1), 0));

  fail_unless(!strcmp(chars1, "This is my text"));
  fail_unless(!strcmp(chars2, "This is additional text"));

  XMLNode_free(node);
  XMLNode_free(node1);
}
END_TEST


START_TEST (test_SBase_appendNotes1)
{
  // add a html tag to an html tag
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLTriple_t *html_triple = XMLTriple_createWith("html", "", "");
  XMLTriple_t *head_triple = XMLTriple_createWith("head", "", "");
  XMLTriple_t *body_triple = XMLTriple_createWith("body", "", "");
  XMLTriple_t *p_triple = XMLTriple_createWith("p", "", "");
  XMLToken_t *html_token = XMLToken_createWithTripleAttrNS(html_triple, att, ns);
  XMLToken_t *head_token = XMLToken_createWithTripleAttr(head_triple, att);
  XMLToken_t *body_token = XMLToken_createWithTripleAttr(body_triple, att);
  XMLToken_t *p_token = XMLToken_createWithTripleAttr(p_triple, att);
  XMLToken_t *text_token = XMLToken_createWithText("This is my text");
  XMLNode_t *html_node = XMLNode_createFromToken(html_token);
  XMLNode_t *head_node = XMLNode_createFromToken(head_token);
  XMLNode_t *body_node = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node = XMLNode_createFromToken(text_token);

  XMLToken_t *text_token1 = XMLToken_createWithText("This is more text");
  XMLNode_t *html_node1 = XMLNode_createFromToken(html_token);
  XMLNode_t *head_node1 = XMLNode_createFromToken(head_token);
  XMLNode_t *body_node1 = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node1 = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node1 = XMLNode_createFromToken(text_token1);

  XMLNode_t * notes;
  const XMLNode_t *child, *child1;

  XMLNode_addChild(p_node, text_node);
  XMLNode_addChild(body_node, p_node);
  XMLNode_addChild(html_node, head_node);
  XMLNode_addChild(html_node, body_node);

  XMLNode_addChild(p_node1, text_node1);
  XMLNode_addChild(body_node1, p_node1);
  XMLNode_addChild(html_node1, head_node1);
  XMLNode_addChild(html_node1, body_node1);

  SBase_setNotes(S, html_node);
  SBase_appendNotes(S, html_node1);

  notes = SBase_getNotes(S);

  fail_unless(!strcmp(XMLNode_getName(notes), "notes"));
  fail_unless(XMLNode_getNumChildren(notes) == 1);

  child = XMLNode_getChild(notes, 0);

  fail_unless(!strcmp(XMLNode_getName(child), "html"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child), "body"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child1 = XMLNode_getChild(child, 0);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is my text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  child1 = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is more text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  XMLAttributes_free(att);
  XMLNamespaces_free(ns);
  XMLTriple_free(html_triple);
  XMLTriple_free(head_triple);
  XMLTriple_free(body_triple);
  XMLTriple_free(p_triple);
  XMLToken_free(html_token);
  XMLToken_free(head_token);
  XMLToken_free(body_token);
  XMLToken_free(p_token);
  XMLToken_free(text_token);
  XMLToken_free(text_token1);
  XMLNode_free(html_node);
  XMLNode_free(head_node);
  XMLNode_free(body_node);
  XMLNode_free(p_node);
  XMLNode_free(text_node);
  XMLNode_free(html_node1);
  XMLNode_free(head_node1);
  XMLNode_free(body_node1);
  XMLNode_free(p_node1);
  XMLNode_free(text_node1);
}
END_TEST


START_TEST (test_SBase_appendNotes2)
{// add a body tag to an html tag
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLTriple_t *html_triple = XMLTriple_createWith("html", "", "");
  XMLTriple_t *head_triple = XMLTriple_createWith("head", "", "");
  XMLTriple_t *body_triple = XMLTriple_createWith("body", "", "");
  XMLTriple_t *p_triple = XMLTriple_createWith("p", "", "");
  XMLToken_t *html_token = XMLToken_createWithTripleAttrNS(html_triple, att, ns);
  XMLToken_t *head_token = XMLToken_createWithTripleAttr(head_triple, att);
  XMLToken_t *body_token = XMLToken_createWithTripleAttr(body_triple, att);
  XMLToken_t *p_token = XMLToken_createWithTripleAttr(p_triple, att);
  XMLToken_t *text_token = XMLToken_createWithText("This is my text");
  XMLNode_t *html_node = XMLNode_createFromToken(html_token);
  XMLNode_t *head_node = XMLNode_createFromToken(head_token);
  XMLNode_t *body_node = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node = XMLNode_createFromToken(text_token);

  XMLToken_t *body_token1 = XMLToken_createWithTripleAttrNS(body_triple, att, ns);
  XMLToken_t *text_token1 = XMLToken_createWithText("This is more text");
  XMLNode_t *body_node1 = XMLNode_createFromToken(body_token1);
  XMLNode_t *p_node1 = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node1 = XMLNode_createFromToken(text_token1);

  XMLNode_t * notes;
  const XMLNode_t *child, *child1;

  XMLNode_addChild(p_node, text_node);
  XMLNode_addChild(body_node, p_node);
  XMLNode_addChild(html_node, head_node);
  XMLNode_addChild(html_node, body_node);

  XMLNode_addChild(p_node1, text_node1);
  XMLNode_addChild(body_node1, p_node1);

  SBase_setNotes(S, html_node);
  SBase_appendNotes(S, body_node1);

  notes = SBase_getNotes(S);

  fail_unless(!strcmp(XMLNode_getName(notes), "notes"));
  fail_unless(XMLNode_getNumChildren(notes) == 1);

  child = XMLNode_getChild(notes, 0);

  fail_unless(!strcmp(XMLNode_getName(child), "html"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child), "body"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child1 = XMLNode_getChild(child, 0);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is my text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  child1 = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is more text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  XMLAttributes_free(att);
  XMLNamespaces_free(ns);
  XMLTriple_free(html_triple);
  XMLTriple_free(head_triple);
  XMLTriple_free(body_triple);
  XMLTriple_free(p_triple);
  XMLToken_free(html_token);
  XMLToken_free(head_token);
  XMLToken_free(body_token);
  XMLToken_free(p_token);
  XMLToken_free(text_token);
  XMLToken_free(text_token1);
  XMLToken_free(body_token1);
  XMLNode_free(html_node);
  XMLNode_free(head_node);
  XMLNode_free(body_node);
  XMLNode_free(p_node);
  XMLNode_free(text_node);
  XMLNode_free(body_node1);
  XMLNode_free(p_node1);
  XMLNode_free(text_node1);
}
END_TEST


START_TEST (test_SBase_appendNotes3)
{
  // add a p tag to an html tag
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLTriple_t *html_triple = XMLTriple_createWith("html", "", "");
  XMLTriple_t *head_triple = XMLTriple_createWith("head", "", "");
  XMLTriple_t *body_triple = XMLTriple_createWith("body", "", "");
  XMLTriple_t *p_triple = XMLTriple_createWith("p", "", "");
  XMLToken_t *html_token = XMLToken_createWithTripleAttrNS(html_triple, att, ns);
  XMLToken_t *head_token = XMLToken_createWithTripleAttr(head_triple, att);
  XMLToken_t *body_token = XMLToken_createWithTripleAttr(body_triple, att);
  XMLToken_t *p_token = XMLToken_createWithTripleAttr(p_triple, att);
  XMLToken_t *text_token = XMLToken_createWithText("This is my text");
  XMLNode_t *html_node = XMLNode_createFromToken(html_token);
  XMLNode_t *head_node = XMLNode_createFromToken(head_token);
  XMLNode_t *body_node = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node = XMLNode_createFromToken(text_token);

  XMLToken_t *p_token1 = XMLToken_createWithTripleAttrNS(p_triple, att, ns);
  XMLToken_t *text_token1 = XMLToken_createWithText("This is more text");
  XMLNode_t *p_node1 = XMLNode_createFromToken(p_token1);
  XMLNode_t *text_node1 = XMLNode_createFromToken(text_token1);

  XMLNode_t * notes;
  const XMLNode_t *child, *child1;

  XMLNode_addChild(p_node, text_node);
  XMLNode_addChild(body_node, p_node);
  XMLNode_addChild(html_node, head_node);
  XMLNode_addChild(html_node, body_node);

  XMLNode_addChild(p_node1, text_node1);

  SBase_setNotes(S, html_node);
  SBase_appendNotes(S, p_node1);

  notes = SBase_getNotes(S);

  fail_unless(!strcmp(XMLNode_getName(notes), "notes"));
  fail_unless(XMLNode_getNumChildren(notes) == 1);

  child = XMLNode_getChild(notes, 0);

  fail_unless(!strcmp(XMLNode_getName(child), "html"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child), "body"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child1 = XMLNode_getChild(child, 0);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is my text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  child1 = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is more text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  XMLAttributes_free(att);
  XMLNamespaces_free(ns);
  XMLTriple_free(html_triple);
  XMLTriple_free(head_triple);
  XMLTriple_free(body_triple);
  XMLTriple_free(p_triple);
  XMLToken_free(html_token);
  XMLToken_free(head_token);
  XMLToken_free(body_token);
  XMLToken_free(p_token);
  XMLToken_free(text_token);
  XMLToken_free(text_token1);
  XMLToken_free(p_token1);
  XMLNode_free(html_node);
  XMLNode_free(head_node);
  XMLNode_free(body_node);
  XMLNode_free(p_node);
  XMLNode_free(text_node);
  XMLNode_free(p_node1);
  XMLNode_free(text_node1);
}
END_TEST


START_TEST (test_SBase_appendNotes4)
{
  // add a html tag to a body tag
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLTriple_t *html_triple = XMLTriple_createWith("html", "", "");
  XMLTriple_t *head_triple = XMLTriple_createWith("head", "", "");
  XMLTriple_t *body_triple = XMLTriple_createWith("body", "", "");
  XMLTriple_t *p_triple = XMLTriple_createWith("p", "", "");
  XMLToken_t *html_token = XMLToken_createWithTripleAttrNS(html_triple, att, ns);
  XMLToken_t *head_token = XMLToken_createWithTripleAttr(head_triple, att);
  XMLToken_t *body_token = XMLToken_createWithTripleAttr(body_triple, att);
  XMLToken_t *p_token = XMLToken_createWithTripleAttr(p_triple, att);
  XMLToken_t *body_token1 = XMLToken_createWithTripleAttrNS(body_triple, att, ns);
  XMLToken_t *text_token = XMLToken_createWithText("This is my text");
  XMLNode_t *body_node = XMLNode_createFromToken(body_token1);
  XMLNode_t *p_node = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node = XMLNode_createFromToken(text_token);

  XMLToken_t *text_token1 = XMLToken_createWithText("This is more text");
  XMLNode_t *html_node1 = XMLNode_createFromToken(html_token);
  XMLNode_t *head_node1 = XMLNode_createFromToken(head_token);
  XMLNode_t *body_node1 = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node1 = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node1 = XMLNode_createFromToken(text_token1);

  XMLNode_t * notes;
  const XMLNode_t *child, *child1;

  XMLNode_addChild(p_node, text_node);
  XMLNode_addChild(body_node, p_node);

  XMLNode_addChild(p_node1, text_node1);
  XMLNode_addChild(body_node1, p_node1);
  XMLNode_addChild(html_node1, head_node1);
  XMLNode_addChild(html_node1, body_node1);

  SBase_setNotes(S, body_node);
  SBase_appendNotes(S, html_node1);

  notes = SBase_getNotes(S);

  fail_unless(!strcmp(XMLNode_getName(notes), "notes"));
  fail_unless(XMLNode_getNumChildren(notes) == 1);

  child = XMLNode_getChild(notes, 0);

  fail_unless(!strcmp(XMLNode_getName(child), "html"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child), "body"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child1 = XMLNode_getChild(child, 0);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is my text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  child1 = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is more text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  XMLAttributes_free(att);
  XMLNamespaces_free(ns);
  XMLTriple_free(html_triple);
  XMLTriple_free(head_triple);
  XMLTriple_free(body_triple);
  XMLTriple_free(p_triple);
  XMLToken_free(body_token);
  XMLToken_free(p_token);
  XMLToken_free(text_token);
  XMLToken_free(text_token1);
  XMLToken_free(body_token1);
  XMLNode_free(body_node);
  XMLNode_free(p_node);
  XMLNode_free(text_node);
  XMLNode_free(html_node1);
  XMLNode_free(head_node1);
  XMLNode_free(body_node1);
  XMLNode_free(p_node1);
  XMLNode_free(text_node1);
}
END_TEST


START_TEST (test_SBase_appendNotes5)
{
  // add a html tag to a p tag
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLTriple_t *html_triple = XMLTriple_createWith("html", "", "");
  XMLTriple_t *head_triple = XMLTriple_createWith("head", "", "");
  XMLTriple_t *body_triple = XMLTriple_createWith("body", "", "");
  XMLTriple_t *p_triple = XMLTriple_createWith("p", "", "");
  XMLToken_t *html_token = XMLToken_createWithTripleAttrNS(html_triple, att, ns);
  XMLToken_t *head_token = XMLToken_createWithTripleAttr(head_triple, att);
  XMLToken_t *body_token = XMLToken_createWithTripleAttr(body_triple, att);
  XMLToken_t *p_token = XMLToken_createWithTripleAttr(p_triple, att);
  XMLToken_t *p_token1 = XMLToken_createWithTripleAttrNS(p_triple, att, ns);
  XMLToken_t *text_token = XMLToken_createWithText("This is my text");
  XMLNode_t *p_node = XMLNode_createFromToken(p_token1);
  XMLNode_t *text_node = XMLNode_createFromToken(text_token);

  XMLToken_t *text_token1 = XMLToken_createWithText("This is more text");
  XMLNode_t *html_node1 = XMLNode_createFromToken(html_token);
  XMLNode_t *head_node1 = XMLNode_createFromToken(head_token);
  XMLNode_t *body_node1 = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node1 = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node1 = XMLNode_createFromToken(text_token1);

  XMLNode_t * notes;
  const XMLNode_t *child, *child1;

  XMLNode_addChild(p_node, text_node);

  XMLNode_addChild(p_node1, text_node1);
  XMLNode_addChild(body_node1, p_node1);
  XMLNode_addChild(html_node1, head_node1);
  XMLNode_addChild(html_node1, body_node1);

  SBase_setNotes(S, p_node);
  SBase_appendNotes(S, html_node1);

  notes = SBase_getNotes(S);

  fail_unless(!strcmp(XMLNode_getName(notes), "notes"));
  fail_unless(XMLNode_getNumChildren(notes) == 1);

  child = XMLNode_getChild(notes, 0);

  fail_unless(!strcmp(XMLNode_getName(child), "html"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child), "body"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child1 = XMLNode_getChild(child, 0);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is my text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  child1 = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is more text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  XMLAttributes_free(att);
  XMLNamespaces_free(ns);
  XMLTriple_free(html_triple);
  XMLTriple_free(head_triple);
  XMLTriple_free(body_triple);
  XMLTriple_free(p_triple);
  XMLToken_free(body_token);
  XMLToken_free(p_token);
  XMLToken_free(p_token1);
  XMLToken_free(text_token);
  XMLToken_free(text_token1);
  XMLNode_free(p_node);
  XMLNode_free(text_node);
  XMLNode_free(html_node1);
  XMLNode_free(head_node1);
  XMLNode_free(body_node1);
  XMLNode_free(p_node1);
  XMLNode_free(text_node1);
}
END_TEST


START_TEST (test_SBase_appendNotes6)
{// add a body tag to an body tag
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLTriple_t *body_triple = XMLTriple_createWith("body", "", "");
  XMLTriple_t *p_triple = XMLTriple_createWith("p", "", "");
  XMLToken_t *body_token = XMLToken_createWithTripleAttrNS(body_triple, att, ns);
  XMLToken_t *p_token = XMLToken_createWithTripleAttr(p_triple, att);
  XMLToken_t *text_token = XMLToken_createWithText("This is my text");
  XMLNode_t *body_node = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node = XMLNode_createFromToken(text_token);

  XMLToken_t *text_token1 = XMLToken_createWithText("This is more text");
  XMLNode_t *body_node1 = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node1 = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node1 = XMLNode_createFromToken(text_token1);

  XMLNode_t * notes;
  const XMLNode_t *child, *child1;

  XMLNode_addChild(p_node, text_node);
  XMLNode_addChild(body_node, p_node);

  XMLNode_addChild(p_node1, text_node1);
  XMLNode_addChild(body_node1, p_node1);

  SBase_setNotes(S, body_node);
  SBase_appendNotes(S, body_node1);

  notes = SBase_getNotes(S);

  fail_unless(!strcmp(XMLNode_getName(notes), "notes"));
  fail_unless(XMLNode_getNumChildren(notes) == 1);

  child = XMLNode_getChild(notes, 0);

  fail_unless(!strcmp(XMLNode_getName(child), "body"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child1 = XMLNode_getChild(child, 0);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is my text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  child1 = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is more text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  XMLAttributes_free(att);
  XMLNamespaces_free(ns);
  XMLTriple_free(body_triple);
  XMLTriple_free(p_triple);
  XMLToken_free(body_token);
  XMLToken_free(p_token);
  XMLToken_free(text_token);
  XMLToken_free(text_token1);
  XMLNode_free(body_node);
  XMLNode_free(p_node);
  XMLNode_free(text_node);
  XMLNode_free(body_node1);
  XMLNode_free(p_node1);
  XMLNode_free(text_node1);
}
END_TEST


START_TEST (test_SBase_appendNotes7)
{// add a body tag to an p tag
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLTriple_t *body_triple = XMLTriple_createWith("body", "", "");
  XMLTriple_t *p_triple = XMLTriple_createWith("p", "", "");
  XMLToken_t *body_token = XMLToken_createWithTripleAttrNS(body_triple, att, ns);
  XMLToken_t *p_token1 = XMLToken_createWithTripleAttrNS(p_triple, att, ns);
  XMLToken_t *text_token = XMLToken_createWithText("This is my text");
  XMLToken_t *p_token = XMLToken_createWithTripleAttr(p_triple, att);
  XMLNode_t *p_node = XMLNode_createFromToken(p_token1);
  XMLNode_t *text_node = XMLNode_createFromToken(text_token);

  XMLToken_t *text_token1 = XMLToken_createWithText("This is more text");
  XMLNode_t *body_node1 = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node1 = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node1 = XMLNode_createFromToken(text_token1);

  XMLNode_t * notes;
  const XMLNode_t *child, *child1;

  XMLNode_addChild(p_node, text_node);

  XMLNode_addChild(p_node1, text_node1);
  XMLNode_addChild(body_node1, p_node1);

  SBase_setNotes(S, p_node);
  SBase_appendNotes(S, body_node1);

  notes = SBase_getNotes(S);

  fail_unless(!strcmp(XMLNode_getName(notes), "notes"));
  fail_unless(XMLNode_getNumChildren(notes) == 1);

  child = XMLNode_getChild(notes, 0);

  fail_unless(!strcmp(XMLNode_getName(child), "body"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child1 = XMLNode_getChild(child, 0);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is my text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  child1 = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is more text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  XMLAttributes_free(att);
  XMLNamespaces_free(ns);
  XMLTriple_free(body_triple);
  XMLTriple_free(p_triple);
  XMLToken_free(body_token);
  XMLToken_free(p_token);
  XMLToken_free(p_token1);
  XMLToken_free(text_token);
  XMLToken_free(text_token1);
  XMLNode_free(p_node);
  XMLNode_free(text_node);
  XMLNode_free(body_node1);
  XMLNode_free(p_node1);
  XMLNode_free(text_node1);
}
END_TEST


START_TEST (test_SBase_appendNotes8)
{
  // add a p tag to an body tag
  XMLAttributes_t * att = XMLAttributes_create ();
  XMLNamespaces_t *ns = XMLNamespaces_create();
  XMLNamespaces_add(ns, "http://www.w3.org/1999/xhtml", "");
  XMLTriple_t *body_triple = XMLTriple_createWith("body", "", "");
  XMLTriple_t *p_triple = XMLTriple_createWith("p", "", "");
  XMLToken_t *body_token = XMLToken_createWithTripleAttrNS(body_triple, att, ns);
  XMLToken_t *p_token = XMLToken_createWithTripleAttr(p_triple, att);
  XMLToken_t *text_token = XMLToken_createWithText("This is my text");
  XMLNode_t *body_node = XMLNode_createFromToken(body_token);
  XMLNode_t *p_node = XMLNode_createFromToken(p_token);
  XMLNode_t *text_node = XMLNode_createFromToken(text_token);

  XMLToken_t *p_token1 = XMLToken_createWithTripleAttrNS(p_triple, att, ns);
  XMLToken_t *text_token1 = XMLToken_createWithText("This is more text");
  XMLNode_t *p_node1 = XMLNode_createFromToken(p_token1);
  XMLNode_t *text_node1 = XMLNode_createFromToken(text_token1);

  XMLNode_t * notes;
  const XMLNode_t *child, *child1;

  XMLNode_addChild(p_node, text_node);
  XMLNode_addChild(body_node, p_node);

  XMLNode_addChild(p_node1, text_node1);

  SBase_setNotes(S, body_node);
  SBase_appendNotes(S, p_node1);

  notes = SBase_getNotes(S);

  fail_unless(!strcmp(XMLNode_getName(notes), "notes"));
  fail_unless(XMLNode_getNumChildren(notes) == 1);

  child = XMLNode_getChild(notes, 0);

  fail_unless(!strcmp(XMLNode_getName(child), "body"));
  fail_unless(XMLNode_getNumChildren(child) == 2);

  child1 = XMLNode_getChild(child, 0);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is my text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  child1 = XMLNode_getChild(child, 1);

  fail_unless(!strcmp(XMLNode_getName(child1), "p"));
  fail_unless(XMLNode_getNumChildren(child1) == 1);

  child1 = XMLNode_getChild(child1, 0);

  fail_unless(!strcmp(XMLNode_getCharacters(child1), "This is more text"));
  fail_unless(XMLNode_getNumChildren(child1) == 0);

  XMLAttributes_free(att);
  XMLNamespaces_free(ns);
  XMLTriple_free(body_triple);
  XMLTriple_free(p_triple);
  XMLToken_free(body_token);
  XMLToken_free(p_token);
  XMLToken_free(text_token);
  XMLToken_free(text_token1);
  XMLToken_free(p_token1);
  XMLNode_free(body_node);
  XMLNode_free(p_node);
  XMLNode_free(text_node);
  XMLNode_free(p_node1);
  XMLNode_free(text_node1);
}
END_TEST


START_TEST (test_SBase_appendNotesString)
{
  char * notes = "<p xmlns=\"http://www.w3.org/1999/xhtml\">This is a test note </p>";
  char * taggednewnotes = "<notes>\n"
                       "  <p xmlns=\"http://www.w3.org/1999/xhtml\">This is a test note </p>\n"
                       "  <p xmlns=\"http://www.w3.org/1999/xhtml\">This is more test notes </p>\n"
                       "</notes>";
  char * newnotes = "<p xmlns=\"http://www.w3.org/1999/xhtml\">This is more test notes </p>";

  SBase_setNotesString(S, notes);

  fail_unless(SBase_isSetNotes(S) == 1);

  SBase_appendNotesString(S, newnotes);

  const char * notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST (test_SBase_appendNotesString1)
{ // add html to html
  char * notes = "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <head/>\n"
                 "  <body>\n"
                 "    <p>This is a test note </p>\n"
                 "  </body>\n"
                 "</html>";
  char * taggednewnotes = 
                 "<notes>\n"
                 "  <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "    <head/>\n"
                 "    <body>\n"
                 "      <p>This is a test note </p>\n"
                 "      <p>This is more test notes </p>\n"
                 "    </body>\n"
                 "  </html>\n"
                 "</notes>";
  char * addnotes = "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <head/>\n"
                 "  <body>\n"
                 "    <p>This is more test notes </p>\n"
                 "  </body>\n"
                 "</html>";

  SBase_setNotesString(S, notes);
  SBase_appendNotesString(S, addnotes);

  const char *notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST (test_SBase_appendNotesString2)
{ // add body to html
  char * notes = "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <head/>\n"
                 "  <body>\n"
                 "    <p>This is a test note </p>\n"
                 "  </body>\n"
                 "</html>";
  char * taggednewnotes = 
                 "<notes>\n"
                 "  <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "    <head/>\n"
                 "    <body>\n"
                 "      <p>This is a test note </p>\n"
                 "      <p>This is more test notes </p>\n"
                 "    </body>\n"
                 "  </html>\n"
                 "</notes>";
  char * addnotes = "<body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                    "  <p>This is more test notes </p>\n"
                    "</body>\n";

  SBase_setNotesString(S, notes);
  SBase_appendNotesString(S, addnotes);

  const char *notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST (test_SBase_appendNotesString3)
{ // add p to html
  char * notes = "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <head/>\n"
                 "  <body>\n"
                 "    <p>This is a test note </p>\n"
                 "  </body>\n"
                 "</html>";
  char * taggednewnotes = 
                 "<notes>\n"
                 "  <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "    <head/>\n"
                 "    <body>\n"
                 "      <p>This is a test note </p>\n"
                 "      <p xmlns=\"http://www.w3.org/1999/xhtml\">This is more test notes </p>\n"
                 "    </body>\n"
                 "  </html>\n"
                 "</notes>";
  char * addnotes = "<p xmlns=\"http://www.w3.org/1999/xhtml\">This is more test notes </p>";

  SBase_setNotesString(S, notes);
  SBase_appendNotesString(S, addnotes);

  const char *notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST (test_SBase_appendNotesString4)
{ // add html to body
  char * notes = "<body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <p>This is a test note </p>\n"
                 "</body>";
  char * taggednewnotes = 
                 "<notes>\n"
                 "  <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "    <head/>\n"
                 "    <body>\n"
                 "      <p>This is a test note </p>\n"
                 "      <p>This is more test notes </p>\n"
                 "    </body>\n"
                 "  </html>\n"
                 "</notes>";
  char * addnotes = "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <head/>\n"
                 "  <body>\n"
                 "    <p>This is more test notes </p>\n"
                 "  </body>\n"
                 "</html>";

  SBase_setNotesString(S, notes);
  SBase_appendNotesString(S, addnotes);

  const char *notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST (test_SBase_appendNotesString5)
{ // add html to p
  char * notes = "<p xmlns=\"http://www.w3.org/1999/xhtml\">This is a test note </p>";
  char * taggednewnotes = 
                 "<notes>\n"
                 "  <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "    <head/>\n"
                 "    <body>\n"
                 "      <p xmlns=\"http://www.w3.org/1999/xhtml\">This is a test note </p>\n"
                 "      <p>This is more test notes </p>\n"
                 "    </body>\n"
                 "  </html>\n"
                 "</notes>";
  char * addnotes = "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <head/>\n"
                 "  <body>\n"
                 "    <p>This is more test notes </p>\n"
                 "  </body>\n"
                 "</html>";

  SBase_setNotesString(S, notes);
  SBase_appendNotesString(S, addnotes);

  const char *notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST (test_SBase_appendNotesString6)
{ // add body to body
  char * notes = "<body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <p>This is a test note </p>\n"
                 "</body>";
  char * taggednewnotes = 
                 "<notes>\n"
                 "  <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "    <p>This is a test note </p>\n"
                 "    <p>This is more test notes </p>\n"
                 "  </body>\n"
                 "</notes>";
  char * addnotes = "<body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <p>This is more test notes </p>\n"
                 "</body>";

  SBase_setNotesString(S, notes);
  SBase_appendNotesString(S, addnotes);

  const char *notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST (test_SBase_appendNotesString7)
{ // add body to p
  char * notes = "<p xmlns=\"http://www.w3.org/1999/xhtml\">This is a test note </p>";
  char * taggednewnotes = 
                 "<notes>\n"
                 "  <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "    <p xmlns=\"http://www.w3.org/1999/xhtml\">This is a test note </p>\n"
                 "    <p>This is more test notes </p>\n"
                 "  </body>\n"
                 "</notes>";
  char * addnotes = "<body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <p>This is more test notes </p>\n"
                 "</body>";

  SBase_setNotesString(S, notes);
  SBase_appendNotesString(S, addnotes);

  const char *notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST (test_SBase_appendNotesString8)
{ // add p to body
  char * notes = "<body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "  <p>This is a test note </p>\n"
                 "</body>";
  char * taggednewnotes = 
                 "<notes>\n"
                 "  <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                 "    <p>This is a test note </p>\n"
                 "    <p xmlns=\"http://www.w3.org/1999/xhtml\">This is more test notes </p>\n"
                 "  </body>\n"
                 "</notes>";
  char * addnotes = "<p xmlns=\"http://www.w3.org/1999/xhtml\">This is more test notes </p>";

  SBase_setNotesString(S, notes);
  SBase_appendNotesString(S, addnotes);

  const char *notes1 = SBase_getNotesString(S);

  fail_unless(SBase_isSetNotes(S) == 1);
  fail_unless(!strcmp(taggednewnotes, notes1));

}
END_TEST


START_TEST(test_SBase_CVTerms)
{
  CVTerm_t * cv = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  
  fail_unless(SBase_getNumCVTerms(S) == 0);
  fail_unless(SBase_getCVTerms(S) == NULL);

  SBase_setMetaId(S, "sbase1");
  SBase_addCVTerm(S, cv);
  fail_unless(SBase_getNumCVTerms(S) == 1);
  fail_unless(SBase_getCVTerms(S) != NULL);

  fail_unless(SBase_getCVTerm(S, 0) != cv);

  CVTerm_free(cv);


}
END_TEST


START_TEST(test_SBase_addCVTerms)
{
  CVTerm_t * cv = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv, BQB_ENCODES);
  CVTerm_addResource(cv, "foo");
  SBase_setMetaId(S, "sbase1");
  
  SBase_addCVTerm(S, cv);
  
  fail_unless(SBase_getNumCVTerms(S) == 1);
  fail_unless(SBase_getCVTerms(S) != NULL);

  XMLAttributes_t *res = CVTerm_getResources(SBase_getCVTerm(S, 0));
  fail_unless(!strcmp(res->getValue(0).c_str(), "foo"));

  CVTerm_t * cv1 = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv1, BQB_IS);
  CVTerm_addResource(cv1, "bar");
  
  SBase_addCVTerm(S, cv1);
  
  fail_unless(SBase_getNumCVTerms(S) == 2);

  /* same qualifier so should just add to resources of existing term */
  CVTerm_t * cv2 = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv2, BQB_IS);
  CVTerm_addResource(cv2, "bar1");
  
  SBase_addCVTerm(S, cv2);
  
  fail_unless(SBase_getNumCVTerms(S) == 2);
  
  res = CVTerm_getResources(SBase_getCVTerm(S, 1));

  fail_unless(XMLAttributes_getLength(res) == 2);
  fail_unless(!strcmp(res->getValue(0).c_str(), "bar"));
  fail_unless(!strcmp(res->getValue(1).c_str(), "bar1"));


  /* existing term shouldnt get added*/
  CVTerm_t * cv4 = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv4, BQB_IS);
  CVTerm_addResource(cv4, "bar1");
  
  SBase_addCVTerm(S, cv4);
  
  fail_unless(SBase_getNumCVTerms(S) == 2);
  
  res = CVTerm_getResources(SBase_getCVTerm(S, 1));

  fail_unless(XMLAttributes_getLength(res) == 2);
  fail_unless(!strcmp(res->getValue(0).c_str(), "bar"));
  fail_unless(!strcmp(res->getValue(1).c_str(), "bar1"));
  
  /* existing term with different qualifier shouldnt get added*/
  CVTerm_t * cv5 = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv5, BQB_HAS_PART);
  CVTerm_addResource(cv5, "bar1");
  
  SBase_addCVTerm(S, cv5);
  
  fail_unless(SBase_getNumCVTerms(S) == 2);
  
  res = CVTerm_getResources(SBase_getCVTerm(S, 1));

  fail_unless(XMLAttributes_getLength(res) == 2);
  fail_unless(!strcmp(res->getValue(0).c_str(), "bar"));
  fail_unless(!strcmp(res->getValue(1).c_str(), "bar1"));
 
  CVTerm_free(cv);
  CVTerm_free(cv2);
  CVTerm_free(cv1);
  CVTerm_free(cv4);


}
END_TEST


START_TEST(test_SBase_unsetCVTerms)
{
  CVTerm_t * cv = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv, BQB_ENCODES);
  CVTerm_addResource(cv, "foo");
  
  SBase_setMetaId(S, "sbase1");
  SBase_addCVTerm(S, cv);
  CVTerm_t * cv1 = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv1, BQB_IS);
  CVTerm_addResource(cv1, "bar");
  
  SBase_addCVTerm(S, cv1);
  CVTerm_t * cv2 = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv2, BQB_IS);
  CVTerm_addResource(cv2, "bar1");
  
  SBase_addCVTerm(S, cv2);
  CVTerm_t * cv4 = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv4, BQB_IS);
  CVTerm_addResource(cv4, "bar1");
  
  SBase_addCVTerm(S, cv4);
  
  fail_unless(SBase_getNumCVTerms(S) == 2);

  SBase_unsetCVTerms(S);

  fail_unless(SBase_getNumCVTerms(S) == 0);
  fail_unless(SBase_getCVTerms(S) == NULL);
  
  CVTerm_free(cv);
  CVTerm_free(cv2);
  CVTerm_free(cv1);
  CVTerm_free(cv4);
}
END_TEST


START_TEST(test_SBase_getQualifiersFromResources)
{
  CVTerm_t * cv = CVTerm_createWithQualifierType(BIOLOGICAL_QUALIFIER);
  CVTerm_setBiologicalQualifierType(cv, BQB_ENCODES);
  CVTerm_addResource(cv, "foo");
  
  SBase_setMetaId(S, "sbase1");
  SBase_addCVTerm(S, cv);

  fail_unless(SBase_getResourceBiologicalQualifier(S, "foo") == BQB_ENCODES);
  
  CVTerm_t * cv1 = CVTerm_createWithQualifierType(MODEL_QUALIFIER);
  CVTerm_setModelQualifierType(cv1, BQM_IS);
  CVTerm_addResource(cv1, "bar");
  
  SBase_addCVTerm(S, cv1);

  fail_unless(SBase_getResourceModelQualifier(S, "bar") == BQM_IS);
  
  CVTerm_free(cv);
  CVTerm_free(cv1);


}
END_TEST


Suite *
create_suite_SBase (void)
{
  Suite *suite = suite_create("SBase");
  TCase *tcase = tcase_create("SBase");


  tcase_add_checked_fixture(tcase, SBaseTest_setup, SBaseTest_teardown);

  tcase_add_test(tcase, test_SBase_setMetaId     );
  tcase_add_test(tcase, test_SBase_setNotes      );
  tcase_add_test(tcase, test_SBase_setAnnotation );
  tcase_add_test(tcase, test_SBase_setNotesString);
  tcase_add_test(tcase, test_SBase_setAnnotationString);

  tcase_add_test(tcase, test_SBase_appendNotes );
  tcase_add_test(tcase, test_SBase_appendNotes1 );
  tcase_add_test(tcase, test_SBase_appendNotes2 );
  tcase_add_test(tcase, test_SBase_appendNotes3 );
  tcase_add_test(tcase, test_SBase_appendNotes4 );
  tcase_add_test(tcase, test_SBase_appendNotes5 );
  tcase_add_test(tcase, test_SBase_appendNotes6 );
  tcase_add_test(tcase, test_SBase_appendNotes7 );
  tcase_add_test(tcase, test_SBase_appendNotes8 );
  tcase_add_test(tcase, test_SBase_appendNotesString );
  tcase_add_test(tcase, test_SBase_appendNotesString1);
  tcase_add_test(tcase, test_SBase_appendNotesString2);
  tcase_add_test(tcase, test_SBase_appendNotesString3);
  tcase_add_test(tcase, test_SBase_appendNotesString4);
  tcase_add_test(tcase, test_SBase_appendNotesString5);
  tcase_add_test(tcase, test_SBase_appendNotesString6);
  tcase_add_test(tcase, test_SBase_appendNotesString7);
  tcase_add_test(tcase, test_SBase_appendNotesString8);

  tcase_add_test(tcase, test_SBase_CVTerms );
  tcase_add_test(tcase, test_SBase_addCVTerms );
  tcase_add_test(tcase, test_SBase_unsetCVTerms );
  tcase_add_test(tcase, test_SBase_getQualifiersFromResources );

  suite_add_tcase(suite, tcase);

  return suite;
}


END_C_DECLS
