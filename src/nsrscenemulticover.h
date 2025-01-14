#ifndef NSRSCENEMULTICOVER_H_
#define NSRSCENEMULTICOVER_H_

#include "insrscenecover.h"
#include "nsrscenecover.h"
#include "nsrreadingtheme.h"
#include "nsrreader.h"

#if BBNDK_VERSION_AT_LEAST(10,3,0)
#  include <bb/cascades/MultiCover>
#endif

#include <QObject>

class NSRSceneMultiCover :
#if BBNDK_VERSION_AT_LEAST(10,3,0)
			   public bb::cascades::MultiCover,
#else
			   public QObject,
#endif
			   public INSRSceneCover
{
	Q_OBJECT
public:
	NSRSceneMultiCover (QObject *parent = 0);
	virtual ~NSRSceneMultiCover ();

	/* INSRSceneCover interface */
	void setPageData (const NSRRenderedPage&	page,
			  const QString&		title,
			  int				pagesTotal);
	void resetPageData ();

	void updateState (bool isStatic);
	void setTextOnly (bool textOnly);
	void setInvertedColors (bool invertedColors);
	void setTextTheme (NSRReadingTheme::Type type);
	void setFontFamily (const QString& fontFamily);

private:
	NSRSceneCover *	_fullCover;
	NSRSceneCover *	_compactCover;
};

#endif /* NSRSCENEMULTICOVER_H_ */
