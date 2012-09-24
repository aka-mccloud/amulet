# Copyright 1999-2012 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI="4"

inherit cmake-utils git-2

DESCRIPTION="Audio converter based on ffmpeg"
HOMEPAGE="http://gitorious.org/amulet"
EGIT_REPO_URI="git://gitorious.org/amulet/amulet.git"

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="~amd64 ~x86 ~amd64-linux ~x86-linux"
IUSE="flac mp3"

DEPEND="flac? ( media-libs/flac )
        mp3? ( media-sound/lame )
        media-libs/taglib
        x11-libs/qt-gui:4
        x11-libs/qt-core:4"

src_install() {
        cmake-utils_src_install
}