#ifndef VCONFIGMANAGER_H
#define VCONFIGMANAGER_H

#include <QFont>
#include <QPalette>
#include <QVector>
#include <QSettings>
#include "vnotebook.h"

#include "hgmarkdownhighlighter.h"

class QJsonObject;
class QString;

class VConfigManager
{
public:
    VConfigManager();
    ~VConfigManager();
    void initialize();

    // Static helper functions
    // Read config from the directory config json file into a QJsonObject
    static QJsonObject readDirectoryConfig(const QString &path);
    static bool writeDirectoryConfig(const QString &path, const QJsonObject &configJson);
    static bool deleteDirectoryConfig(const QString &path);

    // Constants
    static const QString orgName;
    static const QString appName;

    inline QFont getMdEditFont() const;

    inline QPalette getMdEditPalette() const;

    inline QVector<HighlightingStyle> getMdHighlightingStyles() const;

    inline QString getWelcomePagePath() const;

    inline QString getTemplatePath() const;

    inline QString getTemplateCssUrl() const;

    inline QFont getBaseEditFont() const;

    inline int getCurNotebookIndex() const;
    inline void setCurNotebookIndex(int index);

    inline const QVector<VNotebook>& getNotebooks() const;
    inline void setNotebooks(const QVector<VNotebook> &notebooks);

private:
    void updateMarkdownEditStyle();
    QVariant getConfigFromSettings(const QString &section, const QString &key);
    void setConfigToSettings(const QString &section, const QString &key, const QVariant &value);
    void readNotebookFromSettings();
    void writeNotebookToSettings();

    QFont baseEditFont;
    QPalette baseEditPalette;
    QFont mdEditFont;
    QPalette mdEditPalette;
    QVector<HighlightingStyle> mdHighlightingStyles;
    QString welcomePagePath;
    QString templatePath;
    QString preTemplatePath;
    QString postTemplatePath;
    QString templateCssUrl;
    int curNotebookIndex;
    QVector<VNotebook> notebooks;

    // The name of the config file in each directory
    static const QString dirConfigFileName;
    // The name of the default configuration file
    static const QString defaultConfigFilePath;
    // QSettings for the user configuration
    QSettings *userSettings;
    // Qsettings for @defaultConfigFileName
    QSettings *defaultSettings;
};


inline QFont VConfigManager::getMdEditFont() const
{
    return mdEditFont;
}

inline QPalette VConfigManager::getMdEditPalette() const
{
    return mdEditPalette;
}

inline QVector<HighlightingStyle> VConfigManager::getMdHighlightingStyles() const
{
    return mdHighlightingStyles;
}

inline QString VConfigManager::getWelcomePagePath() const
{
    return welcomePagePath;
}

inline QString VConfigManager::getTemplatePath() const
{
    return templatePath;
}

inline QString VConfigManager::getTemplateCssUrl() const
{
    return templateCssUrl;
}

inline QFont VConfigManager::getBaseEditFont() const
{
    return baseEditFont;
}

inline int VConfigManager::getCurNotebookIndex() const
{
    return curNotebookIndex;
}

inline void VConfigManager::setCurNotebookIndex(int index)
{
    if (index == curNotebookIndex) {
        return;
    }
    curNotebookIndex = index;
    setConfigToSettings("global", "current_notebook", index);
}

inline const QVector<VNotebook>& VConfigManager::getNotebooks() const
{
    return notebooks;
}

inline void VConfigManager::setNotebooks(const QVector<VNotebook> &notebooks)
{
    this->notebooks = notebooks;
    writeNotebookToSettings();
}

#endif // VCONFIGMANAGER_H