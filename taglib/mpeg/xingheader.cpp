/***************************************************************************
    copyright            : (C) 2003 by Ismael Orenstein
    email                : orenstein@kde.org
 ***************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#include <tbytevector.h>
#include <tstring.h>
#include <tdebug.h>

#include "xingheader.h"

using namespace TagLib;

class MPEG::XingHeader::XingHeaderPrivate
{
public:
  XingHeaderPrivate() :
    frames(0),
    size(0),
    startDelay(0),
    endDelay(0),
    vbr(false),
    valid(false)
    {}

  uint frames;
  uint size;
  uint startDelay;
  uint endDelay;
  bool vbr;
  bool valid;
};

MPEG::XingHeader::XingHeader(const ByteVector &data)
{
  d = new XingHeaderPrivate;
  parse(data);
}

MPEG::XingHeader::~XingHeader()
{
  delete d;
}

bool MPEG::XingHeader::isValid() const
{
  return d->valid;
}

TagLib::uint MPEG::XingHeader::totalFrames() const
{
  return d->frames;
}

TagLib::uint MPEG::XingHeader::totalSize() const
{
  return d->size;
}

bool MPEG::XingHeader::isVbr() const
{
  return d->vbr;
}

TagLib::uint MPEG::XingHeader::startDelay() const
{
  return d->startDelay;
}

TagLib::uint MPEG::XingHeader::endDelay() const
{
  return d->endDelay;
}

int MPEG::XingHeader::xingHeaderOffset(TagLib::MPEG::Header::Version v,
                                       TagLib::MPEG::Header::ChannelMode c)
{
  if(v == MPEG::Header::Version1) {
    if(c == MPEG::Header::SingleChannel)
      return 0x15;
    else
      return 0x24;
  }
  else {
    if(c == MPEG::Header::SingleChannel)
      return 0x0D;
    else
      return 0x15;
  }
}

void MPEG::XingHeader::parse(const ByteVector &data)
{
  // Check to see if a valid Xing header is available.

  if (data.startsWith("Xing")) {
    d->vbr = true;
  } else {
    if (!data.startsWith("Info")) return;
  }

  // Get total frames, if available.
  if (data[7] & 0x01) {
    d->frames = data.mid(8, 4).toUInt();
  }

  // Get total size, if available.
  if (data[7] & 0x02) {
    d->size = data.mid(12, 4).toUInt();
  }

  // Check for LAME header.
  if (data.size() > 143) {
    if (data.mid(120, 4) == "LAME") {

      // Encoder delays are only available for Lame 3.90+.
      if (data[124] >= '3' && data[126] >= '9') {
        uint delay = data.mid(140, 4).toUInt();
        d->startDelay = (delay & 0x00FFF000) >> 12;
        d->endDelay = (delay & 0x00000FFF);
      }
    }
  }

  d->valid = true;
}

