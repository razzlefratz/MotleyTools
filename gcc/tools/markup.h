/*====================================================================*
 *
 *   markup.h - markup language definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates for internal use;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MARKUP_HEADER
#define MARKUP_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define ISO_CHARSET "iso-8859-1"
#define ISO_CONTENT "text/html"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define W3C_STD "-//W3C//DTD XHTML 1.0 Strict//EN"
#define W3C_DTD "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define XML_VERSION "1.0"
#define XML_CHARSET ISO_CHARSET
#define XML_SCHEMA "http://www.w3.org/2001/XMLSchema-instance" 
#define XML_NAMESPACE "http://www.w3c.org/1999/xhtml"
#define XML_LANGUAGE "en-us"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define CSS_STYLESHEET "/styles/stylesheet.css"
#define CSS_CONTENT "text/css"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define STYLE_PAGE "page"
#define STYLE_BODY "body"
#define STYLE_DATA "data"
#define STYLE_BASE "base"
#define STYLE_SIZE "size"
#define STYLE_NAME "name"
#define STYLE_TYPE "type"
#define STYLE_TEXT "text"
#define STYLE_HEAD "head"
#define STYLE_FOOT "foot"

#define STYLE_TOPLINK "headerlink"
#define STYLE_BOTLINK "footerlink"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define HTML_CONTENT ISO_CONTENT ";" ISO_CHARSET
#define HTML_PROGRAM PACKAGE " " VERSION " " RELEASE
#define HTML_SUBJECT "Untitled Document"
#define HTML_AUTHOR "cmaier@cmassoc.net"
#define HTML_ROBOTS "noindex,nofollow"

#define HTML_PATH "index.html"
#define HTML_NAME "Index"
#define HTML_PREV "PREV"
#define HTML_HOME "HOME"
#define HTML_NEXT "NEXT"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

