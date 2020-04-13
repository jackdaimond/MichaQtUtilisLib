#pragma once

namespace MichaLib
{

/// This class provides the ability to store user settings like widget geometry or -state.
///
/// This class uses QSettings to load and store user settings for the application. Therefore the application name and
/// the organization and its domain must be set in the QApplication object. See QSettings for further details.
///
/// @code
/// class MyAppConf : public ApplicationSettings
/// {
///     public:
///         enum Widgets
///         {
///             MainWindow,
///             SomeDialog,
///         };
///
///         enum Setting
///         {
///             AFile,
///             MaxRecentFilesCount,
///         };
///     public:
///         AppConfiguration()
///         {
///            m_settingsPaths =
///            {
///                {Setting::AFile,     "Files/AFile"},
///                {Setting::MaxRecentFilesCount, "Files/MaxRecentFilesCount"}
///            };
///
///            m_widgetSettingsPaths =
///            {
///                {Widgets::MainWindow, "MainWindow"},
///                {Widgets::SomeDialog, "SomeDialog"}
///            };
///         }
///
///     protected:
///         bool hasLastRecentElement( SettingType setting ) const override
///         {
///             // For AFile a list of strings (here file paths) is stored
///             return setting == Setting::AFile;
///         }
/// };
///
/// class MainWindow : public QMainWindow
/// {
///     public:
///         void onInit()
///         {
///             //restore geometry and state of the main window
///             mysettings.loadWidget( MyAppConf::MainWindow, this );
///             //restore the geometry of SomeDialog.
///             mysettings.loadWidgetGeometry(MyAppConf::SomeDialog, &m_someDialog);
///
///             // load the last used path of AFile
///             QStringList flist = mysettings.loadSetting(MyAppConf::AFile).toStringList();
///             QString fn;
///             if(flist.size() > 0)
///             {
///                 fn = flist[0];
///                 loadAFile(fn);
///             }
///         }
///
///         void saveFile(const QString &path)
///         {
///             //store file
///             ...
///             // Save the path to AFile. This automatically updates the RecentFiles-List for AFile.
///             mysettings.saveSetting(MyAppConf.AFile, path);
///         }
///
///     private:
///         MyAppConf mysettings;
///         QWidget m_someDialog;
/// };
/// @endcode
///
/// @author Michael Kloske
/// @date 13.04.2020 start/mkl
class ApplicationSettings
{
    public:
        using WidgetsType = int;
        using SettingType = int;
    public:
        ApplicationSettings();
        virtual ~ApplicationSettings() = default;
        void setDefaultSettings();

        /// @name Widget settings
        ///
        /// The methods in this group loads and stores widget geometrys or -states.
        ///
        /// @{
        void saveWidgetGeometry( WidgetsType widget, QWidget *w );

        template<class T>
        void saveWidgetState( WidgetsType widget, T *w )
        {
            checkWidgetInMap( m_widgetSettingsPaths, widget );

            const QString path = "Widgets/" + m_widgetSettingsPaths.value( widget ) + "/State";
            m_settings.setValue( path, w->saveState() );
        }

        template<class T>
        void saveWidget( WidgetsType widget, T *w )
        {
            saveWidgetGeometry( widget, w );
            saveWidgetState( widget, w );
        }

        template<class T>
        void loadWidget( WidgetsType widget, T *w )
        {
            loadWidgetGeometry( widget, w );
            loadWidgetState( widget, w );
        }

        void loadWidgetGeometry( WidgetsType widget, QWidget *w );

        template<class T>
        void loadWidgetState( WidgetsType widget, T *w )
        {
            checkWidgetInMap( m_widgetSettingsPaths, widget );

            const QString path = "Widgets/" + m_widgetSettingsPaths.value( widget ) + "/State";
            const QByteArray val = m_settings.value( path ).toByteArray();
            w->restoreState( val );
        }
        /// @}

        void saveSetting( SettingType setting, const QVariant &value );
        QVariant loadSetting( SettingType setting, const QVariant &defaultValue = QVariant() );


        /// Stores a specific value if it is not already saved in the user settings.
        ///
        /// This may used to store default settings at first startup of a new version of the application.
        void storeIfNotExist( SettingType setting, const QVariant &value );
        int maxRecentFilesCount() const;
        void setMaxRecentFilesCount( int maxRecentFilesCount );

    protected:
        virtual bool hasLastRecentElement( SettingType setting ) const;
        void updateRecentFiles( SettingType setting, const QString &filename );

    protected:
        QMap<SettingType, QString> m_settingsPaths;
        QMap<WidgetsType, QString> m_widgetSettingsPaths;

    private:
        template<class T, class Type>
        inline void checkWidgetInMap( const QMap<T, QString> &map, Type &w )
        {
            Q_ASSERT( map.contains( w ) );
        }

    private:
        QSettings m_settings;
        /// Stores the maximal number of a recent items list.
        ///
        /// @see hasLastRecentElement(), updateRecentFiles()
        int m_maxRecentFilesCount = 10;
};

} //MichaLib
