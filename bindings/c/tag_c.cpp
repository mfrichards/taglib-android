/***************************************************************************
    copyright            : (C) 2003 by Scott Wheeler
    email                : wheeler@kde.org
 ***************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
 *   USA                                                                   *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "tag_c.h"

#include <stdlib.h>
#include <fileref.h>
#include <tfile.h>
#include <asffile.h>
#include <vorbisfile.h>
#include <mpegfile.h>
#include <flacfile.h>
#include <oggflacfile.h>
#include <mpcfile.h>
#include <wavpackfile.h>
#include <speexfile.h>
#include <trueaudiofile.h>
#include <mp4file.h>
#include <tag.h>
#include <string.h>
#include <id3v2framefactory.h>
#include <id3v2tag.h>
#include <commentsframe.h>
#include <textidentificationframe.h>
#include <popularimeterframe.h>
#include <attachedpictureframe.h>
#include <unknownframe.h>
#include <xingheader.h>
#include <ape/apetag.h>
#include <mp4tag.h>
#include <asftag.h>
#include <xiphcomment.h>

using namespace TagLib;

static List<char *> strings;
static bool unicodeStrings = true;
static bool stringManagementEnabled = true;

void taglib_set_strings_unicode(BOOL unicode)
{
  unicodeStrings = bool(unicode);
}

void taglib_set_string_management_enabled(BOOL management)
{
  stringManagementEnabled = bool(management);
}

char *get_cstring(String str)
{
  char *s = ::strdup(str.toCString(unicodeStrings));
  if(stringManagementEnabled)
    strings.append(s);
  return s;
}

////////////////////////////////////////////////////////////////////////////////
// TagLib::File wrapper
////////////////////////////////////////////////////////////////////////////////

TagLib_File *taglib_file_new(const char *filename)
{
  return reinterpret_cast<TagLib_File *>(FileRef::create(filename));
}

TagLib_File *taglib_file_new_type(const char *filename, TagLib_File_Type type)
{
  switch(type) {
  case TagLib_File_MPEG:
    return reinterpret_cast<TagLib_File *>(new MPEG::File(filename));
  case TagLib_File_OggVorbis:
    return reinterpret_cast<TagLib_File *>(new Ogg::Vorbis::File(filename));
  case TagLib_File_FLAC:
    return reinterpret_cast<TagLib_File *>(new FLAC::File(filename));
  case TagLib_File_MPC:
    return reinterpret_cast<TagLib_File *>(new MPC::File(filename));
  case TagLib_File_OggFlac:
    return reinterpret_cast<TagLib_File *>(new Ogg::FLAC::File(filename));
  case TagLib_File_WavPack:
    return reinterpret_cast<TagLib_File *>(new WavPack::File(filename));
  case TagLib_File_Speex:
    return reinterpret_cast<TagLib_File *>(new Ogg::Speex::File(filename));
  case TagLib_File_TrueAudio:
    return reinterpret_cast<TagLib_File *>(new TrueAudio::File(filename));
#ifdef TAGLIB_WITH_MP4
  case TagLib_File_MP4:
    return reinterpret_cast<TagLib_File *>(new MP4::File(filename));
#endif
#ifdef TAGLIB_WITH_ASF
  case TagLib_File_ASF:
    return reinterpret_cast<TagLib_File *>(new ASF::File(filename));
#endif
  default:
    return 0;
  }

  return 0;
}

void taglib_file_free(TagLib_File *file)
{
  delete reinterpret_cast<File *>(file);
}

BOOL taglib_file_is_valid(const TagLib_File *file)
{
  return reinterpret_cast<const File *>(file)->isValid();
}

TagLib_Tag *taglib_file_tag(const TagLib_File *file)
{
  const File *f = reinterpret_cast<const File *>(file);
  return reinterpret_cast<TagLib_Tag *>(f->tag());
}

const TagLib_AudioProperties *taglib_file_audioproperties(const TagLib_File *file)
{
  const File *f = reinterpret_cast<const File *>(file);
  return reinterpret_cast<const TagLib_AudioProperties *>(f->audioProperties());
}

BOOL taglib_file_save(TagLib_File *file)
{
  return reinterpret_cast<File *>(file)->save();
}

////////////////////////////////////////////////////////////////////////////////
// TagLib::Tag wrapper
////////////////////////////////////////////////////////////////////////////////

char *taglib_tag_title(const TagLib_Tag *tag)
{
  const Tag *t = reinterpret_cast<const Tag *>(tag);
  return get_cstring(t->title());
}

char *taglib_tag_artist(const TagLib_Tag *tag)
{
  const Tag *t = reinterpret_cast<const Tag *>(tag);
  return get_cstring(t->artist());
}

char *taglib_tag_album(const TagLib_Tag *tag)
{
  const Tag *t = reinterpret_cast<const Tag *>(tag);
  return get_cstring(t->album());
}

char *taglib_tag_comment(const TagLib_Tag *tag)
{
  const Tag *t = reinterpret_cast<const Tag *>(tag);
  return get_cstring(t->comment());
}

char *taglib_tag_genre(const TagLib_Tag *tag)
{
  const Tag *t = reinterpret_cast<const Tag *>(tag);
  return get_cstring(t->genre());
}

UINT taglib_tag_year(const TagLib_Tag *tag)
{
  const Tag *t = reinterpret_cast<const Tag *>(tag);
  return t->year();
}

UINT taglib_tag_track(const TagLib_Tag *tag)
{
  const Tag *t = reinterpret_cast<const Tag *>(tag);
  return t->track();
}

void taglib_tag_set_title(TagLib_Tag *tag, const char *title)
{
  Tag *t = reinterpret_cast<Tag *>(tag);
  t->setTitle(String(title, unicodeStrings ? String::UTF8 : String::Latin1));
}

void taglib_tag_set_artist(TagLib_Tag *tag, const char *artist)
{
  Tag *t = reinterpret_cast<Tag *>(tag);
  t->setArtist(String(artist, unicodeStrings ? String::UTF8 : String::Latin1));
}

void taglib_tag_set_album(TagLib_Tag *tag, const char *album)
{
  Tag *t = reinterpret_cast<Tag *>(tag);
  t->setAlbum(String(album, unicodeStrings ? String::UTF8 : String::Latin1));
}

void taglib_tag_set_comment(TagLib_Tag *tag, const char *comment)
{
  Tag *t = reinterpret_cast<Tag *>(tag);
  t->setComment(String(comment, unicodeStrings ? String::UTF8 : String::Latin1));
}

void taglib_tag_set_genre(TagLib_Tag *tag, const char *genre)
{
  Tag *t = reinterpret_cast<Tag *>(tag);
  t->setGenre(String(genre, unicodeStrings ? String::UTF8 : String::Latin1));
}

void taglib_tag_set_year(TagLib_Tag *tag, UINT year)
{
  Tag *t = reinterpret_cast<Tag *>(tag);
  t->setYear(year);
}

void taglib_tag_set_track(TagLib_Tag *tag, UINT track)
{
  Tag *t = reinterpret_cast<Tag *>(tag);
  t->setTrack(track);
}

void taglib_tag_free_strings()
{
  if(!stringManagementEnabled)
    return;

  for(List<char *>::Iterator it = strings.begin(); it != strings.end(); ++it)
    free(*it);
  strings.clear();
}

////////////////////////////////////////////////////////////////////////////////
// TagLib::AudioProperties wrapper
////////////////////////////////////////////////////////////////////////////////

int taglib_audioproperties_length(const TagLib_AudioProperties *audioProperties)
{
  const AudioProperties *p = reinterpret_cast<const AudioProperties *>(audioProperties);
  return p->length();
}

int taglib_audioproperties_bitrate(const TagLib_AudioProperties *audioProperties)
{
  const AudioProperties *p = reinterpret_cast<const AudioProperties *>(audioProperties);
  return p->bitrate();
}

int taglib_audioproperties_samplerate(const TagLib_AudioProperties *audioProperties)
{
  const AudioProperties *p = reinterpret_cast<const AudioProperties *>(audioProperties);
  return p->sampleRate();
}

int taglib_audioproperties_channels(const TagLib_AudioProperties *audioProperties)
{
  const AudioProperties *p = reinterpret_cast<const AudioProperties *>(audioProperties);
  return p->channels();
}

////////////////////////////////////////////////////////////////////////////////
// TagLib::ID3v2 wrapper
////////////////////////////////////////////////////////////////////////////////

TagLib_ID3v2Tag *taglib_mpeg_id3v2(TagLib_File *file)
{
  MPEG::File *f = reinterpret_cast<MPEG::File *>(file);
  return reinterpret_cast<TagLib_ID3v2Tag *>(f->ID3v2Tag(false));
}

const TagLib_XingHeader *taglib_mpeg_xing(const TagLib_AudioProperties *audioProperties)
{
  const MPEG::Properties *p = reinterpret_cast<const MPEG::Properties *>(audioProperties);
  return reinterpret_cast<const TagLib_XingHeader *>(p->xingHeader());
}

// Global variables for iterating through a FrameList. (Not thread safe!)
ID3v2::FrameList fl;
ID3v2::FrameList::ConstIterator it;

TagLib_ID3v2Frame *taglib_id3v2_first_frame(TagLib_ID3v2Tag *tag, char *frame)
{
  ID3v2::Tag *t = reinterpret_cast<ID3v2::Tag *>(tag);

  if (frame == NULL)
  {
    fl = t->frameList();
  }
  else
  {
    ByteVector name(frame);
    fl = t->frameList(name);
  }

  it = fl.begin();
  if (it != fl.end())
  {
    return reinterpret_cast<TagLib_ID3v2Frame *>(*it);
  }
  
  return NULL;
}

TagLib_ID3v2Frame *taglib_id3v2_next_frame()
{
  it++;
  if (it != fl.end())
  {
    return reinterpret_cast<TagLib_ID3v2Frame *>(*it);
  }
  
  return NULL;
}

char *taglib_id3v2_comm_desc(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::CommentsFrame *f = reinterpret_cast<const ID3v2::CommentsFrame *>(frame);
  return get_cstring(f->description());
}

char *taglib_id3v2_comm_text(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::CommentsFrame *f = reinterpret_cast<const ID3v2::CommentsFrame *>(frame);
  return get_cstring(f->text());
}

char *taglib_id3v2_txxx_desc(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::UserTextIdentificationFrame *f = reinterpret_cast<const ID3v2::UserTextIdentificationFrame *>(frame);
  return get_cstring(f->description());
}

char *taglib_id3v2_txxx_data(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::UserTextIdentificationFrame *f = reinterpret_cast<const ID3v2::UserTextIdentificationFrame *>(frame);
  return get_cstring(f->toString());
}

char *taglib_id3v2_popm_email(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::PopularimeterFrame *f = reinterpret_cast<const ID3v2::PopularimeterFrame *>(frame);
  return get_cstring(f->email());
}

int taglib_id3v2_popm_rating(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::PopularimeterFrame *f = reinterpret_cast<const ID3v2::PopularimeterFrame *>(frame);
  return f->rating();
}

UINT taglib_id3v2_popm_counter(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::PopularimeterFrame *f = reinterpret_cast<const ID3v2::PopularimeterFrame *>(frame);
  return f->counter();
}

UINT taglib_xing_start_delay(const TagLib_XingHeader *xing)
{
  const MPEG::XingHeader *h = reinterpret_cast<const MPEG::XingHeader *>(xing);
  return h->startDelay();
}

UINT taglib_xing_end_delay(const TagLib_XingHeader *xing)
{
  const MPEG::XingHeader *h = reinterpret_cast<const MPEG::XingHeader *>(xing);
  return h->endDelay();
}

UINT taglib_id3v2_pic_size(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::AttachedPictureFrame *f = reinterpret_cast<const ID3v2::AttachedPictureFrame *>(frame);
  return f->picture().size();
}

UINT taglib_id3v2_pic_type(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::AttachedPictureFrame *f = reinterpret_cast<const ID3v2::AttachedPictureFrame *>(frame);
  return (UINT) (f->type());
}

UINT taglib_id3v2_pic_data(const TagLib_ID3v2Frame *frame, char *buf, UINT max)
{
  UINT count = 0;
  const ID3v2::AttachedPictureFrame *f = reinterpret_cast<const ID3v2::AttachedPictureFrame *>(frame);
  if (f->picture().isNull()) return 0;
  if (f->picture().isEmpty()) return 0;
  UINT size = f->picture().size();
  if (buf == NULL || size > max) return size;
  for (count = 0; count < size; count++)
  {
    buf[count] = f->picture().at(count);
  }
  return count;
}

UINT taglib_id3v2_unknown_int(const TagLib_ID3v2Frame *frame)
{
  const ID3v2::UnknownFrame *f = reinterpret_cast<const ID3v2::UnknownFrame *>(frame);
  UINT result = 0;
  UINT size = f->data().size();
  for (UINT i = 0; i < size; i++)
  {
    result = result * 256 + (UINT) f->data().at(i);
  }
  return result;
}


////////////////////////////////////////////////////////////////////////////////
// TagLib::Ape::Tag wrapper
////////////////////////////////////////////////////////////////////////////////

TagLib_APETag *taglib_mpeg_ape(TagLib_File *file)
{
  MPEG::File *f = reinterpret_cast<MPEG::File *>(file);
  return reinterpret_cast<TagLib_APETag *>(f->APETag(false));
}

// Global variables for iterating through an ItemList. (Not thread safe!)
APE::ItemListMap al;
APE::ItemListMap::ConstIterator ali;

const TagLib_APEItem *taglib_ape_first_item(TagLib_APETag *tag)
{
  APE::Tag *t = reinterpret_cast<APE::Tag *>(tag);

  al = t->itemListMap();
  ali = al.begin();
  if (ali != al.end())
  {
    return reinterpret_cast<const TagLib_APEItem *>(&(*ali).second);
  }

  return NULL;
}

const TagLib_APEItem *taglib_ape_next_item()
{
  ali++;
  if (ali != al.end())
  {
    return reinterpret_cast<const TagLib_APEItem *>(&(*ali).second);
  }

  return NULL;
}

char *taglib_ape_item_key(const TagLib_APEItem *item)
{
  //const std::pair<const String, APE::Item>
  const APE::Item *i = reinterpret_cast<const APE::Item *>(item);
  return get_cstring(i->key());
}

char *taglib_ape_item_value(const TagLib_APEItem *item)
{
  const APE::Item *i = reinterpret_cast<const APE::Item *>(item);
  return get_cstring(i->toString());
}


////////////////////////////////////////////////////////////////////////////////
// TagLib::MP4::Tag wrapper
////////////////////////////////////////////////////////////////////////////////

TagLib_MP4Tag *taglib_mp4_tag(TagLib_File *file)
{
  MP4::File *f = reinterpret_cast<MP4::File *>(file);
  return reinterpret_cast<TagLib_MP4Tag *>(f->tag());
}

// Global variables for iterating through an ItemList. (Not thread safe!)
MP4::ItemListMap ml;
MP4::ItemListMap::ConstIterator mli;

char *taglib_mp4_first_item(TagLib_MP4Tag *tag)
{
  MP4::Tag *t = reinterpret_cast<MP4::Tag *>(tag);

  ml = t->itemListMap();
  mli = ml.begin();
  if (mli != ml.end())
  {
    return get_cstring((*mli).first);
  }

  return NULL;
}

char *taglib_mp4_next_item()
{
  mli++;
  if (mli != ml.end())
  {
     return get_cstring((*mli).first);
  }

  return NULL;
}

char *taglib_mp4_item_string()
{
   MP4::Item i = (*mli).second;
   return get_cstring(i.toStringList().toString());
}

UINT taglib_mp4_item_artwork(char *buf, UINT max)
{
   MP4::CoverArtList l = (*mli).second.toCoverArtList();
   if (l.isEmpty()) return 0;
   MP4::CoverArt c = l.front();
   if (c.data().isNull()) return 0;
   if (c.data().isEmpty()) return 0;
   UINT size = c.data().size();
   if (buf == NULL || size > max) return size;
   UINT count = 0;
   for (count = 0; count < size; count++)
   {
     buf[count] = c.data().at(count);
   }
   return count;
}

char *taglib_mp4_find_string_item(TagLib_MP4Tag *tag, char *name)
{
  MP4::Tag *t = reinterpret_cast<MP4::Tag *>(tag);
  if (t->itemListMap().contains(name)) {
     MP4::Item i = t->itemListMap()[name];
     if (i.isValid()) {
        return get_cstring(i.toStringList().toString());
     }
  }
  return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// TagLib::MP4::Tag wrapper
////////////////////////////////////////////////////////////////////////////////

TagLib_ASFTag *taglib_asf_tag(TagLib_File *file)
{
  ASF::File *f = reinterpret_cast<ASF::File *>(file);
  return reinterpret_cast<TagLib_ASFTag *>(f->tag());
}

// Global variables for iterating through an Attribute List. (Not thread safe!)
ASF::AttributeListMap sl;
ASF::AttributeListMap::ConstIterator sli;

char *taglib_asf_first_item(TagLib_ASFTag *tag)
{
  ASF::Tag *t = reinterpret_cast<ASF::Tag *>(tag);

  sl = t->attributeListMap();
  sli = sl.begin();
  if (sli != sl.end())
  {
    return get_cstring((*sli).first);
  }

  return NULL;
}

char *taglib_asf_next_item()
{
  sli++;
  if (sli != sl.end())
  {
     return get_cstring((*sli).first);
  }

  return NULL;
}

char *taglib_asf_item_string()
{
   ASF::Attribute a = (*sli).second.front();
   return get_cstring(a.toString());
}

UINT taglib_asf_item_int()
{
   ASF::Attribute a = (*sli).second.front();
   return a.toUInt();
}

UINT taglib_asf_item_artwork(char *buf, UINT max)
{
   ASF::Picture p = (*sli).second.front().toPicture();
   if (!p.isValid()) return 0;
   if (p.picture().isNull()) return 0;
   if (p.picture().isEmpty()) return 0;
   UINT size = p.picture().size();
   if (buf == NULL || size > max) return size;
   UINT count = 0;
   for (count = 0; count < size; count++)
   {
     buf[count] = p.picture().at(count);
   }
   return count;
}

////////////////////////////////////////////////////////////////////////////////
// TagLib::Ogg::XiphComment wrapper
////////////////////////////////////////////////////////////////////////////////

TagLib_XiphTag *taglib_ogg_vorbis_xiph_tag(TagLib_File *file)
{
  Ogg::Vorbis::File *f = reinterpret_cast<Ogg::Vorbis::File *>(file);
  return reinterpret_cast<TagLib_XiphTag *>(f->tag());
}

TagLib_XiphTag *taglib_ogg_speex_xiph_tag(TagLib_File *file)
{
  Ogg::Speex::File *f = reinterpret_cast<Ogg::Speex::File *>(file);
  return reinterpret_cast<TagLib_XiphTag *>(f->tag());
}

TagLib_XiphTag *taglib_ogg_flac_xiph_tag(TagLib_File *file)
{
  Ogg::FLAC::File *f = reinterpret_cast<Ogg::FLAC::File *>(file);
  return reinterpret_cast<TagLib_XiphTag *>(f->tag());
}

TagLib_XiphTag *taglib_flac_xiph_tag(TagLib_File *file)
{
  FLAC::File *f = reinterpret_cast<FLAC::File *>(file);
  return reinterpret_cast<TagLib_XiphTag *>(f->tag());
}

// Global variables for iterating through an ItemList. (Not thread safe!)
Ogg::FieldListMap ol;
Ogg::FieldListMap::ConstIterator oli;

char *taglib_xiph_first_comment(TagLib_XiphTag *tag)
{
  Ogg::XiphComment *t = reinterpret_cast<Ogg::XiphComment *>(tag);

  ol = t->fieldListMap();
  oli = ol.begin();
  if (oli != ol.end())
  {
    return get_cstring((*oli).first);
  }

  return NULL;
}

char *taglib_xiph_next_comment()
{
  oli++;
  if (oli != ol.end())
  {
     return get_cstring((*oli).first);
  }

  return NULL;
}

char *taglib_xiph_comment_string()
{
   StringList l = (*oli).second;
   return get_cstring(l.toString());
}

char *taglib_xiph_comment_first_string()
{
   StringList l = (*oli).second;
   return get_cstring(l.front());
}

int taglib_xiph_comment_int()
{
   StringList l = (*oli).second;
   return l.front().toInt();
}


//******************************************************************************

void taglib_id3v2_set_default_text_encoding(TagLib_ID3v2_Encoding encoding)
{
  String::Type type = String::Latin1;

  switch(encoding)
  {
  case TagLib_ID3v2_Latin1:
    type = String::Latin1;
    break;
  case TagLib_ID3v2_UTF16:
    type = String::UTF16;
    break;
  case TagLib_ID3v2_UTF16BE:
    type = String::UTF16BE;
    break;
  case TagLib_ID3v2_UTF8:
    type = String::UTF8;
    break;
  }

  ID3v2::FrameFactory::instance()->setDefaultTextEncoding(type);
}
