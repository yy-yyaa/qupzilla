/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2014  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "bookmarkitem.h"

BookmarkItem::BookmarkItem(BookmarkItem::Type type, BookmarkItem *parent)
    : m_type(type)
    , m_parent(parent)
    , m_expanded(false)
{
    if (m_parent) {
        parent->addChild(this);
    }
}

BookmarkItem::~BookmarkItem()
{
    qDeleteAll(m_children);
}

BookmarkItem::Type BookmarkItem::type() const
{
    return m_type;
}

void BookmarkItem::setType(BookmarkItem::Type type)
{
    m_type = type;
}

BookmarkItem *BookmarkItem::parent() const
{
    return  m_parent;
}

QList<BookmarkItem *> BookmarkItem::children() const
{
    return m_children;
}

QUrl BookmarkItem::url() const
{
    return  m_url;
}

void BookmarkItem::setUrl(const QUrl &url)
{
    m_url = url;
}

QString BookmarkItem::title() const
{
    return m_title;
}

void BookmarkItem::setTitle(const QString &title)
{
    m_title = title;
}

QString BookmarkItem::description() const
{
    return m_description;
}

void BookmarkItem::setDescription(const QString &description)
{
    m_description = description;
}

QString BookmarkItem::keyword() const
{
    return m_keyword;
}

void BookmarkItem::setKeyword(const QString &keyword)
{
    m_keyword = keyword;
}

bool BookmarkItem::isExpanded() const
{
    return m_type == Root ? true : m_expanded;
}

void BookmarkItem::setExpanded(bool expanded)
{
    m_expanded = expanded;
}

void BookmarkItem::addChild(BookmarkItem *child, int index)
{
    if (child->m_parent) {
        child->m_parent->removeChild(child);
    }

    child->m_parent = this;

    if (index == -1) {
        m_children.append(child);
    }
    else {
        m_children.insert(index, child);
    }
}

void BookmarkItem::removeChild(BookmarkItem *child)
{
    child->m_parent = 0;
    m_children.removeOne(child);
}

BookmarkItem::Type BookmarkItem::typeFromString(const QString &string)
{
    if (string == QLatin1String("url")) {
        return Url;
    }

    if (string == QLatin1String("folder")) {
        return Folder;
    }

    if (string == QLatin1String("separator")) {
        return Separator;
    }

    return Invalid;
}

QString BookmarkItem::typeToString(BookmarkItem::Type type)
{
    switch (type) {
    case Url:
        return QString("url");

    case Folder:
        return QString("folder");

    case Separator:
        return QString("separator");

    default:
        return QString("invalid");
    }
}