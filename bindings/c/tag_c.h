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

#ifndef TAGLIB_TAG_C
#define TAGLIB_TAG_C

/* Do not include this in the main TagLib documentation. */
#ifndef DO_NOT_DOCUMENT

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifdef MAKE_TAGLIB_C_LIB
#define TAGLIB_C_EXPORT __declspec(dllexport)
#else
#define TAGLIB_C_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 1)
#define TAGLIB_C_EXPORT __attribute__ ((visibility("default")))
#else
#define TAGLIB_C_EXPORT
#endif

#ifndef BOOL
#define BOOL int
#endif

#define UINT unsigned int

/*******************************************************************************
 * [ TagLib C Binding ]
 *
 * This is an interface to TagLib's "simple" API, meaning that you can read and
 * modify media files in a generic, but not specialized way.  This is a rough
 * representation of TagLib::File and TagLib::Tag, for which the documentation
 * is somewhat more complete and worth consulting.
 *******************************************************************************/

/*
 * These are used for type provide some type safety to the C API (as opposed to
 * using void *, but pointers to them are simply cast to the corresponding C++
 * types in the implementation.
 */

typedef struct { int dummy; } TagLib_File;
typedef struct { int dummy; } TagLib_Tag;
typedef struct { int dummy; } TagLib_AudioProperties;
typedef struct { int dummy; } TagLib_ID3v2Tag;
typedef struct { int dummy; } TagLib_APETag;
typedef struct { int dummy; } TagLib_ID3v2Frame;
typedef struct { int dummy; } TagLib_XingHeader;
typedef struct { int dummy; } TagLib_APEItem;
typedef struct { int dummy; } TagLib_MP4Tag;
typedef struct { int dummy; } TagLib_ASFTag;
typedef struct { int dummy; } TagLib_XiphTag;

/*!
 * By default all strings coming into or out of TagLib's C API are in UTF8.
 * However, it may be desirable for TagLib to operate on Latin1 (ISO-8859-1)
 * strings in which case this should be set to FALSE.
 */
TAGLIB_C_EXPORT void taglib_set_strings_unicode(BOOL unicode);

/*!
 * TagLib can keep track of strings that are created when outputting tag values
 * and clear them using taglib_tag_clear_strings().  This is enabled by default.
 * However if you wish to do more fine grained management of strings, you can do
 * so by setting \a management to FALSE.
 */
TAGLIB_C_EXPORT void taglib_set_string_management_enabled(BOOL management);

/*******************************************************************************
 * File API
 ******************************************************************************/

typedef enum {
  TagLib_File_MPEG,
  TagLib_File_OggVorbis,
  TagLib_File_FLAC,
  TagLib_File_MPC,
  TagLib_File_OggFlac,
  TagLib_File_WavPack,
  TagLib_File_Speex,
  TagLib_File_TrueAudio,
  TagLib_File_MP4,
  TagLib_File_ASF
} TagLib_File_Type;

/*!
 * Creates a TagLib file based on \a filename.  TagLib will try to guess the file
 * type.
 * 
 * \returns NULL if the file type cannot be determined or the file cannot
 * be opened.
 */
TAGLIB_C_EXPORT TagLib_File *taglib_file_new(const char *filename);

/*!
 * Creates a TagLib file based on \a filename.  Rather than attempting to guess
 * the type, it will use the one specified by \a type.
 */
TAGLIB_C_EXPORT TagLib_File *taglib_file_new_type(const char *filename, TagLib_File_Type type);

/*!
 * Frees and closes the file.
 */
TAGLIB_C_EXPORT void taglib_file_free(TagLib_File *file);

/*!
 * Returns true if the file is open and readble and valid information for
 * the Tag and / or AudioProperties was found.
 */

TAGLIB_C_EXPORT BOOL taglib_file_is_valid(const TagLib_File *file);

/*!
 * Returns a pointer to the tag associated with this file.  This will be freed
 * automatically when the file is freed.
 */
TAGLIB_C_EXPORT TagLib_Tag *taglib_file_tag(const TagLib_File *file);

/*!
 * Returns a pointer to the the audio properties associated with this file.  This
 * will be freed automatically when the file is freed.
 */
TAGLIB_C_EXPORT const TagLib_AudioProperties *taglib_file_audioproperties(const TagLib_File *file);

/*!
 * Saves the \a file to disk.
 */
TAGLIB_C_EXPORT BOOL taglib_file_save(TagLib_File *file);

