#include "nsrlastdocitem.h"

#include <bb/cascades/StackLayout>
#include <bb/cascades/DockLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/Color>
#include <bb/cascades/ImagePaint>
#include <bb/cascades/LayoutUpdateHandler>

#include <QFile>

using namespace bb::cascades;

NSRLastDocItem::NSRLastDocItem (bb::cascades::Container* parent) :
	CustomControl (parent),
	_imageView (NULL),
	_lockImage (NULL),
	_textView (NULL),
	_label (NULL),
	_viewContainer (NULL),
	_imgTracker (NULL),
	_solidContainer (NULL),
	_innerContainer (NULL),
	_selectAnimation (NULL),
	_selected (false)
{
	memset (_solidSelect, 0, sizeof (_solidSelect));
	memset (_innerSelect, 0, sizeof (_innerSelect));

	Container *rootContainer = Container::create().horizontal(HorizontalAlignment::Fill)
						      .vertical(VerticalAlignment::Fill)
						      .layout(DockLayout::create ())
						      .background(Color::fromRGBA (0.2, 0.2, 0.2, 1.0));

	_viewContainer = Container::create().horizontal(HorizontalAlignment::Fill)
					    .vertical(VerticalAlignment::Fill)
					    .layout(DockLayout::create())
					    .layoutProperties(StackLayoutProperties::create().spaceQuota(1.0));

	_imageView = ImageView::create().horizontal(HorizontalAlignment::Fill)
					.vertical(VerticalAlignment::Fill)
					.scalingMethod(ScalingMethod::AspectFill);
	_textView = Label::create().horizontal(HorizontalAlignment::Fill)
				   .vertical(VerticalAlignment::Fill)
				   .visible(false);
	_textView->textStyle()->setFontSize (FontSize::XXSmall);
	_textView->textStyle()->setColor (Color::Gray);
	_textView->setMultiline (true);

	_viewContainer->add (_imageView);
	_viewContainer->add (_textView);

	_label = Label::create ().horizontal(HorizontalAlignment::Center)
				 .vertical(VerticalAlignment::Center);
	_label->textStyle()->setColor (Color::White);
	_label->textStyle()->setFontSize (FontSize::XSmall);

	Container *labelContainer = Container::create().horizontal(HorizontalAlignment::Fill)
						       .vertical(VerticalAlignment::Bottom)
						       .layout(DockLayout::create ())
						       .background(Color::Black);
	labelContainer->setOpacity (0.8);
	labelContainer->setMinHeight (70);
	labelContainer->setTopMargin (0);
	labelContainer->setLeftPadding (15);
	labelContainer->setRightPadding (15);
	labelContainer->add (_label);

	_lockImage = ImageView::create().imageSource(QUrl ("asset:///page-lock.png"))
					.horizontal(HorizontalAlignment::Right)
					.vertical(VerticalAlignment::Top)
					.visible(false);

	rootContainer->add (_viewContainer);
	rootContainer->add (labelContainer);
	rootContainer->add (_lockImage);

	_imgTracker = new ImageTracker (this);
	Q_ASSERT (connect (_imgTracker, SIGNAL (stateChanged (bb::cascades::ResourceState::Type)),
			   this, SLOT (onImageStateChanged (bb::cascades::ResourceState::Type))));

	Container *mainContainer = Container::create().horizontal(HorizontalAlignment::Fill)
						      .vertical(VerticalAlignment::Fill)
						      .layout(DockLayout::create())
						      .background(Color::Black);

	_solidContainer = Container::create().horizontal(HorizontalAlignment::Fill)
					     .vertical(VerticalAlignment::Fill)
					     .layout(DockLayout::create())
					     .background(Color::Transparent);

	_solidSelect[0] = Container::create().horizontal(HorizontalAlignment::Fill)
					     .vertical(VerticalAlignment::Top)
					     .background(Color::fromRGBA (0, 0.66, 0.87, 1.0));
	_solidSelect[1] = Container::create().horizontal(HorizontalAlignment::Right)
					     .vertical(VerticalAlignment::Center)
					     .background(Color::fromRGBA (0, 0.66, 0.87, 1.0));
	_solidSelect[2] = Container::create().horizontal(HorizontalAlignment::Fill)
					     .vertical(VerticalAlignment::Bottom)
					     .background(Color::fromRGBA (0, 0.66, 0.87, 1.0));
	_solidSelect[3] = Container::create().horizontal(HorizontalAlignment::Left)
					     .vertical(VerticalAlignment::Center)
					     .background(Color::fromRGBA (0, 0.66, 0.87, 1.0));

	_solidSelect[0]->setPreferredHeight (4);
	_solidSelect[1]->setPreferredWidth (4);
	_solidSelect[2]->setPreferredHeight (4);
	_solidSelect[3]->setPreferredWidth (4);

	_solidContainer->add (_solidSelect[0]);
	_solidContainer->add (_solidSelect[1]);
	_solidContainer->add (_solidSelect[2]);
	_solidContainer->add (_solidSelect[3]);

	_solidContainer->setVisible (false);

	_innerContainer = Container::create().horizontal(HorizontalAlignment::Fill)
					     .vertical(VerticalAlignment::Fill)
					     .layout(DockLayout::create())
					     .background(Color::Transparent);
	_innerContainer->setTopPadding (4);
	_innerContainer->setRightPadding (4);
	_innerContainer->setBottomPadding (4);
	_innerContainer->setLeftPadding (4);

	_innerSelect[0] = Container::create().horizontal(HorizontalAlignment::Fill)
					     .vertical(VerticalAlignment::Top)
					     .background(Color::fromRGBA (0, 0.66, 0.87, 1.0));
	_innerSelect[1] = Container::create().horizontal(HorizontalAlignment::Right)
					     .vertical(VerticalAlignment::Center)
					     .background(Color::fromRGBA (0, 0.66, 0.87, 1.0));
	_innerSelect[2] = Container::create().horizontal(HorizontalAlignment::Fill)
					     .vertical(VerticalAlignment::Bottom)
					     .background(Color::fromRGBA (0, 0.66, 0.87, 1.0));
	_innerSelect[3] = Container::create().horizontal(HorizontalAlignment::Left)
					     .vertical(VerticalAlignment::Center)
					     .background(Color::fromRGBA (0, 0.66, 0.87, 1.0));

	_innerSelect[0]->setPreferredHeight (8);
	_innerSelect[1]->setPreferredWidth (8);
	_innerSelect[2]->setPreferredHeight (8);
	_innerSelect[3]->setPreferredWidth (8);

	_innerContainer->setOpacity (0.0);

	_innerContainer->add (_innerSelect[0]);
	_innerContainer->add (_innerSelect[1]);
	_innerContainer->add (_innerSelect[2]);
	_innerContainer->add (_innerSelect[3]);

	rootContainer->add (_solidContainer);
	rootContainer->add (_innerContainer);

	_selectAnimation = FadeTransition::create().duration(250).delay(100).to(0.5).target(_innerContainer);


	LayoutUpdateHandler::create(this).onLayoutFrameChanged (this,
							       SLOT (onLayoutFrameChanged (QRectF)));

	mainContainer->add (rootContainer);
	setRoot (mainContainer);
}

