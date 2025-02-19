#ifndef NSRLASTDOCSPAGE_H_
#define NSRLASTDOCSPAGE_H_

#include "nsrlastdocslistview.h"
#include "nsrtranslator.h"

#include <bb/cascades/Page>
#include <bb/cascades/GridListLayout>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/Container>

#include <QObject>

class NSRLastDocsPage : public bb::cascades::Page
{
	Q_OBJECT
public:
	NSRLastDocsPage (QObject *parent = 0);
	virtual ~NSRLastDocsPage ();

	void finishToast ();

Q_SIGNALS:
	void requestDocument (const QString& path);
	void documentToBeDeleted (const QString& path);

public Q_SLOTS:
	void onDocumentOpened (const QString& file);
	void onThumbnailRendered ();

private Q_SLOTS:
	void onOrientationAboutToChange (bb::cascades::UIOrientation::Type type);
	void onListItemTriggered (QVariantList indexPath);
	void onModelUpdated (bool isEmpty);
	void onDynamicDUFactorChanged (float dduFactor);

private:
	void loadData ();
	QVariant createModelItem (const QString& file);

	QString				_lastOpenedFile;
	NSRTranslator *			_translator;
	NSRLastDocsListView *		_listView;
	bb::cascades::GridListLayout *	_listLayout;
	bb::cascades::Container *	_rootContainer;
	bb::cascades::Container *	_emptyContainer;
};

#endif /* NSRLASTDOCSPAGE_H_ */
