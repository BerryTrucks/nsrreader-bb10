#include "nsrpreferencespage.h"
#include "nsrsettings.h"

#include <bb/cascades/Container>
#include <bb/cascades/Color>
#include <bb/cascades/StackLayout>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Label>
#include <bb/cascades/TitleBar>
#include <bb/cascades/ScrollView>

using namespace bb::cascades;

NSRPreferencesPage::NSRPreferencesPage (QObject *parent) :
	Page (parent),
	_isSaveLastPos (NULL),
	_isFullscreen (NULL),
	_isTextMode (NULL),
	_isInvertedColors (NULL),
	_encodingsList (NULL)
{
	NSRSettings	settings;
	QString		defEncoding = trUtf8 ("UTF-8");

	Container *rootContainer = Container::create().horizontal(HorizontalAlignment::Fill)
						      .vertical(VerticalAlignment::Fill)
						      .layout(StackLayout::create ());

	_isSaveLastPos = ToggleButton::create().horizontal(HorizontalAlignment::Right);
	_isFullscreen = ToggleButton::create().horizontal(HorizontalAlignment::Right);
	_isTextMode = ToggleButton::create().horizontal(HorizontalAlignment::Right);
	_isInvertedColors = ToggleButton::create().horizontal(HorizontalAlignment::Right);
	_encodingsList = DropDown::create().horizontal(HorizontalAlignment::Fill)
					   .title(trUtf8 ("Text Encoding"));

	_isSaveLastPos->setChecked (settings.isLoadLastDoc ());
	_isFullscreen->setChecked (settings.isFullscreenMode ());
	_isTextMode->setChecked (settings.isWordWrap ());
	_isInvertedColors->setChecked (settings.isInvertedColors ());

	QString textEncoding = settings.getTextEncoding ();
	QStringList encodings = settings.getSupportedEncodings ();
	int encodingIndex = encodings.indexOf (textEncoding, 0);

	if (encodingIndex == -1) {
		textEncoding = defEncoding;
		encodingIndex = encodings.indexOf (textEncoding, 0);
	}

	int count = encodings.count ();
	for (int i = 0; i < count; ++i)
		_encodingsList->add (Option::create().text(encodings.at (i)));
	_encodingsList->setSelectedIndex (encodingIndex);

	/* 'Save last position' option */
	Container *firstContainer = Container::create().horizontal(HorizontalAlignment::Fill)
						       .layout(DockLayout::create());

	firstContainer->setTopPadding (40);
	firstContainer->setBottomPadding (40);
	firstContainer->setLeftPadding (20);
	firstContainer->setRightPadding (20);

	firstContainer->add (Label::create(trUtf8 ("Save Last Position")).horizontal(HorizontalAlignment::Left)
									 .vertical(VerticalAlignment::Center));
	firstContainer->add (_isSaveLastPos);

	/* 'Fullscreen mode' option */
	Container *secondContainer = Container::create().horizontal(HorizontalAlignment::Fill)
							.layout(DockLayout::create());

	secondContainer->setTopPadding (40);
	secondContainer->setBottomPadding (40);
	secondContainer->setLeftPadding (20);
	secondContainer->setRightPadding (20);

	secondContainer->add (Label::create(trUtf8 ("Fullscreen Mode")).horizontal(HorizontalAlignment::Left)
								       .vertical(VerticalAlignment::Center));
	secondContainer->add (_isFullscreen);

	/* 'Text mode' option */
	Container *thirdContainer = Container::create().horizontal(HorizontalAlignment::Fill)
						       .layout(DockLayout::create());

	thirdContainer->setTopPadding (40);
	thirdContainer->setBottomPadding (40);
	thirdContainer->setLeftPadding (20);
	thirdContainer->setRightPadding (20);

	thirdContainer->add (Label::create(trUtf8 ("Column View")).horizontal(HorizontalAlignment::Left)
								  .vertical(VerticalAlignment::Center));
	thirdContainer->add (_isTextMode);

	/* 'Invert colors' option */
	Container *fourthContainer = Container::create().horizontal(HorizontalAlignment::Fill)
							.layout(DockLayout::create());

	fourthContainer->setTopPadding (40);
	fourthContainer->setBottomPadding (40);
	fourthContainer->setLeftPadding (20);
	fourthContainer->setRightPadding (20);

	fourthContainer->add (Label::create(trUtf8 ("Invert Colors")).horizontal(HorizontalAlignment::Left)
								     .vertical(VerticalAlignment::Center));
	fourthContainer->add (_isInvertedColors);

	/* 'Text encoding' drop down list */
	Container *fifthContainer = Container::create().horizontal(HorizontalAlignment::Fill)
						       .layout(StackLayout::create());
	Label *encodingInfo = Label::create(trUtf8 ("Text encoding is used only for pure text files. "
						    "None other format supports encoding selection."))
				     .horizontal(HorizontalAlignment::Fill)
				     .vertical(VerticalAlignment::Center);
	encodingInfo->textStyle()->setFontSize (FontSize::XSmall);
	encodingInfo->setMultiline (true);

	fifthContainer->setTopPadding (40);
	fifthContainer->setBottomPadding (40);
	fifthContainer->setLeftPadding (20);
	fifthContainer->setRightPadding (20);

	fifthContainer->add (_encodingsList);
	fifthContainer->add (encodingInfo);

	/* Add all options to root layout */
	Container *zeroLine = Container::create().horizontal(HorizontalAlignment::Fill)
						 .vertical(VerticalAlignment::Fill)
						 .background(Color::Gray);
	zeroLine->setMaxHeight (1);
	zeroLine->setPreferredHeight (1);

	Container *firstLine = Container::create().horizontal(HorizontalAlignment::Fill)
						  .vertical(VerticalAlignment::Fill)
						  .background(Color::Gray);
	firstLine->setMaxHeight (1);
	firstLine->setPreferredHeight (1);

	Container *secondLine = Container::create().horizontal(HorizontalAlignment::Fill)
						   .vertical(VerticalAlignment::Fill)
						   .background(Color::Gray);
	secondLine->setMaxHeight (1);
	secondLine->setPreferredHeight (1);

	Container *thirdLine = Container::create().horizontal(HorizontalAlignment::Fill)
						  .vertical(VerticalAlignment::Fill)
						  .background(Color::Gray);
	thirdLine->setMaxHeight (1);
	thirdLine->setPreferredHeight (1);

	Container *fourthLine = Container::create().horizontal(HorizontalAlignment::Fill)
						   .vertical(VerticalAlignment::Fill)
						   .background(Color::Gray);
	fourthLine->setMaxHeight (1);
	fourthLine->setPreferredHeight (1);

	Container *fifthLine = Container::create().horizontal(HorizontalAlignment::Fill)
						  .vertical(VerticalAlignment::Fill)
						  .background(Color::Gray);
	fifthLine->setMaxHeight (1);
	fifthLine->setPreferredHeight (1);

	rootContainer->add (zeroLine);
	rootContainer->add (firstContainer);
	rootContainer->add (firstLine);
	rootContainer->add (secondContainer);
	rootContainer->add (secondLine);
	rootContainer->add (thirdContainer);
	rootContainer->add (thirdLine);
	rootContainer->add (fourthContainer);
	rootContainer->add (fourthLine);
	rootContainer->add (fifthContainer);
	rootContainer->add (fifthLine);

	ScrollView *scrollView = ScrollView::create().horizontal(HorizontalAlignment::Fill)
						     .vertical(VerticalAlignment::Fill)
						     .content(rootContainer);

	setContent (scrollView);
	setTitleBar (TitleBar::create().title (trUtf8 ("Settings")));
}

NSRPreferencesPage::~NSRPreferencesPage ()
{
}

void
NSRPreferencesPage::saveSettings ()
{
	NSRSettings settings;

	settings.saveLoadLastDoc (_isSaveLastPos->isChecked ());
	settings.saveFullscreenMode (_isFullscreen->isChecked ());
	settings.saveWordWrap (_isTextMode->isChecked ());
	settings.saveInvertedColors (_isInvertedColors->isChecked ());

	if (_encodingsList->isSelectedOptionSet ())
		settings.saveTextEncoding (_encodingsList->selectedOption()->text ());
}