NSRLastDocItem::~NSRLastDocItem ()
{
}

void
NSRLastDocItem::updateItem (const QString&	title,
			    const QString&	imgPath,
			    const QString&	text,
			    const QString&	path,
			    bool		encrypted)
{
	_label->setText (title);
	_path = path;

	if (QFile::exists (imgPath)) {
		_textView->setVisible (false);
		_imageView->setVisible (true);
		_imgTracker->setImageSource (QUrl::fromLocalFile (imgPath));
		_viewContainer->setBottomMargin (0);
	} else {
		_imageView->setVisible (false);
		_textView->setVisible (true);
		_textView->setText (text);
		_viewContainer->setBottomMargin (10);
	}

	_lockImage->setVisible (encrypted);
}

void
NSRLastDocItem::select (bool select)
{
	if (_selected == select)
		return;

	_selected = select;

	_solidContainer->setVisible (select);
	_innerContainer->setVisible (select);

//	_innerContainer->setOpacity (select ? 1.0 : 0.0);
//	_solidContainer->setOpacity (select ? 1.0 : 0.0);
}

void
NSRLastDocItem::reset (bool selected, bool activated)
{
	select (selected);
	activate (activated);
}

void
NSRLastDocItem::activate (bool activate)
{
	if (_selected)
		return;

	if (activate) {
		_innerContainer->setOpacity (0.0);
		_solidContainer->setOpacity (1.0);
		_selectAnimation->play ();
		_solidContainer->setVisible (true);
		_innerContainer->setVisible (true);
	} else {
		_selectAnimation->stop ();
		_solidContainer->setVisible (false);
		_innerContainer->setVisible (false);
		_innerContainer->setOpacity (1.0);
		_solidContainer->setOpacity (1.0);
	}
}

QString
NSRLastDocItem::getDocumentPath () const
{
	return _path;
}

QString
NSRLastDocItem::getDocumentTitle () const
{
	return _label->text ();
}

void
NSRLastDocItem::onImageStateChanged (bb::cascades::ResourceState::Type state)
{
	if (state == ResourceState::Loaded) {
		_imageView->setImage (_imgTracker->image ());

		if ((double) _imgTracker->height () / _imgTracker->width () < 1.2) {
			_imageView->setScalingMethod (ScalingMethod::AspectFit);
			_imageView->setVerticalAlignment (VerticalAlignment::Fill);
			_imageView->setHorizontalAlignment (HorizontalAlignment::Fill);
		} else {
			_imageView->setScalingMethod (ScalingMethod::AspectFill);
			_imageView->setVerticalAlignment (VerticalAlignment::Fill);
			_imageView->setHorizontalAlignment (HorizontalAlignment::Fill);
		}
	}
}

void
NSRLastDocItem::onLayoutFrameChanged (const QRectF& rect)
{
	_solidSelect[1]->setPreferredHeight (rect.height () - 8);
	_solidSelect[3]->setPreferredHeight (rect.height () - 8);
	_innerSelect[1]->setPreferredHeight (rect.height () - 24);
	_innerSelect[3]->setPreferredHeight (rect.height () - 24);
}
