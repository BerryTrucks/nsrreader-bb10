#ifndef NSRBOOKMARKSPAGE_H_
#define NSRBOOKMARKSPAGE_H_

#include <bb/cascades/Page>
#include <bb/cascades/ListView>
#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/GroupDataModel>
#include <bb/system/SystemToast>

#include "nsrtranslator.h"

class NSRBookmarksPage : public bb::cascades::Page
{
	Q_OBJECT
public:
	NSRBookmarksPage (QObject *parent = 0);
	virtual ~NSRBookmarksPage ();
	bool hasBookmark (int page);

Q_SIGNALS:
	void bookmarkChanged (int page, bool removed);

public Q_SLOTS:
	void onDocumentOpened (const QString& file);
	void onDocumentClosed ();
	void onDocumentToBeDeleted (const QString& file);
	void addBookmark (const QString& title, int page);
	void removeBookmark (int page);

private Q_SLOTS:
	void retranslateUi ();
	void onToastFinished (bb::system::SystemUiResult::Type result);

private:
	void loadData (const QString& file);
	void saveData ();
	void unloadData ();
	void finishToast ();
	void updateUi ();

	NSRTranslator *			_translator;
	bb::cascades::GroupDataModel *	_model;
	bb::cascades::ListView *	_listView;
	bb::cascades::Container *	_emptyContainer;
	bb::cascades::Label		*_noBookmarksLabel;
	bb::cascades::Label		*_noFileLabel;
	bb::system::SystemToast		*_toast;
	QString				_openedFile;
};

#endif /* NSRBOOKMARKSPAGE_H_ */