/******************************************************************************
 * Tag API
 ******************************************************************************/

/*!
 * Returns a string with this tag's title.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
TAGLIB_C_EXPORT char *taglib_tag_title(const TagLib_Tag *tag);

/*!
 * Returns a string with this tag's artist.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
TAGLIB_C_EXPORT char *taglib_tag_artist(const TagLib_Tag *tag);

/*!
 * Returns a string with this tag's album name.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
TAGLIB_C_EXPORT char *taglib_tag_album(const TagLib_Tag *tag);

/*!
 * Returns a string with this tag's comment.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
TAGLIB_C_EXPORT char *taglib_tag_comment(const TagLib_Tag *tag);

/*!
 * Returns a string with this tag's genre.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
TAGLIB_C_EXPORT char *taglib_tag_genre(const TagLib_Tag *tag);

/*!
 * Returns the tag's year or 0 if year is not set.
 */
TAGLIB_C_EXPORT UINT taglib_tag_year(const TagLib_Tag *tag);

/*!
 * Returns the tag's track number or 0 if track number is not set.
 */
TAGLIB_C_EXPORT UINT taglib_tag_track(const TagLib_Tag *tag);

/*!
 * Sets the tag's title.
 *
 * \note By default this string should be UTF8 encoded.
 */
TAGLIB_C_EXPORT void taglib_tag_set_title(TagLib_Tag *tag, const char *title);

/*!
 * Sets the tag's artist.
 *
 * \note By default this string should be UTF8 encoded.
 */
TAGLIB_C_EXPORT void taglib_tag_set_artist(TagLib_Tag *tag, const char *artist);

/*!
 * Sets the tag's album.
 *
 * \note By default this string should be UTF8 encoded.
 */
TAGLIB_C_EXPORT void taglib_tag_set_album(TagLib_Tag *tag, const char *album);

/*!
 * Sets the tag's comment.
 *
 * \note By default this string should be UTF8 encoded.
 */
TAGLIB_C_EXPORT void taglib_tag_set_comment(TagLib_Tag *tag, const char *comment);

/*!
 * Sets the tag's genre.
 *
 * \note By default this string should be UTF8 encoded.
 */
TAGLIB_C_EXPORT void taglib_tag_set_genre(TagLib_Tag *tag, const char *genre);

/*!
 * Sets the tag's year.  0 indicates that this field should be cleared.
 */
TAGLIB_C_EXPORT void taglib_tag_set_year(TagLib_Tag *tag, UINT year);

/*!
 * Sets the tag's track number.  0 indicates that this field should be cleared.
 */
TAGLIB_C_EXPORT void taglib_tag_set_track(TagLib_Tag *tag, UINT track);

/*!
 * Frees all of the strings that have been created by the tag.
 */
TAGLIB_C_EXPORT void taglib_tag_free_strings(void);

/******************************************************************************
 * Audio Properties API
 ******************************************************************************/

/*!
 * Returns the length of the file in seconds.
 */
TAGLIB_C_EXPORT int taglib_audioproperties_length(const TagLib_AudioProperties *audioProperties);

/*!
 * Returns the bitrate of the file in kb/s.
 */
TAGLIB_C_EXPORT int taglib_audioproperties_bitrate(const TagLib_AudioProperties *audioProperties);

/*!
 * Returns the sample rate of the file in Hz.
 */
TAGLIB_C_EXPORT int taglib_audioproperties_samplerate(const TagLib_AudioProperties *audioProperties);

/*!
 * Returns the number of channels in the audio stream.
 */
TAGLIB_C_EXPORT int taglib_audioproperties_channels(const TagLib_AudioProperties *audioProperties);

/******************************************************************************
 * File Type Specific APIs
 ******************************************************************************/

/*** MPEG functions ***/
TAGLIB_C_EXPORT TagLib_ID3v2Tag *taglib_mpeg_id3v2(TagLib_File *file);
TAGLIB_C_EXPORT const TagLib_XingHeader *taglib_mpeg_xing(const TagLib_AudioProperties *audioProperties);

