TEMPLATE = subdirs

SUBDIRS += \
    AmuletCore \
    AmuletPlugins \
    AmuletGUI

INSTALLS += desktop icon

desktop.files = amulet.desktop
desktop.path = /usr/share/applications
icon.files = AmuletGUI/icons/amulet.png
icon.path = /usr/share/icons
