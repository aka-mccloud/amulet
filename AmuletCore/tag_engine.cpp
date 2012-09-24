/**************************************************************************
 *                                                                        *
 *  Copyright (C) 2012 by Yura Ivanov <yura.i1507@gmail.com>              *
 *                                                                        *
 *  This file is part of Amulet audio converter.                          *
 *                                                                        *
 *  Amulet is free software: you can redistribute it and/or modify        *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 2 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 *  Amulet is distributed in the hope that it will be useful,             *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with Amulet.  If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                        *
 **************************************************************************/

#include <QDebug>

#include <tag.h>
#include <fileref.h>

#include "tag_engine.hpp"

TagData * TagEngine::readFromFile(const QFileInfo & file)
{
    TagData * tagData = new TagData();
    TagLib::FileRef fileRef(file.absoluteFilePath().toLocal8Bit());
    
    if (!fileRef.isNull()) {
        TagLib::Tag * tag = NULL;
        tag = fileRef.tag();
        
        if (tag) {
            tagData->album = TStringToQString(tag->album());
            tagData->artist = TStringToQString(tag->artist());
            tagData->comment = TStringToQString(tag->comment());
            tagData->genre = TStringToQString(tag->genre());
            tagData->title = TStringToQString(tag->title());
            tagData->track = tag->track();
            tagData->year = tag->year();
        }
    }
    
    return tagData;
}

bool TagEngine::writeToFile(const QFileInfo & file, TagData * tagData)
{
    TagLib::FileRef fileRef(file.absoluteFilePath().toLocal8Bit());
    
    if (!fileRef.isNull()) {
        TagLib::Tag * tag = NULL;
        tag = fileRef.tag();
        
        if (tag) {
            tag->setAlbum(TagLib::String(tagData->album.toUtf8().data(), TagLib::String::UTF8));
            tag->setArtist(TagLib::String(tagData->artist.toUtf8().data(), TagLib::String::UTF8));
            tag->setComment(TagLib::String(tagData->comment.toUtf8().data(), TagLib::String::UTF8));
            tag->setGenre(TagLib::String(tagData->genre.toUtf8().data(), TagLib::String::UTF8));
            tag->setTitle(TagLib::String(tagData->title.toUtf8().data(), TagLib::String::UTF8));
            tag->setTrack(tagData->track);
            tag->setYear(tagData->year);
        } else {
            return false;
        }
    }
    
    return fileRef.save();
}