/*** ID3v2 Tag functions ***/
TAGLIB_C_EXPORT TagLib_ID3v2Frame *taglib_id3v2_first_frame(TagLib_ID3v2Tag *tag, char *frame);
TAGLIB_C_EXPORT TagLib_ID3v2Frame *taglib_id3v2_next_frame();
TAGLIB_C_EXPORT char *taglib_id3v2_comm_desc(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT char *taglib_id3v2_comm_text(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT char *taglib_id3v2_txxx_desc(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT char *taglib_id3v2_txxx_data(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT char *taglib_id3v2_popm_email(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT int taglib_id3v2_popm_rating(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT UINT taglib_id3v2_popm_counter(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT UINT taglib_xing_start_delay(const TagLib_XingHeader *xing);
TAGLIB_C_EXPORT UINT taglib_xing_end_delay(const TagLib_XingHeader *xing);
TAGLIB_C_EXPORT UINT taglib_id3v2_pic_size(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT UINT taglib_id3v2_pic_type(const TagLib_ID3v2Frame *frame);
TAGLIB_C_EXPORT UINT taglib_id3v2_pic_data(const TagLib_ID3v2Frame *frame, char *buf, UINT max);
TAGLIB_C_EXPORT UINT taglib_id3v2_unknown_int(const TagLib_ID3v2Frame *frame);

/*** APE Tag functions ***/
TAGLIB_C_EXPORT TagLib_APETag *taglib_mpeg_ape(TagLib_File *file);
TAGLIB_C_EXPORT const TagLib_APEItem *taglib_ape_first_item(TagLib_APETag *tag);
TAGLIB_C_EXPORT const TagLib_APEItem *taglib_ape_next_item();
TAGLIB_C_EXPORT char *taglib_ape_item_key(const TagLib_APEItem *item);
TAGLIB_C_EXPORT char *taglib_ape_item_value(const TagLib_APEItem *item);

/*** MP4 functions ***/
TAGLIB_C_EXPORT TagLib_MP4Tag *taglib_mp4_tag(TagLib_File *file);
TAGLIB_C_EXPORT char *taglib_mp4_first_item(TagLib_MP4Tag *tag);
TAGLIB_C_EXPORT char *taglib_mp4_next_item();
TAGLIB_C_EXPORT char *taglib_mp4_item_string();
TAGLIB_C_EXPORT UINT taglib_mp4_item_artwork(char *buf, UINT max);
TAGLIB_C_EXPORT char *taglib_mp4_find_string_item(TagLib_MP4Tag *tag, char *name);

/*** ASF functions ***/
TAGLIB_C_EXPORT TagLib_ASFTag *taglib_asf_tag(TagLib_File *file);
TAGLIB_C_EXPORT char *taglib_asf_first_item(TagLib_ASFTag *tag);
TAGLIB_C_EXPORT char *taglib_asf_next_item();
TAGLIB_C_EXPORT char *taglib_asf_item_string();
TAGLIB_C_EXPORT UINT taglib_asf_item_int();
TAGLIB_C_EXPORT UINT taglib_asf_item_artwork(char *buf, UINT max);

/*** OGG functions ***/
TAGLIB_C_EXPORT TagLib_XiphTag *taglib_ogg_vorbis_xiph_tag(TagLib_File *file);
TAGLIB_C_EXPORT TagLib_XiphTag *taglib_ogg_speex_xiph_tag(TagLib_File *file);
TAGLIB_C_EXPORT TagLib_XiphTag *taglib_ogg_flac_xiph_tag(TagLib_File *file);
TAGLIB_C_EXPORT TagLib_XiphTag *taglib_flac_xiph_tag(TagLib_File *file);
TAGLIB_C_EXPORT char *taglib_xiph_first_comment(TagLib_XiphTag *tag);
TAGLIB_C_EXPORT char *taglib_xiph_next_comment();
TAGLIB_C_EXPORT char *taglib_xiph_comment_string();
TAGLIB_C_EXPORT char *taglib_xiph_comment_first_string();
TAGLIB_C_EXPORT int taglib_xiph_comment_int();

/*******************************************************************************
 * Special convenience ID3v2 functions
 *******************************************************************************/

typedef enum {
  TagLib_ID3v2_Latin1,
  TagLib_ID3v2_UTF16,
  TagLib_ID3v2_UTF16BE,
  TagLib_ID3v2_UTF8
} TagLib_ID3v2_Encoding;

/*!
 * This sets the default encoding for ID3v2 frames that are written to tags.
 */

TAGLIB_C_EXPORT void taglib_id3v2_set_default_text_encoding(TagLib_ID3v2_Encoding encoding);

#ifdef __cplusplus
}
#endif
#endif /* DO_NOT_DOCUMENT */
#endif
