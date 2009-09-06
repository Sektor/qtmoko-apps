# This is a plugin
TEMPLATE=plugin
PLUGIN_FOR=qtopia
PLUGIN_TYPE=mqutim

# This plugin uses Qtopia
CONFIG+=qtopia

TARGET = icq
DEPENDPATH += . \
    settings
INCLUDEPATH += ../../include
QT += core \
    gui \
    network \
    xml
RESOURCES += icq.qrc

# Input
HEADERS += acceptauthdialog.h \
    accountbutton.h \
    addaccountform.h \
    addbuddydialog.h \
    addrenamedialog.h \
    buddycaps.h \
    buddypicture.h \
    buffer.h \
    clientIdentification.h \
    clientidentify.h \
    clientmd5login.h \
    closeconnection.h \
    connection.h \
    contactlist.h \
    customstatusdialog.h \
    deletecontactdialog.h \
    flap.h \
    icqaccount.h \
    icqlayer.h \
    icqmessage.h \
    icqpluginsystem.h \
    metainformation.h \
    modifyitem.h \
    notewidget.h \
    oscarprotocol.h \
    passwordchangedialog.h \
    passworddialog.h \
    privacylistwindow.h \
    quticqglobals.h \
    readawaydialog.h \
    requestauthdialog.h \
    searchuser.h \
    serverloginreply.h \
    servicessetup.h \
    snac.h \
    snacchannel.h \
    statusiconsclass.h \
    tlv.h \
    treebuddyitem.h \
    treegroupitem.h \
    userinformation.h \
    settings/contactsettings.h \
    settings/icqsettings.h \
    settings/networksettings.h \
    settings/statussettings.h \
    plugineventeater.h
FORMS += acceptauthdialog.ui \
    addaccountform.ui \
    addbuddydialog.ui \
    addrenamedialog.ui \
    customstatusdialog.ui \
    deletecontactdialog.ui \
    notewidget.ui \
    passwordchangedialog.ui \
    passworddialog.ui \
    privacylistwindow.ui \
    readawaydialog.ui \
    requestauthdialog.ui \
    searchuser.ui \
    userinformation.ui \
    settings/contactsettings.ui \
    settings/icqsettings.ui \
    settings/networksettings.ui \
    settings/statussettings.ui
SOURCES += acceptauthdialog.cpp \
    accountbutton.cpp \
    addaccountform.cpp \
    addbuddydialog.cpp \
    addrenamedialog.cpp \
    buddypicture.cpp \
    buffer.cpp \
    clientIdentification.cpp \
    clientidentify.cpp \
    clientmd5login.cpp \
    closeconnection.cpp \
    connection.cpp \
    contactlist.cpp \
    customstatusdialog.cpp \
    deletecontactdialog.cpp \
    flap.cpp \
    icqaccount.cpp \
    icqlayer.cpp \
    icqmessage.cpp \
    icqpluginsystem.cpp \
    metainformation.cpp \
    notewidget.cpp \
    oscarprotocol.cpp \
    passwordchangedialog.cpp \
    passworddialog.cpp \
    privacylistwindow.cpp \
    readawaydialog.cpp \
    requestauthdialog.cpp \
    searchuser.cpp \
    serverloginreply.cpp \
    servicessetup.cpp \
    snac.cpp \
    snacchannel.cpp \
    statusiconsclass.cpp \
    tlv.cpp \
    treebuddyitem.cpp \
    treegroupitem.cpp \
    userinformation.cpp \
    settings/contactsettings.cpp \
    settings/icqsettings.cpp \
    settings/networksettings.cpp \
    settings/statussettings.cpp \
    plugineventeater.cpp

