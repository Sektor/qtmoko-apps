/* This file is part of QGoogleTranslate
 *
 * Copyright (C) 2009 Durachenko Alexei V. <lexnewton86@gmail.com>
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QtGui>

#include "../version.h"

// project configuration

#define G_FULL_PROGRAM_NAME (QString("%1 - %2.%3%4 build %5 (%6.%7.%8)").arg(tr(gProgramName)).arg(AutoVersion::MAJOR).arg(AutoVersion::MINOR).arg(AutoVersion::STATUS_SHORT).arg(AutoVersion::BUILD).arg(AutoVersion::YEAR).arg(AutoVersion::MONTH).arg(AutoVersion::DATE))

const char    gProgramName[]    = QT_TR_NOOP("QGoogleTranslate");

const char    gProjectFamily[]  = "QGoogleTranslate";

const char    gProjectName[]    = "QGoogleTranslate";



// google language configuration

typedef struct __tGoogleLang {
    char name[80];
    char code[16];
} tGoogleLang;

const tGoogleLang gGoogleLang[] = {
    {"English"     , "en"}, // ok
    {"Russian"     , "ru"}, // ok
    {"Afrikaans"   , "af"}, // ok
    {"Albanian"    , "sq"}, // ok
    {"Amharic"     , "am"}, // ok
    {"Arabic"      , "ar"}, // ok
    {"Armenian"    , "hy"}, // ok
    {"Azerbaijani" , "az"}, // ok
    {"Basque"      , "eu"}, // ok
    {"Belarusian"  , "be"}, // ok
    {"Bengali"     , "bn"}, // ok
    {"Bihari"      , "bh"}, // ok
    {"Bulgarian"   , "bg"}, // ok
    {"Burmese"     , "my"}, // ok
    {"Catalan"     , "ca"}, // ok
    {"Cherokee"    , "chr"},// ok
    {"Chinese"     , "zh"}, // ok
    {"Chinese_simplified"  , "zh-cn"}, // ok
    {"Chinese_traditional" , "zh-tw"}, // ok
    {"Croatian"    , "hr"}, // ok
    {"Czech"       , "cs"}, // ok
    {"Danish"      , "da"}, // ok
    {"Dhivehi"     , "dv"}, // ok
    {"Dutch"       , "nl"}, // ok
    {"Esperanto"   , "eo"}, // ok
    {"Estonian"    , "et"}, // ok
    {"Filipino"    , "tl"}, // ok
    {"Finnish"     , "fi"}, // ok
    {"French"      , "fr"}, // ok
    {"Galician"    , "gl"}, // ok
    {"Georgian"    , "ka"}, // ok
    {"German"      , "de"}, // ok
    {"Greek"       , "el"}, // ok
    {"Guarani"     , "gn"}, // ok
    {"Gujarati"    , "gu"}, // ok
    {"Hebrew"      , "iw"}, // ok
    {"Hindi"       , "hi"}, // ok
    {"Hungarian"   , "hu"}, // ok
    {"Icelandic"   , "is"}, // ok
    {"Indonesian"  , "id"}, // ok
    {"Inuktitut"   , "iu"}, // ok
    {"Italian"     , "it"}, // ok
    {"Japanese"    , "ja"}, // ok
    {"Kannada"     , "kn"}, // ok
    {"Kazakh"      , "kk"}, // ok
    {"Khmer"       , "km"}, // ok
    {"Korean"      , "ko"}, // ok
    {"Kurdish"     , "ku"}, // ok
    {"Kyrgyz"      , "ky"}, // ok
    {"Laothian"    , "lo"}, // ok
    {"Latvian"     , "lv"}, // ok
    {"Lithuanian"  , "lt"}, // ok
    {"Macedonian"  , "mk"}, // ok
    {"Malay"       , "ms"}, // ok
    {"Malayalam"   , "ml"}, // ok
    {"Maltese"     , "mt"}, // ok
    {"Marathi"     , "mr"}, // ok
    {"Mongolian"   , "mn"}, // ok
    {"Nepali"      , "ne"}, // ok
    {"Norwegian"   , "no"}, // ok
    {"Oriya"       , "or"}, // ok
    {"Pashto"      , "ps"}, // ok
    {"Persian"     , "fa"}, // ok
    {"Polish"      , "pl"}, // ok
    {"Portuguese"  , "pt-pt"}, // ok
    {"Punjabi"     , "pa"}, // ok
    {"Romanian"    , "ro"}, // ok
    {"Sanskrit"    , "sa"}, // ok
    {"Serbian"     , "sr"}, // ok
    {"Sindhi"      , "sd"}, // ok
    {"Sinhalese"   , "si"}, // ok
    {"Slovak"      , "sk"}, // ok
    {"Slovenian"   , "sl"}, // ok
    {"Spanish"     , "es"}, // ok
    {"Swahili"     , "sw"}, // ok
    {"Swedish"     , "sv"}, // ok
    {"Tajik"       , "tg"}, // ok
    {"Tamil"       , "ta"}, // ok
    {"Tagalog"     , "tl"}, // ok
    {"Telugu"      , "te"}, // ok
    {"Thai"        , "th"}, // ok
    {"Tibetan"     , "bo"}, // ok
    {"Turkish"     , "tr"}, // ok
    {"Ukrainian"   , "uk"}, // ok
    {"Urdu"        , "ur"}, // ok
    {"Uzbek"       , "uz"}, // ok
    {"Uighur"      , "ug"}, // ok
    {"Vietnamese"  , "vi"} // ok
};
const int gGoogleLangCount = sizeof( gGoogleLang ) / sizeof( tGoogleLang );

#endif
