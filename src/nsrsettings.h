#ifndef NSRSETTINGS_H
#define NSRSETTINGS_H

#include <QSettings>

#include "nsrsession.h"

class NSRSettings : public QSettings
{
	Q_OBJECT
public:
	explicit NSRSettings (QObject *parent = 0);
	virtual ~NSRSettings () {}
	void saveSession (NSRSession *session);
	NSRSession getLastSession ();
	NSRSession getSessionForFile (const QString& file);

	void saveFullscreenMode (bool fullscreen);
	bool isFullscreenMode () {return _isFullscreenMode;}
	void saveLastOpenDir (const QString& dir);
	QString getLastOpenDir () const {return _lastOpenDir;}
	void saveWordWrap (bool wrap);
	bool isWordWrap () const {return _isWordWrap;}
	void saveTextModeNoted ();
	bool isTextModeNoted () const {return _isTextModeNoted;}
	void saveInvertedColors (bool inverted);
	bool isInvertedColors () const {return _isInvertedColors;}
	void saveAutoCrop (bool crop);
	bool isAutoCrop () const {return _isAutoCrop;}
	bool isNewsShown () const {return _isNewsShown;}
	void saveNewsShown ();
	QString getFontFamily () const {return _fontFamily;}
	void saveFontFamily (const QString& ff);
	QString getTextEncoding () const {return _textEncoding;}
	void saveTextEncoding (const QString& textEnc);
	QStringList getLastDocuments () const;
	void removeLastDocument (const QString& path);
	void addLastDocument (const QString& path);
	bool isFirstStart () const {return _isFirstStart;}
	void saveFirstStart ();

	static QString getVersion ();
	static QStringList getSupportedEncodings ();
	static QString mapIndexToEncoding (int index);
	static int mapEncodingToIndex (const QString& encoding);
	static QString getSettingsDirectory ();

private:
	static QStringList	getSupportedEncodingsShort ();
	QString			formatFileName (const QString& name);
	void			readSession (const QString& name, NSRSession& session);
	void			cleanOldFiles ();

	bool		_isFullscreenMode;
	bool		_isWordWrap;
	bool		_isTextModeNoted;
	bool		_isInvertedColors;
	bool		_isAutoCrop;
	bool		_isNewsShown;
	bool		_isFirstStart;
	QString		_lastOpenDir;
	QString		_fontFamily;
	QString		_textEncoding;
	QStringList	_lastDocuments;
};

#endif // NSRSETTINGS_H
