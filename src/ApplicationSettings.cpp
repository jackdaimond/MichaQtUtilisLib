#include "ApplicationSettings.h"

namespace MichaLib
{

ApplicationSettings::ApplicationSettings()
{
    setDefaultSettings();
}

void ApplicationSettings::setDefaultSettings()
{
    //storeIfNotExist( Setting::MaxRecentFilesCount, 10 );
}

void ApplicationSettings::saveWidgetGeometry( ApplicationSettings::WidgetsType widget, QWidget *w )
{
    checkWidgetInMap( m_widgetSettingsPaths, widget );

    const QString path = "Widgets/" + m_widgetSettingsPaths.value( widget ) + "/Geometry";
    m_settings.setValue( path, w->saveGeometry() );
}

void ApplicationSettings::loadWidgetGeometry( ApplicationSettings::WidgetsType widget, QWidget *w )
{
    checkWidgetInMap( m_widgetSettingsPaths, widget );

    const QString path = "Widgets/" + m_widgetSettingsPaths.value( widget ) + "/Geometry";
    const QByteArray val = m_settings.value( path ).toByteArray();
    w->restoreGeometry( val );
}

void ApplicationSettings::saveSetting( ApplicationSettings::SettingType setting, const QVariant &value )
{
    checkWidgetInMap( m_settingsPaths, setting );

    if ( hasLastRecentElement( setting ) )
    {
        updateRecentFiles( setting, value.toString() );
    }
    else
    {
        const QString path = m_settingsPaths[setting];
        m_settings.setValue( path, value );
    }
}

QVariant ApplicationSettings::loadSetting( ApplicationSettings::SettingType setting, const QVariant &defaultValue )
{
    checkWidgetInMap( m_settingsPaths, setting );

    const QString path = m_settingsPaths[setting];
    return m_settings.value( path, defaultValue );
}

void ApplicationSettings::updateRecentFiles( ApplicationSettings::SettingType setting, const QString &filename )
{
    QStringList l = loadSetting( setting ).toStringList();

    l.removeAll( filename );
    l.prepend( filename );

    while ( m_maxRecentFilesCount > 0 && l.size() > m_maxRecentFilesCount )
    {
        l.removeLast();
    }

    const QString path = m_settingsPaths[setting];
    m_settings.setValue( path, l );
}

bool ApplicationSettings::hasLastRecentElement( ApplicationSettings::SettingType ) const
{
    return false;
}

void ApplicationSettings::storeIfNotExist( ApplicationSettings::SettingType setting, const QVariant &value )
{
    QVariant v = loadSetting( setting );
    if ( !v.isValid() )
    {
        saveSetting( setting, value );
    }
}

int ApplicationSettings::maxRecentFilesCount() const
{
    return m_maxRecentFilesCount;
}

void ApplicationSettings::setMaxRecentFilesCount( int maxRecentFilesCount )
{
    m_maxRecentFilesCount = maxRecentFilesCount;
}


} //MichaLib
