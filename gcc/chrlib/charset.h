/*====================================================================*
 *
 *   charset.h - character set definitions and declarations;
 *
 *   define and declare character convertion functions and symbolically
 *   define common character sets and special characters;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHARSET_HEADER
#define CHARSET_HEADER

/*====================================================================*
 *   character set template strings; characters within most of the strings
 *   in this section have been arranged as they are for a reason; usually,
 *   by probability of occurance; but somtimes for other reasons;
 *--------------------------------------------------------------------*/

#define gcsASCIIUpper "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define gcsASCIILower "abcdefghijklmnopqrstuvwxyz"
#define gcsASCIIAlpha gcsASCIIUpper gcsASCIILower
#define gcsISOUpper gcsASCIIUpper "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖØÙÚÛÜİŞß"
#define gcsISOLower gcsASCIILower "àáâãäåæçèéêëìíîïğñòóôõöøùúûüışß"
#define gcsISOAlpha gcsISOLower gcsISOUpper
#define gcsBlank " \t"
#define gcsBreak "\r\n\f"
#define gcsSpace gcsBlank gcsBreak 
#define gcsUpper gcsASCIIUpper 
#define gcsLower gcsASCIILower
#define gcsAlpha gcsLower gcsUpper 
#define gcsDigit "0123456789"
#define gcsLabel gcsAlpha "._"
#define gcsFloat gcsDigit "."
#define gcsRadix gcsDigit gcsUpper
#define gcsAlnum gcsLower gcsUpper gcsDigit
#define gcsIdent gcsLower gcsUpper "_.-"
#define gcsCName gcsLower gcsUpper "_$"
#define gcsEscap "\\"
#define gcsQuote "\""
#define gcsApost "\'"
#define gcsHexDigit "0123456789ABCDEF"
#define gcsDecDigit "0123456789"
#define gcsOctDigit "01234567"
#define gcsBinDigit "01"
#define gcsFraction "¼½¾"
#define gcsExponent "º¹²³"
#define gcsCurrency "¢£¥€"
#define gcsOperator "+-/*^%!&|~=<>:?"
#define gcsArithmetic "+-/*^%"
#define gcwLogical "!&|~"
#define gcsRelation "=<>:?"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define gwcsASCIIUpper L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define gwcsASCIILower L"abcdefghijklmnopqrstuvwxyz"
#define gwcsASCIIAlpha L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define gwcsISOUpper L"ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖØÙÚÛÜİŞß"
#define gwcsISOLower L"abcdefghijklmnopqrstuvwxyzàáâãäåæçèéêëìíîïğñòóôõöøùúûüışß"
#define gwcsISOAlpha L"ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖØÙÚÛÜİŞßabcdefghijklmnopqrstuvwxyzàáâãäåæçèéêëìíîïğñòóôõöøùúûüışß"
#define gwcsSpace L" \t\r\n"
#define gwcsUpper L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define gwcsLower L"abcdefghijklmnopqrstuvwxyz"
#define gwcsAlpha L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define gwcsLabel L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz._"
#define gwcsDigit L"0123456789"
#define gwcsFloat L"0123456789."
#define gwcsAlnum L"0123456789._ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-"
#define gwcsEscap L"\\"
#define gwcsHexDigit L"0123456789ABCDEF"
#define gwcsOctDigit L"01234567"
#define gwcsBinDigit L"01"
#define gwcsFraction L"¼½¾"
#define gwcsExponent L"º¹²³"
#define gwcsCurrency L"¢£¥€"
#define gwcsOperator L"+-/*^%!&|~=<>:?"
#define gwcsArithmetic L"+-/*^%"
#define gwcsLogical L"!&|~"
#define gwcsRelation L"=<>:?"

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

